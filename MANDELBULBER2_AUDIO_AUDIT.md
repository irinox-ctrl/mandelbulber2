# MANDELBULBER2 AUDIO-SYSTEEM: Nucleaire Diepte-Audit

**Datum**: 2026-04-22  
**Bestanden**: `ao_modes.h`, `audio_fft_data.h/cpp`, `audio_track.h/cpp`, `audio_track_collection.h/cpp`  
**Scope**: Audio decoding, FFT-analyse, band-pass filtering, animatie-curve generatie, track collectie management

---

## INHOUDSOPGAVE

1. [Architectuur-Overzicht](#1-architectuur-overzicht)
2. [cAudioFFTData — De FFT Container](#2-caudiofftdata--de-fft-container)
3. [cAudioTrack — De Audio Verwerkingsmotor](#3-caudiotrack--de-audio-verwerkingsmotor)
4. [De FFT Wiskunde](#4-de-fft-wiskunde)
5. [Band-Pass Extractie & Pitch Detectie](#5-band-pass-extractie--pitch-detectie)
6. [Animatie-Curve Filters](#6-animatie-curve-filters)
7. [cAudioTrackCollection — De Track Manager](#7-caudiotrackcollection--de-track-manager)
8. [Bugs & Riskante Code](#8-bugs--riskante-code)
9. [Appendix: ao_modes.h](#9-appendix-aomodesh)

---

## 1. Architectuur-Overzicht

```
[Audio Bestand (.wav/.mp3)]
        |
        v
[cAudioTrack::LoadAudio()]
        |-- libsndfile (primair)
        |-- QAudioDecoder (fallback)
        |-- NetRender (client-side download)
        |
        v
[rawAudio: vector<float>]  (mono, gesampeld op originele sampleRate)
        |
        v
[cAudioTrack::calculateFFT()]
        |-- Hann window
        |-- GSL FFT (radix-2)
        |-- Magnitude berekening
        |-- Averaging over oversample frames
        |
        v
[fftAudio: vector<cAudioFFTData>]  (per animatie-frame)
        |
        v
[cAudioTrack::calculateAnimation()]
        |-- Band-pass extractie (midFreq + bandwidth)
        |-- Pitch mode (spectrale centroid) of Energy mode (gemiddelde)
        |-- Temporal smoothing (0.5 * frame + 0.5 * prev)
        |
        v
[animation: QVector<float>]  (per animatie-frame, 0..1 genormaliseerd)
        |
        v
[Optionele Post-Processing]
        |-- binaryFilter()  -> gate/hysteresis
        |-- decayFilter()   -> envelope follower
        |-- smoothFilter()  -> IIR low-pass
        |
        v
[cAudioTrackCollection::RefreshAllAudioTracks()]
        |
        v
[Gebruik in animation_frames.cpp::ApplyAudioAnimation()]
```

---

## 2. cAudioFFTData — De FFT Container

**Bestand**: `audio_fft_data.h/cpp` (49 + 48 regels)

Dit is de **simpelst mogelijke data-structuur** — een platte C-array van 2048 floats:

```cpp
class cAudioFFTData {
public:
    static const int fftSize = 2048;
    float data[fftSize];  // 8KB per object
};
```

| Eigenschap | Waarde |
|-----------|--------|
| FFT grootte | 2048 samples |
| Frequentie-resolutie @ 44.1kHz | ~21.5 Hz per bin |
| Nyquist frequentie | 22.05 kHz |
| Memory footprint | 8 KB |

**Initialisatie**: Alle waarden worden op 0.0 gezet in de constructor (range-based for loop).

**Opmerking**: Er is **geen complexe data** opgeslagen. Na de FFT wordt direct de magnitude $\sqrt{re^2 + im^2}$ berekend en opgeslagen. Fase-informatie gaat **verloren** — dit is correct voor audio-visualisatie maar niet voor reconstructie.

---

## 3. cAudioTrack — De Audio Verwerkingsmotor

**Bestand**: `audio_track.h/cpp` (109 + 500 regels)

### 3.1 State Machine

```cpp
class cAudioTrack : public QObject {
    std::vector<float> rawAudio;          // Ruwe mono audio samples
    std::vector<cAudioFFTData> fftAudio;  // FFT per animatie-frame
    QVector<float> animation;             // Geëxtraheerde band per frame
    
    bool loaded;           // Bestand succesvol geladen
    bool loadingInProgress; // Qt decoder is bezig
    bool fftCalculated;    // FFT is berekend
    
    double framesPerSecond; // Animatie fps (default 30)
    int numberOfFrames;     // Totaal aantal animatie-frames
    int soundDelay;         // Frame offset (positief = vertraging, negatief = vooruit)
};
```

### 3.2 Audio Loading Pipeline

#### Primair: libsndfile (`#ifdef USE_SNDFILE`)

```cpp
SNDFILE *infile = sf_open(filename.toLocal8Bit().constData(), SFM_READ, &sfInfo);
sampleRate = sfInfo.samplerate;

std::vector<float> tempBuff(sfInfo.frames * sfInfo.channels);
sf_readf_float(infile, tempBuff.data(), sfInfo.frames);

// Mix naar mono
for (int64_t i = 0; i < readSamples; i++) {
    float sample = 0.0;
    for (int chan = 0; chan < sfInfo.channels; chan++) {
        sample += tempBuff[i * sfInfo.channels + chan];
    }
    sample /= sfInfo.channels;  // Gemiddelde van alle kanalen
    rawAudio[i] = sample;
    maxVolume = qMax(sample, maxVolume);
}
```

**Kenmerken**:
- Ondersteunt elk formaat dat libsndfile aankan (WAV, FLAC, OGG, etc.)
- Automatische **mono-downmix** door kanalen te middelen
- Synchroon laden (blocking)

#### Fallback: QAudioDecoder

```cpp
decoder.reset(new QAudioDecoder());
decoder->setAudioFormat(desiredFormat);  // Mono, 44.1kHz, 16-bit signed int
decoder->setSourceFilename(filename);
decoder->start();

while (loadingInProgress) {
    QApplication::processEvents();  // Event loop draait tijdens laden!
}
```

**Kenmerken**:
- Asynchroon via Qt event loop
- Formaat conversie naar mono 16-bit signed int
- Buffer wordt gelezen per frame en geconverteerd:
```cpp
qint16 *frames = audioBuffer.data<qint16>();
for (int i = 0; i < frameCount; i++) {
    float sample = frames[i] / 32768.0f;  // Normaliseer naar [-1, 1]
    rawAudio.push_back(sample);
    maxVolume = qMax(sample, maxVolume);
}
```

**NetRender support**:
```cpp
if (gNetRender->IsClient()) {
    filename = gNetRender->GetFileFromNetRender(_filename, -1);
}
```

Audio bestanden worden **gedownload** naar clients via het NetRender systeem. Dit zorgt ervoor dat distributed rendering dezelfde audio-bron heeft.

### 3.3 FFT Berekening

```cpp
void cAudioTrack::calculateFFT() {
    if (loaded && !fftCalculated && length > cAudioFFTData::fftSize) {
        fftAudio.resize(numberOfFrames);
        
        const int overSample = int(sampleRate / framesPerSecond / fftSize + 2);
        
        #pragma omp parallel for
        for (int frame = 0; frame < numberOfFrames; ++frame) {
            cAudioFFTData fftFrame;
            
            for (int ov = 0; ov < overSample; ov++) {
                int sampleOffset = int(qint64(frame * overSample + ov) 
                                       * sampleRate / framesPerSecond / overSample);
                
                // 1. Hann window + complex data preparatie
                double fftData[fftSize * 2];
                for (int i = 0; i < fftSize; i++) {
                    fftData[2*i] = double(getSample(i + sampleOffset)) 
                                 * 0.5 * (1.0 - cos((2.0 * M_PI * i) / (fftSize - 1)));
                    fftData[2*i + 1] = 0.0;
                }
                
                // 2. GSL FFT
                gsl_fft_complex_radix2_forward(fftData, 1, fftSize);
                
                // 3. Magnitude berekening + averaging
                for (int i = 0; i < fftSize; i++) {
                    float re = fftData[2*i];
                    float im = fftData[2*i + 1];
                    float absVal = sqrt(re*re + im*im);
                    fftFrame.data[i] += absVal / overSample;  // Gemiddelde over oversamples
                    maxFft = qMax(absVal, maxFft);
                    maxFftArray.data[i] = qMax(maxFftArray.data[i], absVal);
                }
            }
            fftAudio[frame] = fftFrame;
        }
        fftCalculated = true;
    }
}
```

### 3.4 OverSample Factor

```cpp
const int overSample = int(sampleRate / framesPerSecond / fftSize + 2);
```

| Scenario | sampleRate | fps | fftSize | overSample |
|----------|-----------|-----|---------|------------|
| Standaard | 44100 | 30 | 2048 | 2 |
| Hoge fps | 44100 | 60 | 2048 | 2 |
| Lage fps | 44100 | 10 | 2048 | 4 |

De overSample bepaalt hoeveel **overlapende** FFT vensters er per animatie-frame worden berekend. Hogere waarden = betere tijdsresolutie maar meer CPU-belasting.

### 3.5 Band-Pass Extractie

```cpp
float cAudioTrack::getBand(int frame, double midFreq, double bandwidth, bool pitchMode) const {
    int first = freq2FftPos(midFreq - 0.5 * bandwidth);
    int last  = freq2FftPos(midFreq + 0.5 * bandwidth);
    // Clamp naar [0, fftSize/2]
    
    if (pitchMode) {
        // Spectrale centroid (gewogen gemiddelde)
        double nominator = 0.0, denominator = 0.0;
        for (int i = first; i <= last; i++) {
            double val = i - first;
            double weight = pow(double(fft.data[i]), 5.0);  // 5e macht = sterke gewichting van pieken
            nominator += val * weight;
            denominator += weight;
        }
        value = nominator / (denominator + 0.1) / (last - first + 1);
    }
    else {
        // Energie gemiddelde, genormaliseerd
        double sum = 0.0;
        float maxVal = 0.0;
        for (int i = first; i <= last; i++) {
            sum += fft.data[i];
            maxVal += maxFftArray.data[i];
        }
        maxVal /= count;
        value = sum / count / maxVal;  // Genormaliseerd naar [0, ~1]
    }
}
```

### 3.6 Animatie-Curve Generatie

```cpp
void cAudioTrack::calculateAnimation(double midFreq, double bandwidth, bool pitchMode) {
    animation.clear();
    for (int i = 0; i < numberOfFrames; i++) {
        float value;
        if (i == 0)
            value = getBand(i, midFreq, bandwidth, pitchMode);
        else
            value = 0.5f * (getBand(i, midFreq, bandwidth, pitchMode)
                          + getBand(i - 1, midFreq, bandwidth, pitchMode));
        animation.append(value);
    }
}
```

**Temporal smoothing**: Elke frame is het gemiddelde van zichzelf en de vorige. Dit voorkomt hakkeltjes.

### 3.7 Post-Processing Filters

#### Decay Filter (Envelope Follower)

```cpp
void cAudioTrack::decayFilter(double strength) {
    float value = 0.0f;
    for (int i = 0; i < numberOfFrames; i++) {
        if (animation[i] > value) {
            value = animation[i];  // Instant attack
        } else {
            value = (animation[i] - value) / strength + value;  // Exponentiële decay
        }
        animation[i] = value;
    }
}
```

**Wiskunde**:
$$v_{out}[n] = \begin{cases} v_{in}[n] & \text{als } v_{in}[n] > v_{out}[n-1] \\ v_{out}[n-1] + \frac{v_{in}[n] - v_{out}[n-1]}{strength} & \text{anders} \end{cases}$$

Dit is een **peak detector met exponentiële decay** — het volgt de pieken van de audio en laat ze langzaam terugvallen.

#### Smooth Filter (IIR Low-Pass)

```cpp
void cAudioTrack::smoothFilter(double strength) {
    float value = 0.0f;
    for (int i = 0; i < numberOfFrames; i++) {
        value = (animation[i] - value) / strength + value;
        animation[i] = value;
    }
}
```

**Wiskunde**:
$$v_{out}[n] = v_{out}[n-1] + \frac{v_{in}[n] - v_{out}[n-1]}{strength}$$

Dit is een **eerste-orde IIR low-pass filter** met cutoff-afhankelijk van `strength`.

#### Binary Filter (Gate/Hysteresis)

```cpp
void cAudioTrack::binaryFilter(double thresh, int lengthInput) {
    float value = 0.0f;
    int count = 0;
    bool counterWasReset = false;
    for (int i = 0; i < numberOfFrames; i++) {
        count++;
        if (animation[i] > thresh) {
            if (!counterWasReset) {
                count = 0;
                counterWasReset = true;
            }
            value = 1.0f;  // ON
        }
        else if (count > lengthInput) {
            value = 0.0f;  // OFF
            count = 0;
            counterWasReset = false;
        }
        animation[i] = value;
    }
}
```

**Gedrag**: De output is binair (0 of 1). De threshold bepaalt wanneer de gate opent. De `lengthInput` parameter voegt **hysteresis** toe: pas na `lengthInput` frames onder de threshold wordt de gate gesloten. Dit voorkomt snel flikkeren.

---

## 4. De FFT Wiskunde

### 4.1 Hann Window

```cpp
fftData[2*i] = sample * 0.5 * (1.0 - cos((2.0 * M_PI * i) / (fftSize - 1)));
```

$$w[n] = 0.5 \cdot \left(1 - \cos\left(\frac{2\pi n}{N-1}\right)\right)$$

**Eigenschappen**:
- Vermindert **spectrale leakage** door de randen naar nul te brengen
- Main lobe breedte: 2 bins
- Side lobe attenuatie: ~31 dB

### 4.2 GSL FFT

```cpp
double fftData[fftSize * 2];  // [re0, im0, re1, im1, ...]
gsl_fft_complex_radix2_forward(data, 1, fftSize);
```

De GSL complexe radix-2 FFT vereist dat `fftSize` een **macht van 2** is. 2048 = $2^{11}$, dus dit is geldig.

**Magnitude**:
$$|X[k]| = \sqrt{Re(X[k])^2 + Im(X[k])^2}$$

### 4.3 Frequentie-Bin Mapping

```cpp
int cAudioTrack::freq2FftPos(double freq) const {
    return int(double(fftSize) / double(sampleRate) * freq);
}
```

| Frequentie | FFT bin @ 44.1kHz, N=2048 |
|-----------|---------------------------|
| 20 Hz (laagste hoorbaar) | ~1 |
| 100 Hz | ~5 |
| 1000 Hz | ~46 |
| 10000 Hz | ~465 |
| 20000 Hz (Nyquist) | ~930 |

---

## 5. Band-Pass Extractie & Pitch Detectie

### 5.1 Energy Mode (pitchMode = false)

```cpp
sum = 0;
for (i = first; i <= last; i++) sum += fft.data[i];
value = sum / count / maxVal;
```

Dit geeft de **gemiddelde energie** in het bandje, genormaliseerd door het maximale FFT spectrum (`maxFftArray`).

### 5.2 Pitch Mode (pitchMode = true)

```cpp
for (i = first; i <= last; i++) {
    double val = i - first;  // Relatieve positie in band
    double weight = pow(double(fft.data[i]), 5.0);  // Sterke gewichting
    nominator += val * weight;
    denominator += weight;
}
value = nominator / (denominator + 0.1) / (last - first + 1);
```

Dit berekent de **spectrale centroid** (zwaartepunt van de frequentie-energie) binnen het bandje. De 5e macht van de amplitude zorgt ervoor dat sterke pieken zwaarder wegen dan zwakke ruis.

**Gebruik**: Pitch mode is nuttig als je de "toonhoogte" binnen een band wilt volgen, bijvoorbeeld voor een baslijn die op en neer gaat.

---

## 6. Animatie-Curve Filters

| Filter | Wiskunde | Visueel Effect |
|--------|----------|----------------|
| `decayFilter` | $v_{out} = \max(v_{in}, v_{out} + (v_{in} - v_{out})/strength)$ | Peak hold met fade-out |
| `smoothFilter` | $v_{out} = v_{out} + (v_{in} - v_{out})/strength$ | Gladdere curves |
| `binaryFilter` | Hysteresis gate: ON als > thresh, OFF na length frames | Stroboscoop/beat effect |

---

## 7. cAudioTrackCollection — De Track Manager

**Bestand**: `audio_track_collection.h/cpp` (77 + 256 regels)

### 7.1 Fake Copy Constructor

```cpp
/* Warning! this is fake constructor to avoid copying audio data to cUndo buffers */
cAudioTrackCollection(const cAudioTrackCollection &collection) {
    Q_UNUSED(collection);
    audioTracks.clear();
}
```

Dit is een **architecturale hack**: wanneer de gebruiker een undo stap maakt, wordt de `cAnimationFrames` gekopieerd naar de undo buffer. De `cAudioTrackCollection` zit in `cAnimationFrames`. Zonder deze fake copy constructor zou **alle ruwe audio + FFT data** worden gekopieerd naar de undo buffer, wat honderden megabytes per stap zou verbruiken.

### 7.2 Parameter Naming Conventie

```cpp
QString FullParameterName(const QString &nameOfSoundParameter, const QString parameterName) const {
    return prefix + "_" + nameOfSoundParameter + "_" + parameterName;
}
```

Voorbeelden:
- `animsound_enable_main_camera_x` (keyframe animatie)
- `flightanimsound_enable_main_camera_x` (flight animatie)

### 7.3 Automatische Parameter Generatie

Wanneer een audio track wordt toegevoegd, worden automatisch **16 parameters** aangemaakt in de parameter container:

| Parameter | Type | Default | Beschrijving |
|-----------|------|---------|--------------|
| `enable` | bool | false | Audio-modulatie aan/uit |
| `soundfile` | string | "" | Pad naar audio bestand |
| `midfreq` | double | 1000.0 | Middenfrequentie van de band (5 - 20000 Hz) |
| `bandwidth` | double | 200.0 | Breedte van de band (5 - 20000 Hz) |
| `additionfactor` | double | 1.0 | Additieve amplitude (-65535 - 65535) |
| `multfactor` | double | 1.0 | Multiplicatieve amplitude (0 - 20000) |
| `negative` | bool | false | Negatieve modus (delen in plaats van vermenigvuldigen) |
| `pitchmode` | bool | false | Spectrale centroid in plaats van energie |
| `decayfilter` | bool | false | Decay filter toepassen |
| `smoothfilter` | bool | false | Smooth filter toepassen |
| `binaryfilter` | bool | false | Binary/gate filter toepassen |
| `decaystrength` | double | 5.0 | Decay factor (0.01 - 1000) |
| `smoothstrength` | double | 5.0 | Smooth factor (0.01 - 1000) |
| `binarythresh` | double | 0.5 | Threshold voor binary gate (0 - 1) |
| `binarylength` | int | 1 | Minimum frames onder threshold voor OFF (1 - 1000) |
| `sounddelay` | int | 0 | Frame offset (-1000000 - 1000000) |

### 7.4 Refresh Pipeline

```cpp
void cAudioTrackCollection::RefreshAllAudioTracks(std::shared_ptr<cParameterContainer> params) {
    for (elke track) {
        track->setFramesPerSecond(params->Get<double>("keyframe_frames_per_second"));
        track->setSoundDelay(params->Get<int>(...sounddelay...));
        
        track->calculateFFT();
        track->calculateAnimation(midFreq, bandwidth, pitchmode);
        
        if (binaryfilter) track->binaryFilter(thresh, length);
        if (decayfilter)  track->decayFilter(strength);
        if (smoothfilter) track->smoothFilter(strength);
    }
}
```

De volledige pipeline wordt **herberekend** bij elke refresh. Dit is nodig omdat parameters (midFreq, bandwidth, filters) door de gebruiker kunnen worden gewijzigd.

### 7.5 HTTP Support

```cpp
cResourceHttpProvider httpProvider(filename);
if (httpProvider.IsUrl()) filename = httpProvider.cacheAndGetFilename();
```

Audio bestanden kunnen **vanaf een URL** worden geladen. Het bestand wordt eerst gecached naar de lokale schijf en daarna als normaal bestand behandeld.

---

## 8. Bugs & Riskante Code

### Riskante Code #1: QAudioDecoder blockt de event loop

```cpp
while (loadingInProgress) {
    QApplication::processEvents();  // <<<< RE-ENTRANT RISICO
}
```

De `LoadAudio()` functie met QAudioDecoder draait een **busy-wait loop** met `processEvents()`. Dit kan leiden tot:
- Re-entrantie problemen als andere slots worden aangeroepen tijdens het laden
- UI freeze als het laden lang duurt
- Hogere CPU-belasting tijdens laden

**Aanbeveling**: Gebruik een QEventLoop met een QTimer timeout, of maak het laden volledig asynchroon.

### Riskante Code #2: maxFftArray is globaal per track, niet per band

```cpp
maxVal += maxFftArray.data[i];  // In getBand()
maxVal /= count;
value = sum / count / maxVal;
```

De `maxFftArray` bevat het **maximum per FFT bin over ALLE frames**. Dit betekent dat als één frame een piek heeft in een bepaalde bin, de normalisatie van ALLE andere frames wordt beïnvloed. Dit kan leiden tot ondergewaardeerde waarden in rustige secties van het nummer.

### Riskante Code #3: Geen bounds check bij getAnimation()

```cpp
float cAudioTrack::getAnimation(int frame) const {
    if (numberOfFrames > 0) {
        if (frame < numberOfFrames) return animation[frame];
        else return animation.last();  // <<<< Clamping, maar geen lower bound check!
    }
}
```

Als `frame < 0` (wat kan gebeuren bij negatieve soundDelay), wordt **undefined behavior** getriggerd.

### Riskante Code #4: GSL FFT geen error check

```cpp
gsl_fft_complex_radix2_forward(data, 1, fftSize);
```

Er is **geen error checking** op de GSL return value. Als `fftData` niet correct aligned is of als de GSL bibliotheek een probleem heeft, wordt dit stilzwijgend genegeerd.

### Riskante Code #5: OverSample berekening kan 0 worden

```cpp
const int overSample = int(sampleRate / framesPerSecond / fftSize + 2);
```

Als `sampleRate / fps / fftSize < -2` (wat theoretisch kan bij extreem lage sample rates of hoge fps), wordt `overSample` negatief of nul. Dit is extreem onwaarschijnlijk maar niet expliciet afgevangen.

### Riskante Code #6: Decay filter formule is verkeerd geïnterpreteerd

```cpp
value = (animation[i] - value) / strength + value;
```

Als `strength < 1.0`, wordt de output **groter** dan de input (overshoot). De parameter range is 0.01 - 1000, dus waarden < 1 zijn geldig. Dit kan onverwacht gedrag geven.

---

## 9. Appendix: ao_modes.h

**Bestand**: `ao_modes.h` (48 regels)

Dit bestand hoort **eigenlijk niet bij het audio-systeem** — het definieert Ambient Occlusion modes:

```cpp
namespace params {
enum enumAOMode {
    AOModeFast = 0,           // Snelle ambient occlusion
    AOModeMultipleRays = 1,   // Multi-ray AO (lichtmap textuur)
    AOModeScreenSpace = 2     // Screen-space AO (SSAO)
};
}
```

Dit wordt gebruikt door de renderer, niet door de audio pipeline.

---

*Dit document beschrijft de volledige audio-analyse en modulatie pipeline van Mandelbulber2. De audio-engine is opmerkelijk krachtig voor een fractal renderer: FFT-gebaseerde band-pass extractie, pitch detectie, en meerdere post-processing filters maken het mogelijk om vrijwel elk visueel parameter te synchroniseren met audio-frequenties.*
