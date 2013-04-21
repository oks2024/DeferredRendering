#pragma once

#include "stdafx.h"
#include "Chunk.h"




Chunk::Chunk(/*int p_X, int p_Y, int p_Z*/)
{
	/*m_X = p_X;
	m_Y = p_Y;
	m_Z = p_Z;*/

	// Initialize datas.
	m_pVoxels = new Voxel**[CHUNK_SIZE];
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		m_pVoxels[i] = new Voxel*[CHUNK_SIZE];
		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			m_pVoxels[i][j] = new Voxel[CHUNK_SIZE];
		}
	}
}


Chunk::~Chunk(void)
{
	// Delete datas.
	for (int i = 0; i < CHUNK_SIZE; i++)
	{
		for (int j = 0; j < CHUNK_SIZE; j++)
		{
			delete [] m_pVoxels[i][j];
		}
		delete [] m_pVoxels[i];
	}
	delete [] m_pVoxels;
}

void Chunk::Update()
{
	//std::vector<VertexPositionNormalTexture> *vertexBuffer = new std::vector<VertexPositionNormalTexture>();
	//std::vector<WORD> *indexBuffer = new std::vector<WORD>();

	for (int x = 0; x < CHUNK_SIZE; x++)
	{
		for (int y = 0; y < CHUNK_SIZE; y++)
		{
			for (int z = 0; z < CHUNK_SIZE; z++)
			{
				CreateVoxel();
			}
		}
	}


}


void Chunk::CreateVoxel()
{

}

Voxel* Chunk::GetVoxel(const int p_X,const int p_Y,const int p_Z)
{
	return &(m_pVoxels[p_X][p_Y][p_Z]);
}
