// Auto-generated mutation switch for system: noise
// Target: CPU
// Generated mutations: 100
switch (mut.noiseType)
{
	case 1: // Type 1
	{
		double h = sin(na*z.x*12.9898 + nb*z.y*78.233 + nc*z.z*45.164)*43758.5453; h = h - floor(h); aux.DE *= (1.0 + nf*h);
		break;
	}
	case 2: // Type 2
	{
		double h1 = sin(na*z.x*12.9898 + z.y*78.233)*43758.5453; h1=h1-floor(h1); double h2 = sin(z.y*12.9898 + na*z.z*78.233)*43758.5453; h2=h2-floor(h2); aux.DE *= (1.0 + nf*(h1+h2)*0.5);
		break;
	}
	case 3: // Type 3
	{
		double p = na*z.x + nb*z.y + nc*z.z; double h = sin(p*127.1)*43758.5453; h=h-floor(h); double h2 = sin(p*269.5)*43758.5453; h2=h2-floor(h2); aux.DE *= (1.0 + nf*fabs(h-h2));
		break;
	}
	case 4: // Type 4
	{
		double fx = z.x*nfq; double fy = z.y*nfq; double fz = z.z*nfq; double ix = floor(fx); double iy = floor(fy); double iz = floor(fz); double tx = fx-ix; double ty = fy-iy; double tz = fz-iz; double h000 = sin(ix*127.1+iy*311.7+iz*74.7)*43758.5453; h000=h000-floor(h000); double h100 = sin((ix+1)*127.1+iy*311.7+iz*74.7)*43758.5453; h100=h100-floor(h100); double v = h000*(1.0-tx) + h100*tx; aux.DE *= (1.0 + nf*v);
		break;
	}
	case 5: // Type 5
	{
		double fx = z.x*nfq; double fy = z.y*nfq; double h00 = sin(floor(fx)*127.1+floor(fy)*311.7)*43758.5453; h00=h00-floor(h00); double h10 = sin((floor(fx)+1)*127.1+floor(fy)*311.7)*43758.5453; h10=h10-floor(h10); double h01 = sin(floor(fx)*127.1+(floor(fy)+1)*311.7)*43758.5453; h01=h01-floor(h01); double h11 = sin((floor(fx)+1)*127.1+(floor(fy)+1)*311.7)*43758.5453; h11=h11-floor(h11); double tx=fx-floor(fx); double ty=fy-floor(fy); double v = h00*(1-tx)*(1-ty)+h10*tx*(1-ty)+h01*(1-tx)*ty+h11*tx*ty; aux.DE *= (1.0 + nf*v);
		break;
	}
	case 6: // Type 6
	{
		double h = sin(z.x*na*12.9898 + z.y*nb*78.233 + z.z*nc*45.164 + nd*i)*43758.5453; h=h-floor(h); h = h*h*(3.0-2.0*h); aux.DE *= (1.0 + nf*h);
		break;
	}
	case 7: // Type 7
	{
		double h = sin(z.x*nfq + z.y*nfq*1.3 + z.z*nfq*0.7)*43758.5453; h=h-floor(h); h = 6.0*h*h*h*h*h - 15.0*h*h*h*h + 10.0*h*h*h; aux.DE *= (1.0 + nf*h);
		break;
	}
	case 8: // Type 8
	{
		double p = na*z.x*nfq + nb*z.y*nfq + nc*z.z*nfq; double h = sin(p)*0.5+0.5; aux.DE *= (1.0 + nf*h*h);
		break;
	}
	case 9: // Type 9
	{
		double h1 = sin(z.x*nfq*12.9898)*43758.5453; h1=h1-floor(h1); double h2 = sin(z.y*nfq*78.233)*43758.5453; h2=h2-floor(h2); double h3 = sin(z.z*nfq*45.164)*43758.5453; h3=h3-floor(h3); aux.DE *= (1.0 + nf*(h1*h2*h3));
		break;
	}
	case 10: // Type 10
	{
		double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double h = sin(r*nfq)*43758.5453; h=h-floor(h); aux.DE *= (1.0 + nf*h);
		break;
	}
	case 11: // Type 11
	{
		double gx = sin(z.x*nfq*127.1+z.y*311.7)*2.0-1.0; double gy = sin(z.y*nfq*269.5+z.z*183.3)*2.0-1.0; double gz = sin(z.z*nfq*419.2+z.x*371.9)*2.0-1.0; double v = (gx*z.x+gy*z.y+gz*z.z)*nam; aux.DE *= (1.0 + nf*sin(v));
		break;
	}
	case 12: // Type 12
	{
		double px = z.x*nfq; double py = z.y*nfq; double g1 = sin(floor(px)*127.1+floor(py)*311.7)*2.0-1.0; double g2 = sin((floor(px)+1)*127.1+floor(py)*311.7)*2.0-1.0; double t = px-floor(px); t = t*t*(3.0-2.0*t); double v = g1*(1.0-t)+g2*t; aux.DE *= (1.0 + nf*v);
		break;
	}
	case 13: // Type 13
	{
		double px = z.x*nfq; double py = z.y*nfq; double pz = z.z*nfq; double g = sin(px*127.1+py*311.7+pz*74.7)*2.0-1.0; double t = g*g*(3.0-2.0*g); aux.DE *= (1.0 + nf*t*nam);
		break;
	}
	case 14: // Type 14
	{
		double v = sin(z.x*nfq)*cos(z.y*nfq*1.3)*sin(z.z*nfq*0.7); aux.DE *= (1.0 + nf*v*nam);
		break;
	}
	case 15: // Type 15
	{
		double v1 = sin(z.x*nfq+z.y*nfq*0.5); double v2 = sin(z.y*nfq*1.3+z.z*nfq*0.7); double v3 = sin(z.z*nfq*0.9+z.x*nfq*1.1); aux.DE *= (1.0 + nf*(v1+v2+v3)/3.0);
		break;
	}
	case 16: // Type 16
	{
		double px = z.x*nfq; double h = sin(px*12.9898+z.y*nfq*78.233)*43758.5453; h=h-floor(h); double g = (h*2.0-1.0)*(px-floor(px)); aux.DE *= (1.0 + nf*g);
		break;
	}
	case 17: // Type 17
	{
		double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double th = atan2(z.y,z.x); double v = sin(r*nfq+th*na)*nam; aux.DE *= (1.0 + nf*v);
		break;
	}
	case 18: // Type 18
	{
		double v = sin(z.x*nfq)*sin(z.y*nfq)*sin(z.z*nfq); v = v*v*(3.0-2.0*v); aux.DE *= (1.0 + nf*v*nam);
		break;
	}
	case 19: // Type 19
	{
		double dx = sin(z.x*nfq*12.9898)*2.0-1.0; double dy = sin(z.y*nfq*78.233)*2.0-1.0; double dz = sin(z.z*nfq*45.164)*2.0-1.0; double v = sqrt(dx*dx+dy*dy+dz*dz); aux.DE *= (1.0 + nf*(v-1.0)*nam);
		break;
	}
	case 20: // Type 20
	{
		double r = sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double phi = atan2(z.y,z.x); double theta = acos(z.z/fmax(r,1e-21)); double v = sin(r*nfq)*cos(phi*na)*sin(theta*nb); aux.DE *= (1.0 + nf*v);
		break;
	}
	case 21: // Type 21
	{
		double v=0, a=nam, f=nfq; for(int k=0;k<4;k++){ v += a*sin(z.x*f*12.9898+z.y*f*78.233+z.z*f*45.164); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 22: // Type 22
	{
		double v=0, a=nam, f=nfq; for(int k=0;k<6;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*h; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 23: // Type 23
	{
		double v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*fabs(h*2.0-1.0); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 24: // Type 24
	{
		double v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*(1.0-fabs(h*2.0-1.0)); f*=na; a*=nb; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 25: // Type 25
	{
		double v=0, a=nam, f=nfq, px=z.x,py=z.y,pz=z.z; for(int k=0;k<5;k++){ double h=sin(px*f*127.1+py*f*311.7+pz*f*74.7)*43758.5453; h=h-floor(h); v+=a*h; double d=sin(px*f*269.5+py*f*183.3)*43758.5453; d=d-floor(d); px+=d*na; py+=d*nb; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 26: // Type 26
	{
		double v=0, a=1.0, f=nfq, mx=0; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*h; mx+=a; f*=2.0; a*=0.5; } v/=fmax(mx,1e-21); aux.DE *= (1.0 + nf*v*nam);
		break;
	}
	case 27: // Type 27
	{
		double v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ double h1=sin(z.x*f+z.y*f*1.3)*0.5+0.5; double h2=sin(z.y*f*0.7+z.z*f*1.1)*0.5+0.5; v+=a*fmin(h1,h2); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 28: // Type 28
	{
		double v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ double h1=sin(z.x*f+z.y*f*1.3)*0.5+0.5; double h2=sin(z.y*f*0.7+z.z*f*1.1)*0.5+0.5; v+=a*fmax(h1,h2); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 29: // Type 29
	{
		double v=0, a=nam, f=nfq; double cs=cos(nd*M_PI/180.0), sn=sin(nd*M_PI/180.0); double px=z.x,py=z.y; for(int k=0;k<5;k++){ double h=sin(px*f*127.1+py*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*h; double nx=px*cs-py*sn; py=px*sn+py*cs; px=nx; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 30: // Type 30
	{
		double v=0, a=nam, f=nfq; for(int k=0;k<6;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*sin(h*M_PI); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 31: // Type 31
	{
		double v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ double r2=z.x*z.x+z.y*z.y+z.z*z.z; double h=sin(r2*f)*43758.5453; h=h-floor(h); v+=a*h; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 32: // Type 32
	{
		double v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f)*cos(z.y*f)*sin(z.z*f); v+=a*h; f*=na; a*=nb; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 33: // Type 33
	{
		double v=0, w=1.0, f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=w*h; w*=h; f*=2.0; } aux.DE *= (1.0 + nf*v*nam);
		break;
	}
	case 34: // Type 34
	{
		double v=1.0, f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v*=(h*0.5+0.75); f*=2.0; } aux.DE *= (1.0 + nf*(v-1.0)*nam);
		break;
	}
	case 35: // Type 35
	{
		double v=0, a=nam, f=nfq; double px=z.x,py=z.y,pz=z.z; for(int k=0;k<5;k++){ double h=sin(px*f*127.1+py*f*311.7+pz*f*74.7)*43758.5453; h=h-floor(h); v+=a*h; px=fabs(px)*2.0-na; py=fabs(py)*2.0-nb; pz=fabs(pz)*2.0-nc; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 36: // Type 36
	{
		double md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ double cx=floor(z.x*nfq)+dx+0.5; double cy=floor(z.y*nfq)+dy+0.5; double cz=floor(z.z*nfq)+dz+0.5; double h=sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); cx+=h*0.5; double d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md)md=d; } aux.DE *= (1.0 + nf*sqrt(md)*nam);
		break;
	}
	case 37: // Type 37
	{
		double md1=1e10,md2=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ double cx=floor(z.x*nfq)+dx; double cy=floor(z.y*nfq)+dy; double cz=floor(z.z*nfq)+dz; double h=sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); cx+=h; double d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md1){md2=md1;md1=d;}else if(d<md2)md2=d; } aux.DE *= (1.0 + nf*(sqrt(md2)-sqrt(md1))*nam);
		break;
	}
	case 38: // Type 38
	{
		double md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++){ double cx=floor(z.x*nfq)+dx+0.5; double cy=floor(z.y*nfq)+dy+0.5; double h=sin(cx*127.1+cy*311.7)*43758.5453; h=h-floor(h); cx+=h*0.5; double d=fabs(z.x*nfq-cx)+fabs(z.y*nfq-cy); if(d<md)md=d; } aux.DE *= (1.0 + nf*md*nam);
		break;
	}
	case 39: // Type 39
	{
		double md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ double cx=floor(z.x*nfq)+dx; double cy=floor(z.y*nfq)+dy; double cz=floor(z.z*nfq)+dz; double h=sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); cx+=h; double d=fmax(fabs(z.x*nfq-cx),fmax(fabs(z.y*nfq-cy),fabs(z.z*nfq-cz))); if(d<md)md=d; } aux.DE *= (1.0 + nf*md*nam);
		break;
	}
	case 40: // Type 40
	{
		double md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ double cx=floor(z.x*nfq)+dx; double cy=floor(z.y*nfq)+dy; double cz=floor(z.z*nfq)+dz; double h1=sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h1=h1-floor(h1); double h2=sin(cx*269.5+cy*183.3+cz*346.9)*43758.5453; h2=h2-floor(h2); double h3=sin(cx*419.2+cy*371.9+cz*529.7)*43758.5453; h3=h3-floor(h3); double d=(z.x*nfq-cx-h1)*(z.x*nfq-cx-h1)+(z.y*nfq-cy-h2)*(z.y*nfq-cy-h2)+(z.z*nfq-cz-h3)*(z.z*nfq-cz-h3); if(d<md)md=d; } aux.DE *= (1.0 + nf*sqrt(md)*nam);
		break;
	}
	case 41: // Type 41
	{
		double md1=1e10,md2=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ double cx=floor(z.x*nfq)+dx; double cy=floor(z.y*nfq)+dy; double cz=floor(z.z*nfq)+dz; double h=sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); cx+=h; double d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md1){md2=md1;md1=d;}else if(d<md2)md2=d; } aux.DE *= (1.0 + nf*md1*md2*nam);
		break;
	}
	case 42: // Type 42
	{
		double md=1e10; double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double th=atan2(z.y,z.x); for(int k=0;k<8;k++){ double a2=k*M_PI*2.0/8.0; double d=fabs(th-a2); if(d>M_PI)d=2.0*M_PI-d; if(d<md)md=d; } aux.DE *= (1.0 + nf*md*r*nam*nfq);
		break;
	}
	case 43: // Type 43
	{
		double v=0; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ double cx=floor(z.x*nfq)+dx; double cy=floor(z.y*nfq)+dy; double cz=floor(z.z*nfq)+dz; double h=sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); double d=(z.x*nfq-cx-h)*(z.x*nfq-cx-h)+(z.y*nfq-cy-h)*(z.y*nfq-cy-h)+(z.z*nfq-cz-h)*(z.z*nfq-cz-h); v+=exp(-na*d); } aux.DE *= (1.0 + nf*(1.0-v)*nam);
		break;
	}
	case 44: // Type 44
	{
		double md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ double cx=floor(z.x*nfq)+dx; double cy=floor(z.y*nfq)+dy; double cz=floor(z.z*nfq)+dz; double h=sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); cx+=h; double d=sqrt((z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz)); if(d<md)md=d; } double v=sin(md*M_PI*na); aux.DE *= (1.0 + nf*v*nam);
		break;
	}
	case 45: // Type 45
	{
		double md=1e10,cd=0; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ double cx=floor(z.x*nfq)+dx; double cy=floor(z.y*nfq)+dy; double cz=floor(z.z*nfq)+dz; double h=sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); cx+=h; double d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md){md=d;cd=h;} } aux.DE *= (1.0 + nf*cd*nam);
		break;
	}
	case 46: // Type 46
	{
		double md1=1e10,md2=1e10,md3=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ double cx=floor(z.x*nfq)+dx; double cy=floor(z.y*nfq)+dy; double cz=floor(z.z*nfq)+dz; double h=sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); cx+=h; double d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md1){md3=md2;md2=md1;md1=d;}else if(d<md2){md3=md2;md2=d;}else if(d<md3)md3=d; } aux.DE *= (1.0 + nf*(sqrt(md3)-sqrt(md1))*nam);
		break;
	}
	case 47: // Type 47
	{
		double md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++){ double cx=floor(z.x*nfq)+dx; double cy=floor(z.y*nfq)+dy; double h=sin(cx*127.1+cy*311.7)*43758.5453; h=h-floor(h); cx+=h*na; double hy=sin(cx*269.5+cy*183.3)*43758.5453; hy=hy-floor(hy); cy+=hy*nb; double d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy); if(d<md)md=d; } double v = sin(z.z*nfq)*0.5+0.5; aux.DE *= (1.0 + nf*(sqrt(md)+v*nc)*nam);
		break;
	}
	case 48: // Type 48
	{
		double md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ double cx=floor(z.x*nfq)+dx; double cy=floor(z.y*nfq)+dy; double cz=floor(z.z*nfq)+dz; double h=sin(cx*127.1+cy*311.7+cz*74.7)*43758.5453; h=h-floor(h); cx+=h; double d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md)md=d; } md=sqrt(md); double v=md-floor(md*na)/na; aux.DE *= (1.0 + nf*v*nam);
		break;
	}
	case 49: // Type 49
	{
		double v=0,a=nam,f=nfq; for(int k=0;k<4;k++){ double md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++){ double cx=floor(z.x*f)+dx; double cy=floor(z.y*f)+dy; double h=sin(cx*127.1+cy*311.7)*43758.5453; h=h-floor(h); cx+=h; double d=(z.x*f-cx)*(z.x*f-cx)+(z.y*f-cy)*(z.y*f-cy); if(d<md)md=d; } v+=a*sqrt(md); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 50: // Type 50
	{
		double md=1e10; int nn = (int)fmax(2.0, fmin(na*8.0, 20.0)); for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++) for(int dz=-1;dz<=1;dz++){ double cx=floor(z.x*nfq)+dx; double cy=floor(z.y*nfq)+dy; double cz=floor(z.z*nfq)+dz; for(int p=0;p<2;p++){ double h1=sin((cx+p*0.5)*127.1+cy*311.7+cz*74.7)*43758.5453; h1=h1-floor(h1); double h2=sin(cx*269.5+(cy+p*0.5)*183.3+cz*346.9)*43758.5453; h2=h2-floor(h2); double d=(z.x*nfq-cx-h1)*(z.x*nfq-cx-h1)+(z.y*nfq-cy-h2)*(z.y*nfq-cy-h2)+(z.z*nfq-cz)*(z.z*nfq-cz); if(d<md)md=d; } } aux.DE *= (1.0 + nf*sqrt(md)*nam);
		break;
	}
	case 51: // Type 51
	{
		double v=0, a=nam, f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); double r2=fabs(h*2.0-1.0); v+=a*(1.0-r2); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v*v);
		break;
	}
	case 52: // Type 52
	{
		double v=0,a=nam,f=nfq,w=1.0; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); double r2=1.0-fabs(h*2.0-1.0); r2*=r2; v+=r2*a*w; w=fmin(r2*na, 1.0); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 53: // Type 53
	{
		double v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f+z.y*f*1.3+z.z*f*0.7); v+=a*fabs(h); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 54: // Type 54
	{
		double v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*fabs(sin(h*M_PI*na)); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 55: // Type 55
	{
		double v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f+z.y*f*1.3+z.z*f*0.7); double ridge=1.0-fabs(h); ridge=ridge*ridge; v+=a*ridge; f*=na; a*=nb; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 56: // Type 56
	{
		double v=0,f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v=fmax(v,h*nam/(1.0+k*0.5)); f*=2.0; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 57: // Type 57
	{
		double v=0,a=nam,f=nfq,prev=0; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); double cur=fabs(h*2.0-1.0); v+=a*cur*prev; prev=cur; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 58: // Type 58
	{
		double v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ double h1=sin(z.x*f+z.y*f*1.3)*0.5+0.5; double h2=sin(z.y*f*0.7+z.z*f*1.1)*0.5+0.5; double h3=sin(z.z*f*0.9+z.x*f*1.5)*0.5+0.5; v+=a*(h1+h2+h3)/3.0; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*(v*2.0-1.0));
		break;
	}
	case 59: // Type 59
	{
		double v=0,a=nam,f=nfq; for(int k=0;k<6;k++){ double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double h=sin(r*f)*43758.5453; h=h-floor(h); v+=a*h; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 60: // Type 60
	{
		double v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f+z.y*f*1.3+z.z*f*0.7); double billow=fabs(h)*2.0-1.0; v+=a*billow; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 61: // Type 61
	{
		double v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f+z.y*f*0.7+z.z*f*1.3)*0.5+0.5; v+=a*pow(h, na); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 62: // Type 62
	{
		double v=0,a=nam,f=nfq; double px=z.x,py=z.y,pz=z.z; for(int k=0;k<5;k++){ double h=sin(px*f*127.1+py*f*311.7+pz*f*74.7)*43758.5453; h=h-floor(h); v+=a*fabs(h*2.0-1.0); double wx=sin(py*f*269.5)*na; double wy=sin(pz*f*183.3)*nb; double wz=sin(px*f*419.2)*nc; px+=wx; py+=wy; pz+=wz; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 63: // Type 63
	{
		double v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); if(k%2==0) v+=a*h; else v+=a*(1.0-h); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 64: // Type 64
	{
		double v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f+z.y*f*1.3+z.z*f*0.7); double hs=h*h*sign(h); v+=a*hs; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 65: // Type 65
	{
		double v=0,a=nam,f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7+nd*i)*43758.5453; h=h-floor(h); v+=a*h; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 66: // Type 66
	{
		double wx=z.x+nam*sin(z.y*nfq); double wy=z.y+nam*sin(z.z*nfq); double wz=z.z+nam*sin(z.x*nfq); double h=sin(wx*127.1+wy*311.7+wz*74.7)*43758.5453; h=h-floor(h); aux.DE *= (1.0 + nf*h);
		break;
	}
	case 67: // Type 67
	{
		double wx=z.x+nam*sin(z.y*nfq+z.z*nfq*0.5); double wy=z.y+nam*sin(z.z*nfq*1.3+z.x*nfq*0.7); double wz=z.z+nam*sin(z.x*nfq*0.9+z.y*nfq*1.1); double wx2=wx+nb*sin(wy*nfq*2.0); double wy2=wy+nb*sin(wz*nfq*2.0); double wz2=wz+nb*sin(wx*nfq*2.0); double h=sin(wx2*127.1+wy2*311.7+wz2*74.7)*43758.5453; h=h-floor(h); aux.DE *= (1.0 + nf*h);
		break;
	}
	case 68: // Type 68
	{
		double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double th=atan2(z.y,z.x)+nam*sin(r*nfq); double ph=acos(z.z/fmax(r,1e-21))+nb*cos(r*nfq*0.7); double h=sin(th*na+ph*nc)*0.5+0.5; aux.DE *= (1.0 + nf*h);
		break;
	}
	case 69: // Type 69
	{
		double h1=sin(z.x*nfq*127.1+z.y*nfq*311.7)*43758.5453; h1=h1-floor(h1); double h2=sin(z.y*nfq*269.5+z.z*nfq*183.3)*43758.5453; h2=h2-floor(h2); double wx=z.x+(h1*2.0-1.0)*nam; double wy=z.y+(h2*2.0-1.0)*nam; double v=sin(wx*nfq*na+wy*nfq*nb); aux.DE *= (1.0 + nf*v);
		break;
	}
	case 70: // Type 70
	{
		double v=0,f=nfq,a=nam; double px=z.x,py=z.y,pz=z.z; for(int k=0;k<4;k++){ double h=sin(px*f*127.1+py*f*311.7+pz*f*74.7)*43758.5453; h=h-floor(h); v+=a*h; px+=sin(py*f*na)*nb; py+=sin(pz*f*na)*nb; pz+=sin(px*f*na)*nb; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 71: // Type 71
	{
		double wx=z.x+nam*sin(z.y*nfq)*cos(z.z*nfq*0.5); double wy=z.y+nam*cos(z.x*nfq*0.7)*sin(z.z*nfq); double v=sin(wx*na)*cos(wy*nb); aux.DE *= (1.0 + nf*v);
		break;
	}
	case 72: // Type 72
	{
		double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double wr=r+nam*sin(r*nfq); double h=sin(wr*na*127.1)*43758.5453; h=h-floor(h); aux.DE *= (1.0 + nf*h);
		break;
	}
	case 73: // Type 73
	{
		double v=sin(z.x*nfq+nam*sin(z.y*nfq+nam*sin(z.z*nfq))); aux.DE *= (1.0 + nf*v);
		break;
	}
	case 74: // Type 74
	{
		double t=nd*i*0.01; double wx=z.x+nam*sin(z.y*nfq+t); double wy=z.y+nam*sin(z.z*nfq+t*1.3); double wz=z.z+nam*sin(z.x*nfq+t*0.7); double h=sin(wx*127.1+wy*311.7+wz*74.7)*43758.5453; h=h-floor(h); aux.DE *= (1.0 + nf*h);
		break;
	}
	case 75: // Type 75
	{
		double scale=nfq; double wx=z.x*scale; double wy=z.y*scale; double wz=z.z*scale; for(int k=0;k<3;k++){ wx=sin(wx*na+wy); wy=cos(wy*nb+wz); wz=sin(wz*nc+wx); } double h=sin(wx+wy+wz)*0.5+0.5; aux.DE *= (1.0 + nf*h*nam);
		break;
	}
	case 76: // Type 76
	{
		double h1=sin(z.x*nfq+z.y*nfq*0.5)*0.5+0.5; double h2=sin(z.y*nfq*1.3+z.z*nfq*0.7)*0.5+0.5; double v=sin((z.x+h1*nam)*na)*cos((z.y+h2*nam)*nb); aux.DE *= (1.0 + nf*v);
		break;
	}
	case 77: // Type 77
	{
		double wx=z.x+nam*sin(nfq*z.y); double wy=z.y+nam*cos(nfq*z.x); double v1=sin(wx*na); double v2=cos(wy*nb); double v=v1*v2; z.x+=nf*v*nc*0.01; z.y+=nf*v*nd*0.01; aux.DE *= (1.0 + nf*fabs(v)*0.1);
		break;
	}
	case 78: // Type 78
	{
		double r2=z.x*z.x+z.y*z.y+z.z*z.z; double h=sin(r2*nfq)*43758.5453; h=h-floor(h); double wx=z.x*(1.0+h*nam); double wy=z.y*(1.0+h*nam); double v=sin(wx*na+wy*nb)*0.5+0.5; aux.DE *= (1.0 + nf*v);
		break;
	}
	case 79: // Type 79
	{
		double v=0,f=nfq; for(int k=0;k<4;k++){ double h=sin(z.x*f+sin(z.y*f*na)*nam); v+=h/(1.0+k); f*=2.0; } aux.DE *= (1.0 + nf*v*0.25);
		break;
	}
	case 80: // Type 80
	{
		double wx=z.x+nam*sin(z.y*nfq)*sin(z.z*nfq*0.5); double wy=z.y+nam*sin(z.z*nfq*0.7)*sin(z.x*nfq); double wz=z.z+nam*sin(z.x*nfq*1.3)*sin(z.y*nfq*0.9); double v=sin(wx*na)*sin(wy*nb)*sin(wz*nc); aux.DE *= (1.0 + nf*v);
		break;
	}
	case 81: // Type 81
	{
		double s=(z.x+z.y+z.z)/3.0; double ix=floor(z.x+s); double iy=floor(z.y+s); double iz=floor(z.z+s); double t=(ix+iy+iz)/6.0; double x0=z.x-ix+t; double y0=z.y-iy+t; double z0=z.z-iz+t; double h=sin(ix*127.1+iy*311.7+iz*74.7)*43758.5453; h=h-floor(h); double v=fmax(0.0,0.6-x0*x0-y0*y0-z0*z0); v=v*v*v*v*h; aux.DE *= (1.0 + nf*v*nam*32.0);
		break;
	}
	case 82: // Type 82
	{
		double s=(z.x+z.y+z.z)*nfq/3.0; double v=sin(s*127.1)*43758.5453; v=v-floor(v); double v2=sin(s*269.5)*43758.5453; v2=v2-floor(v2); aux.DE *= (1.0 + nf*(v*na+v2*nb)*0.5*nam);
		break;
	}
	case 83: // Type 83
	{
		double skew=(z.x+z.y)*nfq*(sqrt(3.0)-1.0)/2.0; double ix=floor(z.x*nfq+skew); double iy=floor(z.y*nfq+skew); double unskew=(ix+iy)*(3.0-sqrt(3.0))/6.0; double x0=z.x*nfq-ix+unskew; double y0=z.y*nfq-iy+unskew; double h=sin(ix*127.1+iy*311.7)*43758.5453; h=h-floor(h); double t0=0.5-x0*x0-y0*y0; double v=t0>0?t0*t0*t0*t0*h:0; aux.DE *= (1.0 + nf*v*nam*70.0);
		break;
	}
	case 84: // Type 84
	{
		double v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ double s=(z.x*f+z.y*f+z.z*f)/3.0; double h=sin(s*127.1+k*519.3)*43758.5453; h=h-floor(h); v+=a*h; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 85: // Type 85
	{
		double v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ double s=(z.x*f+z.y*f+z.z*f)/3.0; double h=sin(s*127.1+k*519.3)*43758.5453; h=h-floor(h); v+=a*fabs(h*2.0-1.0); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 86: // Type 86
	{
		double v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ double s=(z.x*f+z.y*f+z.z*f)/3.0; double h=sin(s*127.1+k*519.3)*43758.5453; h=h-floor(h); double ridge=1.0-fabs(h*2.0-1.0); ridge*=ridge; v+=a*ridge; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 87: // Type 87
	{
		double s=(z.x+z.y+z.z)*nfq; double v1=sin(s*na)*0.5+0.5; double v2=sin(s*nb+M_PI*0.5)*0.5+0.5; double v=v1*v2; aux.DE *= (1.0 + nf*v*nam);
		break;
	}
	case 88: // Type 88
	{
		double v=0; double px=z.x*nfq,py=z.y*nfq,pz=z.z*nfq; for(int k=0;k<4;k++){ double s=(px+py+pz)/3.0; double h=sin(s*127.1+k*91.7)*43758.5453; h=h-floor(h); v+=h*nam/(1.0+k); px+=sin(py)*na; py+=sin(pz)*nb; pz+=sin(px)*nc; } aux.DE *= (1.0 + nf*v*0.25);
		break;
	}
	case 89: // Type 89
	{
		double r=sqrt(z.x*z.x+z.y*z.y+z.z*z.z); double th=atan2(z.y,z.x); double s=(r*nfq+th*na)/3.0; double h=sin(s*127.1)*43758.5453; h=h-floor(h); aux.DE *= (1.0 + nf*h*nam);
		break;
	}
	case 90: // Type 90
	{
		double v=0,f=nfq,a=nam; double cs=cos(nd*M_PI/180.0),sn=sin(nd*M_PI/180.0); double px=z.x,py=z.y; for(int k=0;k<5;k++){ double s=(px*f+py*f+z.z*f)/3.0; double h=sin(s*127.1+k*519.3)*43758.5453; h=h-floor(h); v+=a*h; double nx=px*cs-py*sn; py=px*sn+py*cs; px=nx; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 91: // Type 91
	{
		double vn=sin(z.x*nfq*127.1+z.y*nfq*311.7+z.z*nfq*74.7)*43758.5453; vn=vn-floor(vn); double md=1e10; for(int dx=-1;dx<=1;dx++) for(int dy=-1;dy<=1;dy++){ double cx=floor(z.x*nfq)+dx; double cy=floor(z.y*nfq)+dy; double h=sin(cx*127.1+cy*311.7)*43758.5453; h=h-floor(h); cx+=h; double d=(z.x*nfq-cx)*(z.x*nfq-cx)+(z.y*nfq-cy)*(z.y*nfq-cy); if(d<md)md=d; } aux.DE *= (1.0 + nf*(vn*na+sqrt(md)*nb)*nam);
		break;
	}
	case 92: // Type 92
	{
		double v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v+=a*sin(h*M_PI*2.0*na); f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 93: // Type 93
	{
		double t=nd*i*0.1; double v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7+t)*43758.5453; h=h-floor(h); v+=a*h; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 94: // Type 94
	{
		double v1=0,v2=0,f=nfq,a=nam; for(int k=0;k<4;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v1+=a*h; v2+=a*fabs(h*2.0-1.0); f*=2.0; a*=0.5; } double blend=sin(z.x*na+z.y*nb)*0.5+0.5; aux.DE *= (1.0 + nf*(v1*blend+v2*(1.0-blend)));
		break;
	}
	case 95: // Type 95
	{
		double v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); double erosion=exp(-na*h); v+=a*erosion; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 96: // Type 96
	{
		double v=0,f=nfq; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); double terrace=floor(h*na+0.5)/fmax(na,1e-21); v+=terrace/(1.0+k); f*=2.0; } aux.DE *= (1.0 + nf*v*nam*0.2);
		break;
	}
	case 97: // Type 97
	{
		double v=0,f=nfq,a=nam; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); double swiss=fabs(h*2.0-1.0); swiss=1.0-swiss*swiss; v+=a*swiss; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 98: // Type 98
	{
		double v=0,f=nfq,a=nam; double px=z.x,py=z.y,pz=z.z; for(int k=0;k<5;k++){ double h=sin(px*f*127.1+py*f*311.7+pz*f*74.7)*43758.5453; h=h-floor(h); v+=a*h; double wx=sin(py*f*na)*nb*a; double wy=sin(pz*f*na)*nb*a; double wz=sin(px*f*na)*nb*a; px+=wx; py+=wy; pz+=wz; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 99: // Type 99
	{
		double v=0,f=nfq,a=nam; double offset=0; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7+offset)*43758.5453; h=h-floor(h); double r=fabs(h*2.0-1.0); r=offset+r*r*na; v+=a*r; offset=r; f*=2.0; a*=0.5; } aux.DE *= (1.0 + nf*v);
		break;
	}
	case 100: // Type 100
	{
		double v1=0,v2=0,f=nfq,a=nam; for(int k=0;k<5;k++){ double h=sin(z.x*f*127.1+z.y*f*311.7+z.z*f*74.7)*43758.5453; h=h-floor(h); v1+=a*h; double ridge=1.0-fabs(h*2.0-1.0); v2+=a*ridge*ridge; f*=2.0; a*=0.5; } double t=sin(z.x*na+z.y*nb+z.z*nc)*0.5+0.5; aux.DE *= (1.0 + nf*(v1*(1.0-t)+v2*t));
		break;
	}
	default: break;
}