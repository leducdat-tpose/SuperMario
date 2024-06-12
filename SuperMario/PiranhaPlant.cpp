#include "PiranhaPlant.h"

CPiranhaPlant::CPiranhaPlant(float x, float y, LPGAMEOBJECT player, int type) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = 0;
	float disXToPlayer = 0;
	float disYToPlayer = 0;
	this->player = player;
	shoot_start = -1;
	this->type = type;
	isFlip = 0;
	if (type == PIRANHAPLANT_TYPE_SHOOT)
	{
		SetState(PIRANHAPLANT_STATE_HEAD_DOWN);
	}
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
	if (type == PIRANHAPLANT_TYPE_SHOOT)
	{
		CalPosPlayer();
		if (shoot_start == -1) shoot_start = GetTickCount64();
		if (GetTickCount64() - shoot_start > PIRANHAPLANT_SHOOT_DELAY_TIME)
		{
			shoot_start = -1;
			Shoot();
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPiranhaPlant::CalPosPlayer()
{
	if (player == nullptr) return;
	float posX_player = 0, posY_player = 0;
	player->GetPosition(posX_player, posY_player);
	//This index can negative
	disXToPlayer = posX_player - x;
	disYToPlayer = posY_player - y;

	if (disYToPlayer > 0) SetState(PIRANHAPLANT_STATE_HEAD_DOWN);
	else SetState(PIRANHAPLANT_STATE_HEAD_UP);
	if (disXToPlayer > 0) isFlip = 1;
	else isFlip = 0;
}

void CPiranhaPlant::Shoot()
{
	LPGAMEOBJECT fireball = new CFireBall(x, y - 8, disXToPlayer, disYToPlayer);
	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	if (playScene != nullptr)
	{
		playScene->AddObject(fireball);
	}
	else {
		DebugOut(L"[ERROR] Can't spawn obj in PiranhaPlant\n");
	}
}


void CPiranhaPlant::Render()
{
	int aniId = ID_ANI_PIRANHAPLANT_NOT_SHOOT;
	if (type == PIRANHAPLANT_TYPE_SHOOT)
	{
		if (isFlip)
		{
			if (state == PIRANHAPLANT_STATE_HEAD_UP)
			{
				aniId = ID_ANI_PIRANHAPLANT_HEAD_UP_FLIP;
			}
			else if (state == PIRANHAPLANT_STATE_HEAD_DOWN)
			{
				aniId = ID_ANI_PIRANHAPLANT_HEAD_DOWN_FLIP;
			}
		}
		else {

			if (state == PIRANHAPLANT_STATE_HEAD_UP)
			{
				aniId = ID_ANI_PIRANHAPLANT_HEAD_UP;
			}
			else if (state == PIRANHAPLANT_STATE_HEAD_DOWN)
			{
				aniId = ID_ANI_PIRANHAPLANT_HEAD_DOWN;
			}
		}
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