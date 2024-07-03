#include "HiddenButton.h"

void CHiddenButton::Render()
{
	if (!enable) return;
	int aniId = ID_ANI_HIDDENBUTTON;
	if (isClicked)
	{
		aniId = ID_ANI_HIDDENBUTTON_CLICKED;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}
void CHiddenButton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	UpdateCheckFall();
	//if (!enable) return;
	//if (isClicked == false) return;
	if (enable && isClicked)
	{
		if (GetTickCount64() - unenable_start > HIDDENBUTTON_UNENABLE_TIME)
		{
			enable = false;
			unenable_start = -1;
		}
	}
	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}
void CHiddenButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (!enable) return;
	l = x - HIDDENBUTTON_BBOX_WIDTH / 2;
	t = y - HIDDENBUTTON_BBOX_HEIGHT / 2;
	r = l + HIDDENBUTTON_BBOX_WIDTH;
	b = t + HIDDENBUTTON_BBOX_HEIGHT;
}
void CHiddenButton::OnCollisionWith(LPCOLLISIONEVENT e) {};
void CHiddenButton::SetIsClicked(bool isClicked)
{
	if (this->isClicked) return;
	this->isClicked = isClicked;
	if (this->isClicked) unenable_start = GetTickCount64();
}
bool CHiddenButton::GetIsClicked()
{
	return this->isClicked;
}
void CHiddenButton::AddCheckFall()
{
	checkfall = new CCheckFall(this, this->x, this->y, HIDDENBUTTON_BBOX_WIDTH/2, HIDDENBUTTON_BBOX_HEIGHT/2);
	CPlayScene* playScene = dynamic_cast<CPlayScene*>(CGame::GetInstance()->GetCurrentScene());
	if (playScene != nullptr)
	{
		playScene->AddObject(this->checkfall);
		checkfall->SetEnable(true);
	}
	else {
		DebugOut(L"[ERROR] Can't spawn check fall from HiddenButton!");
	}
}

void CHiddenButton::UpdateCheckFall()
{
	if (checkfall == nullptr || checkfall->IsEnable() == false || checkfall->IsDeleted() == true) return;
	if (checkfall->GetPositionY() - this->y > 10.0f)
	{
		checkfall->SetEnable(false);
		this->SetEnable(true);
	}
	
}