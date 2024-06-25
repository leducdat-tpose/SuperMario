#pragma once
#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Sprites.h"
#include "Textures.h"

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