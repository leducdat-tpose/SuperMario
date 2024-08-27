#include "HitBox.h"
#include "ObjectPool.h"
#include "PiranhaPlant.h"

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
	else if (dynamic_cast<CPiranhaPlant*>(e->obj))
		OnCollisionWithPiranhaPlant(e);
	else if (dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	SetEnable(false);
}

void CHitBox::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (goomba->GetState() != GOOMBA_STATE_DIE)
	{
		float goombaX, goombaY;
		goomba->GetPosition(goombaX, goombaY);
		CObjectPool::getInstance()->getEffect()->SetValue(goombaX, goombaY, EFFECT_TYPE_KABOOM, 0, 0.0f, 0.0f);
		CObjectPool::getInstance()->getEffect()->SetValue(goombaX, goombaY, EFFECT_TYPE_POINT, 100);
		goomba->SetDieFlip(true);
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
void CHitBox::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);
	if (brick->GetType() != TYPE_GOLD_BRICK) return;
	brick->Delete();
}
void CHitBox::OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e)
{
	CPiranhaPlant* piranha = dynamic_cast<CPiranhaPlant*>(e->obj);
	float piranhaPosX, piranhaPosY;
	piranha->GetPosition(piranhaPosX, piranhaPosY);
	piranha->Delete();
	CObjectPool::getInstance()->getEffect()->SetValue(piranhaPosX, piranhaPosY, EFFECT_TYPE_KABOOM, 0, 0.0f, 0.0f);
	CObjectPool::getInstance()->getEffect()->SetValue(piranhaPosX, piranhaPosY, EFFECT_TYPE_POINT, 100);
}