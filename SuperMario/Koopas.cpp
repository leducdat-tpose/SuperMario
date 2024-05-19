#include "Koopas.h"

CKoopas::CKoopas(float x, float y, bool specialAbility) :CGameObject(x, y)
{
	this->specialAbility = specialAbility;
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	if (this->specialAbility == true) SetState(PARAKOOPAS_STATE_WALKING_LEFT);
	else SetState(KOOPAS_STATE_WALKING_LEFT);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPAS_STATE_WALKING_RIGHT)
	{
		//Not code yet, it's from Goomba.cpp
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
	else if (state == KOOPAS_STATE_WALKING_LEFT)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
	else if (state == KOOPAS_STATE_HIDE || state == KOOPAS_STATE_HIDE_FLIP)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
	else if (state == PARAKOOPAS_STATE_WALKING_LEFT|| state == PARAKOOPAS_STATE_WALKING_RIGHT)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
	else if (PARAKOOPAS_STATE_FLY)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
	else {
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
}

void CKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}
//Copy from Goomba
void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopas*>(e->obj)) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
		if (vx > 0 && specialAbility == false) SetState(KOOPAS_STATE_WALKING_RIGHT);
		else if (vx <= 0 && specialAbility == false) SetState(KOOPAS_STATE_WALKING_LEFT);
		else if (vx > 0 && specialAbility == true) SetState(PARAKOOPAS_STATE_WALKING_RIGHT);
		else if (vx <= 0 && specialAbility == true) SetState(PARAKOOPAS_STATE_WALKING_LEFT);
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	//Not having idea yet
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);

}

void CKoopas::Render()
{
	int aniId = KOOPAS_ANI_WALKING_LEFT;
	if (state == KOOPAS_STATE_WALKING_LEFT) {
		aniId = KOOPAS_ANI_WALKING_LEFT;
	}
	else if (state == KOOPAS_STATE_WALKING_RIGHT)
	{
		aniId = KOOPAS_ANI_WALKING_RIGHT;
	}
	else if (state == KOOPAS_STATE_HIDE)
	{
		aniId = KOOPAS_ANI_HIDE;
	}
	else if (state == KOOPAS_STATE_HIDE_FLIP)
	{
		aniId = KOOPAS_ANI_HIDE_FLIP;
	}
	else if (state == KOOPAS_STATE_DIE)
	{
		//Need to know when koopas is die
		aniId = KOOPAS_ANI_DIE;
	}
	else if (state == PARAKOOPAS_STATE_WALKING_LEFT)
	{
		aniId = PARAKOOPAS_ANI_WALKING_LEFT;
	}
	else if (state == PARAKOOPAS_STATE_WALKING_RIGHT)
	{
		aniId = PARAKOOPAS_ANI_WALKING_RIGHT;

	}
	else if (state == PARAKOOPAS_STATE_FLY)
	{
		aniId = PARAKOOPAS_ANI_FLY;
	}
	else if (vx > 0 && specialAbility == false) aniId = KOOPAS_ANI_WALKING_RIGHT;
	else if (vx <= 0 && specialAbility == false) aniId = KOOPAS_ANI_WALKING_LEFT;
	else if (vx > 0 && specialAbility == true) aniId = PARAKOOPAS_ANI_WALKING_RIGHT;
	else if (vx <= 0 && specialAbility == true) aniId = PARAKOOPAS_ANI_WALKING_LEFT;

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);

	RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_HIDE:
		//Need to code here
		y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE + 1;
		//
		vx = 0;
		vy = 0;
		ay = 0;
		break;
	case KOOPAS_STATE_HIDE_FLIP:
		//Need to code here
		y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE + 1;
		//
		vx = 0;
		vy = 0;
		ay = 0;
		break;
		break;
	case KOOPAS_STATE_WALKING_LEFT:
		vx = -KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_WALKING_RIGHT:
		vx = KOOPAS_WALKING_SPEED;
		break;
	case PARAKOOPAS_STATE_WALKING_LEFT:
		vx = -KOOPAS_WALKING_SPEED;
		break;
	case PARAKOOPAS_STATE_WALKING_RIGHT:
		vx = KOOPAS_WALKING_SPEED;
		break;
	}
}