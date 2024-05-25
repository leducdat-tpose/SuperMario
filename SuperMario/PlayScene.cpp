#include <iostream>
#include <fstream>
#include "AssetIDs.h"


#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Platform.h"
#include "LuckyBox.h"
#include "Koopas.h"
#include "Ground.h"

#include "SampleKeyEventHandler.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) :
	CScene(id, filePath)
{
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
}

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);

	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x, y);
		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object has been created!\n");
		break;
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x, y, false); break;
	case OBJECT_TYPE_PARAGOOMBA: obj = new CGoomba(x, y, true); break;
	case OBJECT_TYPE_BRICK: obj = new CBrick(x, y); break;
	case OBJECT_TYPE_COIN: obj = new CCoin(x, y); break;
	case OBJECT_TYPE_LUCKYBOX: obj = new CLuckyBox(x, y); break;
	case OBJECT_TYPE_KOOPAS: obj = new CKoopas(x, y, false); break;
	case OBJECT_TYPE_PARAKOOPAS: obj = new CKoopas(x, y, true); break;
	case OBJECT_TYPE_MUSHROOM: obj = new CMushroom(x, y); break;

	case OBJECT_TYPE_PLATFORM:
	{

		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}

	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;


	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);


	objects.push_back(obj);
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}
//
//void CPlayScene::LoadObjects(LPCWSTR filePath)
//{
//	fstream fs;
//	fs.open(filePath, ios::in);
//	if (fs.fail())
//	{
//		DebugOut(L"[ERROR] from LoadObjects in PlayScene!");
//		fs.close();
//		return;
//	}
//	int idObj = 0;
//	float posX, posY;
//
//	while (!fs.eof())
//	{
//		fs >> idObj >> posX >> posY;
//		switch (idObj)
//		{
//		case OBJECT_TYPE_MARIO:
//		{
//			break;
//		}
//		case OBJECT_TYPE_BRICK:
//		{
//			CBrick* brick = new CBrick(posX, posY);
//			unit = new Unit(grid, brick, posX, posY);
//			break;
//		}
//			
//		case OBJECT_TYPE_GOOMBA:
//		{
//			CGoomba* goomba = new CGoomba(posX, posY, false);
//			unit = new Unit(grid, goomba, posX, posY);
//			break;
//		}
//			
//		case OBJECT_TYPE_KOOPAS:
//		{
//			CKoopas* koopas = new CKoopas(posX, posY, false);
//			unit = new Unit(grid, koopas, posX, posY);
//			break;
//		}
//		case OBJECT_TYPE_COIN:
//		{
//			CCoin* coin = new CCoin(posX, posY);
//			unit = new Unit(grid, coin, posX, posY);
//			break;
//		}
//		case OBJECT_TYPE_PLATFORM:
//		{
//			//Not now
//			break;
//		}
//		case OBJECT_TYPE_LUCKYBOX:
//		{
//			CLuckyBox* luckybox = new CLuckyBox(posX, posY);
//			unit = new Unit(grid, luckybox, posX, posY);
//			break;
//		}
//		case OBJECT_TYPE_PARAGOOMBA:
//		{
//			CGoomba* paragoomba = new CGoomba(posX, posY, true);
//			unit = new Unit(grid, paragoomba, posX, posY);
//			break;
//		}
//		case OBJECT_TYPE_MUSHROOM:
//		{
//			CMushroom* mushroom = new CMushroom(posX, posY);
//			unit = new Unit(grid, mushroom, posX, posY);
//			break;
//		}
//		case OBJECT_TYPE_PARAKOOPAS:
//		{
//			CKoopas* parakoopas = new CKoopas(posX, posY, true);
//			unit = new Unit(grid, parakoopas, posX, posY);
//			break;
//		}
//		case OBJECT_TYPE_GROUND:
//		{
//			CGround* ground = new CGround();
//			unit = new Unit(grid, ground, posX, posY);
//			break;
//		}
//		}
//	}
//	
//}


void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

//void CPlayScene::UpdateGrid() {
//	for (int i = 0; i < listUnits.size(); i++)
//	{
//		LPGAMEOBJECT obj = listUnits[i]->GetObj();
//
//		if (obj->IsEnable() == false) continue;
//
//		float newPosX, newPosY;
//		obj->GetPosition(newPosX, newPosY);
//		listUnits[i]->Move(newPosX, newPosY);
//	}
//}

void CPlayScene::Update(DWORD dt)
{
	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame* game = CGame::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;
	cy -= game->GetBackBufferHeight() / 2;

	if (cx < 0) cx = 0;

	CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);

	PurgeDeletedObjects();
	/*if (id == SCENE_TITLE)
	{
		return;
	}

	GetObjectsFromGrid();

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 0; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}
	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	UpdateCameraPosition();

	UpdateGrid();

	PurgeDeletedObjects();*/

	//vector<LPGAMEOBJECT> coObjects;
	//for (size_t i = 1; i < objects.size(); i++)
	//{
	//	coObjects.push_back(objects[i]);
	//}

	//for (size_t i = 0; i < objects.size(); i++)
	//{
	//	objects[i]->Update(dt, &coObjects);
	//}
	//if (id == SCENE_1)
	//{

	//}
	//else if(id == SCENE_2)
	//{

	//}
	//if (isGameOver == true) return;


	//// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	//if (player == NULL) return;

	//// Update camera to follow mario
	//float cx, cy;
	//player->GetPosition(cx, cy);

	//GetObjectsFromGrid();
	//UpdateGrid();

	//cx -= game->GetBackBufferWidth() / 2;
	//cy -= game->GetBackBufferHeight() / 2;

	//if (cx < 0) cx = 0;

	//CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);

	//PurgeDeletedObjects();
}

void CPlayScene::UpdateMario(DWORD dt)
{
}

void CPlayScene::UpdateCameraPosition()
{
	float cx, cy;
	mario->GetPosition(cx, cy);
	cx -= game->GetBackBufferWidth() / 2;
	cy -= game->GetBackBufferHeight() / 2;
	if (cx < 0) cx = 0;
	CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
}
//
//void CPlayScene::GetObjectsFromGrid()
//{
//	//clear a units from previous scene
//
//	listUnits.clear();
//	listCanEarnObjectsToRender.clear();
//	listStaticObjectsToRender.clear();
//	listMovingObjectsToRender.clear();
//	listPipeObjectsToRender.clear();
//	grid->Get(game->GetCameraPositon(), listUnits);
//
//	for (UINT i = 0; i < listUnits.size(); i++)
//	{
//		LPGAMEOBJECT obj = listUnits[i]->GetObj();
//		objects.push_back(obj);
//		listMovingObjectsToRender.push_back(obj);
//	}
//}
//Use when mario jump in a pipe or something else, it will teleport to that position
//void CPlayScene::SetGameState(int state)
//{
//	switch (state)
//	{
//	case GAMESTATE_1:
//		mario->SetState(1);
//		mario->SetPosition(20,10);
//		game->SetCamPos(20,10);
//		tilemaps->Get(SCENE_1)->index = 0;
//		break;
//	default:
//		break;
//	}
//}

//void CPlayScene::Init(int id)
//{
//	//When the project is quiet complete, I will change this into read file just like professor
//	this->id = id;
//	switch (this->id)
//	{
//	case SCENE_TITLE:
//		break;
//	case SCENE_1:
//		grid = new Grid(2816, 626);
//		LoadObjects(L"scenes\\scene_1_objects.txt");
//		SetGameState(GAMESTATE_1);
//		break;
//	case SCENE_2:
//		break;
//	}
//}

void CPlayScene::Render()
{
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
}


/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}