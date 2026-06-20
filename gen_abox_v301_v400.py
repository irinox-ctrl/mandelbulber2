#!/usr/bin/env python3
"""Generate Abox V301-V400 (Quantum Physics) for CPU and GPU."""

def gen_abox_v301_v400_cpu():
    """Generate 100 Abox DE cases V301-V400 for CPU."""
    cases = []
    
    # V301: Quantum Measurement — DE *= (1 + f * |psi|^2) using sin^2 as measurement projection
    cases.append('case 301: { double psi = sin(aa*r + ab*z.x); aux.DE *= (1.0 + af * psi*psi); break; }')
    # V302: Weak Measurement — weak value = Re(projection / overlap)
    cases.append('case 302: { double psi_f = cos(aa*r); double psi_i = sin(ab*r); double overlap = psi_f*psi_i + 1e-21; double wv = (psi_f*sin(ac*z.x)) / overlap; aux.DE *= (1.0 + af * fabs(wv)); break; }')
    # V303: Quantum Zeno — exp(-rate * time * variance)
    cases.append('case 303: { double rate = fabs(aa); double variance = z.x*z.x + z.y*z.y; aux.DE *= (1.0 + af * exp(-rate * (double)i * 0.01 * variance)); break; }')
    # V304: Quantum Anti-Zeno — (1 + rate * sin²(E*t))
    cases.append('case 304: { double E = aa*r; double t = (double)i * 0.01; aux.DE *= (1.0 + af * fabs(ab) * sin(E*t)*sin(E*t)); break; }')
    # V305: Quantum Cheshire Cat — separation of properties
    cases.append('case 305: { double path1 = sin(aa*z.x + ab*z.y); double path2 = sin(ac*z.x - ab*z.y); aux.DE *= (1.0 + af * fabs(path1 - path2)); break; }')
    # V306: Quantum Delayed Choice — step function at choice_time
    cases.append('case 306: { double choice_time = fabs(aa) * 10.0; double theta = (double)i > choice_time ? 1.0 : 0.0; aux.DE *= (1.0 + af * ab * theta); break; }')
    # V307: Quantum Eraser — restored interference
    cases.append('case 307: { double visibility = cos(aa*r)*cos(aa*r); double erased = sin(ab*z.x + ac*z.y); aux.DE *= (1.0 + af * visibility * erased*erased); break; }')
    # V308: Quantum Teleportation — fidelity of state transfer
    cases.append('case 308: { double source = sin(aa*z.x + ab*z.y + ac*z.z); double target = sin(aa*(z.x+ad) + ab*(z.y+ae) + ac*(z.z+afp)); double fidelity = source*target; aux.DE *= (1.0 + af * fabs(fidelity)); break; }')
    # V309: Quantum Cloning — approximate cloning fidelity
    cases.append('case 309: { double psi = sin(aa*r); double clone = sin(aa*r + ab*0.1); double fidelity = 1.0 - (psi-clone)*(psi-clone)*0.5; aux.DE *= (1.0 + af * fmax(fidelity, 0.0)); break; }')
    # V310: Quantum Discord — non-classical correlations
    cases.append('case 310: { double Iz = sin(aa*z.x)*sin(ab*z.y); double classical = sin(aa*z.x)*0.5; double discord = fabs(Iz - classical); aux.DE *= (1.0 + af * discord); break; }')
    
    # V311: Quantum Steering
    cases.append('case 311: { double epr = sin(aa*z.x)*cos(ab*z.y) - cos(aa*z.x)*sin(ab*z.y); aux.DE *= (1.0 + af * fabs(epr)); break; }')
    # V312: Quantum Contextuality — Kochen-Specker violation
    cases.append('case 312: { double v1 = sin(aa*z.x)*sin(aa*z.y); double v2 = cos(ab*z.y)*cos(ab*z.z); double violation = fabs(v1 + v2) - 1.0; aux.DE *= (1.0 + af * fmax(violation, 0.0)); break; }')
    # V313: Quantum Nonlocality — CHSH correlation
    cases.append('case 313: { double ca = cos(aa*z.x); double cb = cos(ab*z.y); double corr = ca*cb + ca*sin(ab*z.y) + sin(aa*z.x)*cb - sin(aa*z.x)*sin(ab*z.y); aux.DE *= (1.0 + af * fabs(corr) * 0.25); break; }')
    # V314: Quantum Bell Inequality — S_CHSH - 2
    cases.append('case 314: { double S = 2.0*sqrt(2.0)*sin(aa*r)*cos(ab*r); double violation = fmax(fabs(S) - 2.0, 0.0); aux.DE *= (1.0 + af * violation); break; }')
    # V315: Quantum Tsirelson — bound at 2*sqrt(2)
    cases.append('case 315: { double bound = 2.0*sqrt(2.0); double corr = bound * cos(aa*r) * sin(ab*z.x); aux.DE *= (1.0 + af * fabs(corr) / bound); break; }')
    # V316: Quantum Leggett-Garg — temporal correlation
    cases.append('case 316: { double t1 = sin(aa*(double)i*0.1); double t2 = sin(aa*((double)i+ab)*0.1); double temporal = t1*t2 + t1*sin(aa*((double)i+ac)*0.1); aux.DE *= (1.0 + af * fabs(temporal)); break; }')
    # V317: Quantum Witness — entanglement detection
    cases.append('case 317: { double rho = sin(aa*z.x)*sin(aa*z.x) + cos(ab*z.y)*cos(ab*z.y); double witness = rho - ac; aux.DE *= (1.0 + af * fmax(-witness, 0.0)); break; }')
    # V318: Quantum Fisher — information for parameter estimation
    cases.append('case 318: { double dpsi = aa*cos(aa*r + ab*z.x); double fisher = 4.0*dpsi*dpsi; aux.DE *= (1.0 + af * fisher / (1.0 + fisher)); break; }')
    # V319: Quantum Cramér-Rao — precision bound
    cases.append('case 319: { double F_Q = 4.0*(aa*cos(aa*r))*(aa*cos(aa*r)); double bound = 1.0/sqrt(fmax(ab*F_Q, 1e-21)); aux.DE *= (1.0 + af * bound); break; }')
    # V320: Quantum Metrology — super-Heisenberg scaling
    cases.append('case 320: { double N = fmax(fabs(aa)*10.0, 1.0); double dphi = 1.0/(N*sqrt(fmax(fabs(ab), 1e-21))); double sql = 1.0/sqrt(N); double gain = (sql*sql)/(dphi*dphi+1e-21); aux.DE *= (1.0 + af * fmin(gain, 10.0) * sin(ac*r)*sin(ac*r)); break; }')
    
    # V321: Quantum Sensing — NV-center like
    cases.append('case 321: { double T2 = fabs(aa) + 0.01; double sensitivity = 1.0/(ab*sqrt(T2)+1e-21); aux.DE *= (1.0 + af * sin(ac*r)*sin(ac*r) * fmin(sensitivity, 10.0)); break; }')
    # V322: Quantum Imaging — super-resolution
    cases.append('case 322: { double lambda_r = fabs(aa)+0.1; double NA = fabs(ab)+0.1; double N_ph = fmax(fabs(ac)*10, 1.0); double res = lambda_r/(2.0*NA*sqrt(N_ph)); aux.DE *= (1.0 + af * sin(r/fmax(res,0.01))*sin(r/fmax(res,0.01))); break; }')
    # V323: Quantum Lithography — N00N state sub-wavelength
    cases.append('case 323: { double N = fmax(fabs(aa)*5, 1.0); double pattern = sin(N*ab*z.x)*sin(N*ab*z.y); aux.DE *= (1.0 + af * pattern*pattern); break; }')
    # V324: Quantum Radar — illumination advantage
    cases.append('case 324: { double snr_q = exp(-aa*r*r); double snr_c = exp(-ab*r*r); double advantage = snr_q/(snr_c+1e-21); aux.DE *= (1.0 + af * fmin(advantage, 10.0)); break; }')
    # V325: Quantum Lidar — ranging
    cases.append('case 325: { double tau = fabs(aa)*r; double N_s = fmax(fabs(ab), 0.1); double N_i = fmax(fabs(ac), 0.1); double range_res = tau/(2.0*sqrt(N_s*N_i)+1e-21); aux.DE *= (1.0 + af * sin(range_res)*sin(range_res)); break; }')
    # V326: Quantum Gyroscope — Sagnac
    cases.append('case 326: { double omega_rot = aa*z.x + ab*z.y; double phase = ac*omega_rot; aux.DE *= (1.0 + af * sin(phase)*sin(phase)); break; }')
    # V327: Quantum Gravimeter — atom interferometry
    cases.append('case 327: { double g_eff = aa; double T = fabs(ab)+0.01; double phase = g_eff*T*T*ac; aux.DE *= (1.0 + af * cos(phase)*cos(phase)); break; }')
    # V328: Quantum Clock — optical lattice precision
    cases.append('case 328: { double omega0 = fabs(aa)*100.0+1.0; double tau_c = fabs(ab)+0.01; double stability = 1.0/(omega0*sqrt(tau_c*(double)(i+1)*0.01)+1e-21); aux.DE *= (1.0 + af * fmin(stability*ac, 5.0)); break; }')
    # V329: Quantum Magnetometer — SERF sensitivity
    cases.append('case 329: { double B = aa*z.x + ab*z.y + ac*z.z; double sensitivity = sin(ad*B); aux.DE *= (1.0 + af * sensitivity*sensitivity); break; }')
    # V330: Quantum Accelerometer — cold atom
    cases.append('case 330: { double k_eff = aa; double T = fabs(ab)+0.01; double accel = k_eff*T*T*ac*r; aux.DE *= (1.0 + af * sin(accel)*sin(accel)); break; }')
    
    # V331: Quantum Thermometer — nanoscale
    cases.append('case 331: { double T_eff = fabs(aa)*r + 0.01; double C = fabs(ab)+0.1; double dE = fabs(ac)+0.01; double res = T_eff*T_eff/(C*dE); aux.DE *= (1.0 + af * fmin(res, 10.0)); break; }')
    # V332: Quantum Pressure — optomechanical
    cases.append('case 332: { double pressure = aa*r*r + ab*z.x; double sensitivity = sin(ac*pressure); aux.DE *= (1.0 + af * sensitivity*sensitivity); break; }')
    # V333: Quantum Strain — gauge
    cases.append('case 333: { double dL = aa*(z.x - z.y); double L = fmax(r, 0.01); double strain = dL/L; double gauge = ab*strain; aux.DE *= (1.0 + af * sin(gauge)*sin(gauge)); break; }')
    # V334: Quantum Force — optomechanical sensing
    cases.append('case 334: { double omega0 = fabs(aa)+0.1; double Q = fabs(ab)+1.0; double force = ac/(2.0*Q*omega0+1e-21); aux.DE *= (1.0 + af * sin(force*r)*sin(force*r)); break; }')
    # V335: Quantum Torque — nanomechanical
    cases.append('case 335: { double torque = aa*z.x*z.y - ab*z.y*z.z; double thermal = fabs(ac)+0.01; aux.DE *= (1.0 + af * fabs(torque)/(thermal+fabs(torque))); break; }')
    # V336: Quantum Electric Field — Rydberg
    cases.append('case 336: { double E_field = aa*z.x + ab*z.y + ac*z.z; double rydberg = sin(ad*E_field*E_field); aux.DE *= (1.0 + af * rydberg*rydberg); break; }')
    # V337: Quantum Voltage — Josephson junction
    cases.append('case 337: { double V_jj = aa*sin(ab*r); double josephson = cos(ac*V_jj); aux.DE *= (1.0 + af * (1.0 - josephson*josephson)); break; }')
    # V338: Quantum Current — single-electron tunneling
    cases.append('case 338: { double tunnel = exp(-aa*fabs(r-ab)); double current = ac*tunnel; aux.DE *= (1.0 + af * fabs(current)); break; }')
    # V339: Quantum Resistance — quantum Hall
    cases.append('case 339: { double n = floor(fabs(aa)*r*5.0+0.5); double R_H = 1.0/(fmax(n,1.0)*ab+1e-21); aux.DE *= (1.0 + af * fmin(R_H, 10.0)); break; }')
    # V340: Quantum Capacitance — quantum dot
    cases.append('case 340: { double C_q = aa*aa/(2.0*(fabs(ab)+0.01)); double charging = exp(-C_q*r*r); aux.DE *= (1.0 + af * charging); break; }')
    
    # V341: Quantum Inductance — SQUID
    cases.append('case 341: { double flux = aa*z.x*z.y; double inductance = cos(ab*flux); aux.DE *= (1.0 + af * inductance*inductance); break; }')
    # V342: Quantum Impedance — matching
    cases.append('case 342: { double L_q = fabs(aa)+0.01; double C_q = fabs(ab)+0.01; double Z = sqrt(L_q/C_q); double match = 1.0/(1.0 + (Z-ac)*(Z-ac)); aux.DE *= (1.0 + af * match); break; }')
    # V343: Quantum Power — spectral density
    cases.append('case 343: { double omega = aa*r; double n_th = 1.0/(exp(fabs(ab)*omega+1e-21)-1.0+1e-21); double psd = omega*(n_th+0.5); aux.DE *= (1.0 + af * fmin(fabs(psd), 10.0)); break; }')
    # V344: Quantum Energy — time-energy uncertainty
    cases.append('case 344: { double dE = fabs(aa)*r; double tau = fmax(fabs(ab),0.01); double uncertainty = dE*tau; aux.DE *= (1.0 + af * exp(-uncertainty)); break; }')
    # V345: Quantum Work — Jarzynski
    cases.append('case 345: { double W = aa*r*r; double T_eff = fmax(fabs(ab), 0.01); double jarzynski = exp(-W/T_eff); aux.DE *= (1.0 + af * jarzynski); break; }')
    # V346: Quantum Heat — stochastic thermo
    cases.append('case 346: { double Q_heat = aa*r; double T_eff = fmax(fabs(ab), 0.01); double C = fmax(fabs(ac), 0.01); double fluct = Q_heat/(T_eff*T_eff*C+1e-21); aux.DE *= (1.0 + af * exp(-fabs(fluct))); break; }')
    # V347: Quantum Entropy Production
    cases.append('case 347: { double sigma = fabs(aa)*r*r; double relax = fmax(fabs(ab), 0.01); double prod = sigma/relax; aux.DE *= (1.0 + af * (1.0 - exp(-prod))); break; }')
    # V348: Quantum Fluctuation Theorem
    cases.append('case 348: { double W = aa*(z.x*z.x + z.y*z.y); double T_eff = fmax(fabs(ab), 0.01); double ratio = exp(-W/T_eff); aux.DE *= (1.0 + af * fmin(ratio, 10.0)); break; }')
    # V349: Quantum Maxwell Demon
    cases.append('case 349: { double info = fabs(sin(aa*z.x)*cos(ab*z.y)); double work = ac*info*log(2.0); aux.DE *= (1.0 + af * fabs(work)/(1.0+fabs(work))); break; }')
    # V350: Quantum Szilard Engine
    cases.append('case 350: { double W = fabs(aa)*log(2.0)*sin(ab*r)*sin(ab*r); aux.DE *= (1.0 + af * W); break; }')
    
    # V351: Quantum Carnot
    cases.append('case 351: { double T_hot = fmax(fabs(aa)*r, 0.01); double T_cold = fmax(fabs(ab)*0.5, 0.001); double eff = 1.0 - T_cold/T_hot; double qcorr = sin(ac*r)*sin(ac*r); aux.DE *= (1.0 + af * fabs(eff) * qcorr); break; }')
    # V352: Quantum Otto
    cases.append('case 352: { double w_cold = fabs(aa)+0.1; double w_hot = fabs(ab)+0.2; double eff = 1.0 - w_cold/w_hot; double adiabatic = cos(ac*r)*cos(ac*r); aux.DE *= (1.0 + af * fabs(eff) * adiabatic); break; }')
    # V353: Quantum Stirling
    cases.append('case 353: { double V_ratio = fmax(fabs(aa), 0.1)/fmax(fabs(ab), 0.1); double T_ratio = fmax(fabs(ac), 0.1)/fmax(fabs(ad), 0.1); double eff = log(V_ratio)/(log(T_ratio)+1e-21); aux.DE *= (1.0 + af * fmin(fabs(eff), 5.0) * sin(r)*sin(r)); break; }')
    # V354: Quantum Diesel
    cases.append('case 354: { double gamma_g = 1.4; double ratio = fmax(fabs(aa), 0.1); double eff = 1.0 - (pow(ratio, gamma_g)-1.0)/(gamma_g*(ratio-1.0)+1e-21); aux.DE *= (1.0 + af * fabs(eff) * sin(ab*r)*sin(ab*r)); break; }')
    # V355: Quantum Brayton
    cases.append('case 355: { double P_ratio = fmax(fabs(aa), 0.1); double gamma_g = 1.4; double eff = 1.0 - pow(1.0/P_ratio, (gamma_g-1.0)/gamma_g); aux.DE *= (1.0 + af * fabs(eff) * cos(ab*r)*cos(ab*r)); break; }')
    # V356: Quantum Ericsson
    cases.append('case 356: { double T_ratio = fmax(fabs(aa)+0.1, 0.01) / fmax(fabs(ab)+0.1, 0.01); double regen = fmin(fabs(ac), 1.0); double eff = (1.0 - 1.0/T_ratio) * regen; aux.DE *= (1.0 + af * fabs(eff)); break; }')
    # V357: Quantum Atkinson
    cases.append('case 357: { double expansion = fmax(fabs(aa), 0.1); double T_ratio = fmax(fabs(ab)+0.1, 0.01)/fmax(fabs(ac)+0.1, 0.01); double eff = (1.0 - 1.0/T_ratio)*expansion/(expansion+1.0); aux.DE *= (1.0 + af * fabs(eff) * sin(ad*r)*sin(ad*r)); break; }')
    # V358: Quantum Miller
    cases.append('case 358: { double T_ratio = fmax(fabs(aa)+0.1,0.01)/fmax(fabs(ab)+0.1,0.01); double loss = 1.0-fmin(fabs(ac),0.99); double eff = (1.0-1.0/T_ratio)*loss; aux.DE *= (1.0 + af * fabs(eff) * cos(ad*r)*cos(ad*r)); break; }')
    # V359: Quantum Refrigeration
    cases.append('case 359: { double T_cold = fmax(fabs(aa),0.01); double T_hot = fmax(fabs(ab),0.02); double cop = T_cold/(T_hot-T_cold+1e-21); double qcop = cop*sin(ac*r)*sin(ac*r); aux.DE *= (1.0 + af * fmin(fabs(qcop),10.0)); break; }')
    # V360: Quantum Heat Pump
    cases.append('case 360: { double T_hot = fmax(fabs(aa),0.02); double T_cold = fmax(fabs(ab),0.01); double cop = T_hot/(T_hot-T_cold+1e-21); double enhance = cos(ac*r)*cos(ac*r); aux.DE *= (1.0 + af * fmin(cop*enhance,10.0)); break; }')
    
    # V361: Quantum Laser Cooling — Doppler
    cases.append('case 361: { double k = aa; double Gamma = fabs(ab)+0.01; double delta = fabs(ac)+0.01; double cooling = Gamma/(2.0*(1.0 + 4.0*delta*delta/(Gamma*Gamma))); aux.DE *= (1.0 + af * cooling * sin(k*r)*sin(k*r)); break; }')
    # V362: Quantum Sisyphus — sub-Doppler
    cases.append('case 362: { double U0 = aa; double delta = fabs(ab)+0.01; double pol_grad = sin(ac*z.x)*cos(ac*z.y); double eff = U0/(delta+1e-21)*pol_grad*pol_grad; aux.DE *= (1.0 + af * fmin(fabs(eff),10.0)); break; }')
    # V363: Quantum Evaporative — BEC
    cases.append('case 363: { double T_ratio = fmax(fabs(aa),0.01)/fmax(fabs(ab),0.01); double eta = fabs(ac)+1.0; double eff = pow(T_ratio, 3.0)*eta; aux.DE *= (1.0 + af * fmin(fabs(eff),10.0) * sin(r)*sin(r)); break; }')
    # V364: Quantum Sympathetic — ion cooling
    cases.append('case 364: { double m_ratio = fmax(fabs(aa),0.1)/fmax(fabs(ab),0.1); double collision = fabs(ac); double eff = m_ratio*collision; aux.DE *= (1.0 + af * fmin(eff,10.0) * sin(ad*r)*sin(ad*r)); break; }')
    # V365: Quantum Sideband — resolved
    cases.append('case 365: { double eta = fabs(aa)*0.1; double Omega = fabs(ab)+0.1; double nu_m = fabs(ac)+0.1; double eff = eta*Omega*Omega/((fabs(ad)+0.01)*nu_m); aux.DE *= (1.0 + af * fmin(eff,10.0)); break; }')
    # V366: Quantum Feedback Cooling
    cases.append('case 366: { double Sxy = sin(aa*z.x)*cos(ab*z.y); double Sxx = sin(aa*z.x)*sin(aa*z.x)+0.01; double Syy = cos(ab*z.y)*cos(ab*z.y)+0.01; double gain = Sxy*Sxy/(Sxx*Syy); aux.DE *= (1.0 + af * fabs(gain)); break; }')
    # V367: Quantum Cavity Cooling — optomechanics
    cases.append('case 367: { double g = fabs(aa)+0.01; double kappa = fabs(ab)+0.01; double delta = fabs(ac)+0.01; double cooling = g*g/(kappa*kappa+delta*delta); double n_ph = sin(ad*r)*sin(ad*r)*10.0; aux.DE *= (1.0 + af * cooling*fmin(n_ph,10.0)); break; }')
    # V368: Quantum Electromechanical
    cases.append('case 368: { double Cg = fabs(aa)+0.01; double Vg = ab; double C = fabs(ac)+0.01; double coupling = Cg*Vg/C; aux.DE *= (1.0 + af * sin(coupling*r)*sin(coupling*r)); break; }')
    # V369: Quantum Thermoelectric — Seebeck
    cases.append('case 369: { double S = aa; double sigma = fabs(ab)+0.01; double T_eff = fabs(ac)*r+0.01; double kappa = fabs(ad)+0.01; double ZT = S*S*sigma*T_eff/kappa; aux.DE *= (1.0 + af * fmin(ZT,10.0)); break; }')
    # V370: Quantum Spin Seebeck
    cases.append('case 370: { double Ss = aa; double gradT = ab*z.x+ac*z.y; double spin_pol = sin(ad*r); aux.DE *= (1.0 + af * fabs(Ss*gradT*spin_pol)); break; }')
    
    # V371: Quantum Nernst — thermomagnetism
    cases.append('case 371: { double Bz = aa; double gradT = ab*z.x; double Ey = ac*gradT*Bz; aux.DE *= (1.0 + af * sin(Ey)*sin(Ey)); break; }')
    # V372: Quantum Hall — quantized conductance
    cases.append('case 372: { double n_level = floor(fabs(aa)*r*5.0+0.5); double conductance = fmax(n_level,1.0)*ab; aux.DE *= (1.0 + af * fmin(fabs(conductance),10.0) * sin(ac*r)*sin(ac*r)); break; }')
    # V373: Quantum Spin Hall — helical edge
    cases.append('case 373: { double edge = exp(-aa*fabs(z.x)); double helical = sin(ab*z.y); aux.DE *= (1.0 + af * edge * helical*helical); break; }')
    # V374: Quantum Anomalous Hall — magnetic order
    cases.append('case 374: { double chern = floor(fabs(aa)*2.0+0.5); double mag_order = sin(ab*z.x)*sin(ab*z.y); aux.DE *= (1.0 + af * fabs(chern) * mag_order*mag_order); break; }')
    # V375: Quantum Valley Hall — valley contrast
    cases.append('case 375: { double valley = sin(aa*z.x)*cos(ab*z.y) - cos(aa*z.x)*sin(ab*z.y); double broken_inv = sin(ac*r); aux.DE *= (1.0 + af * fabs(valley*broken_inv)); break; }')
    # V376: Quantum Topological Insulator — Dirac cone
    cases.append('case 376: { double bulk_gap = fabs(aa); double surface = sin(ab*z.x)*sin(ab*z.y)*exp(-ac*fabs(z.z)); double k_F = ad*r; aux.DE *= (1.0 + af * bulk_gap*fabs(surface)*fmin(k_F,5.0)); break; }')
    # V377: Quantum Weyl — chiral Fermi arcs
    cases.append('case 377: { double kx = aa*z.x; double ky = ab*z.y; double kz = ac*z.z; double chirality = kx*kx + ky*ky - kz*kz; double fermi_arc = exp(-fabs(chirality)*ad); aux.DE *= (1.0 + af * fermi_arc); break; }')
    # V378: Quantum Dirac — 3D Dirac cone
    cases.append('case 378: { double E_D = aa; double v_F = fabs(ab)+0.01; double k = ac*r; double cone = fabs(E_D)/(v_F*fmax(fabs(k),0.01)); aux.DE *= (1.0 + af * fmin(cone,10.0) * sin(r)*sin(r)); break; }')
    # V379: Quantum Majorana — topological qubit
    cases.append('case 379: { double xi = fmax(fabs(aa),0.01); double L = fabs(ab)*r; double overlap = exp(-L/xi); double gap = fabs(ac); aux.DE *= (1.0 + af * overlap*gap); break; }')
    # V380: Quantum Kitaev — spin liquid
    cases.append('case 380: { double J = fabs(aa)+0.01; double alpha = fabs(ab)+0.01; double g = fabs(ac)+0.01; double gap = J*exp(-1.0/(alpha*g)); aux.DE *= (1.0 + af * gap * sin(ad*r)*sin(ad*r)); break; }')
    
    # V381: Quantum Ising — critical point
    cases.append('case 381: { double J = fabs(aa)+0.01; double h = fabs(ab)+0.01; double gap = fabs(J-h)/J; double crit_exp = fabs(ac)+0.5; aux.DE *= (1.0 + af * pow(fmax(gap,1e-10), crit_exp)); break; }')
    # V382: Quantum Heisenberg — antiferromagnet
    cases.append('case 382: { double J = aa; double Si = sin(ab*z.x); double Sj = sin(ab*z.y); double coupling = J*Si*Sj; aux.DE *= (1.0 + af * fabs(coupling)); break; }')
    # V383: Quantum XY — KT transition
    cases.append('case 383: { double J = aa; double Sx = sin(ab*z.x)*cos(ac*z.y); double Sy = cos(ab*z.x)*sin(ac*z.y); double coupling = J*(Sx+Sy); aux.DE *= (1.0 + af * fabs(coupling)); break; }')
    # V384: Quantum Potts — q-state
    cases.append('case 384: { double J = aa; double q = fmax(floor(fabs(ab)*5+2), 2.0); double sigma_i = floor(sin(ac*z.x)*q); double sigma_j = floor(sin(ac*z.y)*q); double delta_s = (sigma_i == sigma_j) ? 1.0 : 0.0; aux.DE *= (1.0 + af * J*delta_s); break; }')
    # V385: Quantum Clock — parafermion
    cases.append('case 385: { double J = aa; double q = fmax(floor(fabs(ab)*5+2), 2.0); double angle = 2.0*M_PI/q; double sigma_diff = sin(ac*z.x) - sin(ac*z.y); aux.DE *= (1.0 + af * J*cos(angle*sigma_diff)); break; }')
    # V386: Quantum Ashkin-Teller — coupled Ising
    cases.append('case 386: { double J = aa; double lambda = ab; double sigma = sin(ac*z.x)*sin(ac*z.y); double tau = cos(ad*z.x)*cos(ad*z.y); double coupling = J*(sigma + tau + lambda*sigma*tau); aux.DE *= (1.0 + af * fabs(coupling)); break; }')
    # V387: Quantum Baxter — 8-vertex
    cases.append('case 387: { double W = aa; double X = ab; double Y = ac; double sigma = sin(ad*z.x)*sin(ad*z.y); double tau = cos(ad*z.x)*cos(ad*z.y); double v = W*sigma + X*tau + Y*sigma*tau; aux.DE *= (1.0 + af * fabs(v)); break; }')
    # V388: Quantum Hubbard — Mott transition
    cases.append('case 388: { double U = fabs(aa)+0.01; double t = fabs(ab)+0.01; double n_up = sin(ac*z.x)*sin(ac*z.x); double n_down = cos(ac*z.y)*cos(ac*z.y); double mott = U*n_up*n_down/t; aux.DE *= (1.0 + af * fmin(mott,10.0)); break; }')
    # V389: Quantum t-J — strong coupling
    cases.append('case 389: { double t = fabs(aa)+0.01; double J = ab; double hop = t*sin(ac*z.x)*cos(ac*z.y); double exchange = J*sin(ad*z.x)*sin(ad*z.y); aux.DE *= (1.0 + af * fabs(hop + exchange)); break; }')
    # V390: Quantum Anderson — localization
    cases.append('case 390: { double xi_loc = fmax(fabs(aa),0.01); double disorder = fabs(ab); double loc = exp(-r/xi_loc)*disorder; aux.DE *= (1.0 + af * loc); break; }')
    
    # V391: Quantum Mott — insulator
    cases.append('case 391: { double U = fabs(aa)+0.01; double U_c = fabs(ab)+0.01; double n = sin(ac*r)*0.5+0.5; double gap = (U/U_c)*(n-0.5)*(n-0.5); aux.DE *= (1.0 + af * fmin(gap*4.0,10.0)); break; }')
    # V392: Quantum Peierls — dimerization
    cases.append('case 392: { double alpha = aa; double u = ab; double k_F = ac; double gap = 2.0*fabs(alpha*u)*fabs(cos(2.0*k_F*z.x)); aux.DE *= (1.0 + af * fmin(gap,10.0)); break; }')
    # V393: Quantum Spin Peierls — singlet
    cases.append('case 393: { double J = fabs(aa)+0.01; double g = fabs(ab)+0.01; double gap = J*exp(-M_PI*J/(g*g)); double singlet = cos(ac*z.x)*cos(ac*z.y); aux.DE *= (1.0 + af * gap*singlet*singlet); break; }')
    # V394: Quantum Haldane — integer spin chain
    cases.append('case 394: { double J = fabs(aa)+0.01; double S = fmax(floor(fabs(ab)+1),1.0); double gap = J*exp(-M_PI*S); double string_order = sin(ac*r); aux.DE *= (1.0 + af * gap*string_order*string_order); break; }')
    # V395: Quantum AKLT — valence bond
    cases.append('case 395: { double J = fabs(aa)+0.01; double SiSj = sin(ab*z.x)*sin(ab*z.y); double SiSj2 = SiSj*SiSj; double aklt = J*(SiSj + SiSj2/3.0); aux.DE *= (1.0 + af * fabs(aklt)); break; }')
    # V396: Quantum Toric Code — Z2 anyons
    cases.append('case 396: { double J = fabs(aa)+0.01; double Av = sin(ab*z.x)*sin(ab*z.y); double Bp = cos(ac*z.x)*cos(ac*z.y); double toric = 4.0*J*(Av*Av + Bp*Bp); aux.DE *= (1.0 + af * fmin(toric,10.0)); break; }')
    # V397: Quantum Wen — string-net
    cases.append('case 397: { double F1 = sin(aa*z.x); double F2 = sin(ab*z.y); double F3 = cos(ac*z.x); double F4 = cos(ad*z.y); double wen = F1*F2*F3*F4; aux.DE *= (1.0 + af * fabs(wen)); break; }')
    # V398: Quantum Levin-Wen — TQFT
    cases.append('case 398: { double sn = sin(aa*z.x+ab*z.y); double fusion = sn*sn; double F_sym = cos(ac*r)*cos(ac*r); double lw = fusion*F_sym; aux.DE *= (1.0 + af * lw); break; }')
    # V399: Quantum Walker — quantum walk
    cases.append('case 399: { double psi = sin(aa*z.x + ab*(double)i*0.1); double coin = cos(ac*z.y); double walker = psi*psi*coin*coin; aux.DE *= (1.0 + af * walker); break; }')
    # V400: Quantum Cellular Automaton
    cases.append('case 400: { double rule = sin(aa*z.x)*sin(ab*z.y)*cos(ac*z.z); double evolution = cos(ad*(double)i*0.1); double qca = rule*evolution; aux.DE *= (1.0 + af * qca*qca); break; }')
    
    return cases


def to_gpu(cpu_code):
    """Convert CPU code to OpenCL GPU code."""
    gpu = cpu_code
    gpu = gpu.replace('double ', 'float ')
    gpu = gpu.replace('M_PI', 'M_PI_F')
    gpu = gpu.replace('sin(', 'native_sin(')
    gpu = gpu.replace('cos(', 'native_cos(')
    gpu = gpu.replace('mut.', 'mut->')
    gpu = gpu.replace('in.point', 'in->point')
    # Fix double replacements
    gpu = gpu.replace('native_sin(h(', 'sinh(')
    gpu = gpu.replace('native_cos(h(', 'cosh(')
    gpu = gpu.replace('anative_cos(', 'acos(')
    gpu = gpu.replace('anative_sin(', 'asin(')
    return gpu


if __name__ == '__main__':
    cases = gen_abox_v301_v400_cpu()
    
    # Write CPU cases
    with open('gen_abox_v301_v400_cpu.txt', 'w') as f:
        for c in cases:
            f.write('\t\t\t\t\t\t' + c + '\n')
    
    # Write GPU cases
    with open('gen_abox_v301_v400_gpu.txt', 'w') as f:
        for c in cases:
            f.write('\t\t\t\t\t' + to_gpu(c) + '\n')
    
    print(f'Generated {len(cases)} Abox cases (V301-V400)')
    print('CPU: gen_abox_v301_v400_cpu.txt')
    print('GPU: gen_abox_v301_v400_gpu.txt')
