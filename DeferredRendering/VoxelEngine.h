#pragma once
#include "Chunk.h"
class VoxelEngine
{
public:
	VoxelEngine(int p_Width, int p_Height, int p_Depth);
	~VoxelEngine(void);

	Voxel* GetVoxel(int p_X, int p_Y, int p_Z);

private:
	Chunk*** m_pChunks;
	int m_Width, m_Height, m_Depth;
};
