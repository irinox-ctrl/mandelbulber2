/**
 * Voxel fog light cache for volumetric fog acceleration.
 */

#ifndef MANDELBULBER2_OPENCL_VOXEL_FOG_CACHE_CL_H_
#define MANDELBULBER2_OPENCL_VOXEL_FOG_CACHE_CL_H_

typedef struct
{
	float4 irradianceAndDensity;
	int valid;
	int pad0;
	int pad1;
	int pad2;
} sLightVoxelCl;

#endif /* MANDELBULBER2_OPENCL_VOXEL_FOG_CACHE_CL_H_ */
