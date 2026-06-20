/**
 * Voxel fog cache lookup helpers.
 */

#ifdef VOXEL_FOG_CACHE

float3 LookupVoxelFogIrradiance(float3 point, __global sLightVoxelCl *voxelCache, float3 voxelMin,
	float3 voxelSize, int voxelRes)
{
	if (voxelRes <= 0 || voxelCache == 0) return (float3)0.0f;

	int3 idx = convert_int3(floor((point - voxelMin) / voxelSize));
	if (idx.x < 0 || idx.y < 0 || idx.z < 0 || idx.x >= voxelRes || idx.y >= voxelRes || idx.z >= voxelRes)
		return (float3)0.0f;

	const int vIdx = idx.x + idx.y * voxelRes + idx.z * voxelRes * voxelRes;
	if (!voxelCache[vIdx].valid) return (float3)0.0f;

	return voxelCache[vIdx].irradianceAndDensity.xyz;
}

#endif // VOXEL_FOG_CACHE
