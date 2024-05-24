#pragma once
#include <vector>
#include "PlayScene.h"

using namespace std;

class CPlayer
{
	LPGAME game;
	LPSCENE scene;
	CMario* mario;

	//information of player such as point, gadget own or archive
	string information;
	int score;
	int time;
	vector<LPGAMEOBJECT> gadget;
public:
	CPlayer(LPGAME game, LPSCENE scene);
	~CPlayer();

	void Update(DWORD dt);
};