// Auto-generated mutation switch for system: clip
// Target: CPU
// Generated mutations: 100
switch (mut.clipType)
{
	case 1: // Type 1
	{
		clipDist=sqrt((cz.x/mut.clipSizeX)*(cz.x/mut.clipSizeX)+(cz.y/mut.clipSizeY)*(cz.y/mut.clipSizeY)+(cz.z/mut.clipSizeZ)*(cz.z/mut.clipSizeZ))-1.0; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 2: // Type 2
	{
		double rxy=sqrt(cz.x*cz.x+cz.y*cz.y)-mut.clipMajorRadius; clipDist=sqrt(rxy*rxy+cz.z*cz.z)-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 3: // Type 3
	{
		clipDist=sqrt(cz.x*cz.x+cz.y*cz.y)-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 4: // Type 4
	{
		double tanAlpha=tan(mut.clipAngle*M_PI/180.0); clipDist=sqrt(cz.x*cz.x+cz.y*cz.y)-tanAlpha*fabs(cz.z); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 5: // Type 5
	{
		clipDist=(cz.x/mut.clipSizeX)*(cz.x/mut.clipSizeX)+(cz.y/mut.clipSizeY)*(cz.y/mut.clipSizeY)-(cz.z/mut.clipSizeZ)*(cz.z/mut.clipSizeZ)-1.0; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 6: // Type 6
	{
		clipDist=cz.x*cz.x+cz.y*cz.y-mut.clipParamA*cz.z; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 7: // Type 7
	{
		clipDist=(cz.x/mut.clipSizeX)*(cz.x/mut.clipSizeX)-(cz.y/mut.clipSizeY)*(cz.y/mut.clipSizeY)-cz.z; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 8: // Type 8
	{
		double r2d=sqrt(cz.x*cz.x+cz.y*cz.y); double theta=atan2(cz.y,cz.x); clipDist=r2d-mut.clipParamA*exp(mut.clipParamB*theta); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 9: // Type 9
	{
		double freq=mut.clipFrequency; double amp=mut.clipAmplitude; clipDist=cz.z-amp*sin(freq*cz.x)*sin(freq*cz.y); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 10: // Type 10
	{
		double n=sin(cz.x*12.9898+cz.y*78.233)*43758.5453; n=(n-floor(n))*2.0-1.0; double n2=sin(cz.y*19.8672+cz.z*53.471)*28947.3125; n2=(n2-floor(n2))*2.0-1.0; clipDist=cz.z-mut.clipAmplitude*(n+n2)*0.5; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 11: // Type 11
	{
		double d1=sqrt((cz.x/mut.clipSizeX)*(cz.x/mut.clipSizeX)+(cz.y/mut.clipSizeY)*(cz.y/mut.clipSizeY)+(cz.z/mut.clipSizeZ)*(cz.z/mut.clipSizeZ))-1.0; double d2=cz.Length()-mut.clipRadius; clipDist=fmin(d1,d2); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 12: // Type 12
	{
		double dA=sqrt((cz.x/mut.clipSizeX)*(cz.x/mut.clipSizeX)+(cz.y/mut.clipSizeY)*(cz.y/mut.clipSizeY)+(cz.z/mut.clipSizeZ)*(cz.z/mut.clipSizeZ))-1.0; double dB=cz.Length()-mut.clipRadius; clipDist=fmax(dA,-dB); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 13: // Type 13
	{
		double dA2=sqrt((cz.x/mut.clipSizeX)*(cz.x/mut.clipSizeX)+(cz.y/mut.clipSizeY)*(cz.y/mut.clipSizeY)+(cz.z/mut.clipSizeZ)*(cz.z/mut.clipSizeZ))-1.0; double dB2=cz.Length()-mut.clipRadius; clipDist=fmax(fmin(dA2,dB2),-fmax(dA2,dB2)); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 14: // Type 14
	{
		double d1s=sqrt((cz.x/mut.clipSizeX)*(cz.x/mut.clipSizeX)+(cz.y/mut.clipSizeY)*(cz.y/mut.clipSizeY)+(cz.z/mut.clipSizeZ)*(cz.z/mut.clipSizeZ))-1.0; double d2s=cz.Length()-mut.clipRadius; double k=mut.clipSmoothK; double h=fmax(0.0,fmin(1.0,0.5+0.5*(d2s-d1s)/k)); clipDist=d2s+(d1s-d2s)*h-k*h*(1.0-h); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 15: // Type 15
	{
		double dAs=sqrt((cz.x/mut.clipSizeX)*(cz.x/mut.clipSizeX)+(cz.y/mut.clipSizeY)*(cz.y/mut.clipSizeY)+(cz.z/mut.clipSizeZ)*(cz.z/mut.clipSizeZ))-1.0; double dBs=cz.Length()-mut.clipRadius; double k2=mut.clipSmoothK; double h2=fmax(0.0,fmin(1.0,0.5-0.5*(dAs+dBs)/k2)); clipDist=dAs+(-dBs-dAs)*h2+k2*h2*(1.0-h2); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 16: // Type 16
	{
		double dc1=cz.Length()-mut.clipRadius; double dc2=fmax(fabs(cz.x)-mut.clipSizeX,fmax(fabs(cz.y)-mut.clipSizeY,fabs(cz.z)-mut.clipSizeZ)); double dc3=sqrt(cz.x*cz.x+cz.y*cz.y)-mut.clipRadius*0.5; clipDist=fmax(dc1,fmax(dc2,dc3)); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 17: // Type 17
	{
		CVector3 rp=cz; if(mut.clipSizeX>0.001)rp.x=fmod(cz.x+mut.clipSizeX*0.5,mut.clipSizeX)-mut.clipSizeX*0.5; if(mut.clipSizeY>0.001)rp.y=fmod(cz.y+mut.clipSizeY*0.5,mut.clipSizeY)-mut.clipSizeY*0.5; if(mut.clipSizeZ>0.001)rp.z=fmod(cz.z+mut.clipSizeZ*0.5,mut.clipSizeZ)-mut.clipSizeZ*0.5; clipDist=rp.Length()-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 18: // Type 18
	{
		CVector3 cell; cell.x=(mut.clipSizeX>0.001)?floor(cz.x/mut.clipSizeX):0; cell.y=(mut.clipSizeY>0.001)?floor(cz.y/mut.clipSizeY):0; cell.z=(mut.clipSizeZ>0.001)?floor(cz.z/mut.clipSizeZ):0; double h=fabs(sin(cell.x*127.1+cell.y*311.7+cell.z*74.7)*43758.5453); h=h-floor(h); CVector3 rp2=cz; if(mut.clipSizeX>0.001)rp2.x=fmod(cz.x+mut.clipSizeX*0.5,mut.clipSizeX)-mut.clipSizeX*0.5; if(mut.clipSizeY>0.001)rp2.y=fmod(cz.y+mut.clipSizeY*0.5,mut.clipSizeY)-mut.clipSizeY*0.5; if(mut.clipSizeZ>0.001)rp2.z=fmod(cz.z+mut.clipSizeZ*0.5,mut.clipSizeZ)-mut.clipSizeZ*0.5; clipDist=rp2.Length()-mut.clipRadius*(0.5+h); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 19: // Type 19
	{
		double coarse=fmax(fabs(cz.x)-mut.clipSizeX*2.0,fmax(fabs(cz.y)-mut.clipSizeY*2.0,fabs(cz.z)-mut.clipSizeZ*2.0)); double fine=cz.Length()-mut.clipRadius; clipDist=(coarse<0.0)?fine:coarse; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 20: // Type 20
	{
		CVector3 fz=cz; double fscale=1.0; for(int k=0;k<4;k++){fz.x=fabs(fz.x)*2.0-mut.clipParamA; fz.y=fabs(fz.y)*2.0-mut.clipParamA; fz.z=fabs(fz.z)*2.0-mut.clipParamA; fscale*=2.0;} clipDist=(fz.Length()-mut.clipRadius)/fscale; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 21: // Type 21
	{
		clipDist=cz.Length()-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 22: // Type 22
	{
		CVector3 scaled(cz.x*mut.clipSizeX,cz.y*mut.clipSizeY,cz.z*mut.clipSizeZ); clipDist=scaled.Length()-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 23: // Type 23
	{
		CVector3 sheared=cz; sheared.x+=mut.clipAmplitude*cz.y; clipDist=sheared.Length()-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 24: // Type 24
	{
		CVector3 folded=cz; double lim=mut.clipParamA; if(folded.x>lim)folded.x=2.0*lim-folded.x; if(folded.x<-lim)folded.x=-2.0*lim-folded.x; if(folded.y>lim)folded.y=2.0*lim-folded.y; if(folded.y<-lim)folded.y=-2.0*lim-folded.y; if(folded.z>lim)folded.z=2.0*lim-folded.z; if(folded.z<-lim)folded.z=-2.0*lim-folded.z; clipDist=folded.Length()-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 25: // Type 25
	{
		CVector3 absed(fabs(cz.x),fabs(cz.y),fabs(cz.z)); clipDist=absed.Length()-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 26: // Type 26
	{
		clipDist=cz.Length()-mut.clipRadius; double pulse=1.0+0.1*sin((double)i*mut.clipFrequency); clipDist*=pulse; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 27: // Type 27
	{
		clipDist=cz.Length()-mut.clipRadius; double sf=mut.clipParamA*(1.0+0.1*(double)i/250.0); clipDist*=sf; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 28: // Type 28
	{
		clipDist=cz.Length()-mut.clipRadius; if(clipDist<0.0) aux.color+=fabs(clipDist)*mut.clipAmplitude; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 29: // Type 29
	{
		clipDist=cz.Length()-mut.clipRadius; double trap=cz.Length(); if(trap<aux.color)aux.color=trap; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 30: // Type 30
	{
		clipDist=cz.Length()-mut.clipRadius; aux.color=log(1.0+fabs(aux.dist))*mut.clipAmplitude; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 31: // Type 31
	{
		double r2d=sqrt(cz.x*cz.x+cz.y*cz.y); double theta=atan2(cz.y,cz.x); int n=mut.clipNPoints; double starR=mut.clipRadius*(1.0+mut.clipAmplitude*cos((double)n*theta)); clipDist=r2d-starR; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 32: // Type 32
	{
		double x2h=cz.x*cz.x+cz.y*cz.y; clipDist=(x2h-1.0)*(x2h-1.0)*(x2h-1.0)-cz.x*cz.x*cz.y*cz.y*cz.y; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 33: // Type 33
	{
		double r2d2=sqrt(cz.x*cz.x+cz.y*cz.y); double theta2=atan2(cz.y,cz.x); double m=(double)mut.clipNPoints; double n1=mut.clipParamA,n2=mut.clipParamB,n3=mut.clipParamC; double t=m*theta2/4.0; double r_sf=pow(pow(fabs(cos(t)/mut.clipSizeX),n2)+pow(fabs(sin(t)/mut.clipSizeY),n3),-1.0/n1); clipDist=r2d2-r_sf*mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 34: // Type 34
	{
		double r2d3=sqrt(cz.x*cz.x+cz.y*cz.y); double theta3=atan2(cz.y,cz.x); int ng=mut.clipNPoints; double gearR=mut.clipRadius*(1.0+0.1*tanh(sin((double)ng*theta3))); clipDist=r2d3-gearR; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 35: // Type 35
	{
		double r2d4=sqrt(cz.x*cz.x+cz.y*cz.y); double theta4=atan2(cz.y,cz.x); int ns=mut.clipNPoints; double spiralR=mut.clipParamA*exp(-mut.clipParamB*theta4)*(1.0+mut.clipParamC*cos((double)ns*theta4)); clipDist=r2d4-spiralR; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 36: // Type 36
	{
		CVector3 seeds[4]; seeds[0]=CVector3(mut.clipParamA,0,0); seeds[1]=CVector3(-mut.clipParamA,mut.clipParamB,0); seeds[2]=CVector3(0,-mut.clipParamA,mut.clipParamC); seeds[3]=CVector3(mut.clipParamB,mut.clipParamC,-mut.clipParamA); double minVD=1e20; for(int k=0;k<4;k++){double vd=(cz-seeds[k]).Length(); if(vd<minVD)minVD=vd;} clipDist=minVD-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 37: // Type 37
	{
		CVector3 edges[3]; edges[0]=CVector3(mut.clipParamA,0,0); edges[1]=CVector3(-mut.clipParamA*0.5,mut.clipParamA*0.866,0); edges[2]=CVector3(-mut.clipParamA*0.5,-mut.clipParamA*0.866,0); double minED=1e20; for(int k=0;k<3;k++){CVector3 e=edges[(k+1)%3]-edges[k]; CVector3 p=cz-edges[k]; double t=fmax(0.0,fmin(1.0,p.Dot(e)/e.Dot(e))); double ed=(p-e*t).Length(); if(ed<minED)minED=ed;} clipDist=minED-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 38: // Type 38
	{
		CVector3 lz=cz; double lscale=1.0; for(int k=0;k<3;k++){lz.x=fabs(lz.x); lz.y=fabs(lz.y); lz.z=fabs(lz.z); if(lz.x<lz.y){double t=lz.x;lz.x=lz.y;lz.y=t;} if(lz.x<lz.z){double t=lz.x;lz.x=lz.z;lz.z=t;} if(lz.y<lz.z){double t=lz.y;lz.y=lz.z;lz.z=t;} lz=lz*mut.clipParamA-CVector3(mut.clipParamB,mut.clipParamB,mut.clipParamB)*(mut.clipParamA-1.0); lscale*=mut.clipParamA;} clipDist=(lz.Length()-mut.clipRadius)/lscale; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 39: // Type 39
	{
		double jx=cz.x,jy=cz.y; for(int k=0;k<8;k++){double tx=jx*jx-jy*jy+mut.clipParamA; jy=2.0*jx*jy+mut.clipParamB; jx=tx; if(jx*jx+jy*jy>4.0)break;} double jDist=(jx*jx+jy*jy>4.0)?-mut.clipRadius:mut.clipRadius; clipDist=fmax(jDist,fabs(cz.z)-mut.clipSizeZ); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 40: // Type 40
	{
		double mx=0,my=0; for(int k=0;k<8;k++){double tx2=mx*mx-my*my+cz.x; my=2.0*mx*my+cz.y; mx=tx2; if(mx*mx+my*my>4.0)break;} double mDist=(mx*mx+my*my>4.0)?-mut.clipRadius:mut.clipRadius; clipDist=fmax(mDist,fabs(cz.z)-mut.clipSizeZ); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 41: // Type 41
	{
		clipDist=fmax(fmax(fabs(cz.x),fabs(cz.y)),fmax(fabs(cz.z),fabs(z.w)))-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 42: // Type 42
	{
		clipDist=sqrt(cz.x*cz.x+cz.y*cz.y+cz.z*cz.z+z.w*z.w)-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 43: // Type 43
	{
		double time=(double)i*mut.clipFrequency; double tR=mut.clipRadius*(1.0+mut.clipAmplitude*sin(time)); clipDist=cz.Length()-tR; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 44: // Type 44
	{
		double orbitR=mut.clipRadius*(1.0+mut.clipAmplitude*sin(aux.color*mut.clipFrequency)); clipDist=cz.Length()-orbitR; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 45: // Type 45
	{
		double deR=mut.clipRadius*(1.0+mut.clipAmplitude*log(1.0+fabs(aux.DE))); clipDist=cz.Length()-deR; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 46: // Type 46
	{
		double colR=mut.clipRadius*(1.0+mut.clipAmplitude*sin(aux.color*mut.clipFrequency)); clipDist=cz.Length()-colR; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 47: // Type 47
	{
		double iterR=mut.clipRadius*(1.0+mut.clipAmplitude*(double)i/250.0); clipDist=cz.Length()-iterR; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 48: // Type 48
	{
		double rh=fabs(sin((double)i*12.9898+cz.x*78.233)*43758.5453); rh=rh-floor(rh); double randR=mut.clipRadius*(1.0+mut.clipAmplitude*(rh-0.5)); clipDist=cz.Length()-randR; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 49: // Type 49
	{
		double nx=tanh(mut.clipParamA*cz.x+mut.clipParamB*cz.y+mut.clipParamC*cz.z); double ny=tanh(mut.clipParamB*cz.x-mut.clipParamA*cz.y+mut.clipParamC*cz.z); double nz=tanh(mut.clipParamC*cz.x+mut.clipParamA*cz.y-mut.clipParamB*cz.z); clipDist=sqrt(nx*nx+ny*ny+nz*nz)-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 50: // Type 50
	{
		CVector3 rz=cz; double rscale=1.0; for(int k=0;k<5;k++){rz.x=fabs(rz.x)*2.0-mut.clipParamA; rz.y=fabs(rz.y)*2.0-mut.clipParamA; rz.z=fabs(rz.z)*2.0-mut.clipParamA; rscale*=2.0; double rd=rz.Length()-mut.clipRadius; rd/=rscale; if(rd<clipDist)clipDist=rd;} if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 51: // Gyroid surface
	{
		clipDist=sin(cz.x*mut.clipParamA)*cos(cz.y*mut.clipParamA)+sin(cz.y*mut.clipParamA)*cos(cz.z*mut.clipParamA)+sin(cz.z*mut.clipParamA)*cos(cz.x*mut.clipParamA)-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 52: // Schwarz P surface
	{
		clipDist=cos(cz.x*mut.clipParamA)+cos(cz.y*mut.clipParamA)+cos(cz.z*mut.clipParamA)-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 53: // Diamond surface
	{
		clipDist=sin(cz.x*mut.clipParamA)*sin(cz.y*mut.clipParamA)*sin(cz.z*mut.clipParamA)+sin(cz.x*mut.clipParamA)*cos(cz.y*mut.clipParamA)*cos(cz.z*mut.clipParamA)+cos(cz.x*mut.clipParamA)*sin(cz.y*mut.clipParamA)*cos(cz.z*mut.clipParamA)+cos(cz.x*mut.clipParamA)*cos(cz.y*mut.clipParamA)*sin(cz.z*mut.clipParamA)-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 54: // Lidinoid surface
	{
		clipDist=0.5*(sin(2.0*cz.x*mut.clipParamA)*cos(cz.y*mut.clipParamA)*sin(cz.z*mut.clipParamA)+sin(2.0*cz.y*mut.clipParamA)*cos(cz.z*mut.clipParamA)*sin(cz.x*mut.clipParamA)+sin(2.0*cz.z*mut.clipParamA)*cos(cz.x*mut.clipParamA)*sin(cz.y*mut.clipParamA))-0.5*(cos(2.0*cz.x*mut.clipParamA)*cos(2.0*cz.y*mut.clipParamA)+cos(2.0*cz.y*mut.clipParamA)*cos(2.0*cz.z*mut.clipParamA)+cos(2.0*cz.z*mut.clipParamA)*cos(2.0*cz.x*mut.clipParamA))-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 55: // Neovius surface
	{
		clipDist=3.0*(cos(cz.x*mut.clipParamA)+cos(cz.y*mut.clipParamA)+cos(cz.z*mut.clipParamA))+4.0*cos(cz.x*mut.clipParamA)*cos(cz.y*mut.clipParamA)*cos(cz.z*mut.clipParamA)-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 56: // Torus knot (2,3)
	{
		double t56=atan2(cz.y,cz.x); double r56xy=sqrt(cz.x*cz.x+cz.y*cz.y); double kx=cos(2.0*t56)*(mut.clipMajorRadius+mut.clipRadius*cos(3.0*t56)); double ky=sin(2.0*t56)*(mut.clipMajorRadius+mut.clipRadius*cos(3.0*t56)); double kz=mut.clipRadius*sin(3.0*t56); clipDist=sqrt((cz.x-kx)*(cz.x-kx)+(cz.y-ky)*(cz.y-ky)+(cz.z-kz)*(cz.z-kz))-mut.clipParamA; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 57: // Cross-cap surface
	{
		double r57=cz.Length(); clipDist=cz.x*cz.x*cz.z+cz.y*cz.y*cz.z-mut.clipParamA*cz.x*cz.y-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 58: // Barth sextic
	{
		double phi58=0.5*(1.0+sqrt(5.0)); double p2=phi58*phi58; clipDist=4.0*(p2*cz.x*cz.x-cz.y*cz.y)*(p2*cz.y*cz.y-cz.z*cz.z)*(p2*cz.z*cz.z-cz.x*cz.x)-(1.0+2.0*phi58)*(cz.x*cz.x+cz.y*cz.y+cz.z*cz.z-mut.clipParamA*mut.clipParamA)*(cz.x*cz.x+cz.y*cz.y+cz.z*cz.z-mut.clipParamA*mut.clipParamA); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 59: // Steiner surface
	{
		clipDist=cz.x*cz.x*cz.y*cz.y+cz.y*cz.y*cz.z*cz.z+cz.z*cz.z*cz.x*cz.x-mut.clipParamA*cz.x*cz.y*cz.z; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 60: // Boy surface approximation
	{
		double r60=cz.Length(); if(r60<1e-15)r60=1e-15; double x60=cz.x/r60,y60=cz.y/r60,z60=cz.z/r60; clipDist=64.0*x60*x60*x60*z60-48.0*x60*z60*(3.0*x60*x60+z60*z60)+12.0*z60*(x60*x60-z60*z60)+x60*x60+y60*y60+z60*z60-mut.clipRadius*mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 61: // Exponential decay shell
	{
		double r61=cz.Length(); clipDist=r61*exp(-mut.clipParamA*r61)-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 62: // Logarithmic spiral shell
	{
		double r62=sqrt(cz.x*cz.x+cz.y*cz.y); double t62=atan2(cz.y,cz.x); double spiralR=mut.clipParamA*exp(mut.clipParamB*t62); clipDist=fabs(r62-spiralR)+fabs(cz.z)-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 63: // Double helix
	{
		double t63=atan2(cz.y,cz.x); double r63=sqrt(cz.x*cz.x+cz.y*cz.y); double h1=r63-mut.clipMajorRadius-mut.clipRadius*cos(mut.clipParamA*cz.z); double h2=r63-mut.clipMajorRadius+mut.clipRadius*cos(mut.clipParamA*cz.z+M_PI); clipDist=fmin(sqrt(h1*h1+pow(mut.clipRadius*sin(mut.clipParamA*cz.z),2.0)),sqrt(h2*h2+pow(mut.clipRadius*sin(mut.clipParamA*cz.z+M_PI),2.0)))-mut.clipParamB; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 64: // Chamfered cube
	{
		double dx64=fabs(cz.x)-mut.clipSizeX; double dy64=fabs(cz.y)-mut.clipSizeY; double dz64=fabs(cz.z)-mut.clipSizeZ; double chamfer=mut.clipParamA; clipDist=fmax(fmax(dx64,fmax(dy64,dz64)),(dx64+dy64+dz64)*chamfer); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 65: // Rounded box
	{
		double dx65=fmax(fabs(cz.x)-mut.clipSizeX,0.0); double dy65=fmax(fabs(cz.y)-mut.clipSizeY,0.0); double dz65=fmax(fabs(cz.z)-mut.clipSizeZ,0.0); clipDist=sqrt(dx65*dx65+dy65*dy65+dz65*dz65)-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 66: // Octahedron
	{
		clipDist=fabs(cz.x)+fabs(cz.y)+fabs(cz.z)-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 67: // Dodecahedron approx
	{
		double phi67=0.5*(1.0+sqrt(5.0)); double iphi67=1.0/phi67; clipDist=fmax(fmax(fabs(cz.x)+phi67*fabs(cz.y),fabs(cz.y)+phi67*fabs(cz.z)),fabs(cz.z)+phi67*fabs(cz.x))-mut.clipRadius*(1.0+phi67); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 68: // Icosahedron approx
	{
		double phi68=0.5*(1.0+sqrt(5.0)); clipDist=fmax(fabs(cz.x)+phi68*fabs(cz.z),fmax(fabs(cz.y)+phi68*fabs(cz.x),fabs(cz.z)+phi68*fabs(cz.y)))-mut.clipRadius*phi68*phi68; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 69: // Truncated octahedron
	{
		double d69a=fmax(fabs(cz.x),fmax(fabs(cz.y),fabs(cz.z)))-mut.clipSizeX; double d69b=(fabs(cz.x)+fabs(cz.y)+fabs(cz.z))*0.577-mut.clipRadius; clipDist=fmax(d69a,d69b); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 70: // Hex prism
	{
		double q70x=fabs(cz.x); double q70y=fabs(cz.y); clipDist=fmax(q70x*0.866+q70y*0.5,q70y)-mut.clipRadius; clipDist=fmax(clipDist,fabs(cz.z)-mut.clipSizeZ); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 71: // Triangular prism
	{
		clipDist=fmax(fabs(cz.z)-mut.clipSizeZ,fmax(fabs(cz.x)*0.866+cz.y*0.5,-cz.y)-mut.clipRadius); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 72: // Link (two interlocked tori)
	{
		double rxy72a=sqrt(cz.x*cz.x+cz.y*cz.y); double d72a=sqrt((rxy72a-mut.clipMajorRadius)*(rxy72a-mut.clipMajorRadius)+cz.z*cz.z)-mut.clipRadius; double ryz72=sqrt(cz.y*cz.y+cz.z*cz.z); double d72b=sqrt((ryz72-mut.clipMajorRadius)*(ryz72-mut.clipMajorRadius)+cz.x*cz.x)-mut.clipRadius; clipDist=fmin(d72a,d72b); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 73: // Capped cylinder
	{
		double r73=sqrt(cz.x*cz.x+cz.y*cz.y)-mut.clipRadius; double h73=fabs(cz.z)-mut.clipSizeZ; clipDist=fmin(fmax(r73,h73),0.0)+sqrt(fmax(r73,0.0)*fmax(r73,0.0)+fmax(h73,0.0)*fmax(h73,0.0)); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 74: // Capsule
	{
		double capH=fmax(0.0,fmin(mut.clipSizeZ,cz.z)); clipDist=sqrt(cz.x*cz.x+cz.y*cz.y+(cz.z-capH)*(cz.z-capH))-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 75: // Trefoil knot
	{
		double t75=atan2(cz.y,cz.x); double r75=sqrt(cz.x*cz.x+cz.y*cz.y); double knotR=mut.clipMajorRadius+mut.clipRadius*cos(3.0*t75); clipDist=sqrt((r75-knotR)*(r75-knotR)+cz.z*cz.z)-mut.clipParamA; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 76: // Möbius strip approx
	{
		double t76=atan2(cz.y,cz.x); double r76=sqrt(cz.x*cz.x+cz.y*cz.y)-mut.clipMajorRadius; double localZ=cz.z*cos(t76*0.5)-r76*sin(t76*0.5); clipDist=fabs(localZ)-mut.clipParamA; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 77: // Sine cage
	{
		double sc77x=sin(cz.x*mut.clipParamA)*sin(cz.x*mut.clipParamA); double sc77y=sin(cz.y*mut.clipParamA)*sin(cz.y*mut.clipParamA); double sc77z=sin(cz.z*mut.clipParamA)*sin(cz.z*mut.clipParamA); clipDist=sc77x+sc77y+sc77z-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 78: // Pillow shape
	{
		clipDist=cz.x*cz.x*cz.x*cz.x+cz.y*cz.y*cz.y*cz.y+cz.z*cz.z*cz.z*cz.z-mut.clipParamA*(cz.x*cz.x+cz.y*cz.y+cz.z*cz.z); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 79: // Displacement sphere (noise)
	{
		double n79=sin(mut.clipParamA*cz.x)*sin(mut.clipParamA*cz.y)*sin(mut.clipParamA*cz.z); clipDist=cz.Length()-mut.clipRadius-mut.clipParamB*n79; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 80: // Corkscrew
	{
		double r80=sqrt(cz.x*cz.x+cz.y*cz.y)-mut.clipMajorRadius; double c80=r80*r80+(cz.z-mut.clipParamA*atan2(cz.y,cz.x)/(2.0*M_PI))*(cz.z-mut.clipParamA*atan2(cz.y,cz.x)/(2.0*M_PI))-mut.clipRadius*mut.clipRadius; clipDist=c80; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 81: // Klein bottle cross-section
	{
		double u81=atan2(cz.y,cz.x); double v81=atan2(cz.z,sqrt(cz.x*cz.x+cz.y*cz.y)-mut.clipMajorRadius); double kb=mut.clipParamA*(1.0-0.5*cos(u81))*sin(v81)-mut.clipParamB*cos(v81); clipDist=fabs(kb)-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 82: // Wavy cylinder
	{
		double r82=sqrt(cz.x*cz.x+cz.y*cz.y); double wave82=mut.clipRadius+mut.clipParamA*sin(mut.clipParamB*cz.z); clipDist=r82-wave82; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 83: // Twisted box
	{
		double twist83=mut.clipParamA*cz.z; double rx83=cz.x*cos(twist83)-cz.y*sin(twist83); double ry83=cz.x*sin(twist83)+cz.y*cos(twist83); clipDist=fmax(fabs(rx83)-mut.clipSizeX,fmax(fabs(ry83)-mut.clipSizeY,fabs(cz.z)-mut.clipSizeZ)); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 84: // Bent torus
	{
		double bend84=mut.clipParamA*cz.x; double bz84=cz.z+bend84*bend84; double rxy84=sqrt(cz.x*cz.x+cz.y*cz.y)-mut.clipMajorRadius; clipDist=sqrt(rxy84*rxy84+bz84*bz84)-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 85: // Corrugated plane
	{
		clipDist=cz.z-mut.clipParamA*sin(mut.clipParamB*cz.x)-mut.clipParamC*cos(mut.clipParamB*cz.y)-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 86: // Supershape 3D
	{
		double r86=cz.Length(); if(r86<1e-15)r86=1e-15; double theta86=acos(cz.z/r86); double phi86=atan2(cz.y,cz.x); double m86=(double)mut.clipNPoints; double st86=pow(pow(fabs(cos(m86*theta86/4.0)),mut.clipParamB)+pow(fabs(sin(m86*theta86/4.0)),mut.clipParamC),-1.0/mut.clipParamA); double sp86=pow(pow(fabs(cos(m86*phi86/4.0)),mut.clipParamB)+pow(fabs(sin(m86*phi86/4.0)),mut.clipParamC),-1.0/mut.clipParamA); clipDist=r86-mut.clipRadius*st86*sp86; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 87: // Egg shape
	{
		double r87=cz.Length(); double cosTheta87=cz.z/(r87+1e-15); clipDist=r87-mut.clipRadius*(1.0+mut.clipParamA*cosTheta87); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 88: // Genus-2 surface
	{
		double x2_88=cz.x*cz.x,y2_88=cz.y*cz.y,z2_88=cz.z*cz.z; clipDist=2.0*y2_88*(y2_88-mut.clipParamA*mut.clipParamA)*(y2_88-mut.clipParamA*mut.clipParamA)-x2_88*x2_88+2.0*mut.clipParamA*mut.clipParamA*(x2_88-z2_88*3.0)*(x2_88-z2_88); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 89: // Folded sphere
	{
		double fx89=fabs(fmod(cz.x+mut.clipParamA,2.0*mut.clipParamA))-mut.clipParamA; double fy89=fabs(fmod(cz.y+mut.clipParamA,2.0*mut.clipParamA))-mut.clipParamA; double fz89=fabs(fmod(cz.z+mut.clipParamA,2.0*mut.clipParamA))-mut.clipParamA; clipDist=sqrt(fx89*fx89+fy89*fy89+fz89*fz89)-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 90: // Rhombic dodecahedron
	{
		clipDist=fmax(fmax(fabs(cz.x+cz.y),fabs(cz.x-cz.y)),fmax(fabs(cz.y+cz.z),fmax(fabs(cz.y-cz.z),fmax(fabs(cz.x+cz.z),fabs(cz.x-cz.z)))))-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 91: // Tetrahedral symmetry clip
	{
		clipDist=fmax(fabs(cz.x+cz.y+cz.z),fmax(fabs(cz.x-cz.y-cz.z),fmax(fabs(-cz.x+cz.y-cz.z),fabs(-cz.x-cz.y+cz.z))))-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 92: // Sine-wave egg crate
	{
		clipDist=sin(mut.clipParamA*cz.x)+sin(mut.clipParamA*cz.y)+sin(mut.clipParamA*cz.z)-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 93: // Scherk surface
	{
		clipDist=sin(mut.clipParamA*cz.x)-sinh(mut.clipParamA*cz.y)*sinh(mut.clipParamA*cz.z)/(cosh(mut.clipParamA*cz.y)*cosh(mut.clipParamA*cz.z)+1e-10); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 94: // Enneper surface level set
	{
		double u94=cz.x,v94=cz.y; double ex94=u94-u94*u94*u94/3.0+u94*v94*v94; double ey94=v94-v94*v94*v94/3.0+v94*u94*u94; double ez94=u94*u94-v94*v94; clipDist=sqrt((cz.x-ex94)*(cz.x-ex94)+(cz.y-ey94)*(cz.y-ey94)+(cz.z-ez94)*(cz.z-ez94))-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 95: // Saddle clip
	{
		clipDist=cz.x*cz.x/fmax(mut.clipSizeX*mut.clipSizeX,1e-10)-cz.y*cz.y/fmax(mut.clipSizeY*mut.clipSizeY,1e-10)-cz.z; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 96: // Monkey saddle
	{
		clipDist=cz.x*(cz.x*cz.x-3.0*cz.y*cz.y)-mut.clipParamA*cz.z; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 97: // Cross-polytope (hyperoctahedron)
	{
		clipDist=fabs(cz.x)+fabs(cz.y)+fabs(cz.z)+fabs(z.w)-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 98: // Elliptic paraboloid
	{
		clipDist=cz.x*cz.x/fmax(mut.clipSizeX*mut.clipSizeX,1e-10)+cz.y*cz.y/fmax(mut.clipSizeY*mut.clipSizeY,1e-10)-cz.z; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 99: // Smooth intersection (sphere-box)
	{
		double d99s=cz.Length()-mut.clipRadius; double d99b=fmax(fabs(cz.x)-mut.clipSizeX,fmax(fabs(cz.y)-mut.clipSizeY,fabs(cz.z)-mut.clipSizeZ)); double k99=mut.clipSmoothK; double h99=fmax(0.0,fmin(1.0,0.5-0.5*(d99s-d99b)/fmax(k99,1e-10))); clipDist=d99s*(1.0-h99)+d99b*h99+k99*h99*(1.0-h99); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	case 100: // Fractal IFS (Sierpinski tetrahedron)
	{
		CVector3 ifs=cz; double ifsScale=1.0; for(int k=0;k<6;k++){if(ifs.x+ifs.y<0.0){double tx=-ifs.y;ifs.y=-ifs.x;ifs.x=tx;} if(ifs.x+ifs.z<0.0){double tx=-ifs.z;ifs.z=-ifs.x;ifs.x=tx;} if(ifs.y+ifs.z<0.0){double ty=-ifs.z;ifs.z=-ifs.y;ifs.y=ty;} ifs=ifs*mut.clipParamA-CVector3(mut.clipParamB,mut.clipParamB,mut.clipParamB)*(mut.clipParamA-1.0); ifsScale*=mut.clipParamA;} clipDist=(ifs.Length()-mut.clipRadius)/ifsScale; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0;
		break;
	}
	default: break;
}