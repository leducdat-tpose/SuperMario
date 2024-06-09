#include "HitBox.h"

void CHitBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (!active) return;
	l = x - bboxWidth / 2;
	t = y - bboxHeight / 2;
	r = l + bboxWidth;
	b = t + bboxHeight;
}

void CHitBox::Update(DWORD dt)
{
	//Code to make the Hit box move, then collide with others object(e.g: goomba, koopas, etc.)
}