#include "FireBall.h"

CFireBall::CFireBall(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	disable_start = -1;
}

void CFireBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x  / 2;
	top = y  / 2;
	right = left;
	bottom = top;
}

void CFireBall::OnNoCollision(DWORD dt)
{
};

void CFireBall::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CFireBall*>(e->obj)) return;
}

void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFireBall::Render()
{
	int aniId = 1;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CFireBall::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	default:
		break;
	}
}