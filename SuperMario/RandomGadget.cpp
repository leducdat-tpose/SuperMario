#include "RandomGadget.h"
#include "DataManager.h"
#include <random>

CRandomGadget::CRandomGadget(float x, float y):CGameObject(x,y)
{

}
void CRandomGadget::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_RANDOMGADGET)->Render(x, y);
	RenderBoundingBox();
}
void CRandomGadget::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}
void CRandomGadget::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - RANDOMGADGET_BBOX_WIDTH / 2;
	t = y - RANDOMGADGET_BBOX_HEIGHT / 2;
	r = l + RANDOMGADGET_BBOX_WIDTH;
	b = t + RANDOMGADGET_BBOX_HEIGHT;
}
void CRandomGadget::OnCollisionWith(LPCOLLISIONEVENT e)
{

}

void CRandomGadget::CollectGadget()
{
	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<int> distribution(1, 3);
	CDataManager::getInstance()->UpdateGadget(distribution(generator) * 10);
	this->Delete();
}