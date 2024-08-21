#include "OverGameMenu.h"

void COverGameMenu::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!enable && CGame::GetInstance()->GetIsGameOver() == 1)
	{
		selectOption->SetEnable(true);
		playScene->AddObject(selectOption);
		enable = true;
	}
	CGameObject::Update(dt, coObjects);
}

void COverGameMenu::Render()
{
	if (CGame::GetInstance()->GetIsGameOver() != 1) return;
	CSprites::GetInstance()->Get(ID_SPRITE_GAMEOVER_MENU)->Draw(x, y);
};

void COverGameMenu::RunOption()
{
	selectOption->SetEnable(false);
	enable = false;
	CDataManager::getInstance()->ResetData();
	CGame::GetInstance()->SetIsGameOver(-1);
	playScene->ResetCurrentIdPath();
	if (option == OPTION_END)
	{
		CGame::GetInstance()->InitiateSwitchScene(SCENE_TITLE);
	}
}