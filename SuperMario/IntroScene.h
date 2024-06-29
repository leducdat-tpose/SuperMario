#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Sprites.h"
#include "Textures.h"

#define ID_ANI_INTRO_SCENE_1_ENTITY 31000
#define ID_ANI_INTRO_SCENE_1_HELP_MESSAGE 32000

#define ENTITY_TYPE_TREE 0
#define ENTITY_TYPE_HELP_MESSAGE 1

class CIntroScene:public CGameObject
{
	int id;
public:
	CIntroScene(int id, float x, float y);
	~CIntroScene(){}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};

class CIntroSceneEntity :public CGameObject
{
	int type;
public:
	CIntroSceneEntity(float x, float y, int type = ENTITY_TYPE_TREE);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b) {};
};

class CPath {
private:
	int idPath;
	float x;
	float y;
	int directUp;
	int directDown;
	int directRight;
	int directLeft;
	int scene_id;
public:
	CPath(int idPath, float x, float y, int directUp = 0, int directDown = 0, int directRight = 0, int directLeft = 0, int scene_id = 0)
	{
		this->idPath = idPath;
		this->x = x;
		this->y = y;
		this->directUp = directUp;
		this->directDown = directDown;
		this->directRight = directRight;
		this->directLeft = directLeft;
		this->scene_id = scene_id;
	}
	int GetIdPath() const { return this->idPath; }
	float GetPathX()const { return this->x; }
	float GetPathY() const { return this->y; }
	int GetDirectUp() const { return this->directUp; }
	int GetDirectDown() const { return this->directDown; }
	int GetDirectRight() const { return this->directRight; }
	int GetDirectLeft() const { return this->directLeft; }
	int GetSceneId() const { return this->scene_id; }
};