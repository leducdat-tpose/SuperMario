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

	void returnEffect(CEffects* effect)
	{
		effect->reset();
		effects.push_back(effect);
	}

	void startInit()
	{
		if (isInit == true) return;
		for (int i = 0; i < 10; i++)
		{
			CPlayScene* playScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
			DebugOut(L"[INFO]Creating new Effect from ObjectPool number %d.\n", i);
			CEffects* effect = new CEffects;
			effects.push_back(effect);
			playScene->AddObject(effect);
		}
		isInit = true;
	}
};
typedef CObjectPool* LPOBJECTPOOL;