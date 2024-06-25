#include "Koopas.h"
#include "ObjectPool.h"

CKoopas::CKoopas(float x, float y, bool specialAbility) :CGameObject(x, y)
{
	this->specialAbility = specialAbility;
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	this->isFly = false;
	this->fly_start = -1;
	this->dirKicked = 1;
	checkfall = nullptr;
	AddCheckFall();
	if (this->specialAbility == true) SetState(PARAKOOPAS_STATE_WALKING_LEFT);
	else if(this->specialAbility == false) SetState(KOOPAS_STATE_WALKING_LEFT);
}

void CKoopas::SetSpecialAbility(bool specialAbility) {
	this->specialAbility = specialAbility;
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPAS_STATE_WALKING_RIGHT)
	{
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
	else if (state == KOOPAS_STATE_HIDE || state == KOOPAS_STATE_HIDE_FLIP || state == KOOPAS_STATE_HIDE_MOVING)
	{
		left = x - KOOPAS_HIDE_BBOX_WIDTH / 2;
		top = y - KOOPAS_HIDE_BBOX_HEIGHT / 2;
		right = left + KOOPAS_HIDE_BBOX_WIDTH;
		bottom = top + KOOPAS_HIDE_BBOX_HEIGHT;
	}
	else if (state == PARAKOOPAS_STATE_WALKING_LEFT|| state == PARAKOOPAS_STATE_WALKING_RIGHT)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
	else if (PARAKOOPAS_STATE_FLY_LEFT)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
	else if (PARAKOOPAS_STATE_FLY_LEFT)
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

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	if(dynamic_cast<CLuckyBox*>(e->obj))
		OnCollisionWithLuckyBox(e);
	else if(dynamic_cast<CBrick*>(e->obj))
		OnCollisionWithBrick(e);
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CKoopas*>(e->obj)) return;
	if (e->ny < 0 && (state == PARAKOOPAS_STATE_FLY_LEFT|| state == PARAKOOPAS_STATE_FLY_RIGHT))
	{
		isFly = false;
		if (state == PARAKOOPAS_STATE_FLY_LEFT) SetState(PARAKOOPAS_STATE_WALKING_LEFT);
		else SetState(PARAKOOPAS_STATE_FLY_RIGHT);
	}
	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
		if (state != KOOPAS_STATE_HIDE_MOVING && state != KOOPAS_STATE_HIDE && state != KOOPAS_STATE_HIDE_FLIP)
		{
			if (specialAbility == true)
			{
				if (vx > 0) SetState(PARAKOOPAS_STATE_WALKING_RIGHT);
				else SetState(PARAKOOPAS_STATE_WALKING_LEFT);
			}
			else {
				if (vx > 0) SetState(KOOPAS_STATE_WALKING_RIGHT);
				else SetState(KOOPAS_STATE_WALKING_LEFT);
			}
		}
	}

	
}

void CKoopas::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
	if (state == KOOPAS_STATE_HIDE_MOVING)
	{
		if (goomba->GetState() == PARAGOOMBA_STATE_WALKING || goomba->GetState() == PARAGOOMBA_STATE_FLY)
		{
			goomba->SetSpecialAbility(false);
			goomba->SetState(GOOMBA_STATE_WALKING);
		}
		else if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			float goombaX, goombaY;
			goomba->GetPosition(goombaX, goombaY);
			CObjectPool::getInstance()->getEffect()->SetValue(goombaX, goombaY, EFFECT_TYPE_KABOOM, 0, 0.0f, 0.0f);
			goomba->SetState(GOOMBA_STATE_DIE);
		}
	}
	
}

void CKoopas::OnCollisionWithLuckyBox(LPCOLLISIONEVENT e)
{
	CLuckyBox* luckybox = dynamic_cast<CLuckyBox*>(e->obj);
	if (state == KOOPAS_STATE_HIDE_MOVING)
	{
		if (!luckybox->GetIsCollected())
		{
			CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
			if (playScene == nullptr)
			{
				DebugOut(L"[ERROR] Collect coin in Koopas\n");
				return;
			}
			CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			switch (luckybox->GetTypeObjectSpawned())
			{
			case OBJECT_TYPE_COIN:
				mario->CollectCoin();
				break;
			default:
				if (mario->GetLevel() == MARIO_LEVEL_SMALL || mario->GetLevel() == MARIO_LEVEL_RACCOON)
					luckybox->SetTypeObjectSpawned(OBJECT_TYPE_MUSHROOM);
				else
				{
					luckybox->SetTypeObjectSpawned(OBJECT_TYPE_SUPERLEAF);
				}
				break;
			}
			luckybox->SetIsCollected(true);
			luckybox->SpawnObject();
		}
	}
}

void CKoopas::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);
	if (brick->GetType() != TYPE_GOLD_BRICK) return;
	if (state == KOOPAS_STATE_HIDE_MOVING)
	{
		if (e->nx != 0) brick->Delete();
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;
	if ((state == PARAKOOPAS_STATE_WALKING_RIGHT || state == PARAKOOPAS_STATE_WALKING_LEFT) && (GetTickCount64() - fly_start > PARAKOOPAS_FLY_DELAY_TIME))
	{
		fly_start = 0;
		isFly = true;
		if (state == PARAKOOPAS_STATE_WALKING_LEFT)	SetState(PARAKOOPAS_STATE_FLY_LEFT);
		else SetState(PARAKOOPAS_STATE_FLY_RIGHT);
	}
	UpdateCheckFall();
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
	else if (state == KOOPAS_STATE_HIDE || state == KOOPAS_STATE_HELD)
	{
		aniId = KOOPAS_ANI_HIDE;
	}
	else if (state == KOOPAS_STATE_HIDE_FLIP)
	{
		aniId = KOOPAS_ANI_HIDE_FLIP;
	}
	else if (state == KOOPAS_STATE_DIE)
	{
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
	else if (state == PARAKOOPAS_STATE_FLY_LEFT)
	{
		aniId = PARAKOOPAS_ANI_FLY_LEFT;
	}
	else if (state == PARAKOOPAS_STATE_FLY_RIGHT)
	{
		aniId = PARAKOOPAS_ANI_FLY_RIGHT;
	}
	else if (state == KOOPAS_STATE_HIDE_MOVING)
	{
		aniId = KOOPAS_ANI_HIDE_MOVING;
	}
	else if (specialAbility == true)
	{
		if (vx > 0)aniId = PARAKOOPAS_ANI_WALKING_RIGHT;
		else aniId = PARAKOOPAS_ANI_WALKING_LEFT;
	}
	else if(specialAbility == false)
	{
		if(vx > 0)aniId = KOOPAS_ANI_WALKING_RIGHT;
		else aniId = KOOPAS_ANI_WALKING_LEFT;
	}

	CAnimations::GetInstance()->Get(aniId)->Render(x, y);

	RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	if (state != KOOPAS_STATE_WALKING_LEFT && state != KOOPAS_STATE_WALKING_RIGHT)
		checkfall->SetEnable(false);
	else checkfall->SetEnable(true);
	ay = KOOPAS_GRAVITY;
	switch (state)
	{
	case KOOPAS_STATE_HIDE_MOVING:
	{
		vx = KOOPAS_WALKING_SPEED * 7 * dirKicked;
		y -= 2.0f;
		break;
	}
	case KOOPAS_STATE_HIDE:
	{
		//Need to code here
		y += (KOOPAS_BBOX_HEIGHT - KOOPAS_HIDE_BBOX_HEIGHT - 6)/2;
		y -= 4.0f;
		vx = 0;
		vy = 0;
		break;
	}
	case KOOPAS_STATE_HIDE_FLIP:
	{
		y += (KOOPAS_BBOX_HEIGHT - KOOPAS_HIDE_BBOX_HEIGHT - 2)/2;
		vx = 0;
		vy = 0;
		break;
	}
	case KOOPAS_STATE_WALKING_LEFT:
		vx = -KOOPAS_WALKING_SPEED;
		break;
	case KOOPAS_STATE_WALKING_RIGHT:
		vx = KOOPAS_WALKING_SPEED;
		break;
	case PARAKOOPAS_STATE_WALKING_LEFT:
		fly_start = GetTickCount64();
		vx = -KOOPAS_WALKING_SPEED;
		break;
	case PARAKOOPAS_STATE_WALKING_RIGHT:
		fly_start = GetTickCount64();
		vx = KOOPAS_WALKING_SPEED;
		break;
	case PARAKOOPAS_STATE_FLY_LEFT:
		if (isFly)
		{
			vy = -PARAKOOPAS_FLY_SPEED;
			vx = vx * 3.3f;
		}
		break;
	case PARAKOOPAS_STATE_FLY_RIGHT:
		if (isFly)
		{
			vy = -PARAKOOPAS_FLY_SPEED;
			vx = vx * 3.3f;
		}
		break;
	case KOOPAS_STATE_HELD:
		ay = 0;
		break;
	}
}

void CKoopas::AddCheckFall()
{
	checkfall = new CCheckFall(this, x + KOOPAS_BBOX_WIDTH/2 + 1.5f, y, 3.0f, KOOPAS_BBOX_HEIGHT);
	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	if (playScene != nullptr)
	{
		playScene->AddObject(this->checkfall);
	}
	else {
		DebugOut(L"[ERROR] Can't spawn check fall from Koopas!");
	}
}

void CKoopas::UpdateCheckFall()
{
	if ((state == KOOPAS_STATE_WALKING_RIGHT || state == KOOPAS_STATE_WALKING_LEFT) && !checkfall->IsEnable())
	{
		checkfall->SetPositionY(this->y);
		checkfall->SetEnable(true);
	}
	if (!checkfall->IsEnable()) return;
	if(vx > 0)
		checkfall->SetPositionX(this->x + 13.0f);
	else 
		checkfall->SetPositionX(this->x - 13.0f);
	if (checkfall->GetPositionY() - this->y > 3.0f)
	{
		if (this->vx > 0)
			SetState(KOOPAS_STATE_WALKING_LEFT);
		else
			SetState(KOOPAS_STATE_WALKING_RIGHT);
		checkfall->SetEnable(false);
	}

}