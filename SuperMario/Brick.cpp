#include "Brick.h"

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (type != TYPE_GOLD_BRICK) return;
	ChangeToCoin();
	if (isChangeToCoin)
	{
		if (GetTickCount64() - change_to_coin_start > BRICK_CHANGE_TO_COIN_TIME)
		{
			isChangeToCoin = false;
			change_to_coin_start = -1;
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CBrick::ChangeToCoin()
{
	CHiddenButton* hiddenbutton = (CHiddenButton*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetHiddenButton();
	if (hiddenbutton->GetIsClicked() && hiddenbutton->IsEnable())
	{
		isChangeToCoin = true;
		change_to_coin_start = GetTickCount64();
	}
}

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (type == TYPE_GOLD_BRICK)
	{
		//CHiddenButton* hiddenbutton = (CHiddenButton*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetHiddenButton();
		if (isChangeToCoin == true)
		{
			DebugOut(L"[INFO] debug!");
			return;
		}
		animations->Get(ID_ANI_GOLD_BRICK)->Render(x, y);
	}
	else
		animations->Get(ID_ANI_BRICK)->Render(x, y);
}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (isChangeToCoin) return;
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}