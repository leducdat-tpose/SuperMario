#pragma once
#include <string>
#include <iostream>
#include <list>

#include "Effects.h"

class CObjectPool
{
private:
	list<CEffects*> effects;

	static CObjectPool* instance;
	CObjectPool(){}
public:
	static CObjectPool* getInstance()
	{
		if (instance == 0)
		{
			instance = new CObjectPool;
		}
		return instance;
	}
	CEffects* getEffect()
	{
		if (effects.empty())
		{
			cout << "Don't have any effect left in ObjectPool" << endl;
			return nullptr;
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