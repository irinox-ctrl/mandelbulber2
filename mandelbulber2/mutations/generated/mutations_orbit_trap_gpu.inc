// Auto-generated mutation switch for system: orbit_trap
// Target: GPU
// Generated mutations: 100
switch (mut->orbitTrapType)
{
	case 1: // Type 1
	{
		double d = sqrt((z.x-oa)*(z.x-oa)+(z.y-ob)*(z.y-ob)+(z.z-oc)*(z.z-oc)); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 2: // Type 2
	{
		double d = fabs(z.x-oa)+fabs(z.y-ob)+fabs(z.z-oc); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 3: // Type 3
	{
		double d = fmax(fabs(z.x-oa),fmax(fabs(z.y-ob),fabs(z.z-oc))); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 4: // Type 4
	{
		double d1=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double d2=sqrt((z.x-oa)*(z.x-oa)+(z.y-ob)*(z.y-ob)+(z.z-oc)*(z.z-oc)); aux.DE *= (1.0f + of*exp(-od*fmin(d1,d2)));
		break;
	}
	case 5: // Type 5
	{
		double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double ring=fabs(d-oa); aux.DE *= (1.0f + of*exp(-od*ring));
		break;
	}
	case 6: // Type 6
	{
		double dx=z.x-oa*round(z.x/fmax(oa,1e-21)); double dy=z.y-ob*round(z.y/fmax(ob,1e-21)); double dz=z.z-oc*round(z.z/fmax(oc,1e-21)); double d=sqrt(dx*dx+dy*dy+dz*dz); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 7: // Type 7
	{
		double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double shell=fabs(d-oa); double shell2=fabs(d-ob); aux.DE *= (1.0f + of*exp(-od*fmin(shell,shell2)));
		break;
	}
	case 8: // Type 8
	{
		double ph=atan2(z.y,z.x); double r=sqrt(z.x*z.x+z.y*z.y); double spiral_r=oa+ob*ph/(2.0f*M_PI); double d=fabs(r-spiral_r); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 9: // Type 9
	{
		double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double v=sin(d*oa*M_PI)*0.5f+0.5f; aux.DE *= (1.0f + of*v);
		break;
	}
	case 10: // Type 10
	{
		int nn=(int)fmax(2,fmin(oa*6,12)); double md=1e10; for(int k=0;k<nn;k++){ double ang=k*2.0f*M_PI/nn; double cx=ob*cos(ang); double cy=ob*sin(ang); double d=(z.x-cx)*(z.x-cx)+(z.y-cy)*(z.y-cy)+z.z*z.z; if(d<md)md=d; } aux.DE *= (1.0f + of*exp(-od*sqrt(md)));
		break;
	}
	case 11: // Type 11
	{
		double d=z.x*z.x/(oa*oa+1e-21)+z.y*z.y/(ob*ob+1e-21)+z.z*z.z/(oc*oc+1e-21); d=fabs(sqrt(d)-1.0f); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 12: // Type 12
	{
		double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double th=atan2(z.y,z.x); double d=fabs(r-oa*(1.0f+ob*cos(oc*th))); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 13: // Type 13
	{
		double r2=z.x*z.x+z.y*z.y+z.z*z.z; double inv_r=oa*oa/fmax(r2,1e-21); double d=fabs(inv_r-1.0f)*sqrt(r2); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 14: // Type 14
	{
		double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double s=sin(d*oa); double c=cos(d*ob); aux.DE *= (1.0f + of*(s*s+c*c*0.5f)*exp(-od*d));
		break;
	}
	case 15: // Type 15
	{
		double d=fabs(z.x*oa+z.y*ob+z.z*oc)/fmax(sqrt(oa*oa+ob*ob+oc*oc),1e-21); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 16: // Type 16
	{
		double d=sqrt(z.y*z.y+z.z*z.z); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 17: // Type 17
	{
		double d=sqrt(z.x*z.x+z.z*z.z); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 18: // Type 18
	{
		double d=sqrt(z.x*z.x+z.y*z.y); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 19: // Type 19
	{
		double d=fabs(z.x*oa+z.y*ob+z.z*oc-od); aux.DE *= (1.0f + of*exp(-d));
		break;
	}
	case 20: // Type 20
	{
		double d=fmin(fabs(z.x),fmin(fabs(z.y),fabs(z.z))); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 21: // Type 21
	{
		double d1=fabs(z.x); double d2=fabs(z.y); double d3=fabs(z.z); aux.DE *= (1.0f + of*exp(-od*fmin(d1,d2))*exp(-od*d3));
		break;
	}
	case 22: // Type 22
	{
		double d=fmin(sqrt(z.x*z.x+z.y*z.y),sqrt(z.y*z.y+z.z*z.z)); d=fmin(d,sqrt(z.x*z.x+z.z*z.z)); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 23: // Type 23
	{
		double d1=fabs(z.x-oa); double d2=fabs(z.y-ob); double d3=fabs(z.z-oc); double d=d1*d2*d3; aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 24: // Type 24
	{
		double cs=cos(oa*M_PI/180.0f),sn=sin(oa*M_PI/180.0f); double rx=z.x*cs-z.y*sn; double ry=z.x*sn+z.y*cs; double d=fabs(ry); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 25: // Type 25
	{
		double d=fmin(fabs(z.x),fabs(z.y)); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 26: // Type 26
	{
		double d1=fabs(z.y-oa*z.x); double d2=fabs(z.y+oa*z.x); aux.DE *= (1.0f + of*exp(-od*fmin(d1,d2)));
		break;
	}
	case 27: // Type 27
	{
		double ph=atan2(z.y,z.x); int n=(int)fmax(3,fmin(oa,12)); double seg=2.0f*M_PI/n; double sph=fmod(ph+M_PI,seg)-seg*0.5f; double r=sqrt(z.x*z.x+z.y*z.y); double d=fabs(r*sin(sph)); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 28: // Type 28
	{
		double d1=fabs(z.x*sin(oa*M_PI/180.0f)-z.y*cos(oa*M_PI/180.0f)); double d2=fabs(z.x*sin(ob*M_PI/180.0f)-z.y*cos(ob*M_PI/180.0f)); aux.DE *= (1.0f + of*exp(-od*(d1+d2)));
		break;
	}
	case 29: // Type 29
	{
		double d=fabs(z.z-oa*sin(ob*z.x)*cos(oc*z.y)); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 30: // Type 30
	{
		double r=sqrt(z.x*z.x+z.y*z.y); double d=fabs(z.z-oa*sin(ob*r)); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 31: // Type 31
	{
		double r=sqrt(z.x*z.x+z.y*z.y); double d=fabs(r-oa); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 32: // Type 32
	{
		double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double d=fabs(r-oa); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 33: // Type 33
	{
		double r=sqrt(z.x*z.x+z.y*z.y); double d=sqrt((r-oa)*(r-oa)+z.z*z.z)-ob; aux.DE *= (1.0f + of*exp(-od*fabs(d)));
		break;
	}
	case 34: // Type 34
	{
		double r=sqrt(z.x*z.x+z.y*z.y); double th=atan2(z.y,z.x); double sf2=pow(fabs(cos(oa*th/4.0f)),ob)+pow(fabs(sin(oa*th/4.0f)),ob); double sr=oc*pow(sf2,-1.0f/fmax(ob,1e-21)); double d=fabs(r-sr); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 35: // Type 35
	{
		double ph=atan2(z.y,z.x); double r=sqrt(z.x*z.x+z.y*z.y); int n=(int)fmax(3,fmin(oa,12)); double star_r=ob*(1.0f+oc*cos(n*ph)); double d=fabs(r-star_r); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 36: // Type 36
	{
		double r=sqrt(z.x*z.x+z.y*z.y); double ph=atan2(z.y,z.x); double lemnR=oa*oa*cos(2.0f*ph); double d=fabs(r*r-lemnR); aux.DE *= (1.0f + of*exp(-od*d*0.5f));
		break;
	}
	case 37: // Type 37
	{
		double r=sqrt(z.x*z.x+z.y*z.y); double ph=atan2(z.y,z.x); double rose_r=oa*sin(ob*ph); double d=fabs(r-fabs(rose_r)); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 38: // Type 38
	{
		double ph=atan2(z.y,z.x); double r=sqrt(z.x*z.x+z.y*z.y); double spiral_r=oa*exp(ob*ph); double d=fabs(r-spiral_r); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 39: // Type 39
	{
		double r=sqrt(z.x*z.x+z.y*z.y); double ph=atan2(z.y,z.x); double heart_r=oa*(1.0f-sin(ph)); double d=fabs(r-heart_r); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 40: // Type 40
	{
		double d1=sqrt(z.x*z.x+z.y*z.y)-oa; double d2=sqrt(z.y*z.y+z.z*z.z)-oa; double d3=sqrt(z.x*z.x+z.z*z.z)-oa; double d=fmin(fabs(d1),fmin(fabs(d2),fabs(d3))); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 41: // Type 41
	{
		double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double d1=fabs(r-oa); double d2=fabs(r-ob); aux.DE *= (1.0f + of*exp(-od*d1)*exp(-od*d2));
		break;
	}
	case 42: // Type 42
	{
		double r=sqrt(z.x*z.x+z.y*z.y); double d=r*r-(oa*z.x+ob*z.y); d=fabs(d)/fmax(r+1e-21, 1e-21); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 43: // Type 43
	{
		double ex=z.x*z.x/(oa*oa+1e-21); double ey=z.y*z.y/(ob*ob+1e-21); double d=fabs(ex+ey-1.0f)*sqrt(oa*oa+ob*ob); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 44: // Type 44
	{
		double r=sqrt(z.x*z.x+z.y*z.y); double t2=sqrt((r-oa)*(r-oa)+z.z*z.z); double d=fabs(t2-ob)+fabs(z.z)*oc; aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 45: // Type 45
	{
		double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double ph=atan2(z.y,z.x); double th=acos(z.z/fmax(r,1e-21)); double d=fabs(r-oa*(1.0f+ob*sin(oc*ph)*cos(od*th))); aux.DE *= (1.0f + of*exp(-d));
		break;
	}
	case 46: // Type 46
	{
		double d=fabs(z.x*z.x+z.y*z.y-oa*z.z*z.z); d=sqrt(d); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 47: // Type 47
	{
		double d=fabs(z.x*z.x/fmax(oa*oa,1e-21)+z.y*z.y/fmax(ob*ob,1e-21)-z.z*z.z/fmax(oc*oc,1e-21)-1.0f); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 48: // Type 48
	{
		double r=sqrt(z.x*z.x+z.y*z.y); double ph=atan2(z.y,z.x); double cyl_r=oa+ob*sin(oc*z.z)*cos(od*ph); double d=fabs(r-cyl_r); aux.DE *= (1.0f + of*exp(-d));
		break;
	}
	case 49: // Type 49
	{
		double d1=fabs(fmax(fabs(z.x),fabs(z.y))-oa); double d2=fabs(fmax(fabs(z.y),fabs(z.z))-oa); double d3=fabs(fmax(fabs(z.x),fabs(z.z))-oa); double d=fmin(d1,fmin(d2,d3)); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 50: // Type 50
	{
		double dx=fabs(fabs(z.x)-oa); double dy=fabs(fabs(z.y)-oa); double dz=fabs(fabs(z.z)-oa); double d=dx+dy+dz; aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 51: // Type 51
	{
		double d1=fabs(z.x); double d2=fabs(z.y); double d=fmin(d1,d2); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 52: // Type 52
	{
		double d1=fmin(fabs(z.x),fabs(z.y)); double d2=fabs(z.z); aux.DE *= (1.0f + of*exp(-od*(d1+d2*oa)));
		break;
	}
	case 53: // Type 53
	{
		double gx=fabs(z.x-oa*round(z.x/fmax(oa,1e-21))); double gy=fabs(z.y-ob*round(z.y/fmax(ob,1e-21))); double d=fmin(gx,gy); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 54: // Type 54
	{
		double gx=fabs(z.x-oa*round(z.x/fmax(oa,1e-21))); double gy=fabs(z.y-oa*round(z.y/fmax(oa,1e-21))); double gz=fabs(z.z-oa*round(z.z/fmax(oa,1e-21))); double d=fmin(gx,fmin(gy,gz)); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 55: // Type 55
	{
		double cs=cos(oa*M_PI/180.0f),sn=sin(oa*M_PI/180.0f); double rx=z.x*cs-z.y*sn; double ry=z.x*sn+z.y*cs; double d=fmin(fabs(rx),fabs(ry)); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 56: // Type 56
	{
		double ph=atan2(z.y,z.x); int n=(int)fmax(3,fmin(oa,16)); double d=sqrt(z.x*z.x+z.y*z.y)*fabs(sin(n*ph*0.5f)); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 57: // Type 57
	{
		double d1=fabs(z.x-z.y); double d2=fabs(z.x+z.y); double d=fmin(d1,d2)*0.7071f; aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 58: // Type 58
	{
		double gx=oa>0.001f?fabs(sin(z.x*M_PI/oa)):fabs(z.x); double gy=ob>0.001f?fabs(sin(z.y*M_PI/ob)):fabs(z.y); double d=gx*gy; aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 59: // Type 59
	{
		double d1=fmin(fabs(z.x-oa),fabs(z.x+oa)); double d2=fmin(fabs(z.y-ob),fabs(z.y+ob)); double d3=fmin(fabs(z.z-oc),fabs(z.z+oc)); double d=fmin(d1,fmin(d2,d3)); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 60: // Type 60
	{
		double r=sqrt(z.x*z.x+z.y*z.y); double ph=atan2(z.y,z.x); int n=(int)fmax(3,fmin(oa,16)); double seg=2.0f*M_PI/n; double sph=fmod(ph+M_PI+seg*0.5f,seg)-seg*0.5f; double d=r*fabs(sin(sph)); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 61: // Type 61
	{
		double d=fabs(z.x*z.x-z.y*z.y-oa*oa); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 62: // Type 62
	{
		double hx=z.x*2.0f/3.0f+z.y/3.0f; double hy=z.y*2.0f/sqrt(3.0f); double d=fmin(fabs(hx-round(hx)),fabs(hy-round(hy)))*oa; aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 63: // Type 63
	{
		double d=sin(z.x*oa*M_PI)*sin(z.y*ob*M_PI)*sin(z.z*oc*M_PI); aux.DE *= (1.0f + of*fabs(d));
		break;
	}
	case 64: // Type 64
	{
		double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double ph=atan2(z.y,z.x); double th=acos(z.z/fmax(r,1e-21)); double d=fabs(sin(oa*ph)*sin(ob*th))*r; aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 65: // Type 65
	{
		double gx=fabs(z.x-oa*round(z.x/fmax(oa,1e-21))); double gy=fabs(z.y-ob*round(z.y/fmax(ob,1e-21))); double d=sqrt(gx*gx+gy*gy); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 66: // Type 66
	{
		double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double w=exp(-oa*(double)i); aux.DE *= (1.0f + of*exp(-od*d)*w);
		break;
	}
	case 67: // Type 67
	{
		double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double phase=sin(ob*(double)i*M_PI/180.0f)*0.5f+0.5f; aux.DE *= (1.0f + of*exp(-od*d)*phase);
		break;
	}
	case 68: // Type 68
	{
		double d=sqrt((z.x-oa*sin(ob*i))*(z.x-oa*sin(ob*i))+(z.y-oa*cos(ob*i))*(z.y-oa*cos(ob*i))+z.z*z.z); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 69: // Type 69
	{
		double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double trap_r=oa+ob*(double)i; double ring=fabs(d-trap_r); aux.DE *= (1.0f + of*exp(-od*ring));
		break;
	}
	case 70: // Type 70
	{
		double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); if(d < oa) { aux.DE *= (1.0f + of*exp(-od*(oa-d))); }
		break;
	}
	case 71: // Type 71
	{
		double d=fabs(z.x)+fabs(z.y)+fabs(z.z); double w = (i%2==0) ? 1.0f : -0.5f; aux.DE *= (1.0f + of*w*exp(-od*d));
		break;
	}
	case 72: // Type 72
	{
		double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double v=sin(d*oa+ob*(double)i); aux.DE *= (1.0f + of*v*v);
		break;
	}
	case 73: // Type 73
	{
		double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double prevR=in.point.Length(); double dr=fabs(r-prevR); aux.DE *= (1.0f + of*exp(-od*dr));
		break;
	}
	case 74: // Type 74
	{
		double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double n=fmax(1.0f,oa*10.0f); double trap=fabs(d-round(d*n)/n)*n; aux.DE *= (1.0f + of*exp(-od*trap));
		break;
	}
	case 75: // Type 75
	{
		double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double v=1.0f/(1.0f+exp(-oa*(d-ob))); aux.DE *= (1.0f + of*(v-0.5f)*2.0f);
		break;
	}
	case 76: // Type 76
	{
		double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double decay=exp(-oa*d); double osc=sin(ob*d+oc*(double)i); aux.DE *= (1.0f + of*decay*osc);
		break;
	}
	case 77: // Type 77
	{
		double d=fabs(z.x*z.y)+fabs(z.y*z.z)+fabs(z.z*z.x); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 78: // Type 78
	{
		double d=z.x*z.x+z.y*z.y+z.z*z.z; double v=exp(-oa*d)*sin(ob*sqrt(d)); aux.DE *= (1.0f + of*v);
		break;
	}
	case 79: // Type 79
	{
		double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double ph=atan2(z.y,z.x); double d=fabs(r-oa)*fabs(sin(ob*ph)); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 80: // Type 80
	{
		double d=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double cs=cos(oa*(double)i*M_PI/180.0f); double sn=sin(oa*(double)i*M_PI/180.0f); double rd=fabs((z.x*cs-z.y*sn)); aux.DE *= (1.0f + of*exp(-od*rd));
		break;
	}
	case 81: // Type 81
	{
		double d=fabs(z.x*z.x+z.y*z.y-oa*oa*z.z); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 82: // Type 82
	{
		double r=sqrt(z.x*z.x+z.y*z.y); double ph=atan2(z.y,z.x); double d=fabs(r-oa*fabs(cos(ob*ph/2.0f))); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 83: // Type 83
	{
		double mx=fabs(z.x); double my=fabs(z.y); double mz=fabs(z.z); if(mx<my){double t=mx;mx=my;my=t;} if(mx<mz){double t=mx;mx=mz;mz=t;} double d=mx-oa; aux.DE *= (1.0f + of*exp(-od*fabs(d)));
		break;
	}
	case 84: // Type 84
	{
		double d1=sqrt(z.x*z.x+z.y*z.y)-oa; double d2=fabs(z.z)-ob; double d=sqrt(fmax(d1,0.0f)*fmax(d1,0.0f)+fmax(d2,0.0f)*fmax(d2,0.0f))+fmin(fmax(d1,d2),0.0f); aux.DE *= (1.0f + of*exp(-od*fabs(d)));
		break;
	}
	case 85: // Type 85
	{
		double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double ph=atan2(z.y,z.x); double th=acos(z.z/fmax(r,1e-21)); int nph=(int)fmax(2,oa*4); int nth=(int)fmax(2,ob*4); double dph=fabs(sin(nph*ph*0.5f)); double dth=fabs(sin(nth*th*0.5f)); double d=r*dph*dth; aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 86: // Type 86
	{
		double d=fabs(sin(z.x*oa)*sin(z.y*ob)*sin(z.z*oc)); aux.DE *= (1.0f + of*d);
		break;
	}
	case 87: // Type 87
	{
		double d1=sqrt(z.x*z.x+z.y*z.y+z.z*z.z)-oa; double d2=fmax(fabs(z.x),fmax(fabs(z.y),fabs(z.z)))-ob; double d=fmax(d1,-d2); aux.DE *= (1.0f + of*exp(-od*fabs(d)));
		break;
	}
	case 88: // Type 88
	{
		double r=sqrt(z.x*z.x+z.y*z.y); double d=sqrt((r-oa)*(r-oa)+z.z*z.z); double knot=fabs(d-ob*fabs(sin(oc*atan2(z.z,r-oa)))); aux.DE *= (1.0f + of*exp(-od*knot));
		break;
	}
	case 89: // Type 89
	{
		double d=pow(fabs(z.x),oa)+pow(fabs(z.y),oa)+pow(fabs(z.z),oa); d=pow(d,1.0f/fmax(oa,1e-21))-ob; aux.DE *= (1.0f + of*exp(-od*fabs(d)));
		break;
	}
	case 90: // Type 90
	{
		double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double th=atan2(z.y,z.x); double d=fabs(r-oa*(sin(ob*th)*sin(ob*th)+oc)); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 91: // Type 91
	{
		double d1=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double d2=sqrt((z.x-oa)*(z.x-oa)+(z.y-ob)*(z.y-ob)+(z.z-oc)*(z.z-oc)); double d=fabs(d1-d2); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 92: // Type 92
	{
		double d=fabs(z.x*z.y*z.z); d=pow(d,1.0f/3.0f); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 93: // Type 93
	{
		double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double ph=atan2(z.y,z.x); double clover=oa*fabs(sin(ob*ph)); double d=fabs(r-clover); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 94: // Type 94
	{
		double d1=fabs(z.x)-oa; double d2=fabs(z.y)-ob; double d3=fabs(z.z)-oc; double outside=sqrt(fmax(d1,0.0f)*fmax(d1,0.0f)+fmax(d2,0.0f)*fmax(d2,0.0f)+fmax(d3,0.0f)*fmax(d3,0.0f)); double inside=fmin(fmax(d1,fmax(d2,d3)),0.0f); double d=outside+inside; aux.DE *= (1.0f + of*exp(-od*fabs(d)));
		break;
	}
	case 95: // Type 95
	{
		double md=1e10; for(int k=0;k<(int)fmax(2,fmin(oa*4,8));k++){ double ang=k*2.0f*M_PI/fmax(oa*4,2); double cx=ob*cos(ang); double cy=ob*sin(ang); for(int j=0;j<(int)fmax(2,fmin(oc*4,8));j++){ double az=j*2.0f*M_PI/fmax(oc*4,2); double cz=od*sin(az); double d=(z.x-cx)*(z.x-cx)+(z.y-cy)*(z.y-cy)+(z.z-cz)*(z.z-cz); if(d<md)md=d; }} aux.DE *= (1.0f + of*exp(-sqrt(md)));
		break;
	}
	case 96: // Type 96
	{
		double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double d=sin(r*oa)*sin(z.x*ob)*sin(z.y*oc); aux.DE *= (1.0f + of*fabs(d));
		break;
	}
	case 97: // Type 97
	{
		double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double ph=atan2(z.y,z.x); double th=acos(z.z/fmax(r,1e-21)); double Y=sin(th)*cos(oa*ph); double d=fabs(r-ob*(1.0f+oc*Y)); aux.DE *= (1.0f + of*exp(-od*d));
		break;
	}
	case 98: // Type 98
	{
		double d=0; for(int k=1;k<=(int)fmax(1,fmin(oa*4,6));k++){ double rk=ob*(double)k; double dk=fabs(sqrt(z.x*z.x+z.y*z.y+z.z*z.z)-rk); d+=exp(-oc*dk); } aux.DE *= (1.0f + of*d/(oa*4+1e-21));
		break;
	}
	case 99: // Type 99
	{
		double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double d=fabs(r-oa); double v=exp(-ob*d)*cos(oc*d); z.x += of*v*z.x/fmax(r,1e-21)*0.01f; z.y += of*v*z.y/fmax(r,1e-21)*0.01f; z.z += of*v*z.z/fmax(r,1e-21)*0.01f; aux.DE *= (1.0f + of*fabs(v)*0.1f);
		break;
	}
	case 100: // Type 100
	{
		double d1=sqrt(z.x*z.x+z.y*z.y+z.z*z.z)-oa; double d2=sqrt((z.x-ob)*(z.x-ob)+z.y*z.y+z.z*z.z)-oc; double d=fmin(fabs(d1),fabs(d2)); double blend=sin(z.x*od+z.y*od)*0.5f+0.5f; aux.DE *= (1.0f + of*(d1*(1.0f-blend)+d2*blend)*exp(-d));
		break;
	}
	default: break;
}