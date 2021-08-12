#include "WallTextureStore.h"

bool WallTextureStore::LoadWallT()
{
	if (!WallT1->loadFromFile("Textures/Walls/Wall1.png"))
		return 0;
}

bool WallTextureStore::MountTextures()
{
	bool Success = true;

	Success = LoadWallT();

	return Success;
}
