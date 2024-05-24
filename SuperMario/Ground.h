#pragma once

#include "GameObject.h"
#include "Sprites.h"
#include "Textures.h"
#define GROUND_BBOX_WIDTH 16
#define GROUND_BBOX_HEIGHT 16

#define ID_ANI_GROUND 16000

class CGround : public CGameObject
{
public:
	CGround() {};
	CGround(float x, float y):CGameObject(x,y){}
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};