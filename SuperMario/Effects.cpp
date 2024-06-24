#include "Effects.h"

CEffects::CEffects(float x, float y) : CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
}

void CEffects::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
void CEffects::Render()
{

}
void CEffects::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
