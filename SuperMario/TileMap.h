#pragma once

#include <Windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <d3d9.h>

#include "Textures.h"
#include "Sprites.h"
#include "Debug.h"

using namespace std;

class CTileMap {
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
public:
	vector<vector<int>> limitColToDraw;
	int index = 0;
	CTileMap(int ID, LPCWSTR filePathTexture, LPCWSTR filePathData,
		int mapWidth, int mapHeight, int tileWidth = 16, int tileHeight = 16);

	void LoadResources();
	void LoadMap();
	void CreateZoneToDraw();
	void Draw(D3DXVECTOR3 camPosition, bool isCrossEffect = false);
};
typedef CTileMap* LPTILEMAP;