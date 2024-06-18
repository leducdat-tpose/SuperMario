#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "AssetIDs.h"
#include "PlayScene.h"

#define HIDDENBUTTON_UNENABLE_TIME 4000
#define ID_ANI_HIDDENBUTTON 19000
#define ID_ANI_HIDDENBUTTON_CLICKED 19001
#define HIDDENBUTTON_WIDTH 16
#define HIDDENBUTTON_BBOX_WIDTH 16
#define HIDDENBUTTON_BBOX_HEIGHT 16

class CHiddenButton : public CGameObject {
private:
	bool isClicked;
	ULONGLONG unenable_start;
public:
	CHiddenButton(float x, float y) : CGameObject(x, y) {
		this->enable = true;
		this->isClicked = false;
		unenable_start = -1;
	}
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	int IsBlocking() { return 0; }
	void SetIsClicked(bool isClicked);
	bool GetIsClicked();
};