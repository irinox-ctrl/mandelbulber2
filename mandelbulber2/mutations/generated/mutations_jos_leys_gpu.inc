// Auto-generated mutation switch for system: jos_leys
// Target: GPU
// Generated mutations: 100
switch (mut->josLeysDeType)
{
	case 1: // Type 1
	{
		double k1=ja,k2=jb,k3=jc,k4=jd; double curv=(k1+k2+k3+k4)/fmax(1.0f,r); aux.DE*=(1.0f+jf*curv);
		break;
	}
	case 2: // Type 2
	{
		double phi=atan2(zy,zx); double sp=ja*exp(2.0f*M_PI*(jb*phi+jc*log(fmax(1e-10,r)))); aux.DE*=(1.0f+jf*sp);
		break;
	}
	case 3: // Type 3
	{
		double prod=1.0f; for(int k=0;k<4;k++){double dk=r+ja*(double)(k+1); prod*=fmax(0.01f,dk);} aux.DE*=(1.0f+jf*jsc/fmax(1e-10,prod));
		break;
	}
	case 4: // Type 4
	{
		double af=ja*log(fmax(1e-10,r))+jb*atan2(zy,zx); aux.DE*=(1.0f+jf*tanh(af));
		break;
	}
	case 5: // Type 5
	{
		double hyp=4.0f*M_PI*(ja-1.0f)/fmax(1e-10,rr); aux.DE*=(1.0f+jf*tanh(hyp));
		break;
	}
	case 6: // Type 6
	{
		double bel=ja*zy/fmax(1e-10,rr); aux.DE*=(1.0f+jf*tanh(bel));
		break;
	}
	case 7: // Type 7
	{
		double tr=ja*jb/fmax(1e-10,r); aux.DE*=(1.0f+jf*tanh(tr));
		break;
	}
	case 8: // Type 8
	{
		double rl=ja/(fmax(1e-10,r*r)+jb*jb); aux.DE*=(1.0f+jf*rl);
		break;
	}
	case 9: // Type 9
	{
		double bs=ja*jb*jc/fmax(1e-10,rr); aux.DE*=(1.0f+jf*tanh(bs));
		break;
	}
	case 10: // Type 10
	{
		double ew=ja*sin(jfreq*zx)*cos(jfreq*zy)/fmax(1e-10,r); aux.DE*=(1.0f+jf*ew);
		break;
	}
	case 11: // Type 11
	{
		double hc=exp(-fabs(zy))*ja/fmax(1e-10,r); aux.DE*=(1.0f+jf*hc);
		break;
	}
	case 12: // Type 12
	{
		double q2=fmax(1.0f,ja); double fr2=1.0f/(2.0f*q2*q2); aux.DE*=(1.0f+jf*fr2/fmax(1e-10,r));
		break;
	}
	case 13: // Type 13
	{
		double med=(zx+zy)/(fmax(1e-10,2.0f*r)); aux.DE*=(1.0f+jf*ja*med);
		break;
	}
	case 14: // Type 14
	{
		double jt=ja*sin(M_PI*zx/fmax(0.01f,jb))*sin(M_PI*zy/fmax(0.01f,jc)); aux.DE*=(1.0f+jf*jt/fmax(1e-10,rr));
		break;
	}
	case 15: // Type 15
	{
		double eta=exp(M_PI*zy/(12.0f*fmax(0.01f,ja))); for(int n=1;n<8;n++) eta*=(1.0f-exp(-2.0f*M_PI*n*fabs(zy)/fmax(0.01f,ja))); aux.DE*=(1.0f+jf*fabs(eta));
		break;
	}
	case 16: // Type 16
	{
		double wp=1.0f/(rr+1e-10); for(int n=1;n<6;n++){double dn2=(zx-n*ja)*(zx-n*ja)+(zy-n*jb)*(zy-n*jb)+zz2*zz2; wp+=1.0f/fmax(1e-10,dn2)-1.0f/(n*n*ja*ja+n*n*jb*jb+1e-10);} aux.DE*=(1.0f+jf*fabs(wp));
		break;
	}
	case 17: // Type 17
	{
		double th=0.0f; for(int n=0;n<8;n++){double qn=exp(-M_PI*n*n*fabs(zy)/fmax(0.01f,ja)); th+=qn*cos(2.0f*M_PI*n*zx/fmax(0.01f,ja));} aux.DE*=(1.0f+jf*fabs(th));
		break;
	}
	case 18: // Type 18
	{
		double eis=0.0f; for(int m=-3;m<=3;m++) for(int n=-3;n<=3;n++){if(m==0&&n==0)continue; double dn=m*ja+n*jb; eis+=1.0f/fmax(1e-10,pow(fabs(dn*dn+rr),jc));} aux.DE*=(1.0f+jf*fabs(eis));
		break;
	}
	case 19: // Type 19
	{
		double hek=ja*sin(jfreq*r)*cos(jfreq*atan2(zy,zx)+jph); aux.DE*=(1.0f+jf*hek/fmax(1e-10,r));
		break;
	}
	case 20: // Type 20
	{
		double maas=ja*sin(jfreq*log(fmax(1e-10,r)))*cos(jfreq*atan2(zy,zx)); aux.DE*=(1.0f+jf*maas);
		break;
	}
	case 21: // Type 21
	{
		double selb=1.0f; for(int k=1;k<=5;k++){selb*=(1.0f-exp(-ja*k*r));} aux.DE*=(1.0f+jf*(1.0f-fabs(selb)));
		break;
	}
	case 22: // Type 22
	{
		double ruel=1.0f; for(int k=1;k<=5;k++){ruel*=(1.0f-exp(-ja*k*log(fmax(1e-10,r))));} aux.DE*=(1.0f+jf*fabs(ruel));
		break;
	}
	case 23: // Type 23
	{
		double dz=ja*sin(jfreq*r)*exp(-jb*r); aux.DE*=(1.0f+jf*dz);
		break;
	}
	case 24: // Type 24
	{
		double gut=0.0f; for(int p=1;p<=5;p++){gut+=ja*cos(jfreq*p*r+jph)/fmax(1.0f,(double)p);} aux.DE*=(1.0f+jf*gut/fmax(1e-10,r));
		break;
	}
	case 25: // Type 25
	{
		double berry=ja*zy*zz2/fmax(1e-10,rr*r); aux.DE*=(1.0f+jf*berry);
		break;
	}
	case 26: // Type 26
	{
		double hann=ja*zx*zy/fmax(1e-10,rr); aux.DE*=(1.0f+jf*hann);
		break;
	}
	case 27: // Type 27
	{
		double ab_ph=ja*atan2(zy,zx)/fmax(1e-10,r); aux.DE*=(1.0f+jf*ab_ph);
		break;
	}
	case 28: // Type 28
	{
		double ac_ph=ja*jb*zz2/fmax(1e-10,rr); aux.DE*=(1.0f+jf*ac_ph);
		break;
	}
	case 29: // Type 29
	{
		double sab=ja*sin(jfreq*r)*zy/fmax(1e-10,rr); aux.DE*=(1.0f+jf*sab);
		break;
	}
	case 30: // Type 30
	{
		double hmw=ja*(zx*zy-zy*zz2)/fmax(1e-10,rr*r); aux.DE*=(1.0f+jf*hmw);
		break;
	}
	case 31: // Type 31
	{
		double ana=ja*sin(jfreq*rr+jph)/fmax(1e-10,r); aux.DE*=(1.0f+jf*ana);
		break;
	}
	case 32: // Type 32
	{
		double panch=ja*cos(jfreq*zx)*cos(jfreq*zy)*cos(jfreq*zz2); aux.DE*=(1.0f+jf*panch/fmax(1e-10,r));
		break;
	}
	case 33: // Type 33
	{
		double mt=ja/(2.0f*fmax(1e-10,fabs(zx-zy))); aux.DE*=(1.0f+jf*tanh(mt));
		break;
	}
	case 34: // Type 34
	{
		double ml=M_PI*ja/(2.0f*fmax(1e-10,r)); aux.DE*=(1.0f+jf*tanh(ml));
		break;
	}
	case 35: // Type 35
	{
		double sw=ja*jb/(fmax(1e-10,r)*jc); aux.DE*=(1.0f+jf*tanh(sw));
		break;
	}
	case 36: // Type 36
	{
		double pw=ja*exp(-jb*rr); aux.DE*=(1.0f+jf*pw);
		break;
	}
	case 37: // Type 37
	{
		double gp=ja*sqrt(fmax(0.0f,r/jb)); aux.DE*=(1.0f+jf*tanh(gp));
		break;
	}
	case 38: // Type 38
	{
		double rov=ja*sin(jfreq*zx+jph)*cos(jfreq*zy); aux.DE*=(1.0f+jf*rov/fmax(1e-10,r));
		break;
	}
	case 39: // Type 39
	{
		double barb=ja*sqrt(fmax(0.0f,zx*zx+zy*zy))/fmax(1e-10,r); aux.DE*=(1.0f+jf*barb);
		break;
	}
	case 40: // Type 40
	{
		double con=ja*exp(-jb*fabs(zz2))*sin(jfreq*r); aux.DE*=(1.0f+jf*con);
		break;
	}
	case 41: // Type 41
	{
		double ach=ja*sin(jfreq*zx)*sin(jfreq*zy)*cos(jfreq*zz2)/fmax(1e-10,r); aux.DE*=(1.0f+jf*ach);
		break;
	}
	case 42: // Type 42
	{
		double que=ja/(fmax(1e-10,rr)); aux.DE*=(1.0f+jf*que);
		break;
	}
	case 43: // Type 43
	{
		double rw=0.0f; for(int n=1;n<=8;n++){rw+=cos(jfreq*n*zx+jph*n)*exp(-jb*n);} aux.DE*=(1.0f+jf*ja*rw/fmax(1e-10,r));
		break;
	}
	case 44: // Type 44
	{
		double nd=ja*floor(sin(jfreq*zx)*sin(jfreq*zy)*4.0f+2.0f)/4.0f; aux.DE*=(1.0f+jf*nd);
		break;
	}
	case 45: // Type 45
	{
		double nl=ja*fabs(sin(jfreq*zx)*cos(jfreq*zy))*jb; aux.DE*=(1.0f+jf*nl/fmax(1e-10,r));
		break;
	}
	case 46: // Type 46
	{
		double pc=ja*(tanh(jb*(r-jc))+1.0f)*0.5f; aux.DE*=(1.0f+jf*pc);
		break;
	}
	case 47: // Type 47
	{
		double ip=ja*tanh(jb*(sin(jfreq*zx)+sin(jfreq*zy)+sin(jfreq*zz2))); aux.DE*=(1.0f+jf*ip);
		break;
	}
	case 48: // Type 48
	{
		double cle=ja*sin(jfreq*atan2(zy,zx))*exp(-jb*r); aux.DE*=(1.0f+jf*cle);
		break;
	}
	case 49: // Type 49
	{
		double sle=ja*zy/(fmax(1e-10,rr))*exp(-jb*fabs(zx)); aux.DE*=(1.0f+jf*sle);
		break;
	}
	case 50: // Type 50
	{
		double gff=ja*cos(jfreq*zx)*cos(jfreq*zy)/fmax(1e-10,r); aux.DE*=(1.0f+jf*gff);
		break;
	}
	case 51: // Type 51
	{
		double lqg=ja*exp(fmin(jb*sin(jfreq*r+jph),20.0f)); aux.DE*=(1.0f+jf*lqg/fmax(1e-10,r));
		break;
	}
	case 52: // Type 52
	{
		double bm=ja*sqrt(fmax(0.0f,rr-jb*jb))/fmax(1e-10,rr); aux.DE*=(1.0f+jf*bm);
		break;
	}
	case 53: // Type 53
	{
		double pm2=ja*(2.0f-fabs(zx)+fabs(zy)-fabs(zz2))/fmax(1e-10,r); aux.DE*=(1.0f+jf*tanh(pm2));
		break;
	}
	case 54: // Type 54
	{
		double tt=ja*(zx*zy+zy*zz2+zz2*zx)/fmax(1e-10,rr*r); aux.DE*=(1.0f+jf*tt);
		break;
	}
	case 55: // Type 55
	{
		double jon=ja*sin(M_PI*jb*r+jph)/fmax(1e-10,r); aux.DE*=(1.0f+jf*jon);
		break;
	}
	case 56: // Type 56
	{
		double hom=ja*(sin(jfreq*zx)+sin(jfreq*zy))*jb/fmax(1e-10,rr); aux.DE*=(1.0f+jf*hom);
		break;
	}
	case 57: // Type 57
	{
		double kau=ja*tanh(jb*sin(jfreq*r)*cos(jfreq*atan2(zy,zx))); aux.DE*=(1.0f+jf*kau);
		break;
	}
	case 58: // Type 58
	{
		double cs=ja*sin(jfreq*zx)*sin(jfreq*zy)*sin(jfreq*zz2)/(fmax(1e-10,r*r)); aux.DE*=(1.0f+jf*cs);
		break;
	}
	case 59: // Type 59
	{
		double wrt=ja*jb*cos(jfreq*r+jph)/fmax(1e-10,rr); aux.DE*=(1.0f+jf*wrt);
		break;
	}
	case 60: // Type 60
	{
		double tv=ja*jb*jc/(fmax(1e-10,rr*r)); aux.DE*=(1.0f+jf*tanh(tv));
		break;
	}
	case 61: // Type 61
	{
		double cy=ja*pow(fmax(1e-10,r),jb-3.0f); aux.DE*=(1.0f+jf*cy);
		break;
	}
	case 62: // Type 62
	{
		double dw=ja/(fmax(1e-10,rr))*cos(jfreq*zz2); aux.DE*=(1.0f+jf*dw);
		break;
	}
	case 63: // Type 63
	{
		double yd=ja*jb*(zx*zy-zy*zx)/(fmax(1e-10,rr)); aux.DE*=(1.0f+jf*yd*jc);
		break;
	}
	case 64: // Type 64
	{
		double mtc=ja*sin(jfreq*zx+jph)*cos(jfreq*zy)*sin(jfreq*zz2)/fmax(1e-10,r); aux.DE*=(1.0f+jf*mtc);
		break;
	}
	case 65: // Type 65
	{
		double fus=ja*(sin(jb*zx)*sin(jc*zy)+sin(jd*zz2))/fmax(1e-10,r); aux.DE*=(1.0f+jf*fus);
		break;
	}
	case 66: // Type 66
	{
		double bra=ja*cos(jfreq*atan2(zy,zx)+jph)*cos(jfreq*atan2(zz2,r)); aux.DE*=(1.0f+jf*bra);
		break;
	}
	case 67: // Type 67
	{
		double rib=ja*sin(jfreq*r)*cos(jb*atan2(zy,zx)+jph); aux.DE*=(1.0f+jf*rib/fmax(1e-10,r));
		break;
	}
	case 68: // Type 68
	{
		double hopf=ja*jb*tanh(jc*(zx*zy+zy*zz2)); aux.DE*=(1.0f+jf*hopf/fmax(1e-10,r));
		break;
	}
	case 69: // Type 69
	{
		double qg=ja*pow(fmax(1e-10,r),-jb)*sin(jfreq*r+jph); aux.DE*=(1.0f+jf*qg);
		break;
	}
	case 70: // Type 70
	{
		double dd=ja*jb*(1.0f/(fmax(1e-10,rr))+zx*zy/(fmax(1e-10,rr*r))); aux.DE*=(1.0f+jf*tanh(dd));
		break;
	}
	case 71: // Type 71
	{
		double nich=ja*exp(-jb*rr)*sin(jfreq*zx)*cos(jfreq*zy); aux.DE*=(1.0f+jf*nich);
		break;
	}
	case 72: // Type 72
	{
		double rack=ja*(zx*zx-zy*zy)/(fmax(1e-10,rr))*jb; aux.DE*=(1.0f+jf*rack);
		break;
	}
	case 73: // Type 73
	{
		double quan=ja*(zx*zx*zx-3.0f*zx*zy*zy)/(fmax(1e-10,rr*r))*jb; aux.DE*=(1.0f+jf*quan);
		break;
	}
	case 74: // Type 74
	{
		double biq=ja*sin(jfreq*(zx+zy))*cos(jfreq*(zx-zy))/fmax(1e-10,r); aux.DE*=(1.0f+jf*biq);
		break;
	}
	case 75: // Type 75
	{
		double ske=ja*jb*sin(jfreq*r+jph)/(fmax(1e-10,rr)); aux.DE*=(1.0f+jf*ske);
		break;
	}
	case 76: // Type 76
	{
		double khov=ja*pow(fmax(1e-10,sin(jfreq*r)),2.0f)*jb/fmax(1e-10,r); aux.DE*=(1.0f+jf*khov);
		break;
	}
	case 77: // Type 77
	{
		double hf=ja*exp(-jb*r)*cos(jfreq*zz2+jph); aux.DE*=(1.0f+jf*hf);
		break;
	}
	case 78: // Type 78
	{
		double kf=ja*atan2(zy,zx)*exp(-jb*fabs(zz2))/M_PI; aux.DE*=(1.0f+jf*kf/fmax(1e-10,r));
		break;
	}
	case 79: // Type 79
	{
		double ech2=ja*sin(jfreq*zx)*exp(-jb*zy)*cos(jfreq*zz2)/fmax(1e-10,r); aux.DE*=(1.0f+jf*ech2);
		break;
	}
	case 80: // Type 80
	{
		double sft=ja*cos(jfreq*r)*sin(jfreq*atan2(zy,zx)+jph)/fmax(1e-10,r); aux.DE*=(1.0f+jf*sft);
		break;
	}
	case 81: // Type 81
	{
		double lag=ja*(zx*zy+zy*zz2)/(fmax(1e-10,rr))*jb; aux.DE*=(1.0f+jf*lag);
		break;
	}
	case 82: // Type 82
	{
		double fuk=ja*sin(jb*zx)*cos(jc*zy)*sin(jd*zz2)/fmax(1e-10,r); aux.DE*=(1.0f+jf*fuk);
		break;
	}
	case 83: // Type 83
	{
		double mir=ja*(sin(jfreq*zx)*sin(jfreq*zy)-cos(jfreq*zz2))/fmax(1e-10,r); aux.DE*=(1.0f+jf*mir);
		break;
	}
	case 84: // Type 84
	{
		double hmir=ja*cos(jfreq*(zx+zy+zz2)+jph)/fmax(1e-10,r); aux.DE*=(1.0f+jf*hmir);
		break;
	}
	case 85: // Type 85
	{
		double syz=ja*sin(jfreq*r)*sin(jfreq*atan2(zy,zx))*cos(jfreq*zz2/fmax(0.01f,jb)); aux.DE*=(1.0f+jf*syz);
		break;
	}
	case 86: // Type 86
	{
		double slag=ja*cos(jfreq*zx+jph)*jb; aux.DE*=(1.0f+jf*slag/fmax(1e-10,r));
		break;
	}
	case 87: // Type 87
	{
		double g2=ja*sin(jfreq*zx)*sin(jfreq*zy)*sin(jfreq*zz2)*jb; aux.DE*=(1.0f+jf*g2/fmax(1e-10,rr));
		break;
	}
	case 88: // Type 88
	{
		double sp7=ja*cos(jfreq*(zx*zy+zy*zz2+zz2*zx)/fmax(1e-10,rr)+jph); aux.DE*=(1.0f+jf*sp7);
		break;
	}
	case 89: // Type 89
	{
		double cy2=ja*exp(-jb*rr)*jc; aux.DE*=(1.0f+jf*cy2);
		break;
	}
	case 90: // Type 90
	{
		double hkah=ja*(zx*zx-zy*zy+zz2*zz2)/(fmax(1e-10,rr*r))*jb; aux.DE*=(1.0f+jf*hkah);
		break;
	}
	case 91: // Type 91
	{
		double qkah=ja*jb*(zx*zy*zz2)/(fmax(1e-10,rr*rr)); aux.DE*=(1.0f+jf*tanh(qkah));
		break;
	}
	case 92: // Type 92
	{
		double sas=ja*sqrt(fmax(0.0f,r-jb))/fmax(1e-10,r); aux.DE*=(1.0f+jf*sas);
		break;
	}
	case 93: // Type 93
	{
		double s3s=ja*(sin(jfreq*zx)+sin(jfreq*zy)+sin(jfreq*zz2))/(3.0f*fmax(1e-10,r)); aux.DE*=(1.0f+jf*s3s);
		break;
	}
	case 94: // Type 94
	{
		double exh=ja*pow(fmax(1e-10,r),-jb)*cos(jfreq*r+jph); aux.DE*=(1.0f+jf*exh);
		break;
	}
	case 95: // Type 95
	{
		double joy=ja*sin(jfreq*zx/fmax(0.01f,jb))*sin(jfreq*zy/fmax(0.01f,jc))*sin(jfreq*zz2/fmax(0.01f,jd)); aux.DE*=(1.0f+jf*joy);
		break;
	}
	case 96: // Type 96
	{
		double kov=ja*exp(-jb*fabs(zz2))*cos(jfreq*sqrt(fmax(0.0f,zx*zx+zy*zy))); aux.DE*=(1.0f+jf*kov);
		break;
	}
	case 97: // Type 97
	{
		double chnp=ja*jb*tanh(jc*r-jd); aux.DE*=(1.0f+jf*chnp/fmax(1e-10,r));
		break;
	}
	case 98: // Type 98
	{
		double bs=ja*exp(-jb*r)*cos(jfreq*r+jph)*jc; aux.DE*=(1.0f+jf*bs);
		break;
	}
	case 99: // Type 99
	{
		double ah=ja*jb/(fmax(1e-10,rr))*cos(jfreq*atan2(zy,zx)+jph); aux.DE*=(1.0f+jf*ah);
		break;
	}
	case 100: // Type 100
	{
		double gh=ja*jb*jc/fmax(1e-10,r)*sin(jfreq*zz2+jph); aux.DE*=(1.0f+jf*gh);
		break;
	}
	default: break;
}