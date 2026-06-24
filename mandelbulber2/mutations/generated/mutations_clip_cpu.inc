// Auto-generated mutation switch for system: clip
// Target: CPU
// Generated mutations: 8
switch (mut.clipType)
{
	case 1: // Ellipsoid clip
	{
		clipDist=sqrt((cz.x/mut.clipSizeX)*(cz.x/mut.clipSizeX)+(cz.y/mut.clipSizeY)*(cz.y/mut.clipSizeY)+(cz.z/mut.clipSizeZ)*(cz.z/mut.clipSizeZ))-1.0; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0; }
		break;
	}
	case 2: // Torus clip
	{
		double rxy=sqrt(cz.x*cz.x+cz.y*cz.y)-mut.clipMajorRadius; clipDist=sqrt(rxy*rxy+cz.z*cz.z)-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0; }
		break;
	}
	case 3: // Cylinder XY clip
	{
		clipDist=sqrt(cz.x*cz.x+cz.y*cz.y)-mut.clipRadius; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0; }
		break;
	}
	case 4: // Cone clip
	{
		double tanAlpha=tan(mut.clipAngle*M_PI/180.0); clipDist=sqrt(cz.x*cz.x+cz.y*cz.y)-tanAlpha*fabs(cz.z); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0; }
		break;
	}
	case 5: // Hyperboloid one-sheet clip
	{
		clipDist=(cz.x/mut.clipSizeX)*(cz.x/mut.clipSizeX)+(cz.y/mut.clipSizeY)*(cz.y/mut.clipSizeY)-(cz.z/mut.clipSizeZ)*(cz.z/mut.clipSizeZ)-1.0; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0; }
		break;
	}
	case 6: // Parabolic clip
	{
		clipDist=cz.x*cz.x+cz.y*cz.y-mut.clipParamA*cz.z; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0; }
		break;
	}
	case 7: // Hyperbolic saddle clip
	{
		clipDist=(cz.x/mut.clipSizeX)*(cz.x/mut.clipSizeX)-(cz.y/mut.clipSizeY)*(cz.y/mut.clipSizeY)-cz.z; if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0; }
		break;
	}
	case 8: // Log-spiral clip
	{
		double r2d=sqrt(cz.x*cz.x+cz.y*cz.y); double theta=atan2(cz.y,cz.x); clipDist=r2d-mut.clipParamA*exp(mut.clipParamB*theta); if (clipDist < 0.0) { cz.x *= 0.0; cz.y *= 0.0; cz.z *= 0.0; }
		break;
	}
	default: break;
}