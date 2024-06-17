#include "Brick.h"

void CBrick::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	if (type == TYPE_GOLD_BRICK)
	{
		CHiddenButton* hiddenbutton = (CHiddenButton*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetHiddenButton();
		if (hiddenbutton->GetIsClicked() == true)
			return;
		animations->Get(ID_ANI_GOLD_BRICK)->Render(x, y);
	}
	else
		animations->Get(ID_ANI_BRICK)->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	CHiddenButton* hiddenbutton = (CHiddenButton*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetHiddenButton();
	if (hiddenbutton->GetIsClicked() == true)
		return;
	l = x - BRICK_BBOX_WIDTH / 2;
	t = y - BRICK_BBOX_HEIGHT / 2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}