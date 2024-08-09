#include "SuperLeaf.h"

CSuperLeaf::CSuperLeaf(float x, float y) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = SUPERLEAF_GRAVITY;
	fall_start = -1;
	SetState(SUPERLEAF_STATE_FALL_LEFT);
}

void CSuperLeaf::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!enable) return;
	left = x - SUPERLEAF_BBOX_WIDTH / 2;
	top = y - SUPERLEAF_BBOX_HEIGHT / 2;
	right = left + SUPERLEAF_BBOX_WIDTH;
	bottom = top + SUPERLEAF_BBOX_HEIGHT;
}

void CSuperLeaf::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CSuperLeaf::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CSuperLeaf*>(e->obj)) return;
	if (e->ny != 0)
	{
		vy = 0;
		isCollidable = true;
	}
};

void CSuperLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!enable) return;
	vy = ay * dt;
	vx += ax * dt;
	if ((GetTickCount64() - fall_start > SUPERLEAF_TIME_TURN_STATE) && (state == SUPERLEAF_STATE_FALL_LEFT))
	{
		SetState(SUPERLEAF_STATE_FALL_RIGHT);
	}
	else if ((GetTickCount64() - fall_start > SUPERLEAF_TIME_TURN_STATE) && (state == SUPERLEAF_STATE_FALL_RIGHT))
	{
		SetState(SUPERLEAF_STATE_FALL_LEFT);
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CSuperLeaf::Render()
{
	if (!enable) return;
	int aniId = ID_ANI_SUPERLEAF;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CSuperLeaf:: SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case SUPERLEAF_STATE_FALL_LEFT:
	{
		fall_start = GetTickCount64();
		vx = -SUPERLEAF_SPEED;
		break;
	}
	case SUPERLEAF_STATE_FALL_RIGHT:
	{
		fall_start = GetTickCount64();
		vx = SUPERLEAF_SPEED;
		break;
	}
	}
}