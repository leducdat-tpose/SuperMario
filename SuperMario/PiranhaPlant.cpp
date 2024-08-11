#include "PiranhaPlant.h"

CPiranhaPlant::CPiranhaPlant(float x, float y, LPGAMEOBJECT player, int type) :CGameObject(x, y)
{
	this->enable = true;
	this->ax = 0;
	this->ay = -PIRANHAPLANT_GRAVITY;
	this->disXToPlayer = 0;
	this->disYToPlayer = 0;
	this->player = player;
	shoot_start = -1;
	this->type = type;
	this->hibernate = false;
	this->initY = y;
	isFlip = 0;
	if (type == PIRANHAPLANT_TYPE_SHOOT)
	{
		SetState(PIRANHAPLANT_STATE_HEAD_DOWN);
	}
}

void CPiranhaPlant::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!enable) return;
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
	if (!enable) return;
	vy = ay * dt;
	y += vy * dt;
	CalPosPlayer();
	GoUpAndDown();
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CPiranhaPlant::GoUpAndDown()
{
	if (hibernate == false && (initY - y > PIRANHAPLANT_BBOX_HEIGHT - 4))
	{
		ay = 0;
		if (shoot_start == -1) shoot_start = GetTickCount64();
		if (GetTickCount64() - shoot_start > PIRANHAPLANT_SHOOT_DELAY_TIME)
		{
			shoot_start = -1;
			if (type == PIRANHAPLANT_TYPE_SHOOT) Shoot();
			SetState(PIRANHAPLANT_STATE_DOWN);
		}
	}
	if (hibernate == true && (y - initY > PIRANHAPLANT_BBOX_HEIGHT / 2 - 2))
	{
		ay = 0;
		if (shoot_start == -1) shoot_start = GetTickCount64();
		if (GetTickCount64() - shoot_start > PIRANHAPLANT_SHOOT_DELAY_TIME)
		{
			shoot_start = -1;
			SetState(PIRANHAPLANT_STATE_UP);
		}
	}
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
	if (!enable) return;
	int aniId = ID_ANI_PIRANHAPLANT_NOT_SHOOT;
	if (type == PIRANHAPLANT_TYPE_SHOOT)
	{
		if (isFlip)
		{
			if (state == PIRANHAPLANT_STATE_HEAD_UP || state == PIRANHAPLANT_STATE_UP || state == PIRANHAPLANT_STATE_DOWN)
			{
				aniId = ID_ANI_PIRANHAPLANT_HEAD_UP_FLIP;
			}
			else if (state == PIRANHAPLANT_STATE_HEAD_DOWN || state == PIRANHAPLANT_STATE_UP || state == PIRANHAPLANT_STATE_DOWN)
			{
				aniId = ID_ANI_PIRANHAPLANT_HEAD_DOWN_FLIP;
			}
		}
		else {

			if (state == PIRANHAPLANT_STATE_HEAD_UP || state == PIRANHAPLANT_STATE_UP || state == PIRANHAPLANT_STATE_DOWN)
			{
				aniId = ID_ANI_PIRANHAPLANT_HEAD_UP;
			}
			else if (state == PIRANHAPLANT_STATE_HEAD_DOWN || state == PIRANHAPLANT_STATE_UP || state == PIRANHAPLANT_STATE_DOWN)
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
	case PIRANHAPLANT_STATE_UP:
		ay = -PIRANHAPLANT_GRAVITY;
		hibernate = false;
		break;
	case PIRANHAPLANT_STATE_DOWN:
		ay = PIRANHAPLANT_GRAVITY;
		hibernate = true;
		break;
	}
}