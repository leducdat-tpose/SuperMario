#include "Effects.h"

CEffects::CEffects() : CGameObject(0, 0)
{
	this->ax = 0;
	this->ay = 0;
	this->type = EFFECT_TYPE_NONE;
	this->point = 0;
	this->existStart = -1;
}

CEffects::CEffects(float x, float y, int type, int point) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	this->type = type;
	this->point = point;
	this->existStart = -1;
}

void CEffects::OnNoCollision(DWORD dt)
{
	if (type == EFFECT_TYPE_NONE) return;
	x += vx * dt;
	y += vy * dt;
}
void CEffects::Render()
{
	if (type == EFFECT_TYPE_NONE) return;
	int ainId = ID_ANI_EFFECT_100_POINT;
	if (type == EFFECT_TYPE_POINT)
	{
		if (point == 200)
			ainId = ID_ANI_EFFECT_200_POINT;
		else if (point == 400)
			ainId = ID_ANI_EFFECT_400_POINT;
		else if (point == 800)
			ainId = ID_ANI_EFFECT_800_POINT;
		else if (point == 1000)
			ainId = ID_ANI_EFFECT_1000_POINT;
		else if (point == 2000)
			ainId = ID_ANI_EFFECT_2000_POINT;
		else if (point == 4000)
			ainId = ID_ANI_EFFECT_4000_POINT;
		else if (point == 8000)
			ainId = ID_ANI_EFFECT_8000_POINT;
	}
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ainId)->Render(x, y);
}
void CEffects::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (type == EFFECT_TYPE_NONE) return;
	vy += ay * dt;
	vx += ax * dt;
	if (GetTickCount64() - existStart > EFFECT_EXIST_TIME)
	{
		existStart = -1;
		this->reset();
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CEffects::DisplayPoint(int point)
{
	if (type != EFFECT_TYPE_POINT) return;
	this->point = point;
}

void CEffects::reset()
{
	ax = 0;
	ay = 0;
	point = 0;
	type = EFFECT_TYPE_NONE;
	existStart = -1;
}
