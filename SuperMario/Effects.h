#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

#define EFFECT_EXIST_TIME 350
#define EFFECT_GRAVITY 0.002f//This gravity is use for collecting point
#define EFFECT_CRUMB_GRAVITY 0.008f

#define EFFECT_TYPE_NONE 0
#define EFFECT_TYPE_POINT 100
#define EFFECT_TYPE_KABOOM 200
#define EFFECT_TYPE_BREAK_BRICK 300
#define EFFECT_TYPE_1UP 400
#define EFFECT_TYPE_TRANSFORM 500
#define EFFECT_TYPE_SWITCH_SCENE 600
#define EFFECT_TYPE_OTHER 700

#define ID_ANI_EFFECT 20000

#define ID_ANI_EFFECT_100_POINT (ID_ANI_EFFECT + 10)
#define ID_ANI_EFFECT_200_POINT (ID_ANI_EFFECT + 20)
#define ID_ANI_EFFECT_400_POINT (ID_ANI_EFFECT + 30)
#define ID_ANI_EFFECT_800_POINT (ID_ANI_EFFECT + 40)

#define ID_ANI_EFFECT_1000_POINT (ID_ANI_EFFECT + 50)
#define ID_ANI_EFFECT_2000_POINT (ID_ANI_EFFECT + 60)
#define ID_ANI_EFFECT_4000_POINT (ID_ANI_EFFECT + 70)
#define ID_ANI_EFFECT_8000_POINT (ID_ANI_EFFECT + 80)

#define ID_ANI_EFFECT_KABOOM (ID_ANI_EFFECT + 90)//e.g koopas hit goomba 
#define ID_ANI_EFFECT_BRICK_CRUMB (ID_ANI_EFFECT + 100)

#define ID_ANI_EFFECT_1UP (ID_ANI_EFFECT + 110)

#define ID_ANI_EFFECT_TRANSFORM (ID_ANI_EFFECT + 120)

class CEffects : public CGameObject {
private:
protected:
	float alphaSwitchScene;
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
	void SetValue(float x, float y, int type, int point, float ax = 0.0f, float ay = -EFFECT_GRAVITY);
};