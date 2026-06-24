// Auto-generated mutation switch for system: sm
// Target: GPU
// Generated mutations: 100
switch (mut->smType)
{
	case 1: // Type 1
	{
		double branch = 2.0f + floor(3.0f*sin((double)i*ta*0.1f)); aux.DE *= fmax(branch*tb, 0.01f);
		break;
	}
	case 2: // Type 2
	{
		double bx=fmax(ta,1.0f),by=fmax(tb,1.0f),bz=fmax(tc,1.0f); aux.DE *= fmax(fmax(bx,by),bz)*sf;
		break;
	}
	case 3: // Type 3
	{
		double angle = (double)i * 2.39996322972865332f * ta; double cosA=cos(angle),sinA=sin(angle); double nx=z.x*cosA-z.y*sinA; z.y=z.x*sinA+z.y*cosA; z.x=nx;
		break;
	}
	case 4: // Type 4
	{
		double jm = sin(z.x*ta)*cos(z.y*tb); double r_ratio = 1.0f + sf*0.3f*jm; aux.DE *= r_ratio;
		break;
	}
	case 5: // Type 5
	{
		double h = sin(z.x*ta*127.1f+z.y*ta*311.7f+z.z*ta*74.7f)*43758.5453f; h=h-floor(h); aux.DE *= (1.0f + sf*(h*2.0f-1.0f)*tb);
		break;
	}
	case 6: // Type 6
	{
		double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double d1 = r - ta; double d2 = r - tb; aux.DE *= (1.0f + sf*exp(-fmin(d1*d1,d2*d2)*tc));
		break;
	}
	case 7: // Type 7
	{
		double w = fabs(ta)+0.01f; double wd = w*sin(z.x*tb)*cos(z.y*tc); aux.DE *= (1.0f + sf*wd*td);
		break;
	}
	case 8: // Type 8
	{
		double ax=fmax(fabs(ta),0.01f),ay=fmax(fabs(tb),0.01f),az=fmax(fabs(tc),0.01f); double ell = sqrt((z.x/ax)*(z.x/ax)+(z.y/ay)*(z.y/ay)+(z.z/az)*(z.z/az))-1.0f; aux.DE *= (1.0f + sf*exp(-ell*ell*td));
		break;
	}
	case 9: // Type 9
	{
		double r2d = sqrt(z.x*z.x+z.y*z.y); double R=fabs(ta)+0.1f,r=fabs(tb)+0.01f; double td2 = (r2d-R)*(r2d-R)+z.z*z.z-r*r; aux.DE *= (1.0f + sf*exp(-fabs(td2)*tc));
		break;
	}
	case 10: // Type 10
	{
		double px=z.x,py=z.y,pz=z.z; double seg_d=fabs(pz)-fabs(ta); double cap_d=sqrt(px*px+py*py+fmax(seg_d,0.0f)*fmax(seg_d,0.0f))-fabs(tb); aux.DE *= (1.0f + sf*exp(-cap_d*cap_d*tc));
		break;
	}
	case 11: // Type 11
	{
		double theta=atan2(z.y,z.x); double phi2=acos(z.z/fmax(sqrt(z.x*z.x+z.y*z.y+z.z*z.z),1e-21)); double m=fmax(ta,1.0f); double sf_r=pow(fmax(pow(fabs(cos(m*theta/4.0f)),tc)+pow(fabs(sin(m*theta/4.0f)),tc),1e-21),-1.0f/fmax(tb,0.1f)); double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE *= (1.0f + sf*exp(-fabs(r-sf_r*td)*5.0f));
		break;
	}
	case 12: // Type 12
	{
		double jx=z.x*z.x-z.y*z.y+ta; double jy=2.0f*z.x*z.y+tb; z.x=jx; z.y=jy; aux.DE *= 2.0f*sqrt(jx*jx+jy*jy);
		break;
	}
	case 13: // Type 13
	{
		double mx=z.x*z.x-z.y*z.y+z.x; double my=2.0f*z.x*z.y+z.y; z.x=mx; z.y=my; aux.DE *= 2.0f*sqrt(mx*mx+my*my);
		break;
	}
	case 14: // Type 14
	{
		double a1=ta*M_PI/180.0f; double a2=tb*M_PI/180.0f; double ca1=cos(a1),sa1=sin(a1); double newx=z.x+z.x*ca1-z.y*sa1; double newy=z.y+z.x*sa1+z.y*ca1; z.x=newx*0.5f; z.y=newy*0.5f; z.z*=tc; aux.DE *= fabs(tc);
		break;
	}
	case 15: // Type 15
	{
		double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double koch_amp = ta*sin(r*tb*10.0f); aux.DE *= (1.0f + sf*koch_amp*koch_amp);
		break;
	}
	case 16: // Type 16
	{
		double scale4 = fabs(ta)+1.0f; if(z.x+z.y<0.0f){double t=z.x;z.x=-z.y;z.y=-t;} if(z.x+z.z<0.0f){double t=z.x;z.x=-z.z;z.z=-t;} if(z.y+z.z<0.0f){double t=z.y;z.y=-z.z;z.z=-t;} z = z*scale4 - CVector4(1,1,1,0)*(scale4-1.0f)*tb; aux.DE = aux.DE*scale4+1.0f;
		break;
	}
	case 17: // Type 17
	{
		double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); if(r<1e-21)r=1e-21; double mde=ta*ta/r/r; z*=mde; aux.DE*=mde;
		break;
	}
	case 18: // Type 18
	{
		double h=sin(z.x*ta*12.9898f+z.y*tb*78.233f+z.z*tc*45.164f)*43758.5453f; h=h-floor(h); z.x+=h*td*0.1f; z.y+=(1.0f-h)*td*0.1f;
		break;
	}
	case 19: // Type 19
	{
		double min_dist=fabs(ta)+0.1f; double h=sin(z.x*12.9898f+z.y*78.233f)*43758.5453f; h=h-floor(h); z.x=floor(z.x/min_dist+h)*min_dist; z.y=floor(z.y/min_dist+h)*min_dist;
		break;
	}
	case 20: // Type 20
	{
		double h=sin(z.x*12.9898f+z.y*78.233f+z.z*45.164f)*43758.5453f; h=fabs(h-floor(h)); z.x+=h*ta*0.1f; z.y+=(1.0f-h)*tb*0.1f; z.z+=fabs(sin(h*tc))*td*0.1f;
		break;
	}
	case 21: // Type 21
	{
		double theta = (double)i * 2.39996322972865332f; double r = sqrt((double)i+0.5f)*ta; z.x += r*cos(theta)*sf*0.1f; z.y += r*sin(theta)*sf*0.1f;
		break;
	}
	case 22: // Type 22
	{
		double phi3 = 1.6180339887f; double r_n = ta/pow(phi3, (double)i); aux.DE *= 1.0f/phi3; z *= r_n/fmax(sqrt(z.x*z.x+z.y*z.y+z.z*z.z),0.01f);
		break;
	}
	case 23: // Type 23
	{
		double r_n = ta * exp(-(double)i * fabs(tb)); aux.DE *= exp(-fabs(tb)); z *= r_n/fmax(sqrt(z.x*z.x+z.y*z.y+z.z*z.z),0.01f);
		break;
	}
	case 24: // Type 24
	{
		double n = fmax((double)i+1.0f, 1.0f); double r_n = ta / (1.0f + log(n)*tb); aux.DE *= 1.0f/(1.0f+log(n)*tb); z *= r_n/fmax(sqrt(z.x*z.x+z.y*z.y+z.z*z.z),0.01f);
		break;
	}
	case 25: // Type 25
	{
		double n = fmax((double)i+1.0f, 1.0f); double p = fmax(fabs(ta), 0.1f); aux.DE *= 1.0f/pow(n,p);
		break;
	}
	case 26: // Type 26
	{
		double sc = 3.0f + 0.5f*sin((double)i*ta); z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 27: // Type 27
	{
		double sx=fmax(ta,1.0f),sy=fmax(tb,1.0f),sz=fmax(tc,1.0f); z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z.x=z.x*sx-(sx-1.0f); z.y=z.y*sy-(sy-1.0f); z.z=z.z*sz-(sz-1.0f); aux.DE=aux.DE*fmax(fmax(sx,sy),sz)+1.0f;
		break;
	}
	case 28: // Type 28
	{
		double h=sin(z.x*ta*127.1f+z.y*ta*311.7f+z.z*ta*74.7f)*43758.5453f; h=h-floor(h); double sc=3.0f; z=fabs(z)+CVector4(h*tb,h*tb,h*tb,0)*0.1f; if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 29: // Type 29
	{
		double angle=ta*M_PI/180.0f; double ca=cos(angle),sa=sin(angle); double nx=z.x*ca-z.y*sa; double ny=z.x*sa+z.y*ca; z.x=fabs(nx);z.y=fabs(ny);z.z=fabs(z.z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} double sc=3.0f; z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 30: // Type 30
	{
		double eps=fmax(fabs(ta),0.01f); double sc=3.0f; z.x=fabs(z.x);z.y=fabs(z.y);z.z=fabs(z.z); double t; if(z.x<z.y){t=z.x+(z.y-z.x)*0.5f*(1.0f+tanh((z.y-z.x)/eps));z.y=z.y-(z.y-z.x)*0.5f*(1.0f+tanh((z.y-z.x)/eps));z.x=z.y;z.y=t;} if(z.x<z.z){t=z.x;z.x=z.z;z.z=t;} if(z.y<z.z){t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 31: // Type 31
	{
		double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f)+CVector4(ta,tb,tc,0); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 32: // Type 32
	{
		double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); z.x+=aux.const_c.x*ta; z.y+=aux.const_c.y*ta; z.z+=aux.const_c.z*ta; aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 33: // Type 33
	{
		double sc=3.0f; double period=fmax(fabs(ta),0.1f); z=CVector4(fmod(z.x+100.0f*period,period)-period*0.5f, fmod(z.y+100.0f*period,period)-period*0.5f, fmod(z.z+100.0f*period,period)-period*0.5f, z.w); z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 34: // Type 34
	{
		double sc=3.0f; double r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<1e-21)r2=1e-21; double inv=ta*ta/r2; z*=inv; aux.DE*=inv; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 35: // Type 35
	{
		double lim=fabs(ta)+0.5f; if(z.x>lim)z.x=2.0f*lim-z.x; if(z.x<-lim)z.x=-2.0f*lim-z.x; if(z.y>lim)z.y=2.0f*lim-z.y; if(z.y<-lim)z.y=-2.0f*lim-z.y; if(z.z>lim)z.z=2.0f*lim-z.z; if(z.z<-lim)z.z=-2.0f*lim-z.z; double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 36: // Type 36
	{
		double r2=z.x*z.x+z.y*z.y+z.z*z.z; double minR2=fabs(ta)*fabs(ta); double fixedR2=1.0f; double m; if(r2<minR2)m=fixedR2/minR2; else if(r2<fixedR2)m=fixedR2/r2; else m=1.0f; z*=m; aux.DE*=m; double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 37: // Type 37
	{
		int n=(int)fmax(ta,2.0f); double angle=M_PI/n; for(int k=0;k<n;k++){double a=k*2.0f*angle; double d=z.x*cos(a)+z.y*sin(a); if(d<0.0f){z.x-=2.0f*d*cos(a);z.y-=2.0f*d*sin(a);}} double sc=3.0f; z=z*sc-CVector4(1,1,1,0)*(sc-1.0f)*tb; aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 38: // Type 38
	{
		z.x=fabs(z.x);z.y=-fabs(z.y);z.z=fabs(z.z); double sc=3.0f; if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 39: // Type 39
	{
		double twist_k=ta*0.01f; double angle=twist_k*(double)i; double ca=cos(angle),sa=sin(angle); double nx=z.x*ca-z.y*sa; z.y=z.x*sa+z.y*ca; z.x=nx; double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 40: // Type 40
	{
		double bend=ta*0.001f; z.z+=bend*(z.x*z.x+z.y*z.y); double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 41: // Type 41
	{
		double shear=ta*0.1f; z.x+=shear*z.y; double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 42: // Type 42
	{
		double taper=ta*0.01f; z.x*=(1.0f-taper*z.z); z.y*=(1.0f-taper*z.z); double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 43: // Type 43
	{
		double period=fmax(fabs(ta),0.1f); z=CVector4(fmod(z.x+100.0f*period,period)-period*0.5f, fmod(z.y+100.0f*period,period)-period*0.5f, fmod(z.z+100.0f*period,period)-period*0.5f, z.w); double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 44: // Type 44
	{
		double sc1=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc1-CVector4(1,1,1,0)*(sc1-1.0f); aux.DE=aux.DE*sc1+1.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc1-CVector4(1,1,1,0)*(sc1-1.0f); aux.DE=aux.DE*sc1+1.0f;
		break;
	}
	case 45: // Type 45
	{
		double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*fabs(sc)+1.0f; double surfScale=fabs(ta)+0.5f; z.x=fabs(z.x+surfScale)-fabs(z.x-surfScale)-z.x; z.y=fabs(z.y+surfScale)-fabs(z.y-surfScale)-z.y;
		break;
	}
	case 46: // Type 46
	{
		double sc=3.0f; double r2=z.x*z.x+z.y*z.y+z.z*z.z; double minR2=fabs(ta)*fabs(ta); double fixedR2=1.0f; double m; if(r2<minR2)m=fixedR2/minR2; else if(r2<fixedR2)m=fixedR2/r2; else m=1.0f; z*=m; aux.DE=aux.DE*m; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 47: // Type 47
	{
		double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; double k_angle=ta*M_PI/180.0f; CVector3 nv(cos(k_angle),sin(k_angle),0); CVector3 zv=z.GetXYZ(); double dot=zv.Dot(nv); if(dot<0){zv=zv-nv*(2.0f*dot); z=CVector4(zv,z.w);}
		break;
	}
	case 48: // Type 48
	{
		double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; z+=CVector4(aux.const_c.x*ta,aux.const_c.y*ta,aux.const_c.z*ta,0)*tb;
		break;
	}
	case 49: // Type 49
	{
		double sc=3.0f+0.1f*sin((double)i*ta); z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*fabs(sc)+1.0f; z=CVector4(0.9f*z.x+0.1f*ta,0.9f*z.y+0.1f*tb,0.9f*z.z+0.1f*tc,z.w);
		break;
	}
	case 50: // Type 50
	{
		double h1=sin(ta*z.x+tb*z.y+tc*z.z); double h2=sin(td*h1+ta*(double)i*0.1f); double sc=3.0f+sf*h2*0.1f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*fabs(sc)+1.0f;
		break;
	}
	case 51: // Type 51
	{
		double sc=3.0f; CVector4 zz=fabs(z); double vals[4]={zz.x,zz.y,zz.z,zz.w}; for(int a=0;a<4;a++)for(int b=a+1;b<4;b++){if(vals[a]<vals[b]){double t=vals[a];vals[a]=vals[b];vals[b]=t;}} z=CVector4(vals[0],vals[1],vals[2],vals[3])*sc-CVector4(1,1,1,1)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 52: // Type 52
	{
		double sc=3.0f; double v[5]={fabs(z.x),fabs(z.y),fabs(z.z),fabs(z.w),fabs(sin(z.x+z.y))}; for(int a=0;a<5;a++)for(int b=a+1;b<5;b++){if(v[a]<v[b]){double t=v[a];v[a]=v[b];v[b]=t;}} z=CVector4(v[0],v[1],v[2],v[3])*sc-CVector4(1,1,1,1)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 53: // Type 53
	{
		double sc=3.0f; z.w=ta; CVector4 zz=fabs(z); double vals[4]={zz.x,zz.y,zz.z,zz.w}; for(int a=0;a<4;a++)for(int b=a+1;b<4;b++){if(vals[a]<vals[b]){double t=vals[a];vals[a]=vals[b];vals[b]=t;}} z=CVector4(vals[0],vals[1],vals[2],vals[3])*sc-CVector4(1,1,1,1)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 54: // Type 54
	{
		double angle4d=ta*M_PI/180.0f*(double)i; double ca=cos(angle4d),sa=sin(angle4d); double nx=z.x*ca-z.w*sa; z.w=z.x*sa+z.w*ca; z.x=nx; double sc=3.0f; CVector4 zz=fabs(z); double vals[4]={zz.x,zz.y,zz.z,zz.w}; for(int a=0;a<4;a++)for(int b=a+1;b<4;b++){if(vals[a]<vals[b]){double t=vals[a];vals[a]=vals[b];vals[b]=t;}} z=CVector4(vals[0],vals[1],vals[2],vals[3])*sc-CVector4(1,1,1,1)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 55: // Type 55
	{
		double sc=3.0f; CVector4 zz=fabs(z); double vals[4]={zz.x,zz.y,zz.z,zz.w}; for(int a=0;a<4;a++)for(int b=a+1;b<4;b++){if(vals[a]<vals[b]){double t=vals[a];vals[a]=vals[b];vals[b]=t;}} z=CVector4(vals[0],vals[1],vals[2],vals[3])*sc-CVector4(1,1,1,1)*(sc-1.0f)+CVector4(ta,tb,tc,td); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 56: // Type 56
	{
		double sc=3.0f; double qn=sqrt(z.x*z.x+z.y*z.y+z.z*z.z+z.w*z.w); z.w=qn*ta; CVector4 zz=fabs(z); double vals[4]={zz.x,zz.y,zz.z,zz.w}; for(int a=0;a<4;a++)for(int b=a+1;b<4;b++){if(vals[a]<vals[b]){double t=vals[a];vals[a]=vals[b];vals[b]=t;}} z=CVector4(vals[0],vals[1],vals[2],vals[3])*sc-CVector4(1,1,1,1)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 57: // Type 57
	{
		double sc=3.0f; double qr=z.x,qi=z.y,qj=z.z,qk=z.w; z.x=qr*qi-qj*qk; z.y=qr*qj+qi*qk; z.z=qr*qk-qi*qj; z.w=qr*qr-qi*qi-qj*qj-qk*qk; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,1)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 58: // Type 58
	{
		double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z+z.w*z.w); double d=tanh(fmin(r*ta,10.0f)); CVector4 unit=z/fmax(r,1e-21); z=unit*d; double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); double ch=cosh(fmin(r*ta,20.0f)); aux.DE=aux.DE*sc/(ch*ch)+1.0f;
		break;
	}
	case 59: // Type 59
	{
		double r4=sqrt(z.x*z.x+z.y*z.y+z.z*z.z+z.w*z.w); if(r4>1e-21){z/=r4;} double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 60: // Type 60
	{
		double r2d=sqrt(z.x*z.x+z.y*z.y); double theta=atan2(z.y,z.x); z.x=r2d; z.y=theta*ta; double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); z.x=z.x*cos(z.y/fmax(ta,0.01f))-z.z*sin(z.y/fmax(ta,0.01f)); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 61: // Type 61
	{
		double R=fabs(ta)+0.5f; double r2d=sqrt(z.x*z.x+z.y*z.y); z.x=r2d-R; double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 62: // Type 62
	{
		double theta4=ta*M_PI/180.0f; double ca=cos(theta4),sa=sin(theta4); double nx=z.z*ca-z.w*sa; z.w=z.z*sa+z.w*ca; z.z=nx; double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 63: // Type 63
	{
		double golden=2.39996322972865332f; double theta=(double)i*golden*ta; z.x+=cos(theta)*tb*0.01f; z.y+=sin(theta)*tb*0.01f; z.z+=cos(theta*0.5f)*tc*0.01f; z.w=sin(theta*0.5f)*td*0.01f; double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 64: // Type 64
	{
		double D=2.7268f; double sc=pow(3.0f,D/3.0f); z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 65: // Type 65
	{
		double h=sin(z.x*12.9898f+z.y*78.233f+z.z*45.164f+(double)i*ta)*43758.5453f; h=h-floor(h); double sc=3.0f; z=fabs(z); double vals[3]={z.x,z.y,z.z}; if(h>0.5f){if(vals[0]<vals[1]){double t=vals[0];vals[0]=vals[1];vals[1]=t;}} if(h>0.25f){if(vals[0]<vals[2]){double t=vals[0];vals[0]=vals[2];vals[2]=t;}} if(h>0.75f){if(vals[1]<vals[2]){double t=vals[1];vals[1]=vals[2];vals[2]=t;}} z=CVector4(vals[0],vals[1],vals[2],z.w)*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 66: // Type 66
	{
		double sc=3.0f; double sq32=0.866025f; z=fabs(z); double d=z.x*sq32+z.y*0.5f; if(d<0.0f){z.x-=2.0f*d*sq32;z.y-=d;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 67: // Type 67
	{
		double sc=3.0f; double a60=M_PI/3.0f; for(int k=0;k<6;k++){double a=k*a60; double d=z.x*cos(a)+z.y*sin(a); if(d<0.0f){z.x-=2.0f*d*cos(a);z.y-=2.0f*d*sin(a);}} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 68: // Type 68
	{
		double sc=3.0f; double a45=M_PI/4.0f; for(int k=0;k<8;k++){double a=k*a45; double d=z.x*cos(a)+z.y*sin(a); if(d<0.0f){z.x-=2.0f*d*cos(a);z.y-=2.0f*d*sin(a);}} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 69: // Type 69
	{
		double sc=3.0f; double a30=M_PI/6.0f; for(int k=0;k<12;k++){double a=k*a30; double d=z.x*cos(a)+z.y*sin(a); if(d<0.0f){z.x-=2.0f*d*cos(a);z.y-=2.0f*d*sin(a);}} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 70: // Type 70
	{
		double sc=3.0f; double a72=M_PI*2.0f/5.0f; for(int k=0;k<5;k++){double a=k*a72; double d=z.x*cos(a)+z.y*sin(a); if(d<0.0f){z.x-=2.0f*d*cos(a);z.y-=2.0f*d*sin(a);}} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 71: // Type 71
	{
		double sc=3.0f; double a60=M_PI/3.0f; for(int k=0;k<6;k++){double a=k*a60; double d=z.x*cos(a)+z.y*sin(a); if(d<0.0f){z.x-=2.0f*d*cos(a);z.y-=2.0f*d*sin(a);}} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 72: // Type 72
	{
		double sc=3.0f; double a45=M_PI/4.0f; for(int k=0;k<8;k++){double a=k*a45; double d=z.x*cos(a)+z.y*sin(a); if(d<0.0f){z.x-=2.0f*d*cos(a);z.y-=2.0f*d*sin(a);}} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 73: // Type 73
	{
		double sc=3.0f; double a36=M_PI/5.0f; for(int k=0;k<10;k++){double a=k*a36; double d=z.x*cos(a)+z.y*sin(a); if(d<0.0f){z.x-=2.0f*d*cos(a);z.y-=2.0f*d*sin(a);}} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 74: // Type 74
	{
		int n=(int)fmax(ta,3.0f); double sc=3.0f; double aStep=M_PI*2.0f/n; for(int k=0;k<n&&k<16;k++){double a=k*aStep; double d=z.x*cos(a)+z.y*sin(a); if(d<0.0f){z.x-=2.0f*d*cos(a);z.y-=2.0f*d*sin(a);}} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f)*tb; aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 75: // Type 75
	{
		double sc=3.0f; int n=(int)fmax(ta,3.0f); double amp=fabs(tb); double theta=atan2(z.y,z.x); double r2d=sqrt(z.x*z.x+z.y*z.y); double star_r=r2d*(1.0f+amp*cos(n*theta)); z.x=star_r*cos(theta); z.y=star_r*sin(theta); z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 76: // Type 76
	{
		double sc=3.0f; double theta=atan2(z.y,z.x); double r2d=sqrt(z.x*z.x+z.y*z.y); double heart_r=r2d*(1.0f-sin(theta)*fabs(ta)); z.x=heart_r*cos(theta); z.y=heart_r*sin(theta); z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 77: // Type 77
	{
		double spiral_a=ta*0.01f*(double)i; double ca=cos(spiral_a),sa=sin(spiral_a); double nx=z.x*ca-z.y*sa; z.y=z.x*sa+z.y*ca; z.x=nx; double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 78: // Type 78
	{
		double r2=z.x*z.x+z.y*z.y; z.z+=ta*0.001f*r2; double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 79: // Type 79
	{
		double r2d=sqrt(z.x*z.x+z.y*z.y); double taper_w=1.0f-ta*0.01f*fabs(r2d); z.x*=taper_w; z.y*=taper_w; double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 80: // Type 80
	{
		double twist_a=ta*0.01f*sqrt(z.x*z.x+z.y*z.y); double ca=cos(twist_a),sa=sin(twist_a); double nx=z.x*ca-z.y*sa; z.y=z.x*sa+z.y*ca; z.x=nx; double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 81: // Type 81
	{
		double eps=fmax(fabs(ta),0.01f); double sc=3.0f; z=fabs(z); double t; if(z.x<z.y){double blend=0.5f+0.5f*tanh((z.y-z.x)/eps);t=z.x*(1.0f-blend)+z.y*blend;z.y=z.y*(1.0f-blend)+z.x*blend;z.x=t;} if(z.x<z.z){t=z.x;z.x=z.z;z.z=t;} if(z.y<z.z){t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 82: // Type 82
	{
		double h=sin(z.x*ta*127.1f+z.y*ta*311.7f+z.z*ta*74.7f)*43758.5453f; h=h-floor(h); z+=CVector4(h,1.0f-h,h*0.5f,0)*tb*0.01f; double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 83: // Type 83
	{
		double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f)+CVector4(ta,tb,tc,0); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 84: // Type 84
	{
		double period=fmax(fabs(ta),0.1f); z=CVector4(fmod(fabs(z.x)+100.0f*period,period)-period*0.5f, fmod(fabs(z.y)+100.0f*period,period)-period*0.5f, fmod(fabs(z.z)+100.0f*period,period)-period*0.5f, z.w); double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 85: // Type 85
	{
		double r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<1e-21)r2=1e-21; double inv=ta*ta/r2; z*=inv; aux.DE*=inv; double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 86: // Type 86
	{
		double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); aux.DE*=(1.0f+sf*exp(-r*ta)*tb);
		break;
	}
	case 87: // Type 87
	{
		double sc=3.0f; if(z.x+z.y<0.0f){double t=z.x;z.x=-z.y;z.y=-t;} if(z.x+z.z<0.0f){double t=z.x;z.x=-z.z;z.z=-t;} if(z.y+z.z<0.0f){double t=z.y;z.y=-z.z;z.z=-t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f)*ta; aux.DE=aux.DE*sc+1.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 88: // Type 88
	{
		double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; double koch_scale=2.0f*ta; z.x=fabs(z.x)-koch_scale*0.5f; z.y=fabs(z.y)-koch_scale*0.5f;
		break;
	}
	case 89: // Type 89
	{
		double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; if(z.x>0)z.x=-(z.x-1.0f);
		break;
	}
	case 90: // Type 90
	{
		double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; double fern_angle=ta*M_PI/180.0f; double ca=cos(fern_angle),sa=sin(fern_angle); double nx=z.x*ca-z.z*sa; z.z=z.x*sa+z.z*ca; z.x=nx; z*=0.85f*tb; aux.DE*=0.85f*fabs(tb);
		break;
	}
	case 91: // Type 91
	{
		double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f; double shell=fabs(r-ta)-tb; aux.DE*=(1.0f+sf*exp(-shell*shell*tc));
		break;
	}
	case 92: // Type 92
	{
		double period=fmax(fabs(ta),0.1f); z=CVector4(fmod(z.x+100.0f*period,period)-period*0.5f, fmod(z.y+100.0f*period,period)-period*0.5f, fmod(z.z+100.0f*period,period)-period*0.5f, z.w); double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 93: // Type 93
	{
		double r2=z.x*z.x+z.y*z.y+z.z*z.z; if(r2<1e-21)r2=1e-21; double inv=ta*ta/r2; z*=inv; aux.DE*=inv; double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 94: // Type 94
	{
		double clip=fabs(ta); z.x=fmin(fmax(z.x,-clip),clip); z.y=fmin(fmax(z.y,-clip),clip); z.z=fmin(fmax(z.z,-clip),clip); double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 95: // Type 95
	{
		double lim=fabs(ta)+0.5f; if(z.x>lim)z.x=2.0f*lim-z.x; if(z.x<-lim)z.x=-2.0f*lim-z.x; if(z.y>lim)z.y=2.0f*lim-z.y; if(z.y<-lim)z.y=-2.0f*lim-z.y; if(z.z>lim)z.z=2.0f*lim-z.z; if(z.z<-lim)z.z=-2.0f*lim-z.z; double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 96: // Type 96
	{
		double r2=z.x*z.x+z.y*z.y+z.z*z.z; double minR2=fabs(ta)*fabs(ta); double fixedR2=1.0f; double m; if(r2<minR2)m=fixedR2/minR2; else if(r2<fixedR2)m=fixedR2/r2; else m=1.0f; z*=m; aux.DE*=m; double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 97: // Type 97
	{
		double angle=ta*M_PI/180.0f*(double)i; double ca=cos(angle),sa=sin(angle); double nx=z.x*ca-z.y*sa; z.y=z.x*sa+z.y*ca; z.x=nx; double sc=3.0f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+1.0f;
		break;
	}
	case 98: // Type 98
	{
		double sc=3.0f*(1.0f+sf*0.1f*sin((double)i*ta)); z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*fabs(sc)+1.0f;
		break;
	}
	case 99: // Type 99
	{
		double sc=3.0f; double offset=fabs(ta); z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*sc+offset;
		break;
	}
	case 100: // Type 100
	{
		double h1=sin(ta*z.x+tb*z.y+tc*z.z); double h2=sin(td*h1+ta*(double)i*0.1f); double sc=3.0f+sf*h2*0.05f; z=fabs(z); if(z.x-z.y<0.0f){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0.0f){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0.0f){double t=z.y;z.y=z.z;z.z=t;} z=z*sc-CVector4(1,1,1,0)*(sc-1.0f); aux.DE=aux.DE*fabs(sc)+1.0f;
		break;
	}
	default: break;
}