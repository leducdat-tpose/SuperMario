#include "TriggerButton.h"

CTriggerButton::CTriggerButton(float x, float y): CGameObject(x,y)
{
	isClicked = false;
	enable = true;
	this->ay = 0;
}

void CTriggerButton::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (!enable) return;
	left = x - TRIGGER_BUTTON_BBOX_WIDTH / 2;
	top = y - TRIGGER_BUTTON_BBOX_HEIGHT / 2;
	right = left + TRIGGER_BUTTON_BBOX_WIDTH;
	bottom = top + TRIGGER_BUTTON_BBOX_HEIGHT;
}

void CTriggerButton::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!enable) return;
	vy += ay * dt;
}

void CTriggerButton::CTriggerButton::Render()
{
	if (!enable) return;
	int aniId = ID_ANI_TRIGGER_BUTTON;
	if (isClicked) ID_ANI_TRIGGER_BUTTON_CLICKED;
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CTriggerButton::OnNoCollision(DWORD dt)
{
	if (!enable) return;
	x += vx * dt;
	y += vy * dt;
}

void CTriggerButton::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CTriggerButton*>(e->obj)) return;
}