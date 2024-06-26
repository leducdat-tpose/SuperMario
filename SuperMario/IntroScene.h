#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Sprites.h"
#include "Textures.h"

#define ID_ANI_INTRO_SCENE_1_ENTITY 31000

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
public:
	CIntroSceneEntity(float x, float y);
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
public:
	CPath(int idPath, float x, float y, int directUp = -1, int directDown = -1, int directRight = -1, int directLeft = -1)
	{
		this->idPath = idPath;
		this->x = x;
		this->y = y;
		this->directUp = directUp;
		this->directDown = directDown;
		this->directRight = directRight;
		this->directLeft = directLeft;
	}
};