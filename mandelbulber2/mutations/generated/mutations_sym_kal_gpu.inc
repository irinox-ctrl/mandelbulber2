// Auto-generated mutation switch for system: sym_kal
// Target: GPU
// Generated mutations: 100
switch (mut->symKalType)
{
	case 1: // Type 1
	{
		z.x = fabs(z.x);
		break;
	}
	case 2: // Type 2
	{
		z.y = fabs(z.y);
		break;
	}
	case 3: // Type 3
	{
		z.z = fabs(z.z);
		break;
	}
	case 4: // Type 4
	{
		z.x = fabs(z.x); z.y = fabs(z.y);
		break;
	}
	case 5: // Type 5
	{
		z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z);
		break;
	}
	case 6: // Type 6
	{
		if(z.x < 0) z.x = -z.x - soff; else z.x = z.x + soff;
		break;
	}
	case 7: // Type 7
	{
		if(z.y < 0) z.y = -z.y - soff; else z.y = z.y + soff;
		break;
	}
	case 8: // Type 8
	{
		if(z.x + z.y < 0) { double t = z.x; z.x = -z.y; z.y = -t; }
		break;
	}
	case 9: // Type 9
	{
		if(z.x - z.y < 0) { double t = z.x; z.x = z.y; z.y = t; }
		break;
	}
	case 10: // Type 10
	{
		if(z.x + z.z < 0) { double t = z.x; z.x = -z.z; z.z = -t; }
		break;
	}
	case 11: // Type 11
	{
		{ double ang2 = atan2(zy, zx); double n = fmax(1.0f, sa); double sector = 2.0f*M_PI/n; ang2 = fmod(ang2 + 10.0f*M_PI, sector) - sector*0.5f; double rxy = sqrt(zx*zx+zy*zy); z.x = rxy*cos(ang2); z.y = rxy*sin(ang2); }
		break;
	}
	case 12: // Type 12
	{
		{ double ang2 = atan2(zy, zx); double n = 3.0f; double sector = 2.0f*M_PI/n; ang2 = fmod(ang2 + 10.0f*M_PI, sector) - sector*0.5f; double rxy = sqrt(zx*zx+zy*zy); z.x = rxy*cos(ang2); z.y = rxy*sin(ang2); }
		break;
	}
	case 13: // Type 13
	{
		{ double ang2 = atan2(zy, zx); double n = 4.0f; double sector = 2.0f*M_PI/n; ang2 = fmod(ang2 + 10.0f*M_PI, sector) - sector*0.5f; double rxy = sqrt(zx*zx+zy*zy); z.x = rxy*cos(ang2); z.y = rxy*sin(ang2); }
		break;
	}
	case 14: // Type 14
	{
		{ double ang2 = atan2(zy, zx); double n = 5.0f; double sector = 2.0f*M_PI/n; ang2 = fmod(ang2 + 10.0f*M_PI, sector) - sector*0.5f; double rxy = sqrt(zx*zx+zy*zy); z.x = rxy*cos(ang2); z.y = rxy*sin(ang2); }
		break;
	}
	case 15: // Type 15
	{
		{ double ang2 = atan2(zy, zx); double n = 6.0f; double sector = 2.0f*M_PI/n; ang2 = fmod(ang2 + 10.0f*M_PI, sector) - sector*0.5f; double rxy = sqrt(zx*zx+zy*zy); z.x = rxy*cos(ang2); z.y = rxy*sin(ang2); }
		break;
	}
	case 16: // Type 16
	{
		{ double ang2 = atan2(zy, zx); double n = 8.0f; double sector = 2.0f*M_PI/n; ang2 = fmod(ang2 + 10.0f*M_PI, sector) - sector*0.5f; double rxy = sqrt(zx*zx+zy*zy); z.x = rxy*cos(ang2); z.y = rxy*sin(ang2); }
		break;
	}
	case 17: // Type 17
	{
		{ double ang2 = atan2(zy, zx); double n = 12.0f; double sector = 2.0f*M_PI/n; ang2 = fmod(ang2 + 10.0f*M_PI, sector) - sector*0.5f; double rxy = sqrt(zx*zx+zy*zy); z.x = rxy*cos(ang2); z.y = rxy*sin(ang2); }
		break;
	}
	case 18: // Type 18
	{
		{ double ang2 = atan2(zz2, zx); double n = fmax(1.0f, sa); double sector = 2.0f*M_PI/n; ang2 = fmod(ang2 + 10.0f*M_PI, sector) - sector*0.5f; double rxz = sqrt(zx*zx+zz2*zz2); z.x = rxz*cos(ang2); z.z = rxz*sin(ang2); }
		break;
	}
	case 19: // Type 19
	{
		{ double ang2 = atan2(zz2, zy); double n = fmax(1.0f, sa); double sector = 2.0f*M_PI/n; ang2 = fmod(ang2 + 10.0f*M_PI, sector) - sector*0.5f; double ryz = sqrt(zy*zy+zz2*zz2); z.y = ryz*cos(ang2); z.z = ryz*sin(ang2); }
		break;
	}
	case 20: // Type 20
	{
		{ double ang2 = atan2(zy, zx); double n = fmax(1.0f, sa); double sector = 2.0f*M_PI/n; ang2 = fmod(ang2 + 10.0f*M_PI, sector); if(fmod(floor(ang2/sector), 2.0f) > 0.5f) ang2 = sector - fmod(ang2, sector); else ang2 = fmod(ang2, sector); ang2 -= sector*0.5f; double rxy = sqrt(zx*zx+zy*zy); z.x = rxy*cos(ang2); z.y = rxy*sin(ang2); }
		break;
	}
	case 21: // Type 21
	{
		{ double cs = cos(sang), sn = sin(sang); double nx = zx*cs - zy*sn; z.y = zx*sn + zy*cs; z.x = fabs(nx); }
		break;
	}
	case 22: // Type 22
	{
		{ double cs = cos(sang), sn = sin(sang); z.x = fabs(zx); double nx = zx*cs - zy*sn; z.y = zx*sn + zy*cs; z.x = nx; z.x = fabs(z.x); }
		break;
	}
	case 23: // Type 23
	{
		{ if(z.x + z.y < soff) { double t = z.x; z.x = -z.y; z.y = -t; } double cs = cos(sang), sn = sin(sang); double nx = zx*cs - zy*sn; z.y = zx*sn + zy*cs; z.x = nx; }
		break;
	}
	case 24: // Type 24
	{
		{ z.x = fabs(z.x); z.y = fabs(z.y); double cs = cos(sang), sn = sin(sang); double nx = z.x*cs - z.y*sn; z.y = z.x*sn + z.y*cs; z.x = nx; z.x = fabs(z.x); }
		break;
	}
	case 25: // Type 25
	{
		{ z.x = fabs(z.x) + soff; z.y = fabs(z.y) + soff; double cs = cos(sang), sn = sin(sang); double nx = z.x*cs - z.y*sn; z.y = z.x*sn + z.y*cs; z.x = nx; }
		break;
	}
	case 26: // Type 26
	{
		{ for(int k=0; k<int(sa); k++) { z.x = fabs(z.x); z.y = fabs(z.y); double cs = cos(sang), sn = sin(sang); double nx = z.x*cs - z.y*sn; z.y = z.x*sn + z.y*cs; z.x = nx; } }
		break;
	}
	case 27: // Type 27
	{
		{ for(int k=0; k<int(sa); k++) { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); double cs = cos(sang+k*sb), sn = sin(sang+k*sb); double nx = z.x*cs - z.y*sn; z.y = z.x*sn + z.y*cs; z.x = nx; } }
		break;
	}
	case 28: // Type 28
	{
		{ double cs1 = cos(sang), sn1 = sin(sang); double nx = zx*cs1 - zy*sn1; z.y = zx*sn1 + zy*cs1; z.x = nx; z.x = fabs(z.x); double cs2 = cos(-sang), sn2 = sin(-sang); nx = z.x*cs2 - z.y*sn2; z.y = z.x*sn2 + z.y*cs2; z.x = nx; }
		break;
	}
	case 29: // Type 29
	{
		{ z.x = fabs(z.x); if(z.x - z.y < 0) { double t = z.x; z.x = z.y; z.y = t; } z.y = fabs(z.y); double cs = cos(sang), sn = sin(sang); double nx = z.x*cs - z.z*sn; z.z = z.x*sn + z.z*cs; z.x = nx; }
		break;
	}
	case 30: // Type 30
	{
		{ double n = fmax(2.0f, sa); for(int k=0; k<int(n); k++) { double a = k * 2.0f*M_PI/n; double cs = cos(a), sn = sin(a); double d = z.x*cs + z.y*sn; if(d < 0) { z.x -= 2.0f*d*cs; z.y -= 2.0f*d*sn; } } }
		break;
	}
	case 31: // Type 31
	{
		{ z.x = fabs(z.x); z.y = fabs(z.y); if(z.y > z.x) { double t=z.x; z.x=z.y; z.y=t; } z.x -= sa; z.y -= sb; }
		break;
	}
	case 32: // Type 32
	{
		{ z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); if(z.y > z.x) { double t=z.x; z.x=z.y; z.y=t; } if(z.z > z.x) { double t=z.x; z.x=z.z; z.z=t; } if(z.z > z.y) { double t=z.y; z.y=z.z; z.z=t; } z.x -= sa; z.y -= sb; z.z -= sc; }
		break;
	}
	case 33: // Type 33
	{
		{ z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); if(z.x - z.y < 0) { double t=z.x; z.x=z.y; z.y=t; } if(z.x - z.z < 0) { double t=z.x; z.x=z.z; z.z=t; } if(z.y - z.z < 0) { double t=z.y; z.y=z.z; z.z=t; } z.x -= sa; z.y -= sb; z.z -= sc; double cs = cos(sang), sn = sin(sang); double nx = z.x*cs - z.y*sn; z.y = z.x*sn + z.y*cs; z.x = nx; }
		break;
	}
	case 34: // Type 34
	{
		{ z.x = fabs(z.x); z.y = fabs(z.y); double d = z.x*cos(sang) + z.y*sin(sang); if(d < 0) { z.x -= 2.0f*d*cos(sang); z.y -= 2.0f*d*sin(sang); } z.x -= sa; z.y -= sb; z.z -= 0; }
		break;
	}
	case 35: // Type 35
	{
		{ z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); z.x -= sa; z.y -= sb; z.z -= sc; if(z.y > z.x) { double t=z.x; z.x=z.y; z.y=t; } if(z.z > z.x) { double t=z.x; z.x=z.z; z.z=t; } if(z.z > z.y) { double t=z.y; z.y=z.z; z.z=t; } }
		break;
	}
	case 36: // Type 36
	{
		{ double d = 2.0f*fmax(0.0f, z.x*cos(sang) + z.y*sin(sang)); z.x -= d*cos(sang); z.y -= d*sin(sang); z.x = fabs(z.x); }
		break;
	}
	case 37: // Type 37
	{
		{ z.x = fabs(z.x); z.y = fabs(z.y); double a = sang; for(int k=0; k<3; k++) { double d = 2.0f*fmin(0.0f, z.x*cos(a) + z.y*sin(a)); z.x -= d*cos(a); z.y -= d*sin(a); a += M_PI/3.0f; } z.x -= sa; z.y -= sb; z.z -= 0; }
		break;
	}
	case 38: // Type 38
	{
		{ for(int k=0; k<int(fmax(1,sa)); k++) { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); z.x -= sb; z.y -= sc; z.z -= sd; if(z.y > z.x) { double t=z.x; z.x=z.y; z.y=t; } if(z.z > z.x) { double t=z.x; z.x=z.z; z.z=t; } if(z.z > z.y) { double t=z.y; z.y=z.z; z.z=t; } z *= sf; aux.DE *= fabs(sf); } }
		break;
	}
	case 39: // Type 39
	{
		{ for(int k=0; k<int(fmax(1,sa)); k++) { double cs = cos(sang+k*sb), sn = sin(sang+k*sb); double d = z.x*cs + z.y*sn; if(d < 0) { z.x -= 2.0f*d*cs; z.y -= 2.0f*d*sn; } z.x = fabs(z.x) - sc; z.y = fabs(z.y) - sd; } }
		break;
	}
	case 40: // Type 40
	{
		{ z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); z.x = z.x - sa*round(z.x/fmax(sa,1e-21)); z.y = z.y - sb*round(z.y/fmax(sb,1e-21)); z.z = z.z - sc*round(z.z/fmax(sc,1e-21)); }
		break;
	}
	case 41: // Type 41
	{
		{ z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); if(z.x - z.y < 0) { double t=z.x; z.x=z.y; z.y=t; } if(z.x - z.z < 0) { double t=z.x; z.x=z.z; z.z=t; } if(z.y - z.z < 0) { double t=z.y; z.y=z.z; z.z=t; } z *= sf; { double _cF=(sf-1.0f); z.x -= sa*_cF; z.y -= sb*_cF; z.z -= sc*_cF; }; aux.DE = aux.DE * fabs(sf) + 1.0f; }
		break;
	}
	case 42: // Type 42
	{
		{ if(z.x + z.y < 0) { double t=-z.y; z.y=-z.x; z.x=t; } if(z.x + z.z < 0) { double t=-z.z; z.z=-z.x; z.x=t; } if(z.y + z.z < 0) { double t=-z.z; z.z=-z.y; z.y=t; } z *= sf; { double _cF=(sf-1.0f); z.x -= sa*_cF; z.y -= sb*_cF; z.z -= sc*_cF; }; aux.DE = aux.DE * fabs(sf) + 1.0f; }
		break;
	}
	case 43: // Type 43
	{
		{ z.x = fabs(z.x); z.y = fabs(z.y); if(z.x - z.y < 0) { double t=z.x; z.x=z.y; z.y=t; } z.x -= sa; z *= sf; z.x += sa; aux.DE = aux.DE * fabs(sf) + 1.0f; }
		break;
	}
	case 44: // Type 44
	{
		{ z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); if(z.x - z.y < 0) { double t=z.x; z.x=z.y; z.y=t; } if(z.x - z.z < 0) { double t=z.x; z.x=z.z; z.z=t; } if(z.y - z.z < 0) { double t=z.y; z.y=z.z; z.z=t; } z.z -= 0.5f*sc*(sf-1.0f)/sf; z.z = fabs(z.z); z.z += 0.5f*sc*(sf-1.0f)/sf; z *= sf; { double _cF=(sf-1.0f); z.x -= sa*_cF; z.y -= sb*_cF; z.z -= sc*_cF; }; aux.DE = aux.DE*fabs(sf)+1.0f; }
		break;
	}
	case 45: // Type 45
	{
		{ z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); double t; if(z.x-z.y<0){t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0){t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0){t=z.y;z.y=z.z;z.z=t;} z *= sf; double _f45=(sf-1.0f)*sa; z.x -= _f45; z.y -= _f45; z.z -= _f45; aux.DE=aux.DE*fabs(sf)+1.0f; z.x=fabs(z.x); z.y=fabs(z.y); }
		break;
	}
	case 46: // Type 46
	{
		{ z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); double d1 = z.x - z.y; double d2 = z.y - z.z; if(d1 < 0){double t=z.x;z.x=z.y;z.y=t;} if(d2 < 0){double t=z.y;z.y=z.z;z.z=t;} if(z.x-z.y < 0){double t=z.x;z.x=z.y;z.y=t;} z.x -= sa; z.y -= sb; z.z -= sc; z *= sf; z.x += sa; z.y += sb; z.z += sc; aux.DE = aux.DE*fabs(sf)+1.0f; }
		break;
	}
	case 47: // Type 47
	{
		{ z.x = sa - fabs(z.x - sa); z.y = sb - fabs(z.y - sb); z.z = sc - fabs(z.z - sc); }
		break;
	}
	case 48: // Type 48
	{
		{ z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); if(z.x>sa) z.x=2.0f*sa-z.x; if(z.y>sb) z.y=2.0f*sb-z.y; if(z.z>sc) z.z=2.0f*sc-z.z; }
		break;
	}
	case 49: // Type 49
	{
		{ double p=sa; z.x = z.x - p*floor(z.x/p+0.5f); z.y = z.y - p*floor(z.y/p+0.5f); z.z = z.z - p*floor(z.z/p+0.5f); }
		break;
	}
	case 50: // Type 50
	{
		{ double px=sa, py=sb; z.x = z.x - px*floor(z.x/px+0.5f); z.y = z.y - py*floor(z.y/py+0.5f); }
		break;
	}
	case 51: // Type 51
	{
		{ double ph2=atan2(zy,zx); double n=fmax(1.0f,sa); double s=2.0f*M_PI/n; ph2=fmod(ph2+10.0f*M_PI,s)-s*0.5f; double rxy=sqrt(zx*zx+zy*zy); z.x=rxy*cos(ph2); z.y=rxy*sin(ph2); z.z=fabs(z.z); }
		break;
	}
	case 52: // Type 52
	{
		{ double ph2=atan2(zy,zx); double th=acos(zz2/r); double n=fmax(1.0f,sa); double sp=2.0f*M_PI/n; ph2=fmod(ph2+10.0f*M_PI,sp)-sp*0.5f; double m=fmax(1.0f,sb); double st=M_PI/m; th=fmod(th+10.0f*M_PI,st); z.x=r*sin(th)*cos(ph2); z.y=r*sin(th)*sin(ph2); z.z=r*cos(th); }
		break;
	}
	case 53: // Type 53
	{
		{ double ph2=atan2(zy,zx)+sang; double rxy=sqrt(zx*zx+zy*zy); z.x=rxy*cos(ph2); z.y=rxy*sin(ph2); z.z=fabs(zz2); }
		break;
	}
	case 54: // Type 54
	{
		{ double rxy=sqrt(zx*zx+zy*zy); if(rxy>sa) { double f=sa/rxy; z.x*=f; z.y*=f; } }
		break;
	}
	case 55: // Type 55
	{
		{ if(r>sa) z*=sa/r; }
		break;
	}
	case 56: // Type 56
	{
		{ if(r<sa) z*=sa*sa/(r*r); else if(r<sb) z*=sa*sa/(r*r); }
		break;
	}
	case 57: // Type 57
	{
		{ double rr=r*r; if(rr<sa*sa) z*=sb*sb/(sa*sa); else if(rr<sb*sb) z*=sb*sb/rr; }
		break;
	}
	case 58: // Type 58
	{
		{ double th=acos(zz2/r); double n=fmax(1.0f,sa); double st=M_PI/n; th=fmod(th+10.0f*M_PI,st); z.x=r*sin(th)*cos(atan2(zy,zx)); z.y=r*sin(th)*sin(atan2(zy,zx)); z.z=r*cos(th); }
		break;
	}
	case 59: // Type 59
	{
		{ double p=sa; z.x=z.x-p*round(z.x/p); z.y=z.y-p*round(z.y/p); z.z=z.z-p*round(z.z/p); }
		break;
	}
	case 60: // Type 60
	{
		{ z.x=fabs(z.x)-sa; z.y=fabs(z.y)-sb; z.z=fabs(z.z)-sc; if(z.x<0) z.x=-z.x; if(z.y<0) z.y=-z.y; if(z.z<0) z.z=-z.z; }
		break;
	}
	case 61: // Type 61
	{
		{ double px=fmax(sa,0.01f); z.x=z.x-px*floor(z.x/px); z.y=fabs(z.y); }
		break;
	}
	case 62: // Type 62
	{
		{ double px=fmax(sa,0.01f), py=fmax(sb,0.01f); z.x=z.x-px*floor(z.x/px); z.y=z.y-py*floor(z.y/py); }
		break;
	}
	case 63: // Type 63
	{
		{ double px=fmax(sa,0.01f), py=fmax(sb,0.01f); z.x=z.x-px*floor(z.x/px); z.y=z.y-py*floor(z.y/py); z.x=fabs(z.x-px*0.5f); }
		break;
	}
	case 64: // Type 64
	{
		{ double px=fmax(sa,0.01f), py=fmax(sb,0.01f); double ix=floor(z.x/px); z.x=z.x-px*ix; z.y=z.y-py*floor(z.y/py); if(fmod(ix,2.0f)>0.5f) z.x=px-z.x; }
		break;
	}
	case 65: // Type 65
	{
		{ double p=fmax(sa,0.01f); double a60=M_PI/3.0f; double ux=p, uy=0; double vx=p*cos(a60), vy=p*sin(a60); double det=ux*vy-uy*vx; double ix=floor((z.x*vy-z.y*vx)/det+0.5f); double iy=floor((z.y*ux-z.x*uy)/det+0.5f); z.x-=ix*ux+iy*vx; z.y-=ix*uy+iy*vy; }
		break;
	}
	case 66: // Type 66
	{
		{ double px=fmax(sa,0.01f), py=fmax(sb,0.01f), pz=fmax(sc,0.01f); z.x=z.x-px*floor(z.x/px); z.y=z.y-py*floor(z.y/py); z.z=z.z-pz*floor(z.z/pz); }
		break;
	}
	case 67: // Type 67
	{
		{ double px=fmax(sa,0.01f), py=fmax(sb,0.01f), pz=fmax(sc,0.01f); z.x=z.x-px*round(z.x/px); z.y=z.y-py*round(z.y/py); z.z=z.z-pz*round(z.z/pz); z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); }
		break;
	}
	case 68: // Type 68
	{
		{ double p=fmax(sa,0.01f); z.x=z.x-p*round(z.x/p); z.y=z.y-p*round(z.y/p); z.z=z.z-p*round(z.z/p); double cs=cos(sang),sn=sin(sang); double nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; }
		break;
	}
	case 69: // Type 69
	{
		{ double p=fmax(sa,0.01f); double ix=round(z.x/p); double iy=round(z.y/p); z.x-=ix*p; z.y-=iy*p; double a=sang*(ix+iy); double cs=cos(a),sn=sin(a); double nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; }
		break;
	}
	case 70: // Type 70
	{
		{ double p=fmax(sa,0.01f); z.x=z.x-p*floor(z.x/p+0.5f); z.y=z.y-p*floor(z.y/p+0.5f); double cs=cos(sang),sn=sin(sang); if(z.x+z.y>0) { double nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; } }
		break;
	}
	case 71: // Type 71
	{
		if(z.x*z.y > 0) { double t=z.x; z.x=z.y; z.y=t; }
		break;
	}
	case 72: // Type 72
	{
		if(z.x*z.y < 0) { z.x = fabs(z.x); z.y = fabs(z.y); }
		break;
	}
	case 73: // Type 73
	{
		if(r < sa) { z *= sf; aux.DE *= fabs(sf); } else { z.x = fabs(z.x); z.y = fabs(z.y); }
		break;
	}
	case 74: // Type 74
	{
		if(fmod(double(i), sa) < sb) { z.x = fabs(z.x); z.y = fabs(z.y); z.z = fabs(z.z); }
		break;
	}
	case 75: // Type 75
	{
		{ double d = z.x*cos(sang) + z.y*sin(sang); if(d < soff) { z.x -= 2.0f*(d-soff)*cos(sang); z.y -= 2.0f*(d-soff)*sin(sang); } }
		break;
	}
	case 76: // Type 76
	{
		{ double d1 = z.x*cos(sang)+z.y*sin(sang); if(d1<0){z.x-=2.0f*d1*cos(sang);z.y-=2.0f*d1*sin(sang);} double a2=sang+M_PI/fmax(1.0f,sa); double d2=z.x*cos(a2)+z.y*sin(a2); if(d2<0){z.x-=2.0f*d2*cos(a2);z.y-=2.0f*d2*sin(a2);} }
		break;
	}
	case 77: // Type 77
	{
		{ for(int k=0;k<int(fmax(1,sa));k++){ z.x=fabs(z.x)-sb; z.y=fabs(z.y)-sc; if(z.x<z.y){double t=z.x;z.x=z.y;z.y=t;} } }
		break;
	}
	case 78: // Type 78
	{
		{ z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); double m=fmax(fmax(z.x,z.y),z.z); if(m==z.y){double t=z.x;z.x=z.y;z.y=t;} if(m==z.z){double t=z.x;z.x=z.z;z.z=t;} }
		break;
	}
	case 79: // Type 79
	{
		{ z.x = sa*floor(z.x/fmax(sa,0.01f)+0.5f)*2.0f-z.x; z.y = sb*floor(z.y/fmax(sb,0.01f)+0.5f)*2.0f-z.y; }
		break;
	}
	case 80: // Type 80
	{
		{ double a=sang; for(int k=0;k<3;k++){ z.x=fabs(z.x); double d=z.x*cos(a)+z.y*sin(a); if(d<0){z.x-=2.0f*d*cos(a);z.y-=2.0f*d*sin(a);} a+=M_PI/3.0f*sf; } }
		break;
	}
	case 81: // Type 81
	{
		{ double n=fmax(2.0f,sa+sb*sin(sfq*i)); double ang2=atan2(zy,zx); double s=2.0f*M_PI/n; ang2=fmod(ang2+10.0f*M_PI,s)-s*0.5f; double rxy=sqrt(zx*zx+zy*zy); z.x=rxy*cos(ang2); z.y=rxy*sin(ang2); }
		break;
	}
	case 82: // Type 82
	{
		{ double a=sang+sam*sin(sfq*i); double cs=cos(a),sn=sin(a); z.x=fabs(z.x); double nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; }
		break;
	}
	case 83: // Type 83
	{
		{ double d=sf*sam*sin(sfq*r+sang); z.x=fabs(z.x)+d; z.y=fabs(z.y)+d; z.z=fabs(z.z)+d; aux.DE*=(1.0f+fabs(d)/r); }
		break;
	}
	case 84: // Type 84
	{
		{ double n=fmax(2.0f,sa); double ang2=atan2(zy,zx); double s=2.0f*M_PI/n; ang2=fmod(ang2+10.0f*M_PI+sam*sin(sfq*i),s)-s*0.5f; double rxy=sqrt(zx*zx+zy*zy); z.x=rxy*cos(ang2); z.y=rxy*sin(ang2); }
		break;
	}
	case 85: // Type 85
	{
		{ z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); z *= sf + sam*sin(sfq*i); aux.DE *= fabs(sf + sam*sin(sfq*i)); { double _cF=(sf-1.0f); z.x -= sa*_cF; z.y -= sb*_cF; z.z -= sc*_cF; }; }
		break;
	}
	case 86: // Type 86
	{
		{ if(i%2==0){z.x=fabs(z.x);z.y=fabs(z.y);} else{double cs=cos(sang),sn=sin(sang);double nx=z.x*cs-z.y*sn;z.y=z.x*sn+z.y*cs;z.x=nx;} }
		break;
	}
	case 87: // Type 87
	{
		{ double rr=z.x*z.x+z.y*z.y+z.z*z.z; if(rr<sa*sa){z*=sb*sb/(sa*sa);aux.DE*=sb*sb/(sa*sa);} else if(rr<sb*sb){z*=sb*sb/rr;aux.DE*=sb*sb/rr;} z.x=fabs(z.x); z.y=fabs(z.y); }
		break;
	}
	case 88: // Type 88
	{
		{ if(z.x+z.y<0){double t=-z.y;z.y=-z.x;z.x=t;} if(z.x+z.z<0){double t=-z.z;z.z=-z.x;z.x=t;} z *= sf; { double _cF=(sf-1.0f); z.x -= sa*_cF; z.y -= sb*_cF; z.z -= sc*_cF; }; aux.DE=aux.DE*fabs(sf)+1.0f; if(z.y-z.z<0){double t=z.y;z.y=z.z;z.z=t;} }
		break;
	}
	case 89: // Type 89
	{
		{ z.x=fabs(z.x)-sa; z.y=fabs(z.y)-sb; if(z.x<z.y){double t=z.x;z.x=z.y;z.y=t;} double rr=z.x*z.x+z.y*z.y+z.z*z.z; if(rr<sc*sc){double m=sd*sd/(sc*sc);z*=m;aux.DE*=m;} else if(rr<sd*sd){double m=sd*sd/rr;z*=m;aux.DE*=m;} }
		break;
	}
	case 90: // Type 90
	{
		{ double p=fmax(sa,0.01f); z.x=z.x-p*round(z.x/p); z.y=z.y-p*round(z.y/p); z.x=fabs(z.x); z.y=fabs(z.y); if(z.x<z.y){double t=z.x;z.x=z.y;z.y=t;} z *= sf; aux.DE *= fabs(sf); { double _cF=(sf-1.0f); z.x -= sb*_cF; z.y -= sc*_cF; z.z -= 0*_cF; }; }
		break;
	}
	case 91: // Type 91
	{
		{ z.x=fabs(z.x)-sa; z.y=fabs(z.y)-sb; z.z=fabs(z.z)-sc; if(z.x<z.y){double t=z.x;z.x=z.y;z.y=t;} if(z.x<z.z){double t=z.x;z.x=z.z;z.z=t;} if(z.y<z.z){double t=z.y;z.y=z.z;z.z=t;} z*=sf; aux.DE*=fabs(sf); z.x += sa; z.y += sb; z.z += sc; }
		break;
	}
	case 92: // Type 92
	{
		{ double cs=cos(sang),sn=sin(sang); z.x=fabs(z.x); z.y=fabs(z.y); double d=z.x*sn+z.y*cs; if(d<0){z.x-=2.0f*d*sn;z.y-=2.0f*d*cs;} z.x-=sa; z.y-=sb; z*=sf; z.x+=sa; z.y+=sb; aux.DE=aux.DE*fabs(sf)+1.0f; }
		break;
	}
	case 93: // Type 93
	{
		{ z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); if(z.x-z.y<0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0){double t=z.x;z.x=z.z;z.z=t;} z*=sf; z.x-=sa*(sf-1.0f); z.y-=sb*(sf-1.0f); z.z-=sc*(sf-1.0f); double rr=z.x*z.x+z.y*z.y+z.z*z.z; if(rr<sd*sd){z*=sd*sd/rr;aux.DE*=sd*sd/rr;} aux.DE=aux.DE*fabs(sf)+1.0f; }
		break;
	}
	case 94: // Type 94
	{
		{ for(int k=0;k<int(fmax(1,sa));k++){ z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); if(z.x-z.y<0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0){double t=z.y;z.y=z.z;z.z=t;} z.x-=sb; z.y-=sc; z.z-=sd; double cs=cos(sang+k*sfq),sn=sin(sang+k*sfq); double nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; z.x+=sb; z.y+=sc; z.z+=sd; } }
		break;
	}
	case 95: // Type 95
	{
		{ double n=fmax(2.0f,sa); for(int k=0;k<int(n);k++){ double a=k*M_PI/n; double d=z.x*cos(a)+z.y*sin(a); if(d<0){z.x-=2.0f*d*cos(a);z.y-=2.0f*d*sin(a);} } z.z=fabs(z.z); }
		break;
	}
	case 96: // Type 96
	{
		{ z=fabs(z); if(z.x<z.y){double t=z.x;z.x=z.y;z.y=t;} if(z.x<z.z){double t=z.x;z.x=z.z;z.z=t;} if(z.y<z.z){double t=z.y;z.y=z.z;z.z=t;} z.x -= sa; z.y -= sb; z.z -= sc; double rr=z.x*z.x+z.y*z.y+z.z*z.z; if(rr<sd*sd){double m=sf*sf/fmax(rr,1e-21);z*=m;aux.DE*=m;} z*=sf;aux.DE*=fabs(sf); z.x += sa; z.y += sb; z.z += sc; }
		break;
	}
	case 97: // Type 97
	{
		{ double a=2.0f*M_PI/fmax(1.0f,sa); double cs=cos(a),sn=sin(a); z.x=fabs(z.x); z.y=fabs(z.y); double d=z.x*sn+z.y*cs-soff; if(d>0){z.x-=d*sn;z.y-=d*cs;} z.x-=sb; z*=sf; z.x+=sb; aux.DE=aux.DE*fabs(sf)+1.0f; }
		break;
	}
	case 98: // Type 98
	{
		{ z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); double d=2.0f*fmin(0.0f,z.x+z.y+z.z-sa); z.x-=d/3.0f; z.y-=d/3.0f; z.z-=d/3.0f; }
		break;
	}
	case 99: // Type 99
	{
		{ z.x=fabs(z.x); z.y=fabs(z.y); z.z=fabs(z.z); if(z.x-z.y<0){double t=z.x;z.x=z.y;z.y=t;} if(z.x-z.z<0){double t=z.x;z.x=z.z;z.z=t;} if(z.y-z.z<0){double t=z.y;z.y=z.z;z.z=t;} z.z-=0.5f*sa; z.z=-fabs(z.z)+0.5f*sa; double cs=cos(sang),sn=sin(sang); double nx=z.x*cs-z.y*sn; z.y=z.x*sn+z.y*cs; z.x=nx; }
		break;
	}
	case 100: // Type 100
	{
		{ z.x=fabs(z.x)-sa; z.y=fabs(z.y)-sb; z.z=fabs(z.z)-sc; if(z.x<z.y){double t=z.x;z.x=z.y;z.y=t;} if(z.x<z.z){double t=z.x;z.x=z.z;z.z=t;} if(z.y<z.z){double t=z.y;z.y=z.z;z.z=t;} double rr=z.x*z.x+z.y*z.y+z.z*z.z; if(rr<sd*sd){double m=sf*sf/fmax(rr,1e-21);z*=m;aux.DE*=m;} z*=sf; aux.DE=aux.DE*fabs(sf)+1.0f; { double _cF=(1.0f-sf); z.x += sa*_cF; z.y += sb*_cF; z.z += sc*_cF; }; }
		break;
	}
	default: break;
}