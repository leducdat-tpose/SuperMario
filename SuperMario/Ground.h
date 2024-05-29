#pragma once

#include "GameObject.h"
#include "Sprites.h"
#include "Textures.h"
#define GROUND_BBOX_WIDTH 16
#define GROUND_BBOX_HEIGHT 16

class CGround : public CGameObject
{
	int spriteId;
	LPSPRITE sprite;
public:
	CGround(float x, float y, int spriteId):CGameObject(x,y){
		this->spriteId = spriteId;
		sprite = CSprites::GetInstance()->Get(spriteId);
	}
	void Render();
	void Update(DWORD dt) {};
	void GetBoundingBox(float& l, float& t, float& r, float& b);
};