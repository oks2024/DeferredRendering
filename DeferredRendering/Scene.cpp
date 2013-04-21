#pragma once

#include "stdafx.h"
#include "Scene.h"


Scene::Scene(void)
{
	m_Models.push_back(new Model(NULL, NULL));
	srand(0);
	for (int x = 0; x < 64; x++)
		for (int y = 0; y < 10; y++)
			for (int z = 0; z < 64; z++)
			{
				if (rand()%2 == 0)
					voxels[x][y][z].State = Active;
				else
					voxels[x][y][z].State = Inactive;
			}
}


Scene::~Scene(void)
{
}

std::vector<Model*> Scene::GetModels()
{
	return m_Models;
}
