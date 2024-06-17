#include "HiddenButton.h"

void CHiddenButton::Render()
{
	int aniId = ID_ANI_HIDDENBUTTON;
	if (isClicked)
	{
		aniId = ID_ANI_HIDDENBUTTON_CLICKED;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}
void CHiddenButton::Update(DWORD dt)
{

}
void CHiddenButton::GetBoundingBox(float& l, float& t, float& r, float& b)
{
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
}
bool CHiddenButton::GetIsClicked()
{
	return this->isClicked;
}