#include "SampleKeyEventHandler.h"

#include "debug.h"
#include "Game.h"

#include "Mario.h"
#include "OverGameMenu.h"
#include "PlayScene.h"

void CSampleKeyHandler::OnKeyDown(int KeyCode)
{
	CPlayScene* playScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	CMario* mario = (CMario*)playScene->GetPlayer();
	if (playScene->GetId() == SCENE_TITLE)
	{
		if (KeyCode == DIK_W)	CGame::GetInstance()->InitiateSwitchScene(SCENE_INTRO);
		return;
	}
	if (CGame::GetInstance()->GetIsGameOver() == 1)
	{
		COverGameMenu* gameOverMenu = (COverGameMenu*)playScene->GetGameOverMenu();
		if (KeyCode == DIK_UP)
		{
			gameOverMenu->ChooseOption(OPTION_CONTINUE);
		}
		else if (KeyCode == DIK_DOWN)
		{
			gameOverMenu->ChooseOption(OPTION_END);
		}
		else if (KeyCode == DIK_W)
		{
			gameOverMenu->RunOption();
		}
		return;
	}
	if (playScene->GetId() == SCENE_INTRO)
	{
		CPath* currentPath = playScene->GetCurrentPath();
		if (currentPath == nullptr) return;
		switch (KeyCode)
		{
		case DIK_UP:
			playScene->UpdateCurrentIdPath(currentPath->GetDirectUp());
			break;
		case DIK_DOWN:
			playScene->UpdateCurrentIdPath(currentPath->GetDirectDown());
			break;
		case DIK_RIGHT:
			playScene->UpdateCurrentIdPath(currentPath->GetDirectRight());
			break;
		case DIK_LEFT:
			playScene->UpdateCurrentIdPath(currentPath->GetDirectLeft());
			break;
		case DIK_S:
			if (currentPath->GetSceneId() == 0) return;
			CGame::GetInstance()->InitiateSwitchScene(currentPath->GetSceneId());
			break;
		}
		return;
	}
	switch (KeyCode)
	{
	case DIK_DOWN:
		mario->SetState(MARIO_STATE_SIT);
		break;
	case DIK_S:
		mario->keyJumpDown = true;
		if (mario->GetLevel() == MARIO_LEVEL_RACCOON)
		{
			mario->StartAllowFly();
			if (!mario->GetIsFly() && mario->GetAllowFly()) 
				mario->StartFly();
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
	case DIK_I:
		CGame::GetInstance()->OnOffDisplayBoundingBox();
		break;
	case DIK_P:
		//CDataManager::getInstance()->SetIsFinishStage(playScene->GetId(), true);
		CGame::GetInstance()->InitiateSwitchScene(SCENE_INTRO);
		break;
	case DIK_W:
		CGame::GetInstance()->PauseGame();
		playScene->PauseGame(CGame::GetInstance()->GetIsPauseGame());
		break;
	case DIK_T:
		DebugOut(L"Mario's position X: %f\n", mario->GetPositionX());
	}
}

void CSampleKeyHandler::OnKeyUp(int KeyCode)
{
	//DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);
	CPlayScene* playScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	if (playScene->GetId() == SCENE_INTRO) return;

	CMario* mario = (CMario*)playScene->GetPlayer();
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
	CPlayScene* playScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
	if (playScene->GetId() == SCENE_INTRO) return;
	LPGAME game = CGame::GetInstance();
	CMario* mario = (CMario*)playScene->GetPlayer();

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