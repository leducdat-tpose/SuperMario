#include "PiranhaPlant.h"

CPiranhaPlant::CPiranhaPlant(float x, float y, LPGAMEOBJECT player) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	float disXToPlayer = 0;
	float disYToPlayer = 0;
	this->player = player;
	this->time_swap_State = -1;
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
	CalPosPlayer();
	DistanceToShoot();
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPiranhaPlant::DistanceToShoot()
{
	float distance = 0;
	distance = sqrt(pow(disXToPlayer, 2) + pow(disYToPlayer, 2));
	if (5 <= distance && distance <= 10)
	{
		shoot_start = GetTickCount64();
	}
}

void CPiranhaPlant::CalPosPlayer()
{
	float posX_player = 0, posY_player = 0;
	player->GetPosition(posX_player, posY_player);
	if (posY_player > y)
	{
		SetState(PIRANHAPLANT_STATE_HEAD_DOWN);
	}
	else 
	{
		SetState(PIRANHAPLANT_STATE_HEAD_UP);
	}
	disXToPlayer = abs(posX_player - x);
	disYToPlayer = abs(posY_player - y);
}

void CPiranhaPlant::Shoot()
{
	LPGAMEOBJECT fireball = new CFireBall(x,y, 0, 0);
	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	if (playScene != nullptr)
	{

	}
	else {
	}
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
	default:
		break;
	}
}