// Auto-generated mutation switch for system: torus
// Target: GPU
// Generated mutations: 100
switch (mut->torusType)
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
		double h = sin(z.x*127.1f+z.y*311.7f+z.z*74.7f)*43758.5453f; h=h-floor(h); aux.DE += tf*(h*2.0f-1.0f)*ta;
		break;
	}
	case 6: // Type 6
	{
		double jx=z.x*z.x-z.y*z.y+ta; double jy=2.0f*z.x*z.y+tb; double julia_mag=sqrt(jx*jx+jy*jy); aux.DE *= (1.0f + tf*0.1f*julia_mag);
		break;
	}
	case 7: // Type 7
	{
		aux.DE *= (1.0f + tf*0.1f*sin(ta*(double)i*0.1f));
		break;
	}
	case 8: // Type 8
	{
		double alpha=fmin(fmax(ta,0.01f),0.99f); aux.DE = alpha*aux.DE + (1.0f-alpha)*tb;
		break;
	}
	case 9: // Type 9
	{
		double h1=sin(ta*z.x+tb*z.y+tc*z.z); double h2=sin(td*h1+ta*aux.DE); aux.DE *= (1.0f + tf*h2);
		break;
	}
	case 10: // Type 10
	{
		double v=0,f=ta,a=1.0f; for(int k=0;k<4;k++){double h=sin(z.x*f*127.1f+z.y*f*311.7f+z.z*f*74.7f)*43758.5453f;h=h-floor(h);v+=a*h;f*=2.0f;a*=0.5f;} aux.DE *= (1.0f + tf*0.1f*v);
		break;
	}
	case 11: // Type 11
	{
		double speed = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE /= (1.0f + tf*speed*ta);
		break;
	}
	case 12: // Type 12
	{
		double sc = fabs(ta) + 0.01f; aux.DE *= sc;
		break;
	}
	case 13: // Type 13
	{
		double angle = atan2(z.y,z.x); aux.DE *= (1.0f + tf*fabs(angle)*ta/(M_PI));
		break;
	}
	case 14: // Type 14
	{
		double shear = fabs(z.x*z.y*ta) + fabs(z.y*z.z*tb) + fabs(z.z*z.x*tc); aux.DE *= (1.0f + tf*shear);
		break;
	}
	case 15: // Type 15
	{
		double progress = (double)i / fmax((double)(i+10), 1.0f); aux.DE *= (1.0f + tf*(1.0f-progress)*ta);
		break;
	}
	case 16: // Type 16
	{
		double box = fmax(fabs(z.x),fmax(fabs(z.y),fabs(z.z))); if(box > fabs(ta)) aux.DE *= (1.0f + tf*tb);
		break;
	}
	case 17: // Type 17
	{
		double d = sqrt((z.x-ta)*(z.x-ta)+(z.y-tb)*(z.y-tb)+(z.z-tc)*(z.z-tc)); if(d < fabs(td)) aux.DE *= (1.0f + tf);
		break;
	}
	case 18: // Type 18
	{
		double w = fabs(ta)+0.01f; if(fabs(z.x)<w && fabs(z.y)<w) aux.DE *= (1.0f + tf*tb);
		break;
	}
	case 19: // Type 19
	{
		double intensity = sin(z.x*ta)*sin(z.y*tb)*sin(z.z*tc); aux.DE *= (1.0f + tf*0.1f*intensity*intensity);
		break;
	}
	case 20: // Type 20
	{
		double ao = 1.0f/(1.0f + (double)i*ta*0.01f); aux.DE *= (1.0f - tf*ao*fabs(tb));
		break;
	}
	case 21: // Type 21
	{
		double gi = sin(z.x*ta+z.y*tb)*0.5f+0.5f; aux.DE /= (1.0f + tf*gi*fabs(tc));
		break;
	}
	case 22: // Type 22
	{
		double depth = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= (1.0f + tf*ta*depth);
		break;
	}
	case 23: // Type 23
	{
		double light_accum = sin(z.x*ta)*sin(z.y*ta)*0.5f+0.5f; aux.DE /= (1.0f + tf*light_accum*tb);
		break;
	}
	case 24: // Type 24
	{
		double ss_depth = exp(-fabs(ta)*sqrt(z.x*z.x+z.y*z.y+z.z*z.z)); aux.DE *= (1.0f + tf*ss_depth*tb);
		break;
	}
	case 25: // Type 25
	{
		double wl_diff = fabs(z.x*ta - tb); aux.DE *= (1.0f + tf*tc*wl_diff);
		break;
	}
	case 26: // Type 26
	{
		double caustic = sin(z.x*ta*10.0f)*sin(z.y*tb*10.0f); aux.DE *= (1.0f + tf*caustic*caustic*tc);
		break;
	}
	case 27: // Type 27
	{
		double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double view_dot = z.z/fmax(r,1e-21); double fresnel = pow(fmax(1.0f-fabs(view_dot),0.0f), ta); aux.DE *= (1.0f + tf*fresnel*tb);
		break;
	}
	case 28: // Type 28
	{
		double thin_film = sin(ta*sqrt(z.x*z.x+z.y*z.y+z.z*z.z)*M_PI*2.0f); aux.DE *= (1.0f + tf*thin_film*thin_film*tb);
		break;
	}
	case 29: // Type 29
	{
		double tangent_dot = fabs(z.x*cos(ta)+z.y*sin(ta))/fmax(sqrt(z.x*z.x+z.y*z.y),1e-21); aux.DE *= (1.0f + tf*tangent_dot*tb);
		break;
	}
	case 30: // Type 30
	{
		double subdiv = fmax(1.0f, floor(ta*(double)i*0.1f+1.0f)); aux.DE /= subdiv*tf+1.0f;
		break;
	}
	case 31: // Type 31
	{
		double dist = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double lod = fmin(dist*ta, tb); aux.DE *= (1.0f + tf*lod);
		break;
	}
	case 32: // Type 32
	{
		double edge = fabs(z.x-round(z.x*ta)/fmax(ta,1e-21)) + fabs(z.y-round(z.y*ta)/fmax(ta,1e-21)); aux.DE *= (1.0f + tf*edge*tb);
		break;
	}
	case 33: // Type 33
	{
		double h = sin(z.x*ta*10.0f)*sin(z.y*tb*10.0f)*sin(z.z*tc*10.0f); aux.DE += tf*h*td;
		break;
	}
	case 34: // Type 34
	{
		double perturb = sin(z.x*ta*20.0f)*cos(z.y*tb*20.0f)*sin(z.z*tc*20.0f); aux.DE *= (1.0f + tf*perturb*td);
		break;
	}
	case 35: // Type 35
	{
		double depth = sin(z.x*ta+z.y*tb)*0.5f+0.5f; aux.DE *= (1.0f + tf*depth*tc);
		break;
	}
	case 36: // Type 36
	{
		double n = fmax(fabs(ta), 0.1f); aux.DE /= n;
		break;
	}
	case 37: // Type 37
	{
		double dist = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= exp(-tf*fabs(ta)*dist);
		break;
	}
	case 38: // Type 38
	{
		double cos_th = z.z/fmax(sqrt(z.x*z.x+z.y*z.y+z.z*z.z),1e-21); double phase = (1.0f-ta*ta)/(1.0f+ta*ta-2.0f*ta*cos_th+1e-21); aux.DE *= (1.0f + tf*phase*tb);
		break;
	}
	case 39: // Type 39
	{
		double emission = sin(z.x*ta)*sin(z.y*ta)*sin(z.z*ta); emission = emission*emission; aux.DE /= (1.0f + tf*emission*tb);
		break;
	}
	case 40: // Type 40
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double theta = atan2(z.z,r2d-ta); double twist = sin(tb*phi + tc*theta); aux.DE *= (1.0f + tf*twist*twist);
		break;
	}
	case 41: // Type 41
	{
		double R = fabs(ta)+0.1f; double r_min = fabs(tb)+0.01f; double ratio = R/r_min; aux.DE *= (1.0f + tf*ratio*0.1f);
		break;
	}
	case 42: // Type 42
	{
		double R = fabs(ta)+0.1f; double r_min = fabs(tb)+0.01f; double ratio = r_min/R; aux.DE *= (1.0f + tf*ratio);
		break;
	}
	case 43: // Type 43
	{
		double phi = atan2(z.y,z.x); double revolutions = ta*phi/(2.0f*M_PI); aux.DE *= (1.0f + tf*sin(revolutions*2.0f*M_PI)*tb);
		break;
	}
	case 44: // Type 44
	{
		double r2 = z.x*z.x+z.y*z.y+z.z*z.z+1e-21; double w = sin(ta*r2); double hopf = cos(tb*atan2(z.y,z.x))*sin(tc*acos(z.z/sqrt(r2))); aux.DE *= (1.0f + tf*w*hopf);
		break;
	}
	case 45: // Type 45
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double helix_r = ta + tb*sin(tc*phi); double d = fabs(r2d - helix_r); aux.DE *= (1.0f + tf*exp(-td*d));
		break;
	}
	case 46: // Type 46
	{
		double phi = atan2(z.y,z.x); double half_twist = sin(phi*0.5f); double r2d = sqrt(z.x*z.x+z.y*z.y); double torus_d = fabs(r2d-ta); aux.DE *= (1.0f + tf*half_twist*half_twist*exp(-tb*torus_d));
		break;
	}
	case 47: // Type 47
	{
		double phi = atan2(z.y,z.x); double R = ta; double r_k = tb*(1.0f+0.5f*cos(phi)); double r2d = sqrt(z.x*z.x+z.y*z.y); double d = fabs(r2d-R) + fabs(z.z)*r_k; aux.DE *= (1.0f + tf*exp(-tc*d));
		break;
	}
	case 48: // Type 48
	{
		double phi = atan2(z.y,z.x); double genus = fmax(floor(fabs(ta)*3+1),1.0f); double fiber = sin(genus*phi)*cos(tb*z.z); aux.DE *= (1.0f + tf*fiber*fiber*tc);
		break;
	}
	case 49: // Type 49
	{
		double phi = atan2(z.y,z.x); double wrapping = floor(fabs(ta)*4+2); double companion = sin(wrapping*phi)*tb; double r2d = sqrt(z.x*z.x+z.y*z.y); double d = fabs(r2d-tc-companion); aux.DE *= (1.0f + tf*exp(-td*d));
		break;
	}
	case 50: // Type 50
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double neg_curv = sin(ta*phi)*sin(tb*z.z)*exp(-tc*fabs(r2d-td)); aux.DE *= (1.0f + tf*neg_curv*neg_curv);
		break;
	}
	case 51: // Type 51
	{
		double phi = atan2(z.y,z.x); double r2d = sqrt(z.x*z.x+z.y*z.y); double p=fmax(floor(fabs(ta)*3+2),2.0f); double q=fmax(floor(fabs(tb)*3+3),3.0f); double knot_r = tc + td*cos(q*phi); double knot_z2 = td*sin(q*phi); double d = sqrt((r2d-knot_r)*(r2d-knot_r)+(z.z-knot_z2)*(z.z-knot_z2)); aux.DE *= (1.0f + tf*exp(-d*5.0f));
		break;
	}
	case 52: // Type 52
	{
		double phi = atan2(z.y,z.x); double r2d = sqrt(z.x*z.x+z.y*z.y); double trefoil_r = ta*(2.0f+cos(3.0f*phi)); double trefoil_z = ta*sin(3.0f*phi); double d = sqrt((r2d-trefoil_r)*(r2d-trefoil_r)+(z.z-trefoil_z)*(z.z-trefoil_z)); aux.DE *= (1.0f + tf*exp(-tb*d));
		break;
	}
	case 53: // Type 53
	{
		double phi = atan2(z.y,z.x); double r2d = sqrt(z.x*z.x+z.y*z.y); double cinquefoil_r = ta*(2.0f+cos(5.0f*phi)); double cinquefoil_z = ta*sin(5.0f*phi); double d = sqrt((r2d-cinquefoil_r)*(r2d-cinquefoil_r)+(z.z-cinquefoil_z)*(z.z-cinquefoil_z)); aux.DE *= (1.0f + tf*exp(-tb*d));
		break;
	}
	case 54: // Type 54
	{
		double phi = atan2(z.y,z.x); double r2d = sqrt(z.x*z.x+z.y*z.y); double fig8_r = ta*(2.0f+cos(2.0f*phi)); double fig8_z = ta*sin(4.0f*phi)*0.5f; double d = sqrt((r2d-fig8_r)*(r2d-fig8_r)+(z.z-fig8_z)*(z.z-fig8_z)); aux.DE *= (1.0f + tf*exp(-tb*d));
		break;
	}
	case 55: // Type 55
	{
		double t2 = atan2(z.y,z.x)*ta; double r2d = sqrt(z.x*z.x+z.y*z.y); double lissajous_r = tb*(2.0f+sin(3.0f*t2)*cos(2.0f*t2)); double d = fabs(r2d-lissajous_r)+fabs(z.z)*tc; aux.DE *= (1.0f + tf*exp(-d*td));
		break;
	}
	case 56: // Type 56
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double theta = atan2(z.z,r2d-ta); double bump = sin(tb*phi)*sin(tc*theta); aux.DE *= (1.0f + tf*bump*bump*td);
		break;
	}
	case 57: // Type 57
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double R = ta; double r = tb; double torus_d = sqrt((r2d-R)*(r2d-R)+z.z*z.z)-r; double corrugation = sin(tc*atan2(z.y,z.x)*10.0f)*td; aux.DE *= (1.0f + tf*exp(-(torus_d-corrugation)*(torus_d-corrugation)));
		break;
	}
	case 58: // Type 58
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double wave_R = ta + tb*sin(tc*phi)*sin(td*z.z); double d = fabs(r2d-wave_R); aux.DE *= (1.0f + tf*exp(-d*5.0f));
		break;
	}
	case 59: // Type 59
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double spiral_R = ta + tb*phi/(2.0f*M_PI); double d = fabs(r2d-spiral_R)+fabs(z.z)*tc; aux.DE *= (1.0f + tf*exp(-d*td));
		break;
	}
	case 60: // Type 60
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double star_n = fmax(floor(fabs(ta)*5+3),3.0f); double phi = atan2(z.y,z.x); double star_R = tb*(1.0f+tc*cos(star_n*phi)); double d = fabs(r2d-star_R)+fabs(z.z)*td; aux.DE *= (1.0f + tf*exp(-d*5.0f));
		break;
	}
	case 61: // Type 61
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double R = ta; double r = tb; double torus_d = sqrt((r2d-R)*(r2d-R)+z.z*z.z)-r; double fracture = sin(z.x*tc*20.0f)*sin(z.y*tc*20.0f)*td; aux.DE *= (1.0f + tf*exp(-fabs(torus_d)*5.0f)*(1.0f+fracture));
		break;
	}
	case 62: // Type 62
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double egg_R = ta*(1.0f+tb*sin(phi)); double d = sqrt((r2d-egg_R)*(r2d-egg_R)+z.z*z.z)-tc; aux.DE *= (1.0f + tf*exp(-fabs(d)*td));
		break;
	}
	case 63: // Type 63
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double gear_n = fmax(floor(fabs(ta)*8+4),4.0f); double gear_R = tb*(1.0f+tc*fmax(cos(gear_n*phi)-0.5f,0.0f)); double d = fabs(r2d-gear_R); aux.DE *= (1.0f + tf*exp(-d*td*10.0f));
		break;
	}
	case 64: // Type 64
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double R = ta; double r = tb; double torus_d = sqrt((r2d-R)*(r2d-R)+z.z*z.z)-r; double erosion = sin(z.x*tc*5.0f)*sin(z.y*tc*5.0f)*sin(z.z*tc*5.0f); aux.DE *= (1.0f + tf*exp(-fabs(torus_d)*5.0f)*fabs(erosion)*td);
		break;
	}
	case 65: // Type 65
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double theta = atan2(z.z,r2d-ta); double superformula = pow(fabs(cos(tb*theta/4.0f)),tc)+pow(fabs(sin(tb*theta/4.0f)),tc); double sf_r = td*pow(superformula,-1.0f/fmax(tc,0.01f)); double d = sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-sf_r; aux.DE *= (1.0f + tf*exp(-fabs(d)*5.0f));
		break;
	}
	case 66: // Type 66
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double R = ta; double gravity = 1.0f/fmax((r2d-R)*(r2d-R)+z.z*z.z+0.01f, 0.01f); aux.DE *= (1.0f + tf*fmin(gravity*tb,10.0f));
		break;
	}
	case 67: // Type 67
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double B_field = ta*sin(tb*phi)/(fmax(fabs(r2d-tc),0.01f)); aux.DE *= (1.0f + tf*fmin(fabs(B_field),10.0f)*td);
		break;
	}
	case 68: // Type 68
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double vortex = ta*exp(-tb*((r2d-tc)*(r2d-tc)+z.z*z.z)); double circulation = sin(td*atan2(z.y,z.x)); aux.DE *= (1.0f + tf*vortex*circulation);
		break;
	}
	case 69: // Type 69
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double plasma = sin(ta*r2d)*cos(tb*phi)*sin(tc*z.z); double temperature = exp(-td*sqrt((r2d-1.0f)*(r2d-1.0f)+z.z*z.z)); aux.DE *= (1.0f + tf*plasma*temperature);
		break;
	}
	case 70: // Type 70
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double R = ta; double charge = tb/fmax(sqrt((r2d-R)*(r2d-R)+z.z*z.z),0.01f); double screen = exp(-tc*sqrt((r2d-R)*(r2d-R)+z.z*z.z)); aux.DE *= (1.0f + tf*charge*screen*td);
		break;
	}
	case 71: // Type 71
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double wave1 = sin(ta*phi + tb*z.z); double wave2 = sin(tc*phi - tb*z.z); double interference = (wave1+wave2)*(wave1+wave2)*0.25f; aux.DE *= (1.0f + tf*interference*td);
		break;
	}
	case 72: // Type 72
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double R = ta; double thermal = exp(-tb*((r2d-R)*(r2d-R)+z.z*z.z)); double fluctuation = sin(tc*z.x)*sin(tc*z.y)*sin(tc*z.z); aux.DE *= (1.0f + tf*thermal*(1.0f+td*fluctuation));
		break;
	}
	case 73: // Type 73
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); int modes = (int)fmax(2,fmin(ta*5,10)); double v = 0; for(int m=1;m<=modes;m++) v+=sin(m*phi*tb)*cos(m*z.z*tc)/m; aux.DE *= (1.0f + tf*v*v*td);
		break;
	}
	case 74: // Type 74
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double R = ta; double diffusion = 1.0f/(1.0f + tb*(double)i*0.01f); double concentration = exp(-tc*fabs(r2d-R))*diffusion; aux.DE *= (1.0f + tf*concentration*td);
		break;
	}
	case 75: // Type 75
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double reaction = sin(ta*phi)*sin(tb*z.z); double diffuse = exp(-tc*((r2d-td)*(r2d-td))); double rd = reaction*diffuse; aux.DE *= (1.0f + tf*rd*rd);
		break;
	}
	case 76: // Type 76
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double d1 = sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; double d2 = sqrt((r2d-tc)*(r2d-tc)+z.z*z.z)-td; aux.DE *= (1.0f + tf*exp(-fmin(d1*d1,d2*d2)*5.0f));
		break;
	}
	case 77: // Type 77
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double ryz = sqrt(z.y*z.y+z.z*z.z); double d1 = sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; double d2 = sqrt((ryz-ta)*(ryz-ta)+z.x*z.x)-tb; aux.DE *= (1.0f + tf*exp(-fmin(d1*d1,d2*d2)*tc));
		break;
	}
	case 78: // Type 78
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double rxz = sqrt(z.x*z.x+z.z*z.z); double ryz = sqrt(z.y*z.y+z.z*z.z); double d1=fabs(sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb); double d2=fabs(sqrt((rxz-ta)*(rxz-ta)+z.y*z.y)-tb); double d3=fabs(sqrt((ryz-ta)*(ryz-ta)+z.x*z.x)-tb); aux.DE *= (1.0f + tf*exp(-fmin(d1,fmin(d2,d3))*tc));
		break;
	}
	case 79: // Type 79
	{
		double phi = atan2(z.y,z.x); double r2d = sqrt(z.x*z.x+z.y*z.y); int n = (int)fmax(2,fmin(ta*4,8)); double md = 1e10; for(int k=0;k<n;k++){ double ang = k*2.0f*M_PI/n; double cx = tb*cos(ang); double cy = tb*sin(ang); double d = sqrt((z.x-cx)*(z.x-cx)+(z.y-cy)*(z.y-cy)+z.z*z.z)-tc; if(fabs(d)<md) md=fabs(d); } aux.DE *= (1.0f + tf*exp(-md*td));
		break;
	}
	case 80: // Type 80
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double R_var = ta + tb*sin(tc*phi); double torus_d = sqrt((r2d-R_var)*(r2d-R_var)+z.z*z.z)-td; aux.DE *= (1.0f + tf*exp(-torus_d*torus_d*5.0f));
		break;
	}
	case 81: // Type 81
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double d1 = sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; double d2 = sqrt((r2d-ta)*(r2d-ta)+(z.z-tc)*(z.z-tc))-tb; aux.DE *= (1.0f + tf*exp(-fmin(fabs(d1),fabs(d2))*td));
		break;
	}
	case 82: // Type 82
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double R1 = ta; double r1 = tb; double R2 = tc; double r2 = td; double d1 = sqrt((r2d-R1)*(r2d-R1)+z.z*z.z)-r1; double d2 = sqrt((r2d-R2)*(r2d-R2)+z.z*z.z)-r2; double smooth = -log(fmax(exp(-d1*5.0f)+exp(-d2*5.0f),1e-21))/5.0f; aux.DE *= (1.0f + tf*exp(-smooth*smooth));
		break;
	}
	case 83: // Type 83
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double torus_d = sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; double sphere_d = sqrt(z.x*z.x+z.y*z.y+z.z*z.z)-tc; double d = fmax(torus_d, -sphere_d); aux.DE *= (1.0f + tf*exp(-fabs(d)*td));
		break;
	}
	case 84: // Type 84
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double torus_d = sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; double box_d = fmax(fabs(z.x)-tc,fmax(fabs(z.y)-tc,fabs(z.z)-td))-0.0f; double d = fmax(torus_d,box_d); aux.DE *= (1.0f + tf*exp(-fabs(d)*5.0f));
		break;
	}
	case 85: // Type 85
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double inner_r = tb*(1.0f+tc*sin(td*phi)); double torus_d = sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-inner_r; aux.DE *= (1.0f + tf*exp(-torus_d*torus_d*5.0f));
		break;
	}
	case 86: // Type 86
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double flow = sin(ta*phi-(double)i*tb*0.1f); double torus_d = sqrt((r2d-tc)*(r2d-tc)+z.z*z.z)-td; aux.DE *= (1.0f + tf*flow*flow*exp(-fabs(torus_d)*5.0f));
		break;
	}
	case 87: // Type 87
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double omega = ta*(double)i*0.01f; double R_t = tb*(1.0f+tc*sin(omega)); double torus_d = sqrt((r2d-R_t)*(r2d-R_t)+z.z*z.z)-td; aux.DE *= (1.0f + tf*exp(-torus_d*torus_d*5.0f));
		break;
	}
	case 88: // Type 88
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double stretch = 1.0f + ta*sin(tb*phi); double torus_d = sqrt((r2d-tc*stretch)*(r2d-tc*stretch)+z.z*z.z)-td/stretch; aux.DE *= (1.0f + tf*exp(-torus_d*torus_d*5.0f));
		break;
	}
	case 89: // Type 89
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phase = ta*(double)i*0.1f; double wobble_z = tb*sin(phase); double torus_d = sqrt((r2d-tc)*(r2d-tc)+(z.z-wobble_z)*(z.z-wobble_z))-td; aux.DE *= (1.0f + tf*exp(-torus_d*torus_d*5.0f));
		break;
	}
	case 90: // Type 90
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double pulse = exp(-ta*((double)i*0.1f-tb)*((double)i*0.1f-tb)); double torus_d = sqrt((r2d-tc)*(r2d-tc)+z.z*z.z)-td*(1.0f+pulse); aux.DE *= (1.0f + tf*exp(-torus_d*torus_d*5.0f));
		break;
	}
	case 91: // Type 91
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double bifurcation = ta*sin(tb*phi)*sin(tc*phi*2.0f); double torus_d = sqrt((r2d-td-bifurcation)*(r2d-td-bifurcation)+z.z*z.z)-0.3f; aux.DE *= (1.0f + tf*exp(-torus_d*torus_d*5.0f));
		break;
	}
	case 92: // Type 92
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double chaos = sin(ta*z.x)*cos(tb*z.y)*sin(tc*z.z); double torus_d = sqrt((r2d-td)*(r2d-td)+z.z*z.z)-fabs(chaos)*0.5f; aux.DE *= (1.0f + tf*exp(-torus_d*torus_d*5.0f));
		break;
	}
	case 93: // Type 93
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double soliton = 1.0f/cosh(ta*(r2d-tb)); double torus_phase = sin(tc*phi+td*z.z); aux.DE *= (1.0f + tf*soliton*torus_phase*torus_phase);
		break;
	}
	case 94: // Type 94
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double breather = sin(ta*(double)i*0.1f)*sin(tb*phi)/cosh(tc*(r2d-td)); aux.DE *= (1.0f + tf*breather*breather);
		break;
	}
	case 95: // Type 95
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double torus_d = sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-tb; double damping = exp(-tc*(double)i*0.01f); aux.DE *= (1.0f + tf*sin(torus_d*td*10.0f)*damping);
		break;
	}
	case 96: // Type 96
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double theta = atan2(z.z,r2d-ta); double villarceau = sin(phi+theta*tb)*sin(phi-theta*tb); aux.DE *= (1.0f + tf*villarceau*villarceau*tc);
		break;
	}
	case 97: // Type 97
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double dupin = ta*(1.0f+tb*cos(phi))*(1.0f+tc*cos(atan2(z.z,r2d-ta))); double d = fabs(sqrt((r2d-ta)*(r2d-ta)+z.z*z.z)-dupin*0.3f); aux.DE *= (1.0f + tf*exp(-d*td));
		break;
	}
	case 98: // Type 98
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double theta = atan2(z.z,r2d-ta); double clifford_r = ta*(cos(tb*phi)*cos(tc*theta)); double clifford_d = fabs(sqrt(z.x*z.x+z.y*z.y+z.z*z.z)-fabs(clifford_r)); aux.DE *= (1.0f + tf*exp(-clifford_d*td));
		break;
	}
	case 99: // Type 99
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double lawson_r = ta*cos(tb*phi)*cos(tc*z.z); double d = fabs(r2d-fabs(lawson_r)-td); aux.DE *= (1.0f + tf*exp(-d*5.0f));
		break;
	}
	case 100: // Type 100
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double phi = atan2(z.y,z.x); double theta = atan2(z.z,r2d-ta); double p=fmax(ta,0.1f); double q=fmax(tb,0.1f); double torus_knot_r = tc*(2.0f+cos(q/p*phi)); double torus_knot_z = tc*sin(q/p*phi); double d = sqrt((r2d-torus_knot_r)*(r2d-torus_knot_r)+(z.z-torus_knot_z)*(z.z-torus_knot_z))-td; aux.DE *= (1.0f + tf*exp(-fabs(d)*5.0f));
		break;
	}
	default: break;
}