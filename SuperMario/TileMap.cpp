#include "TileMap.h"
#include "AssetIDs.h"
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
	CTextures* texture = CTextures::GetInstance();
	texture->Add(ID, filePathTexture);
	LPTEXTURE texTileMap = texture->Get(ID);
	int textureWidth;
	int textureHeight;
	int level = 0;
	if(ID== 0){}
	else if (ID == 1) {
		textureWidth = 320;
		textureHeight = 96;
	}
	int numsRowToRead = textureHeight / tileHeight;
	int numsRolToRead = textureWidth / tileWidth;
	
	int idSprite = 1;
	for (UINT i = 0; i < numsRowToRead; i++)
	{
		for (UINT j = 0; j < numsRolToRead; j++)
		{
			int idTile = idSprite + ID_TILE;
			sprites->Add(idTile, tileWidth * j, tileHeight * i, tileWidth * (j + 1), tileHeight * (i + 1), texTileMap);
			idSprite += 1;
		}
	}
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