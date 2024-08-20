#pragma once
#include "GameObject.h"
#include "IntroScene.h"
#include "PlayScene.h"

#define OPTION_CONTINUE	100
#define OPTION_END			200

class COverGameMenu : public CGameObject
{
private:
	int option;
	CIntroSceneEntity* selectOption;
public:
	COverGameMenu(float x, float y):CGameObject(x,y)
	{
		enable = false;
		option = OPTION_CONTINUE;
		selectOption = new CIntroSceneEntity(x - 15, y + 12, ENTITY_TYPE_SELECT_OPTION);
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b){}
	void ChooseOption(int option)
	{
		this->option = option;
		if (option == OPTION_END)
			selectOption->SetPosition(x - 15, y + 20);
		else selectOption->SetPosition(x - 15, y + 12);
	}
	void RunOption()
	{
		int selectScene;
		if (option == OPTION_CONTINUE) selectScene = SCENE_INTRO;
		else selectScene = SCENE_TITLE;
		CGame::GetInstance()->InitiateSwitchScene(selectScene);
	}
};
