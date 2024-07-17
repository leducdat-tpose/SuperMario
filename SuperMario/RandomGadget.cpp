#include "RandomGadget.h"
#include "DataManager.h"
#include "Sprites.h"
#include <random>

CRandomGadget::CRandomGadget(float x, float y):CGameObject(x,y)
{
	isCollected = 0;
	ay = 0;
}
void CRandomGadget::Render()
{
	if (isCollected == 0)
		CAnimations::GetInstance()->Get(ID_ANI_RANDOMGADGET)->Render(x, y);
	else
		CSprites::GetInstance()->Get(ID_SPRITE_RANDOMGADGET + isCollected)->Draw(x, y);
	RenderBoundingBox();
}
void CRandomGadget::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CRandomGadget::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - RANDOMGADGET_BBOX_WIDTH / 2;
	t = y - RANDOMGADGET_BBOX_HEIGHT / 2;
	r = l + RANDOMGADGET_BBOX_WIDTH;
	b = t + RANDOMGADGET_BBOX_HEIGHT;
}
void CRandomGadget::OnNoCollision(DWORD dt)
{
	y += vy * dt;
}
void CRandomGadget::OnCollisionWith(LPCOLLISIONEVENT e)
{

}

void CRandomGadget::CollectGadget()
{
	if (isCollected != 0) return;
	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<int> distribution(1, 3);
	isCollected = distribution(generator) * 10;
	CDataManager::getInstance()->UpdateGadget(isCollected);
	ay = RANDOMGADGET_GRAVITY;
}