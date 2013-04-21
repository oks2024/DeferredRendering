#pragma once

#include <vector>

#include "Voxel.h"
#include "d3d11.h"
#include "VertexStructures.h"

class Chunk
{
public:
	Chunk(/*int p_X, int p_Y, int p_Z*/);
	~Chunk(void);

	void Update();
	Voxel* GetVoxel(const int p_X,const int p_Y,const int p_Z);
	static const int CHUNK_SIZE = 16;

	int m_X;
	int m_Y;
	int m_Z;

private:
	Voxel*** m_pVoxels;
	/*ID3D11Buffer* m_pVertexBuffer;
	ID3D11Buffer* m_pIndexBuffer;*/
	std::vector<VertexPositionNormalTexture> m_VertexList;

	//// Pre allocated vertex and index arrays
	//VertexPositionNormalTexture* m_pVertexData[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];
	//WORD* m_pIndexData[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE];

	


	void ComputeBuffers();
	void CreateVoxel();

};