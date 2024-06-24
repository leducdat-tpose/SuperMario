#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "ObjectPool.h"

#define EFFECT_EXIST_TIME 500

#define EFFECT_TYPE_NONE 0
#define EFFECT_TYPE_POINT 100
#define EFFECT_TYPE_OTHER 200

#define ID_ANI_EFFECT 20000

#define ID_ANI_EFFECT_100_POINT (ID_ANI_EFFECT + 10)
#define ID_ANI_EFFECT_200_POINT (ID_ANI_EFFECT + 20)
#define ID_ANI_EFFECT_400_POINT (ID_ANI_EFFECT + 30)
#define ID_ANI_EFFECT_800_POINT (ID_ANI_EFFECT + 40)

#define ID_ANI_EFFECT_1000_POINT (ID_ANI_EFFECT + 50)
#define ID_ANI_EFFECT_2000_POINT (ID_ANI_EFFECT + 60)
#define ID_ANI_EFFECT_4000_POINT (ID_ANI_EFFECT + 70)
#define ID_ANI_EFFECT_8000_POINT (ID_ANI_EFFECT + 80)

class CEffects : public CGameObject {
private:
protected:
	float ax;
	float ay;
	int type;
	int point;
	ULONGLONG existStart;
	virtual void OnNoCollision(DWORD dt);
	virtual int IsCollidable() { return 1; };
public:
	CEffects();
	CEffects(float x, float y, int type, int point = 0);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	int IsBlocking() { return 0; };
	void DisplayPoint(int point);
	void GetBoundingBox(float& l, float& t, float& r, float& b){}
	void reset();
	void SetValue(float x, float y, int type, int point, float ax, float ay)
	{
		this->x = x;
		this->y = y;
		this->type = type;
		this->point = point;
		this->ax = ax;
		this->ay = ay;
		if (this->type != EFFECT_TYPE_NONE) 
		{
			existStart = GetTickCount64();
		}
	}
};