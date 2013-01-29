#pragma once
#include <vector>

#include "Model.h"
#include "Voxel.h"

class Scene
{
public:
	Scene(void);
	~Scene(void);

	std::vector<Model*> GetModels();
	Voxel voxels[256][256][256];

private:
	std::vector<Model*> m_Models;
};

