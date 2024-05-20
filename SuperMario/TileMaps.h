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
#include "TileMap.h"

using namespace std;

class CTileMaps {
	static CTileMaps* __instance;
	unordered_map<int, LPTILEMAP> tilemaps;

public:
	void Add(int ID, LPCWSTR filePathTexture, LPCWSTR filePathData,
		int mapWidth, int mapHeight, int tileWidth = 16, int tileHeight = 16);
	LPTILEMAP Get(int ID) {
		return tilemaps[ID];
	}
	static CTileMaps* GetInstance();
};