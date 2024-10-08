#include <algorithm>
#include "debug.h"

#include "Mario.h"
#include "Game.h"

#include "Mushroom.h"
#include "Goomba.h"
#include "Coin.h"
#include "Portal.h"
#include "Koopas.h"
#include "LuckyBox.h"
#include "SuperLeaf.h"
#include "FireBall.h"
#include "PiranhaPlant.h"
#include "Teleport.h"
#include "HiddenButton.h"
#include "ObjectPool.h"
#include "DataManager.h"
#include "RandomGadget.h"

#include "Collision.h"

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!enable) return;
	if (inTransform)
	{
		vx = 0;
		vy = 0;
		int transform_time = 0;
		if (transformSmallToBig != 0) transform_time = MARIO_TRANSFORM_TIME;
		else transform_time = MARIO_TRANSFORM_RACCOON_TIME;
		if (GetTickCount64() - transform_start > transform_time)
		{
			inTransform = false;
			//This line code is for mario changes from big to small
			if(transformSmallToBig == -1) y += (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
			transformSmallToBig = 0;
		}
	}
	else
	{
		vy += ay * dt;
		vx += ax * dt;
		MarioDecelerate();
		if (abs(vx) > abs(maxVx)) vx = maxVx;
		CheckingNextToWall();
		if (heldKoopas != nullptr) HoldKoopas();
		// reset untouchable timer if untouchable time has passed
		if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
		{
			untouchable_start = 0;
			untouchable = 0;
		}
		if (isAttack)
		{
			if (GetTickCount64() - attack_start > MARIO_ATTACK_TIME) {
				SetAttack(false);
				hitbox->SetEnable(false);
				attack_start = -1;
				if (keyRunDown == false) attackDone = false;
				else attackDone = true; // prevent hold attack button
			}
		}
		if (isKick)
		{
			if (GetTickCount64() - kick_start > MARIO_KICK_ANIMATION_TIME) {
				StopKick();
			}
		}
		if (!allowFly) {
			AllowToFly();
		}
		Fly();
		if (!isFly) isOnPlatform = false;
		else isOnPlatform = true;
		if (y > 624) SetState(MARIO_STATE_DIE);
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CMario::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMario::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CTeleport*>(e->obj))
		OnCollisionWithTeleport(e);

	if (e->ny != 0 && e->obj->IsBlocking())
	{
		
		vy = 0;
		if (e->ny < 0)
		{
			aniFly = false;
			isOnPlatform = true;
			isFly = false;
			allowFly = false;
			fly_cooldown_start = -1;
			allow_fly_start = -1;
		}
	}
	if (e->nx != 0 && e->obj->IsBlocking())
	{
		preX = x;
		isNextToWall = true;
		vx = 0;
	}

	if (dynamic_cast<CGoomba*>(e->obj))
		OnCollisionWithGoomba(e);
	else if (dynamic_cast<CCoin*>(e->obj))
		OnCollisionWithCoin(e);
	else if (dynamic_cast<CPortal*>(e->obj))
		OnCollisionWithPortal(e);
	else if (dynamic_cast<CKoopas*>(e->obj))
		OnCollisionWithKoopas(e);
	else if (dynamic_cast<CMushroom*>(e->obj))
		OnCollisionWithMushroom(e);
	else if (dynamic_cast<CLuckyBox*>(e->obj))
		OnCollisionWithLuckybox(e);
	else if (dynamic_cast<CFireBall*>(e->obj))
		OnCollisionWithFireBall(e);
	else if (dynamic_cast<CPiranhaPlant*>(e->obj))
		OnCollisionWithPiranhaPlant(e);
	else if (dynamic_cast<CSuperLeaf*>(e->obj))
		OnCollisionWithSuperLeaf(e);
	else if (dynamic_cast<CHiddenButton*>(e->obj))
		OnCollisionWithHiddenButton(e);
	else if (dynamic_cast<CRandomGadget*>(e->obj))
		OnCollisionWithRandomGadget(e);
}

void CMario::OnCollisionWithTeleport(LPCOLLISIONEVENT e)
{
	CTeleport* teleport = dynamic_cast<CTeleport*>(e->obj);
	if (isSitting)
	{
		teleport->Teleport(this->x, this->y);
		isInSecret = true;
	}
	else if(isInSecret)
	{
		teleport->Teleport(this->x, this->y);
		isInSecret = false;
	}
}

void CMario::OnCollisionWithLuckybox(LPCOLLISIONEVENT e) {
	CLuckyBox* luckybox = dynamic_cast<CLuckyBox*>(e->obj);
	if (e->ny <= 0) return;
	if (!luckybox->GetIsCollected())
	{
		switch (luckybox->GetTypeObjectSpawned())
		{
		case OBJECT_TYPE_COIN:
			CollectCoin();
			break;
		default:
			if (GetLevel() == MARIO_LEVEL_SMALL)
				luckybox->SetTypeObjectSpawned(OBJECT_TYPE_MUSHROOM);
			else if(GetLevel() == MARIO_LEVEL_BIG)
			{
				luckybox->SetTypeObjectSpawned(OBJECT_TYPE_SUPERLEAF);
			}
			else if (GetLevel() == MARIO_LEVEL_RACCOON)
			{
				luckybox->SetTypeObjectSpawned(OBJECT_TYPE_MUSHROOM_GREEN);
			}
			break;
		}
		luckybox->SetIsCollected(true);
		luckybox->SpawnObject();
	}
}

void CMario::OnCollisionWithGoomba(LPCOLLISIONEVENT e)
{
	CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);

	// jump on top >> kill Goomba and deflect a bit 
	if (e->ny < 0)
	{
		if (goomba->GetState() == PARAGOOMBA_STATE_WALKING || goomba->GetState() == PARAGOOMBA_STATE_FLY)
		{
			goomba->SetSpecialAbility(false);
			goomba->SetState(GOOMBA_STATE_WALKING);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			float goombaX, goombaY;
			goomba->GetPosition(goombaX, goombaY);
			CObjectPool::getInstance()->getEffect()->SetValue(goombaX, goombaY, EFFECT_TYPE_POINT, 100);
			goomba->SetState(GOOMBA_STATE_DIE);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
	}
	else // hit by Goomba
	{
		if (goomba->GetState() != GOOMBA_STATE_DIE)
		{
			DamagedMario();
		}
	}
}

void CMario::CollectCoin()
{
	coin++;
	CDataManager::getInstance()->AddCoin(1);
}

void CMario::OnCollisionWithCoin(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	CollectCoin();
}

void CMario::OnCollisionWithMushroom(LPCOLLISIONEVENT e)
{
	e->obj->Delete();

	if (level == MARIO_LEVEL_SMALL)
	{
		SetLevel(MARIO_LEVEL_BIG);
		CObjectPool::getInstance()->getEffect()->SetValue(this->x, this->y, EFFECT_TYPE_POINT, 1000);
	}
	else if (level == MARIO_LEVEL_RACCOON)
	{
		CObjectPool::getInstance()->getEffect()->SetValue(this->x, this->y, EFFECT_TYPE_1UP, 0);
	}
	vy = -MARIO_JUMP_DEFLECT_SPEED;
	
}

void CMario::OnCollisionWithPortal(LPCOLLISIONEVENT e)
{
	if (!isFinishScene) return;
	CPortal* p = (CPortal*)e->obj;
	p->SwitchScene(SCENE_INTRO);
}

void CMario::OnCollisionWithKoopas(LPCOLLISIONEVENT e)
{
	CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
	if (e->ny < 0)
	{
		if (koopas->GetState() == PARAKOOPAS_STATE_WALKING_RIGHT ||
			koopas->GetState() == PARAKOOPAS_STATE_WALKING_LEFT ||
			koopas->GetState() == PARAKOOPAS_STATE_FLY_LEFT ||
			koopas->GetState() == PARAKOOPAS_STATE_FLY_RIGHT)
		{
			koopas->SetIsFly(false);
			koopas->SetSpecialAbility(false);
			koopas->SetState(KOOPAS_STATE_WALKING_LEFT);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if ((koopas->GetState() != KOOPAS_STATE_HIDE && koopas->GetState() != KOOPAS_STATE_HIDE_FLIP) || koopas->GetState() == KOOPAS_STATE_HIDE_MOVING)
		{
			koopas->SetState(KOOPAS_STATE_HIDE);
			CObjectPool::getInstance()->getEffect()->SetValue(koopas->GetPositionX(), koopas->GetPositionY(), EFFECT_TYPE_POINT, 100);
			vy = -MARIO_JUMP_DEFLECT_SPEED;
		}
		else if (koopas->GetState() == KOOPAS_STATE_HIDE || koopas->GetState() == KOOPAS_STATE_HIDE_FLIP)
		{
			this->SetState(MARIO_STATE_KICK);
			if (this->nx > 0)koopas->SetDirKicked(1);
			else koopas->SetDirKicked(-1);
			koopas->SetState(KOOPAS_STATE_HIDE_MOVING);
		}
	}
	else
	{
		if (this->keyRunDown && this->level != MARIO_LEVEL_RACCOON && (koopas->GetState() == KOOPAS_STATE_HIDE || koopas->GetState() == KOOPAS_STATE_HIDE_FLIP))
		{
			koopas->SetState(KOOPAS_STATE_HELD);
			heldKoopas = koopas;
			return;
		}
		//Mario interact with koopas when his hide
		if (koopas->GetState() == KOOPAS_STATE_HIDE || koopas->GetState() == KOOPAS_STATE_HIDE_FLIP)
		{
			this->SetState(MARIO_STATE_KICK);
			if (this->nx > 0)koopas->SetDirKicked(1);
			else koopas->SetDirKicked(-1);
			koopas->SetState(KOOPAS_STATE_HIDE_MOVING);
		}
		//Damage mario
		else if (koopas->GetState() != KOOPAS_STATE_HIDE && koopas->GetState() != KOOPAS_STATE_HIDE_FLIP)
		{
			DamagedMario();
		}
	}
}

void CMario::OnCollisionWithSuperLeaf(LPCOLLISIONEVENT e)
{
	e->obj->Delete();
	if (level == MARIO_LEVEL_BIG) SetLevel(MARIO_LEVEL_RACCOON);
	CObjectPool::getInstance()->getEffect()->SetValue(this->x, this->y, EFFECT_TYPE_POINT, 1000);
}

void CMario::OnCollisionWithFireBall(LPCOLLISIONEVENT e)
{
	DamagedMario();
}

void CMario::OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e)
{
	DamagedMario();
}

void CMario::OnCollisionWithHiddenButton(LPCOLLISIONEVENT e)
{
	CHiddenButton* hiddenbutton = dynamic_cast<CHiddenButton*>(e->obj);
	if (e->ny < 0)
	{
		hiddenbutton->SetIsClicked(true);
	}
}

void CMario::OnCollisionWithRandomGadget(LPCOLLISIONEVENT e)
{
	CRandomGadget* randomGadget = dynamic_cast<CRandomGadget*>(e->obj);
	randomGadget->CollectGadget();
	this->isFinishScene = true;
	this->autoMoving = 1;
}
//
// Get animation ID for small Mario
//
int CMario::GetAniIdSmall()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(vx) == MARIO_RUNNING_SPEED)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0 || isNextToWall)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_SMALL_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
				{
					aniId = ID_ANI_MARIO_SMALL_BRACE_RIGHT;
					if (isKick) StopKick();
				}
				else if (isKick)
					aniId = ID_ANI_MARIO_SMALL_KICK_RIGHT;
				else if (vx == MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_RIGHT;
				else if (vx > 0 && vx < MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_SMALL_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
				{
					aniId = ID_ANI_MARIO_SMALL_BRACE_LEFT;
					if (isKick) StopKick();
				}
				else if (isKick)
					aniId = ID_ANI_MARIO_SMALL_KICK_LEFT;
				else if (vx == -MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_SMALL_RUNNING_LEFT;
				else if (-MARIO_RUNNING_SPEED < vx && vx < 0)
					aniId = ID_ANI_MARIO_SMALL_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_SMALL_IDLE_RIGHT;

	return aniId;
}

//
// Get animdation ID for big Mario
//
int CMario::GetAniIdBig()
{
	int aniId = -1;
	if (!isOnPlatform)
	{
		if (abs(vx) == MARIO_RUNNING_SPEED)
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_RUN_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_RUN_LEFT;
		}
		else
		{
			if (nx >= 0)
				aniId = ID_ANI_MARIO_JUMP_WALK_RIGHT;
			else
				aniId = ID_ANI_MARIO_JUMP_WALK_LEFT;
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_SIT_LEFT;
		}
		else
			if (vx == 0 || isNextToWall)
			{
				if (nx > 0) aniId = ID_ANI_MARIO_IDLE_RIGHT;
				else aniId = ID_ANI_MARIO_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
				{
					aniId = ID_ANI_MARIO_BRACE_RIGHT;
					if (isKick) StopKick();
				}
				else if (isKick)
					aniId = ID_ANI_MARIO_KICK_RIGHT;
				else if (vx == MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_RUNNING_RIGHT;
				else if (vx > 0 && vx < MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_WALKING_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
				{
					aniId = ID_ANI_MARIO_BRACE_LEFT;
					if (isKick) StopKick();
				}
				else if (isKick)
					aniId = ID_ANI_MARIO_KICK_LEFT;
				else if (vx == -MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_RUNNING_LEFT;
				else if (-MARIO_RUNNING_SPEED < vx && vx < 0)
					aniId = ID_ANI_MARIO_WALKING_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_IDLE_RIGHT;

	return aniId;
}
//
// Get animation ID for Raccoon Mario
//
int CMario::GetAniIdRaccoon()
{
	int aniId = -1;
	if (aniFly)
	{
		if (abs(vx) == MARIO_RUNNING_SPEED)
		{
			if (nx >= 0)
			{
				aniId = ID_ANI_MARIO_RACCOON_FLY_FAST_RIGHT;
			}
			else
			{
				aniId = ID_ANI_MARIO_RACCOON_FLY_FAST_LEFT;
			}
		}
		else
		{
			if (nx >= 0)
			{
				aniId = ID_ANI_MARIO_RACCOON_FLY_RIGHT;
			}
			else
			{
				aniId = ID_ANI_MARIO_RACCOON_FLY_LEFT;
			}
		}
	}
	else if (!isOnPlatform)
	{
		if (abs(ax) == MARIO_ACCEL_RUN_X)
		{
			if (nx >= 0)
			{
				aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT;
			}
			else
			{
				aniId = ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT;
			}
		}
		else
		{
			if (nx >= 0)
			{
				aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT;
			}
			else
			{
				aniId = ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT;
			}
		}
	}
	else
		if (isSitting)
		{
			if (nx > 0)
				aniId = ID_ANI_MARIO_RACCOON_SIT_RIGHT;
			else
				aniId = ID_ANI_MARIO_RACCOON_SIT_LEFT;
		}
		else
			if (vx == 0 || isNextToWall)
			{
				if (isAttack)
					if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_ATTACK_RIGHT;
					else aniId = ID_ANI_MARIO_RACCOON_ATTACK_LEFT;
				else
					if (nx > 0) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;
					else aniId = ID_ANI_MARIO_RACCOON_IDLE_LEFT;
			}
			else if (vx > 0)
			{
				if (ax < 0)
				{
					aniId = ID_ANI_MARIO_RACCOON_BRACE_RIGHT;
					if (isKick) StopKick();
				}
				else if (isKick)
					aniId = ID_ANI_MARIO_RACCOON_KICK_RIGHT;
				else if (vx == MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_RACCOON_RUNNING_RIGHT;
				else if (vx > 0 && vx < MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_RACCOON_WALKING_RIGHT;
				if(isAttack && aniId == ID_ANI_MARIO_RACCOON_WALKING_RIGHT)
					aniId = ID_ANI_MARIO_RACCOON_ATTACK_RIGHT;
			}
			else // vx < 0
			{
				if (ax > 0)
				{
					aniId = ID_ANI_MARIO_RACCOON_BRACE_LEFT;
					if (isKick) StopKick();
				}
				else if (isKick)
					aniId = ID_ANI_MARIO_RACCOON_KICK_LEFT;
				else if (vx == -MARIO_RUNNING_SPEED)
					aniId = ID_ANI_MARIO_RACCOON_RUNNING_LEFT;
				else if (-MARIO_RUNNING_SPEED < vx && vx < 0)
					aniId = ID_ANI_MARIO_RACCOON_WALKING_LEFT;
				if (isAttack && aniId == ID_ANI_MARIO_RACCOON_WALKING_LEFT)
					aniId = ID_ANI_MARIO_RACCOON_ATTACK_LEFT;
			}

	if (aniId == -1) aniId = ID_ANI_MARIO_RACCOON_IDLE_RIGHT;

	//DebugOut(L"[INFO] aniId: %d\n", aniId);

	return aniId;
}

void CMario::Render()
{
	if (!enable) return;
	if (inTransform)
	{
		if (transformSmallToBig == 0) return;
		CAnimations* animations = CAnimations::GetInstance();
		if (transformSmallToBig == -1)
		{
			if(nx > 0)	animations->Get(ID_ANI_MARIO_TRANSFORM_BIG_SMALL_RIGHT)->Render(x, y);
			else animations->Get(ID_ANI_MARIO_TRANSFORM_BIG_SMALL_LEFT)->Render(x, y);
		}
		else 
			if (nx > 0)	animations->Get(ID_ANI_MARIO_TRANSFORM_SMALL_BIG_RIGHT)->Render(x, y);
			else animations->Get(ID_ANI_MARIO_TRANSFORM_SMALL_BIG_LEFT)->Render(x, y);
		return;
	}
	
	CAnimations* animations = CAnimations::GetInstance();
	int aniId = -1;
	DebugOutTitle(L"Coins: %d", coin);
	if (isInIntroScene == true)
	{
		aniId = ID_ANI_MARIO_INTRO_SCENE_SMALL;
		animations->Get(aniId)->Render(x, y);
		return;
	}

	if (state == MARIO_STATE_DIE)
		aniId = ID_ANI_MARIO_DIE;
	else if (level == MARIO_LEVEL_BIG)
		aniId = GetAniIdBig();
	else if (level == MARIO_LEVEL_SMALL)
		aniId = GetAniIdSmall();
	else if (level == MARIO_LEVEL_RACCOON)
		aniId = GetAniIdRaccoon();

	animations->Get(aniId)->Render(x, y);
	RenderBoundingBox();

}

void CMario::SetState(int state)
{
	// DIE is the end state, cannot be changed! 
	if (this->state == MARIO_STATE_DIE) {
		if (GetTickCount64() - switchscene_start > MARIO_SWITCH_SCENE_OVERWORLD_TIME)
		{
			CGame::GetInstance()->InitiateSwitchScene(SCENE_INTRO);
			switchscene_start = -1;
		}
		return;
	}
	switch (autoMoving)
	{
	case 0: break;
	case 1:
	{
		state = MARIO_STATE_WALKING_RIGHT;
		break;
	}
	}
	switch (state)
	{
	case MARIO_STATE_RUNNING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_RUNNING_SPEED;
		ax = MARIO_ACCEL_RUN_X;
		nx = 1;
		break;
	case MARIO_STATE_RUNNING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_RUNNING_SPEED;
		ax = -MARIO_ACCEL_RUN_X;
		nx = -1;
		break;
	case MARIO_STATE_WALKING_RIGHT:
		if (isSitting) break;
		maxVx = MARIO_WALKING_SPEED;
		ax = MARIO_ACCEL_WALK_X;
		nx = 1;
		break;
	case MARIO_STATE_WALKING_LEFT:
		if (isSitting) break;
		maxVx = -MARIO_WALKING_SPEED;
		ax = -MARIO_ACCEL_WALK_X;
		nx = -1;
		break;
	case MARIO_STATE_JUMP:
		if (isSitting) break;
		if (isOnPlatform)
		{
			if (!isFly) {
				if (abs(this->vx) == MARIO_RUNNING_SPEED)
					vy = -MARIO_JUMP_RUN_SPEED_Y;
				else
					vy = -MARIO_JUMP_SPEED_Y;
				if (GetLevel() == MARIO_LEVEL_RACCOON) AllowToFly();
			}
			else {
				if (abs(this->vx) == MARIO_RUNNING_SPEED)
					vy = -MARIO_FLY_SPEED_Y;
				else
					vy = -MARIO_FLY_SPEED_Y / 2;
				ay = MARIO_FLY_GRAVITY;
			}
		}
		break;
	case MARIO_STATE_FLY:
		ay = -MARIO_GRAVITY;
		break;
	case MARIO_STATE_RELEASE_JUMP:
		if (vy < 0) vy += MARIO_JUMP_SPEED_Y / 2;
		break;

	case MARIO_STATE_SIT:
		if (isOnPlatform && level != MARIO_LEVEL_SMALL)
		{
			state = MARIO_STATE_IDLE;
			isSitting = true;
			vx = 0; vy = 0.0f;
			y += MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_SIT_RELEASE:
		if (isSitting)
		{
			isSitting = false;
			state = MARIO_STATE_IDLE;
			y -= MARIO_SIT_HEIGHT_ADJUST;
		}
		break;

	case MARIO_STATE_IDLE:
		break;

	case MARIO_STATE_DIE:
		vy = -MARIO_JUMP_DEFLECT_SPEED;
		vx = 0;
		ax = 0;
		CDataManager::getInstance()->AddLife(-1);
		switchscene_start = GetTickCount64();
		break;
	case MARIO_STATE_KICK:
		isKick = true;
		kick_start = GetTickCount64();
		break;
	}

	CGameObject::SetState(state);
}

void CMario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (inTransform || !enable) return;
	if (level == MARIO_LEVEL_BIG || level == MARIO_LEVEL_RACCOON)
	{
		if (isSitting)
		{
			left = x - MARIO_BIG_SITTING_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_SITTING_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_SITTING_BBOX_WIDTH;
			bottom = top + MARIO_BIG_SITTING_BBOX_HEIGHT;
		}
		else
		{
			left = x - MARIO_BIG_BBOX_WIDTH / 2;
			top = y - MARIO_BIG_BBOX_HEIGHT / 2;
			right = left + MARIO_BIG_BBOX_WIDTH;
			bottom = top + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else
	{
		left = x - MARIO_SMALL_BBOX_WIDTH / 2;
		top = y - MARIO_SMALL_BBOX_HEIGHT / 2;
		right = left + MARIO_SMALL_BBOX_WIDTH;
		bottom = top + MARIO_SMALL_BBOX_HEIGHT;
	}
}

void CMario::SetLevel(int l)
{
	// Adjust position to avoid falling off platform
	if (this->level == MARIO_LEVEL_SMALL)
	{
		y -= (MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT) / 2;
	}
	if (this->level == MARIO_LEVEL_SMALL && l == MARIO_LEVEL_BIG)
	{
		StartTransform();
		transformSmallToBig = 1;
	}
	else if (this->level == MARIO_LEVEL_BIG && l == MARIO_LEVEL_SMALL)
	{
		StartTransform();
		transformSmallToBig = -1;
	}
	if (level == MARIO_LEVEL_RACCOON && l == MARIO_LEVEL_BIG)
	{
		StartTransform();
		CObjectPool::getInstance()->getEffect()->SetValue(this->x, this->y, EFFECT_TYPE_TRANSFORM, 0, 0, 0);
	}
	level = l;
	if (level == MARIO_LEVEL_RACCOON)
	{
		StartTransform();
		CObjectPool::getInstance()->getEffect()->SetValue(this->x, this->y, EFFECT_TYPE_TRANSFORM, 0, 0,0);
		AddHitBox();
	}
}

void CMario::DamagedMario()
{
	if (untouchable != 0) return;
	if (level == MARIO_LEVEL_RACCOON)
	{
		SetLevel(MARIO_LEVEL_BIG);
		StartUntouchable();
	}
	else if (level == MARIO_LEVEL_BIG)
	{
		SetLevel(MARIO_LEVEL_SMALL);
		StartUntouchable();
	}
	else if (level == MARIO_LEVEL_SMALL)
	{
		DebugOut(L">>> Mario DIE >>> \n");
		SetState(MARIO_STATE_DIE);
	}
}
void CMario::StartAttack()
{
	if (isSitting) return;
	if (autoMoving != 0) return;
	//This function is use to avoid attack many times as the same time(spam attack)
	if (isAttack) return;
	attack_start = GetTickCount64();
	SetAttack(true);
	hitbox->SetPosition(this->x, this->y + 5.0f);
	hitbox->SetDirection(this->nx);
	hitbox->SetSpeed((MARIO_WALKING_SPEED+0.01f) * nx, 0);
	hitbox->SetEnable(true);
}
void CMario::AddHitBox()
{
	hitbox = new CHitBox(this, x, y, 12.0f, 8.0f, false);
	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	if (playScene != nullptr)
	{
		playScene->AddObject(hitbox);
	}
	else {
		DebugOut(L"[ERROR] Can't spawn Mario's hitbox");
	}
}

void CMario::StopKick()
{
	isKick = false;
	kick_start = -1;
}

void CMario::HoldKoopas()
{
	if (level == MARIO_LEVEL_RACCOON) return;
	if (keyRunDown == false) return;
	CKoopas* koopas = dynamic_cast<CKoopas*>(heldKoopas);
	if (koopas->GetState() == KOOPAS_STATE_HELD)
	{
		if (nx > 0)
			koopas->SetPosition(this->x + 13, this->y - 2);
		else koopas->SetPosition(this->x - 13, this->y - 2);
	}
}
void CMario::ReleaseKoopas()
{
	if (level == MARIO_LEVEL_RACCOON) return;
	if (keyRunDown == true) return;
	CKoopas* koopas = dynamic_cast<CKoopas*>(heldKoopas);
	if (heldKoopas->GetState() == KOOPAS_STATE_HELD)
	{
		this->SetState(MARIO_STATE_KICK);
		if (this->nx > 0)koopas->SetDirKicked(1);
		else koopas->SetDirKicked(-1);
		koopas->SetState(KOOPAS_STATE_HIDE_MOVING);
	}
	heldKoopas = nullptr;
}

void CMario:: StartFly()
{
	if (state != MARIO_STATE_RUNNING_LEFT && state != MARIO_STATE_RUNNING_RIGHT
		&& state != MARIO_STATE_JUMP && state != MARIO_STATE_RELEASE_JUMP) return;
	isFly = true;
	aniFly = true;
	fly_cooldown_start = GetTickCount64();
}

void CMario::Fly()
{
	if (level != MARIO_LEVEL_RACCOON || isFly == false) return;
	if (GetTickCount64() - allow_fly_start > MARIO_ALLOW_FLY_TIME)
	{
		allowFly = true;
		allow_fly_start = -1;
	}
	if (allowFly == false) return;
	if (GetTickCount64() - fly_cooldown_start > MARIO_FLY_COOLDOWN_TIME)
	{
		isFly = false;
		fly_cooldown_start = -1;
		ay = MARIO_GRAVITY;
	}
}

void CMario::AllowToFly()
{
	if (GetLevel() != MARIO_LEVEL_RACCOON) return;
	if (GetTickCount64() - allow_fly_start > MARIO_ALLOW_FLY_TIME)
	{
		allow_fly_start = -1;
		allowFly = true;
	}
}

void CMario::StartAllowFly()
{
	allow_fly_start = GetTickCount64();
}

void CMario::MarioDecelerate()
{
	if (vx == 0 || state != MARIO_STATE_IDLE) return;
	if (vx > 0)
	{ 
		vx -= abs(ax) * MARIO_DECEL_RUN_X;
		if (vx < 0)
		{
			vx = 0;
			ax = 0;
		}
	}
	else if (vx < 0)
	{
		vx += abs(ax) * MARIO_DECEL_RUN_X;
		if (vx > 0)
		{
			vx = 0;
			ax = 0;
		}
	}
}

void CMario::StartTransform()
{
	inTransform = true;
	transform_start = GetTickCount64();
}

void CMario::CheckingNextToWall()
{
	if (!isNextToWall)
	{
		return;
	}
	if (abs(preX - x) > 1.0f) isNextToWall = false;
}