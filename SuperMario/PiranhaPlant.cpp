#include "PiranhaPlant.h"

CPiranhaPlant::CPiranhaPlant(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	shoot_start = -1;

}

void CPiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{

}

void CPiranhaPlant::OnNoCollision(DWORD dt)
{

};

void CPiranhaPlant::OnCollisionWith(LPCOLLISIONEVENT e)
{

}

void CPiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

void CPiranhaPlant::Render()
{

}

void CPiranhaPlant::SetState(int state)
{

}