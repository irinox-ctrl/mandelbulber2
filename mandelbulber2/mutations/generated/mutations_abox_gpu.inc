// Auto-generated mutation switch for system: abox
// Target: GPU
// Generated mutations: 400
switch (mut->aboxType)
{
	case 1: // Type 1
	{
		aux.DE *= (1.0f + af * aa);
		break;
	}
	case 2: // Type 2
	{
		aux.DE *= (1.0f + af * aa * sin(ab * r));
		break;
	}
	case 3: // Type 3
	{
		aux.DE *= (1.0f + af * aa * cos(ab * r));
		break;
	}
	case 4: // Type 4
	{
		aux.DE *= (1.0f + af * aa * exp(-ab * r));
		break;
	}
	case 5: // Type 5
	{
		aux.DE *= (1.0f + af * aa * exp(-ab * rr));
		break;
	}
	case 6: // Type 6
	{
		aux.DE *= (1.0f + af * aa * log(1.0f + ab * r));
		break;
	}
	case 7: // Type 7
	{
		aux.DE *= (1.0f + af * aa * tanh(ab * r));
		break;
	}
	case 8: // Type 8
	{
		aux.DE *= (1.0f + af * aa * sin(ab * zx) * cos(ac * zy));
		break;
	}
	case 9: // Type 9
	{
		aux.DE *= (1.0f + af * aa * sin(ab * zy) * cos(ac * zz2));
		break;
	}
	case 10: // Type 10
	{
		aux.DE *= (1.0f + af * aa * sin(ab * zz2) * cos(ac * zx));
		break;
	}
	case 11: // Type 11
	{
		aux.DE *= (1.0f + af * aa * (sin(ab*zx) + sin(ac*zy) + sin(ad*zz2)) / 3.0f);
		break;
	}
	case 12: // Type 12
	{
		aux.DE *= (1.0f + af * aa / (1.0f + ab * rr));
		break;
	}
	case 13: // Type 13
	{
		aux.DE *= (1.0f + af * aa * pow(r, ab - 1.0f));
		break;
	}
	case 14: // Type 14
	{
		aux.DE *= (1.0f + af * aa * fabs(sin(ab * r)));
		break;
	}
	case 15: // Type 15
	{
		aux.DE *= (1.0f + af * aa * (1.0f - exp(-ab * r)));
		break;
	}
	case 16: // Type 16
	{
		{ double sg = 1.0f/(1.0f+exp(-aa*(r-ab))); aux.DE *= (1.0f + af * sg); }
		break;
	}
	case 17: // Type 17
	{
		aux.DE *= (1.0f + af * aa * sin(ab*zx)*sin(ac*zy)*sin(ad*zz2));
		break;
	}
	case 18: // Type 18
	{
		aux.DE *= (1.0f + af * aa * cos(ab*zx)*cos(ac*zy)*cos(ad*zz2));
		break;
	}
	case 19: // Type 19
	{
		aux.DE *= (1.0f + af * aa * sin(ab*r+ac*atan2(zy,zx)));
		break;
	}
	case 20: // Type 20
	{
		aux.DE *= (1.0f + af * aa * sin(ab*r)*cos(ac*acos(zz2/r)));
		break;
	}
	case 21: // Type 21
	{
		{ double v = 0; for(int o=0;o<4;o++) v += sin(ab*pow(2.0f,o)*r)/(pow(2.0f,o)); aux.DE *= (1.0f + af * aa * v); }
		break;
	}
	case 22: // Type 22
	{
		aux.DE *= (1.0f + af * aa * (zx*zy+zy*zz2+zz2*zx)/(rr+1e-21));
		break;
	}
	case 23: // Type 23
	{
		aux.DE *= (1.0f + af * aa * fabs(zx*zy*zz2)/(r*r*r+1e-21));
		break;
	}
	case 24: // Type 24
	{
		aux.DE *= (1.0f + af * aa * sin(ab*(zx*zx-zy*zy)/(rr+1e-21)));
		break;
	}
	case 25: // Type 25
	{
		aux.DE *= (1.0f + af * aa * atan2(sqrt(zx*zx+zy*zy), zz2) / M_PI);
		break;
	}
	case 26: // Type 26
	{
		{ double rr2=rr; if(rr2<aa*aa) { double m=ab*ab/fmax(rr2,1e-21); aux.DE*=m; } aux.DE*=(1.0f+af*0.1f); }
		break;
	}
	case 27: // Type 27
	{
		{ double rr2=rr; double mR2=aa*aa; double fR2=ab*ab; if(rr2<mR2) aux.DE*=fR2/mR2; else if(rr2<fR2) aux.DE*=fR2/rr2; }
		break;
	}
	case 28: // Type 28
	{
		aux.DE *= (1.0f + af * aa * exp(-ab*(r-ac)*(r-ac)));
		break;
	}
	case 29: // Type 29
	{
		aux.DE *= (1.0f + af * aa * (1.0f/(1.0f+exp(-ab*(r-ac))) - 0.5f));
		break;
	}
	case 30: // Type 30
	{
		aux.DE *= (1.0f + af * aa * sin(ab*r)*exp(-ac*r));
		break;
	}
	case 31: // Type 31
	{
		aux.DE *= (1.0f + af * aa * fabs(sin(ab*r+ac))*exp(-ad*r));
		break;
	}
	case 32: // Type 32
	{
		{ double s = aa * sin(ab*r+ac*atan2(zy,zx)) * exp(-ad*r); aux.DE *= (1.0f + af*s); }
		break;
	}
	case 33: // Type 33
	{
		aux.DE *= (1.0f + af * aa * tanh(ab*(r-ac)));
		break;
	}
	case 34: // Type 34
	{
		aux.DE *= (1.0f + af * aa * sin(ab*log(r+1e-21)));
		break;
	}
	case 35: // Type 35
	{
		aux.DE *= (1.0f + af * aa * cos(ab*log(r+1e-21)+ac));
		break;
	}
	case 36: // Type 36
	{
		{ double ph=atan2(zy,zx); double th=acos(zz2/r); aux.DE*=(1.0f+af*aa*sin(ab*ph)*sin(ac*th)); }
		break;
	}
	case 37: // Type 37
	{
		{ double ph=atan2(zy,zx); aux.DE*=(1.0f+af*aa*cos(ab*ph+ac*r)); }
		break;
	}
	case 38: // Type 38
	{
		aux.DE *= fmax(0.01f, 1.0f + af * aa * sin(ab*r) * cos(ac*r));
		break;
	}
	case 39: // Type 39
	{
		{ double d=r-aa; aux.DE*=(1.0f+af*ab*exp(-ac*d*d)); }
		break;
	}
	case 40: // Type 40
	{
		aux.DE *= (1.0f + af * aa * sin(ab*r) / (r+1e-21));
		break;
	}
	case 41: // Type 41
	{
		{ double n=sin(aa*zx)*sin(ab*zy)*sin(ac*zz2); aux.DE*=(1.0f+af*ad*n); }
		break;
	}
	case 42: // Type 42
	{
		{ double rxy=sqrt(zx*zx+zy*zy+1e-21); aux.DE*=(1.0f+af*aa*sin(ab*rxy+ac*zz2)); }
		break;
	}
	case 43: // Type 43
	{
		aux.DE *= (1.0f + af * aa * cos(ab*zx+ac*zy+ad*zz2));
		break;
	}
	case 44: // Type 44
	{
		{ double v=aa*sin(ab*r)+ac*cos(ad*r); aux.DE*=(1.0f+af*v*0.5f); }
		break;
	}
	case 45: // Type 45
	{
		aux.DE *= fmax(0.01f, 1.0f + af * aa * pow(fabs(sin(ab*r)), ac));
		break;
	}
	case 46: // Type 46
	{
		aux.DE *= (1.0f + af * aa * sin(ab*r*r/(r+1e-21)));
		break;
	}
	case 47: // Type 47
	{
		{ double f=aa+ab*sin(ac*i); aux.DE*=(1.0f+af*f); }
		break;
	}
	case 48: // Type 48
	{
		{ double rr2=rr; double minR=aa; double fixR=ab; if(rr2<minR*minR){double m=fixR*fixR/(minR*minR);aux.DE*=m;} else if(rr2<fixR*fixR){double m=fixR*fixR/rr2;aux.DE*=m;} aux.DE*=(1.0f+af*ac*sin(ad*r)); }
		break;
	}
	case 49: // Type 49
	{
		aux.DE *= (1.0f + af * aa * (sin(ab*r) + cos(ac*r*r/(r+1e-21))) * 0.5f);
		break;
	}
	case 50: // Type 50
	{
		{ double d=fabs(r-aa); double ring=exp(-ab*d*d); aux.DE*=(1.0f+af*ac*ring); }
		break;
	}
	case 51: // Type 51
	{
		aux.DE *= fabs(aa);
		break;
	}
	case 52: // Type 52
	{
		aux.DE *= fabs(aa + ab*sin(ac*i));
		break;
	}
	case 53: // Type 53
	{
		aux.DE *= fabs(aa * pow(ab, ac));
		break;
	}
	case 54: // Type 54
	{
		aux.DE *= fabs(aa + ab * r);
		break;
	}
	case 55: // Type 55
	{
		aux.DE *= fmax(0.01f, fabs(aa + ab * sin(ac * r)));
		break;
	}
	case 56: // Type 56
	{
		aux.DE *= fabs(aa + ab * exp(-ac * i));
		break;
	}
	case 57: // Type 57
	{
		aux.DE *= fabs(aa + ab * log(1.0f + ac * i));
		break;
	}
	case 58: // Type 58
	{
		{ double golden=1.6180339887f; aux.DE*=fabs(aa+ab*pow(golden,ac*i-ad)); }
		break;
	}
	case 59: // Type 59
	{
		aux.DE *= fabs(aa + ab * sin(ac * i) * cos(ad * r));
		break;
	}
	case 60: // Type 60
	{
		{ double s=aa+ab*tanh(ac*(i-ad)); aux.DE*=fabs(s); }
		break;
	}
	case 61: // Type 61
	{
		aux.DE *= fmax(0.01f, fabs(aa + ab * fmod(double(i) * ac, ad)));
		break;
	}
	case 62: // Type 62
	{
		aux.DE *= fabs(aa + ab / (1.0f + ac * i));
		break;
	}
	case 63: // Type 63
	{
		{ double ph=atan2(zy,zx); aux.DE*=fabs(aa+ab*sin(ac*ph)); }
		break;
	}
	case 64: // Type 64
	{
		aux.DE *= fabs(aa + ab * (zx*zx - zy*zy) / (rr + 1e-21));
		break;
	}
	case 65: // Type 65
	{
		aux.DE *= fabs(aa + ab * sin(ac * i * M_PI / ad));
		break;
	}
	case 66: // Type 66
	{
		{ double s=aa*(1.0f+ab*sin(ac*double(i))); aux.DE*=fabs(s); }
		break;
	}
	case 67: // Type 67
	{
		aux.DE *= fabs(aa + ab * fabs(sin(ac * r + ad * i)));
		break;
	}
	case 68: // Type 68
	{
		{ double s=aa+ab*cos(ac*r)*sin(ad*i*0.1f); aux.DE*=fabs(s); }
		break;
	}
	case 69: // Type 69
	{
		aux.DE *= fabs(aa + ab * (sin(ac*zx)+sin(ad*zy)+sin(ae*zz2))/3.0f);
		break;
	}
	case 70: // Type 70
	{
		{ double rat=aa/fmax(ab,1e-21); double s=pow(fabs(rat),ac); aux.DE*=s; }
		break;
	}
	case 71: // Type 71
	{
		aux.DE *= fmax(0.01f, fabs(aa * exp(-ab * fabs(sin(ac * r)))));
		break;
	}
	case 72: // Type 72
	{
		{ double s=aa+ab*pow(fabs(sin(ac*r)),ad); aux.DE*=fabs(s); }
		break;
	}
	case 73: // Type 73
	{
		aux.DE *= fabs(aa + ab * tanh(ac * sin(ad * r)));
		break;
	}
	case 74: // Type 74
	{
		{ double mix=0.5f+0.5f*sin(ac*i); double s=aa*(1.0f-mix)+ab*mix; aux.DE*=fabs(s); }
		break;
	}
	case 75: // Type 75
	{
		aux.DE *= fabs(aa + ab * sin(ac * r) * log(1.0f + ad * r));
		break;
	}
	case 76: // Type 76
	{
		{ double a=aa*M_PI/180.0f; aux.DE*=(1.0f+af*fabs(sin(a))); }
		break;
	}
	case 77: // Type 77
	{
		{ double a=aa*M_PI/180.0f+ab*sin(ac*i); aux.DE*=(1.0f+af*fabs(sin(a))); }
		break;
	}
	case 78: // Type 78
	{
		aux.DE *= (1.0f + af * aa * sin(ab*atan2(zy,zx)));
		break;
	}
	case 79: // Type 79
	{
		aux.DE *= (1.0f + af * aa * cos(ab*atan2(zy,zx)+ac*acos(zz2/r)));
		break;
	}
	case 80: // Type 80
	{
		{ double ph=atan2(zy,zx); double n=fmax(1.0f,aa); double s=2.0f*M_PI/n; double sector=fmod(ph+10.0f*M_PI,s)/s; aux.DE*=(1.0f+af*ab*sin(M_PI*sector)); }
		break;
	}
	case 81: // Type 81
	{
		aux.DE *= (1.0f + af * aa * fabs(sin(ab * atan2(zz2, sqrt(zx*zx+zy*zy+1e-21)))));
		break;
	}
	case 82: // Type 82
	{
		{ double q1=zx*cos(aa)-zy*sin(aa); double q2=zx*sin(aa)+zy*cos(aa); aux.DE*=(1.0f+af*ab*sin(ac*q1)*cos(ad*q2)); }
		break;
	}
	case 83: // Type 83
	{
		aux.DE *= (1.0f + af * aa * cos(ab * (zx+zy+zz2)));
		break;
	}
	case 84: // Type 84
	{
		{ double cs=cos(aa*M_PI/180.0f),sn=sin(aa*M_PI/180.0f); double rxy=sqrt(zx*zx+zy*zy+1e-21); double nph=atan2(zy,zx)+ab*sin(ac*rxy); aux.DE*=(1.0f+af*ad*sin(ae*nph)); }
		break;
	}
	case 85: // Type 85
	{
		aux.DE *= (1.0f + af * aa * sin(ab*(zx*zy+zy*zz2+zz2*zx)/(rr+1e-21)));
		break;
	}
	case 86: // Type 86
	{
		{ double gld=aa*0.618033988749895f; aux.DE*=(1.0f+af*ab*sin(ac*gld*i)); }
		break;
	}
	case 87: // Type 87
	{
		aux.DE *= (1.0f + af * aa * sin(ab*r+ac*atan2(zy,zx)+ad*i*0.1f));
		break;
	}
	case 88: // Type 88
	{
		{ double sw=fabs(zx)>fabs(zy)?zx:zy; aux.DE*=(1.0f+af*aa*sin(ab*sw)); }
		break;
	}
	case 89: // Type 89
	{
		aux.DE *= (1.0f + af * aa * cos(ab*zx*zy/(r+1e-21)));
		break;
	}
	case 90: // Type 90
	{
		{ double fld=aa*(fabs(zx)+fabs(zy)+fabs(zz2)); aux.DE*=(1.0f+af*ab*sin(fld)); }
		break;
	}
	case 91: // Type 91
	{
		aux.DE *= (1.0f + af * aa * sin(ab*i) * cos(ac*r) * sin(ad*atan2(zy,zx)));
		break;
	}
	case 92: // Type 92
	{
		{ double sym=fabs(zx-zy)+fabs(zy-zz2)+fabs(zz2-zx); aux.DE*=(1.0f+af*aa*sin(ab*sym)); }
		break;
	}
	case 93: // Type 93
	{
		aux.DE *= (1.0f + af * aa * tanh(ab*sin(ac*atan2(zy,zx))));
		break;
	}
	case 94: // Type 94
	{
		{ double det=zx*zy-zy*zz2+zz2*zx; aux.DE*=(1.0f+af*aa*sin(ab*det/(rr+1e-21))); }
		break;
	}
	case 95: // Type 95
	{
		aux.DE *= (1.0f + af * aa * sin(ab*r) * sin(ac*atan2(zy,zx)+ad*acos(zz2/r)));
		break;
	}
	case 96: // Type 96
	{
		{ double tw=aa*zz2+ab; double cs=cos(tw),sn=sin(tw); aux.DE*=(1.0f+af*ac*fabs(sn)); }
		break;
	}
	case 97: // Type 97
	{
		aux.DE *= (1.0f + af * aa * fabs(sin(ab*zx))*fabs(sin(ac*zy))*fabs(sin(ad*zz2)));
		break;
	}
	case 98: // Type 98
	{
		{ double mir=fmin(fabs(zx),fmin(fabs(zy),fabs(zz2))); aux.DE*=(1.0f+af*aa*sin(ab*mir)); }
		break;
	}
	case 99: // Type 99
	{
		{ double mx=fmax(fabs(zx),fmax(fabs(zy),fabs(zz2))); aux.DE*=(1.0f+af*aa*cos(ab*mx)); }
		break;
	}
	case 100: // Type 100
	{
		aux.DE *= (1.0f + af * aa * sin(ab*r+ac*sin(ad*r)));
		break;
	}
	case 101: // Type 101
	{
		{ double w=aa*sin(ab*r); aux.DE*=(1.0f+af*ac*fabs(w)); }
		break;
	}
	case 102: // Type 102
	{
		{ double r4=sqrt(rr+aa*aa*sin(ab*r)*sin(ab*r)); aux.DE*=(1.0f+af*ac*(r4-r)/(r+1e-21)); }
		break;
	}
	case 103: // Type 103
	{
		{ double w=aa*cos(ab*zx+ac*zy); aux.DE*=(1.0f+af*ad*w*w); }
		break;
	}
	case 104: // Type 104
	{
		{ double w=aa*sin(ab*i*0.1f); double r4=sqrt(rr+w*w); aux.DE*=(1.0f+af*ac*sin(ad*r4)); }
		break;
	}
	case 105: // Type 105
	{
		aux.DE *= (1.0f + af * aa * sin(ab*(zx*zx+zy*zy-zz2*zz2)/(rr+1e-21)));
		break;
	}
	case 106: // Type 106
	{
		{ double w=aa*sin(ab*r+ac*i*0.1f); aux.DE*=(1.0f+af*ad*exp(-ae*w*w)); }
		break;
	}
	case 107: // Type 107
	{
		{ double q=zx*zx-zy*zy; double s=2.0f*zx*zy; aux.DE*=(1.0f+af*aa*sin(ab*q/(rr+1e-21))*cos(ac*s/(rr+1e-21))); }
		break;
	}
	case 108: // Type 108
	{
		aux.DE *= (1.0f + af * aa * sin(ab*(zx*zy+ac*zz2)));
		break;
	}
	case 109: // Type 109
	{
		{ double hd=sin(aa*zx)*cos(ab*zy)+sin(ac*zy)*cos(ad*zz2)+sin(ae*zz2)*cos(aff*zx); aux.DE*=(1.0f+af*ag*hd/3.0f); }
		break;
	}
	case 110: // Type 110
	{
		{ double cr=zx*zx+zy*zy; double ci=2.0f*zx*zy; double r4=sqrt(cr*cr+ci*ci+zz2*zz2); aux.DE*=(1.0f+af*aa*sin(ab*r4)); }
		break;
	}
	case 111: // Type 111
	{
		aux.DE *= (1.0f + af * aa * tanh(ab*(zx*zx+zy*zy-zz2*zz2)));
		break;
	}
	case 112: // Type 112
	{
		aux.DE *= (1.0f + af * aa * sin(ab*zx+ac) * sin(ad*zy+ae) * cos(aff*zz2));
		break;
	}
	case 113: // Type 113
	{
		{ double p=aa*zx*zy*zz2/(r*r*r+1e-21); aux.DE*=(1.0f+af*ab*sin(ac*p)); }
		break;
	}
	case 114: // Type 114
	{
		{ double s1=sin(aa*r),s2=sin(ab*r); double w=s1*s1-s2*s2; aux.DE*=(1.0f+af*ac*w); }
		break;
	}
	case 115: // Type 115
	{
		aux.DE *= (1.0f + af * aa * cos(ab*r*r/(r+1e-21)+ac*sin(ad*r)));
		break;
	}
	case 116: // Type 116
	{
		{ double w=aa*sin(ab*(zx+zy+zz2))+ac*cos(ad*(zx-zy+zz2)); aux.DE*=(1.0f+af*w*0.5f); }
		break;
	}
	case 117: // Type 117
	{
		aux.DE *= (1.0f + af * aa * sin(ab*zx*zx/(rr+1e-21)+ac*zy*zy/(rr+1e-21)));
		break;
	}
	case 118: // Type 118
	{
		{ double v=aa*sin(ab*r)+ac*sin(ad*r)+ae*sin(aff*r); aux.DE*=(1.0f+af*v/3.0f); }
		break;
	}
	case 119: // Type 119
	{
		aux.DE *= (1.0f + af * aa * exp(-ab*fabs(zx*zy*zz2)/(r*r*r+1e-21)));
		break;
	}
	case 120: // Type 120
	{
		{ double w=aa+ab*sin(ac*r+ad*sin(ae*r)); aux.DE*=(1.0f+af*w); }
		break;
	}
	case 121: // Type 121
	{
		aux.DE *= (1.0f + af * aa * sin(ab*(r - floor(r*ac)/ac)));
		break;
	}
	case 122: // Type 122
	{
		{ double ph4=atan2(zz2,sqrt(zx*zx+zy*zy+1e-21)); aux.DE*=(1.0f+af*aa*sin(ab*ph4+ac*r)); }
		break;
	}
	case 123: // Type 123
	{
		aux.DE *= (1.0f + af * aa * fabs(sin(ab*r)*cos(ac*r)*sin(ad*r)));
		break;
	}
	case 124: // Type 124
	{
		{ double v=aa*sin(ab*zx)*cos(ac*zx)+ad*sin(ae*zy)*cos(aff*zy); aux.DE*=(1.0f+af*v*0.5f); }
		break;
	}
	case 125: // Type 125
	{
		aux.DE *= (1.0f + af * aa * (sin(ab*r)+sin(ac*r)+sin(ad*r)+sin(ae*r))/4.0f);
		break;
	}
	case 126: // Type 126
	{
		aux.DE *= (1.0f + af * aa * fabs(zx)/(r+1e-21));
		break;
	}
	case 127: // Type 127
	{
		aux.DE *= (1.0f + af * aa * fabs(zy)/(r+1e-21));
		break;
	}
	case 128: // Type 128
	{
		aux.DE *= (1.0f + af * aa * fabs(zz2)/(r+1e-21));
		break;
	}
	case 129: // Type 129
	{
		{ double orb=fmin(fabs(zx),fmin(fabs(zy),fabs(zz2))); aux.DE*=(1.0f+af*aa*sin(ab*orb)); }
		break;
	}
	case 130: // Type 130
	{
		{ double orb=fmax(fabs(zx),fmax(fabs(zy),fabs(zz2))); aux.DE*=(1.0f+af*aa*cos(ab*orb)); }
		break;
	}
	case 131: // Type 131
	{
		{ double orb=sqrt(zx*zx+zy*zy); aux.DE*=(1.0f+af*aa*sin(ab*orb)); }
		break;
	}
	case 132: // Type 132
	{
		{ double dt=fabs(sqrt(zx*zx+zy*zy)-aa); aux.DE*=(1.0f+af*ab*exp(-ac*dt*dt)); }
		break;
	}
	case 133: // Type 133
	{
		{ double ds=fmax(fabs(zx)-aa,fabs(zy)-ab); ds=fmax(ds,fabs(zz2)-ac); aux.DE*=(1.0f+af*ad*exp(-ae*ds*ds)); }
		break;
	}
	case 134: // Type 134
	{
		{ double dp=fabs(zx*cos(aa)+zy*sin(aa)-ab); aux.DE*=(1.0f+af*ac*exp(-ad*dp*dp)); }
		break;
	}
	case 135: // Type 135
	{
		{ double dl=fabs(zx-aa*zy-ab); aux.DE*=(1.0f+af*ac*exp(-ad*dl*dl)); }
		break;
	}
	case 136: // Type 136
	{
		{ double c=fabs(sin(aa*zx)+sin(ab*zy)+sin(ac*zz2))/3.0f; aux.DE*=(1.0f+af*ad*c); }
		break;
	}
	case 137: // Type 137
	{
		{ double c=fabs(sin(aa*r)*cos(ab*atan2(zy,zx))); aux.DE*=(1.0f+af*ac*c); }
		break;
	}
	case 138: // Type 138
	{
		{ double c=fabs(zx*zy+zy*zz2+zz2*zx)/(rr+1e-21); aux.DE*=(1.0f+af*aa*c); }
		break;
	}
	case 139: // Type 139
	{
		{ double h=atan2(zy,zx)/(2.0f*M_PI)+0.5f; aux.DE*=(1.0f+af*aa*sin(ab*h*M_PI*2.0f)); }
		break;
	}
	case 140: // Type 140
	{
		{ double s=r/(r+aa); aux.DE*=(1.0f+af*ab*s); }
		break;
	}
	case 141: // Type 141
	{
		{ double v=sin(aa*zx)*sin(ab*zy)+sin(ac*zy)*sin(ad*zz2); aux.DE*=(1.0f+af*ae*v*0.5f); }
		break;
	}
	case 142: // Type 142
	{
		{ double orb=fabs(zx-floor(zx*aa)/aa)*fabs(zy-floor(zy*ab)/ab); aux.DE*=(1.0f+af*ac*sin(ad*orb)); }
		break;
	}
	case 143: // Type 143
	{
		aux.DE *= (1.0f + af * aa * sin(ab * (fabs(zx)+fabs(zy)+fabs(zz2))));
		break;
	}
	case 144: // Type 144
	{
		{ double d2=fabs(zx*zx/fmax(aa*aa,0.01f)+zy*zy/fmax(ab*ab,0.01f)-1.0f); aux.DE*=(1.0f+af*ac*exp(-ad*d2)); }
		break;
	}
	case 145: // Type 145
	{
		{ double sp=zx*cos(aa*zy)+zy*cos(aa*zz2)+zz2*cos(aa*zx); aux.DE*=(1.0f+af*ab*sin(ac*sp)); }
		break;
	}
	case 146: // Type 146
	{
		{ double cl=sin(aa*in.point.Length()+ab*r); aux.DE*=(1.0f+af*ac*cl); }
		break;
	}
	case 147: // Type 147
	{
		{ double it=double(i)/fmax(double(aa),1.0f); aux.DE*=(1.0f+af*ab*sin(ac*it*M_PI)); }
		break;
	}
	case 148: // Type 148
	{
		{ double gr=sin(aa*zx*zy/(r+1e-21))+cos(ab*zy*zz2/(r+1e-21)); aux.DE*=(1.0f+af*ac*gr*0.5f); }
		break;
	}
	case 149: // Type 149
	{
		{ double pat=sin(aa*zx)*cos(ab*zy)*sin(ac*zz2)*cos(ad*r); aux.DE*=(1.0f+af*ae*pat); }
		break;
	}
	case 150: // Type 150
	{
		{ double comb=aa*sin(ab*r)+ac*cos(ad*atan2(zy,zx))+ae*sin(aff*acos(zz2/r)); aux.DE*=(1.0f+af*comb/3.0f); }
		break;
	}
	case 151: // Type 151
	{
		{ double de=aa*r*log(r+1e-21)/fmax(ab,0.01f); aux.DE*=(1.0f+af*de/(r+1e-21)); }
		break;
	}
	case 152: // Type 152
	{
		aux.DE *= fmax(0.01f, 1.0f + af * aa * r * sin(ab*log(r+1e-21)+ac));
		break;
	}
	case 153: // Type 153
	{
		{ double lip=aa*fmin(1.0f,ab/fmax(r,1e-21)); aux.DE*=(1.0f+af*lip); }
		break;
	}
	case 154: // Type 154
	{
		aux.DE *= (1.0f + af * aa * exp(-ab*r) * sin(ac*r+ad));
		break;
	}
	case 155: // Type 155
	{
		{ double bess=sin(aa*r)/(aa*r+1e-21); aux.DE*=(1.0f+af*ab*bess); }
		break;
	}
	case 156: // Type 156
	{
		{ double cheb=cos(aa*acos(fmin(1.0f,fmax(-1.0f,zz2/r)))); aux.DE*=(1.0f+af*ab*cheb); }
		break;
	}
	case 157: // Type 157
	{
		{ double leg=(3.0f*(zz2/r)*(zz2/r)-1.0f)*0.5f; aux.DE*=(1.0f+af*aa*leg); }
		break;
	}
	case 158: // Type 158
	{
		{ double herm=(4.0f*(zz2/r)*(zz2/r)-2.0f)*exp(-(zz2/r)*(zz2/r)*0.5f); aux.DE*=(1.0f+af*aa*ab*herm); }
		break;
	}
	case 159: // Type 159
	{
		{ double lag=1.0f-aa*r+aa*aa*r*r*0.5f; aux.DE*=(1.0f+af*ab*lag*exp(-ac*r)); }
		break;
	}
	case 160: // Type 160
	{
		aux.DE *= (1.0f + af * aa * sin(ab*r+ac) * sin(ad*r+ae) * sin(aff*r+ag));
		break;
	}
	case 161: // Type 161
	{
		{ double gr=aa*r*exp(-ab*r*r)*sin(ac*r); aux.DE*=(1.0f+af*gr); }
		break;
	}
	case 162: // Type 162
	{
		aux.DE *= (1.0f + af * aa * sin(ab*r) * tanh(ac*r));
		break;
	}
	case 163: // Type 163
	{
		{ double sg=1.0f/(1.0f+exp(-aa*(r-ab))); aux.DE*=(1.0f+af*ac*sg*(1.0f-sg)); }
		break;
	}
	case 164: // Type 164
	{
		{ double gau=exp(-aa*(r-ab)*(r-ab)); aux.DE*=(1.0f+af*ac*gau); }
		break;
	}
	case 165: // Type 165
	{
		{ double stp=(r>aa)?ab:ac; aux.DE*=(1.0f+af*stp); }
		break;
	}
	case 166: // Type 166
	{
		{ double bnd=aa*sin(floor(r*ab)*M_PI/ab); aux.DE*=(1.0f+af*bnd); }
		break;
	}
	case 167: // Type 167
	{
		{ double v=0; for(int o=0;o<4;o++){v+=sin(aa*pow(2.0f,o)*r+ab*o)/(pow(2.0f,o));} aux.DE*=(1.0f+af*ac*v); }
		break;
	}
	case 168: // Type 168
	{
		{ double jc=aa*sin(ab*r)+ac*sin(ad*atan2(zy,zx)); aux.DE*=(1.0f+af*jc*0.5f); }
		break;
	}
	case 169: // Type 169
	{
		{ double tmp=aa+ab*sin(ac*r)*cos(ad*i*0.1f); aux.DE*=(1.0f+af*tmp); }
		break;
	}
	case 170: // Type 170
	{
		{ double fb=0; double prev=aa; double curr=ab; for(int k=0;k<6;k++){double nxt=prev+curr; fb+=sin(nxt*r)/(nxt+1.0f); prev=curr; curr=nxt;} aux.DE*=(1.0f+af*ac*fb); }
		break;
	}
	case 171: // Type 171
	{
		{ double orb=r; double v=aa*sin(ab*orb)+ac*cos(ad*orb*orb/(r+1e-21)); aux.DE*=(1.0f+af*v); }
		break;
	}
	case 172: // Type 172
	{
		aux.DE *= (1.0f + af * aa * fabs(sin(ab*r)) * fabs(cos(ac*r)));
		break;
	}
	case 173: // Type 173
	{
		aux.DE *= fabs(aa);
		break;
	}
	case 174: // Type 174
	{
		aux.DE *= (1.0f + fabs(aa*M_PI/180.0f) * ab);
		break;
	}
	case 175: // Type 175
	{
		aux.DE *= (1.0f + fabs(aa + ab + ac));
		break;
	}
	case 176: // Type 176
	{
		aux.DE *= fmax(0.01f, aa * double(i) / fmax(double(ab), 1.0f));
		break;
	}
	case 177: // Type 177
	{
		{ if(fabs(zx)>aa||fabs(zy)>aa||fabs(zz2)>aa) aux.DE*=ab; }
		break;
	}
	case 178: // Type 178
	{
		{ double d=sqrt((zx-aa)*(zx-aa)+(zy-ab)*(zy-ab)+(zz2-ac)*(zz2-ac)); if(d<ad) aux.DE*=ae; }
		break;
	}
	case 179: // Type 179
	{
		{ if(fabs(zx)<aa && fabs(zy)<aa) aux.DE*=ab; }
		break;
	}
	case 180: // Type 180
	{
		aux.DE *= (1.0f + 0.1f * aa * fabs(sin(ab*r)));
		break;
	}
	case 181: // Type 181
	{
		aux.DE *= (1.0f - aa * ab * exp(-ac*r));
		break;
	}
	case 182: // Type 182
	{
		aux.DE /= fmax(0.01f, 1.0f + aa * ab);
		break;
	}
	case 183: // Type 183
	{
		aux.DE *= (1.0f + aa * ab * r);
		break;
	}
	case 184: // Type 184
	{
		aux.DE /= fmax(0.01f, 1.0f + aa * ab * sin(ac*r));
		break;
	}
	case 185: // Type 185
	{
		aux.DE *= (1.0f + aa * ab * r);
		break;
	}
	case 186: // Type 186
	{
		aux.DE *= (1.0f + aa * fabs(ab - 550.0f) * 0.001f);
		break;
	}
	case 187: // Type 187
	{
		aux.DE *= (1.0f + aa * fabs(sin(ab*zx)*cos(ac*zy)));
		break;
	}
	case 188: // Type 188
	{
		{ double fr=pow(fabs(1.0f-fabs(zz2)/r),5.0f); aux.DE*=(1.0f+aa*fr); }
		break;
	}
	case 189: // Type 189
	{
		{ double tf=sin(aa*r+ab)*cos(ac*r); aux.DE*=(1.0f+ad*fabs(tf)); }
		break;
	}
	case 190: // Type 190
	{
		{ double an=fabs(zx*aa+zy*ab+zz2*ac)/(r+1e-21); aux.DE*=(1.0f+ad*an); }
		break;
	}
	case 191: // Type 191
	{
		aux.DE /= fmax(0.01f, 1.0f + aa * ab);
		break;
	}
	case 192: // Type 192
	{
		aux.DE *= (1.0f + aa * exp(-ab * r));
		break;
	}
	case 193: // Type 193
	{
		aux.DE *= (1.0f + aa * ab * r);
		break;
	}
	case 194: // Type 194
	{
		aux.DE += aa * ab * sin(ac*zx)*cos(ad*zy);
		break;
	}
	case 195: // Type 195
	{
		aux.DE *= (1.0f + aa * ab * sin(ac*zx+ad*zy+ae*zz2));
		break;
	}
	case 196: // Type 196
	{
		aux.DE *= fmax(0.01f, aa * ab / fmax(ac, 0.01f));
		break;
	}
	case 197: // Type 197
	{
		aux.DE /= fmax(0.01f, aa);
		break;
	}
	case 198: // Type 198
	{
		aux.DE *= exp(-aa * ab * r);
		break;
	}
	case 199: // Type 199
	{
		aux.DE *= (1.0f + aa * ab * (1.0f + ac*cos(ad*atan2(zy,zx))));
		break;
	}
	case 200: // Type 200
	{
		aux.DE /= fmax(0.01f, 1.0f + aa * ab);
		break;
	}
	case 201: // Type 201
	{
		{ double curl=sin(aa*zy+ab*zz2)-sin(aa*zz2+ab*zx); aux.DE*=(1.0f+ac*fabs(curl)); }
		break;
	}
	case 202: // Type 202
	{
		{ double grad=(zx*aa+zy*ab+zz2*ac)/(rr+1e-21); aux.DE/=fmax(0.01f,1.0f+ad*fabs(grad)); }
		break;
	}
	case 203: // Type 203
	{
		aux.DE *= (1.0f + aa * ab / fmax(rr, 1e-21));
		break;
	}
	case 204: // Type 204
	{
		{ double v2=aa*aa; double c2=ab*ab; aux.DE*=sqrt(fmax(0.01f,1.0f-v2/fmax(c2,1e-21))); }
		break;
	}
	case 205: // Type 205
	{
		aux.DE *= exp(-aa * fabs(r - ab));
		break;
	}
	case 206: // Type 206
	{
		{ double psi=sin(aa*zx)*sin(ab*zy)*sin(ac*zz2); aux.DE*=fmax(0.01f,psi*psi); }
		break;
	}
	case 207: // Type 207
	{
		aux.DE *= (1.0f + aa / fmax(2.0f * ab * r, 1e-21));
		break;
	}
	case 208: // Type 208
	{
		aux.DE *= (1.0f + aa * (zx*ab + zy*ac + zz2*ad)/(r+1e-21));
		break;
	}
	case 209: // Type 209
	{
		{ double corr=sin(aa*zx)*sin(aa*(-zx))+cos(ab*zy)*cos(ab*(-zy)); aux.DE*=(1.0f+ac*fabs(corr)); }
		break;
	}
	case 210: // Type 210
	{
		aux.DE *= exp(-aa * ab * double(i) * 0.01f);
		break;
	}
	case 211: // Type 211
	{
		{ double ent=sin(aa*zx)*log(fabs(sin(aa*zx))+1e-21)+sin(ab*zy)*log(fabs(sin(ab*zy))+1e-21); aux.DE*=(1.0f+ac*fabs(ent)*0.1f); }
		break;
	}
	case 212: // Type 212
	{
		aux.DE *= (1.0f + aa / fmax(ab * ac, 1e-21));
		break;
	}
	case 213: // Type 213
	{
		{ double vg=(sin(aa*(zx+0.01f))-sin(aa*zx))/0.01f; aux.DE*=(1.0f+ab*fabs(vg)); }
		break;
	}
	case 214: // Type 214
	{
		{ double curv=(sin(aa*zx+0.01f)+sin(aa*zx-0.01f)-2.0f*sin(aa*zx))/0.0001f; aux.DE*=(1.0f+ab*fabs(curv)); }
		break;
	}
	case 215: // Type 215
	{
		aux.DE *= (1.0f + aa * cos(ab) / fmax(ac, 0.01f));
		break;
	}
	case 216: // Type 216
	{
		{ double cg=(sin(aa*(zx+0.01f))-sin(aa*zx))/0.01f; aux.DE*=(1.0f+ab*fabs(cg)); }
		break;
	}
	case 217: // Type 217
	{
		{ double lap=sin(aa*(zx+0.01f))+sin(aa*(zx-0.01f))-2.0f*sin(aa*zx); aux.DE+=ab*lap; }
		break;
	}
	case 218: // Type 218
	{
		{ double adv=(sin(aa*zx)-sin(aa*(zx-0.01f)))/0.01f; aux.DE*=(1.0f+ab*fabs(adv)); }
		break;
	}
	case 219: // Type 219
	{
		{ double v=0; for(int o=0;o<4;o++){v+=sin(aa*pow(2.0f,o)*r)/pow(2.0f,o);} aux.DE*=(1.0f+ab*fabs(v)); }
		break;
	}
	case 220: // Type 220
	{
		{ double sh=(r>aa)?ab:0.0f; aux.DE*=(1.0f+ac*sh); }
		break;
	}
	case 221: // Type 221
	{
		{ double dw=aa-ab; double bw=ac*0.5f; double q=ad/fmax(sqrt(dw*dw+bw*bw),1e-21); aux.DE*=(1.0f+af*q); }
		break;
	}
	case 222: // Type 222
	{
		aux.DE *= (1.0f + aa * cos(ab * r + ac));
		break;
	}
	case 223: // Type 223
	{
		aux.DE *= (1.0f + aa / fmax(ab, 1e-21) * cos(ac));
		break;
	}
	case 224: // Type 224
	{
		aux.DE *= (1.0f + aa * cos(2.0f * ab * atan2(zy, zx)));
		break;
	}
	case 225: // Type 225
	{
		aux.DE *= (1.0f + aa * fabs(sin(2.0f * ab * atan2(zz2, sqrt(zx*zx+zy*zy+1e-21)))));
		break;
	}
	case 226: // Type 226
	{
		aux.DE *= (1.0f + aa * ab * ac);
		break;
	}
	case 227: // Type 227
	{
		{ double lp=fmod(r*aa, ab); aux.DE*=(1.0f+ac*sin(M_PI*lp/fmax(ab,0.01f))); }
		break;
	}
	case 228: // Type 228
	{
		{ double skin=exp(-fabs(zz2)*aa/fmax(ab,0.01f)); aux.DE*=(1.0f+ac*skin); }
		break;
	}
	case 229: // Type 229
	{
		aux.DE *= (1.0f + aa * fabs(ab));
		break;
	}
	case 230: // Type 230
	{
		{ double wn=floor(atan2(zy,zx)*aa/(2.0f*M_PI)+0.5f); aux.DE*=(1.0f+ab*fabs(wn)); }
		break;
	}
	case 231: // Type 231
	{
		{ double tc=floor(atan2(zy,zx)*aa/(2.0f*M_PI)+0.5f); aux.DE*=(1.0f+ab*fabs(tc)*sin(ac*r)); }
		break;
	}
	case 232: // Type 232
	{
		{ double vort=fabs(-aa*zy/(rr+1e-21)-(-ab*zx/(rr+1e-21))); aux.DE*=(1.0f+ac*vort); }
		break;
	}
	case 233: // Type 233
	{
		{ double sw=1.0f/cosh(aa*fabs(r-ab)); aux.DE*=(1.0f+ac*sw); }
		break;
	}
	case 234: // Type 234
	{
		{ double inst=exp(-aa*(rr+1e-21)); aux.DE*=(1.0f+ab*inst); }
		break;
	}
	case 235: // Type 235
	{
		aux.DE *= (1.0f + aa / fmax(r, 1e-21));
		break;
	}
	case 236: // Type 236
	{
		{ double sl=fabs(sqrt(zx*zx+zy*zy)); aux.DE*=(1.0f+aa*log(sl+1e-21)*ab); }
		break;
	}
	case 237: // Type 237
	{
		{ double bd=exp(-aa*fabs(zz2-ab)); aux.DE*=(1.0f+ac*bd); }
		break;
	}
	case 238: // Type 238
	{
		{ double wh=exp(-(r-aa)*(r-aa)/(fmax(ab*ab,0.01f))); aux.DE*=(1.0f+ac*wh); }
		break;
	}
	case 239: // Type 239
	{
		aux.DE /= fmax(0.01f, 1.0f - aa / fmax(r, aa + 1e-21));
		break;
	}
	case 240: // Type 240
	{
		{ double jet=exp(-fabs(sqrt(zx*zx+zy*zy)-aa)/(fmax(ab,0.01f))); aux.DE*=(1.0f+ac*jet); }
		break;
	}
	case 241: // Type 241
	{
		{ double halo=1.0f/(1.0f+pow(r/fmax(aa,0.01f),2.0f)); aux.DE*=(1.0f+ab*halo); }
		break;
	}
	case 242: // Type 242
	{
		aux.DE *= exp(fmin(aa * ab * r, 20.0f));
		break;
	}
	case 243: // Type 243
	{
		{ double cs2=log(fmax(fabs(sqrt(zx*zx+zy*zy)),1e-21)/fmax(aa,0.01f)); aux.DE*=(1.0f+ab*ac*cs2); }
		break;
	}
	case 244: // Type 244
	{
		aux.DE *= (1.0f + aa * tanh(fabs(zz2 - ab) / fmax(ac, 0.01f)));
		break;
	}
	case 245: // Type 245
	{
		{ double ylm=sin(aa*acos(zz2/r))*cos(ab*atan2(zy,zx)); aux.DE*=(1.0f+ac*fabs(ylm)); }
		break;
	}
	case 246: // Type 246
	{
		aux.DE *= exp(aa * ab);
		break;
	}
	case 247: // Type 247
	{
		{ double rh=aa*ab*exp(-ac*double(i)*0.01f); aux.DE*=(1.0f+rh); }
		break;
	}
	case 248: // Type 248
	{
		{ double ns=aa*ab*sin(ac*r)/(1.0f+ad*r); aux.DE*=(1.0f+ns); }
		break;
	}
	case 249: // Type 249
	{
		{ double rc=aa*exp(-ab/(fmax(ac*r,0.01f))); aux.DE*=(1.0f+rc); }
		break;
	}
	case 250: // Type 250
	{
		{ double sf2=1.0f+aa*r; aux.DE*=sf2*sqrt(fmax(0.01f,ab*ac/(fmax(r,1e-21)))); }
		break;
	}
	case 251: // Type 251
	{
		{ double sf2=fmax(0.01f,1.0f+aa*r); aux.DE/=sf2; }
		break;
	}
	case 252: // Type 252
	{
		aux.DE *= (1.0f + aa * (1.0f - exp(-double(i) * 0.01f / fmax(ab, 0.01f))));
		break;
	}
	case 253: // Type 253
	{
		{ double bn=exp(-aa*rr)*ab; aux.DE*=(1.0f+bn); }
		break;
	}
	case 254: // Type 254
	{
		{ double fv=aa*exp(-ab*rr); aux.DE*=(1.0f+fv); }
		break;
	}
	case 255: // Type 255
	{
		{ double op=sin(aa*r)*sin(aa*r); aux.DE*=(1.0f+ab*op); }
		break;
	}
	case 256: // Type 256
	{
		{ double d=fabs(r-aa); aux.DE*=fmax(0.01f,pow(d+1e-21,-ab)); }
		break;
	}
	case 257: // Type 257
	{
		aux.DE *= (1.0f + aa * log(fmax(ab, 0.01f) / fmax(r, 1e-21)));
		break;
	}
	case 258: // Type 258
	{
		{ double div=(sin(aa*(zx+0.01f))-sin(aa*zx))/0.01f; aux.DE*=(1.0f+ab*fabs(div)); }
		break;
	}
	case 259: // Type 259
	{
		{ double vev=aa*r*r; aux.DE*=(1.0f+ab*vev); }
		break;
	}
	case 260: // Type 260
	{
		{ double grd=(sin(aa*(r+0.01f))-sin(aa*r))/0.01f; aux.DE*=(1.0f+ab*fabs(grd)); }
		break;
	}
	case 261: // Type 261
	{
		aux.DE *= (1.0f + aa * ab * rr);
		break;
	}
	case 262: // Type 262
	{
		{ double a2=sin(aa*zx)*sin(aa*zx)+sin(ab*zy)*sin(ab*zy); aux.DE*=(1.0f+ac*ad*a2); }
		break;
	}
	case 263: // Type 263
	{
		{ double psi2=sin(aa*r)*sin(aa*r); aux.DE*=(1.0f+ab*psi2); }
		break;
	}
	case 264: // Type 264
	{
		{ double phi=sin(aa*r); aux.DE*=(1.0f+ab*phi*phi+ac*phi*phi*phi*phi); }
		break;
	}
	case 265: // Type 265
	{
		{ double tmn=(zx*zx+zy*zy+zz2*zz2)/(rr+1e-21); aux.DE*=(1.0f+aa*ab*tmn); }
		break;
	}
	case 266: // Type 266
	{
		{ double sp=sin(aa*zx)*cos(ab*zy); aux.DE*=(1.0f+ac*fabs(sp)); }
		break;
	}
	case 267: // Type 267
	{
		{ double rs=sin(aa*r)*fabs(cos(ab*atan2(zy,zx))); aux.DE*=(1.0f+ac*rs*rs); }
		break;
	}
	case 268: // Type 268
	{
		{ double kr=sin(aa*zx)*sin(ab*zy)-cos(aa*zx)*cos(ab*zy); aux.DE*=(1.0f+ac*kr*kr); }
		break;
	}
	case 269: // Type 269
	{
		{ double gv=sin(aa*r)*sin(ab*r); aux.DE*=(1.0f+ac*gv*gv); }
		break;
	}
	case 270: // Type 270
	{
		{ double xs=fabs(sin(aa*r)-zx); aux.DE*=(1.0f+ab*xs*xs); }
		break;
	}
	case 271: // Type 271
	{
		{ double m5=sin(aa*r)*sin(ab*r)*sin(ac*r); aux.DE*=(1.0f+ad*m5*m5); }
		break;
	}
	case 272: // Type 272
	{
		{ double wf2=exp(-aa*fabs(zz2)); aux.DE*=(1.0f+ab*ac*wf2); }
		break;
	}
	case 273: // Type 273
	{
		{ double kk=sin(aa*r/fmax(ab,0.01f))*sin(ac*r/fmax(ab,0.01f)); aux.DE*=(1.0f+ad*kk); }
		break;
	}
	case 274: // Type 274
	{
		aux.DE *= exp(-aa * fabs(zz2 - ab));
		break;
	}
	case 275: // Type 275
	{
		{ double av=r>1e-21?(fabs(zx)+fabs(zy)+fabs(zz2))/(r):1.0f; aux.DE*=(1.0f+aa*ab*av); }
		break;
	}
	case 276: // Type 276
	{
		{ double cf=1.0f/(1.0f+aa*rr); aux.DE*=(1.0f+ab*cf); }
		break;
	}
	case 277: // Type 277
	{
		{ double ms=fmin(fabs(zx),fmin(fabs(zy),fabs(zz2))); aux.DE*=(1.0f+aa*ms); }
		break;
	}
	case 278: // Type 278
	{
		{ double fw=exp(-aa*fabs(r-ab)*fabs(r-ab)*1000.0f); aux.DE*=(1.0f+ac*fw); }
		break;
	}
	case 279: // Type 279
	{
		{ double ee=sin(aa*zx)*sin(aa*(-zx+ab)); aux.DE*=(1.0f+ac*fabs(ee)); }
		break;
	}
	case 280: // Type 280
	{
		{ double vol=r*r*r; aux.DE*=(1.0f+aa*vol/(vol+ab+1e-21)); }
		break;
	}
	case 281: // Type 281
	{
		{ double ly=exp(aa*double(i)*0.01f); aux.DE*=(1.0f+ab*fmin(ly,ac)); }
		break;
	}
	case 282: // Type 282
	{
		{ double bv=fabs(zx-aa*sin(ab*zy))/(double(i)+1.0f); aux.DE*=(1.0f+ac*bv); }
		break;
	}
	case 283: // Type 283
	{
		{ double scr=log(fmax(aa,1.0f))*ab*sin(ac*r); aux.DE*=(1.0f+fabs(scr)*0.01f); }
		break;
	}
	case 284: // Type 284
	{
		{ double sff=sin(aa*double(i)*0.1f)*sin(ab*double(i)*0.1f); aux.DE*=(1.0f+ac*fabs(sff)); }
		break;
	}
	case 285: // Type 285
	{
		{ double goe=sin(aa*r)*cos(ab*r)*sin(ac*r); aux.DE*=(1.0f+ad*fabs(goe)); }
		break;
	}
	case 286: // Type 286
	{
		{ double syk=sin(aa*zx)*sin(ab*zy)*sin(ac*zz2)*sin(ad*r); aux.DE*=(1.0f+ae*fabs(syk)); }
		break;
	}
	case 287: // Type 287
	{
		{ double bd2=sin(aa*r)*sin(aa*r); double ent=bd2*log(bd2+1e-21); aux.DE*=(1.0f+ab*fabs(ent)); }
		break;
	}
	case 288: // Type 288
	{
		{ double ml=floor(log(r+1e-21)/log(fmax(aa,1.01f))); aux.DE*=(1.0f+ab*sin(ac*ml)); }
		break;
	}
	case 289: // Type 289
	{
		{ double cd=floor(r*aa); double le=exp(-ab*cd); aux.DE*=(1.0f+ac*le); }
		break;
	}
	case 290: // Type 290
	{
		{ double wn2=floor(atan2(zy,zx)*aa/(2.0f*M_PI)+0.5f); aux.DE*=(1.0f+ab*sin(ac*wn2)); }
		break;
	}
	case 291: // Type 291
	{
		{ double sw2=floor(zx*aa+0.5f)*floor(zy*ab+0.5f); aux.DE*=(1.0f+ac*sin(ad*sw2)); }
		break;
	}
	case 292: // Type 292
	{
		{ double cc=floor(r*aa)*3.0f; aux.DE*=(1.0f+ab*sin(ac*cc)); }
		break;
	}
	case 293: // Type 293
	{
		{ double pc=fmod(floor(r*aa),ab); aux.DE*=(1.0f+ac*sin(ad*pc)); }
		break;
	}
	case 294: // Type 294
	{
		{ double ce=sin(aa*zx)*cos(ab*zy)*sin(ac*zz2); aux.DE*=(1.0f+ad*fabs(ce)); }
		break;
	}
	case 295: // Type 295
	{
		{ double ev=sin(aa*r)*sin(aa*r)+cos(ab*r)*cos(ab*r); aux.DE*=(1.0f+ac*ev*0.5f); }
		break;
	}
	case 296: // Type 296
	{
		{ double sgn=sin(aa*r)>0?1.0f:-1.0f; double mc=exp(-ab*rr)*sgn; aux.DE*=(1.0f+ac*fabs(mc)); }
		break;
	}
	case 297: // Type 297
	{
		{ double pur=sin(aa*r)*sin(aa*r); aux.DE*=(1.0f+ab*pur*pur); }
		break;
	}
	case 298: // Type 298
	{
		{ double wig=sin(aa*zx)*cos(ab*zy); aux.DE*=(1.0f+ac*fabs(wig)); }
		break;
	}
	case 299: // Type 299
	{
		{ double hus=exp(-aa*(zx*zx+zy*zy))*sin(ab*r); aux.DE*=(1.0f+ac*fabs(hus)); }
		break;
	}
	case 300: // Type 300
	{
		{ double mi=sin(aa*r)*sin(ab*r); aux.DE*=(1.0f+ac*mi*mi); }
		break;
	}
	case 301: // Type 301
	{
		double psi = sin(aa*r + ab*z.x); aux.DE *= (1.0f + af * psi*psi);
		break;
	}
	case 302: // Type 302
	{
		double psi_f = cos(aa*r); double psi_i = sin(ab*r); double overlap = psi_f*psi_i + 1e-21; double wv = (psi_f*sin(ac*z.x)) / overlap; aux.DE *= (1.0f + af * fabs(wv));
		break;
	}
	case 303: // Type 303
	{
		double rate = fabs(aa); double variance = z.x*z.x + z.y*z.y; aux.DE *= (1.0f + af * exp(-rate * (double)i * 0.01f * variance));
		break;
	}
	case 304: // Type 304
	{
		double E = aa*r; double t = (double)i * 0.01f; aux.DE *= (1.0f + af * fabs(ab) * sin(E*t)*sin(E*t));
		break;
	}
	case 305: // Type 305
	{
		double path1 = sin(aa*z.x + ab*z.y); double path2 = sin(ac*z.x - ab*z.y); aux.DE *= (1.0f + af * fabs(path1 - path2));
		break;
	}
	case 306: // Type 306
	{
		double choice_time = fabs(aa) * 10.0f; double theta = (double)i > choice_time ? 1.0f : 0.0f; aux.DE *= (1.0f + af * ab * theta);
		break;
	}
	case 307: // Type 307
	{
		double visibility = cos(aa*r)*cos(aa*r); double erased = sin(ab*z.x + ac*z.y); aux.DE *= (1.0f + af * visibility * erased*erased);
		break;
	}
	case 308: // Type 308
	{
		double source = sin(aa*z.x + ab*z.y + ac*z.z); double target = sin(aa*(z.x+ad) + ab*(z.y+ae) + ac*(z.z+aff)); double fidelity = source*target; aux.DE *= (1.0f + af * fabs(fidelity));
		break;
	}
	case 309: // Type 309
	{
		double psi = sin(aa*r); double clone = sin(aa*r + ab*0.1f); double fidelity = 1.0f - (psi-clone)*(psi-clone)*0.5f; aux.DE *= (1.0f + af * fmax(fidelity, 0.0f));
		break;
	}
	case 310: // Type 310
	{
		double Iz = sin(aa*z.x)*sin(ab*z.y); double classical = sin(aa*z.x)*0.5f; double discord = fabs(Iz - classical); aux.DE *= (1.0f + af * discord);
		break;
	}
	case 311: // Type 311
	{
		double epr = sin(aa*z.x)*cos(ab*z.y) - cos(aa*z.x)*sin(ab*z.y); aux.DE *= (1.0f + af * fabs(epr));
		break;
	}
	case 312: // Type 312
	{
		double v1 = sin(aa*z.x)*sin(aa*z.y); double v2 = cos(ab*z.y)*cos(ab*z.z); double violation = fabs(v1 + v2) - 1.0f; aux.DE *= (1.0f + af * fmax(violation, 0.0f));
		break;
	}
	case 313: // Type 313
	{
		double ca = cos(aa*z.x); double cb = cos(ab*z.y); double corr = ca*cb + ca*sin(ab*z.y) + sin(aa*z.x)*cb - sin(aa*z.x)*sin(ab*z.y); aux.DE *= (1.0f + af * fabs(corr) * 0.25f);
		break;
	}
	case 314: // Type 314
	{
		double S = 2.0f*sqrt(2.0f)*sin(aa*r)*cos(ab*r); double violation = fmax(fabs(S) - 2.0f, 0.0f); aux.DE *= (1.0f + af * violation);
		break;
	}
	case 315: // Type 315
	{
		double bound = 2.0f*sqrt(2.0f); double corr = bound * cos(aa*r) * sin(ab*z.x); aux.DE *= (1.0f + af * fabs(corr) / bound);
		break;
	}
	case 316: // Type 316
	{
		double t1 = sin(aa*(double)i*0.1f); double t2 = sin(aa*((double)i+ab)*0.1f); double temporal = t1*t2 + t1*sin(aa*((double)i+ac)*0.1f); aux.DE *= (1.0f + af * fabs(temporal));
		break;
	}
	case 317: // Type 317
	{
		double rho = sin(aa*z.x)*sin(aa*z.x) + cos(ab*z.y)*cos(ab*z.y); double witness = rho - ac; aux.DE *= (1.0f + af * fmax(-witness, 0.0f));
		break;
	}
	case 318: // Type 318
	{
		double dpsi = aa*cos(aa*r + ab*z.x); double fisher = 4.0f*dpsi*dpsi; aux.DE *= (1.0f + af * fisher / (1.0f + fisher));
		break;
	}
	case 319: // Type 319
	{
		double F_Q = 4.0f*(aa*cos(aa*r))*(aa*cos(aa*r)); double bound = 1.0f/sqrt(fmax(ab*F_Q, 1e-21)); aux.DE *= (1.0f + af * bound);
		break;
	}
	case 320: // Type 320
	{
		double N = fmax(fabs(aa)*10.0f, 1.0f); double dphi = 1.0f/(N*sqrt(fmax(fabs(ab), 1e-21))); double sql = 1.0f/sqrt(N); double gain = (sql*sql)/(dphi*dphi+1e-21); aux.DE *= (1.0f + af * fmin(gain, 10.0f) * sin(ac*r)*sin(ac*r));
		break;
	}
	case 321: // Type 321
	{
		double T2 = fabs(aa) + 0.01f; double sensitivity = 1.0f/(ab*sqrt(T2)+1e-21); aux.DE *= (1.0f + af * sin(ac*r)*sin(ac*r) * fmin(sensitivity, 10.0f));
		break;
	}
	case 322: // Type 322
	{
		double lambda_r = fabs(aa)+0.1f; double NA = fabs(ab)+0.1f; double N_ph = fmax(fabs(ac)*10, 1.0f); double res = lambda_r/(2.0f*NA*sqrt(N_ph)); aux.DE *= (1.0f + af * sin(r/fmax(res,0.01f))*sin(r/fmax(res,0.01f)));
		break;
	}
	case 323: // Type 323
	{
		double N = fmax(fabs(aa)*5, 1.0f); double pattern = sin(N*ab*z.x)*sin(N*ab*z.y); aux.DE *= (1.0f + af * pattern*pattern);
		break;
	}
	case 324: // Type 324
	{
		double snr_q = exp(-aa*r*r); double snr_c = exp(-ab*r*r); double advantage = snr_q/(snr_c+1e-21); aux.DE *= (1.0f + af * fmin(advantage, 10.0f));
		break;
	}
	case 325: // Type 325
	{
		double tau = fabs(aa)*r; double N_s = fmax(fabs(ab), 0.1f); double N_i = fmax(fabs(ac), 0.1f); double range_res = tau/(2.0f*sqrt(N_s*N_i)+1e-21); aux.DE *= (1.0f + af * sin(range_res)*sin(range_res));
		break;
	}
	case 326: // Type 326
	{
		double omega_rot = aa*z.x + ab*z.y; double phase = ac*omega_rot; aux.DE *= (1.0f + af * sin(phase)*sin(phase));
		break;
	}
	case 327: // Type 327
	{
		double g_eff = aa; double T = fabs(ab)+0.01f; double phase = g_eff*T*T*ac; aux.DE *= (1.0f + af * cos(phase)*cos(phase));
		break;
	}
	case 328: // Type 328
	{
		double omega0 = fabs(aa)*100.0f+1.0f; double tau_c = fabs(ab)+0.01f; double stability = 1.0f/(omega0*sqrt(tau_c*(double)(i+1)*0.01f)+1e-21); aux.DE *= (1.0f + af * fmin(stability*ac, 5.0f));
		break;
	}
	case 329: // Type 329
	{
		double B = aa*z.x + ab*z.y + ac*z.z; double sensitivity = sin(ad*B); aux.DE *= (1.0f + af * sensitivity*sensitivity);
		break;
	}
	case 330: // Type 330
	{
		double k_eff = aa; double T = fabs(ab)+0.01f; double accel = k_eff*T*T*ac*r; aux.DE *= (1.0f + af * sin(accel)*sin(accel));
		break;
	}
	case 331: // Type 331
	{
		double T_eff = fabs(aa)*r + 0.01f; double C = fabs(ab)+0.1f; double dE = fabs(ac)+0.01f; double res = T_eff*T_eff/(C*dE); aux.DE *= (1.0f + af * fmin(res, 10.0f));
		break;
	}
	case 332: // Type 332
	{
		double pressure = aa*r*r + ab*z.x; double sensitivity = sin(ac*pressure); aux.DE *= (1.0f + af * sensitivity*sensitivity);
		break;
	}
	case 333: // Type 333
	{
		double dL = aa*(z.x - z.y); double L = fmax(r, 0.01f); double strain = dL/L; double gauge = ab*strain; aux.DE *= (1.0f + af * sin(gauge)*sin(gauge));
		break;
	}
	case 334: // Type 334
	{
		double omega0 = fabs(aa)+0.1f; double Q = fabs(ab)+1.0f; double force = ac/(2.0f*Q*omega0+1e-21); aux.DE *= (1.0f + af * sin(force*r)*sin(force*r));
		break;
	}
	case 335: // Type 335
	{
		double torque = aa*z.x*z.y - ab*z.y*z.z; double thermal = fabs(ac)+0.01f; aux.DE *= (1.0f + af * fabs(torque)/(thermal+fabs(torque)));
		break;
	}
	case 336: // Type 336
	{
		double E_field = aa*z.x + ab*z.y + ac*z.z; double rydberg = sin(ad*E_field*E_field); aux.DE *= (1.0f + af * rydberg*rydberg);
		break;
	}
	case 337: // Type 337
	{
		double V_jj = aa*sin(ab*r); double josephson = cos(ac*V_jj); aux.DE *= (1.0f + af * (1.0f - josephson*josephson));
		break;
	}
	case 338: // Type 338
	{
		double tunnel = exp(-aa*fabs(r-ab)); double current = ac*tunnel; aux.DE *= (1.0f + af * fabs(current));
		break;
	}
	case 339: // Type 339
	{
		double n = floor(fabs(aa)*r*5.0f+0.5f); double R_H = 1.0f/(fmax(n,1.0f)*ab+1e-21); aux.DE *= (1.0f + af * fmin(R_H, 10.0f));
		break;
	}
	case 340: // Type 340
	{
		double C_q = aa*aa/(2.0f*(fabs(ab)+0.01f)); double charging = exp(-C_q*r*r); aux.DE *= (1.0f + af * charging);
		break;
	}
	case 341: // Type 341
	{
		double flux = aa*z.x*z.y; double inductance = cos(ab*flux); aux.DE *= (1.0f + af * inductance*inductance);
		break;
	}
	case 342: // Type 342
	{
		double L_q = fabs(aa)+0.01f; double C_q = fabs(ab)+0.01f; double Z = sqrt(L_q/C_q); double match = 1.0f/(1.0f + (Z-ac)*(Z-ac)); aux.DE *= (1.0f + af * match);
		break;
	}
	case 343: // Type 343
	{
		double omega = aa*r; double n_th = 1.0f/(exp(fabs(ab)*omega+1e-21)-1.0f+1e-21); double psd = omega*(n_th+0.5f); aux.DE *= (1.0f + af * fmin(fabs(psd), 10.0f));
		break;
	}
	case 344: // Type 344
	{
		double dE = fabs(aa)*r; double tau = fmax(fabs(ab),0.01f); double uncertainty = dE*tau; aux.DE *= (1.0f + af * exp(-uncertainty));
		break;
	}
	case 345: // Type 345
	{
		double W = aa*r*r; double T_eff = fmax(fabs(ab), 0.01f); double jarzynski = exp(-W/T_eff); aux.DE *= (1.0f + af * jarzynski);
		break;
	}
	case 346: // Type 346
	{
		double Q_heat = aa*r; double T_eff = fmax(fabs(ab), 0.01f); double C = fmax(fabs(ac), 0.01f); double fluct = Q_heat/(T_eff*T_eff*C+1e-21); aux.DE *= (1.0f + af * exp(-fabs(fluct)));
		break;
	}
	case 347: // Type 347
	{
		double sigma = fabs(aa)*r*r; double relax = fmax(fabs(ab), 0.01f); double prod = sigma/relax; aux.DE *= (1.0f + af * (1.0f - exp(-prod)));
		break;
	}
	case 348: // Type 348
	{
		double W = aa*(z.x*z.x + z.y*z.y); double T_eff = fmax(fabs(ab), 0.01f); double ratio = exp(-W/T_eff); aux.DE *= (1.0f + af * fmin(ratio, 10.0f));
		break;
	}
	case 349: // Type 349
	{
		double info = fabs(sin(aa*z.x)*cos(ab*z.y)); double work = ac*info*log(2.0f); aux.DE *= (1.0f + af * fabs(work)/(1.0f+fabs(work)));
		break;
	}
	case 350: // Type 350
	{
		double W = fabs(aa)*log(2.0f)*sin(ab*r)*sin(ab*r); aux.DE *= (1.0f + af * W);
		break;
	}
	case 351: // Type 351
	{
		double T_hot = fmax(fabs(aa)*r, 0.01f); double T_cold = fmax(fabs(ab)*0.5f, 0.001f); double eff = 1.0f - T_cold/T_hot; double qcorr = sin(ac*r)*sin(ac*r); aux.DE *= (1.0f + af * fabs(eff) * qcorr);
		break;
	}
	case 352: // Type 352
	{
		double w_cold = fabs(aa)+0.1f; double w_hot = fabs(ab)+0.2f; double eff = 1.0f - w_cold/w_hot; double adiabatic = cos(ac*r)*cos(ac*r); aux.DE *= (1.0f + af * fabs(eff) * adiabatic);
		break;
	}
	case 353: // Type 353
	{
		double V_ratio = fmax(fabs(aa), 0.1f)/fmax(fabs(ab), 0.1f); double T_ratio = fmax(fabs(ac), 0.1f)/fmax(fabs(ad), 0.1f); double eff = log(fmax(V_ratio,1e-21))/(log(fmax(T_ratio,1e-21))+1e-21); aux.DE *= (1.0f + af * fmin(fabs(eff), 5.0f) * sin(r)*sin(r));
		break;
	}
	case 354: // Type 354
	{
		double gamma_g = 1.4f; double ratio = fmax(fabs(aa), 0.1f); double eff = 1.0f - (pow(ratio, gamma_g)-1.0f)/(gamma_g*(ratio-1.0f)+1e-21); aux.DE *= (1.0f + af * fabs(eff) * sin(ab*r)*sin(ab*r));
		break;
	}
	case 355: // Type 355
	{
		double P_ratio = fmax(fabs(aa), 0.1f); double gamma_g = 1.4f; double eff = 1.0f - pow(1.0f/P_ratio, (gamma_g-1.0f)/gamma_g); aux.DE *= (1.0f + af * fabs(eff) * cos(ab*r)*cos(ab*r));
		break;
	}
	case 356: // Type 356
	{
		double T_ratio = fmax(fabs(aa)+0.1f, 0.01f) / fmax(fabs(ab)+0.1f, 0.01f); double regen = fmin(fabs(ac), 1.0f); double eff = (1.0f - 1.0f/T_ratio) * regen; aux.DE *= (1.0f + af * fabs(eff));
		break;
	}
	case 357: // Type 357
	{
		double expansion = fmax(fabs(aa), 0.1f); double T_ratio = fmax(fabs(ab)+0.1f, 0.01f)/fmax(fabs(ac)+0.1f, 0.01f); double eff = (1.0f - 1.0f/T_ratio)*expansion/(expansion+1.0f); aux.DE *= (1.0f + af * fabs(eff) * sin(ad*r)*sin(ad*r));
		break;
	}
	case 358: // Type 358
	{
		double T_ratio = fmax(fabs(aa)+0.1f,0.01f)/fmax(fabs(ab)+0.1f,0.01f); double loss = 1.0f-fmin(fabs(ac),0.99f); double eff = (1.0f-1.0f/T_ratio)*loss; aux.DE *= (1.0f + af * fabs(eff) * cos(ad*r)*cos(ad*r));
		break;
	}
	case 359: // Type 359
	{
		double T_cold = fmax(fabs(aa),0.01f); double T_hot = fmax(fabs(ab),0.02f); double cop = T_cold/(T_hot-T_cold+1e-21); double qcop = cop*sin(ac*r)*sin(ac*r); aux.DE *= (1.0f + af * fmin(fabs(qcop),10.0f));
		break;
	}
	case 360: // Type 360
	{
		double T_hot = fmax(fabs(aa),0.02f); double T_cold = fmax(fabs(ab),0.01f); double cop = T_hot/(T_hot-T_cold+1e-21); double enhance = cos(ac*r)*cos(ac*r); aux.DE *= (1.0f + af * fmin(cop*enhance,10.0f));
		break;
	}
	case 361: // Type 361
	{
		double k = aa; double Gamma = fabs(ab)+0.01f; double delta = fabs(ac)+0.01f; double cooling = Gamma/(2.0f*(1.0f + 4.0f*delta*delta/(Gamma*Gamma))); aux.DE *= (1.0f + af * cooling * sin(k*r)*sin(k*r));
		break;
	}
	case 362: // Type 362
	{
		double U0 = aa; double delta = fabs(ab)+0.01f; double pol_grad = sin(ac*z.x)*cos(ac*z.y); double eff = U0/(delta+1e-21)*pol_grad*pol_grad; aux.DE *= (1.0f + af * fmin(fabs(eff),10.0f));
		break;
	}
	case 363: // Type 363
	{
		double T_ratio = fmax(fabs(aa),0.01f)/fmax(fabs(ab),0.01f); double eta = fabs(ac)+1.0f; double eff = pow(T_ratio, 3.0f)*eta; aux.DE *= (1.0f + af * fmin(fabs(eff),10.0f) * sin(r)*sin(r));
		break;
	}
	case 364: // Type 364
	{
		double m_ratio = fmax(fabs(aa),0.1f)/fmax(fabs(ab),0.1f); double collision = fabs(ac); double eff = m_ratio*collision; aux.DE *= (1.0f + af * fmin(eff,10.0f) * sin(ad*r)*sin(ad*r));
		break;
	}
	case 365: // Type 365
	{
		double eta = fabs(aa)*0.1f; double Omega = fabs(ab)+0.1f; double nu_m = fabs(ac)+0.1f; double eff = eta*Omega*Omega/((fabs(ad)+0.01f)*nu_m); aux.DE *= (1.0f + af * fmin(eff,10.0f));
		break;
	}
	case 366: // Type 366
	{
		double Sxy = sin(aa*z.x)*cos(ab*z.y); double Sxx = sin(aa*z.x)*sin(aa*z.x)+0.01f; double Syy = cos(ab*z.y)*cos(ab*z.y)+0.01f; double gain = Sxy*Sxy/(Sxx*Syy); aux.DE *= (1.0f + af * fabs(gain));
		break;
	}
	case 367: // Type 367
	{
		double g = fabs(aa)+0.01f; double kappa = fabs(ab)+0.01f; double delta = fabs(ac)+0.01f; double cooling = g*g/(kappa*kappa+delta*delta); double n_ph = sin(ad*r)*sin(ad*r)*10.0f; aux.DE *= (1.0f + af * cooling*fmin(n_ph,10.0f));
		break;
	}
	case 368: // Type 368
	{
		double Cg = fabs(aa)+0.01f; double Vg = ab; double C = fabs(ac)+0.01f; double coupling = Cg*Vg/C; aux.DE *= (1.0f + af * sin(coupling*r)*sin(coupling*r));
		break;
	}
	case 369: // Type 369
	{
		double S = aa; double sigma = fabs(ab)+0.01f; double T_eff = fabs(ac)*r+0.01f; double kappa = fabs(ad)+0.01f; double ZT = S*S*sigma*T_eff/kappa; aux.DE *= (1.0f + af * fmin(ZT,10.0f));
		break;
	}
	case 370: // Type 370
	{
		double Ss = aa; double gradT = ab*z.x+ac*z.y; double spin_pol = sin(ad*r); aux.DE *= (1.0f + af * fabs(Ss*gradT*spin_pol));
		break;
	}
	case 371: // Type 371
	{
		double Bz = aa; double gradT = ab*z.x; double Ey = ac*gradT*Bz; aux.DE *= (1.0f + af * sin(Ey)*sin(Ey));
		break;
	}
	case 372: // Type 372
	{
		double n_level = floor(fabs(aa)*r*5.0f+0.5f); double conductance = fmax(n_level,1.0f)*ab; aux.DE *= (1.0f + af * fmin(fabs(conductance),10.0f) * sin(ac*r)*sin(ac*r));
		break;
	}
	case 373: // Type 373
	{
		double edge = exp(-aa*fabs(z.x)); double helical = sin(ab*z.y); aux.DE *= (1.0f + af * edge * helical*helical);
		break;
	}
	case 374: // Type 374
	{
		double chern = floor(fabs(aa)*2.0f+0.5f); double mag_order = sin(ab*z.x)*sin(ab*z.y); aux.DE *= (1.0f + af * fabs(chern) * mag_order*mag_order);
		break;
	}
	case 375: // Type 375
	{
		double valley = sin(aa*z.x)*cos(ab*z.y) - cos(aa*z.x)*sin(ab*z.y); double broken_inv = sin(ac*r); aux.DE *= (1.0f + af * fabs(valley*broken_inv));
		break;
	}
	case 376: // Type 376
	{
		double bulk_gap = fabs(aa); double surface = sin(ab*z.x)*sin(ab*z.y)*exp(-ac*fabs(z.z)); double k_F = ad*r; aux.DE *= (1.0f + af * bulk_gap*fabs(surface)*fmin(k_F,5.0f));
		break;
	}
	case 377: // Type 377
	{
		double kx = aa*z.x; double ky = ab*z.y; double kz = ac*z.z; double chirality = kx*kx + ky*ky - kz*kz; double fermi_arc = exp(-fabs(chirality)*ad); aux.DE *= (1.0f + af * fermi_arc);
		break;
	}
	case 378: // Type 378
	{
		double E_D = aa; double v_F = fabs(ab)+0.01f; double k = ac*r; double cone = fabs(E_D)/(v_F*fmax(fabs(k),0.01f)); aux.DE *= (1.0f + af * fmin(cone,10.0f) * sin(r)*sin(r));
		break;
	}
	case 379: // Type 379
	{
		double xi = fmax(fabs(aa),0.01f); double L = fabs(ab)*r; double overlap = exp(-L/xi); double gap = fabs(ac); aux.DE *= (1.0f + af * overlap*gap);
		break;
	}
	case 380: // Type 380
	{
		double J = fabs(aa)+0.01f; double alpha = fabs(ab)+0.01f; double g = fabs(ac)+0.01f; double gap = J*exp(-1.0f/(alpha*g)); aux.DE *= (1.0f + af * gap * sin(ad*r)*sin(ad*r));
		break;
	}
	case 381: // Type 381
	{
		double J = fabs(aa)+0.01f; double h = fabs(ab)+0.01f; double gap = fabs(J-h)/J; double crit_exp = fabs(ac)+0.5f; aux.DE *= (1.0f + af * pow(fmax(gap,1e-10), crit_exp));
		break;
	}
	case 382: // Type 382
	{
		double J = aa; double Si = sin(ab*z.x); double Sj = sin(ab*z.y); double coupling = J*Si*Sj; aux.DE *= (1.0f + af * fabs(coupling));
		break;
	}
	case 383: // Type 383
	{
		double J = aa; double Sx = sin(ab*z.x)*cos(ac*z.y); double Sy = cos(ab*z.x)*sin(ac*z.y); double coupling = J*(Sx+Sy); aux.DE *= (1.0f + af * fabs(coupling));
		break;
	}
	case 384: // Type 384
	{
		double J = aa; double q = fmax(floor(fabs(ab)*5+2), 2.0f); double sigma_i = floor(sin(ac*z.x)*q); double sigma_j = floor(sin(ac*z.y)*q); double delta_s = (sigma_i == sigma_j) ? 1.0f : 0.0f; aux.DE *= (1.0f + af * J*delta_s);
		break;
	}
	case 385: // Type 385
	{
		double J = aa; double q = fmax(floor(fabs(ab)*5+2), 2.0f); double angle = 2.0f*M_PI/q; double sigma_diff = sin(ac*z.x) - sin(ac*z.y); aux.DE *= (1.0f + af * J*cos(angle*sigma_diff));
		break;
	}
	case 386: // Type 386
	{
		double J = aa; double lambda = ab; double sigma = sin(ac*z.x)*sin(ac*z.y); double tau = cos(ad*z.x)*cos(ad*z.y); double coupling = J*(sigma + tau + lambda*sigma*tau); aux.DE *= (1.0f + af * fabs(coupling));
		break;
	}
	case 387: // Type 387
	{
		double W = aa; double X = ab; double Y = ac; double sigma = sin(ad*z.x)*sin(ad*z.y); double tau = cos(ad*z.x)*cos(ad*z.y); double v = W*sigma + X*tau + Y*sigma*tau; aux.DE *= (1.0f + af * fabs(v));
		break;
	}
	case 388: // Type 388
	{
		double U = fabs(aa)+0.01f; double t = fabs(ab)+0.01f; double n_up = sin(ac*z.x)*sin(ac*z.x); double n_down = cos(ac*z.y)*cos(ac*z.y); double mott = U*n_up*n_down/t; aux.DE *= (1.0f + af * fmin(mott,10.0f));
		break;
	}
	case 389: // Type 389
	{
		double t = fabs(aa)+0.01f; double J = ab; double hop = t*sin(ac*z.x)*cos(ac*z.y); double exchange = J*sin(ad*z.x)*sin(ad*z.y); aux.DE *= (1.0f + af * fabs(hop + exchange));
		break;
	}
	case 390: // Type 390
	{
		double xi_loc = fmax(fabs(aa),0.01f); double disorder = fabs(ab); double loc = exp(-r/xi_loc)*disorder; aux.DE *= (1.0f + af * loc);
		break;
	}
	case 391: // Type 391
	{
		double U = fabs(aa)+0.01f; double U_c = fabs(ab)+0.01f; double n = sin(ac*r)*0.5f+0.5f; double gap = (U/U_c)*(n-0.5f)*(n-0.5f); aux.DE *= (1.0f + af * fmin(gap*4.0f,10.0f));
		break;
	}
	case 392: // Type 392
	{
		double alpha = aa; double u = ab; double k_F = ac; double gap = 2.0f*fabs(alpha*u)*fabs(cos(2.0f*k_F*z.x)); aux.DE *= (1.0f + af * fmin(gap,10.0f));
		break;
	}
	case 393: // Type 393
	{
		double J = fabs(aa)+0.01f; double g = fabs(ab)+0.01f; double gap = J*exp(-M_PI*J/(g*g)); double singlet = cos(ac*z.x)*cos(ac*z.y); aux.DE *= (1.0f + af * gap*singlet*singlet);
		break;
	}
	case 394: // Type 394
	{
		double J = fabs(aa)+0.01f; double S = fmax(floor(fabs(ab)+1),1.0f); double gap = J*exp(-M_PI*S); double string_order = sin(ac*r); aux.DE *= (1.0f + af * gap*string_order*string_order);
		break;
	}
	case 395: // Type 395
	{
		double J = fabs(aa)+0.01f; double SiSj = sin(ab*z.x)*sin(ab*z.y); double SiSj2 = SiSj*SiSj; double aklt = J*(SiSj + SiSj2/3.0f); aux.DE *= (1.0f + af * fabs(aklt));
		break;
	}
	case 396: // Type 396
	{
		double J = fabs(aa)+0.01f; double Av = sin(ab*z.x)*sin(ab*z.y); double Bp = cos(ac*z.x)*cos(ac*z.y); double toric = 4.0f*J*(Av*Av + Bp*Bp); aux.DE *= (1.0f + af * fmin(toric,10.0f));
		break;
	}
	case 397: // Type 397
	{
		double F1 = sin(aa*z.x); double F2 = sin(ab*z.y); double F3 = cos(ac*z.x); double F4 = cos(ad*z.y); double wen = F1*F2*F3*F4; aux.DE *= (1.0f + af * fabs(wen));
		break;
	}
	case 398: // Type 398
	{
		double sn = sin(aa*z.x+ab*z.y); double fusion = sn*sn; double F_sym = cos(ac*r)*cos(ac*r); double lw = fusion*F_sym; aux.DE *= (1.0f + af * lw);
		break;
	}
	case 399: // Type 399
	{
		double psi = sin(aa*z.x + ab*(double)i*0.1f); double coin = cos(ac*z.y); double walker = psi*psi*coin*coin; aux.DE *= (1.0f + af * walker);
		break;
	}
	case 400: // Type 400
	{
		double rule = sin(aa*z.x)*sin(ab*z.y)*cos(ac*z.z); double evolution = cos(ad*(double)i*0.1f); double qca = rule*evolution; aux.DE *= (1.0f + af * qca*qca);
		break;
	}
	default: break;
}