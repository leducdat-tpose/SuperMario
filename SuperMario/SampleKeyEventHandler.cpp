#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"
#include "ObjectPool.h"

#include "Mario.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
		mario->keyJumpDown = true;
		if (mario->GetLevel() == MARIO_LEVEL_RACCOON)
		{
			if (mario->GetIsFly() == false) mario->StartFly();
		}
		mario->SetState(MARIO_STATE_JUMP);
		break;
	case DIK_1:
		mario->SetLevel(MARIO_LEVEL_SMALL);
		break;
	case DIK_2:
		mario->SetLevel(MARIO_LEVEL_BIG);
		break;
	case DIK_3:
		mario->SetLevel(MARIO_LEVEL_RACCOON);
		break;
	case DIK_0:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_R: // reset
		//Reload();
		break;
	case DIK_A:
		mario->keyRunDown = true;
		break;
	case DIK_U:
		//Tele to secret room SCENE_1
		mario->SetPosition(2264.0f, 64.0f);
		break;
	case DIK_O:
		CObjectPool::getInstance()->getEffect()->SetValue(48.0f, 384.0f, EFFECT_TYPE_POINT, 200, 0.0f, 0.0f);
		break;
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (KeyCode)
	{
	case DIK_S:
		mario->keyJumpDown = false;
		mario->SetState(MARIO_STATE_RELEASE_JUMP);
		break;
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT_RELEASE);
		break;
	case DIK_A:
		mario->keyRunDown = false;
		if (mario->GetHeldKoopas() != nullptr)
		{
			mario->ReleaseKoopas();
		}
		if (mario->GetLevel() == MARIO_LEVEL_RACCOON)
			mario->SetAttackDone(false);
		break;
	}
}

void CSampleKeyHandler::KeyState(BYTE* states)
{
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();

	if (game->IsKeyDown(DIK_RIGHT))
	{
		if (game->IsKeyDown(DIK_A))
		{
			if (mario->GetAttackDone() == false && mario->GetLevel() == MARIO_LEVEL_RACCOON)
				mario->StartAttack();
			else mario->SetState(MARIO_STATE_RUNNING_RIGHT);
		}
		else
			mario->SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
		if (game->IsKeyDown(DIK_A))
		{
			if (mario->GetAttackDone() == false && mario->GetLevel() == MARIO_LEVEL_RACCOON)
				mario->StartAttack();
			else mario->SetState(MARIO_STATE_RUNNING_LEFT);
		}
		else
			mario->SetState(MARIO_STATE_WALKING_LEFT);
	}
	else
	{
		mario->SetState(MARIO_STATE_IDLE);
		if (game->IsKeyDown(DIK_A))
			if (mario->GetAttackDone() == false && mario->GetLevel() == MARIO_LEVEL_RACCOON)
				mario->StartAttack();
	}
}