// Auto-generated mutation switch for system: mb_math
// Target: GPU
// Generated mutations: 200
switch (mut->mbMathType)
{
	case 1: // Type 1
	{
		if(zx>ma) z.x=mb*2.0f-zx; if(zx<-ma) z.x=-mb*2.0f-zx; if(zy>ma) z.y=mb*2.0f-zy; if(zy<-ma) z.y=-mb*2.0f-zy; if(zz2>ma) z.z=mb*2.0f-zz2; if(zz2<-ma) z.z=-mb*2.0f-zz2; aux.DE*=fabs(mf);
		break;
	}
	case 2: // Type 2
	{
		double lim=ma*(1.0f+0.1f*sin(i*mc)); if(fabs(zx)>lim) z.x=copysign(mb*2.0f,zx)-zx; if(fabs(zy)>lim) z.y=copysign(mb*2.0f,zy)-zy; if(fabs(zz2)>lim) z.z=copysign(mb*2.0f,zz2)-zz2; aux.DE*=fabs(mf);
		break;
	}
	case 3: // Type 3
	{
		double sx=ma,sy=mb,sz=mc; double fx=1.0f/(1.0f+exp(-sx*(fabs(zx)-md))); double fy=1.0f/(1.0f+exp(-sy*(fabs(zy)-md))); double fz=1.0f/(1.0f+exp(-sz*(fabs(zz2)-md))); z.x=zx*(1.0f-fx)+copysign(me*2.0f-fabs(zx),zx)*fx; z.y=zy*(1.0f-fy)+copysign(me*2.0f-fabs(zy),zy)*fy; z.z=zz2*(1.0f-fz)+copysign(me*2.0f-fabs(zz2),zz2)*fz; aux.DE*=fabs(mf);
		break;
	}
	case 4: // Type 4
	{
		double l1=ma,v1=mb,l2=mc,v2=md; if(fabs(zx)>l1) z.x=copysign(v1*2.0f,zx)-zx; if(fabs(zx)>l2) z.x=copysign(v2*2.0f,zx)-zx; if(fabs(zy)>l1) z.y=copysign(v1*2.0f,zy)-zy; if(fabs(zy)>l2) z.y=copysign(v2*2.0f,zy)-zy; if(fabs(zz2)>l1) z.z=copysign(v1*2.0f,zz2)-zz2; if(fabs(zz2)>l2) z.z=copysign(v2*2.0f,zz2)-zz2; aux.DE*=fabs(mf);
		break;
	}
	case 5: // Type 5
	{
		double rxy=sqrt(zx*zx+zy*zy); if(rxy>ma){ double th=atan2(zy,zx); double nr=ma*2.0f-rxy; z.x=nr*cos(th); z.y=nr*sin(th); } aux.DE*=fabs(mf);
		break;
	}
	case 6: // Type 6
	{
		double rxy=sqrt(zx*zx+zy*zy); double ea=(zx/(ma+1e-21))*(zx/(ma+1e-21))+(zy/(mb+1e-21))*(zy/(mb+1e-21)); if(ea>1.0f){ double sc=1.0f/sqrt(ea); z.x*=sc; z.y*=sc; } aux.DE*=fabs(mf);
		break;
	}
	case 7: // Type 7
	{
		if(fabs(zx)+fabs(zy)>ma){ double sx=(zx>0)?1.0f:-1.0f,sy=(zy>0)?1.0f:-1.0f; double nx=ma*0.5f*sx,ny=ma*0.5f*sy; z.x=2.0f*nx-zx; z.y=2.0f*ny-zy; } aux.DE*=fabs(mf)*1.41421356f;
		break;
	}
	case 8: // Type 8
	{
		double ax=fabs(zx),ay=fabs(zy); double hx=fmax(ax,ay*0.8660254f+ax*0.5f); if(hx>ma){ z.x=copysign(ma*2.0f-ax,zx); z.y=copysign(ma*2.0f-ay,zy); } aux.DE*=fabs(mf);
		break;
	}
	case 9: // Type 9
	{
		double ax=fabs(zx),ay=fabs(zy); double ox=fmax(ax,fmax(ay,(ax+ay)*0.7071068f)); if(ox>ma){ z.x=copysign(ma*2.0f-ax,zx); z.y=copysign(ma*2.0f-ay,zy); } aux.DE*=fabs(mf);
		break;
	}
	case 10: // Type 10
	{
		double th=atan2(zy,zx); double rxy=sqrt(zx*zx+zy*zy); double rlim=ma*(1.0f+mb*cos(mc*th)); if(rxy>rlim){ double nr=rlim*2.0f-rxy; z.x=nr*cos(th); z.y=nr*sin(th); } aux.DE*=fabs(mf);
		break;
	}
	case 11: // Type 11
	{
		double th=atan2(zy,zx); double rxy=sqrt(zx*zx+zy*zy); double rlim=ma*exp(-mb*th); if(rxy>rlim){ double nr=rlim*2.0f-rxy; z.x=nr*cos(th); z.y=nr*sin(th); } aux.DE*=fabs(mf);
		break;
	}
	case 12: // Type 12
	{
		double limy=ma+mb*sin(mc*zy); if(fabs(zx)>limy) z.x=copysign(limy*2.0f,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0f,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0f,zz2)-zz2; aux.DE*=fabs(mf)*(1.0f+fabs(mb*mc));
		break;
	}
	case 13: // Type 13
	{
		double h1=ma+mb*sin(mc*zx)*sin(mc*zy)*sin(mc*zz2); if(fabs(zx)>h1) z.x=copysign(h1*2.0f,zx)-zx; if(fabs(zy)>h1) z.y=copysign(h1*2.0f,zy)-zy; if(fabs(zz2)>h1) z.z=copysign(h1*2.0f,zz2)-zz2; aux.DE*=fabs(mf);
		break;
	}
	case 14: // Type 14
	{
		double h1=ma+mb*sin(mc*zx)*cos(md*zy); if(fabs(zx)>h1) z.x=copysign(h1*2.0f,zx)-zx; if(fabs(zy)>h1) z.y=copysign(h1*2.0f,zy)-zy; if(fabs(zz2)>h1) z.z=copysign(h1*2.0f,zz2)-zz2; aux.DE*=fabs(mf)*(1.0f+fabs(mb*mc));
		break;
	}
	case 15: // Type 15
	{
		double jv=ma+0.1f*sin(mc*zx)*sin(mc*zy); if(fabs(zx)>jv) z.x=copysign(jv*2.0f,zx)-zx; if(fabs(zy)>jv) z.y=copysign(jv*2.0f,zy)-zy; aux.DE*=fabs(mf);
		break;
	}
	case 16: // Type 16
	{
		double lt=ma+0.1f*sin(mb*i); if(fabs(zx)>lt) z.x=copysign(lt*2.0f,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0f,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0f,zz2)-zz2; aux.DE*=fabs(mf);
		break;
	}
	case 17: // Type 17
	{
		double lt=ma*(1.0f+0.1f*r); if(fabs(zx)>lt) z.x=copysign(lt*2.0f,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0f,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0f,zz2)-zz2; aux.DE*=fabs(mf);
		break;
	}
	case 18: // Type 18
	{
		double cl=fabs(in.point.Length()); double lt=ma+cl*mb; if(fabs(zx)>lt) z.x=copysign(lt*2.0f,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0f,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0f,zz2)-zz2; aux.DE*=fabs(mf);
		break;
	}
	case 19: // Type 19
	{
		double c1=ma,c2=-ma; if(zx>c1+mb) z.x=2.0f*c1+mb*2.0f-zx; if(zx<c2-mb) z.x=2.0f*c2-mb*2.0f-zx; if(zy>c1+mb) z.y=2.0f*c1+mb*2.0f-zy; if(zy<c2-mb) z.y=2.0f*c2-mb*2.0f-zy; aux.DE*=fabs(mf);
		break;
	}
	case 20: // Type 20
	{
		double lt=ma; for(int n=0;n<3&&n<(int)mb;n++){ lt*=0.5f; if(fabs(zx)>lt) z.x=copysign(lt*2.0f,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0f,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0f,zz2)-zz2; } aux.DE*=fabs(mf);
		break;
	}
	case 21: // Type 21
	{
		if(i>(int)mb){ if(fabs(zx)>ma) z.x=copysign(ma*2.0f,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0f,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0f,zz2)-zz2; } aux.DE*=fabs(mf);
		break;
	}
	case 22: // Type 22
	{
		double h=((sin(i*12.9898f+zx*78.233f)*43758.5453f) - floor(sin(i*12.9898f+zx*78.233f)*43758.5453f)); if(h<mc){ if(fabs(zx)>ma) z.x=copysign(ma*2.0f,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0f,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0f,zz2)-zz2; } aux.DE*=fabs(mf)*(1.0f-mc+mc*mb);
		break;
	}
	case 23: // Type 23
	{
		double dt=zx*mc+zy*md+zz2*me; double lt=ma*(1.0f+0.1f*dt/fmax(1e-10,r)); if(fabs(zx)>lt) z.x=copysign(lt*2.0f,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0f,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0f,zz2)-zz2; aux.DE*=fabs(mf);
		break;
	}
	case 24: // Type 24
	{
		double lt=ma+mc*zx*zx; if(fabs(zx)>lt) z.x=copysign(lt*2.0f,zx)-zx; double lty=ma+mc*zy*zy; if(fabs(zy)>lty) z.y=copysign(lty*2.0f,zy)-zy; aux.DE*=fabs(mf)*(1.0f+2.0f*fabs(mc*r));
		break;
	}
	case 25: // Type 25
	{
		double lt=ma+mb*sin(mc*zx); if(fabs(zx)>lt) z.x=copysign(lt*2.0f,zx)-zx; double lty=ma+mb*sin(mc*zy); if(fabs(zy)>lty) z.y=copysign(lty*2.0f,zy)-zy; double ltz=ma+mb*sin(mc*zz2); if(fabs(zz2)>ltz) z.z=copysign(ltz*2.0f,zz2)-zz2; aux.DE*=fabs(mf)*(1.0f+fabs(mb*mc));
		break;
	}
	case 26: // Type 26
	{
		double rre=(zx/(ma+1e-10))*(zx/(ma+1e-10))+(zy/(mb+1e-10))*(zy/(mb+1e-10))+(zz2/(mc+1e-10))*(zz2/(mc+1e-10)); if(rre<1e-21) rre=1e-21; double m2=md*md/rre; z*=m2; aux.DE*=m2;
		break;
	}
	case 27: // Type 27
	{
		double rrc=zx*zx+zy*zy; if(rrc<1e-21) rrc=1e-21; double m2=ma*ma/rrc; z.x*=m2; z.y*=m2; z.z*=m2; aux.DE*=m2;
		break;
	}
	case 28: // Type 28
	{
		double rxy=sqrt(zx*zx+zy*zy); double rrt=(rxy-ma)*(rxy-ma)+zz2*zz2; if(rrt<1e-21) rrt=1e-21; double m2=mb*mb/rrt; z*=m2; aux.DE*=m2;
		break;
	}
	case 29: // Type 29
	{
		double rrh=zx*zx+zy*zy-zz2*zz2; double ar=fabs(rrh); if(ar<1e-21) ar=1e-21; double m2=ma*ma/ar; z*=m2; aux.DE*=m2*fmax(1.0f,fabs(zz2));
		break;
	}
	case 30: // Type 30
	{
		double rrp=zx*zx+zy*zy-ma*zz2; double ar=fabs(rrp); if(ar<1e-21) ar=1e-21; double m2=mb*mb/ar; z*=m2; aux.DE*=m2*sqrt(1.0f+4.0f*ma*ma);
		break;
	}
	case 31: // Type 31
	{
		double mR2=ma*(1.0f+0.1f*sin(i*mc)); double fR2=mb; if(rr<mR2) z*=fR2/mR2; else if(rr<fR2) z*=fR2/rr; aux.DE*=fabs(mf)*fR2/fmax(1e-21,fmin(rr,mR2));
		break;
	}
	case 32: // Type 32
	{
		double mx=ma,my=mb,mz=mc; double rrm=fmax(zx*zx/fmax(1e-21,mx),fmax(zy*zy/fmax(1e-21,my),zz2*zz2/fmax(1e-21,mz))); double fR2=md; if(rrm<fR2){ double m2=fR2/fmax(1e-21,rrm); z*=m2; aux.DE*=m2; }
		break;
	}
	case 33: // Type 33
	{
		double mR2_1=ma,f1=mb,mR2_2=mc,f2=md; if(rr<mR2_1){ z*=f1; aux.DE*=f1; } double rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2<mR2_2){ z*=f2; aux.DE*=f2; }
		break;
	}
	case 34: // Type 34
	{
		double sm=mc; double mR2=ma,fR2=mb; double t=1.0f/(1.0f+exp(-sm*(rr-mR2))); double m2=fR2/fmax(1e-21,rr); double sf=(1.0f-t)*m2+t*1.0f; z*=sf; aux.DE*=sf;
		break;
	}
	case 35: // Type 35
	{
		double fR2=mb; double lg=log(fmax(1e-21,fR2))/log(fmax(1e-21,rr)); z*=lg; aux.DE*=lg/(rr*log(fmax(1e-21,rr)));
		break;
	}
	case 36: // Type 36
	{
		double fR2=mb; double ex=exp(fR2-rr); z*=ex; aux.DE*=ex;
		break;
	}
	case 37: // Type 37
	{
		double fR2=mb; double pw=mc; double m2=pow(fmax(1e-21,fR2/rr),pw); z*=m2; aux.DE*=m2;
		break;
	}
	case 38: // Type 38
	{
		double k=mc,fR2=mb; double sg=1.0f/(1.0f+exp(k*(rr-fR2))); z*=sg; aux.DE*=sg;
		break;
	}
	case 39: // Type 39
	{
		double fR2=mb,sg=mc; double gs=exp(-(rr-fR2)*(rr-fR2)/(sg*sg+1e-21)); z*=gs; aux.DE*=gs;
		break;
	}
	case 40: // Type 40
	{
		double mR2=ma,fR2=mb,f1=mc; double m2=(rr<mR2)?f1:((rr<fR2)?fR2/rr:1.0f); z*=m2; aux.DE*=m2;
		break;
	}
	case 41: // Type 41
	{
		double b1=ma,f1=mb,b2=mc,f2=md,b3=me,f3=mff; double m2=(rr<b1)?f1:((rr<b2)?f2:((rr<b3)?f3:1.0f)); z*=m2; aux.DE*=m2;
		break;
	}
	case 42: // Type 42
	{
		double fR2=mb; if(rr<fR2){ double m2=1.0f/fmax(1e-21,rr); z.x=ma+fR2*(zx-ma)*m2; z.y=ma+fR2*(zy-ma)*m2; z.z=ma+fR2*(zz2-ma)*m2; aux.DE*=fR2*m2; }
		break;
	}
	case 43: // Type 43
	{
		double fR2=mb; if(rr<fR2){ double den=mc*zx+md+1e-21; z.x=(ma*zx+mb)/(den); z.y=zy/fmax(1e-10,fabs(den)); z.z=zz2/fmax(1e-10,fabs(den)); aux.DE*=fabs(ma*md-mb*mc)/(den*den); }
		break;
	}
	case 44: // Type 44
	{
		double fR2=mb; if(rr<fR2){ double qn=rr; if(qn<1e-21) qn=1e-21; double m2=fR2/qn; z*=m2; aux.DE*=m2; }
		break;
	}
	case 45: // Type 45
	{
		double dm=fmax(1e-10,acosh(fmax(1.0f,r))); double dmax=ma; if(dm<dmax){ double sc=dmax/dm; z*=sc; aux.DE*=sc*dmax/(dm*sinh(dm)+1e-21); }
		break;
	}
	case 46: // Type 46
	{
		double ox=ma,oy=mb,oz=mc; double rrc=(zx-ox)*(zx-ox)+(zy-oy)*(zy-oy)+(zz2-oz)*(zz2-oz); if(rrc<1e-21) rrc=1e-21; double fR2=md; if(rrc<fR2){ double m2=fR2/rrc; z*=m2; aux.DE*=m2; }
		break;
	}
	case 47: // Type 47
	{
		double th=ma*M_PI/180.0f; double cs=cos(th),sn=sin(th); double rx=zx*cs-zy*sn; double ry=zx*sn+zy*cs; double rrc=rx*rx+ry*ry+zz2*zz2; if(rrc<1e-21) rrc=1e-21; double fR2=mb; if(rrc<fR2){ double m2=fR2/rrc; z*=m2; aux.DE*=m2; }
		break;
	}
	case 48: // Type 48
	{
		double fR2=ma*(1.0f+0.1f*sin(i*mb)); double mR2=mc; if(rr<mR2){ z*=fR2/mR2; aux.DE*=fR2/mR2; } else if(rr<fR2){ z*=fR2/rr; aux.DE*=fR2/rr; }
		break;
	}
	case 49: // Type 49
	{
		double mR2=ma,fR2=mb; double cf=(rr<mR2)?mc:((rr<fR2)?md:0.0f); aux.color+=cf;
		break;
	}
	case 50: // Type 50
	{
		aux.color+=log(fmax(1e-21,aux.DE))*ma;
		break;
	}
	case 51: // Type 51
	{
		z.x*=ma; z.y*=mb; z.z*=mc; aux.DE*=fmax(fabs(ma),fmax(fabs(mb),fabs(mc)));
		break;
	}
	case 52: // Type 52
	{
		double sc=ma+mb*sin(i*mc); z*=sc; aux.DE*=fabs(sc);
		break;
	}
	case 53: // Type 53
	{
		double sc=ma*exp(-i*mb); z*=sc; aux.DE*=fabs(sc);
		break;
	}
	case 54: // Type 54
	{
		double sc=ma/(1.0f+log(1.0f+i)); z*=sc; aux.DE*=fabs(sc);
		break;
	}
	case 55: // Type 55
	{
		double p=fmax(0.01f,mb); double sc=ma/fmax(1e-10,pow(fmax(1.0f,(double)i),p)); z*=sc; aux.DE*=fabs(sc);
		break;
	}
	case 56: // Type 56
	{
		double f0=1,f1=1; for(int n=0;n<fmin((double)i,20.0f);n++){double t=f1;f1=f0+f1;f0=t;} double sc=ma/fmax(1.0f,f1); z*=sc; aux.DE*=fabs(sc);
		break;
	}
	case 57: // Type 57
	{
		double ns=sin(i*12.9898f+zx*78.233f)*43758.5453f; ns=ns-floor(ns); double sc=ma+ns*mb; z*=sc; aux.DE*=fabs(sc);
		break;
	}
	case 58: // Type 58
	{
		double jv=sin(i*mb)*cos(i*mc); double sc=ma+0.1f*fabs(jv); z*=sc; aux.DE*=fabs(sc);
		break;
	}
	case 59: // Type 59
	{
		double sc=ma*(1.0f+0.1f*r); z*=sc; aux.DE*=fabs(sc)*(1.0f+0.1f*r);
		break;
	}
	case 60: // Type 60
	{
		double sc=ma+0.1f*sin(i*mb); z*=sc; aux.DE*=fabs(sc);
		break;
	}
	case 61: // Type 61
	{
		double sc=ma+0.1f*mf; z*=sc; aux.DE*=fabs(sc)*1.1f;
		break;
	}
	case 62: // Type 62
	{
		double sc=(zx>0)?ma:mb; z*=sc; aux.DE*=fmax(fabs(ma),fabs(mb));
		break;
	}
	case 63: // Type 63
	{
		double th=atan2(zy,zx); double sc=ma+mb*cos(mc*th); z*=sc; aux.DE*=fabs(sc);
		break;
	}
	case 64: // Type 64
	{
		double th=atan2(sqrt(zx*zx+zy*zy),zz2); double ph=atan2(zy,zx); double sc=ma+mb*cos(mc*th)*sin(md*ph); z*=sc; aux.DE*=fabs(sc);
		break;
	}
	case 65: // Type 65
	{
		double off=ma+0.1f*sin(i*mb); z.x+=off; z.y+=off; z.z+=off; aux.DE*=fabs(mf);
		break;
	}
	case 66: // Type 66
	{
		z.x+=ma; z.y+=mb; z.z+=mc; aux.DE*=fabs(mf);
		break;
	}
	case 67: // Type 67
	{
		double cl=in.point.Length(); z.x+=cl*ma; z.y+=cl*ma; z.z+=cl*ma; aux.DE*=fabs(mf);
		break;
	}
	case 68: // Type 68
	{
		z.x+=zx*0.1f*ma; z.y+=zy*0.1f*ma; z.z+=zz2*0.1f*ma; aux.DE*=fabs(mf);
		break;
	}
	case 69: // Type 69
	{
		double ns=sin(zx*ma+zy*mb+zz2*mc)*md; z.x+=ns; z.y+=ns; z.z+=ns; aux.DE*=fabs(mf);
		break;
	}
	case 70: // Type 70
	{
		double off=ma+0.1f*sin(i*mb); z.x+=off; z.y+=off*0.5f; z.z+=off*0.25f; aux.DE*=fabs(mf);
		break;
	}
	case 71: // Type 71
	{
		double off=ma+0.1f*mf; z.x+=off; z.y+=off; z.z+=off; aux.DE*=fabs(mf);
		break;
	}
	case 72: // Type 72
	{
		double off=(rr<ma)?mb:mc; z.x+=off; z.y+=off; z.z+=off; aux.DE*=fabs(mf);
		break;
	}
	case 73: // Type 73
	{
		double off=ma*(1.0f+0.1f*r); z.x+=off; z.y+=off; z.z+=off; aux.DE*=fabs(mf);
		break;
	}
	case 74: // Type 74
	{
		double th=i*ma; double spr=mb; z.x+=spr*cos(th); z.y+=spr*sin(th); aux.DE*=fabs(mf);
		break;
	}
	case 75: // Type 75
	{
		z.x+=ma*sin(mb*i); z.y+=mc*sin(md*i); z.z+=me*sin(mff*i); aux.DE*=fabs(mf);
		break;
	}
	case 76: // Type 76
	{
		double ga=2.39996322973f; double th=i*ga; double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; double ny=zx*sn+zy*cs; z.x=nx; z.y=ny; aux.DE*=fabs(mf);
		break;
	}
	case 77: // Type 77
	{
		double hth=ma*M_PI/360.0f; double ax=mb,ay=mc,az=md; double nm=sqrt(ax*ax+ay*ay+az*az+1e-21); ax/=nm;ay/=nm;az/=nm; double cq=cos(hth),sq=sin(hth); double qw=cq,qx=sq*ax,qy=sq*ay,qz=sq*az; double nx=zx*(1-2*(qy*qy+qz*qz))+zy*2*(qx*qy-qw*qz)+zz2*2*(qx*qz+qw*qy); double ny=zx*2*(qx*qy+qw*qz)+zy*(1-2*(qx*qx+qz*qz))+zz2*2*(qy*qz-qw*qx); double nz=zx*2*(qx*qz-qw*qy)+zy*2*(qy*qz+qw*qx)+zz2*(1-2*(qx*qx+qy*qy)); z.x=nx;z.y=ny;z.z=nz; aux.DE*=fabs(mf);
		break;
	}
	case 78: // Type 78
	{
		double th=ma*M_PI/180.0f; double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; double ny=zx*sn+zy*cs; z.x=nx; z.y=ny; double ph=mb*M_PI/180.0f; double cp=cos(ph),sp=sin(ph); double nxz=z.x*cp-zz2*sp; double nz=z.x*sp+zz2*cp; z.x=nxz; z.z=nz; aux.DE*=fabs(mf);
		break;
	}
	case 79: // Type 79
	{
		double th=ma*M_PI/180.0f; double cs=cos(th),sn=sin(th); z.x=zx*cs-zy*sn; z.y=zx*sn+zy*cs; double ph=mb*M_PI/180.0f; cs=cos(ph); sn=sin(ph); double ty=z.y*cs-zz2*sn; z.z=z.y*sn+zz2*cs; z.y=ty; double ps=mc*M_PI/180.0f; cs=cos(ps);sn=sin(ps); double tx=z.x*cs-z.z*sn; z.z=z.x*sn+z.z*cs; z.x=tx; aux.DE*=fabs(mf);
		break;
	}
	case 80: // Type 80
	{
		double v=ma; double gm=1.0f/sqrt(fmax(1e-10,1.0f-v*v)); z.x=gm*(zx-v*zz2); z.z=gm*(zz2-v*zx); aux.DE*=fabs(mf)*gm;
		break;
	}
	case 81: // Type 81
	{
		z.x+=ma; z.y+=mb*sin(mc*zz2); aux.DE*=fabs(mf);
		break;
	}
	case 82: // Type 82
	{
		double s=ma; double th=mb*M_PI/180.0f; double cs=cos(th),sn=sin(th); z.x=s*(zx*cs-zy*sn); z.y=s*(zx*sn+zy*cs); z.z*=s; aux.DE*=fabs(s)*fabs(mf);
		break;
	}
	case 83: // Type 83
	{
		double N=fmax(2.0f,ma); double th=2.0f*M_PI/N; double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; double ny=zx*sn+zy*cs; z.x=nx; z.y=ny; aux.DE*=fabs(mf);
		break;
	}
	case 84: // Type 84
	{
		double ax=sin(i*ma),ay=cos(i*ma); double nm=sqrt(ax*ax+ay*ay+1e-21); ax/=nm; ay/=nm; double th=mb*M_PI/180.0f; double cs=cos(th),sn=sin(th); double d=zx*ax+zy*ay; double px=zx-d*ax,py=zy-d*ay; double rx=px*cs-py*sn+d*ax,ry=px*sn+py*cs+d*ay; z.x=rx;z.y=ry; aux.DE*=fabs(mf);
		break;
	}
	case 85: // Type 85
	{
		double ns=sin(i*12.9898f+78.233f)*43758.5453f; ns=ns-floor(ns); double th=ns*2.0f*M_PI*ma; double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; double ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf);
		break;
	}
	case 86: // Type 86
	{
		double th=ma+mb*i; double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; double ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf);
		break;
	}
	case 87: // Type 87
	{
		double th=ma+mf; double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; double ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf);
		break;
	}
	case 88: // Type 88
	{
		if(zx>0){ double th=ma*M_PI/180.0f; double cs=cos(th),sn=sin(th); z.x=zx*cs-zy*sn; z.y=zx*sn+zy*cs; } else { double th=mb*M_PI/180.0f; double cs=cos(th),sn=sin(th); z.x=zx*cs-zy*sn; z.y=zx*sn+zy*cs; } aux.DE*=fabs(mf);
		break;
	}
	case 89: // Type 89
	{
		double th=ma*(1.0f+0.1f*r); double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; double ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf);
		break;
	}
	case 90: // Type 90
	{
		double ph=atan2(zy,zx); double th=ma+mb*cos(mc*ph); double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; double ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf);
		break;
	}
	case 91: // Type 91
	{
		double N=fmax(2.0f,ma); double th=atan2(zy,zx); double sector=2.0f*M_PI/N; th=fmod(th+sector*0.5f+100.0f*sector,sector)-sector*0.5f; double rxy=sqrt(zx*zx+zy*zy); z.x=rxy*cos(th); z.y=rxy*sin(th); aux.DE*=fabs(mf);
		break;
	}
	case 92: // Type 92
	{
		double nx=fabs(zx); double ny=fabs(zy); double nz2=fabs(zz2); if(ma>0) z.x=nx; if(mb>0) z.y=ny; if(mc>0) z.z=nz2; aux.DE*=fabs(mf);
		break;
	}
	case 93: // Type 93
	{
		z.x+=ma*zy; z.y+=mb*zz2; aux.DE*=fabs(mf)*sqrt(1.0f+ma*ma+mb*mb);
		break;
	}
	case 94: // Type 94
	{
		double rxy=sqrt(zx*zx+zy*zy); double th=atan2(zy,zx)+ma*zz2; z.x=rxy*cos(th); z.y=rxy*sin(th); aux.DE*=fabs(mf)*sqrt(1.0f+ma*ma*rxy*rxy);
		break;
	}
	case 95: // Type 95
	{
		double cv=ma; double rxy=sqrt(zx*zx+zy*zy); double th=atan2(zy,zx)+cv*rxy; z.x=rxy*cos(th); z.y=rxy*sin(th); aux.DE*=fabs(mf)*(1.0f+cv*rxy);
		break;
	}
	case 96: // Type 96
	{
		double tf=ma; z.x*=(1.0f-tf*zz2); z.y*=(1.0f-tf*zz2); aux.DE*=fabs(mf)*(1.0f-tf*zz2);
		break;
	}
	case 97: // Type 97
	{
		double g=ma; double th=atan2(zy,zx)+g*log(fmax(1e-10,sqrt(zx*zx+zy*zy))); double rxy=sqrt(zx*zx+zy*zy); z.x=rxy*cos(th); z.y=rxy*sin(th); aux.DE*=fabs(mf)*g;
		break;
	}
	case 98: // Type 98
	{
		double th=ma*exp(i*mb); double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; double ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf);
		break;
	}
	case 99: // Type 99
	{
		double th=ma*log(1.0f+i); double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; double ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf);
		break;
	}
	case 100: // Type 100
	{
		double p=mb; double th=ma*pow(fmax(1.0f,(double)i),p); double cs=cos(th),sn=sin(th); double nx=zx*cs-zy*sn; double ny=zx*sn+zy*cs; z.x=nx;z.y=ny; aux.DE*=fabs(mf);
		break;
	}
	case 101: // Type 101
	{
		double w=ma; double rr4=rr+w*w; if(rr4<1e-21) rr4=1e-21; double sc=mf; z.x=zx*sc+w*0.1f; z.y=zy*sc; z.z=zz2*sc; aux.DE*=fabs(sc);
		break;
	}
	case 102: // Type 102
	{
		double w=ma,v=mb; double rr5=rr+w*w+v*v; if(rr5<1e-21) rr5=1e-21; double sc=mf; z*=sc; z.x+=w*0.05f; z.y+=v*0.05f; aux.DE*=fabs(sc);
		break;
	}
	case 103: // Type 103
	{
		double w=ma*sin(mb*i); z.x+=w*0.1f; aux.DE*=fabs(mf);
		break;
	}
	case 104: // Type 104
	{
		double th4=ma*M_PI/180.0f; double cs=cos(th4),sn=sin(th4); double nw=zz2*sn; z.z=zz2*cs; z.x+=nw*0.1f; aux.DE*=fabs(mf);
		break;
	}
	case 105: // Type 105
	{
		double cx=ma,cy=mb,cz=mc; (void)md; z.x+=cx*mf; z.y+=cy*mf; z.z+=cz*mf; aux.DE*=fabs(mf);
		break;
	}
	case 106: // Type 106
	{
		double qw=ma,qx=zx,qy=zy,qz=zz2; double nm=sqrt(qw*qw+qx*qx+qy*qy+qz*qz+1e-21); z.x=qx/nm*mf; z.y=qy/nm*mf; z.z=qz/nm*mf; aux.DE*=fabs(mf)/nm;
		break;
	}
	case 107: // Type 107
	{
		double q1w=ma,q2w=mb; double nm1=sqrt(zx*zx+zy*zy+q1w*q1w+1e-21); double nm2=sqrt(zz2*zz2+q2w*q2w+1e-21); z.x*=nm2/(nm1+1e-21); z.y*=nm2/(nm1+1e-21); aux.DE*=fabs(mf)*nm2/(nm1+1e-21);
		break;
	}
	case 108: // Type 108
	{
		double d4=sqrt(rr+ma*ma); double td=tanh(d4); z*=td/fmax(1e-10,d4); double ch=cosh(d4); aux.DE*=fabs(mf)/(ch*ch+1e-21);
		break;
	}
	case 109: // Type 109
	{
		double rr4=rr+ma*ma; double nm4=sqrt(rr4+1e-21); z*=1.0f/nm4; aux.DE*=fabs(mf)/nm4;
		break;
	}
	case 110: // Type 110
	{
		double rxy=sqrt(zx*zx+zy*zy+1e-21); z.x=(rxy-ma)*cos(atan2(zy,zx)); z.y=(rxy-ma)*sin(atan2(zy,zx)); aux.DE*=fabs(mf)*rxy;
		break;
	}
	case 111: // Type 111
	{
		double R=ma,rr2=mb; double th=atan2(zy,zx); z.x=(R+rr2*cos(th))*cos(mc*i); z.y=(R+rr2*cos(th))*sin(mc*i); z.z=rr2*sin(th); aux.DE*=fabs(mf)*R;
		break;
	}
	case 112: // Type 112
	{
		double th=ma*M_PI/180.0f; double ph=mb*M_PI/180.0f; double cs1=cos(th),sn1=sin(th),cs2=cos(ph); double nx=zx*cs1-zy*sn1; double ny=zx*sn1+zy*cs1; double nz2=zz2*cs2; z.x=nx;z.y=ny;z.z=nz2; aux.DE*=fabs(mf);
		break;
	}
	case 113: // Type 113
	{
		double ga=2.39996322973f; double th=i*ga; double r4=sqrt(rr+1e-21); z.x=r4*cos(th)*cos(ma*i); z.y=r4*sin(th)*cos(ma*i); z.z=r4*sin(ma*i); aux.DE*=fabs(mf);
		break;
	}
	case 114: // Type 114
	{
		double D=ma; double sc=pow(2.0f,D); z*=sc/fmax(1e-10,r); aux.DE*=sc/fmax(1e-10,r);
		break;
	}
	case 115: // Type 115
	{
		double h=((sin(i*12.9898f+78.233f)*43758.5453f) - floor(sin(i*12.9898f+78.233f)*43758.5453f)); if(h<ma){ z.x=-z.x; z.y=-z.y; } aux.DE*=fabs(mf);
		break;
	}
	case 116: // Type 116
	{
		double w=ma+0.1f*sin(i*mb); z.x+=w*0.1f; aux.DE*=fabs(mf);
		break;
	}
	case 117: // Type 117
	{
		z.x+=0.1f*zx*ma; z.y+=0.1f*zy*ma; z.z+=0.1f*zz2*ma; aux.DE*=fabs(mf)*1.1f;
		break;
	}
	case 118: // Type 118
	{
		double ns=sin(zx*ma+i*mb)*cos(zy*mc); z.x+=ns*0.1f*md; z.y+=ns*0.1f*md; aux.DE*=fabs(mf);
		break;
	}
	case 119: // Type 119
	{
		double jv=sin(i*ma)*cos(i*mb); double sc=mf+0.1f*jv; z*=sc; aux.DE*=fabs(sc);
		break;
	}
	case 120: // Type 120
	{
		double sc1=ma,sc2=mb; z*=sc1; double rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2>1e-21){ z*=sc2/sqrt(rr2); } aux.DE*=fmax(fabs(sc1),fabs(sc2));
		break;
	}
	case 121: // Type 121
	{
		double h=((sin(i*12.9898f+78.233f)*43758.5453f) - floor(sin(i*12.9898f+78.233f)*43758.5453f)); double w=(h<ma)?mb:mc; z.x+=w*0.1f; aux.DE*=fabs(mf);
		break;
	}
	case 122: // Type 122
	{
		double h=((sin(i*12.9898f+zx*78.233f)*43758.5453f) - floor(sin(i*12.9898f+zx*78.233f)*43758.5453f)); double sc=ma+h*mb*0.1f; z*=sc; aux.DE*=fabs(sc);
		break;
	}
	case 123: // Type 123
	{
		double p=ma; z.x=fmod(zx+p*0.5f,p)-p*0.5f; z.y=fmod(zy+p*0.5f,p)-p*0.5f; z.z=fmod(zz2+p*0.5f,p)-p*0.5f; aux.DE*=fabs(mf)/fmax(0.01f,p);
		break;
	}
	case 124: // Type 124
	{
		double fR2=ma; if(rr<fR2){ double m2=fR2/fmax(1e-21,rr); z*=m2; aux.DE*=m2; }
		break;
	}
	case 125: // Type 125
	{
		if(fabs(zx)>ma) z.x=copysign(ma,zx); if(fabs(zy)>ma) z.y=copysign(ma,zy); if(fabs(zz2)>ma) z.z=copysign(ma,zz2); aux.DE*=fabs(mf);
		break;
	}
	case 126: // Type 126
	{
		double dx=fabs(z.x-zx),dy=fabs(z.y-zy),dz=fabs(z.z-zz2); aux.color+=ma*dx+mb*dy+mc*dz;
		break;
	}
	case 127: // Type 127
	{
		double mR2=ma,fR2=mb; double t=(rr-mR2)/(fR2-mR2+1e-21); t=fmax(0.0f,fmin(1.0f,t)); aux.color+=t*mc;
		break;
	}
	case 128: // Type 128
	{
		aux.color+=log(fabs(mf)+1e-21)*ma;
		break;
	}
	case 129: // Type 129
	{
		double th=atan2(zy,zx); aux.color+=fabs(th)*ma;
		break;
	}
	case 130: // Type 130
	{
		double td=sqrt((zx-ma)*(zx-ma)+(zy-mb)*(zy-mb)+(zz2-mc)*(zz2-mc))-md; aux.color+=fmax(0.0f,1.0f-fabs(td))*me;
		break;
	}
	case 131: // Type 131
	{
		double ax1=ma,ay1=mb,bx1=mc,by1=md; double dx=bx1-ax1,dy=by1-ay1; double t=((zx-ax1)*dx+(zy-ay1)*dy)/(dx*dx+dy*dy+1e-21); t=fmax(0.0f,fmin(1.0f,t)); double px=ax1+t*dx,py=ay1+t*dy; double dd=sqrt((zx-px)*(zx-px)+(zy-py)*(zy-py)); aux.color+=fmax(0.0f,1.0f-dd)*me;
		break;
	}
	case 132: // Type 132
	{
		double dd=fmin(fabs(zx),fmin(fabs(zy),fabs(zz2))); aux.color+=fmax(0.0f,1.0f-dd*ma)*mb;
		break;
	}
	case 133: // Type 133
	{
		double nx=ma,ny=mb,nz2=mc; double nm=sqrt(nx*nx+ny*ny+nz2*nz2+1e-21); double dd=fabs(zx*nx/nm+zy*ny/nm+zz2*nz2/nm-md); aux.color+=fmax(0.0f,1.0f-dd)*me;
		break;
	}
	case 134: // Type 134
	{
		double R=ma,rr2=mb; double rxy=sqrt(zx*zx+zy*zy+1e-21); double td=(rxy-R)*(rxy-R)+zz2*zz2-rr2*rr2; aux.color+=fmax(0.0f,1.0f-fabs(td))*mc;
		break;
	}
	case 135: // Type 135
	{
		double jv=sin(zx*ma)*sin(zy*mb); aux.color+=fabs(jv)*mc;
		break;
	}
	case 136: // Type 136
	{
		aux.color+=(double)i/fmax(1.0f,ma)*mb;
		break;
	}
	case 137: // Type 137
	{
		aux.color+=log(fmax(1e-21,aux.DE))*ma;
		break;
	}
	case 138: // Type 138
	{
		double spd=sqrt((z.x-zx)*(z.x-zx)+(z.y-zy)*(z.y-zy)+(z.z-zz2)*(z.z-zz2)); aux.color+=spd*ma;
		break;
	}
	case 139: // Type 139
	{
		aux.color+=r*ma*0.01f;
		break;
	}
	case 140: // Type 140
	{
		double th=atan2(zy,zx); aux.color+=th*ma;
		break;
	}
	case 141: // Type 141
	{
		aux.color+=r*ma;
		break;
	}
	case 142: // Type 142
	{
		double p=fmax(0.01f,ma); double cx2=floor(zx/p),cy2=floor(zy/p),cz2=floor(zz2/p); double h=((sin(cx2*12.9898f+cy2*78.233f+cz2*37.719f)*43758.5453f) - floor(sin(cx2*12.9898f+cy2*78.233f+cz2*37.719f)*43758.5453f)); aux.color+=h*mb;
		break;
	}
	case 143: // Type 143
	{
		aux.color+=sin(i*ma+mb)*mc;
		break;
	}
	case 144: // Type 144
	{
		aux.color=0.9f*aux.color+0.1f*ma*r;
		break;
	}
	case 145: // Type 145
	{
		double ns=sin(zx*ma+zy*mb+zz2*mc)*md; aux.color+=ns;
		break;
	}
	case 146: // Type 146
	{
		double cl=in.point.Length(); aux.color+=cl*ma;
		break;
	}
	case 147: // Type 147
	{
		aux.color+=sqrt(zx*zx+zy*zy)*ma;
		break;
	}
	case 148: // Type 148
	{
		double fc=fabs(z.x-zx)*0.3f+r*0.3f+fabs(atan2(zy,zx))*0.4f; aux.color+=fc*ma;
		break;
	}
	case 149: // Type 149
	{
		double ns=sin(zx*ma+zy*mb)*cos(zz2*mc+i*md); aux.color+=fabs(ns)*me;
		break;
	}
	case 150: // Type 150
	{
		double jv=sin(zx*ma)*sin(zy*mb)*sin(zz2*mc); aux.color+=fabs(jv)*md;
		break;
	}
	case 151: // Type 151
	{
		double eps=ma*0.001f; double dx=(sqrt((zx+eps)*(zx+eps)+zy*zy+zz2*zz2)-sqrt((zx-eps)*(zx-eps)+zy*zy+zz2*zz2))/(2.0f*eps); aux.DE=fmax(1e-21,fabs(dx)*aux.DE);
		break;
	}
	case 152: // Type 152
	{
		double de_num=r*0.5f; double de_safe=fmin(aux.DE,de_num); aux.DE=de_safe;
		break;
	}
	case 153: // Type 153
	{
		aux.DE=0.9f*aux.DE+0.1f*r*ma;
		break;
	}
	case 154: // Type 154
	{
		double prev=aux.DE; aux.DE=prev+0.5f*(prev-ma);
		break;
	}
	case 155: // Type 155
	{
		double spd=r*0.01f; aux.DE=aux.DE*(1.0f+0.5f*spd);
		break;
	}
	case 156: // Type 156
	{
		double tr=ma; aux.DE=fmin(aux.DE,tr);
		break;
	}
	case 157: // Type 157
	{
		double j11=1.0f+ma*cos(zx),j22=1.0f+mb*cos(zy),j33=1.0f+mc*cos(zz2); aux.DE*=fmax(fabs(j11),fmax(fabs(j22),fabs(j33)));
		break;
	}
	case 158: // Type 158
	{
		double h=ma*sin(zx)*sin(zy)*sin(zz2); aux.DE*=(1.0f+h*0.5f);
		break;
	}
	case 159: // Type 159
	{
		aux.DE=log(fmax(1e-21,aux.DE))*ma+mb;
		break;
	}
	case 160: // Type 160
	{
		aux.DE=(exp(fmin(10.0f,aux.DE))-1.0f)*ma;
		break;
	}
	case 161: // Type 161
	{
		double p=ma; aux.DE=pow(fmax(1e-21,aux.DE),p);
		break;
	}
	case 162: // Type 162
	{
		double k=ma,de0=mb; aux.DE=1.0f/(1.0f+exp(-k*(aux.DE-de0)));
		break;
	}
	case 163: // Type 163
	{
		double de0=ma,sg=mb; aux.DE=exp(-(aux.DE-de0)*(aux.DE-de0)/(sg*sg+1e-21));
		break;
	}
	case 164: // Type 164
	{
		double th2=ma; aux.DE=(aux.DE>th2)?mb:mc;
		break;
	}
	case 165: // Type 165
	{
		double b1=ma,d1=mb,b2=mc,d2=md; aux.DE=(aux.DE<b1)?d1:((aux.DE<b2)?d2:aux.DE);
		break;
	}
	case 166: // Type 166
	{
		double ns=sin(zx*ma+zy*mb+zz2*mc)*md; aux.DE+=ns; aux.DE=fmax(1e-21,aux.DE);
		break;
	}
	case 167: // Type 167
	{
		double jv=fabs(sin(zx*ma)*sin(zy*mb)); aux.DE*=(1.0f+0.1f*jv);
		break;
	}
	case 168: // Type 168
	{
		aux.DE*=(1.0f+0.1f*sin(i*ma));
		break;
	}
	case 169: // Type 169
	{
		aux.DE=0.9f*aux.DE+0.1f*ma;
		break;
	}
	case 170: // Type 170
	{
		double ns=sin(zx*ma+zy*mb)*cos(zz2*mc+i*md); aux.DE*=(1.0f+me*ns);
		break;
	}
	case 171: // Type 171
	{
		double fn=sin(zx*ma*10.0f)*sin(zy*mb*10.0f)*sin(zz2*mc*10.0f); aux.DE*=(1.0f+0.1f*fn);
		break;
	}
	case 172: // Type 172
	{
		double spd=r*0.01f; aux.DE/=(1.0f+spd);
		break;
	}
	case 173: // Type 173
	{
		aux.DE*=fabs(mf);
		break;
	}
	case 174: // Type 174
	{
		if(fabs(zx)>ma) z.x=copysign(ma*2.0f,zx)-zx; double rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2<mb*mb) z*=mc*mc/(rr2+1e-21); aux.DE*=fabs(mf);
		break;
	}
	case 175: // Type 175
	{
		double sc=ma+mb*sin(i*mc); z*=sc; if(fabs(z.x)>md) z.x=copysign(md*2.0f,z.x)-z.x; aux.DE*=fabs(sc);
		break;
	}
	case 176: // Type 176
	{
		double th=ma*M_PI/180.0f; double cs=cos(th),sn=sin(th); z.x=zx*cs-zy*sn; z.y=zx*sn+zy*cs; if(fabs(z.x)>mb) z.x=copysign(mb*2.0f,z.x)-z.x; aux.DE*=fabs(mf);
		break;
	}
	case 177: // Type 177
	{
		if(fabs(zx)>ma) z.x=copysign(ma*2.0f,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0f,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0f,zz2)-zz2; double rr2=z.x*z.x+z.y*z.y+z.z*z.z; double fR2=mb; if(rr2<mc) z*=fR2/mc; else if(rr2<fR2) z*=fR2/rr2; z*=md; z.x+=me; z.y+=mff; z.z+=mg; aux.DE*=fabs(md);
		break;
	}
	case 178: // Type 178
	{
		double th=i*2.39996322973f; double cs=cos(th),sn=sin(th); z.x=zx*cs-zy*sn; z.y=zx*sn+zy*cs; if(fabs(z.x)>ma) z.x=copysign(ma*2.0f,z.x)-z.x; z*=mb; aux.DE*=fabs(mb);
		break;
	}
	case 179: // Type 179
	{
		double rxy=sqrt(zx*zx+zy*zy); if(rxy>ma){ double th=atan2(zy,zx); z.x=(ma*2.0f-rxy)*cos(th); z.y=(ma*2.0f-rxy)*sin(th); } double rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2<mb) z*=mc/rr2; aux.DE*=fabs(mf);
		break;
	}
	case 180: // Type 180
	{
		z.x+=ma*sin(mb*zy); z.y+=mc*sin(md*zz2); z.z+=me*sin(mff*zx); aux.DE*=fabs(mf)*(1.0f+fabs(ma*mb)+fabs(mc*md)+fabs(me*mff));
		break;
	}
	case 181: // Type 181
	{
		if(fabs(zx)>ma) z.x=copysign(ma*2.0f,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0f,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0f,zz2)-zz2; aux.color+=mb*fabs(z.x-zx); aux.DE*=fabs(mf);
		break;
	}
	case 182: // Type 182
	{
		double rr2=rr; double mR2=ma*ma; double fR2=mb*mb; if(rr2<mR2){ z*=fR2/mR2; aux.DE*=fR2/mR2; } else if(rr2<fR2){ z*=fR2/rr2; aux.DE*=fR2/rr2; } aux.color+=mc*log(fmax(1e-21,rr2/(mR2+1e-21)));
		break;
	}
	case 183: // Type 183
	{
		double sc=ma; z*=sc; aux.DE*=fabs(sc); z.x+=mb; z.y+=mc; z.z+=md; double th=me*M_PI/180.0f; double cs=cos(th),sn=sin(th); double nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx;
		break;
	}
	case 184: // Type 184
	{
		double lt=ma*(1.0f+mb*r/fmax(1e-10,sqrt(rr))); if(fabs(zx)>lt) z.x=copysign(lt*2.0f,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0f,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0f,zz2)-zz2; aux.DE*=fabs(mf);
		break;
	}
	case 185: // Type 185
	{
		double mR2=ma*ma; double fR2=mb*mb; double sm=mc; double t=1.0f/(1.0f+exp(-sm*(rr-mR2))); double m2=fR2/fmax(1e-21,rr); double sf=(1.0f-t)*m2+t; z*=sf; aux.DE*=sf; z*=md; z.x+=me; aux.DE*=fabs(md);
		break;
	}
	case 186: // Type 186
	{
		double N=fmax(2.0f,ma); double th=atan2(zy,zx); double sector=2.0f*M_PI/N; th=fmod(th+sector*0.5f+100.0f*sector,sector)-sector*0.5f; double rxy=sqrt(zx*zx+zy*zy); z.x=rxy*cos(th); z.y=rxy*sin(th); if(fabs(z.x)>mb) z.x=copysign(mb*2.0f,z.x)-z.x; aux.DE*=fabs(mf);
		break;
	}
	case 187: // Type 187
	{
		z.x=fabs(zx); z.y=fabs(zy); z.z=fabs(zz2); if(fabs(z.x)>ma) z.x=ma*2.0f-z.x; if(fabs(z.y)>ma) z.y=ma*2.0f-z.y; if(fabs(z.z)>ma) z.z=ma*2.0f-z.z; aux.DE*=fabs(mf);
		break;
	}
	case 188: // Type 188
	{
		if(fabs(zx)>ma) z.x=copysign(ma*2.0f,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0f,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0f,zz2)-zz2; double rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2<mb) z*=mc/rr2; else if(rr2<mc) z*=mc/rr2; double th=md*M_PI/180.0f; double cs=cos(th),sn=sin(th); double nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; z*=me; z.x+=mff; aux.DE*=fabs(me);
		break;
	}
	case 189: // Type 189
	{
		double rxy=sqrt(zx*zx+zy*zy); double th=atan2(zy,zx)+ma*sin(mb*zz2); z.x=rxy*cos(th); z.y=rxy*sin(th); if(fabs(z.x)>mc) z.x=copysign(mc*2.0f,z.x)-z.x; aux.DE*=fabs(mf)*(1.0f+fabs(ma*mb));
		break;
	}
	case 190: // Type 190
	{
		double pw=ma; double rp=pow(fmax(1e-10,r),pw-1.0f); double th=atan2(zy,zx)*pw; double ph=asin(zz2/fmax(1e-10,r))*pw; z.x=rp*cos(ph)*cos(th); z.y=rp*cos(ph)*sin(th); z.z=rp*sin(ph); aux.DE*=pw*rp;
		break;
	}
	case 191: // Type 191
	{
		z.x+=ma*sin(mb*i)*cos(mc*zy); z.y+=md*cos(me*i)*sin(mff*zx); z.z+=mg*sin(mh*i); aux.DE*=fabs(mf);
		break;
	}
	case 192: // Type 192
	{
		double sc=mf; z*=sc; double lt=ma; if(fabs(z.x)>lt) z.x=copysign(lt*2.0f,z.x)-z.x; if(fabs(z.y)>lt) z.y=copysign(lt*2.0f,z.y)-z.y; if(fabs(z.z)>lt) z.z=copysign(lt*2.0f,z.z)-z.z; double rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2<mb) z*=mc/rr2; aux.DE*=fabs(sc);
		break;
	}
	case 193: // Type 193
	{
		double p=fmax(0.01f,ma); z.x=fmod(zx+p*0.5f,p)-p*0.5f; z.y=fmod(zy+p*0.5f,p)-p*0.5f; z.z=fmod(zz2+p*0.5f,p)-p*0.5f; if(fabs(z.x)>mb) z.x=copysign(mb*2.0f,z.x)-z.x; aux.DE*=fabs(mf)/fmax(0.01f,p);
		break;
	}
	case 194: // Type 194
	{
		double ex=exp(-ma*rr); z*=(1.0f+mb*ex); aux.DE*=(1.0f+mb*ex);
		break;
	}
	case 195: // Type 195
	{
		double sg=1.0f/(1.0f+exp(-ma*(r-mb))); z*=(1.0f+mc*sg); aux.DE*=(1.0f+mc*sg);
		break;
	}
	case 196: // Type 196
	{
		z.x+=ma*sin(mb*zx)*cos(mc*zy); z.y+=md*cos(me*zy)*sin(mff*zz2); z.z+=mg*sin(mh*zz2)*cos(ma*zx); aux.DE*=fabs(mf);
		break;
	}
	case 197: // Type 197
	{
		double th1=ma*M_PI/180.0f+mb*sin(i*mc); double cs1=cos(th1),sn1=sin(th1); z.x=zx*cs1-zy*sn1; z.y=zx*sn1+zy*cs1; if(fabs(z.x)>md) z.x=copysign(md*2.0f,z.x)-z.x; z*=me; aux.DE*=fabs(me);
		break;
	}
	case 198: // Type 198
	{
		double rr2=rr; double fR2=ma*ma; if(rr2<fR2){ double m2=fR2/fmax(1e-21,rr2); z*=m2; aux.DE*=m2; } double th=mb*M_PI/180.0f; double cs=cos(th),sn=sin(th); double nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; z*=mc; z.x+=md; aux.DE*=fabs(mc);
		break;
	}
	case 199: // Type 199
	{
		double lt=ma+mb*sin(mc*i)*cos(md*r); if(fabs(zx)>lt) z.x=copysign(lt*2.0f,zx)-zx; if(fabs(zy)>lt) z.y=copysign(lt*2.0f,zy)-zy; if(fabs(zz2)>lt) z.z=copysign(lt*2.0f,zz2)-zz2; double rr2=z.x*z.x+z.y*z.y+z.z*z.z; if(rr2<me*me) z*=mff*mff/(rr2+1e-21); z*=mg; aux.DE*=fabs(mg);
		break;
	}
	case 200: // Type 200
	{
		if(fabs(zx)>ma) z.x=copysign(ma*2.0f,zx)-zx; if(fabs(zy)>ma) z.y=copysign(ma*2.0f,zy)-zy; if(fabs(zz2)>ma) z.z=copysign(ma*2.0f,zz2)-zz2; double rr2=z.x*z.x+z.y*z.y+z.z*z.z; double fR2=mb*mb; double mR2=mc*mc; if(rr2<mR2) z*=fR2/mR2; else if(rr2<fR2) z*=fR2/rr2; z*=md; z.x+=me; z.y+=mff; z.z+=mg; double th=mh*M_PI/180.0f; double cs=cos(th),sn=sin(th); double nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; aux.DE*=fabs(md);
		break;
	}
	default: break;
}