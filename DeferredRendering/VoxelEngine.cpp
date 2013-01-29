#include "stdafx.h"
#include "VoxelEngine.h"


VoxelEngine::VoxelEngine(int p_Width, int p_Height, int p_Depth)
{
	this->m_Width = p_Width;
	this->m_Height = p_Depth;
	this->m_Depth = p_Depth;

	// Initialize datas.
	m_pChunks = new Chunk**[m_Width];
	for (int i = 0; i < m_Width; i++)
	{
		m_pChunks[i] = new Chunk*[m_Height];
		for (int j = 0; j < m_Height; j++)
		{
			m_pChunks[i][j] = new Chunk[m_Depth];
		}
	}
}


VoxelEngine::~VoxelEngine(void)
{
	// Delete datas.
	for (int i = 0; i < m_Width; i++)
	{
		for (int j = 0; j < m_Height; j++)
		{
			delete [] m_pChunks[i][j];
		}
		delete [] m_pChunks[i];
	}
	delete [] m_pChunks;
}

Voxel* VoxelEngine::GetVoxel(int p_X, int p_Y, int p_Z)
{
	int chunkSize = Chunk::CHUNK_SIZE;
	Chunk* chunk = &(m_pChunks[p_X/chunkSize][p_Y/chunkSize][p_Z/chunkSize]);

	return chunk->GetVoxel(p_X%chunkSize, p_Y%chunkSize, p_Z%chunkSize);
}
