// Auto-generated mutation switch for system: inversion
// Target: GPU
// Generated mutations: 50
switch (mut->inversionType)
{
	case 1: // Type 1
	{
		rr=(zz.x/mut->invParamA)*(zz.x/mut->invParamA)+(zz.y/mut->invParamB)*(zz.y/mut->invParamB)+(zz.z/mut->invParamC)*(zz.z/mut->invParamC); if(rr<1e-21)rr=1e-21; mde=1.0f/rr; zz.x*=mde*mut->invParamA*mut->invParamA; zz.y*=mde*mut->invParamB*mut->invParamB; zz.z*=mde*mut->invParamC*mut->invParamC; mde=1.0f/rr;
		break;
	}
	case 2: // Type 2
	{
		rr=zz.x*zz.x+zz.y*zz.y; if(rr<1e-21)rr=1e-21; mde=mut->invRadius*mut->invRadius/rr; zz.x*=mde; zz.y*=mde;
		break;
	}
	case 3: // Type 3
	{
		double rxy=sqrt(zz.x*zz.x+zz.y*zz.y); rr=(rxy-mut->invParamA)*(rxy-mut->invParamA)+zz.z*zz.z; if(rr<1e-21)rr=1e-21; mde=mut->invRadius*mut->invRadius/rr; zz*=mde;
		break;
	}
	case 4: // Type 4
	{
		rr=(zz.x/mut->invParamA)*(zz.x/mut->invParamA)+(zz.y/mut->invParamB)*(zz.y/mut->invParamB)-(zz.z/mut->invParamC)*(zz.z/mut->invParamC); if(fabs(rr)<1e-21)rr=1e-21; mde=1.0f/fabs(rr); zz*=mde;
		break;
	}
	case 5: // Type 5
	{
		rr=zz.x*zz.x+zz.y*zz.y-mut->invParamA*zz.z; if(fabs(rr)<1e-21)rr=1e-21; mde=1.0f/fabs(rr); zz*=mde;
		break;
	}
	case 6: // Type 6
	{
		double tanA=tan(mut->invAngle*M_PI/180.0f); rr=zz.x*zz.x+zz.y*zz.y-tanA*tanA*zz.z*zz.z; if(fabs(rr)<1e-21)rr=1e-21; mde=1.0f/fabs(rr); zz*=mde;
		break;
	}
	case 7: // Type 7
	{
		rr=(zz.x/mut->invParamA)*(zz.x/mut->invParamA)-(zz.y/mut->invParamB)*(zz.y/mut->invParamB)-zz.z; if(fabs(rr)<1e-21)rr=1e-21; mde=1.0f/fabs(rr); zz*=mde;
		break;
	}
	case 8: // Type 8
	{
		double r2d=sqrt(zz.x*zz.x+zz.y*zz.y); double theta=atan2(zz.y,zz.x); double k=mut->invFrequency; rr=r2d*exp(-k*theta); if(fabs(rr)<1e-21)rr=1e-21; mde=1.0f/rr; zz*=mde;
		break;
	}
	case 9: // Type 9
	{
		double x2=zz.x*zz.x,y2=zz.y*zz.y; rr=(x2+y2)*(x2+y2)-mut->invParamA*mut->invParamA*(x2-y2); if(fabs(rr)<1e-21)rr=1e-21; mde=1.0f/fabs(rr); zz*=mde;
		break;
	}
	case 10: // Type 10
	{
		double d1sq=(zz.x-mut->invParamA)*(zz.x-mut->invParamA)+zz.y*zz.y; double d2sq=(zz.x+mut->invParamA)*(zz.x+mut->invParamA)+zz.y*zz.y; rr=d1sq*d2sq+zz.z*zz.z; if(fabs(rr)<1e-21)rr=1e-21; mde=1.0f/rr; zz*=mde;
		break;
	}
	case 11: // Type 11
	{
		CVector3 c1(mut.invCenterX,mut.invCenterY,mut.invCenterZ); CVector3 c2(mut.invCenter2X,mut.invCenter2Y,mut.invCenter2Z); CVector3 zr=zz+CVector3(mut.invCenterX,mut.invCenterY,mut.invCenterZ); double d1=(zr-c1).Dot(zr-c1); if(d1<1e-21)d1=1e-21; double d2=(zr-c2).Dot(zr-c2); if(d2<1e-21)d2=1e-21; mde=mut->invRadius*mut->invRadius/d1-mut.invRadius2*mut.invRadius2/d2; zz*=mde; mde=fabs(mde);
		break;
	}
	case 12: // Type 12
	{
		CVector3 c1(0,0,0); CVector3 c2(mut.invCenter2X,mut.invCenter2Y,mut.invCenter2Z); double w1=mut->invWeight,w2=1.0f-w1; double d1=(zz-c1).Dot(zz-c1); if(d1<1e-21)d1=1e-21; double d2=(zz-c2).Dot(zz-c2); if(d2<1e-21)d2=1e-21; mde=w1*mut->invRadius*mut->invRadius/d1+w2*mut.invRadius2*mut.invRadius2/d2; zz*=mde; mde=fabs(mde);
		break;
	}
	case 13: // Type 13
	{
		CVector3 c1(0,0,0); CVector3 c2(mut.invCenter2X,mut.invCenter2Y,mut.invCenter2Z); double d1=(zz-c1).Dot(zz-c1); if(d1<1e-21)d1=1e-21; double m1=mut->invRadius*mut->invRadius/d1; CVector3 z1=c1+(zz-c1)*m1; double d2=(z1-c2).Dot(z1-c2); if(d2<1e-21)d2=1e-21; double m2=mut.invRadius2*mut.invRadius2/d2; zz=c2+(z1-c2)*m2; mde=m1*m2;
		break;
	}
	case 14: // Type 14
	{
		mde=1.0f; CVector3 cc(0,0,0); double rk=mut->invRadius; for(int k=0;k<mut->invNSteps&&k<8;k++){CVector3 delta=zz-cc; double dk=delta.Dot(delta); if(dk<1e-21)dk=1e-21; double mk=rk*rk/dk; zz=cc+delta*mk; mde*=mk; cc.x+=mut.invCenter2X/(double)(k+1); cc.y+=mut.invCenter2Y/(double)(k+1); cc.z+=mut.invCenter2Z/(double)(k+1); rk*=0.8f;} mde=fabs(mde);
		break;
	}
	case 15: // Type 15
	{
		CVector3 centers[4]; centers[0]=CVector3(mut->invParamA,0,0); centers[1]=CVector3(-mut->invParamA,0,0); centers[2]=CVector3(0,mut->invParamA,0); centers[3]=CVector3(0,0,mut->invParamA); double minD=1e20; int nearest=0; for(int k=0;k<4;k++){double d=(zz-centers[k]).Dot(zz-centers[k]); if(d<minD){minD=d;nearest=k;}} if(minD<1e-21)minD=1e-21; mde=mut->invRadius*mut->invRadius/minD; zz=centers[nearest]+(zz-centers[nearest])*mde;
		break;
	}
	case 16: // Type 16
	{
		double q=fmax(1.0f,mut->invParamA); double cr2=1.0f/(2.0f*q*q); CVector3 fc(1.0f/q,cr2,0); double d=(zz-fc).Dot(zz-fc); if(d<1e-21)d=1e-21; mde=cr2*cr2/d; zz=fc+(zz-fc)*mde;
		break;
	}
	case 17: // Type 17
	{
		CVector3 c1(mut->invParamA,0,0); CVector3 c2(-mut->invParamA,0,0); double d1=(zz-c1).Dot(zz-c1); if(d1<1e-21)d1=1e-21; double d2=(zz-c2).Dot(zz-c2); if(d2<1e-21)d2=1e-21; if(d1<d2){mde=mut->invRadius*mut->invRadius/d1; zz=c1+(zz-c1)*mde;} else{mde=mut->invRadius*mut->invRadius/d2; zz=c2+(zz-c2)*mde;
		break;
	}
	case 18: // Type 18
	{
		double cz_d=mut->invParamC*zz.x+1.0f; double dn=cz_d*cz_d+mut->invParamC*mut->invParamC*zz.y*zz.y; if(dn<1e-21)dn=1e-21; mde=1.0f/dn; double nx=(mut->invParamA*zz.x+mut->invParamB)*cz_d+mut->invParamA*mut->invParamC*zz.y*zz.y; double ny=zz.y*(mut->invParamA-mut->invParamB*mut->invParamC); zz.x=nx*mde; zz.y=ny*mde;
		break;
	}
	case 19: // Type 19
	{
		rr=zz.x*zz.x+zz.y*zz.y; if(rr<1e-21)rr=1e-21; if(rr<1.0f){mde=1.0f/rr;zz.x*=mde;zz.y*=-mde;} else{mde=1.0f;} if(zz.x>0.5f)zz.x-=1.0f; if(zz.x<-0.5f)zz.x+=1.0f;
		break;
	}
	case 20: // Type 20
	{
		double lambda=2.0f*cos(M_PI/mut->invParamA); rr=zz.x*zz.x+zz.y*zz.y; if(rr<1e-21)rr=1e-21; if(rr<1.0f){mde=1.0f/rr;zz.x*=mde;zz.y*=-mde;} else{mde=1.0f;} if(zz.x>lambda*0.5f)zz.x-=lambda; if(zz.x<-lambda*0.5f)zz.x+=lambda;
		break;
	}
	case 21: // Type 21
	{
		rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=mut->invRadius*mut->invRadius/rr; zz*=mde;
		break;
	}
	case 22: // Type 22
	{
		zz.x+=mut->invAmplitude*zz.y; rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=mut->invRadius*mut->invRadius/rr; zz*=mde; zz.x-=mut->invAmplitude*zz.y;
		break;
	}
	case 23: // Type 23
	{
		double lim=mut->invParamA; if(zz.x>lim)zz.x=2.0f*lim-zz.x; if(zz.x<-lim)zz.x=-2.0f*lim-zz.x; if(zz.y>lim)zz.y=2.0f*lim-zz.y; if(zz.y<-lim)zz.y=-2.0f*lim-zz.y; if(zz.z>lim)zz.z=2.0f*lim-zz.z; if(zz.z<-lim)zz.z=-2.0f*lim-zz.z; rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=mut->invRadius*mut->invRadius/rr; zz*=mde;
		break;
	}
	case 24: // Type 24
	{
		zz.x=fabs(zz.x); zz.y=fabs(zz.y); zz.z=fabs(zz.z); rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=mut->invRadius*mut->invRadius/rr; zz*=mde;
		break;
	}
	case 25: // Type 25
	{
		rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=mut->invRadius*mut->invRadius/rr; zz*=mde; double pulse=mut->invScale*(1.0f+0.1f*sin((double)i*mut->invFrequency)); zz*=pulse; mde*=fabs(pulse);
		break;
	}
	case 26: // Type 26
	{
		rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=mut->invRadius*mut->invRadius/rr; zz*=mde; double freq=mut->invFrequency; zz.x+=mut->invAmplitude*sin(freq*zz.x); zz.y+=mut->invAmplitude*sin(freq*zz.y); zz.z+=mut->invAmplitude*sin(freq*zz.z);
		break;
	}
	case 27: // Type 27
	{
		rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=mut->invRadius*mut->invRadius/rr; zz*=mde; double ga=(double)i*2.399963f; double cosA=cos(ga),sinA=sin(ga); double tx=zz.x*cosA-zz.y*sinA; zz.y=zz.x*sinA+zz.y*cosA; zz.x=tx;
		break;
	}
	case 28: // Type 28
	{
		if(aux.DE<mut->invThreshold){rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=mut->invRadius*mut->invRadius/rr; zz*=mde;
		break;
	}
	case 29: // Type 29
	{
		rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=mut->invRadius*mut->invRadius/rr; zz*=mde; aux.color+=mut->invColorFactor*fabs(mde-1.0f);
		break;
	}
	case 30: // Type 30
	{
		rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=mut->invRadius*mut->invRadius/rr; zz*=mde; double trap=zz.Length(); if(trap<aux.color)aux.color=trap;
		break;
	}
	case 31: // Type 31
	{
		CVector4 q(zz.x,zz.y,zz.z,z.w); double qn=q.Dot(q); if(qn<1e-21)qn=1e-21; mde=1.0f/qn; q=CVector4(q.x,-q.y,-q.z,-q.w)*mde; zz=CVector3(q.x,q.y,q.z); z.w=q.w;
		break;
	}
	case 32: // Type 32
	{
		double n1=zz.x*zz.x+zz.y*zz.y; if(n1<1e-21)n1=1e-21; double n2=zz.z*zz.z+z.w*z.w; if(n2<1e-21)n2=1e-21; zz.x/=n1; zz.y/=-n1; zz.z/=n2; z.w/=-n2; mde=fmax(1.0f/n1,1.0f/n2);
		break;
	}
	case 33: // Type 33
	{
		double dn=zz.x*zz.x-zz.y*zz.y; if(fabs(dn)<1e-21)dn=1e-21; mde=1.0f/fabs(dn); zz.x=zz.x/dn; zz.y=-zz.y/dn;
		break;
	}
	case 34: // Type 34
	{
		if(fabs(zz.x)<1e-21)zz.x=1e-21; mde=1.0f/(zz.x*zz.x); double ox=1.0f/zz.x; double oy=-zz.y/(zz.x*zz.x); zz.x=ox; zz.y=oy;
		break;
	}
	case 35: // Type 35
	{
		double on=zz.Dot(zz)+z.w*z.w; if(on<1e-21)on=1e-21; mde=1.0f/on; zz*=mde; z.w*=-mde; zz.y=-zz.y; zz.z=-zz.z;
		break;
	}
	case 36: // Type 36
	{
		double sn=zz.Dot(zz)+z.w*z.w; if(sn<1e-21)sn=1e-21; mde=1.0f/sn; zz=CVector3(zz.x,-zz.y,-zz.z)*mde; z.w*=-mde;
		break;
	}
	case 37: // Type 37
	{
		rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=1.0f/rr; zz*=mde;
		break;
	}
	case 38: // Type 38
	{
		double hodge=zz.x*(zz.y*zz.z); if(fabs(hodge)<1e-21)hodge=1e-21; mde=1.0f/fabs(hodge); zz.x=(zz.y*zz.z)*mde; zz.y=(zz.x*zz.z)*mde; zz.z=(zz.x*zz.y)*mde;
		break;
	}
	case 39: // Type 39
	{
		double detA=zz.x*zz.y-zz.z*zz.z; if(fabs(detA)<1e-21)detA=1e-21; mde=1.0f/fabs(detA); double tx=zz.y*mde; zz.y=zz.x*mde; zz.x=tx; zz.z=-zz.z*mde;
		break;
	}
	case 40: // Type 40
	{
		double hash=fabs(sin(zz.x*12.9898f+zz.y*78.233f+zz.z*45.164f)*43758.5453f); hash=hash-floor(hash); double p=mut->invWeight; rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; if(hash<p){mde=mut->invRadius*mut->invRadius/rr;zz*=mde;} else{mde=1.0f;} mde=(1.0f-p)+p*mde;
		break;
	}
	case 41: // Type 41
	{
		rr=zz.Dot(zz); double minR2=mut->invMinR*mut->invMinR; double maxR2=mut->invMaxR*mut->invMaxR; if(rr<minR2)mde=maxR2/minR2; else if(rr<maxR2)mde=maxR2/rr; else mde=1.0f; zz*=mde;
		break;
	}
	case 42: // Type 42
	{
		double lim=mut->invParamA; if(zz.x>lim)zz.x=2.0f*lim-zz.x; if(zz.x<-lim)zz.x=-2.0f*lim-zz.x; if(zz.y>lim)zz.y=2.0f*lim-zz.y; if(zz.y<-lim)zz.y=-2.0f*lim-zz.y; if(zz.z>lim)zz.z=2.0f*lim-zz.z; if(zz.z<-lim)zz.z=-2.0f*lim-zz.z; rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=mut->invRadius*mut->invRadius/rr; zz*=mde; lim=mut->invParamB; if(zz.x>lim)zz.x=2.0f*lim-zz.x; if(zz.x<-lim)zz.x=-2.0f*lim-zz.x; if(zz.y>lim)zz.y=2.0f*lim-zz.y; if(zz.y<-lim)zz.y=-2.0f*lim-zz.y; if(zz.z>lim)zz.z=2.0f*lim-zz.z; if(zz.z<-lim)zz.z=-2.0f*lim-zz.z;
		break;
	}
	case 43: // Type 43
	{
		double cz_d2=mut->invParamC*zz.x+1.0f; double dn2=cz_d2*cz_d2+mut->invParamC*mut->invParamC*zz.y*zz.y; if(dn2<1e-21)dn2=1e-21; double mobMde=(mut->invParamA*1.0f-mut->invParamB*mut->invParamC)/dn2; zz.x=(mut->invParamA*zz.x+mut->invParamB)/(mut->invParamC*zz.x+1.0f+1e-21); zz.y=zz.y*mobMde; rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=mut->invRadius*mut->invRadius/rr; zz*=mde; mde*=fabs(mobMde);
		break;
	}
	case 44: // Type 44
	{
		CVector3 dynC=zz*mut->invAmplitude; rr=(zz-dynC).Dot(zz-dynC); if(rr<1e-21)rr=1e-21; mde=mut->invRadius*mut->invRadius/rr; zz=dynC+(zz-dynC)*mde;
		break;
	}
	case 45: // Type 45
	{
		CVector3 jc(mut.invCenter2X,mut.invCenter2Y,mut.invCenter2Z); rr=(zz-jc).Dot(zz-jc); if(rr<1e-21)rr=1e-21; mde=mut->invRadius*mut->invRadius/rr; zz=jc+(zz-jc)*mde;
		break;
	}
	case 46: // Type 46
	{
		CVector3 ifs_c(mut->invParamA,mut->invParamB,mut->invParamC); double d=(zz-ifs_c).Dot(zz-ifs_c); if(d<1e-21)d=1e-21; mde=mut->invRadius*mut->invRadius/d; zz=ifs_c+(zz-ifs_c)*mde; zz.x=fabs(zz.x); zz.y=fabs(zz.y);
		break;
	}
	case 47: // Type 47
	{
		rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=mut->invRadius*mut->invRadius/rr; zz*=mde; double theta=mut->invAngle*M_PI/180.0f; double cosT=cos(theta),sinT=sin(theta); double tx2=zz.x*cosT-zz.y*sinT; zz.y=zz.x*sinT+zz.y*cosT; zz.x=tx2; zz*=mut->invScale; mde*=fabs(mut->invScale);
		break;
	}
	case 48: // Type 48
	{
		zz.x+=mut->invAmplitude; zz.y+=mut->invAmplitude*zz.x*zz.x; rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=mut->invRadius*mut->invRadius/rr; zz*=mde;
		break;
	}
	case 49: // Type 49
	{
		double theta=mut->invAngle*M_PI/180.0f; double cosT=cos(theta),sinT=sin(theta); double tx3=zz.x*cosT-zz.y*sinT; zz.y=zz.x*sinT+zz.y*cosT; zz.x=tx3; rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; mde=mut->invRadius*mut->invRadius/rr; zz*=mde;
		break;
	}
	case 50: // Type 50
	{
		CVector3 aa(mut.invCenter2X,mut.invCenter2Y,mut.invCenter2Z); double an=aa.Dot(aa); double za=zz.Dot(aa); double zn=zz.Dot(zz); double dn3=1.0f+2.0f*za+an*zn; if(fabs(dn3)<1e-21)dn3=1e-21; zz=(zz*(1.0f+2.0f*za+an)+aa*(1.0f+zn))/dn3; mde=(1.0f-an)/(dn3*dn3); rr=zz.Dot(zz); if(rr<1e-21)rr=1e-21; double invMde=mut->invRadius*mut->invRadius/rr; zz*=invMde; mde*=invMde; mde=fabs(mde);
		break;
	}
	default: break;
}