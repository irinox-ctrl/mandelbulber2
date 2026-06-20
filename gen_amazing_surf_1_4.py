#!/usr/bin/env python3
"""Generate Amazing Surf 1-4 DE System (100 types) for CPU and GPU."""

def gen_as_cpu():
    """Generate 100 Amazing Surf DE cases for CPU."""
    cases = []

    # === AS1 V1-V25: Basis DE-modificaties ===
    cases.append('case 1: { double k = ta; double DE0 = tb; aux.DE = 1.0/(1.0 + exp(-k*(aux.DE - DE0))); break; }')
    cases.append('case 2: { double DE0 = ta; double sigma = fmax(fabs(tb), 0.01); aux.DE *= exp(-(aux.DE-DE0)*(aux.DE-DE0)/(sigma*sigma)); break; }')
    cases.append('case 3: { double threshold = ta; double DE_max = fabs(tb)+1.0; double DE_min = fabs(tc)*0.01; aux.DE = (aux.DE > threshold) ? DE_max : DE_min; break; }')
    cases.append('case 4: { double b1=ta, b2=tb; double d1=fabs(tc),d2=fabs(td); if(aux.DE<b1) aux.DE=d1; else if(aux.DE<b2) aux.DE=d2; break; }')
    cases.append('case 5: { double h = sin(z.x*127.1+z.y*311.7+z.z*74.7)*43758.5453; h=h-floor(h); aux.DE += sf*(h*2.0-1.0)*ta; break; }')
    cases.append('case 6: { double jx=z.x*z.x-z.y*z.y+ta; double jy=2.0*z.x*z.y+tb; double julia_mag=sqrt(jx*jx+jy*jy); aux.DE *= (1.0 + sf*0.1*julia_mag); break; }')
    cases.append('case 7: { aux.DE *= (1.0 + sf*0.1*sin(ta*(double)i*0.1)); break; }')
    cases.append('case 8: { double alpha=fmin(fmax(ta,0.01),0.99); aux.DE = alpha*aux.DE + (1.0-alpha)*tb; break; }')
    cases.append('case 9: { double h1=sin(ta*z.x+tb*z.y+tc*z.z); double h2=sin(td*h1+ta*aux.DE); aux.DE *= (1.0 + sf*h2); break; }')
    cases.append('case 10: { double v=0,f=ta,a=1.0; for(int k=0;k<4;k++){double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453;h=h-floor(h);v+=a*h;f*=2.0;a*=0.5;} aux.DE *= (1.0 + sf*0.1*v); break; }')
    cases.append('case 11: { double speed = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE /= (1.0 + sf*speed*ta); break; }')
    cases.append('case 12: { double sc = fabs(ta) + 0.01; aux.DE *= sc; break; }')
    cases.append('case 13: { double angle = atan2(z.y,z.x); aux.DE *= (1.0 + sf*fabs(angle)*ta/M_PI); break; }')
    cases.append('case 14: { double shear = fabs(z.x*z.y*ta) + fabs(z.y*z.z*tb) + fabs(z.z*z.x*tc); aux.DE *= (1.0 + sf*shear); break; }')
    cases.append('case 15: { double progress = (double)i / fmax((double)(i+10), 1.0); aux.DE *= (1.0 + sf*(1.0-progress)*ta); break; }')
    cases.append('case 16: { double box = fmax(fabs(z.x),fmax(fabs(z.y),fabs(z.z))); if(box > fabs(ta)) aux.DE *= (1.0 + sf*tb); break; }')
    cases.append('case 17: { double d = sqrt((z.x-ta)*(z.x-ta)+(z.y-tb)*(z.y-tb)+(z.z-tc)*(z.z-tc)); if(d < fabs(td)) aux.DE *= (1.0 + sf); break; }')
    cases.append('case 18: { double w = fabs(ta)+0.01; if(fabs(z.x)<w && fabs(z.y)<w) aux.DE *= (1.0 + sf*tb); break; }')
    cases.append('case 19: { double intensity = sin(z.x*ta)*sin(z.y*tb)*sin(z.z*tc); aux.DE *= (1.0 + sf*0.1*intensity*intensity); break; }')
    cases.append('case 20: { double ao = 1.0/(1.0 + (double)i*ta*0.01); aux.DE *= (1.0 - sf*ao*fabs(tb)); break; }')
    cases.append('case 21: { double gi = sin(z.x*ta+z.y*tb)*0.5+0.5; aux.DE /= (1.0 + sf*gi*fabs(tc)); break; }')
    cases.append('case 22: { double depth = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= (1.0 + sf*ta*depth); break; }')
    cases.append('case 23: { double light_accum = sin(z.x*ta)*sin(z.y*ta)*0.5+0.5; aux.DE /= (1.0 + sf*light_accum*tb); break; }')
    cases.append('case 24: { double ss_depth = exp(-fabs(ta)*sqrt(z.x*z.x+z.y*z.y+z.z*z.z)); aux.DE *= (1.0 + sf*ss_depth*tb); break; }')
    cases.append('case 25: { double wl_diff = fabs(z.x*ta - tb); aux.DE *= (1.0 + sf*tc*wl_diff); break; }')

    # === AS2 V1-V25: Materialen & Kwantum ===
    cases.append('case 26: { double caustic = sin(z.x*ta*10.0)*sin(z.y*tb*10.0); aux.DE *= (1.0 + sf*caustic*caustic*tc); break; }')
    cases.append('case 27: { double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double view_dot = z.z/fmax(r,1e-21); double fresnel = pow(fmax(1.0-fabs(view_dot),0.0), ta); aux.DE *= (1.0 + sf*fresnel*tb); break; }')
    cases.append('case 28: { double thin_film = sin(ta*sqrt(z.x*z.x+z.y*z.y+z.z*z.z)*M_PI*2.0); aux.DE *= (1.0 + sf*thin_film*thin_film*tb); break; }')
    cases.append('case 29: { double tangent_dot = fabs(z.x*cos(ta)+z.y*sin(ta))/fmax(sqrt(z.x*z.x+z.y*z.y),1e-21); aux.DE *= (1.0 + sf*tangent_dot*tb); break; }')
    cases.append('case 30: { double subdiv = fmax(1.0, fabs(ta)); aux.DE /= (1.0 + sf*subdiv*tb); break; }')
    cases.append('case 31: { double dist = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double lod = fmax(0.1, dist*ta); aux.DE *= lod; break; }')
    cases.append('case 32: { double edge_len = fabs(z.x-z.y) + fabs(z.y-z.z) + fabs(z.z-z.x); aux.DE *= (1.0 + sf*ta*edge_len*tb); break; }')
    cases.append('case 33: { double disp = sin(z.x*ta*5.0)*sin(z.y*tb*5.0)*sin(z.z*tc*5.0); aux.DE += sf*disp*td; break; }')
    cases.append('case 34: { double h = sin(z.x*ta*7.0+z.y*tb*11.0+z.z*tc*13.0)*43758.5453; h=h-floor(h); aux.DE *= (1.0 + sf*(h*2.0-1.0)*td*0.1); break; }')
    cases.append('case 35: { double parallax = fabs(ta)*z.z/fmax(fabs(tb),0.01); aux.DE *= (1.0 + sf*parallax*0.1); break; }')
    cases.append('case 36: { double n = fmax(fabs(ta)+1.0, 1.01); aux.DE /= n; break; }')
    cases.append('case 37: { double dist_traveled = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= exp(-sf*fabs(ta)*dist_traveled); break; }')
    cases.append('case 38: { double cos_theta = z.z/fmax(sqrt(z.x*z.x+z.y*z.y+z.z*z.z),1e-21); double phase = (1.0+cos_theta*cos_theta)*0.75; aux.DE *= (1.0 + sf*phase*ta); break; }')
    cases.append('case 39: { double emission = sin(z.x*ta)*sin(z.y*ta)*0.5+0.5; aux.DE /= (1.0 + sf*emission*fabs(tb)); break; }')
    cases.append('case 40: { double curl_approx = sin(z.y*ta)*cos(z.z*tb) - cos(z.y*ta)*sin(z.z*tb); aux.DE *= (1.0 + sf*fabs(curl_approx)*tc); break; }')
    cases.append('case 41: { double grad = (sin(z.x*ta)-sin((z.x+0.01)*ta))/0.01; aux.DE /= (1.0 + sf*fabs(grad)*tb); break; }')
    cases.append('case 42: { double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double mass_d = fmax(r - ta, 0.01); aux.DE *= (1.0 + sf*tb/(mass_d*mass_d)); break; }')
    cases.append('case 43: { double v2 = (z.x*z.x+z.y*z.y+z.z*z.z)*ta*ta; double lorentz = sqrt(fmax(1.0 - fmin(v2, 0.99), 0.01)); aux.DE *= lorentz; break; }')
    cases.append('case 44: { double barrier = fabs(z.x - ta); aux.DE *= exp(-sf*fabs(tb)*barrier); break; }')
    cases.append('case 45: { double psi2 = sin(ta*z.x)*sin(tb*z.y)*sin(tc*z.z); aux.DE *= (1.0 + sf*psi2*psi2); break; }')
    cases.append('case 46: { double momentum = sqrt(z.x*z.x+z.y*z.y+z.z*z.z)*ta; double pos = fmax(fabs(z.x), 0.01); aux.DE *= (1.0 + sf*tb/(2.0*momentum*pos+0.01)); break; }')
    cases.append('case 47: { double spin_dot = z.x*sin(ta)+z.y*cos(ta)+z.z*sin(tb); aux.DE *= (1.0 + sf*tc*spin_dot); break; }')
    cases.append('case 48: { double corr = sin(z.x*ta)*sin((-z.x)*ta) + sin(z.y*tb)*sin((-z.y)*tb); aux.DE *= (1.0 + sf*fabs(corr)*tc); break; }')
    cases.append('case 49: { double decay = exp(-sf*fabs(ta)*(double)i*0.01); aux.DE *= decay; break; }')
    cases.append('case 50: { double entropy = sin(z.x*ta*3.0)*sin(z.y*tb*5.0)*sin(z.z*tc*7.0); double temp = fabs(td)+0.01; aux.DE *= (1.0 + sf*temp*entropy*entropy); break; }')

    # === AS3 V1-V25: Fluiddynamica & Optica ===
    cases.append('case 51: { double kT = fmax(fabs(ta)*fabs(tb), 0.01); aux.DE *= (1.0 + sf*tc/kT); break; }')
    cases.append('case 52: { double vel_grad = fabs(z.x-z.y)*ta + fabs(z.y-z.z)*tb; aux.DE *= (1.0 + sf*tc*vel_grad); break; }')
    cases.append('case 53: { double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double curv = 1.0/fmax(r,0.01); aux.DE *= (1.0 + sf*ta*curv); break; }')
    cases.append('case 54: { double tube_r = fmax(fabs(sqrt(z.x*z.x+z.y*z.y) - ta), 0.01); aux.DE *= (1.0 + sf*cos(tb)/tube_r); break; }')
    cases.append('case 55: { double conc_grad = fabs(sin(z.x*ta) - sin(z.y*ta)); aux.DE *= (1.0 + sf*tb*conc_grad); break; }')
    cases.append('case 56: { double lap = sin((z.x+0.01)*ta)+sin((z.x-0.01)*ta)-2.0*sin(z.x*ta); aux.DE += sf*tb*lap; break; }')
    cases.append('case 57: { double vel_dot = sin(z.x*ta)*cos(z.y*tb); aux.DE *= (1.0 + sf*vel_dot*tc); break; }')
    cases.append('case 58: { double v=0,f=ta,a=1.0; for(int k=0;k<4;k++){double h=sin(z.x*f*12.9+z.y*f*78.2+z.z*f*45.1)*43758.5453;h=h-floor(h);v+=a*h;f*=2.0;a*=0.5;} aux.DE *= (1.0 + sf*v*tb); break; }')
    cases.append('case 59: { double front = fabs(z.x - ta*i*0.01); double shock = (front < fabs(tb)) ? tc : 1.0; aux.DE *= shock; break; }')
    cases.append('case 60: { double freq_diff = fabs(sin(z.x*ta) - sin(z.x*tb)); double Q = fmax(fabs(tc), 0.1); aux.DE *= (1.0 + sf*Q*1.0/fmax(freq_diff+0.01, 0.01)); break; }')
    cases.append('case 61: { double phase_diff = ta*z.x - tb*z.y; aux.DE *= (1.0 + sf*cos(phase_diff)*tc); break; }')
    cases.append('case 62: { double v_source = ta * 0.1; double angle = atan2(z.y, z.x); aux.DE *= (1.0 + sf*v_source*cos(angle)*tb); break; }')
    cases.append('case 63: { double theta = atan2(z.y, z.x); aux.DE *= (1.0 + sf*ta*cos(2.0*theta)); break; }')
    cases.append('case 64: { double phi2 = atan2(z.z, sqrt(z.x*z.x+z.y*z.y)); aux.DE *= (1.0 + sf*ta*fabs(sin(2.0*phi2))); break; }')
    cases.append('case 65: { double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double path = r * fabs(ta) * fabs(tb); aux.DE *= (1.0 + sf*tc*path); break; }')
    cases.append('case 66: { double lat_pt = fmod(fabs(z.x*ta), 1.0); double bandgap = (lat_pt < 0.5) ? 1.0 : tb; aux.DE *= bandgap; break; }')
    cases.append('case 67: { double surf_dist = fabs(sqrt(z.x*z.x+z.y*z.y+z.z*z.z) - ta); double skin = fmax(fabs(tb), 0.01); aux.DE *= (1.0 + sf*tc*exp(-surf_dist/skin)); break; }')
    cases.append('case 68: { double neg_idx = fabs(ta); aux.DE *= (1.0 + sf*neg_idx*fabs(tb)); break; }')
    cases.append('case 69: { double winding = sin(z.x*ta)*cos(z.y*tb) + cos(z.x*ta)*sin(z.y*tb); aux.DE *= (1.0 + sf*fabs(winding)*tc); break; }')
    cases.append('case 70: { double charge = sin(z.x*ta*5.0)*sin(z.y*tb*5.0)*sin(z.z*tc*5.0); aux.DE *= (1.0 + sf*charge*charge*td); break; }')
    cases.append('case 71: { double curl_mag = fabs(sin(z.y*ta)-sin(z.z*ta)) + fabs(sin(z.z*tb)-sin(z.x*tb)); aux.DE *= (1.0 + sf*curl_mag*tc); break; }')
    cases.append('case 72: { double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double sech_val = 1.0/cosh(fmin(ta*(r-tb), 20.0)); aux.DE *= (1.0 + sf*tc*sech_val); break; }')
    cases.append('case 73: { double S = fabs(ta)*sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= (1.0 + sf*tb*exp(-fmin(S,20.0))); break; }')
    cases.append('case 74: { double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double monopole = fabs(ta)/fmax(r,0.01); aux.DE *= (1.0 + sf*monopole*tb); break; }')
    cases.append('case 75: { double d_axis = sqrt(z.y*z.y+z.z*z.z); aux.DE *= (1.0 + sf*ta*log(fmax(d_axis,0.01))*tb); break; }')

    # === AS4 V1-V25: Kosmologie & Velden ===
    cases.append('case 76: { double d_brane = fabs(z.x - ta); double delta_approx = exp(-d_brane*d_brane*100.0); aux.DE *= (1.0 + sf*tb*delta_approx); break; }')
    cases.append('case 77: { double throat_d = (z.x-ta)*(z.x-ta)+(z.y-tb)*(z.y-tb)+(z.z-tc)*(z.z-tc); double throat_r = fmax(fabs(td), 0.01); aux.DE *= (1.0 + sf*exp(-throat_d/(throat_r*throat_r))); break; }')
    cases.append('case 78: { double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double rs = fmax(fabs(ta), 0.01); aux.DE /= fmax(1.0 - rs/fmax(r,rs+0.01), 0.01); break; }')
    cases.append('case 79: { double jet_d = z.y*z.y+z.z*z.z; double jet_w = fmax(fabs(tb), 0.01); aux.DE *= (1.0 + sf*ta*exp(-jet_d/(jet_w*jet_w))); break; }')
    cases.append('case 80: { double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double halo = 1.0/(1.0 + r*r/(fmax(ta*ta,0.01))); aux.DE *= (1.0 + sf*tb*halo); break; }')
    cases.append('case 81: { double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= exp(sf*fabs(ta)*r*0.01); break; }')
    cases.append('case 82: { double d_string = sqrt(z.y*z.y+z.z*z.z); double horizon = fmax(fabs(tb), 0.01); aux.DE *= (1.0 + sf*ta*log(fmax(d_string/horizon,0.01))); break; }')
    cases.append('case 83: { double d_wall = fabs(z.x - ta); double thickness = fmax(fabs(tb), 0.01); aux.DE *= (1.0 + sf*tc*tanh(d_wall/thickness)); break; }')
    cases.append('case 84: { double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double theta2 = atan2(z.y,z.x); double phi2 = acos(z.z/fmax(r,1e-21)); double Ylm = sin(ta*theta2)*cos(tb*phi2); aux.DE *= (1.0 + sf*tc*Ylm*Ylm); break; }')
    cases.append('case 85: { double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double efold = r*fabs(ta); aux.DE *= exp(sf*fmin(efold*tb, 10.0)); break; }')
    cases.append('case 86: { double decay_t = exp(-fabs(ta)*(double)i*0.01); aux.DE *= (1.0 + sf*tb*decay_t*tc); break; }')
    cases.append('case 87: { double baryon = sin(z.x*ta)*sin(z.y*tb); double rate = exp(-fabs(tc)*(double)i*0.01); aux.DE *= (1.0 + sf*baryon*baryon*rate*td); break; }')
    cases.append('case 88: { double ion_frac = exp(-fabs(ta)/fmax(fabs(tb)*(double)i*0.01+0.01, 0.01)); aux.DE *= (1.0 + sf*ion_frac*tc); break; }')
    cases.append('case 89: { double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double scale_a = fmax(r*ta, 0.01); double energy = 1.0/(scale_a*scale_a); aux.DE *= (1.0 + sf*sqrt(energy)*tb); break; }')
    cases.append('case 90: { double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double scale_a = fmax(r*ta, 0.01); aux.DE /= fmax(scale_a*tb, 0.01); break; }')
    cases.append('case 91: { double ent_max = fabs(ta); double heat_time = fmax(fabs(tb), 0.01); aux.DE *= (1.0 + sf*ent_max*(1.0-exp(-(double)i*0.01/heat_time))); break; }')
    cases.append('case 92: { double bubble = sin(z.x*ta*5.0)*sin(z.y*tb*5.0)*sin(z.z*tc*5.0); aux.DE *= (1.0 + sf*fabs(bubble)*td); break; }')
    cases.append('case 93: { double barrier2 = fabs(ta); double tunnel = exp(-barrier2*sqrt(z.x*z.x+z.y*z.y+z.z*z.z)); aux.DE *= (1.0 + sf*tunnel*tb); break; }')
    cases.append('case 94: { double order = sin(z.x*ta)*sin(z.y*tb); double latent = fabs(tc); aux.DE *= (1.0 + sf*latent*order*order); break; }')
    cases.append('case 95: { double d_crit = sqrt((z.x-ta)*(z.x-ta)+(z.y-tb)*(z.y-tb)+(z.z-tc)*(z.z-tc)); double expo = fmax(fabs(td), 0.1); aux.DE *= pow(fmax(d_crit, 0.01), -expo); break; }')
    cases.append('case 96: { double cutoff = fmax(fabs(ta), 0.01); double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= (1.0 + sf*tb*log(fmax(cutoff/fmax(r,0.01), 0.01))); break; }')
    cases.append('case 97: { double div_approx = cos(z.x*ta)*sin(z.y*tb)*cos(z.z*tc); aux.DE *= (1.0 + sf*fabs(div_approx)*td); break; }')
    cases.append('case 98: { double vev = sqrt(z.x*z.x+z.y*z.y+z.z*z.z)*ta; aux.DE *= (1.0 + sf*vev*vev*tb); break; }')
    cases.append('case 99: { double grad_phase = fabs(cos(z.x*ta)-cos(z.y*ta)) + fabs(cos(z.y*tb)-cos(z.z*tb)); aux.DE *= (1.0 + sf*tc*grad_phase); break; }')
    cases.append('case 100: { double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double higgs = ta*tb*r*r; aux.DE *= (1.0 + sf*higgs); break; }')

    return cases


def gen_spheretree_menger_cpu():
    """Generate 100 SphereTree/Menger DE cases for CPU."""
    cases = []

    # === SphereTree V6-V30 (25 stuks) ===
    cases.append('case 1: { double branch = 2.0 + floor(3.0*sin((double)i*ta*0.1)); aux.DE *= fmax(branch*tb, 0.01); break; }')
    cases.append('case 2: { double bx=fmax(ta,1.0),by=fmax(tb,1.0),bz=fmax(tc,1.0); aux.DE *= fmax(fmax(bx,by),bz)*sf; break; }')
    cases.append('case 3: { double angle = (double)i * 2.39996322972865332 * ta; double cosA=cos(angle),sinA=sin(angle); double nx=z.x*cosA-z.y*sinA; z.y=z.x*sinA+z.y*cosA; z.x=nx; break; }')
    cases.append('case 4: { double jm = sin(z.x*ta)*cos(z.y*tb); double r_ratio = 1.0 + sf*0.3*jm; aux.DE *= r_ratio; break; }')
    cases.append('case 5: { double h = sin(z.x*ta*127.1+z.y*ta*311.7+z.z*ta*74.7)*43758.5453; h=h-floor(h); aux.DE *= (1.0 + sf*(h*2.0-1.0)*tb); break; }')
    cases.append('case 6: { double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double d1 = r - ta; double d2 = r - tb; aux.DE *= (1.0 + sf*exp(-fmin(d1*d1,d2*d2)*tc)); break; }')
    cases.append('case 7: { double w = fabs(ta)+0.01; double wd = w*sin(z.x*tb)*cos(z.y*tc); aux.DE *= (1.0 + sf*wd*td); break; }')
    cases.append('case 8: { double ax=fmax(fabs(ta),0.01),ay=fmax(fabs(tb),0.01),az=fmax(fabs(tc),0.01); double ell = sqrt((z.x/ax)*(z.x/ax)+(z.y/ay)*(z.y/ay)+(z.z/az)*(z.z/az))-1.0; aux.DE *= (1.0 + sf*exp(-ell*ell*td)); break; }')
    cases.append('case 9: { double r2d = sqrt(z.x*z.x+z.y*z.y); double R=fabs(ta)+0.1,r=fabs(tb)+0.01; double td2 = (r2d-R)*(r2d-R)+z.z*z.z-r*r; aux.DE *= (1.0 + sf*exp(-fabs(td2)*tc)); break; }')
    cases.append('case 10: { double px=z.x,py=z.y,pz=z.z; double seg_d=fabs(pz)-fabs(ta); double cap_d=sqrt(px*px+py*py+fmax(seg_d,0.0)*fmax(seg_d,0.0))-fabs(tb); aux.DE *= (1.0 + sf*exp(-cap_d*cap_d*tc)); break; }')
    cases.append('case 11: { double theta=atan2(z.y,z.x); double phi2=acos(z.z/fmax(sqrt(z.x*z.x+z.y*z.y+z.z*z.z),1e-21)); double m=fmax(ta,1.0); double sf_r=pow(fmax(pow(fabs(cos(m*theta/4.0)),tc)+pow(fabs(sin(m*theta/4.0)),tc),1e-21),-1.0/fmax(tb,0.1)); double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= (1.0 + sf*exp(-fabs(r-sf_r*td)*5.0)); break; }')
    cases.append('case 12: { double jx=z.x*z.x-z.y*z.y+ta; double jy=2.0*z.x*z.y+tb; z.x=jx; z.y=jy; aux.DE *= 2.0*sqrt(jx*jx+jy*jy); break; }')
    cases.append('case 13: { double mx=z.x*z.x-z.y*z.y+z.x; double my=2.0*z.x*z.y+z.y; z.x=mx; z.y=my; aux.DE *= 2.0*sqrt(mx*mx+my*my); break; }')
    cases.append('case 14: { double a1=ta*M_PI/180.0; double a2=tb*M_PI/180.0; double ca1=cos(a1),sa1=sin(a1); double newx=z.x+z.x*ca1-z.y*sa1; double newy=z.y+z.x*sa1+z.y*ca1; z.x=newx*0.5; z.y=newy*0.5; z.z*=tc; aux.DE *= fabs(tc); break; }')
    cases.append('case 15: { double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double koch_amp = ta*sin(r*tb*10.0); aux.DE *= (1.0 + sf*koch_amp*koch_amp); break; }')
    cases.append('case 16: { double scale4 = fabs(ta)+1.0; if(z.x+z.y<0.0){double t=z.x;z.x=-z.y;z.y=-t;} if(z.x+z.z<0.0){double t=z.x;z.x=-z.z;z.z=-t;} if(z.y+z.z<0.0){double t=z.y;z.y=-z.z;z.z=-t;} z = z*scale4 - CVector4(1,1,1,0)*(scale4-1.0)*tb; aux.DE = aux.DE*scale4+1.0; break; }')
    cases.append('case 17: { double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); if(r<1e-21)r=1e-21; double mde=ta*ta/r/r; z*=mde; aux.DE*=mde; break; }')
    cases.append('case 18: { double h=sin(z.x*ta*12.9898+z.y*tb*78.233+z.z*tc*45.164)*43758.5453; h=h-floor(h); z.x+=h*td*0.1; z.y+=(1.0-h)*td*0.1; break; }')
    cases.append('case 19: { double min_dist=fabs(ta)+0.1; double h=sin(z.x*12.9898+z.y*78.233)*43758.5453; h=h-floor(h); z.x=floor(z.x/min_dist+h)*min_dist; z.y=floor(z.y/min_dist+h)*min_dist; break; }')
    cases.append('case 20: { double h=sin(z.x*12.9898+z.y*78.233+z.z*45.164)*43758.5453; h=fabs(h-floor(h)); z.x+=h*ta*0.1; z.y+=(1.0-h)*tb*0.1; z.z+=fabs(sin(h*tc))*td*0.1; break; }')
    cases.append('case 21: { double theta = (double)i * 2.39996322972865332; double r = sqrt((double)i+0.5)*ta; z.x += r*cos(theta)*sf*0.1; z.y += r*sin(theta)*sf*0.1; break; }')
    cases.append('case 22: { double phi3 = 1.6180339887; double r_n = ta/pow(phi3, (double)i); aux.DE *= 1.0/phi3; z *= r_n/fmax(sqrt(z.x*z.x+z.y*z.y+z.z*z.z),0.01); break; }')
    cases.append('case 23: { double r_n = ta * exp(-(double)i * fabs(tb)); aux.DE *= exp(-fabs(tb)); z *= r_n/fmax(sqrt(z.x*z.x+z.y*z.y+z.z*z.z),0.01); break; }')
    cases.append('case 24: { double n = fmax((double)i+1.0, 1.0); double r_n = ta / (1.0 + log(n)*tb); aux.DE *= 1.0/(1.0+log(n)*tb); z *= r_n/fmax(sqrt(z.x*z.x+z.y*z.y+z.z*z.z),0.01); break; }')
    cases.append('case 25: { double n = fmax((double)i+1.0, 1.0); double p = fmax(fabs(ta), 0.1); aux.DE *= 1.0/pow(n,p); break; }')

    # === Menger V8-V32 (25 stuks) ===
    cases.append('case 26: { double sc = 3.0 + 0.5*sin((double)i*ta); z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 27: { double sx=fmax(ta,1.0),sy=fmax(tb,1.0),sz=fmax(tc,1.0); z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z.x=z.x*sx-(sx-1.0); z.y=z.y*sy-(sy-1.0); z.z=z.z*sz-(sz-1.0); aux.DE=aux.DE*fmax(fmax(sx,sy),sz)+1.0; break; }')
    cases.append('case 28: { double h=sin(z.x*ta*127.1+z.y*ta*311.7+z.z*ta*74.7)*43758.5453; h=h-floor(h); double sc=3.0; z=fabs(z)+CVector4(h*tb,h*tb,h*tb,0)*0.1; if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 29: { double angle=ta*M_PI/180.0; double ca=cos(angle),sa=sin(angle); double nx=z.x*ca-z.y*sa; double ny=z.x*sa+z.y*ca; z.x=fabs(nx);z.y=fabs(ny);z.z=fabs(z.z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} double sc=3.0; z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 30: { double eps=fmax(fabs(ta),0.01); double sc=3.0; z.x=fabs(z.x);z.y=fabs(z.y);z.z=fabs(z.z); double t; if(z.x<z.y){t=z.x+(z.y-z.x)*0.5*(1.0+tanh((z.y-z.x)/eps));z.y=z.y-(z.y-z.x)*0.5*(1.0+tanh((z.y-z.x)/eps));z.x=z.y;z.y=t;} if(z.x<z.z){t=z.x;z.x=z.z;z.z=t;} if(z.y<z.z){t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 31: { double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0)+CVector4(ta,tb,tc,0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 32: { double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); z.x+=aux.const_c.x*ta; z.y+=aux.const_c.y*ta; z.z+=aux.const_c.z*ta; aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 33: { double sc=3.0; double period=fmax(fabs(ta),0.1); z=CVector4(fmod(z.x+100.0*period,period)-period*0.5, fmod(z.y+100.0*period,period)-period*0.5, fmod(z.z+100.0*period,period)-period*0.5, z.w); z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 34: { double sc=3.0; double r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<1e-21)r2=1e-21; double inv=ta*ta/r2; z*=inv; aux.DE*=inv; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 35: { double lim=fabs(ta)+0.5; if(z.x>lim)z.x=2.0*lim-z.x; if(z.x<-lim)z.x=-2.0*lim-z.x; if(z.y>lim)z.y=2.0*lim-z.y; if(z.y<-lim)z.y=-2.0*lim-z.y; if(z.z>lim)z.z=2.0*lim-z.z; if(z.z<-lim)z.z=-2.0*lim-z.z; double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 36: { double r2=z.x*z.x+z.y*z.y+z.z*z.z; double minR2=fabs(ta)*fabs(ta); double fixedR2=1.0; double m; if(r2<minR2)m=fixedR2/minR2; else if(r2<fixedR2)m=fixedR2/r2; else m=1.0; z*=m; aux.DE*=m; double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 37: { int n=(int)fmax(ta,2.0); double angle=M_PI/n; for(int k=0;k<n;k++){double a=k*2.0*angle; double d=z.x*cos(a)+z.y*sin(a); if(d<0.0){z.x-=2.0*d*cos(a);z.y-=2.0*d*sin(a);}} double sc=3.0; z=z*sc-CVector4(1,1,1,0)*(sc-1.0)*tb; aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 38: { z.x=fabs(z.x);z.y=-fabs(z.y);z.z=fabs(z.z); double sc=3.0; if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0)*ta; aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 39: { double twist_k=ta*0.01; double angle=twist_k*(double)i; double ca=cos(angle),sa=sin(angle); double nx=z.x*ca-z.y*sa; z.y=z.x*sa+z.y*ca; z.x=nx; double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 40: { double bend=ta*0.001; z.z+=bend*(z.x*z.x+z.y*z.y); double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 41: { double shear=ta*0.1; z.x+=shear*z.y; double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 42: { double taper=ta*0.01; z.x*=(1.0-taper*z.z); z.y*=(1.0-taper*z.z); double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 43: { double period=fmax(fabs(ta),0.1); z=CVector4(fmod(z.x+100.0*period,period)-period*0.5, fmod(z.y+100.0*period,period)-period*0.5, fmod(z.z+100.0*period,period)-period*0.5, z.w); double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 44: { double sc1=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc1-CVector4(1,1,1,0)*(sc1-1.0); aux.DE=aux.DE*sc1+1.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc1-CVector4(1,1,1,0)*(sc1-1.0); aux.DE=aux.DE*sc1+1.0; break; }')
    cases.append('case 45: { double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*fabs(sc)+1.0; double surfScale=fabs(ta)+0.5; z.x=fabs(z.x+surfScale)-fabs(z.x-surfScale)-z.x; z.y=fabs(z.y+surfScale)-fabs(z.y-surfScale)-z.y; break; }')
    cases.append('case 46: { double sc=3.0; double r2=z.x*z.x+z.y*z.y+z.z*z.z; double minR2=fabs(ta)*fabs(ta); double fixedR2=1.0; double m; if(r2<minR2)m=fixedR2/minR2; else if(r2<fixedR2)m=fixedR2/r2; else m=1.0; z*=m; aux.DE=aux.DE*m; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 47: { double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; double k_angle=ta*M_PI/180.0; CVector3 nv(cos(k_angle),sin(k_angle),0); CVector3 zv=z.GetXYZ(); double dot=zv.Dot(nv); if(dot<0){zv=zv-nv*(2.0*dot); z=CVector4(zv,z.w);} break; }')
    cases.append('case 48: { double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; z+=CVector4(aux.const_c.x*ta,aux.const_c.y*ta,aux.const_c.z*ta,0)*tb; break; }')
    cases.append('case 49: { double sc=3.0+0.1*sin((double)i*ta); z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*fabs(sc)+1.0; z=CVector4(0.9*z.x+0.1*ta,0.9*z.y+0.1*tb,0.9*z.z+0.1*tc,z.w); break; }')
    cases.append('case 50: { double h1=sin(ta*z.x+tb*z.y+tc*z.z); double h2=sin(td*h1+ta*(double)i*0.1); double sc=3.0+sf*h2*0.1; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*fabs(sc)+1.0; break; }')

    # === 4D Menger & Hyper-Menger (15 stuks) ===
    cases.append('case 51: { double sc=3.0; CVector4 zz=fabs(z); double vals[4]={zz.x,zz.y,zz.z,zz.w}; for(int a=0;a<4;a++)for(int b=a+1;b<4;b++){if(vals[a]<vals[b]){double t=vals[a];vals[a]=vals[b];vals[b]=t;}} z=CVector4(vals[0],vals[1],vals[2],vals[3])*sc-CVector4(1,1,1,1)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 52: { double sc=3.0; double v[5]={fabs(z.x),fabs(z.y),fabs(z.z),fabs(z.w),fabs(sin(z.x+z.y))}; for(int a=0;a<5;a++)for(int b=a+1;b<5;b++){if(v[a]<v[b]){double t=v[a];v[a]=v[b];v[b]=t;}} z=CVector4(v[0],v[1],v[2],v[3])*sc-CVector4(1,1,1,1)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 53: { double sc=3.0; z.w=ta; CVector4 zz=fabs(z); double vals[4]={zz.x,zz.y,zz.z,zz.w}; for(int a=0;a<4;a++)for(int b=a+1;b<4;b++){if(vals[a]<vals[b]){double t=vals[a];vals[a]=vals[b];vals[b]=t;}} z=CVector4(vals[0],vals[1],vals[2],vals[3])*sc-CVector4(1,1,1,1)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 54: { double angle4d=ta*M_PI/180.0*(double)i; double ca=cos(angle4d),sa=sin(angle4d); double nx=z.x*ca-z.w*sa; z.w=z.x*sa+z.w*ca; z.x=nx; double sc=3.0; CVector4 zz=fabs(z); double vals[4]={zz.x,zz.y,zz.z,zz.w}; for(int a=0;a<4;a++)for(int b=a+1;b<4;b++){if(vals[a]<vals[b]){double t=vals[a];vals[a]=vals[b];vals[b]=t;}} z=CVector4(vals[0],vals[1],vals[2],vals[3])*sc-CVector4(1,1,1,1)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 55: { double sc=3.0; CVector4 zz=fabs(z); double vals[4]={zz.x,zz.y,zz.z,zz.w}; for(int a=0;a<4;a++)for(int b=a+1;b<4;b++){if(vals[a]<vals[b]){double t=vals[a];vals[a]=vals[b];vals[b]=t;}} z=CVector4(vals[0],vals[1],vals[2],vals[3])*sc-CVector4(1,1,1,1)*(sc-1.0)+CVector4(ta,tb,tc,td); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 56: { double sc=3.0; double qn=sqrt(z.x*z.x+z.y*z.y+z.z*z.z+z.w*z.w); z.w=qn*ta; CVector4 zz=fabs(z); double vals[4]={zz.x,zz.y,zz.z,zz.w}; for(int a=0;a<4;a++)for(int b=a+1;b<4;b++){if(vals[a]<vals[b]){double t=vals[a];vals[a]=vals[b];vals[b]=t;}} z=CVector4(vals[0],vals[1],vals[2],vals[3])*sc-CVector4(1,1,1,1)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 57: { double sc=3.0; double qr=z.x,qi=z.y,qj=z.z,qk=z.w; z.x=qr*qi-qj*qk; z.y=qr*qj+qi*qk; z.z=qr*qk-qi*qj; z.w=qr*qr-qi*qi-qj*qj-qk*qk; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,1)*(sc-1.0)*ta; aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 58: { double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z+z.w*z.w); double d=tanh(fmin(r*ta,10.0)); CVector4 unit=z/fmax(r,1e-21); z=unit*d; double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); double ch=cosh(fmin(r*ta,20.0)); aux.DE=aux.DE*sc/(ch*ch)+1.0; break; }')
    cases.append('case 59: { double r4=sqrt(z.x*z.x+z.y*z.y+z.z*z.z+z.w*z.w); if(r4>1e-21){z/=r4;} double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0)*ta; aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 60: { double r2d=sqrt(z.x*z.x+z.y*z.y); double theta=atan2(z.y,z.x); z.x=r2d; z.y=theta*ta; double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); z.x=z.x*cos(z.y/fmax(ta,0.01))-z.z*sin(z.y/fmax(ta,0.01)); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 61: { double R=fabs(ta)+0.5; double r2d=sqrt(z.x*z.x+z.y*z.y); z.x=r2d-R; double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 62: { double theta4=ta*M_PI/180.0; double ca=cos(theta4),sa=sin(theta4); double nx=z.z*ca-z.w*sa; z.w=z.z*sa+z.w*ca; z.z=nx; double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 63: { double golden=2.39996322972865332; double theta=(double)i*golden*ta; z.x+=cos(theta)*tb*0.01; z.y+=sin(theta)*tb*0.01; z.z+=cos(theta*0.5)*tc*0.01; z.w=sin(theta*0.5)*td*0.01; double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 64: { double D=2.7268; double sc=pow(3.0,D/3.0); z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0)*ta; aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 65: { double h=sin(z.x*12.9898+z.y*78.233+z.z*45.164+(double)i*ta)*43758.5453; h=h-floor(h); double sc=3.0; z=fabs(z); double vals[3]={z.x,z.y,z.z}; if(h>0.5){if(vals[0]<vals[1]){double t=vals[0];vals[0]=vals[1];vals[1]=t;}} if(h>0.25){if(vals[0]<vals[2]){double t=vals[0];vals[0]=vals[2];vals[2]=t;}} if(h>0.75){if(vals[1]<vals[2]){double t=vals[1];vals[1]=vals[2];vals[2]=t;}} z=CVector4(vals[0],vals[1],vals[2],z.w)*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')

    # === Cross & Prism Menger (20 stuks) ===
    cases.append('case 66: { double sc=3.0; double sq32=0.866025; z=fabs(z); double d=z.x*sq32+z.y*0.5; if(d<0.0){z.x-=2.0*d*sq32;z.y-=d;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0)*ta; aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 67: { double sc=3.0; double a60=M_PI/3.0; for(int k=0;k<6;k++){double a=k*a60; double d=z.x*cos(a)+z.y*sin(a); if(d<0.0){z.x-=2.0*d*cos(a);z.y-=2.0*d*sin(a);}} z=z*sc-CVector4(1,1,1,0)*(sc-1.0)*ta; aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 68: { double sc=3.0; double a45=M_PI/4.0; for(int k=0;k<8;k++){double a=k*a45; double d=z.x*cos(a)+z.y*sin(a); if(d<0.0){z.x-=2.0*d*cos(a);z.y-=2.0*d*sin(a);}} z=z*sc-CVector4(1,1,1,0)*(sc-1.0)*ta; aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 69: { double sc=3.0; double a30=M_PI/6.0; for(int k=0;k<12;k++){double a=k*a30; double d=z.x*cos(a)+z.y*sin(a); if(d<0.0){z.x-=2.0*d*cos(a);z.y-=2.0*d*sin(a);}} z=z*sc-CVector4(1,1,1,0)*(sc-1.0)*ta; aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 70: { double sc=3.0; double a72=M_PI*2.0/5.0; for(int k=0;k<5;k++){double a=k*a72; double d=z.x*cos(a)+z.y*sin(a); if(d<0.0){z.x-=2.0*d*cos(a);z.y-=2.0*d*sin(a);}} z=z*sc-CVector4(1,1,1,0)*(sc-1.0)*ta; aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 71: { double sc=3.0; double a60=M_PI/3.0; for(int k=0;k<6;k++){double a=k*a60; double d=z.x*cos(a)+z.y*sin(a); if(d<0.0){z.x-=2.0*d*cos(a);z.y-=2.0*d*sin(a);}} z=z*sc-CVector4(1,1,1,0)*(sc-1.0)*ta; aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 72: { double sc=3.0; double a45=M_PI/4.0; for(int k=0;k<8;k++){double a=k*a45; double d=z.x*cos(a)+z.y*sin(a); if(d<0.0){z.x-=2.0*d*cos(a);z.y-=2.0*d*sin(a);}} z=z*sc-CVector4(1,1,1,0)*(sc-1.0)*ta; aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 73: { double sc=3.0; double a36=M_PI/5.0; for(int k=0;k<10;k++){double a=k*a36; double d=z.x*cos(a)+z.y*sin(a); if(d<0.0){z.x-=2.0*d*cos(a);z.y-=2.0*d*sin(a);}} z=z*sc-CVector4(1,1,1,0)*(sc-1.0)*ta; aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 74: { int n=(int)fmax(ta,3.0); double sc=3.0; double aStep=M_PI*2.0/n; for(int k=0;k<n&&k<16;k++){double a=k*aStep; double d=z.x*cos(a)+z.y*sin(a); if(d<0.0){z.x-=2.0*d*cos(a);z.y-=2.0*d*sin(a);}} z=z*sc-CVector4(1,1,1,0)*(sc-1.0)*tb; aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 75: { double sc=3.0; int n=(int)fmax(ta,3.0); double amp=fabs(tb); double theta=atan2(z.y,z.x); double r2d=sqrt(z.x*z.x+z.y*z.y); double star_r=r2d*(1.0+amp*cos(n*theta)); z.x=star_r*cos(theta); z.y=star_r*sin(theta); z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 76: { double sc=3.0; double theta=atan2(z.y,z.x); double r2d=sqrt(z.x*z.x+z.y*z.y); double heart_r=r2d*(1.0-sin(theta)*fabs(ta)); z.x=heart_r*cos(theta); z.y=heart_r*sin(theta); z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 77: { double spiral_a=ta*0.01*(double)i; double ca=cos(spiral_a),sa=sin(spiral_a); double nx=z.x*ca-z.y*sa; z.y=z.x*sa+z.y*ca; z.x=nx; double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 78: { double r2=z.x*z.x+z.y*z.y; z.z+=ta*0.001*r2; double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 79: { double r2d=sqrt(z.x*z.x+z.y*z.y); double taper_w=1.0-ta*0.01*fabs(r2d); z.x*=taper_w; z.y*=taper_w; double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 80: { double twist_a=ta*0.01*sqrt(z.x*z.x+z.y*z.y); double ca=cos(twist_a),sa=sin(twist_a); double nx=z.x*ca-z.y*sa; z.y=z.x*sa+z.y*ca; z.x=nx; double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 81: { double eps=fmax(fabs(ta),0.01); double sc=3.0; z=fabs(z); double t; if(z.x<z.y){double blend=0.5+0.5*tanh((z.y-z.x)/eps);t=z.x*(1.0-blend)+z.y*blend;z.y=z.y*(1.0-blend)+z.x*blend;z.x=t;} if(z.x<z.z){t=z.x;z.x=z.z;z.z=t;} if(z.y<z.z){t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 82: { double h=sin(z.x*ta*127.1+z.y*ta*311.7+z.z*ta*74.7)*43758.5453; h=h-floor(h); z+=CVector4(h,1.0-h,h*0.5,0)*tb*0.01; double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 83: { double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0)+CVector4(ta,tb,tc,0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 84: { double period=fmax(fabs(ta),0.1); z=CVector4(fmod(fabs(z.x)+100.0*period,period)-period*0.5, fmod(fabs(z.y)+100.0*period,period)-period*0.5, fmod(fabs(z.z)+100.0*period,period)-period*0.5, z.w); double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 85: { double r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<1e-21)r2=1e-21; double inv=ta*ta/r2; z*=inv; aux.DE*=inv; double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')

    # === Meta-Menger & Hybrides (15 stuks) ===
    cases.append('case 86: { double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE*=(1.0+sf*exp(-r*ta)*tb); break; }')
    cases.append('case 87: { double sc=3.0; if(z.x+z.y<0.0){double t=z.x;z.x=-z.y;z.y=-t;} if(z.x+z.z<0.0){double t=z.x;z.x=-z.z;z.z=-t;} if(z.y+z.z<0.0){double t=z.y;z.y=-z.z;z.z=-t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0)*ta; aux.DE=aux.DE*sc+1.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 88: { double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; double koch_scale=2.0*ta; z.x=fabs(z.x)-koch_scale*0.5; z.y=fabs(z.y)-koch_scale*0.5; break; }')
    cases.append('case 89: { double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; if(z.x>0)z.x=-(z.x-1.0); break; }')
    cases.append('case 90: { double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; double fern_angle=ta*M_PI/180.0; double ca=cos(fern_angle),sa=sin(fern_angle); double nx=z.x*ca-z.z*sa; z.z=z.x*sa+z.z*ca; z.x=nx; z*=0.85*tb; aux.DE*=0.85*fabs(tb); break; }')
    cases.append('case 91: { double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; double shell=fabs(r-ta)-tb; aux.DE*=(1.0+sf*exp(-shell*shell*tc)); break; }')
    cases.append('case 92: { double period=fmax(fabs(ta),0.1); z=CVector4(fmod(z.x+100.0*period,period)-period*0.5, fmod(z.y+100.0*period,period)-period*0.5, fmod(z.z+100.0*period,period)-period*0.5, z.w); double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 93: { double r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<1e-21)r2=1e-21; double inv=ta*ta/r2; z*=inv; aux.DE*=inv; double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 94: { double clip=fabs(ta); z.x=fmin(fmax(z.x,-clip),clip); z.y=fmin(fmax(z.y,-clip),clip); z.z=fmin(fmax(z.z,-clip),clip); double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 95: { double lim=fabs(ta)+0.5; if(z.x>lim)z.x=2.0*lim-z.x; if(z.x<-lim)z.x=-2.0*lim-z.x; if(z.y>lim)z.y=2.0*lim-z.y; if(z.y<-lim)z.y=-2.0*lim-z.y; if(z.z>lim)z.z=2.0*lim-z.z; if(z.z<-lim)z.z=-2.0*lim-z.z; double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 96: { double r2=z.x*z.x+z.y*z.y+z.z*z.z; double minR2=fabs(ta)*fabs(ta); double fixedR2=1.0; double m; if(r2<minR2)m=fixedR2/minR2; else if(r2<fixedR2)m=fixedR2/r2; else m=1.0; z*=m; aux.DE*=m; double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 97: { double angle=ta*M_PI/180.0*(double)i; double ca=cos(angle),sa=sin(angle); double nx=z.x*ca-z.y*sa; z.y=z.x*sa+z.y*ca; z.x=nx; double sc=3.0; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+1.0; break; }')
    cases.append('case 98: { double sc=3.0*(1.0+sf*0.1*sin((double)i*ta)); z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*fabs(sc)+1.0; break; }')
    cases.append('case 99: { double sc=3.0; double offset=fabs(ta); z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*sc+offset; break; }')
    cases.append('case 100: { double h1=sin(ta*z.x+tb*z.y+tc*z.z); double h2=sin(td*h1+ta*(double)i*0.1); double sc=3.0+sf*h2*0.05; z=fabs(z); if(z.x-z.y<0.0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0); aux.DE=aux.DE*fabs(sc)+1.0; break; }')

    return cases


def to_gpu(cpu_code):
    """Convert CPU code to OpenCL GPU code."""
    gpu = cpu_code
    gpu = gpu.replace('double ', 'float ')
    gpu = gpu.replace('M_PI', 'M_PI_F')
    gpu = gpu.replace('sin(', 'native_sin(')
    gpu = gpu.replace('cos(', 'native_cos(')
    gpu = gpu.replace('sqrt(', 'native_sqrt(')
    gpu = gpu.replace('exp(', 'native_exp(')
    gpu = gpu.replace('log(', 'native_log(')
    gpu = gpu.replace('CVector4(', '(float4)(')
    gpu = gpu.replace('CVector3(', '(float3)(')
    gpu = gpu.replace('.GetXYZ()', '.xyz')
    gpu = gpu.replace('.Dot(', ', ')  # approx
    gpu = gpu.replace('aux.', 'aux->')
    # Fix double replacements
    gpu = gpu.replace('native_sin(h(', 'sinh(')
    gpu = gpu.replace('native_cos(h(', 'cosh(')
    gpu = gpu.replace('anative_cos(', 'acos(')
    gpu = gpu.replace('anative_sin(', 'asin(')
    gpu = gpu.replace('fnative_exp(', 'fexp(')  # shouldn't happen but guard
    return gpu


def gen_cpu_section(cases, system_name, type_var, factor_var, param_prefix,
                    iter_start_var, iter_stop_var, version):
    lines = []
    lines.append(f'\t\t\t\t// {version} — {system_name} DE system (per-section iteration range)')
    lines.append(f'\t\t\t\tif (i >= mut.{iter_start_var} && i < mut.{iter_stop_var} && mut.{type_var} != 0)')
    lines.append('\t\t\t\t{')
    lines.append(f'\t\t\t\t\tdouble sf = mut.{factor_var};')
    lines.append(f'\t\t\t\t\tdouble ta = mut.{param_prefix}A, tb = mut.{param_prefix}B;')
    lines.append(f'\t\t\t\t\tdouble tc = mut.{param_prefix}C, td = mut.{param_prefix}D;')
    lines.append(f'\t\t\t\t\tswitch(mut.{type_var}) {{')
    for c in cases:
        lines.append(f'\t\t\t\t\t\t{c}')
    lines.append('\t\t\t\t\t}')
    lines.append('\t\t\t\t}')
    return '\n'.join(lines)


def gen_gpu_section(cases, system_name, type_var, factor_var, param_prefix,
                    iter_start_var, iter_stop_var, version):
    lines = []
    lines.append(f'\t\t\t\t// {version} — {system_name} DE system (per-section iteration range)')
    lines.append(f'\t\t\t\tif (i >= mut->{iter_start_var} && i < mut->{iter_stop_var} && mut->{type_var} != 0)')
    lines.append('\t\t\t\t{')
    lines.append(f'\t\t\t\t\tfloat sf = mut->{factor_var};')
    lines.append(f'\t\t\t\t\tfloat ta = mut->{param_prefix}A, tb = mut->{param_prefix}B;')
    lines.append(f'\t\t\t\t\tfloat tc = mut->{param_prefix}C, td = mut->{param_prefix}D;')
    lines.append(f'\t\t\t\t\tswitch(mut->{type_var}) {{')
    for c in cases:
        lines.append(f'\t\t\t\t\t\t{to_gpu(c)}')
    lines.append('\t\t\t\t\t}')
    lines.append('\t\t\t\t}')
    return '\n'.join(lines)


if __name__ == '__main__':
    # Amazing Surf 1-4
    as_cases = gen_as_cpu()
    as_cpu = gen_cpu_section(as_cases, 'Amazing Surf 1-4', 'asType', 'asFactor',
                             'asParam', 'asIterStart', 'asIterStop', 'v7.13')
    as_gpu = gen_gpu_section(as_cases, 'Amazing Surf 1-4', 'asType', 'asFactor',
                             'asParam', 'asIterStart', 'asIterStop', 'v7.13')
    with open('gen_as_cpu.txt', 'w') as f:
        f.write(as_cpu)
    with open('gen_as_gpu.txt', 'w') as f:
        f.write(as_gpu)

    # SphereTree/Menger
    sm_cases = gen_spheretree_menger_cpu()
    sm_cpu = gen_cpu_section(sm_cases, 'SphereTree/Menger', 'smType', 'smFactor',
                             'smParam', 'smIterStart', 'smIterStop', 'v7.13')
    sm_gpu = gen_gpu_section(sm_cases, 'SphereTree/Menger', 'smType', 'smFactor',
                             'smParam', 'smIterStart', 'smIterStop', 'v7.13')
    with open('gen_sm_cpu.txt', 'w') as f:
        f.write(sm_cpu)
    with open('gen_sm_gpu.txt', 'w') as f:
        f.write(sm_gpu)

    print(f'Generated Amazing Surf 1-4: {len(as_cases)} cases')
    print(f'Generated SphereTree/Menger: {len(sm_cases)} cases')
    print('CPU: gen_as_cpu.txt, gen_sm_cpu.txt')
    print('GPU: gen_as_gpu.txt, gen_sm_gpu.txt')
