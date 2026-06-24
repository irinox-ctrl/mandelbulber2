// Auto-generated mutation switch for system: as
// Target: GPU
// Generated mutations: 100
switch (mut->asType)
{
	case 1: // Type 1
	{
		double k = ta; double DE0 = tb; aux.DE = 1.0f/(1.0f + exp(-k*(aux.DE - DE0)));
		break;
	}
	case 2: // Type 2
	{
		double DE0 = ta; double sigma = fmax(fabs(tb), 0.01f); aux.DE *= exp(-(aux.DE-DE0)*(aux.DE-DE0)/(sigma*sigma));
		break;
	}
	case 3: // Type 3
	{
		double threshold = ta; double DE_max = fabs(tb)+1.0f; double DE_min = fabs(tc)*0.01f; aux.DE = (aux.DE > threshold) ? DE_max : DE_min;
		break;
	}
	case 4: // Type 4
	{
		double b1=ta, b2=tb; double d1=fabs(tc),d2=fabs(td); if(aux.DE<b1) aux.DE=d1; else if(aux.DE<b2) aux.DE=d2;
		break;
	}
	case 5: // Type 5
	{
		double h = sin(z.x*127.1f+z.y*311.7f+z.z*74.7f)*43758.5453f; h=h-floor(h); aux.DE += sf*(h*2.0f-1.0f)*ta;
		break;
	}
	case 6: // Type 6
	{
		double jx=z.x*z.x-z.y*z.y+ta; double jy=2.0f*z.x*z.y+tb; double julia_mag=sqrt(jx*jx+jy*jy); aux.DE *= (1.0f + sf*0.1f*julia_mag);
		break;
	}
	case 7: // Type 7
	{
		aux.DE *= (1.0f + sf*0.1f*sin(ta*(double)i*0.1f));
		break;
	}
	case 8: // Type 8
	{
		double alpha=fmin(fmax(ta,0.01f),0.99f); aux.DE = alpha*aux.DE + (1.0f-alpha)*tb;
		break;
	}
	case 9: // Type 9
	{
		double h1=sin(ta*z.x+tb*z.y+tc*z.z); double h2=sin(td*h1+ta*aux.DE); aux.DE *= (1.0f + sf*h2);
		break;
	}
	case 10: // Type 10
	{
		double v=0,f=ta,a=1.0f; for(int k=0;k<4;k++){double h=sin(z.x*f*127.1f+z.y*f*311.7f+z.z*f*74.7f)*43758.5453f;h=h-floor(h);v+=a*h;f*=2.0f;a*=0.5f;} aux.DE *= (1.0f + sf*0.1f*v);
		break;
	}
	case 11: // Type 11
	{
		double speed = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE /= (1.0f + sf*speed*ta);
		break;
	}
	case 12: // Type 12
	{
		double sc = fabs(ta) + 0.01f; aux.DE *= sc;
		break;
	}
	case 13: // Type 13
	{
		double angle = atan2(z.y,z.x); aux.DE *= (1.0f + sf*fabs(angle)*ta/M_PI);
		break;
	}
	case 14: // Type 14
	{
		double shear = fabs(z.x*z.y*ta) + fabs(z.y*z.z*tb) + fabs(z.z*z.x*tc); aux.DE *= (1.0f + sf*shear);
		break;
	}
	case 15: // Type 15
	{
		double progress = (double)i / fmax((double)(i+10), 1.0f); aux.DE *= (1.0f + sf*(1.0f-progress)*ta);
		break;
	}
	case 16: // Type 16
	{
		double box = fmax(fabs(z.x),fmax(fabs(z.y),fabs(z.z))); if(box > fabs(ta)) aux.DE *= (1.0f + sf*tb);
		break;
	}
	case 17: // Type 17
	{
		double d = sqrt((z.x-ta)*(z.x-ta)+(z.y-tb)*(z.y-tb)+(z.z-tc)*(z.z-tc)); if(d < fabs(td)) aux.DE *= (1.0f + sf);
		break;
	}
	case 18: // Type 18
	{
		double w = fabs(ta)+0.01f; if(fabs(z.x)<w && fabs(z.y)<w) aux.DE *= (1.0f + sf*tb);
		break;
	}
	case 19: // Type 19
	{
		double intensity = sin(z.x*ta)*sin(z.y*tb)*sin(z.z*tc); aux.DE *= (1.0f + sf*0.1f*intensity*intensity);
		break;
	}
	case 20: // Type 20
	{
		double ao = 1.0f/(1.0f + (double)i*ta*0.01f); aux.DE *= (1.0f - sf*ao*fabs(tb));
		break;
	}
	case 21: // Type 21
	{
		double gi = sin(z.x*ta+z.y*tb)*0.5f+0.5f; aux.DE /= (1.0f + sf*gi*fabs(tc));
		break;
	}
	case 22: // Type 22
	{
		double depth = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= (1.0f + sf*ta*depth);
		break;
	}
	case 23: // Type 23
	{
		double light_accum = sin(z.x*ta)*sin(z.y*ta)*0.5f+0.5f; aux.DE /= (1.0f + sf*light_accum*tb);
		break;
	}
	case 24: // Type 24
	{
		double ss_depth = exp(-fabs(ta)*sqrt(z.x*z.x+z.y*z.y+z.z*z.z)); aux.DE *= (1.0f + sf*ss_depth*tb);
		break;
	}
	case 25: // Type 25
	{
		double wl_diff = fabs(z.x*ta - tb); aux.DE *= (1.0f + sf*tc*wl_diff);
		break;
	}
	case 26: // Type 26
	{
		double caustic = sin(z.x*ta*10.0f)*sin(z.y*tb*10.0f); aux.DE *= (1.0f + sf*caustic*caustic*tc);
		break;
	}
	case 27: // Type 27
	{
		double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double view_dot = z.z/fmax(r,1e-21); double fresnel = pow(fmax(1.0f-fabs(view_dot),0.0f), ta); aux.DE *= (1.0f + sf*fresnel*tb);
		break;
	}
	case 28: // Type 28
	{
		double thin_film = sin(ta*sqrt(z.x*z.x+z.y*z.y+z.z*z.z)*M_PI*2.0f); aux.DE *= (1.0f + sf*thin_film*thin_film*tb);
		break;
	}
	case 29: // Type 29
	{
		double tangent_dot = fabs(z.x*cos(ta)+z.y*sin(ta))/fmax(sqrt(z.x*z.x+z.y*z.y),1e-21); aux.DE *= (1.0f + sf*tangent_dot*tb);
		break;
	}
	case 30: // Type 30
	{
		double subdiv = fmax(1.0f, fabs(ta)); aux.DE /= (1.0f + sf*subdiv*tb);
		break;
	}
	case 31: // Type 31
	{
		double dist = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double lod = fmax(0.1f, dist*ta); aux.DE *= lod;
		break;
	}
	case 32: // Type 32
	{
		double edge_len = fabs(z.x-z.y) + fabs(z.y-z.z) + fabs(z.z-z.x); aux.DE *= (1.0f + sf*ta*edge_len*tb);
		break;
	}
	case 33: // Type 33
	{
		double disp = sin(z.x*ta*5.0f)*sin(z.y*tb*5.0f)*sin(z.z*tc*5.0f); aux.DE += sf*disp*td;
		break;
	}
	case 34: // Type 34
	{
		double h = sin(z.x*ta*7.0f+z.y*tb*11.0f+z.z*tc*13.0f)*43758.5453f; h=h-floor(h); aux.DE *= (1.0f + sf*(h*2.0f-1.0f)*td*0.1f);
		break;
	}
	case 35: // Type 35
	{
		double parallax = fabs(ta)*z.z/fmax(fabs(tb),0.01f); aux.DE *= (1.0f + sf*parallax*0.1f);
		break;
	}
	case 36: // Type 36
	{
		double n = fmax(fabs(ta)+1.0f, 1.01f); aux.DE /= n;
		break;
	}
	case 37: // Type 37
	{
		double dist_traveled = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= exp(-sf*fabs(ta)*dist_traveled);
		break;
	}
	case 38: // Type 38
	{
		double cos_theta = z.z/fmax(sqrt(z.x*z.x+z.y*z.y+z.z*z.z),1e-21); double phase = (1.0f+cos_theta*cos_theta)*0.75f; aux.DE *= (1.0f + sf*phase*ta);
		break;
	}
	case 39: // Type 39
	{
		double emission = sin(z.x*ta)*sin(z.y*ta)*0.5f+0.5f; aux.DE /= (1.0f + sf*emission*fabs(tb));
		break;
	}
	case 40: // Type 40
	{
		double curl_approx = sin(z.y*ta)*cos(z.z*tb) - cos(z.y*ta)*sin(z.z*tb); aux.DE *= (1.0f + sf*fabs(curl_approx)*tc);
		break;
	}
	case 41: // Type 41
	{
		double grad = (sin(z.x*ta)-sin((z.x+0.01f)*ta))/0.01f; aux.DE /= (1.0f + sf*fabs(grad)*tb);
		break;
	}
	case 42: // Type 42
	{
		double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double mass_d = fmax(r - ta, 0.01f); aux.DE *= (1.0f + sf*tb/(mass_d*mass_d));
		break;
	}
	case 43: // Type 43
	{
		double v2 = (z.x*z.x+z.y*z.y+z.z*z.z)*ta*ta; double lorentz = sqrt(fmax(1.0f - fmin(v2, 0.99f), 0.01f)); aux.DE *= lorentz;
		break;
	}
	case 44: // Type 44
	{
		double barrier = fabs(z.x - ta); aux.DE *= exp(-sf*fabs(tb)*barrier);
		break;
	}
	case 45: // Type 45
	{
		double psi2 = sin(ta*z.x)*sin(tb*z.y)*sin(tc*z.z); aux.DE *= (1.0f + sf*psi2*psi2);
		break;
	}
	case 46: // Type 46
	{
		double momentum = sqrt(z.x*z.x+z.y*z.y+z.z*z.z)*ta; double pos = fmax(fabs(z.x), 0.01f); aux.DE *= (1.0f + sf*tb/(2.0f*momentum*pos+0.01f));
		break;
	}
	case 47: // Type 47
	{
		double spin_dot = z.x*sin(ta)+z.y*cos(ta)+z.z*sin(tb); aux.DE *= (1.0f + sf*tc*spin_dot);
		break;
	}
	case 48: // Type 48
	{
		double corr = sin(z.x*ta)*sin((-z.x)*ta) + sin(z.y*tb)*sin((-z.y)*tb); aux.DE *= (1.0f + sf*fabs(corr)*tc);
		break;
	}
	case 49: // Type 49
	{
		double decay = exp(-sf*fabs(ta)*(double)i*0.01f); aux.DE *= decay;
		break;
	}
	case 50: // Type 50
	{
		double entropy = sin(z.x*ta*3.0f)*sin(z.y*tb*5.0f)*sin(z.z*tc*7.0f); double temp = fabs(td)+0.01f; aux.DE *= (1.0f + sf*temp*entropy*entropy);
		break;
	}
	case 51: // Type 51
	{
		double kT = fmax(fabs(ta)*fabs(tb), 0.01f); aux.DE *= (1.0f + sf*tc/kT);
		break;
	}
	case 52: // Type 52
	{
		double vel_grad = fabs(z.x-z.y)*ta + fabs(z.y-z.z)*tb; aux.DE *= (1.0f + sf*tc*vel_grad);
		break;
	}
	case 53: // Type 53
	{
		double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double curv = 1.0f/fmax(r,0.01f); aux.DE *= (1.0f + sf*ta*curv);
		break;
	}
	case 54: // Type 54
	{
		double tube_r = fmax(fabs(sqrt(z.x*z.x+z.y*z.y) - ta), 0.01f); aux.DE *= (1.0f + sf*cos(tb)/tube_r);
		break;
	}
	case 55: // Type 55
	{
		double conc_grad = fabs(sin(z.x*ta) - sin(z.y*ta)); aux.DE *= (1.0f + sf*tb*conc_grad);
		break;
	}
	case 56: // Type 56
	{
		double lap = sin((z.x+0.01f)*ta)+sin((z.x-0.01f)*ta)-2.0f*sin(z.x*ta); aux.DE += sf*tb*lap;
		break;
	}
	case 57: // Type 57
	{
		double vel_dot = sin(z.x*ta)*cos(z.y*tb); aux.DE *= (1.0f + sf*vel_dot*tc);
		break;
	}
	case 58: // Type 58
	{
		double v=0,f=ta,a=1.0f; for(int k=0;k<4;k++){double h=sin(z.x*f*12.9f+z.y*f*78.2f+z.z*f*45.1f)*43758.5453f;h=h-floor(h);v+=a*h;f*=2.0f;a*=0.5f;} aux.DE *= (1.0f + sf*v*tb);
		break;
	}
	case 59: // Type 59
	{
		double front = fabs(z.x - ta*i*0.01f); double shock = (front < fabs(tb)) ? tc : 1.0f; aux.DE *= shock;
		break;
	}
	case 60: // Type 60
	{
		double freq_diff = fabs(sin(z.x*ta) - sin(z.x*tb)); double Q = fmax(fabs(tc), 0.1f); aux.DE *= (1.0f + sf*Q*1.0f/fmax(freq_diff+0.01f, 0.01f));
		break;
	}
	case 61: // Type 61
	{
		double phase_diff = ta*z.x - tb*z.y; aux.DE *= (1.0f + sf*cos(phase_diff)*tc);
		break;
	}
	case 62: // Type 62
	{
		double v_source = ta * 0.1f; double angle = atan2(z.y, z.x); aux.DE *= (1.0f + sf*v_source*cos(angle)*tb);
		break;
	}
	case 63: // Type 63
	{
		double theta = atan2(z.y, z.x); aux.DE *= (1.0f + sf*ta*cos(2.0f*theta));
		break;
	}
	case 64: // Type 64
	{
		double phi2 = atan2(z.z, sqrt(z.x*z.x+z.y*z.y)); aux.DE *= (1.0f + sf*ta*fabs(sin(2.0f*phi2)));
		break;
	}
	case 65: // Type 65
	{
		double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double path = r * fabs(ta) * fabs(tb); aux.DE *= (1.0f + sf*tc*path);
		break;
	}
	case 66: // Type 66
	{
		double lat_pt = fmod(fabs(z.x*ta), 1.0f); double bandgap = (lat_pt < 0.5f) ? 1.0f : tb; aux.DE *= bandgap;
		break;
	}
	case 67: // Type 67
	{
		double surf_dist = fabs(sqrt(z.x*z.x+z.y*z.y+z.z*z.z) - ta); double skin = fmax(fabs(tb), 0.01f); aux.DE *= (1.0f + sf*tc*exp(-surf_dist/skin));
		break;
	}
	case 68: // Type 68
	{
		double neg_idx = fabs(ta); aux.DE *= (1.0f + sf*neg_idx*fabs(tb));
		break;
	}
	case 69: // Type 69
	{
		double winding = sin(z.x*ta)*cos(z.y*tb) + cos(z.x*ta)*sin(z.y*tb); aux.DE *= (1.0f + sf*fabs(winding)*tc);
		break;
	}
	case 70: // Type 70
	{
		double charge = sin(z.x*ta*5.0f)*sin(z.y*tb*5.0f)*sin(z.z*tc*5.0f); aux.DE *= (1.0f + sf*charge*charge*td);
		break;
	}
	case 71: // Type 71
	{
		double curl_mag = fabs(sin(z.y*ta)-sin(z.z*ta)) + fabs(sin(z.z*tb)-sin(z.x*tb)); aux.DE *= (1.0f + sf*curl_mag*tc);
		break;
	}
	case 72: // Type 72
	{
		double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double sech_val = 1.0f/cosh(fmin(ta*(r-tb), 20.0f)); aux.DE *= (1.0f + sf*tc*sech_val);
		break;
	}
	case 73: // Type 73
	{
		double S = fabs(ta)*sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= (1.0f + sf*tb*exp(-fmin(S,20.0f)));
		break;
	}
	case 74: // Type 74
	{
		double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double monopole = fabs(ta)/fmax(r,0.01f); aux.DE *= (1.0f + sf*monopole*tb);
		break;
	}
	case 75: // Type 75
	{
		double d_axis = sqrt(z.y*z.y+z.z*z.z); aux.DE *= (1.0f + sf*ta*log(fmax(d_axis,0.01f))*tb);
		break;
	}
	case 76: // Type 76
	{
		double d_brane = fabs(z.x - ta); double delta_approx = exp(-d_brane*d_brane*100.0f); aux.DE *= (1.0f + sf*tb*delta_approx);
		break;
	}
	case 77: // Type 77
	{
		double throat_d = (z.x-ta)*(z.x-ta)+(z.y-tb)*(z.y-tb)+(z.z-tc)*(z.z-tc); double throat_r = fmax(fabs(td), 0.01f); aux.DE *= (1.0f + sf*exp(-throat_d/(throat_r*throat_r)));
		break;
	}
	case 78: // Type 78
	{
		double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double rs = fmax(fabs(ta), 0.01f); aux.DE /= fmax(1.0f - rs/fmax(r,rs+0.01f), 0.01f);
		break;
	}
	case 79: // Type 79
	{
		double jet_d = z.y*z.y+z.z*z.z; double jet_w = fmax(fabs(tb), 0.01f); aux.DE *= (1.0f + sf*ta*exp(-jet_d/(jet_w*jet_w)));
		break;
	}
	case 80: // Type 80
	{
		double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double halo = 1.0f/(1.0f + r*r/(fmax(ta*ta,0.01f))); aux.DE *= (1.0f + sf*tb*halo);
		break;
	}
	case 81: // Type 81
	{
		double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= exp(sf*fabs(ta)*r*0.01f);
		break;
	}
	case 82: // Type 82
	{
		double d_string = sqrt(z.y*z.y+z.z*z.z); double horizon = fmax(fabs(tb), 0.01f); aux.DE *= (1.0f + sf*ta*log(fmax(d_string/horizon,0.01f)));
		break;
	}
	case 83: // Type 83
	{
		double d_wall = fabs(z.x - ta); double thickness = fmax(fabs(tb), 0.01f); aux.DE *= (1.0f + sf*tc*tanh(d_wall/thickness));
		break;
	}
	case 84: // Type 84
	{
		double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double theta2 = atan2(z.y,z.x); double phi2 = acos(z.z/fmax(r,1e-21)); double Ylm = sin(ta*theta2)*cos(tb*phi2); aux.DE *= (1.0f + sf*tc*Ylm*Ylm);
		break;
	}
	case 85: // Type 85
	{
		double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double efold = r*fabs(ta); aux.DE *= exp(sf*fmin(efold*tb, 10.0f));
		break;
	}
	case 86: // Type 86
	{
		double decay_t = exp(-fabs(ta)*(double)i*0.01f); aux.DE *= (1.0f + sf*tb*decay_t*tc);
		break;
	}
	case 87: // Type 87
	{
		double baryon = sin(z.x*ta)*sin(z.y*tb); double rate = exp(-fabs(tc)*(double)i*0.01f); aux.DE *= (1.0f + sf*baryon*baryon*rate*td);
		break;
	}
	case 88: // Type 88
	{
		double ion_frac = exp(-fabs(ta)/fmax(fabs(tb)*(double)i*0.01f+0.01f, 0.01f)); aux.DE *= (1.0f + sf*ion_frac*tc);
		break;
	}
	case 89: // Type 89
	{
		double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double scale_a = fmax(r*ta, 0.01f); double energy = 1.0f/(scale_a*scale_a); aux.DE *= (1.0f + sf*sqrt(energy)*tb);
		break;
	}
	case 90: // Type 90
	{
		double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double scale_a = fmax(r*ta, 0.01f); aux.DE /= fmax(scale_a*tb, 0.01f);
		break;
	}
	case 91: // Type 91
	{
		double ent_max = fabs(ta); double heat_time = fmax(fabs(tb), 0.01f); aux.DE *= (1.0f + sf*ent_max*(1.0f-exp(-(double)i*0.01f/heat_time)));
		break;
	}
	case 92: // Type 92
	{
		double bubble = sin(z.x*ta*5.0f)*sin(z.y*tb*5.0f)*sin(z.z*tc*5.0f); aux.DE *= (1.0f + sf*fabs(bubble)*td);
		break;
	}
	case 93: // Type 93
	{
		double barrier2 = fabs(ta); double tunnel = exp(-barrier2*sqrt(z.x*z.x+z.y*z.y+z.z*z.z)); aux.DE *= (1.0f + sf*tunnel*tb);
		break;
	}
	case 94: // Type 94
	{
		double order = sin(z.x*ta)*sin(z.y*tb); double latent = fabs(tc); aux.DE *= (1.0f + sf*latent*order*order);
		break;
	}
	case 95: // Type 95
	{
		double d_crit = sqrt((z.x-ta)*(z.x-ta)+(z.y-tb)*(z.y-tb)+(z.z-tc)*(z.z-tc)); double expo = fmax(fabs(td), 0.1f); aux.DE *= pow(fmax(d_crit, 0.01f), -expo);
		break;
	}
	case 96: // Type 96
	{
		double cutoff = fmax(fabs(ta), 0.01f); double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= (1.0f + sf*tb*log(fmax(cutoff/fmax(r,0.01f), 0.01f)));
		break;
	}
	case 97: // Type 97
	{
		double div_approx = cos(z.x*ta)*sin(z.y*tb)*cos(z.z*tc); aux.DE *= (1.0f + sf*fabs(div_approx)*td);
		break;
	}
	case 98: // Type 98
	{
		double vev = sqrt(z.x*z.x+z.y*z.y+z.z*z.z)*ta; aux.DE *= (1.0f + sf*vev*vev*tb);
		break;
	}
	case 99: // Type 99
	{
		double grad_phase = fabs(cos(z.x*ta)-cos(z.y*ta)) + fabs(cos(z.y*tb)-cos(z.z*tb)); aux.DE *= (1.0f + sf*tc*grad_phase);
		break;
	}
	case 100: // Type 100
	{
		double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double higgs = ta*tb*r*r; aux.DE *= (1.0f + sf*higgs);
		break;
	}
	default: break;
}