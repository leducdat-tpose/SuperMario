#include "FireBall.h"

CFireBall::CFireBall(float x, float y, float disX, float disY) :CGameObject(x, y)
{
	ax = 0;
	ay = 0;
	if (disX < 0 && disY > 0)
	{
		ax = -FIREBALL_SPEED;
		ay = FIREBALL_GRAVITY;
	}
	else if (disX > 0 && disY > 0)
	{
		ax = FIREBALL_SPEED;
		ay = FIREBALL_GRAVITY;
	}
	else if (disX < 0 && disY < 0)
	{
		ax = -FIREBALL_SPEED;
		ay = -FIREBALL_GRAVITY;
	}
	else if (disX > 0 && disY < 0)
	{
		ax = FIREBALL_SPEED;
		ay = -FIREBALL_GRAVITY;
	}
	disable_start = GetTickCount64();
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

void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy = ay * dt;
	vx = ax * dt;
	if (GetTickCount64() - disable_start > FIREBALL_TIME_ENABLE)
	{
		Delete();
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CFireBall::Render()
{
	int aniId = ID_ANI_FIREBALL;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}
