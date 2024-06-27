#include "IntroScene.h"

CIntroScene::CIntroScene(int id, float x, float y):CGameObject(x,y)
{
	this->id = id;
}

void CIntroScene::Render()
{
	CSprites::GetInstance()->Get(ID_SPRITE_MAP_1)->Draw(x, y);
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
	int aniId = ID_ANI_INTRO_SCENE_1_ENTITY;
	if (type == ENTITY_TYPE_HELP_MESSAGE)
	{
		aniId = ID_ANI_INTRO_SCENE_1_HELP_MESSAGE;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
}

void CIntroSceneEntity::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}