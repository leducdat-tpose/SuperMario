#include "Brick.h"

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (type != TYPE_GOLD_BRICK) return;
	CHiddenButton* hiddenbutton = (CHiddenButton*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetHiddenButton();
	if (hiddenbutton->GetIsClicked() && hiddenbutton->IsEnable() && !isChangeToCoin)
	{
		ChangeToCoin();
	}
	if ((GetTickCount64() - change_to_coin_start > BRICK_CHANGE_TO_COIN_TIME) && isChangeToCoin)
	{
		ChangeBackToBrick();
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBrick::ChangeToCoin()
{
	change_to_coin_start = GetTickCount64();
	isChangeToCoin = true;
	this->coin = new CCoin(this->x, this->y);
	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	if (playScene != nullptr)
	{
		playScene->AddObject(this->coin);
	}
	else {
		DebugOut(L"[ERROR] Can't spawn coin in GoldBrick!\n");
	}
}

void CBrick::ChangeBackToBrick()
{
	if (!coin->IsDeleted())
	{
		coin->Delete();
	}
	else this->Delete();
	isChangeToCoin = false;
	change_to_coin_start = -1;
}

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (type == TYPE_GOLD_BRICK)
	{
		if (isChangeToCoin == true) return;
		animations->Get(ID_ANI_GOLD_BRICK)->Render(x, y);
	}
	else
		animations->Get(ID_ANI_BRICK)->Render(x, y);
}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isChangeToCoin == true) return;
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}