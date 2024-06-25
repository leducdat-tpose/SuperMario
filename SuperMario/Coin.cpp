#include "Coin.h"
#include "ObjectPool.h"

CCoin::CCoin(float x, float y, bool fromLuckyBox) : CGameObject(x, y)
{
	this->fromLuckyBox = fromLuckyBox;
	this->ax = 0;
	if (fromLuckyBox)
	{
		this->ay = -COIN_GRAVITY;
		fly_start = GetTickCount64();
	}
	else {
		this->ay = 0;
		this->fly_start = -1;
	}
}

void CCoin::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(ID_ANI_COIN)->Render(x, y);

	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - COIN_BBOX_WIDTH / 2;
	t = y - COIN_BBOX_HEIGHT / 2;
	r = l + COIN_BBOX_WIDTH;
	b = t + COIN_BBOX_HEIGHT;
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy = ay * dt;
	vx = ax * dt;
	if (GetTickCount64() - fly_start > TIME_FLY_UP && fromLuckyBox)
	{
		ay = COIN_GRAVITY;
		fly_start = -1;
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CCoin::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CCoin::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (dynamic_cast<CLuckyBox*>(e->obj))
		OnCollisionWithLuckybox(e);
}
void CCoin::OnCollisionWithLuckybox(LPCOLLISIONEVENT e)
{
	if (e->ny < 0)
	{
		CObjectPool::getInstance()->getEffect()->SetValue(this->x, this->y, EFFECT_TYPE_POINT, 100);
		this->Delete();
	}
}