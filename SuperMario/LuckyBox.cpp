#include "LuckyBox.h"

void CLuckyBox::Render()
{
	int aniId = ID_ANI_LUCKYBOX;
	if (isCollected)
	{
		aniId = ID_ANI_LUCKYBOX_COLLECTED;
	}
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	//RenderBoundingBox();
}

void CLuckyBox::Update(DWORD dt)
{
}

void CLuckyBox::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case LUCKYBOX_NORNMAL_STATE:
		break;
	case LUCKYBOX_COLLECTED_STATE_UP:
		y -= LUCKYBOX_MOVING_Y;
		break;
	case LUCKYBOX_COLLECTED_STATE_DOWN:
		y += LUCKYBOX_MOVING_Y;
		break;
	default:
		break;
	}
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
	upDown_start = GetTickCount64();
}

