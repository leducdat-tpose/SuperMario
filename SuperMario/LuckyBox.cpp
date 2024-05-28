#include "LuckyBox.h"

void CLuckyBox::Render()
{
	int aniId = ID_ANI_LUCKYBOX;
	if (isCollected)	aniId = ID_ANI_LUCKYBOX_COLLECTED;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CLuckyBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - LUCKYBOX_BBOX_WIDTH / 2;
	t = y - LUCKYBOX_BBOX_HEIGHT / 2;
	r = l + LUCKYBOX_BBOX_WIDTH;
	b = t + LUCKYBOX_BBOX_HEIGHT;
}
void CLuckyBox::SetIsCollected(bool isCollected) {
	this->isCollected = isCollected;
}