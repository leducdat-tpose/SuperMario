#pragma once
#include "GameObject.h"
#include "PlayScene.h"
#include "Animation.h"
#include "Animations.h"

#include "debug.h"

#include "HitBox.h"

#define MARIO_WALKING_SPEED		0.1f
#define MARIO_RUNNING_SPEED		0.2f

#define MARIO_ACCEL_WALK_X	0.0002f
#define MARIO_ACCEL_RUN_X	0.00025f
#define MARIO_DECEL_RUN_X	36.0f // deceleration on x

#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_RUN_SPEED_Y	0.6f
#define MARIO_FLY_SPEED_Y 0.4f

#define MARIO_GRAVITY			0.002f
#define MARIO_FLY_GRAVITY		0.001f

#define MARIO_JUMP_DEFLECT_SPEED  0.4f

#define MARIO_STATE_DIE				-10
#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING_RIGHT	100
#define MARIO_STATE_WALKING_LEFT	200

#define MARIO_STATE_JUMP			300
#define MARIO_STATE_RELEASE_JUMP    301

#define MARIO_STATE_RUNNING_RIGHT	400
#define MARIO_STATE_RUNNING_LEFT	500

#define MARIO_STATE_SIT				600
#define MARIO_STATE_SIT_RELEASE		601

#define MARIO_STATE_ATTACK			700

#define MARIO_STATE_KICK			800

#define MARIO_STATE_FLY				900

#define MARIO_ATTACK_TIME			600
#define MARIO_KICK_ANIMATION_TIME	300
#define MARIO_TRANSFORM_RACCOON_TIME 350
#define MARIO_TRANSFORM_TIME		1200
#define MARIO_SWITCH_SCENE_OVERWORLD_TIME 3000

#pragma region ANIMATION_ID

#define ID_ANI_MARIO_IDLE_RIGHT 400
#define ID_ANI_MARIO_IDLE_LEFT 401

#define ID_ANI_MARIO_WALKING_RIGHT 500
#define ID_ANI_MARIO_WALKING_LEFT 501

#define ID_ANI_MARIO_RUNNING_RIGHT 600
#define ID_ANI_MARIO_RUNNING_LEFT 601

#define ID_ANI_MARIO_JUMP_WALK_RIGHT 700
#define ID_ANI_MARIO_JUMP_WALK_LEFT 701

#define ID_ANI_MARIO_JUMP_RUN_RIGHT 800
#define ID_ANI_MARIO_JUMP_RUN_LEFT 801

#define ID_ANI_MARIO_SIT_RIGHT 900
#define ID_ANI_MARIO_SIT_LEFT 901

#define ID_ANI_MARIO_BRACE_RIGHT 1000
#define ID_ANI_MARIO_BRACE_LEFT 1001

#define ID_ANI_MARIO_DIE 999

// SMALL MARIO
#define ID_ANI_MARIO_SMALL_IDLE_RIGHT 1100
#define ID_ANI_MARIO_SMALL_IDLE_LEFT 1102

#define ID_ANI_MARIO_SMALL_WALKING_RIGHT 1200
#define ID_ANI_MARIO_SMALL_WALKING_LEFT 1201

#define ID_ANI_MARIO_SMALL_RUNNING_RIGHT 1300
#define ID_ANI_MARIO_SMALL_RUNNING_LEFT 1301

#define ID_ANI_MARIO_SMALL_BRACE_RIGHT 1400
#define ID_ANI_MARIO_SMALL_BRACE_LEFT 1401

#define ID_ANI_MARIO_SMALL_JUMP_WALK_RIGHT 1500
#define ID_ANI_MARIO_SMALL_JUMP_WALK_LEFT 1501

#define ID_ANI_MARIO_SMALL_JUMP_RUN_RIGHT 1600
#define ID_ANI_MARIO_SMALL_JUMP_RUN_LEFT 1601

//RACCOON MARIO
#define ID_ANI_MARIO_RACCOON_IDLE_RIGHT 1700
#define ID_ANI_MARIO_RACCOON_IDLE_LEFT 1701

#define ID_ANI_MARIO_RACCOON_WALKING_RIGHT 1800
#define ID_ANI_MARIO_RACCOON_WALKING_LEFT 1801

#define ID_ANI_MARIO_RACCOON_RUNNING_RIGHT 1900
#define ID_ANI_MARIO_RACCOON_RUNNING_LEFT 1901

#define ID_ANI_MARIO_RACCOON_JUMP_WALK_RIGHT 2000
#define ID_ANI_MARIO_RACCOON_JUMP_WALK_LEFT 2001

#define ID_ANI_MARIO_RACCOON_JUMP_RUN_RIGHT 2100
#define ID_ANI_MARIO_RACCOON_JUMP_RUN_LEFT 2101

#define ID_ANI_MARIO_RACCOON_SIT_RIGHT 2200
#define ID_ANI_MARIO_RACCOON_SIT_LEFT 2201

#define ID_ANI_MARIO_RACCOON_BRACE_RIGHT 2300
#define ID_ANI_MARIO_RACCOON_BRACE_LEFT 2301

#define ID_ANI_MARIO_RACCOON_ATTACK_RIGHT 2400
#define ID_ANI_MARIO_RACCOON_ATTACK_LEFT 2401

//MARIO KICK KOOPAS
//SMALL_MARIO
#define ID_ANI_MARIO_SMALL_KICK_RIGHT	2500
#define ID_ANI_MARIO_SMALL_KICK_LEFT	2501

//BIG_MARIO
#define ID_ANI_MARIO_KICK_RIGHT			2600
#define ID_ANI_MARIO_KICK_LEFT			2601

//RACCOON_MARIO
#define ID_ANI_MARIO_RACCOON_KICK_RIGHT	2700
#define ID_ANI_MARIO_RACCOON_KICK_LEFT	2701

#define ID_ANI_MARIO_RACCOON_FLY_RIGHT	2800
#define ID_ANI_MARIO_RACCOON_FLY_LEFT	2801

#define ID_ANI_MARIO_RACCOON_FLY_FAST_RIGHT	2900
#define ID_ANI_MARIO_RACCOON_FLY_FAST_LEFT	2901

#define ID_ANI_MARIO_INTRO_SCENE_SMALL 3000

#define ID_ANI_MARIO_TRANSFORM_SMALL_BIG_RIGHT 3100
#define ID_ANI_MARIO_TRANSFORM_SMALL_BIG_LEFT 3101

#define ID_ANI_MARIO_TRANSFORM_BIG_SMALL_RIGHT 3200
#define ID_ANI_MARIO_TRANSFORM_BIG_SMALL_LEFT 3201
//MARIO_PICK_UP_KOOPAS
//MARIO_BIG
#define ID_ANI_MARIO_PICK_UP_RIGHT	3300
#define ID_ANI_MARIO_PICK_UP_LEFT	3301
#define ID_ANI_MARIO_PICK_UP_IDLE_RIGHT 3302
#define ID_ANI_MARIO_PICK_UP_IDLE_LEFT 3303
//MARIO_SMALL
#define ID_ANI_MARIO_SMALL_PICK_UP_RIGHT	3400
#define ID_ANI_MARIO_SMALL_PICK_UP_LEFT		3401
#define ID_ANI_MARIO_SMALL_PICK_UP_IDLE_RIGHT 3402
#define ID_ANI_MARIO_SMALL_PICK_UP_IDLE_LEFT 3403
//MARIO_RACCOON
#define ID_ANI_MARIO_RACCOON_PICK_UP_RIGHT	3500
#define ID_ANI_MARIO_RACCOON_PICK_UP_LEFT	3501
#define ID_ANI_MARIO_RACCOON_PICK_UP_IDLE_RIGHT 3502
#define ID_ANI_MARIO_RACCOON_PICK_UP_IDLE_LEFT 3503


#pragma endregion

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_RACCOON	3

#define MARIO_BIG_BBOX_WIDTH  14
#define MARIO_BIG_BBOX_HEIGHT 24
#define MARIO_BIG_SITTING_BBOX_WIDTH  14
#define MARIO_BIG_SITTING_BBOX_HEIGHT 16

#define MARIO_SIT_HEIGHT_ADJUST ((MARIO_BIG_BBOX_HEIGHT-MARIO_BIG_SITTING_BBOX_HEIGHT)/2)

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 12


#define MARIO_UNTOUCHABLE_TIME 2500
#define MARIO_FLY_COOLDOWN_TIME 800 //Difference with allow fly time, use to make player has to spam Jump button to continue fly
#define MARIO_ALLOW_FLY_TIME 100 //Time to allow Mario can get in his fly form

class CMario : public CGameObject
{
	LPGAMEOBJECT hitbox;
	LPGAMEOBJECT heldKoopas;
	BOOLEAN isFinishScene;
	BOOLEAN isInSecret;
	BOOLEAN isSitting;
	//Only when level is Racoon
	BOOLEAN isAttack;
	//For attack only once when ever click A button
	BOOLEAN attackDone;
	BOOLEAN isKick;
	BOOLEAN isFly;
	BOOLEAN allowFly;
	BOOLEAN inTransform;
	//To render Mario's fly animations
	int transformSmallToBig;
	bool aniFly;
	float maxVx;
	float ax;				// acceleration on x 
	float ay;				// acceleration on y 
	//Use to make mario stop animation when hit collide forward
	float preX;
	int autoMoving;
	int level;
	int untouchable;
	ULONGLONG untouchable_start;
	ULONGLONG attack_start;
	ULONGLONG kick_start;
	ULONGLONG allow_fly_start;
	ULONGLONG fly_cooldown_start;
	ULONGLONG transform_start;
	ULONGLONG switchscene_start;

	BOOLEAN isOnPlatform;
	BOOLEAN isNextToWall;
	int coin;
	bool isInIntroScene;

	void OnCollisionWithGoomba(LPCOLLISIONEVENT e);
	void OnCollisionWithCoin(LPCOLLISIONEVENT e);
	void OnCollisionWithPortal(LPCOLLISIONEVENT e);
	void OnCollisionWithKoopas(LPCOLLISIONEVENT e);
	void OnCollisionWithMushroom(LPCOLLISIONEVENT e);
	void OnCollisionWithLuckybox(LPCOLLISIONEVENT e);
	void OnCollisionWithSuperLeaf(LPCOLLISIONEVENT e);
	void OnCollisionWithFireBall(LPCOLLISIONEVENT e);
	void OnCollisionWithPiranhaPlant(LPCOLLISIONEVENT e);
	void OnCollisionWithTeleport(LPCOLLISIONEVENT e);
	void OnCollisionWithHiddenButton(LPCOLLISIONEVENT e);
	void OnCollisionWithRandomGadget(LPCOLLISIONEVENT e);

	int GetAniIdBig();
	int GetAniIdSmall();
	int GetAniIdRaccoon();

public:
	bool keyRunDown;
	bool keyJumpDown;
	CMario(float x, float y, bool isInIntroScene = false) : CGameObject(x, y)
	{
		heldKoopas = nullptr;
		hitbox = nullptr;
		isSitting = false;
		isAttack = false;
		preX = 0;
		enable = true;
		isInSecret = false;
		attackDone = false;
		isFinishScene = false;
		isKick = false;
		isFly = false;
		allowFly = false;
		maxVx = 0.0f;
		ax = 0.0f;
		autoMoving = 0;
		keyRunDown = false;
		keyJumpDown = false;
		ay = MARIO_GRAVITY;
		level = MARIO_LEVEL_SMALL;
		untouchable = 0;
		untouchable_start = -1;
		attack_start = -1;
		kick_start = -1;
		allow_fly_start = -1;
		fly_cooldown_start = 0;
		transform_start = -1;
		transformSmallToBig = 0;
		switchscene_start = -1;
		coin = 0;
		isOnPlatform = false;
		isNextToWall = false;
		inTransform = false;
		aniFly = false;
		this->isInIntroScene = isInIntroScene;
		if (this->isInIntroScene == true) this->ay = 0;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();
	void SetState(int state);
	int GetLevel() const { return level; }
	int IsCollidable()
	{
		return (state != MARIO_STATE_DIE);
	}

	int IsBlocking() { return (state != MARIO_STATE_DIE && untouchable == 0); }

	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	void SetLevel(int l);
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }

	void DamagedMario();
	void SetAttack(BOOLEAN isAttack) { this->isAttack = isAttack; }
	void SetFly(BOOLEAN isFly) { this->isFly = isFly; }
	void StartFly();
	void StartAttack();
	void MarioDecelerate();
	void SetAttackDone(BOOLEAN attackDone) { this->attackDone = attackDone; }
	void SetInIntroScene(BOOLEAN isInIntroScene){ 
		this->isInIntroScene = isInIntroScene;
		if(this->isInIntroScene == true) this->ay = 0;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void AddHitBox();
	void StopKick();
	void CollectCoin();
	void HoldKoopas();
	void ReleaseKoopas();
	void StartAllowFly();
	void StartTransform();
	void CheckingNextToWall();
	void AllowToFly();
	void Fly();
	LPGAMEOBJECT GetHeldKoopas() const { return heldKoopas; }
	BOOLEAN GetIsOnPlatform() const { return isOnPlatform; }
	BOOLEAN GetIsFly() const { return isFly; }
	BOOLEAN GetAllowFly() const { return allowFly; }
	BOOLEAN GetAttackDone() const { return attackDone; }
	bool GetAniFly() const { return aniFly; }
	BOOLEAN GetIsInSecretRoom() const { return isInSecret; }
	float GetSpeed() const { return vx; }
};