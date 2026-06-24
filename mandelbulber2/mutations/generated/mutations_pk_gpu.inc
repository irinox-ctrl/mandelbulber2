// Auto-generated mutation switch for system: pk
// Target: GPU
// Generated mutations: 100
switch (mut->pseudoKleinianDeType)
{
	case 1: // Type 1
	{
		double mu=pa*zy/fmax(1e-10,rr); aux.DE*=(1.0f+pf*tanh(mu));
		break;
	}
	case 2: // Type 2
	{
		double bers=pa*log(fmax(1e-10,r))*pb; aux.DE*=(1.0f+pf*tanh(bers));
		break;
	}
	case 3: // Type 3
	{
		double eq=pa*sin(pfreq*zx)*cos(pfreq*zy); aux.DE*=(1.0f+pf*eq/fmax(1e-10,r));
		break;
	}
	case 4: // Type 4
	{
		double bc=pa*pb*zy/fmax(1e-10,rr); aux.DE*=(1.0f+pf*bc);
		break;
	}
	case 5: // Type 5
	{
		double ham=pa*exp(-pb*r)*sin(pfreq*zx); aux.DE*=(1.0f+pf*ham);
		break;
	}
	case 6: // Type 6
	{
		double wp=pa*pb/(fmax(1e-10,rr)); aux.DE*=(1.0f+pf*wp);
		break;
	}
	case 7: // Type 7
	{
		double tm=pa*fabs(zx-zy)/fmax(1e-10,r); aux.DE*=(1.0f+pf*tanh(tm));
		break;
	}
	case 8: // Type 8
	{
		double kob=pa*tanh(pb*r)/fmax(1e-10,r); aux.DE*=(1.0f+pf*kob);
		break;
	}
	case 9: // Type 9
	{
		double car=pa*fabs(sin(pfreq*r))/fmax(1e-10,r); aux.DE*=(1.0f+pf*car);
		break;
	}
	case 10: // Type 10
	{
		double berg=pa*pb*cos(pfreq*zx+pph)*cos(pfreq*zy)/fmax(1e-10,rr); aux.DE*=(1.0f+pf*berg);
		break;
	}
	case 11: // Type 11
	{
		double ke=pa*pb/fmax(1e-10,r)*tanh(pc*rr); aux.DE*=(1.0f+pf*ke);
		break;
	}
	case 12: // Type 12
	{
		double csc2=pa*tanh(pb*(r-pc)); aux.DE*=(1.0f+pf*csc2);
		break;
	}
	case 13: // Type 13
	{
		double duy=pa*pb*exp(-pc*rr); aux.DE*=(1.0f+pf*duy);
		break;
	}
	case 14: // Type 14
	{
		double hk=pa*sin(pfreq*zx)*cos(pfreq*zy)*exp(-pb*fabs(zz2)); aux.DE*=(1.0f+pf*hk);
		break;
	}
	case 15: // Type 15
	{
		double nah=pa*pb*(zx*zy+zy*zz2)/(fmax(1e-10,rr*r)); aux.DE*=(1.0f+pf*nah);
		break;
	}
	case 16: // Type 16
	{
		double hm=pa*exp(-pb*rr)*cos(pfreq*r+pph); aux.DE*=(1.0f+pf*hm);
		break;
	}
	case 17: // Type 17
	{
		double ms=pa*(1.0f-zz2/fmax(1e-10,r)); aux.DE*=(1.0f+pf*ms*pb);
		break;
	}
	case 18: // Type 18
	{
		double cmc=pa*cos(pfreq*zx)*cos(pfreq*zy)*pb; aux.DE*=(1.0f+pf*cmc/fmax(1e-10,r));
		break;
	}
	case 19: // Type 19
	{
		double wil=pa*(zx*zx+zy*zy)/(fmax(1e-10,rr*r))*pb; aux.DE*=(1.0f+pf*wil);
		break;
	}
	case 20: // Type 20
	{
		double iso=pa*cos(pfreq*zx+pph)*cos(pfreq*zy)*pb; aux.DE*=(1.0f+pf*iso);
		break;
	}
	case 21: // Type 21
	{
		double lax=pa*sin(pfreq*zx)*cos(pfreq*zy)*sin(pfreq*zz2)/fmax(1e-10,r); aux.DE*=(1.0f+pf*lax);
		break;
	}
	case 22: // Type 22
	{
		double bac=pa*exp(-pb*r)*sin(pfreq*r+pph); aux.DE*=(1.0f+pf*bac);
		break;
	}
	case 23: // Type 23
	{
		double dar=pa*pb*cos(pfreq*r+pph)/fmax(1e-10,rr); aux.DE*=(1.0f+pf*dar);
		break;
	}
	case 24: // Type 24
	{
		double mou=pa*sin(pfreq*zx)*sin(pfreq*zy)/fmax(1e-10,r); aux.DE*=(1.0f+pf*mou);
		break;
	}
	case 25: // Type 25
	{
		double hir=pa*pb*exp(-pc*rr)*cos(pfreq*r); aux.DE*=(1.0f+pf*hir);
		break;
	}
	case 26: // Type 26
	{
		double sat=pa*sin(pfreq*zx+pph)*cos(pfreq*zy)*sin(pfreq*zz2)/fmax(1e-10,r); aux.DE*=(1.0f+pf*sat);
		break;
	}
	case 27: // Type 27
	{
		double kp=pa*(sin(pfreq*zx)*cos(pfreq*zy)+sin(pfreq*zy)*cos(pfreq*zz2))/fmax(1e-10,r); aux.DE*=(1.0f+pf*kp);
		break;
	}
	case 28: // Type 28
	{
		double kdv=pa*sin(pfreq*zx+pph)*exp(-pb*zy*zy)/fmax(1e-10,r); aux.DE*=(1.0f+pf*kdv);
		break;
	}
	case 29: // Type 29
	{
		double nls=pa*exp(-pb*(zx*zx+zy*zy))*cos(pfreq*zz2+pph); aux.DE*=(1.0f+pf*nls);
		break;
	}
	case 30: // Type 30
	{
		double sg=pa*sin(sin(pfreq*zx+pph))*pb; aux.DE*=(1.0f+pf*sg/fmax(1e-10,r));
		break;
	}
	case 31: // Type 31
	{
		double toda=pa*exp(pb*(zx-zy))-pa*exp(pb*(zy-zz2)); aux.DE*=(1.0f+pf*tanh(toda)/fmax(1e-10,r));
		break;
	}
	case 32: // Type 32
	{
		double cm=0.0f; {double d1=zx-zy; double d2=zy-zz2; double d3=zx-zz2; cm=pa*(1.0f/fmax(1e-10,d1*d1*d1)+1.0f/fmax(1e-10,d2*d2*d2)+1.0f/fmax(1e-10,d3*d3*d3));} aux.DE*=(1.0f+pf*tanh(cm));
		break;
	}
	case 33: // Type 33
	{
		double rs=pa*tanh(pb*(zx-zy))*tanh(pb*(zy-zz2))/fmax(1e-10,r); aux.DE*=(1.0f+pf*rs);
		break;
	}
	case 34: // Type 34
	{
		double hs=pa*pb*(zx*zy+zy*zz2+zz2*zx)/(fmax(1e-10,rr*r)); aux.DE*=(1.0f+pf*hs);
		break;
	}
	case 35: // Type 35
	{
		double bm=pa*sin(pfreq*zx)*sin(pfreq*zy)*pb/fmax(1e-10,r); aux.DE*=(1.0f+pf*bm);
		break;
	}
	case 36: // Type 36
	{
		double aci=pa*sin(pfreq*r+pph)*cos(pfreq*atan2(zy,zx))/fmax(1e-10,r); aux.DE*=(1.0f+pf*aci);
		break;
	}
	case 37: // Type 37
	{
		double sep=pa*(sin(pb*zx)+sin(pc*zy)+sin(pd*zz2))/fmax(1e-10,r); aux.DE*=(1.0f+pf*sep);
		break;
	}
	case 38: // Type 38
	{
		double aa=pa*cos(pfreq*r)*pfreq/fmax(1e-10,r); aux.DE*=(1.0f+pf*aa);
		break;
	}
	case 39: // Type 39
	{
		double kam=pa*cos(pfreq*r+pph)*(1.0f-pb/fmax(1e-10,r)); aux.DE*=(1.0f+pf*kam);
		break;
	}
	case 40: // Type 40
	{
		double nek=pa*exp(-1.0f/fmax(1e-10,pow(fmax(1e-10,pb),pc))); aux.DE*=(1.0f+pf*nek);
		break;
	}
	case 41: // Type 41
	{
		double ard=pa*sin(pfreq*zx)*cos(pfreq*zy)*sin(pfreq*zz2)/fmax(1e-10,rr); aux.DE*=(1.0f+pf*ard);
		break;
	}
	case 42: // Type 42
	{
		double abm=pa*fabs(sin(pfreq*zx+pph))/fmax(1e-10,r); aux.DE*=(1.0f+pf*abm);
		break;
	}
	case 43: // Type 43
	{
		double mse=pa*pb*exp(-pc*rr)*sin(pfreq*zx); aux.DE*=(1.0f+pf*mse);
		break;
	}
	case 44: // Type 44
	{
		double pei=pa*(1.0f-exp(-pb*fabs(zx-zy)))/fmax(1e-10,r); aux.DE*=(1.0f+pf*pei);
		break;
	}
	case 45: // Type 45
	{
		double fk=pa*sin(pfreq*zx+pph)*cos(pb*zy); aux.DE*=(1.0f+pf*fk/fmax(1e-10,r));
		break;
	}
	case 46: // Type 46
	{
		double sm=pa*sin(pfreq*atan2(zy,zx)+pph)*pb; aux.DE*=(1.0f+pf*sm/fmax(1e-10,r));
		break;
	}
	case 47: // Type 47
	{
		double chi=pa*tanh(pb*(r-pc)); aux.DE*=(1.0f+pf*chi);
		break;
	}
	case 48: // Type 48
	{
		double gre=0.5f*(1.0f-pa*cos(pfreq*r+pph)/fmax(1e-10,r)); aux.DE*=(1.0f+pf*gre);
		break;
	}
	case 49: // Type 49
	{
		double rg=pa*pow(fmax(1e-10,r),-pb)*cos(pfreq*log(fmax(1e-10,r))+pph); aux.DE*=(1.0f+pf*rg);
		break;
	}
	case 50: // Type 50
	{
		double fg=pa*4.669201609f*sin(pfreq*r+pph)/(fmax(1e-10,r)); aux.DE*=(1.0f+pf*fg);
		break;
	}
	case 51: // Type 51
	{
		double sh3=pa*floor(sin(pfreq*zx)*3.0f+1.5f)/3.0f; aux.DE*=(1.0f+pf*sh3);
		break;
	}
	case 52: // Type 52
	{
		double sar=pa*(sin(pfreq*zx)*sin(pfreq*zy)*sin(pfreq*zz2)>0.0f?1.0f:-1.0f)*pb; aux.DE*=(1.0f+pf*sar/fmax(1e-10,r));
		break;
	}
	case 53: // Type 53
	{
		double sml=pa*tanh(pb*zx)*tanh(pb*zy); aux.DE*=(1.0f+pf*sml);
		break;
	}
	case 54: // Type 54
	{
		double ano=pa*fabs(fmod(pb*zx+pc*zy,1.0f)-0.5f)*4.0f; aux.DE*=(1.0f+pf*ano/fmax(1e-10,r));
		break;
	}
	case 55: // Type 55
	{
		double axa=pa*exp(-pb*r)*cos(pfreq*r+pph); aux.DE*=(1.0f+pf*axa);
		break;
	}
	case 56: // Type 56
	{
		double srb=pa*pb*exp(-pc*rr)/fmax(1e-10,r); aux.DE*=(1.0f+pf*srb);
		break;
	}
	case 57: // Type 57
	{
		double pes=0.0f; {double lya=pa*log(fmax(1e-10,r)); pes=lya*pb;} aux.DE*=(1.0f+pf*tanh(pes));
		break;
	}
	case 58: // Type 58
	{
		double ly=pa*pb*log(fmax(1e-10,r))/fmax(1e-10,r); aux.DE*=(1.0f+pf*tanh(ly));
		break;
	}
	case 59: // Type 59
	{
		double yt=pa*exp(-pb*r)*sin(pfreq*r+pph); aux.DE*=(1.0f+pf*yt);
		break;
	}
	case 60: // Type 60
	{
		double to=pa*pb*sin(pfreq*zx)*sin(pfreq*zy)/(fmax(1e-10,rr)); aux.DE*=(1.0f+pf*to);
		break;
	}
	case 61: // Type 61
	{
		double rpf=pa*exp(-pb*r)/fmax(1e-10,r); aux.DE*=(1.0f+pf*rpf);
		break;
	}
	case 62: // Type 62
	{
		double thf=pa*tanh(pb*(r-pc))*pd; aux.DE*=(1.0f+pf*thf);
		break;
	}
	case 63: // Type 63
	{
		double gib=pa*exp(-pb*rr)*pc; aux.DE*=(1.0f+pf*gib);
		break;
	}
	case 64: // Type 64
	{
		double eqs=pa*cos(pfreq*r+pph)/(fmax(1e-10,r)); aux.DE*=(1.0f+pf*eqs);
		break;
	}
	case 65: // Type 65
	{
		double pht=pa*(1.0f/(1.0f+exp(-pb*(r-pc)))-0.5f)*2.0f; aux.DE*=(1.0f+pf*pht);
		break;
	}
	case 66: // Type 66
	{
		double brf=pa*exp(-pb*r)*cos(pfreq*atan2(zy,zx)+pph); aux.DE*=(1.0f+pf*brf);
		break;
	}
	case 67: // Type 67
	{
		double spc=pa*sin(pfreq*zx)*cos(pfreq*zy)*sin(pfreq*zz2)*pb; aux.DE*=(1.0f+pf*spc/fmax(1e-10,r));
		break;
	}
	case 68: // Type 68
	{
		double sha=pa*exp(-pb*fabs(r-pc)); aux.DE*=(1.0f+pf*sha);
		break;
	}
	case 69: // Type 69
	{
		double sst=pa*cos(pfreq*r+pph)*exp(-pb*r); aux.DE*=(1.0f+pf*sst);
		break;
	}
	case 70: // Type 70
	{
		double oms=pa*sin(pfreq*zx)*sin(pfreq*zy)*pb/fmax(1e-10,rr); aux.DE*=(1.0f+pf*oms);
		break;
	}
	case 71: // Type 71
	{
		double mss=pa*exp(-pb*r)*(1.0f-cos(pfreq*r)); aux.DE*=(1.0f+pf*mss);
		break;
	}
	case 72: // Type 72
	{
		double gfl=-pa*pb*(zx+zy+zz2)/fmax(1e-10,r*r); aux.DE*=(1.0f+pf*tanh(gfl));
		break;
	}
	case 73: // Type 73
	{
		double mor=pa*(r-pb)*(r-pb)*exp(-pc*r); aux.DE*=(1.0f+pf*mor/fmax(1e-10,r));
		break;
	}
	case 74: // Type 74
	{
		double moh=pa*exp(-pb*rr)*sin(pfreq*r+pph); aux.DE*=(1.0f+pf*moh);
		break;
	}
	case 75: // Type 75
	{
		double flo=pa*sin(pfreq*zx)*cos(pfreq*zy)*pb; aux.DE*=(1.0f+pf*flo/fmax(1e-10,r));
		break;
	}
	case 76: // Type 76
	{
		double sca=pa*pb*r*r/(fmax(1e-10,r*r+pc*pc)); aux.DE*=(1.0f+pf*sca);
		break;
	}
	case 77: // Type 77
	{
		double hof=pa*pb/fmax(1e-10,r); aux.DE*=(1.0f+pf*tanh(hof));
		break;
	}
	case 78: // Type 78
	{
		double hz=pa*M_PI*pb/(2.0f*fmax(1e-10,r)); aux.DE*=(1.0f+pf*tanh(hz));
		break;
	}
	case 79: // Type 79
	{
		double ekh=pa*sin(pfreq*r+pph)*pb/fmax(1e-10,r); aux.DE*=(1.0f+pf*ekh);
		break;
	}
	case 80: // Type 80
	{
		double nsq=pa*pb*(1.0f-r/fmax(1e-10,pc)); aux.DE*=(1.0f+pf*tanh(nsq));
		break;
	}
	case 81: // Type 81
	{
		double emb=pa*pb*sin(pfreq*r+pph)/fmax(1e-10,rr); aux.DE*=(1.0f+pf*emb);
		break;
	}
	case 82: // Type 82
	{
		double echc=pa*sin(pfreq*zx)*cos(pfreq*zy)*pb/fmax(1e-10,r); aux.DE*=(1.0f+pf*echc);
		break;
	}
	case 83: // Type 83
	{
		double fib=pa*sin(pfreq*r)*cos(1.618033988749f*pfreq*r+pph)/fmax(1e-10,r); aux.DE*=(1.0f+pf*fib);
		break;
	}
	case 84: // Type 84
	{
		double hut=pa*pb*sin(pfreq*atan2(zy,zx)+pph)/fmax(1e-10,r); aux.DE*=(1.0f+pf*hut);
		break;
	}
	case 85: // Type 85
	{
		double cmk=pa*cos(pfreq*r)*exp(-pb*r)*pc; aux.DE*=(1.0f+pf*cmk);
		break;
	}
	case 86: // Type 86
	{
		double vfc=pa*pb*sin(pfreq*r+pph)/(fmax(1e-10,r*r)); aux.DE*=(1.0f+pf*vfc);
		break;
	}
	case 87: // Type 87
	{
		double pol=pa*exp(-pb*rr)*cos(pfreq*r)*pc; aux.DE*=(1.0f+pf*pol);
		break;
	}
	case 88: // Type 88
	{
		double scc=pa*tanh(pb*r)*cos(pfreq*r+pph)/fmax(1e-10,r); aux.DE*=(1.0f+pf*scc);
		break;
	}
	case 89: // Type 89
	{
		double gwi=pa*pb*sin(pfreq*zx)*sin(pfreq*zy)*sin(pfreq*zz2)/(fmax(1e-10,rr)); aux.DE*=(1.0f+pf*gwi);
		break;
	}
	case 90: // Type 90
	{
		double qco=pa*cos(pfreq*(zx+zy+zz2)+pph)*pb/fmax(1e-10,r); aux.DE*=(1.0f+pf*qco);
		break;
	}
	case 91: // Type 91
	{
		double msy=pa*(sin(pfreq*zx)*sin(pfreq*zy)-cos(pfreq*zz2))/fmax(1e-10,r); aux.DE*=(1.0f+pf*msy);
		break;
	}
	case 92: // Type 92
	{
		double hv=pa*exp(-pb*rr)*sin(pfreq*r+pph); aux.DE*=(1.0f+pf*hv);
		break;
	}
	case 93: // Type 93
	{
		double bat=pa*cos(pfreq*zx+pph)*cos(pfreq*zy)*cos(pfreq*zz2)/fmax(1e-10,r); aux.DE*=(1.0f+pf*bat);
		break;
	}
	case 94: // Type 94
	{
		double gpo=pa*pb*sin(pfreq*r)/(fmax(1e-10,r*r)); aux.DE*=(1.0f+pf*gpo);
		break;
	}
	case 95: // Type 95
	{
		double syzf=pa*sin(pfreq*r)*sin(pfreq*atan2(zy,zx)+pph)*pb; aux.DE*=(1.0f+pf*syzf/fmax(1e-10,r));
		break;
	}
	case 96: // Type 96
	{
		double gs=pa*exp(-pb*fabs(zz2))*cos(pfreq*sqrt(fmax(0.0f,zx*zx+zy*zy))+pph); aux.DE*=(1.0f+pf*gs);
		break;
	}
	case 97: // Type 97
	{
		double scd=pa*pb*tanh(pc*sin(pfreq*r+pph)); aux.DE*=(1.0f+pf*scd/fmax(1e-10,r));
		break;
	}
	case 98: // Type 98
	{
		double thf2=pa*sin(pfreq*zx+pph)*cos(pfreq*zy)*pb; aux.DE*=(1.0f+pf*thf2/fmax(1e-10,r));
		break;
	}
	case 99: // Type 99
	{
		double cla=pa*pb*(zx*zy+zy*zz2+zz2*zx)/(fmax(1e-10,rr*r)); aux.DE*=(1.0f+pf*cla);
		break;
	}
	case 100: // Type 100
	{
		double clv=pa*sin(pfreq*(zx*zy+zy*zz2)/fmax(1e-10,rr)+pph)*pb; aux.DE*=(1.0f+pf*clv);
		break;
	}
	default: break;
}