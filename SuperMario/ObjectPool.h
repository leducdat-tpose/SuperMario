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

	static CObjectPool* instance;
	CObjectPool(){}
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
		if (effects.empty())
		{
			DebugOut(L"[INFO]Creating new Effect from ObjectPool.\n");
			CPlayScene* playScene = (LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene();
			CEffects* effect = new CEffects;
			//At this point, PoolObject may crash game when ever this effect is create in the previous scene
			//This effect still exist in the next scene
			//To fix, refresh objectPool when change scene, do it later
			playScene->AddObject(effect);
			return effect;
		}
		else
		{
			CEffects* effect = effects.front();
			effects.pop_front();
			return effect;
		}
	}

	void returnEffect(CEffects* effect)
	{
		effect->reset();
		effects.push_back(effect);
	}
};
typedef CObjectPool* LPOBJECTPOOL;