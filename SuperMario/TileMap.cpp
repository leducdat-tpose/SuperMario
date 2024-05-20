#include "TileMap.h"

CTileMap::CTileMap(){}

CTileMap::CTileMap(int ID, LPCWSTR filePathTexture, LPCWSTR filePathData,
	int mapWidth, int mapHeight, int tileWidth, int tileHeight) {
	this->ID = ID;
	this->filePathTexture = filePathTexture;
	this->filePathData = filePathData;
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;

	numsCol = this->mapWidth / this->tileWidth;
	numsRow = this->mapHeight / this->tileHeight;
	LoadResources();
	LoadMap();
	CreateZoneToDraw();
}

void CTileMap::LoadResources()
{

}

void CTileMap::LoadMap()
{

}

void CTileMap::CreateZoneToDraw()
{

}

void CTileMap::Draw(D3DXVECTOR3 camPosition, bool isCrossEffect)
{

}