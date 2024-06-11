#include "CheckFall.h"
void CCheckFall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - bboxWidth / 2;
	t = y - bboxHeight / 2;
	r = l + bboxWidth;
	b = t + bboxHeight;
}
void CCheckFall::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CCheckFall::Render()
{
	RenderBoundingBox();
}
void CCheckFall::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}
void CCheckFall::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CCheckFall*>(e->obj)) return;
}