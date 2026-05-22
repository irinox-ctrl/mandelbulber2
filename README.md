# 3x3lion

**Founded by Iri and Devin** | Based on Mandelbulber by Krzysztof Marczak

![Banner](https://raw.githubusercontent.com/buddhi1980/mandelbulber2/wiki/assets/images/mandelbulberBanner.png)

---

## What is 3x3lion?

3x3lion is a massively expanded 3D fractal generator with **1600+ transformations** and full GPU/CPU parity.

Explore trigonometric, hyper-complex, Mandelbox, IFS, Amazing Surf, SphereTree, Menger, MandelTorus, and hundreds more 3D fractals.

Render with a great palette of customizable materials to create stunning images and videos.

The possibilities are literally **infinite**!

### Transformation Systems (1600+ types)

| System | Types | Description |
|--------|-------|-------------|
| Amazing Surf 1-4 | 100 | Sigmoid, Gaussian, Julia, Neural, Quantum, Fluid, Optical, Cosmological DE mutations |
| SphereTree/Menger | 100 | Variable branching, 4D/5D/6D Menger, Cross/Prism, Meta-hybrids |
| MandelTorus | 100 | Torus knots, Hopf fibration, Villarceau circles, Clifford tori |
| Abox Extended | 300 | Box fold variants, Kali mutations, sphere inversions |
| Noise/Orbit | 200 | Perlin noise DE, orbit trap modifications |
| Symmetry/Kaleidoscope | 100 | N-fold symmetry, kaleidoscopic IFS |
| Warp/Distortion | 100 | Space warping, coordinate distortions |
| Boolean Groups | — | Group-based smooth union/intersection/subtraction |
| Cloner System | 7 modes | Grid, Linear, Radial, Honeycomb, Fibonacci, Random, Spiral |

![Test Render](https://raw.githubusercontent.com/buddhi1980/mandelbulber2/wiki/assets/images/mandelbulberTestrender.jpg)

## Features

- High-Performance computing with multiple graphics accelerator cards (multi-GPU support via OpenCL)
- Mathematical Models and Monte Carlo Algorithms for photo-realistic scenes
- [Enlightening Documentation](https://github.com/buddhi1980/mandelbulber_doc/)
- Renders trigonometric, hyper-complex, Mandelbox, IFS, and many other 3D fractals
- Complex 3D raymarching: hard shadows, ambient occlusion, depth of field, translucency & refraction, etc.
- Rich GUI in Qt 5 environment
- Unlimited image resolution on 64-bit systems
- Program developed for ARM (experimental), x86 and x64 CPUs (Linux, Windows, macOS)
- Simple 3D navigator
- Distributed Network Rendering
- Key-frame animation for all parameters with different interpolations
- Material management
- Texture mapping (color, luminosity, diffusion, normal maps, displacement)
- Exporting of 3D objects
- Rendering queue
- Command line interface for headless systems


![image](https://cloud.githubusercontent.com/assets/11696990/13788910/173cf11a-eae2-11e5-884e-f1d03924a5f3.png)
![image](https://user-images.githubusercontent.com/11696990/52135525-4c3ad100-2646-11e9-920b-770747cb90c0.png)

## Keyboard shortcuts

In render window:

  - <kbd>Shift</kbd>+<kbd>Up</kbd> or <kbd>Q</kbd> / <kbd>Shift</kbd>+<kbd>Down</kbd> or <kbd>Z</kbd>: Move Camera Forward / Backward
  - <kbd>Shift</kbd>+<kbd>Left</kbd> or <kbd>A</kbd> / <kbd>Shift</kbd>+<kbd>Right</kbd> or <kbd>D</kbd>: Move Camera Left / Right
  - <kbd>W</kbd> / <kbd>S</kbd>: Move Camera Up / Down
  - <kbd>Up</kbd> / <kbd>Down</kbd> / <kbd>Left</kbd> / <kbd>Right</kbd>: Rotate Camera
  - <kbd>Ctrl</kbd>+(<kbd>Left</kbd> / <kbd>Right</kbd>): Roll Camera Left / Right

## Building and Deploying 

Download the latest stable version from [Releases](https://github.com/buddhi1980/mandelbulber2/releases) or clone git repository for actual development version.

After downloading, unpack the file and follow our instructions from the [README](https://raw.githubusercontent.com/buddhi1980/mandelbulber2/master/mandelbulber2/deploy/README) file.
Please see additional information in [mandelbulber2/deploy](mandelbulber2/deploy) folder.

## Easy Preparation for Development

The software is natively developed using Qt Creator for Linux (Debian or Ubuntu).

The file [mandelbulber2/qmake/mandelbulber.pro](https://github.com/buddhi1980/mandelbulber2/blob/master/mandelbulber2/qmake/mandelbulber.pro) specifies the build system configuration for Qt Creator. To be able to compile the program, the host operating system requires preparation:

Use the following scripts to prepare your Linux environment for development.
These scripts install all dependencies, compile the program, and create symbolic links in /usr/share/mandelbulber to your working directory.

[Prepare Debian for Development](https://github.com/buddhi1980/mandelbulber2/blob/master/mandelbulber2/tools/prepare_for_dev_debian_testing.sh)

[Prepare Ubuntu for Development](https://github.com/buddhi1980/mandelbulber2/blob/master/mandelbulber2/tools/prepare_for_dev_ubuntu.sh)

[Arch Linux AUR Package (Current release)](https://aur.archlinux.org/packages/mandelbulber2/)

[Arch Linux AUR Package (Current git snapshot)](https://aur.archlinux.org/packages/mandelbulber2-git/)

[Arch Linux AUR Package (Current git snapshot with opencl support)](https://aur.archlinux.org/packages/mandelbulber2-opencl-git/)

In addition, there exists an MSVC Solution located in this git package. The solution accommodates all dependencies with NUGET for autonomous compilation of OpenCL accelerated binary.

The system requires the QT5 framework in conjunction with LZO for real-time data compression and GSL for scientific resources.

## Official partners

[I-love-chaos](http://ilc.fractalforums.com)

[![I-love-chaos](http://ilc.fractalforums.com/img/thumbnail/img/ilc-128x128.png)](http://ilc.fractalforums.com)

## Resources

[Video tutorials](https://www.youtube.com/playlist?list=PLOwamUnstvZF0Y9sjxvwHNvrHHF1ZzFql)

[Image Gallery](http://krzysztofmarczak.deviantart.com/gallery/)

[Forum](https://fractalforums.org/mandelbulber/14)

[Forum Gallery](http://www.fractalforums.com/index.php?action=gallery;cat=51)

[Compiled Binaries](http://sourceforge.net/projects/mandelbulber/)

[Coverity Scan](http://scan.coverity.com/projects/4723?tab=overview)

![Open Hub](https://www.openhub.net/p/mandelbulber2/widgets/project_thin_badge.gif)

## License

GNU GPL v3
