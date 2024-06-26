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
	CPath(int idPath, float x, float y, int directUp = 0, int directDown = 0, int directRight = 0, int directLeft = 0)
	{
		this->idPath = idPath;
		this->x = x;
		this->y = y;
		this->directUp = directUp;
		this->directDown = directDown;
		this->directRight = directRight;
		this->directLeft = directLeft;
	}
	int GetIdPath() const { return this->idPath; }
	float GetPathX()const { return this->x; }
	float GetPathY() const { return this->y; }
	int GetDirectUp() const { return this->directUp; }
	int GetDirectDown() const { return this->directDown; }
	int GetDirectRight() const { return this->directRight; }
	int GetDirectLeft() const { return this->directLeft; }
};