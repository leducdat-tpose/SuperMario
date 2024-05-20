#include "TileMaps.h"

CTileMaps* CTileMaps::__instance = NULL;

void CTileMaps::Add(int ID, LPCWSTR filePathTexture, LPCWSTR filePathData,
	int mapWidth, int mapHeight, int tileWidth, int tileHeight) {
	LPTILEMAP tilemap = new CTileMap(ID, filePathTexture, filePathData, mapWidth, mapHeight, tileWidth, tileHeight);
	tilemaps[ID] = tilemap;
}

CTileMaps* CTileMaps::GetInstance()
{
	if (__instance == NULL) __instance = new CTileMaps();
	return __instance;
}