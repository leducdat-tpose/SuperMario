#include "OverGameMenu.h"

void COverGameMenu::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!enable && CGame::GetInstance()->GetIsGameOver() == 1)
	{
		CPlayScene* playScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
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