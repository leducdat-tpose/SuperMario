#include "RandomGadget.h"
#include "DataManager.h"
#include "Sprites.h"
#include <random>

CRandomGadget::CRandomGadget(float x, float y):CGameObject(x,y)
{
	isCollected = 0;
	ay = 0;
	delete_start = -1;
}
void CRandomGadget::Render()
{
	CAnimations::GetInstance()->Get(ID_ANI_RANDOMGADGET + isCollected)->Render(x, y);
	RenderBoundingBox();
}
void CRandomGadget::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	if (isCollected != 0 && GetTickCount64() - delete_start > RANDOMGADGET_EXIST_TIME)
	{
		this->Delete();
	}
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
	/////////////////Random 1 to 3
	random_device rd;
	mt19937 generator(rd());
	uniform_int_distribution<int> distribution(1, 3);
	isCollected = distribution(generator) * 10;
	////////////////
	ay = RANDOMGADGET_GRAVITY;
	delete_start = GetTickCount64();
	CDataManager::getInstance()->SetIsFinishStage(CGame::GetInstance()->GetCurrentScene()->GetId(), true);
	CDataManager::getInstance()->UpdateGadget(isCollected);
}