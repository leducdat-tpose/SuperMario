#pragma once
#include "Game.h"
#include "Textures.h"
#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"
#include "TileMaps.h"
#include "Grid.h"
#include "Define.h"

class CPlayScene : public CScene
{
	CGame* game = CGame::GetInstance();
	//CTileMaps* tilemaps = CTileMaps::GetInstance();
	CTextures* textures = CTextures::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	//vector<Unit*> listUnits;
	vector<LPGAMEOBJECT> objects;
	//Unit* unit;
	//Grid* grid;

	//Take a sample like brick
	vector<LPGAMEOBJECT> listStaticObjectsToRender;
	//Take a sample such as mario, koopas
	vector<LPGAMEOBJECT> listMovingObjectsToRender;
	//For instance is mushroom, leaf, coin
	vector< LPGAMEOBJECT> listCanEarnObjectsToRender;
	//Mario jump into it
	vector< LPGAMEOBJECT> listPipeObjectsToRender;

	bool isGameOver = false;

protected:
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;
	//MARIO
	CMario* mario;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_TILEMAP(string line);

	void LoadAssets(LPCWSTR assetFile);
	void LoadObjects(LPCWSTR filePath);
	void LoadMap(LPCWSTR filePath, int numsColInMap, int numsRowInMap);
public:
	CPlayScene(int id, LPCWSTR filePath);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();
	void SetGameState(int state);
	void Init(int id);

	LPGAMEOBJECT GetPlayer() { return player; }
	void UpdateGrid();
	void GetObjectsFromGrid();
	void Clear();
	void PurgeDeletedObjects();
	void UpdateCameraPosition();
	void UpdateMario(DWORD dt);


	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

