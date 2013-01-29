#pragma once

#include <vector>

#include "Voxel.h"
#include "d3d11.h"

class Chunk
{
public:
	Chunk(void);
	~Chunk(void);

	void Update();
	Voxel* GetVoxel(int p_X, int p_Y, int p_Z);
	static const int CHUNK_SIZE = 16;

private:
	Voxel*** m_pVoxels;
	ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;

	void ComputeBuffers();
	void CreateVoxel();
};