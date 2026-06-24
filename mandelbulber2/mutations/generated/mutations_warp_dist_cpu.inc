// Auto-generated mutation switch for system: warp_dist
// Target: CPU
// Generated mutations: 100
switch (mut.warpDistType)
{
	case 1: // Type 1
	{
		z.x += wf*wam*sin(wfq*zy + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq*cos(wfq*zy + wph)));
		break;
	}
	case 2: // Type 2
	{
		z.y += wf*wam*sin(wfq*zz2 + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq*cos(wfq*zz2 + wph)));
		break;
	}
	case 3: // Type 3
	{
		z.z += wf*wam*sin(wfq*zx + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq*cos(wfq*zx + wph)));
		break;
	}
	case 4: // Type 4
	{
		z.x += wf*wam*sin(wfq*zy + wph); z.y += wf*wam*sin(wfq*zz2 + wph); z.z += wf*wam*sin(wfq*zx + wph); aux.DE *= (1.0 + 3.0*fabs(wf*wam*wfq));
		break;
	}
	case 5: // Type 5
	{
		z.x += wf*wam*cos(wfq*zy + wph)*sin(wfq*zz2); aux.DE *= (1.0 + fabs(wf*wam*wfq));
		break;
	}
	case 6: // Type 6
	{
		double ph = atan2(zy, zx); z.x += wf*wam*sin(wfq*ph + wph); z.y += wf*wam*cos(wfq*ph + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq));
		break;
	}
	case 7: // Type 7
	{
		double ph = atan2(zy, zx); double th = acos(zz2/r); z.x += wf*wam*sin(wfq*th + wph)*cos(ph); z.y += wf*wam*sin(wfq*th + wph)*sin(ph); z.z += wf*wam*cos(wfq*th + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq));
		break;
	}
	case 8: // Type 8
	{
		z.x += wf*wam*sin(wfq*zy + wph)*cos(wfq*zz2); z.y += wf*wam*sin(wfq*zz2 + wph)*cos(wfq*zx); z.z += wf*wam*sin(wfq*zx + wph)*cos(wfq*zy); aux.DE *= (1.0 + 3.0*fabs(wf*wam*wfq));
		break;
	}
	case 9: // Type 9
	{
		z.x += wf*wam*sin(wfq*zx + wph); z.y += wf*wb*sin(wfq*zy + wph); z.z += wf*wc*sin(wfq*zz2 + wph); aux.DE *= (1.0 + fabs(wf*(wam+wb+wc)*wfq/3.0));
		break;
	}
	case 10: // Type 10
	{
		double d = wf*wam*sin(wfq*r + wph); z.x += d*zx/r; z.y += d*zy/r; z.z += d*zz2/r; aux.DE *= (1.0 + fabs(wf*wam*wfq));
		break;
	}
	case 11: // Type 11
	{
		z.x += wf*wam*sin(wfq*sin(wa*zy) + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq));
		break;
	}
	case 12: // Type 12
	{
		z.y += wf*wam*sin(wfq*cos(wa*zz2) + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq));
		break;
	}
	case 13: // Type 13
	{
		z.z += wf*wam*cos(wfq*sin(wa*zx) + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq));
		break;
	}
	case 14: // Type 14
	{
		double d1 = sin(wfq*zx+wph); double d2 = sin(wa*zy+wb); z.x += wf*wam*sin(wfq*d1+d2); z.y += wf*wam*cos(wa*d1-d2); aux.DE *= (1.0 + 2.0*fabs(wf*wam*wfq));
		break;
	}
	case 15: // Type 15
	{
		z.x += wf*wam*sin(wfq*(zx*zy) + wph); z.y += wf*wam*cos(wfq*(zy*zz2) + wph); z.z += wf*wam*sin(wfq*(zz2*zx) + wph); aux.DE *= (1.0 + 3.0*fabs(wf*wam*wfq));
		break;
	}
	case 16: // Type 16
	{
		double n1 = sin(wfq*zx+wa*zy); double n2 = sin(wa*zy+wb*zz2); z.x += wf*wam*sin(wfq*n1+wph); z.y += wf*wam*sin(wfq*n2+wph); aux.DE *= (1.0 + 2.0*fabs(wf*wam*wfq));
		break;
	}
	case 17: // Type 17
	{
		double n1 = cos(wfq*zx)*sin(wa*zy); double n2 = cos(wa*zy)*sin(wb*zz2); double n3 = cos(wb*zz2)*sin(wfq*zx); z.x += wf*wam*n1; z.y += wf*wam*n2; z.z += wf*wam*n3; aux.DE *= (1.0 + 3.0*fabs(wf*wam));
		break;
	}
	case 18: // Type 18
	{
		z.x += wf*wam*sin(wfq*zy*zz2/(r+1e-21) + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq));
		break;
	}
	case 19: // Type 19
	{
		double t = wfq*r+wph; z.x += wf*wam*sin(t)*cos(wa*zy); z.y += wf*wam*cos(t)*sin(wa*zz2); z.z += wf*wam*sin(t)*cos(wa*zx); aux.DE *= (1.0 + 3.0*fabs(wf*wam));
		break;
	}
	case 20: // Type 20
	{
		double q = sin(wfq*zx+wph)+sin(wa*zy+wb)+sin(wc*zz2+wd); z.x += wf*wam*sin(q); z.y += wf*wam*cos(q); z.z += wf*wam*sin(q+M_PI*0.5); aux.DE *= (1.0 + 3.0*fabs(wf*wam));
		break;
	}
	case 21: // Type 21
	{
		{ double v=0; for(int o=0;o<4;o++){double f=wfq*pow(2.0,o); v+=sin(f*zx+wph)*cos(f*zy)/pow(2.0,o);} z.x+=wf*wam*v; aux.DE*=(1.0+fabs(wf*wam*wfq*4.0)); }
		break;
	}
	case 22: // Type 22
	{
		{ double v=0; for(int o=0;o<4;o++){double f=wfq*pow(2.0,o); v+=sin(f*zy+wph)*cos(f*zz2)/pow(2.0,o);} z.y+=wf*wam*v; aux.DE*=(1.0+fabs(wf*wam*wfq*4.0)); }
		break;
	}
	case 23: // Type 23
	{
		{ double v=0; for(int o=0;o<4;o++){double f=wfq*pow(2.0,o); v+=sin(f*zz2+wph)*cos(f*zx)/pow(2.0,o);} z.z+=wf*wam*v; aux.DE*=(1.0+fabs(wf*wam*wfq*4.0)); }
		break;
	}
	case 24: // Type 24
	{
		{ double vx=0,vy=0,vz=0; for(int o=0;o<4;o++){double f=wfq*pow(2.0,o); double a=1.0/pow(2.0,o); vx+=sin(f*zy+wph)*a; vy+=sin(f*zz2+wph)*a; vz+=sin(f*zx+wph)*a;} z.x+=wf*wam*vx; z.y+=wf*wam*vy; z.z+=wf*wam*vz; aux.DE*=(1.0+3.0*fabs(wf*wam*wfq*4.0)); }
		break;
	}
	case 25: // Type 25
	{
		{ double vx=0,vy=0,vz=0; for(int o=0;o<int(wa);o++){double f=wfq*pow(wb,o); double a=1.0/pow(wb,o); vx+=sin(f*zy+o*wph)*a; vy+=sin(f*zz2+o*wph)*a; vz+=sin(f*zx+o*wph)*a;} z.x+=wf*wam*vx; z.y+=wf*wam*vy; z.z+=wf*wam*vz; aux.DE*=(1.0+3.0*fabs(wf*wam)); }
		break;
	}
	case 26: // Type 26
	{
		{ double v=0; for(int o=0;o<4;o++){double f=wfq*pow(2.0,o); v+=fabs(sin(f*zx+wph))*cos(f*zy)/pow(2.0,o);} z.x+=wf*wam*v; aux.DE*=(1.0+fabs(wf*wam*wfq*4.0)); }
		break;
	}
	case 27: // Type 27
	{
		{ double vx=0,vy=0; for(int o=0;o<4;o++){double f=wfq*pow(2.0,o); vx+=sin(f*zy+wph)*cos(f*zz2)/pow(2.0,o); vy+=cos(f*zx+wph)*sin(f*zz2)/pow(2.0,o);} z.x+=wf*wam*vx; z.y+=wf*wam*vy; aux.DE*=(1.0+2.0*fabs(wf*wam*wfq*4.0)); }
		break;
	}
	case 28: // Type 28
	{
		{ double v=0; for(int o=0;o<6;o++){double f=wfq*pow(2.0,o); v+=sin(f*r+wph)/pow(2.0,o);} double d=wf*wam*v; z.x+=d*zx/r; z.y+=d*zy/r; z.z+=d*zz2/r; aux.DE*=(1.0+fabs(wf*wam*wfq*6.0)); }
		break;
	}
	case 29: // Type 29
	{
		{ double vx=0,vy=0,vz=0; for(int o=0;o<4;o++){double f=wfq*pow(2.0,o); double p=wph+o*M_PI*0.25; vx+=sin(f*zy+p)*cos(f*zz2+p)/pow(2.0,o); vy+=sin(f*zz2+p)*cos(f*zx+p)/pow(2.0,o); vz+=sin(f*zx+p)*cos(f*zy+p)/pow(2.0,o);} z.x+=wf*wam*vx; z.y+=wf*wam*vy; z.z+=wf*wam*vz; aux.DE*=(1.0+3.0*fabs(wf*wam*wfq*4.0)); }
		break;
	}
	case 30: // Type 30
	{
		{ double ph2=atan2(zy,zx); double th=acos(zz2/r); double v=0; for(int o=0;o<4;o++){double f=wfq*pow(2.0,o); v+=sin(f*th+wph)*cos(f*ph2)/pow(2.0,o);} double d=wf*wam*v; z.x+=d*sin(th)*cos(ph2); z.y+=d*sin(th)*sin(ph2); z.z+=d*cos(th); aux.DE*=(1.0+fabs(wf*wam*wfq*4.0)); }
		break;
	}
	case 31: // Type 31
	{
		z.x += wf*wam*(cos(wfq*zy+wph)-cos(wfq*zz2+wph)); z.y += wf*wam*(cos(wfq*zz2+wph)-cos(wfq*zx+wph)); z.z += wf*wam*(cos(wfq*zx+wph)-cos(wfq*zy+wph)); aux.DE *= (1.0 + 3.0*fabs(wf*wam*wfq));
		break;
	}
	case 32: // Type 32
	{
		{ double cx=-wfq*cos(wfq*zy+wph); double cy=-wfq*cos(wfq*zz2+wph); double cz=-wfq*cos(wfq*zx+wph); z.x+=wf*wam*(cy-cz); z.y+=wf*wam*(cz-cx); z.z+=wf*wam*(cx-cy); aux.DE*=(1.0+3.0*fabs(wf*wam*wfq)); }
		break;
	}
	case 33: // Type 33
	{
		z.x += wf*wam*sin(wfq*zy+wph)*sin(wa*zz2); z.y += -wf*wam*sin(wfq*zx+wph)*sin(wa*zz2); aux.DE *= (1.0 + 2.0*fabs(wf*wam*wfq));
		break;
	}
	case 34: // Type 34
	{
		z.x += wf*wam*sin(wfq*zz2+wph); z.z += -wf*wam*sin(wfq*zx+wph); aux.DE *= (1.0 + 2.0*fabs(wf*wam*wfq));
		break;
	}
	case 35: // Type 35
	{
		z.y += wf*wam*sin(wfq*zx+wph); z.x += -wf*wam*sin(wfq*zy+wph); aux.DE *= (1.0 + 2.0*fabs(wf*wam*wfq));
		break;
	}
	case 36: // Type 36
	{
		{ double dx=wf*wam*wfq*cos(wfq*zy+wph); double dy=wf*wam*wa*cos(wa*zz2+wph); double dz=wf*wam*wfq*cos(wfq*zx+wph); z.x+=dy-dz; z.y+=dz-dx; z.z+=dx-dy; aux.DE*=(1.0+3.0*fabs(wf*wam*wfq)); }
		break;
	}
	case 37: // Type 37
	{
		{ double psi=wf*wam*sin(wfq*zx+wph)*cos(wa*zy)*sin(wb*zz2); z.x+=wf*wam*wa*sin(wfq*zx)*cos(wa*zy); z.y+=-wf*wam*wfq*cos(wfq*zx)*sin(wa*zy); aux.DE*=(1.0+2.0*fabs(wf*wam*wfq)); }
		break;
	}
	case 38: // Type 38
	{
		{ double u=wf*wam*sin(wfq*r+wph); z.x+=u*(-zy/r); z.y+=u*(zx/r); aux.DE*=(1.0+fabs(wf*wam*wfq)); }
		break;
	}
	case 39: // Type 39
	{
		{ double u=wf*wam*sin(wfq*zz2+wph); z.x+=u*(-zy/(sqrt(zx*zx+zy*zy)+1e-21)); z.y+=u*(zx/(sqrt(zx*zx+zy*zy)+1e-21)); aux.DE*=(1.0+fabs(wf*wam*wfq)); }
		break;
	}
	case 40: // Type 40
	{
		{ double ph2=atan2(zy,zx); double u=wf*wam*sin(wfq*ph2+wph); z.z+=u; aux.DE*=(1.0+fabs(wf*wam*wfq)); }
		break;
	}
	case 41: // Type 41
	{
		{ double th=wf*wfq*zz2+wph; double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; z.y=zx*sn+zy*cs; z.x=nx; aux.DE*=(1.0+fabs(wf*wfq*wam)); }
		break;
	}
	case 42: // Type 42
	{
		{ double th=wf*wfq*zx+wph; double cs=cos(th),sn=sin(th); double ny=zy*cs-zz2*sn; z.z=zy*sn+zz2*cs; z.y=ny; aux.DE*=(1.0+fabs(wf*wfq*wam)); }
		break;
	}
	case 43: // Type 43
	{
		{ double th=wf*wfq*zy+wph; double cs=cos(th),sn=sin(th); double nx=zx*cs-zz2*sn; z.z=zx*sn+zz2*cs; z.x=nx; aux.DE*=(1.0+fabs(wf*wfq*wam)); }
		break;
	}
	case 44: // Type 44
	{
		{ double th=wf*wfq*r+wph; double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; z.y=zx*sn+zy*cs; z.x=nx; aux.DE*=(1.0+fabs(wf*wfq*wam)); }
		break;
	}
	case 45: // Type 45
	{
		{ double a1=wf*wa*sin(wfq*zz2+wph); double cs=cos(a1),sn=sin(a1); double nx=zx*cs-zy*sn; z.y=zx*sn+zy*cs; z.x=nx; double a2=wf*wb*sin(wfq*zx+wph); cs=cos(a2); sn=sin(a2); double ny=zy*cs-zz2*sn; z.z=zy*sn+zz2*cs; z.y=ny; aux.DE*=(1.0+fabs(wf*(wa+wb)*wfq)); }
		break;
	}
	case 46: // Type 46
	{
		{ double ph2=atan2(zy,zx)+wf*wam*sin(wfq*zz2+wph); double rxy=sqrt(zx*zx+zy*zy); z.x=rxy*cos(ph2); z.y=rxy*sin(ph2); aux.DE*=(1.0+fabs(wf*wam*wfq)); }
		break;
	}
	case 47: // Type 47
	{
		{ double th=acos(zz2/r)+wf*wam*sin(wfq*r+wph); double ph2=atan2(zy,zx); z.x=r*sin(th)*cos(ph2); z.y=r*sin(th)*sin(ph2); z.z=r*cos(th); aux.DE*=(1.0+fabs(wf*wam*wfq)); }
		break;
	}
	case 48: // Type 48
	{
		{ double a=wf*wam*zz2*wfq; double cs=cos(a),sn=sin(a); double nx=zx*cs-zy*sn; z.y=zx*sn+zy*cs; z.x=nx; z.z+=wf*wb*sin(wfq*r+wph); aux.DE*=(1.0+fabs(wf*(wam+wb)*wfq)); }
		break;
	}
	case 49: // Type 49
	{
		{ double a=wf*wam*sin(wfq*zz2+wph); z.x=zx*cos(a)-zy*sin(a)+wf*wb*sin(wfq*zy); z.y=zx*sin(a)+zy*cos(a)+wf*wc*cos(wfq*zz2); z.z+=wf*wd*sin(wfq*zx+wph); aux.DE*=(1.0+fabs(wf*(wam+wb+wc+wd)*wfq/4.0)); }
		break;
	}
	case 50: // Type 50
	{
		{ double t=wf*wfq*log(r+1e-21)+wph; double cs=cos(t),sn=sin(t); double nx=zx*cs-zy*sn; z.y=zx*sn+zy*cs; z.x=nx; aux.DE*=(1.0+fabs(wf*wfq/(r+1e-21))); }
		break;
	}
	case 51: // Type 51
	{
		{ double d=wf*wam*sin(wfq*r+wph); z*=(1.0+d/r); aux.DE*=(1.0+fabs(d/r)); }
		break;
	}
	case 52: // Type 52
	{
		{ double d=wf*wam/(1.0+exp(-wfq*(r-wa))); z*=(1.0+d); aux.DE*=(1.0+fabs(d)); }
		break;
	}
	case 53: // Type 53
	{
		{ double d=wf*wam*exp(-wfq*r*r); z*=(1.0+d); aux.DE*=(1.0+fabs(d)); }
		break;
	}
	case 54: // Type 54
	{
		{ double d=wf*wam*exp(-wfq*fabs(r-wa)); z*=(1.0+d); aux.DE*=(1.0+fabs(d)); }
		break;
	}
	case 55: // Type 55
	{
		{ double d=wf*wam*(sin(wfq*r+wph)+sin(wa*r+wb))*0.5; z*=(1.0+d/r); aux.DE*=(1.0+fabs(d/r)); }
		break;
	}
	case 56: // Type 56
	{
		{ double rxy=sqrt(zx*zx+zy*zy+1e-21); double d=wf*wam*sin(wfq*rxy+wph); z.x+=d*zx/rxy; z.y+=d*zy/rxy; aux.DE*=(1.0+fabs(wf*wam*wfq)); }
		break;
	}
	case 57: // Type 57
	{
		{ double d=wf*wam*sin(wfq*zz2+wph)*exp(-wa*sqrt(zx*zx+zy*zy)); z.x+=d*zx/r; z.y+=d*zy/r; z.z+=d*zz2/r; aux.DE*=(1.0+fabs(d)); }
		break;
	}
	case 58: // Type 58
	{
		{ double ph2=atan2(zy,zx); double th=acos(zz2/r); double d=wf*wam*sin(wfq*ph2*wa+wph)*sin(wb*th); z.x+=d*sin(th)*cos(ph2); z.y+=d*sin(th)*sin(ph2); z.z+=d*cos(th); aux.DE*=(1.0+fabs(wf*wam)); }
		break;
	}
	case 59: // Type 59
	{
		{ double nr=r+wf*wam*sin(wfq*r+wph); z*=(nr/r); aux.DE*=(nr/r); }
		break;
	}
	case 60: // Type 60
	{
		{ double f2=1.0+wf*wam*sin(wfq*r+wph)/(r+1e-21); z*=f2; aux.DE*=fabs(f2); }
		break;
	}
	case 61: // Type 61
	{
		z.x += wf*wam*sin(wfq*floor(zy*wa)/wa + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq));
		break;
	}
	case 62: // Type 62
	{
		z.y += wf*wam*sin(wfq*floor(zz2*wa)/wa + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq));
		break;
	}
	case 63: // Type 63
	{
		z.z += wf*wam*sin(wfq*floor(zx*wa)/wa + wph); aux.DE *= (1.0 + fabs(wf*wam*wfq));
		break;
	}
	case 64: // Type 64
	{
		{ double gx=floor(zx*wa+0.5)/wa; double gy=floor(zy*wa+0.5)/wa; z.x+=wf*wam*sin(wfq*gy+wph); z.y+=wf*wam*cos(wfq*gx+wph); aux.DE*=(1.0+2.0*fabs(wf*wam*wfq)); }
		break;
	}
	case 65: // Type 65
	{
		{ double fx=zx-floor(zx*wa)/wa; double fy=zy-floor(zy*wa)/wa; z.x+=wf*wam*sin(wfq*fx*M_PI*2.0+wph); z.y+=wf*wam*sin(wfq*fy*M_PI*2.0+wph); aux.DE*=(1.0+2.0*fabs(wf*wam*wfq)); }
		break;
	}
	case 66: // Type 66
	{
		{ double d=zx*wa-floor(zx*wa+0.5); z.x+=wf*wam*d*sin(wfq*zy+wph); aux.DE*=(1.0+fabs(wf*wam*wfq)); }
		break;
	}
	case 67: // Type 67
	{
		{ double d=sin(wfq*zx+wph)*sin(wa*zy+wb)*sin(wc*zz2+wd); z.x+=wf*wam*d; z.y+=wf*wam*d; z.z+=wf*wam*d; aux.DE*=(1.0+3.0*fabs(wf*wam)); }
		break;
	}
	case 68: // Type 68
	{
		{ double d=wf*wam*sin(wfq*(zx+zy+zz2)+wph); z.x+=d; z.y+=d; z.z+=d; aux.DE*=(1.0+3.0*fabs(wf*wam*wfq)); }
		break;
	}
	case 69: // Type 69
	{
		{ double d=wf*wam*sin(wfq*(zx*zy+zy*zz2+zz2*zx)/(r*r+1e-21)+wph); z.x+=d; z.y+=d; z.z+=d; aux.DE*=(1.0+3.0*fabs(wf*wam*wfq)); }
		break;
	}
	case 70: // Type 70
	{
		{ double v=wf*wam*cos(wfq*zx+wph)*cos(wa*zy+wb)*cos(wc*zz2+wd); z.x+=v*sin(wfq*zy); z.y+=v*sin(wa*zz2); z.z+=v*sin(wc*zx); aux.DE*=(1.0+3.0*fabs(wf*wam)); }
		break;
	}
	case 71: // Type 71
	{
		{ double d=wf*wam*exp(-wfq*(zx*zx+zy*zy)); z.z+=d; aux.DE*=(1.0+fabs(d)); }
		break;
	}
	case 72: // Type 72
	{
		{ double d=wf*wam*exp(-wfq*r)*sin(wa*r+wph); z.x+=d*zx/r; z.y+=d*zy/r; z.z+=d*zz2/r; aux.DE*=(1.0+fabs(d)); }
		break;
	}
	case 73: // Type 73
	{
		{ double d=wf*wam*exp(-wfq*fabs(zz2))*sin(wa*sqrt(zx*zx+zy*zy)+wph); z.z+=d; aux.DE*=(1.0+fabs(d)); }
		break;
	}
	case 74: // Type 74
	{
		{ double d=wf*wam/(1.0+wfq*(zx*zx+zy*zy+zz2*zz2)); z.x+=d*sin(wa*zy+wph); z.y+=d*cos(wa*zz2+wph); aux.DE*=(1.0+2.0*fabs(d*wa)); }
		break;
	}
	case 75: // Type 75
	{
		{ z *= (1.0 + wf*wam*pow(fabs(sin(wfq*r+wph)), wa)); aux.DE *= (1.0 + fabs(wf*wam)); }
		break;
	}
	case 76: // Type 76
	{
		{ double p=wf*wam*pow(r+1e-21, wa-1.0)*sin(wfq*r+wph); z.x+=p*zx; z.y+=p*zy; z.z+=p*zz2; aux.DE*=(1.0+fabs(p*r)); }
		break;
	}
	case 77: // Type 77
	{
		{ double d=wf*wam*tanh(wfq*(r-wa)); z*=(1.0+d); aux.DE*=(1.0+fabs(d)); }
		break;
	}
	case 78: // Type 78
	{
		{ double d=wf*wam*log(1.0+wfq*r)*sin(wa*r+wph)/(r+1e-21); z.x+=d*zx; z.y+=d*zy; z.z+=d*zz2; aux.DE*=(1.0+fabs(d*r)); }
		break;
	}
	case 79: // Type 79
	{
		{ double d=wf*wam*sin(wfq*log(r+1e-21)+wph); z*=(1.0+d/r); aux.DE*=(1.0+fabs(d/r)); }
		break;
	}
	case 80: // Type 80
	{
		{ double sg=1.0/(1.0+exp(-wfq*(r-wa))); z*=(1.0+wf*wam*(2.0*sg-1.0)); aux.DE*=(1.0+fabs(wf*wam*(2.0*sg-1.0))); }
		break;
	}
	case 81: // Type 81
	{
		{ double rxy=sqrt(zx*zx+zy*zy+1e-21); double d=wf*wam*sin(wfq*rxy+wph); z.z+=d; aux.DE*=(1.0+fabs(wf*wam*wfq)); }
		break;
	}
	case 82: // Type 82
	{
		{ double rxy=sqrt(zx*zx+zy*zy+1e-21); double d=wf*wam*sin(wfq*zz2+wph); z.x+=d*zx/rxy; z.y+=d*zy/rxy; aux.DE*=(1.0+fabs(wf*wam*wfq)); }
		break;
	}
	case 83: // Type 83
	{
		{ double rxy=sqrt(zx*zx+zy*zy+1e-21); double rt=rxy-wa; double dt=sqrt(rt*rt+zz2*zz2); double d=wf*wam*sin(wfq*dt+wph); z.x+=d*(rt/dt)*(zx/rxy); z.y+=d*(rt/dt)*(zy/rxy); z.z+=d*(zz2/dt); aux.DE*=(1.0+fabs(wf*wam*wfq)); }
		break;
	}
	case 84: // Type 84
	{
		{ double ph2=atan2(zy,zx); double d=wf*wam*sin(wfq*ph2*wa+wph); z.z+=d; aux.DE*=(1.0+fabs(wf*wam*wfq)); }
		break;
	}
	case 85: // Type 85
	{
		{ double ph2=atan2(zy,zx); double rxy=sqrt(zx*zx+zy*zy+1e-21); z.x+=-wf*wam*sin(ph2)*sin(wfq*zz2+wph); z.y+=wf*wam*cos(ph2)*sin(wfq*zz2+wph); aux.DE*=(1.0+fabs(wf*wam*wfq)); }
		break;
	}
	case 86: // Type 86
	{
		{ double rxy=sqrt(zx*zx+zy*zy+1e-21); double d=wf*wam*sin(wfq*rxy+wph)*cos(wa*zz2); z.x+=d*zx/rxy; z.y+=d*zy/rxy; z.z+=wf*wam*cos(wfq*rxy+wph)*sin(wa*zz2); aux.DE*=(1.0+2.0*fabs(wf*wam*wfq)); }
		break;
	}
	case 87: // Type 87
	{
		{ double rxy=sqrt(zx*zx+zy*zy+1e-21); double ph2=atan2(zy,zx)+wf*wam*sin(wfq*zz2+wph)/rxy; z.x=rxy*cos(ph2); z.y=rxy*sin(ph2); aux.DE*=(1.0+fabs(wf*wam*wfq/rxy)); }
		break;
	}
	case 88: // Type 88
	{
		{ double rxy=sqrt(zx*zx+zy*zy+1e-21); double ph2=atan2(zy,zx); double nr=rxy+wf*wam*sin(wfq*zz2+wph)*sin(wa*ph2); z.x=nr*cos(ph2); z.y=nr*sin(ph2); aux.DE*=(1.0+fabs(wf*wam*wfq)); }
		break;
	}
	case 89: // Type 89
	{
		{ double rxy=sqrt(zx*zx+zy*zy+1e-21); z.z+=wf*wam*sin(wfq*rxy+wph)*cos(wa*atan2(zy,zx)); aux.DE*=(1.0+fabs(wf*wam*wfq)); }
		break;
	}
	case 90: // Type 90
	{
		{ double rxy=sqrt(zx*zx+zy*zy+1e-21); double rt=rxy-wa; double ang=atan2(zz2,rt); double d=wf*wam*sin(wfq*ang+wph); z.x+=d*(zx/rxy); z.y+=d*(zy/rxy); aux.DE*=(1.0+fabs(wf*wam*wfq)); }
		break;
	}
	case 91: // Type 91
	{
		{ double a=wf*wa; double b=wf*wb; z.x=zx+a*sin(wfq*zy); z.y=zy+b*sin(wfq*zx); aux.DE*=(1.0+fabs((a+b)*wfq)); }
		break;
	}
	case 92: // Type 92
	{
		{ double k=wf*wam; z.x=zx+k*zy; z.y=zy+k*sin(wfq*zx+wph); aux.DE*=(1.0+fabs(k*wfq)); }
		break;
	}
	case 93: // Type 93
	{
		{ z.x=r*cos(wfq*zy/r+wph); z.y=r*sin(wfq*zy/r+wph); aux.DE*=(1.0+fabs(wf*wam*wfq/r)); }
		break;
	}
	case 94: // Type 94
	{
		{ double nr=r+wf*wam*sin(wfq*atan2(zy,zx)*wa+wph); z*=(nr/r); aux.DE*=(nr/r); }
		break;
	}
	case 95: // Type 95
	{
		{ double th=wf*wam/(r*r+1e-10); double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; z.y=zx*sn+zy*cs; z.x=nx; aux.DE*=(1.0+fabs(wf*wam*2.0*r/((r*r+1e-10)*(r*r+1e-10)))); }
		break;
	}
	case 96: // Type 96
	{
		{ double denom=zx*zx+zy*zy+1e-21; z.x=wf*wam*zx/denom+wsc*sin(wfq*zy+wph); z.y=-wf*wam*zy/denom+wsc*cos(wfq*zx+wph); aux.DE*=(1.0+fabs(wf*wam/denom)+fabs(wsc*wfq)); }
		break;
	}
	case 97: // Type 97
	{
		{ double a1=wfq; double a2=wa; z.x=zx*cos(a1*zy)-zy*sin(a1*zy)+wf*wam*sin(a2*zz2+wph); z.y=zx*sin(a1*zy)+zy*cos(a1*zy)+wf*wam*cos(a2*zz2+wph); aux.DE*=(1.0+fabs(wf*wam*a1)+fabs(wf*wam*a2)); }
		break;
	}
	case 98: // Type 98
	{
		{ double lx=wf*wam*sin(wfq*zy+wph)*(1.0-exp(-wa*r)); double ly=wf*wb*sin(wfq*zz2+wph)*(1.0-exp(-wa*r)); double lz=wf*wc*sin(wfq*zx+wph)*(1.0-exp(-wa*r)); z.x+=lx; z.y+=ly; z.z+=lz; aux.DE*=(1.0+fabs(wf*(wam+wb+wc)*wfq/3.0)); }
		break;
	}
	case 99: // Type 99
	{
		{ double t=wfq*r+wph; double d=wf*wam*sin(t)*sin(wa*t); z.x+=d*zx/r; z.y+=d*zy/r; z.z+=d*zz2/r; aux.DE*=(1.0+fabs(d)); }
		break;
	}
	case 100: // Type 100
	{
		{ double d=wf*wam*(sin(wfq*zx+wph)+sin(wa*zy+wb)+sin(wc*zz2+wd)); z*=(1.0+d/(3.0*r)); aux.DE*=(1.0+fabs(d/(3.0*r))); }
		break;
	}
	default: break;
}