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