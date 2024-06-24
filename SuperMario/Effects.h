#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"

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
	virtual void OnNoCollision(DWORD dt);
	virtual int IsCollidable() { return 1; };
public:
	CEffects(float x, float y);
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	int IsBlocking() { return 0; };
};