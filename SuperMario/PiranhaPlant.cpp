#include "PiranhaPlant.h"

CPiranhaPlant::CPiranhaPlant(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	shoot_start = -1;
	SetState(PIRANHAPLANT_STATE_HEAD_DOWN);
}

void CPiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - PIRANHAPLANT_BBOX_WIDTH / 2;
	top = y - PIRANHAPLANT_BBOX_HEIGHT / 2;
	right = left + PIRANHAPLANT_BBOX_WIDTH;
	bottom = top + PIRANHAPLANT_BBOX_HEIGHT;
}

void CPiranhaPlant::OnNoCollision(DWORD dt)
{
};

void CPiranhaPlant::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CPiranhaPlant*>(e->obj)) return;
}

void CPiranhaPlant::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPiranhaPlant::Render()
{
	int aniId = ID_ANI_PIRANHAPLANT_HEAD_UP;
	if (state == PIRANHAPLANT_STATE_HEAD_UP)
	{
		aniId = ID_ANI_PIRANHAPLANT_HEAD_UP;
	}
	else if(state == PIRANHAPLANT_STATE_HEAD_DOWN)
	{
		aniId = ID_ANI_PIRANHAPLANT_HEAD_DOWN;
	}
	else if (state == PIRANHAPLANT_STATE_SHOOT_UP)
	{
		aniId = ID_ANI_PIRANHAPLANT_SHOOT_UP;
	}
	else if (state == PIRANHAPLANT_STATE_SHOOT_DOWN)
	{
		aniId = ID_ANI_PIRANHAPLANT_SHOOT_DOWN;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CPiranhaPlant::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case PIRANHAPLANT_STATE_HEAD_UP:
		break;
	case PIRANHAPLANT_STATE_HEAD_DOWN:
		break;
	case PIRANHAPLANT_STATE_SHOOT_UP:
		break;
	case PIRANHAPLANT_STATE_SHOOT_DOWN:
		break;
	default:
		break;
	}
}