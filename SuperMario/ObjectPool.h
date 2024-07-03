#pragma once
#include <string>
#include <iostream>
#include <list>

#include "debug.h"
#include "Effects.h"
#include "PlayScene.h"

class CObjectPool
{
private:
	list<CEffects*> effects;
	bool isInit;
	static CObjectPool* instance;
	CObjectPool(){
		isInit = false;
	}
	~CObjectPool()
	{
		for (auto it = effects.begin(); it != effects.end(); ++it) {
			delete* it;
		}
		Unload();
	}
public:
	static CObjectPool* getInstance()
	{
		if (instance == NULL)
		{
			DebugOut(L"[INFO]Creating ObjectPool.\n");
			instance = new CObjectPool;
		}
		return instance;
	}

	static void Release()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	CEffects* getEffect()
	{
		//if (effects.empty())
		//{
		//	DebugOut(L"[INFO]Creating new Effect from ObjectPool.\n");
		//	CPlayScene* playScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
		//	CEffects* effect = new CEffects;
		//	//At this point, PoolObject may crash game when ever this effect is create in the previous scene
		//	//This effect still exist in the next scene
		//	//To fix, refresh objectPool when change scene, do it later
		//	playScene->AddObject(effect);
		//	return effect;
		//}
		//else
		//{
		//	CEffects* effect = effects.front();
		//	effects.pop_front();
		//	return effect;
		//}
		//Simply to queue
		CEffects* effect = effects.front();
		effects.pop_front();
		effects.push_back(effect);
		return effect;
	}

	void getEffectBreakBrick(float objX, float objY)
	{
		for (int i = 0; i < 4; i++)
		{
			CEffects* effect = effects.front();
			effects.pop_front();
			effects.push_back(effect);
			effect->SetValue(objX, objY, EFFECT_TYPE_BREAK_BRICK, 0);
		}
	}

	void returnEffect(CEffects* effect)
	{
		effect->reset();
		effects.push_back(effect);
	}

	void startInit()
	{
		if (isInit == true) return;
		for (int i = 0; i < 12; i++)
		{
			CPlayScene* playScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
			CEffects* effect = new CEffects;
			effects.push_back(effect);
			playScene->AddObject(effect);
		}
		isInit = true;
	}

	void Unload()
	{
		isInit = false;
		effects.clear();
	}
};
typedef CObjectPool* LPOBJECTPOOL;