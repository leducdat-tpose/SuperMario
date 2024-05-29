#include "FireBall.h"

CFireBall::CFireBall(float x, float y, float disX, float disY) :CGameObject(x, y)
{
	//L = v * (sqrt(2h/g))
	//Testing
	if (disY == 0)
		this->ax = 0;
	else this->ax = disX / (2 * disY / FIREBALL_GRAVITY);
	this->ay = FIREBALL_GRAVITY;
	disable_start = -1;
}

void CFireBall::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - FIREBALL_BBOX_WIDTH / 2;
	top = y  - FIREBALL_BBOX_HEIGHT / 2;
	right = left + FIREBALL_BBOX_WIDTH;
	bottom = top + FIREBALL_BBOX_HEIGHT;
}

void CFireBall::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
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
	int aniId = ID_ANI_FIREBALL;
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