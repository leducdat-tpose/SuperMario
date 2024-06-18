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
	if (!enable) return;
	if (isClicked == false) return;
	if (GetTickCount64() - unenable_start > HIDDENBUTTON_UNENABLE_TIME)
	{
		enable = false;
		unenable_start = -1;
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