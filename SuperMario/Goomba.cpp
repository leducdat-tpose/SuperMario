#include "Goomba.h"
#include "Brick.h"

CGoomba::CGoomba(float x, float y, bool specialAbility) :CGameObject(x, y)
{
	this->specialAbility = specialAbility;
	this->ax = 0;
	this->ay = GOOMBA_GRAVITY;
	die_start = -1;
	fly_start = -1;
	isFly = false;
	isDieFlip = false;
	isCollidable = 1;
	if (this->specialAbility == true) 
	{
		this->vx = -1;// init
		SetState(PARAGOOMBA_STATE_WALKING);
	}
	else SetState(GOOMBA_STATE_WALKING);
}

void CGoomba::SetSpecialAbility(bool specialAbility) {
	this->specialAbility = specialAbility;
}

void CGoomba::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == GOOMBA_STATE_DIE)
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT_DIE / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else if(state == GOOMBA_STATE_WALKING)
	{
		left = x - GOOMBA_BBOX_WIDTH / 2;
		top = y - GOOMBA_BBOX_HEIGHT / 2;
		right = left + GOOMBA_BBOX_WIDTH;
		bottom = top + GOOMBA_BBOX_HEIGHT;
	}
	else if (state == PARAGOOMBA_STATE_WALKING)
	{
		left = x - PARAGOOMBA_BBOX_WIDTH / 2;
		top = y - PARAGOOMBA_BBOX_HEIGHT / 2;
		right = left + PARAGOOMBA_BBOX_WIDTH;
		bottom = top + PARAGOOMBA_BBOX_HEIGHT;
	}
	else if (state == PARAGOOMBA_STATE_FLY)
	{
		left = x - PARAGOOMBA_BBOX_WIDTH_FLY / 2;
		top = y - PARAGOOMBA_BBOX_HEIGHT_FLY / 2;
		right = left + PARAGOOMBA_BBOX_WIDTH_FLY;
		bottom = top + PARAGOOMBA_BBOX_HEIGHT_FLY;
	}
}

void CGoomba::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
};

void CGoomba::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;
	if (e->ny < 0 && state == PARAGOOMBA_STATE_FLY)
	{
		isFly = false;
		SetState(PARAGOOMBA_STATE_WALKING);
	}

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	if ((state == GOOMBA_STATE_DIE) && (GetTickCount64() - die_start > GOOMBA_DIE_TIMEOUT))
	{
		isDeleted = true;
		return;
	}
	if ((state == PARAGOOMBA_STATE_WALKING) && (GetTickCount64() - fly_start > PARAGOOMBA_FLY_DELAY_TIME))
	{
		fly_start = -1;
		isFly = true;
		SetState(PARAGOOMBA_STATE_FLY);
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}


void CGoomba::Render()
{
	int aniId = ID_ANI_GOOMBA_WALKING;
	if (state == PARAGOOMBA_STATE_WALKING)
	{
		aniId = ID_ANI_PARAGOOMBA_WALKING;
	}
	else if (state == PARAGOOMBA_STATE_FLY)
	{
		aniId = ID_ANI_PARAGOOMBA_FLY;
	}
	if (state == GOOMBA_STATE_DIE)
	{
		aniId = ID_ANI_GOOMBA_DIE;
		if(isDieFlip)
		{
			aniId = ID_ANI_GOOMBA_DIE_FLIP;
		}
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		die_start = GetTickCount64();
		if (!isDieFlip)
		{
			y += (GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE) / 2;
			vx = 0;
			vy = 0;
			ay = 0;
			break;
		}
		vy = -GOOMBA_DIE_DEFLECT_SPEED;
		vx = 0;
		isCollidable = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	case PARAGOOMBA_STATE_WALKING:
		fly_start = GetTickCount64();
		if (vx == -1 || nx <= 0)
		{
			vx = -GOOMBA_WALKING_SPEED;
		}
		else vx = GOOMBA_WALKING_SPEED;
		//Later
		break;
	case PARAGOOMBA_STATE_FLY:
		y -= (PARAGOOMBA_BBOX_HEIGHT_FLY - PARAGOOMBA_BBOX_HEIGHT + 2) / 2;
		if (isFly)
		{
			vy = -PARAGOOMBA_FLY_SPEED;
			vx = vx * 3.3f;
		}
		//Later
		break;
	}
}
