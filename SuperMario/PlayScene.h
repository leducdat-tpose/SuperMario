#pragma once


#include <vector>

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
#include "Effects.h"
#include "IntroScene.h"
#include "DataManager.h"

class CPlayScene : public CScene
{
	CGame* game = CGame::GetInstance();
	CTextures* textures = CTextures::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();
	vector<vector<LPSPRITE>> map;
	int numsRowInMap;
	int numsColInMap;
	float cameraIndexFollowY;

	vector<LPGAMEOBJECT> objects;
	vector<CPath*> listPaths;
	int currentIdPath;

	//Take a sample like brick
	vector<LPGAMEOBJECT> listStaticObjects;
	//Take a sample such as mario, koopas
	vector<LPGAMEOBJECT> listMovingObjects;
	//For instance is mushroom, leaf, coin
	vector<LPGAMEOBJECT> listCanEarnObjects;
	//Mario jump into it
	vector<LPGAMEOBJECT> listPipeObjects;

	bool isGameOver = false;

protected:
	// A play scene has to have player, right? 
	LPGAMEOBJECT player;
	// A hidden button
	LPGAMEOBJECT hiddenbutton;
	//Player information or player status
	LPGAMEOBJECT hud;

	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ASSETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_TILEMAP(string line);
	void _ParseSection_PATHOVERWORLD(string line);

	void LoadAssets(LPCWSTR assetFile);
	void LoadObjectsFromMap();
	void LoadMap(LPCWSTR filePath);
	void RenderMap();
public:
	CPlayScene(int id, LPCWSTR filePath);
	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	LPGAMEOBJECT GetPlayer() const { return player; }
	LPGAMEOBJECT GetHiddenButton() const { return hiddenbutton; }
	void Clear();
	void PurgeDeletedObjects();
	void UpdateCameraPosition();
	void UpdateMario(DWORD dt);
	void AddObject(LPGAMEOBJECT obj);
	void UpdateCurrentIdPath(int index) { 
		if (this->id != SCENE_INTRO) return;
		this->currentIdPath += index; 
	}
	CPath* GetCurrentPath();
	static bool IsGameObjectDeleted(const LPGAMEOBJECT& o);
};

typedef CPlayScene* LPPLAYSCENE;

