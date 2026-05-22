#!/usr/bin/env python3
"""Generate MandelTorus DE System (100 types) for CPU and GPU."""

def gen_mandeltorus_cpu():
    """Generate 100 MandelTorus DE cases for CPU."""
    cases = []
    
    # V1: Sigmoid DE
    cases.append('case 1: { double k = ta; double DE0 = tb; aux.DE = 1.0/(1.0 + exp(-k*(aux.DE - DE0))); break; }')
    # V2: Gaussian DE
    cases.append('case 2: { double DE0 = ta; double sigma = fmax(fabs(tb), 0.01); aux.DE *= exp(-(aux.DE-DE0)*(aux.DE-DE0)/(sigma*sigma)); break; }')
    # V3: Step DE
    cases.append('case 3: { double threshold = ta; double DE_max = fabs(tb)+1.0; double DE_min = fabs(tc)*0.01; aux.DE = (aux.DE > threshold) ? DE_max : DE_min; break; }')
    # V4: Multi-Band DE
    cases.append('case 4: { double b1=ta, b2=tb; double d1=fabs(tc),d2=fabs(td); if(aux.DE<b1) aux.DE=d1; else if(aux.DE<b2) aux.DE=d2; break; }')
    # V5: DE with Noise
    cases.append('case 5: { double h = sin(z.x*127.1+z.y*311.7+z.z*74.7)*43758.5453; h=h-floor(h); aux.DE += tf*(h*2.0-1.0)*ta; break; }')
    # V6: DE with Julia
    cases.append('case 6: { double jx=z.x*z.x-z.y*z.y+ta; double jy=2.0*z.x*z.y+tb; double julia_mag=sqrt(jx*jx+jy*jy); aux.DE *= (1.0 + tf*0.1*julia_mag); break; }')
    # V7: DE with Temporal
    cases.append('case 7: { aux.DE *= (1.0 + tf*0.1*sin(ta*(double)i*0.1)); break; }')
    # V8: DE with Feedback (smoothing)
    cases.append('case 8: { double alpha=fmin(fmax(ta,0.01),0.99); aux.DE = alpha*aux.DE + (1.0-alpha)*tb; break; }')
    # V9: DE with Neural (MLP approximation using sin layers)
    cases.append('case 9: { double h1=sin(ta*z.x+tb*z.y+tc*z.z); double h2=sin(td*h1+ta*aux.DE); aux.DE *= (1.0 + tf*h2); break; }')
    # V10: DE with Fractal noise
    cases.append('case 10: { double v=0,f=ta,a=1.0; for(int k=0;k<4;k++){double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453;h=h-floor(h);v+=a*h;f*=2.0;a*=0.5;} aux.DE *= (1.0 + tf*0.1*v); break; }')
    
    # V11: DE with Orbit speed
    cases.append('case 11: { double speed = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE /= (1.0 + tf*speed*ta); break; }')
    # V12: DE with Scale
    cases.append('case 12: { double sc = fabs(ta) + 0.01; aux.DE *= sc; break; }')
    # V13: DE with Rotation angle
    cases.append('case 13: { double angle = atan2(z.y,z.x); aux.DE *= (1.0 + tf*fabs(angle)*ta/(M_PI)); break; }')
    # V14: DE with Shear
    cases.append('case 14: { double shear = fabs(z.x*z.y*ta) + fabs(z.y*z.z*tb) + fabs(z.z*z.x*tc); aux.DE *= (1.0 + tf*shear); break; }')
    # V15: DE with Fold Timing
    cases.append('case 15: { double progress = (double)i / fmax((double)(i+10), 1.0); aux.DE *= (1.0 + tf*(1.0-progress)*ta); break; }')
    # V16: DE with Box Trap
    cases.append('case 16: { double box = fmax(fabs(z.x),fmax(fabs(z.y),fabs(z.z))); if(box > fabs(ta)) aux.DE *= (1.0 + tf*tb); break; }')
    # V17: DE with Sphere Trap
    cases.append('case 17: { double d = sqrt((z.x-ta)*(z.x-ta)+(z.y-tb)*(z.y-tb)+(z.z-tc)*(z.z-tc)); if(d < fabs(td)) aux.DE *= (1.0 + tf); break; }')
    # V18: DE with Cross Trap
    cases.append('case 18: { double w = fabs(ta)+0.01; if(fabs(z.x)<w && fabs(z.y)<w) aux.DE *= (1.0 + tf*tb); break; }')
    # V19: DE with Orbit Color intensity
    cases.append('case 19: { double intensity = sin(z.x*ta)*sin(z.y*tb)*sin(z.z*tc); aux.DE *= (1.0 + tf*0.1*intensity*intensity); break; }')
    # V20: DE with AO Factor
    cases.append('case 20: { double ao = 1.0/(1.0 + (double)i*ta*0.01); aux.DE *= (1.0 - tf*ao*fabs(tb)); break; }')
    
    # V21: DE with GI Factor
    cases.append('case 21: { double gi = sin(z.x*ta+z.y*tb)*0.5+0.5; aux.DE /= (1.0 + tf*gi*fabs(tc)); break; }')
    # V22: DE with Fog Density
    cases.append('case 22: { double depth = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= (1.0 + tf*ta*depth); break; }')
    # V23: DE with Volumetric Light
    cases.append('case 23: { double light_accum = sin(z.x*ta)*sin(z.y*ta)*0.5+0.5; aux.DE /= (1.0 + tf*light_accum*tb); break; }')
    # V24: DE with Subsurface
    cases.append('case 24: { double ss_depth = exp(-fabs(ta)*sqrt(z.x*z.x+z.y*z.y+z.z*z.z)); aux.DE *= (1.0 + tf*ss_depth*tb); break; }')
    # V25: DE with Dispersion
    cases.append('case 25: { double wl_diff = fabs(z.x*ta - tb); aux.DE *= (1.0 + tf*tc*wl_diff); break; }')
    # V26: DE with Caustics
    cases.append('case 26: { double caustic = sin(z.x*ta*10.0)*sin(z.y*tb*10.0); aux.DE *= (1.0 + tf*caustic*caustic*tc); break; }')
    # V27: DE with Fresnel
    cases.append('case 27: { double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double view_dot = z.z/fmax(r,1e-21); double fresnel = pow(fmax(1.0-fabs(view_dot),0.0), ta); aux.DE *= (1.0 + tf*fresnel*tb); break; }')
    # V28: DE with Iridescence
    cases.append('case 28: { double thin_film = sin(ta*sqrt(z.x*z.x+z.y*z.y+z.z*z.z)*M_PI*2.0); aux.DE *= (1.0 + tf*thin_film*thin_film*tb); break; }')
    # V29: DE with Anisotropy
    cases.append('case 29: { double tangent_dot = fabs(z.x*cos(ta)+z.y*sin(ta))/fmax(sqrt(z.x*z.x+z.y*z.y),1e-21); aux.DE *= (1.0 + tf*tangent_dot*tb); break; }')
    # V30: DE with Subdivision
    cases.append('case 30: { double subdiv = fmax(1.0, floor(ta*(double)i*0.1+1.0)); aux.DE /= subdiv*tf+1.0; break; }')
    
    # V31: DE with LOD
    cases.append('case 31: { double dist = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double lod = fmin(dist*ta, tb); aux.DE *= (1.0 + tf*lod); break; }')
    # V32: DE with Tessellation
    cases.append('case 32: { double edge = fabs(z.x-round(z.x*ta)/fmax(ta,1e-21)) + fabs(z.y-round(z.y*ta)/fmax(ta,1e-21)); aux.DE *= (1.0 + tf*edge*tb); break; }')
    # V33: DE with Displacement
    cases.append('case 33: { double h = sin(z.x*ta*10.0)*sin(z.y*tb*10.0)*sin(z.z*tc*10.0); aux.DE += tf*h*td; break; }')
    # V34: DE with Normal Perturbation
    cases.append('case 34: { double perturb = sin(z.x*ta*20.0)*cos(z.y*tb*20.0)*sin(z.z*tc*20.0); aux.DE *= (1.0 + tf*perturb*td); break; }')
    # V35: DE with Parallax
    cases.append('case 35: { double depth = sin(z.x*ta+z.y*tb)*0.5+0.5; aux.DE *= (1.0 + tf*depth*tc); break; }')
    # V36: DE with Refraction Index
    cases.append('case 36: { double n = fmax(fabs(ta), 0.1); aux.DE /= n; break; }')
    # V37: DE with Absorption
    cases.append('case 37: { double dist = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= exp(-tf*fabs(ta)*dist); break; }')
    # V38: DE with Scattering
    cases.append('case 38: { double cos_th = z.z/fmax(sqrt(z.x*z.x+z.y*z.y+z.z*z.z),1e-21); double phase = (1.0-ta*ta)/(1.0+ta*ta-2.0*ta*cos_th+1e-21); aux.DE *= (1.0 + tf*phase*tb); break; }')
    # V39: DE with Emission
    cases.append('case 39: { double emission = sin(z.x*ta)*sin(z.y*ta)*sin(z.z*ta); emission = emission*emission; aux.DE /= (1.0 + tf*emission*tb); break; }')
    # V40: DE with Torus Twist
    cases.append('case 40: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double theta = atan2(z.z,r2d-ta); double twist = sin(tb*phi + tc*theta); aux.DE *= (1.0 + tf*twist*twist); break; }')
    
    # V41: DE with Torus Major Radius
    cases.append('case 41: { double R = fabs(ta)+0.1; double r_min = fabs(tb)+0.01; double ratio = R/r_min; aux.DE *= (1.0 + tf*ratio*0.1); break; }')
    # V42: DE with Torus Minor Radius
    cases.append('case 42: { double R = fabs(ta)+0.1; double r_min = fabs(tb)+0.01; double ratio = r_min/R; aux.DE *= (1.0 + tf*ratio); break; }')
    # V43: DE with Torus Revolution
    cases.append('case 43: { double phi = atan2(z.y,z.x); double revolutions = ta*phi/(2.0*M_PI); aux.DE *= (1.0 + tf*sin(revolutions*2.0*M_PI)*tb); break; }')
    # V44: DE with Torus Hopf
    cases.append('case 44: { double r2 = z.x*z.x+z.y*z.y+z.z*z.z+1e-21; double w = sin(ta*r2); double hopf = cos(tb*atan2(z.y,z.x))*sin(tc*acos(z.z/sqrt(r2))); aux.DE *= (1.0 + tf*w*hopf); break; }')
    # V45: DE with Torus Helix
    cases.append('case 45: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double helix_r = ta + tb*sin(tc*phi); double d = fabs(r2d - helix_r); aux.DE *= (1.0 + tf*exp(-td*d)); break; }')
    # V46: DE with Torus Mobius
    cases.append('case 46: { double phi = atan2(z.y,z.x); double half_twist = sin(phi*0.5); double r2d = sqrt(z.x*z.x+z.y*z.y); double torus_d = fabs(r2d-ta); aux.DE *= (1.0 + tf*half_twist*half_twist*exp(-tb*torus_d)); break; }')
    # V47: DE with Torus Klein
    cases.append('case 47: { double phi = atan2(z.y,z.x); double R = ta; double r_k = tb*(1.0+0.5*cos(phi)); double r2d = sqrt(z.x*z.x+z.y*z.y); double d = fabs(r2d-R) + fabs(z.z)*r_k; aux.DE *= (1.0 + tf*exp(-tc*d)); break; }')
    # V48: DE with Torus Seifert
    cases.append('case 48: { double phi = atan2(z.y,z.x); double genus = fmax(floor(fabs(ta)*3+1),1.0); double fiber = sin(genus*phi)*cos(tb*z.z); aux.DE *= (1.0 + tf*fiber*fiber*tc); break; }')
    # V49: DE with Torus Satellite
    cases.append('case 49: { double phi = atan2(z.y,z.x); double wrapping = floor(fabs(ta)*4+2); double companion = sin(wrapping*phi)*tb; double r2d = sqrt(z.x*z.x+z.y*z.y); double d = fabs(r2d-tc-companion); aux.DE *= (1.0 + tf*exp(-td*d)); break; }')
    # V50: DE with Torus Hyperbolic
    cases.append('case 50: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double neg_curv = sin(ta*phi)*sin(tb*z.z)*exp(-tc*fabs(r2d-td)); aux.DE *= (1.0 + tf*neg_curv*neg_curv); break; }')
    
    # V51-V60: Torus knot variations (autonomous)
    cases.append('case 51: { double phi = atan2(z.y,z.x); double r2d = sqrt(z.x*z.x+z.y*z.y); double p=fmax(floor(fabs(ta)*3+2),2.0); double q=fmax(floor(fabs(tb)*3+3),3.0); double knot_r = tc + td*cos(q*phi); double knot_z2 = td*sin(q*phi); double d = sqrt((r2d-knot_r)*(r2d-knot_r)+(z.z-knot_z2)*(z.z-knot_z2)); aux.DE *= (1.0 + tf*exp(-d*5.0)); break; }')
    cases.append('case 52: { double phi = atan2(z.y,z.x); double r2d = sqrt(z.x*z.x+z.y*z.y); double trefoil_r = ta*(2.0+cos(3.0*phi)); double trefoil_z = ta*sin(3.0*phi); double d = sqrt((r2d-trefoil_r)*(r2d-trefoil_r)+(z.z-trefoil_z)*(z.z-trefoil_z)); aux.DE *= (1.0 + tf*exp(-tb*d)); break; }')
    cases.append('case 53: { double phi = atan2(z.y,z.x); double r2d = sqrt(z.x*z.x+z.y*z.y); double cinquefoil_r = ta*(2.0+cos(5.0*phi)); double cinquefoil_z = ta*sin(5.0*phi); double d = sqrt((r2d-cinquefoil_r)*(r2d-cinquefoil_r)+(z.z-cinquefoil_z)*(z.z-cinquefoil_z)); aux.DE *= (1.0 + tf*exp(-tb*d)); break; }')
    cases.append('case 54: { double phi = atan2(z.y,z.x); double r2d = sqrt(z.x*z.x+z.y*z.y); double fig8_r = ta*(2.0+cos(2.0*phi)); double fig8_z = ta*sin(4.0*phi)*0.5; double d = sqrt((r2d-fig8_r)*(r2d-fig8_r)+(z.z-fig8_z)*(z.z-fig8_z)); aux.DE *= (1.0 + tf*exp(-tb*d)); break; }')
    cases.append('case 55: { double t2 = atan2(z.y,z.x)*ta; double r2d = sqrt(z.x*z.x+z.y*z.y); double lissajous_r = tb*(2.0+sin(3.0*t2)*cos(2.0*t2)); double d = fabs(r2d-lissajous_r)+fabs(z.z)*tc; aux.DE *= (1.0 + tf*exp(-d*td)); break; }')
    
    # V56-V65: Torus surface deformations (autonomous)
    cases.append('case 56: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double theta = atan2(z.z,r2d-ta); double bump = sin(tb*phi)*sin(tc*theta); aux.DE *= (1.0 + tf*bump*bump*td); break; }')
    cases.append('case 57: { double r2d = sqrt(z.x*z.x+z.y*z.y); double R = ta; double r = tb; double torus_d = sqrt((r2d-R)*(r2d-R)+z.z*z.z)-r; double corrugation = sin(tc*atan2(z.y,z.x)*10.0)*td; aux.DE *= (1.0 + tf*exp(-(torus_d-corrugation)*(torus_d-corrugation))); break; }')
    cases.append('case 58: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double wave_R = ta + tb*sin(tc*phi)*sin(td*z.z); double d = fabs(r2d-wave_R); aux.DE *= (1.0 + tf*exp(-d*5.0)); break; }')
    cases.append('case 59: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double spiral_R = ta + tb*phi/(2.0*M_PI); double d = fabs(r2d-spiral_R)+fabs(z.z)*tc; aux.DE *= (1.0 + tf*exp(-d*td)); break; }')
    cases.append('case 60: { double r2d = sqrt(z.x*z.x+z.y*z.y); double star_n = fmax(floor(fabs(ta)*5+3),3.0); double phi = atan2(z.y,z.x); double star_R = tb*(1.0+tc*cos(star_n*phi)); double d = fabs(r2d-star_R)+fabs(z.z)*td; aux.DE *= (1.0 + tf*exp(-d*5.0)); break; }')
    cases.append('case 61: { double r2d = sqrt(z.x*z.x+z.y*z.y); double R = ta; double r = tb; double torus_d = sqrt((r2d-R)*(r2d-R)+z.z*z.z)-r; double fracture = sin(z.x*tc*20.0)*sin(z.y*tc*20.0)*td; aux.DE *= (1.0 + tf*exp(-fabs(torus_d)*5.0)*(1.0+fracture)); break; }')
    cases.append('case 62: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double egg_R = ta*(1.0+tb*sin(phi)); double d = sqrt((r2d-egg_R)*(r2d-egg_R)+z.z*z.z)-tc; aux.DE *= (1.0 + tf*exp(-fabs(d)*td)); break; }')
    cases.append('case 63: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double gear_n = fmax(floor(fabs(ta)*8+4),4.0); double gear_R = tb*(1.0+tc*fmax(cos(gear_n*phi)-0.5,0.0)); double d = fabs(r2d-gear_R); aux.DE *= (1.0 + tf*exp(-d*td*10.0)); break; }')
    cases.append('case 64: { double r2d = sqrt(z.x*z.x+z.y*z.y); double R = ta; double r = tb; double torus_d = sqrt((r2d-R)*(r2d-R)+z.z*z.z)-r; double erosion = sin(z.x*tc*5.0)*sin(z.y*tc*5.0)*sin(z.z*tc*5.0); aux.DE *= (1.0 + tf*exp(-fabs(torus_d)*5.0)*fabs(erosion)*td); break; }')
    cases.append('case 65: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double theta = atan2(z.z,r2d-ta); double superformula = pow(fabs(cos(tb*theta/4.0)),tc)+pow(fabs(sin(tb*theta/4.0)),tc); double sf_r = td*pow(superformula,-1.0/fmax(tc,0.01)); double d = sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-sf_r; aux.DE *= (1.0 + tf*exp(-fabs(d)*5.0)); break; }')
    
    # V66-V75: Torus field effects (autonomous)
    cases.append('case 66: { double r2d = sqrt(z.x*z.x+z.y*z.y); double R = ta; double gravity = 1.0/fmax((r2d-R)*(r2d-R)+z.z*z.z+0.01, 0.01); aux.DE *= (1.0 + tf*fmin(gravity*tb,10.0)); break; }')
    cases.append('case 67: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double B_field = ta*sin(tb*phi)/(fmax(fabs(r2d-tc),0.01)); aux.DE *= (1.0 + tf*fmin(fabs(B_field),10.0)*td); break; }')
    cases.append('case 68: { double r2d = sqrt(z.x*z.x+z.y*z.y); double vortex = ta*exp(-tb*((r2d-tc)*(r2d-tc)+z.z*z.z)); double circulation = sin(td*atan2(z.y,z.x)); aux.DE *= (1.0 + tf*vortex*circulation); break; }')
    cases.append('case 69: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double plasma = sin(ta*r2d)*cos(tb*phi)*sin(tc*z.z); double temperature = exp(-td*sqrt((r2d-1.0)*(r2d-1.0)+z.z*z.z)); aux.DE *= (1.0 + tf*plasma*temperature); break; }')
    cases.append('case 70: { double r2d = sqrt(z.x*z.x+z.y*z.y); double R = ta; double charge = tb/fmax(sqrt((r2d-R)*(r2d-R)+z.z*z.z),0.01); double screen = exp(-tc*sqrt((r2d-R)*(r2d-R)+z.z*z.z)); aux.DE *= (1.0 + tf*charge*screen*td); break; }')
    cases.append('case 71: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double wave1 = sin(ta*phi + tb*z.z); double wave2 = sin(tc*phi - tb*z.z); double interference = (wave1+wave2)*(wave1+wave2)*0.25; aux.DE *= (1.0 + tf*interference*td); break; }')
    cases.append('case 72: { double r2d = sqrt(z.x*z.x+z.y*z.y); double R = ta; double thermal = exp(-tb*((r2d-R)*(r2d-R)+z.z*z.z)); double fluctuation = sin(tc*z.x)*sin(tc*z.y)*sin(tc*z.z); aux.DE *= (1.0 + tf*thermal*(1.0+td*fluctuation)); break; }')
    cases.append('case 73: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); int modes = (int)fmax(2,fmin(ta*5,10)); double v = 0; for(int m=1;m<=modes;m++) v+=sin(m*phi*tb)*cos(m*z.z*tc)/m; aux.DE *= (1.0 + tf*v*v*td); break; }')
    cases.append('case 74: { double r2d = sqrt(z.x*z.x+z.y*z.y); double R = ta; double diffusion = 1.0/(1.0 + tb*(double)i*0.01); double concentration = exp(-tc*fabs(r2d-R))*diffusion; aux.DE *= (1.0 + tf*concentration*td); break; }')
    cases.append('case 75: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double reaction = sin(ta*phi)*sin(tb*z.z); double diffuse = exp(-tc*((r2d-td)*(r2d-td))); double rd = reaction*diffuse; aux.DE *= (1.0 + tf*rd*rd); break; }')
    
    # V76-V85: Torus multi-torus (autonomous)
    cases.append('case 76: { double r2d = sqrt(z.x*z.x+z.y*z.y); double d1 = sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; double d2 = sqrt((r2d-tc)*(r2d-tc)+z.z*z.z)-td; aux.DE *= (1.0 + tf*exp(-fmin(d1*d1,d2*d2)*5.0)); break; }')
    cases.append('case 77: { double r2d = sqrt(z.x*z.x+z.y*z.y); double ryz = sqrt(z.y*z.y+z.z*z.z); double d1 = sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; double d2 = sqrt((ryz-ta)*(ryz-ta)+z.x*z.x)-tb; aux.DE *= (1.0 + tf*exp(-fmin(d1*d1,d2*d2)*tc)); break; }')
    cases.append('case 78: { double r2d = sqrt(z.x*z.x+z.y*z.y); double rxz = sqrt(z.x*z.x+z.z*z.z); double ryz = sqrt(z.y*z.y+z.z*z.z); double d1=fabs(sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb); double d2=fabs(sqrt((rxz-ta)*(rxz-ta)+z.y*z.y)-tb); double d3=fabs(sqrt((ryz-ta)*(ryz-ta)+z.x*z.x)-tb); aux.DE *= (1.0 + tf*exp(-fmin(d1,fmin(d2,d3))*tc)); break; }')
    cases.append('case 79: { double phi = atan2(z.y,z.x); double r2d = sqrt(z.x*z.x+z.y*z.y); int n = (int)fmax(2,fmin(ta*4,8)); double md = 1e10; for(int k=0;k<n;k++){ double ang = k*2.0*M_PI/n; double cx = tb*cos(ang); double cy = tb*sin(ang); double d = sqrt((z.x-cx)*(z.x-cx)+(z.y-cy)*(z.y-cy)+z.z*z.z)-tc; if(fabs(d)<md) md=fabs(d); } aux.DE *= (1.0 + tf*exp(-md*td)); break; }')
    cases.append('case 80: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double R_var = ta + tb*sin(tc*phi); double torus_d = sqrt((r2d-R_var)*(r2d-R_var)+z.z*z.z)-td; aux.DE *= (1.0 + tf*exp(-torus_d*torus_d*5.0)); break; }')
    cases.append('case 81: { double r2d = sqrt(z.x*z.x+z.y*z.y); double d1 = sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; double d2 = sqrt((r2d-ta)*(r2d-ta)+(z.z-tc)*(z.z-tc))-tb; aux.DE *= (1.0 + tf*exp(-fmin(fabs(d1),fabs(d2))*td)); break; }')
    cases.append('case 82: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double R1 = ta; double r1 = tb; double R2 = tc; double r2 = td; double d1 = sqrt((r2d-R1)*(r2d-R1)+z.z*z.z)-r1; double d2 = sqrt((r2d-R2)*(r2d-R2)+z.z*z.z)-r2; double smooth = -log(exp(-d1*5.0)+exp(-d2*5.0)+1e-21)/5.0; aux.DE *= (1.0 + tf*exp(-smooth*smooth)); break; }')
    cases.append('case 83: { double r2d = sqrt(z.x*z.x+z.y*z.y); double torus_d = sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; double sphere_d = sqrt(z.x*z.x+z.y*z.y+z.z*z.z)-tc; double d = fmax(torus_d, -sphere_d); aux.DE *= (1.0 + tf*exp(-fabs(d)*td)); break; }')
    cases.append('case 84: { double r2d = sqrt(z.x*z.x+z.y*z.y); double torus_d = sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; double box_d = fmax(fabs(z.x)-tc,fmax(fabs(z.y)-tc,fabs(z.z)-td))-0.0; double d = fmax(torus_d,box_d); aux.DE *= (1.0 + tf*exp(-fabs(d)*5.0)); break; }')
    cases.append('case 85: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double inner_r = tb*(1.0+tc*sin(td*phi)); double torus_d = sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-inner_r; aux.DE *= (1.0 + tf*exp(-torus_d*torus_d*5.0)); break; }')
    
    # V86-V95: Torus dynamics (autonomous)
    cases.append('case 86: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double flow = sin(ta*phi-(double)i*tb*0.1); double torus_d = sqrt((r2d-tc)*(r2d-tc)+z.z*z.z)-td; aux.DE *= (1.0 + tf*flow*flow*exp(-fabs(torus_d)*5.0)); break; }')
    cases.append('case 87: { double r2d = sqrt(z.x*z.x+z.y*z.y); double omega = ta*(double)i*0.01; double R_t = tb*(1.0+tc*sin(omega)); double torus_d = sqrt((r2d-R_t)*(r2d-R_t)+z.z*z.z)-td; aux.DE *= (1.0 + tf*exp(-torus_d*torus_d*5.0)); break; }')
    cases.append('case 88: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double stretch = 1.0 + ta*sin(tb*phi); double torus_d = sqrt((r2d-tc*stretch)*(r2d-tc*stretch)+z.z*z.z)-td/stretch; aux.DE *= (1.0 + tf*exp(-torus_d*torus_d*5.0)); break; }')
    cases.append('case 89: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phase = ta*(double)i*0.1; double wobble_z = tb*sin(phase); double torus_d = sqrt((r2d-tc)*(r2d-tc)+(z.z-wobble_z)*(z.z-wobble_z))-td; aux.DE *= (1.0 + tf*exp(-torus_d*torus_d*5.0)); break; }')
    cases.append('case 90: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double pulse = exp(-ta*((double)i*0.1-tb)*((double)i*0.1-tb)); double torus_d = sqrt((r2d-tc)*(r2d-tc)+z.z*z.z)-td*(1.0+pulse); aux.DE *= (1.0 + tf*exp(-torus_d*torus_d*5.0)); break; }')
    cases.append('case 91: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double bifurcation = ta*sin(tb*phi)*sin(tc*phi*2.0); double torus_d = sqrt((r2d-td-bifurcation)*(r2d-td-bifurcation)+z.z*z.z)-0.3; aux.DE *= (1.0 + tf*exp(-torus_d*torus_d*5.0)); break; }')
    cases.append('case 92: { double r2d = sqrt(z.x*z.x+z.y*z.y); double chaos = sin(ta*z.x)*cos(tb*z.y)*sin(tc*z.z); double torus_d = sqrt((r2d-td)*(r2d-td)+z.z*z.z)-fabs(chaos)*0.5; aux.DE *= (1.0 + tf*exp(-torus_d*torus_d*5.0)); break; }')
    cases.append('case 93: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double soliton = 1.0/cosh(ta*(r2d-tb)); double torus_phase = sin(tc*phi+td*z.z); aux.DE *= (1.0 + tf*soliton*torus_phase*torus_phase); break; }')
    cases.append('case 94: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double breather = sin(ta*(double)i*0.1)*sin(tb*phi)/cosh(tc*(r2d-td)); aux.DE *= (1.0 + tf*breather*breather); break; }')
    cases.append('case 95: { double r2d = sqrt(z.x*z.x+z.y*z.y); double torus_d = sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; double damping = exp(-tc*(double)i*0.01); aux.DE *= (1.0 + tf*sin(torus_d*td*10.0)*damping); break; }')
    
    # V96-V100: Torus special (autonomous)
    cases.append('case 96: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double theta = atan2(z.z,r2d-ta); double villarceau = sin(phi+theta*tb)*sin(phi-theta*tb); aux.DE *= (1.0 + tf*villarceau*villarceau*tc); break; }')
    cases.append('case 97: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double dupin = ta*(1.0+tb*cos(phi))*(1.0+tc*cos(atan2(z.z,r2d-ta))); double d = fabs(sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-dupin*0.3); aux.DE *= (1.0 + tf*exp(-d*td)); break; }')
    cases.append('case 98: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double theta = atan2(z.z,r2d-ta); double clifford_r = ta*(cos(tb*phi)*cos(tc*theta)); double clifford_d = fabs(sqrt(z.x*z.x+z.y*z.y+z.z*z.z)-fabs(clifford_r)); aux.DE *= (1.0 + tf*exp(-clifford_d*td)); break; }')
    cases.append('case 99: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double lawson_r = ta*cos(tb*phi)*cos(tc*z.z); double d = fabs(r2d-fabs(lawson_r)-td); aux.DE *= (1.0 + tf*exp(-d*5.0)); break; }')
    cases.append('case 100: { double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double theta = atan2(z.z,r2d-ta); double p=fmax(ta,0.1); double q=fmax(tb,0.1); double torus_knot_r = tc*(2.0+cos(q/p*phi)); double torus_knot_z = tc*sin(q/p*phi); double d = sqrt((r2d-torus_knot_r)*(r2d-torus_knot_r)+(z.z-torus_knot_z)*(z.z-torus_knot_z))-td; aux.DE *= (1.0 + tf*exp(-fabs(d)*5.0)); break; }')
    
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


def gen_section_cpu(cases):
    lines = []
    lines.append('\t\t\t\t// v7.12 — MandelTorus DE system (per-section iteration range)')
    lines.append('\t\t\t\tif (i >= mut.torusIterStart && i < mut.torusIterStop && mut.torusType != 0)')
    lines.append('\t\t\t\t{')
    lines.append('\t\t\t\t\tdouble tf = mut.torusFactor;')
    lines.append('\t\t\t\t\tdouble ta = mut.torusParamA, tb = mut.torusParamB, tc = mut.torusParamC, td = mut.torusParamD;')
    lines.append('\t\t\t\t\tswitch(mut.torusType) {')
    for c in cases:
        lines.append('\t\t\t\t\t\t' + c)
    lines.append('\t\t\t\t\t}')
    lines.append('\t\t\t\t}')
    return '\n'.join(lines)


def gen_section_gpu(cases):
    lines = []
    lines.append('\t\t\t// v7.12 [GPU] — MandelTorus DE system (per-section iteration range)')
    lines.append('\t\t\tif (i >= mut->torusIterStart && i < mut->torusIterStop && mut->torusType != 0)')
    lines.append('\t\t\t{')
    lines.append('\t\t\t\tfloat tf = mut->torusFactor;')
    lines.append('\t\t\t\tfloat ta = mut->torusParamA, tb = mut->torusParamB, tc = mut->torusParamC, td = mut->torusParamD;')
    lines.append('\t\t\t\tswitch(mut->torusType) {')
    for c in cases:
        lines.append('\t\t\t\t\t' + to_gpu(c))
    lines.append('\t\t\t\t}')
    lines.append('\t\t\t}')
    return '\n'.join(lines)


if __name__ == '__main__':
    cases = gen_mandeltorus_cpu()
    
    cpu = gen_section_cpu(cases)
    gpu = gen_section_gpu(cases)
    
    with open('gen_torus_cpu.txt', 'w') as f:
        f.write(cpu)
    with open('gen_torus_gpu.txt', 'w') as f:
        f.write(gpu)
    
    print(f'Generated {len(cases)} MandelTorus cases')
    print('CPU: gen_torus_cpu.txt')
    print('GPU: gen_torus_gpu.txt')
