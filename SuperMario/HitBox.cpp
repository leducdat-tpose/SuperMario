#include "HitBox.h"

void CHitBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (!enable) return;
	l = x - bboxWidth / 2;
	t = y - bboxHeight / 2;
	r = l + bboxWidth;
	b = t + bboxHeight;
}

void CHitBox::Render()
{
	if (!enable) return;
	RenderBoundingBox();
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
	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
}

void CHitBox::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (goomba->GetState() != GOOMBA_STATE_DIE)
	{
		goomba->SetState(GOOMBA_STATE_DIE);
	}
}
void CHitBox::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
	if ((koopas->GetState() != KOOPAS_STATE_HIDE && koopas->GetState() != KOOPAS_STATE_HIDE_FLIP) || koopas->GetState() == KOOPAS_STATE_HIDE_MOVING)
	{
		koopas->SetState(KOOPAS_STATE_HIDE_FLIP);
	}
	else if (state == KOOPAS_STATE_HIDE_FLIP || state == KOOPAS_STATE_HIDE)
	{
		koopas->SetState(KOOPAS_STATE_HIDE_MOVING);
	}
}