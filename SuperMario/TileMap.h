#pragma once

#include <Windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "Textures.h"
#include "Sprites.h"
#include "Debug.h"

using namespace std;

class TileMap {
	CSprites* sprites = CSprites::GetInstance();
	vector<vector<LPSPRITE>> tilemap;

	int mapWidth;
	int mapHeight;
	int numsRow;
	int numsCol;
	int tileWidth;
	int tileHeight;

	LPCWSTR filePathTexture;
	LPCWSTR filePathData;

	int ID;
};