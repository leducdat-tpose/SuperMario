#include "IntroScene.h"

CIntroScene::CIntroScene(int id, float x, float y):CGameObject(x,y)
{
	this->id = id;
}

void CIntroScene::Render()
{
	if (id == 1)
		CSprites::GetInstance()->Get(ID_SPRITE_MAP_1)->Draw(x, y);
	else
		CSprites::GetInstance()->Get(ID_SPRITE_MAP_TITLE)->Draw(x, y);
}

void CIntroScene::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}

CIntroSceneEntity::CIntroSceneEntity(float x, float y, int type) :CGameObject(x, y)
{
	this->type = type;
}

void CIntroSceneEntity::Render()
{
	if (!enable) return;
	int aniId = ID_ANI_INTRO_SCENE_1_ENTITY;
	if (type == ENTITY_TYPE_HELP_MESSAGE)
	{
		aniId = ID_ANI_INTRO_SCENE_1_HELP_MESSAGE;
	}
	else if (type == ENTITY_TYPE_SELECT_OPTION)
	{
		aniId = ID_ANI_SELECT_OPTION;
	}
	else if (type == ENTITY_TYPE_FINISH_MARK)
	{
		CSprites::GetInstance()->Get(ID_SPRITE_FINISH_SCENE)->Draw(x, y);
		return;
	}
	if (type == ENTITY_TYPE_NUMBER_VERSION_3)
	{
		aniId = ID_ANI_INTRO_SCENE_TITLE_NUMBER_3;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CIntroSceneEntity::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}