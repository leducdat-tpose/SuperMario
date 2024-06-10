#include "HitBox.h"

void CHitBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (!active) return;
	l = x - bboxWidth / 2;
	t = y - bboxHeight / 2;
	r = l + bboxWidth;
	b = t + bboxHeight;
}

void CHitBox::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//Code to make the Hit box move, then collide with others object(e.g: goomba, koopas, etc.)
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CHitBox::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CHitBox::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CHitBox*>(e->obj)) return;
}