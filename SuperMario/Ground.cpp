#include "Ground.h"

void CGround::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_GROUND)->Render(x, y);
}

void CGround::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	
}