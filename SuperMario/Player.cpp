#include "Player.h"
#include "DataManager.h"

CPlayer::CPlayer(float x, float y):CGameObject(x,y)
{
	information = "";
	sprite = sprites->Get(ID_SPRITE_PLAYER_STATUS);
	pauseGameSprite = sprites->Get(ID_SPRITE_PAUSE_GAME);
	id_world = 0;
	coin = 0;
	life = 0;
	point = 0;
	time = 0;
	posHudX = x;
	posHudY = y;
	marioSpeed_sub = (float)(MARIO_RUNNING_SPEED - MARIO_WALKING_SPEED) / 8;
	for (int i = 1; i < 9; i++)
	{
		int idMarioSpeed = ID_SPRITE_MARIO_SPEED + i * 10;
		marioSpeed.push_back(sprites->Get(idMarioSpeed));
	}
	UpdateIndex();
	for (int i = 0; i < 3; i++)
	{
		int idGadget = gadgetsList[i];
		gadgetsSprite.push_back(sprites->Get(ID_SPRITE_GADGET + idGadget));
	}
}

CPlayer::~CPlayer(){}

void CPlayer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	UpdateIndex();
	int remainTime = 0;
	if (mario->GetState() != MARIO_STATE_DIE && playScene->GetId() != SCENE_INTRO) time += dt;
	remainTime = DEFAULT_TIME_PLAY - time / CLOCKS_PER_SEC;
	CDataManager::getInstance()->UpdatePlayTime(time / CLOCKS_PER_SEC);
	if (remainTime <= 0)
	{
		remainTime = 0;
		mario->SetState(MARIO_STATE_DIE);
	}
	string point_str = to_string(point);
	while (point_str.length() < 7) point_str = "0" + point_str;

	string time_str = to_string(remainTime);
	while (time_str.length() < 3) time_str = "0" + time_str;

	string world_str = to_string(id_world);

	string life_str = to_string(life);

	string coin_str = to_string(coin);
	while (coin_str.length() < 2) coin_str = "0" + coin_str;

	information = "                         "+ world_str +"                             " + coin_str + "\n";
	information += "                         "+life_str +" " + point_str + "       " + time_str + "\n";
	CGameObject::Update(dt, coObjects);
}

void CPlayer::Render()
{
	
	sprite->Draw(posHudX, posHudY, 1.0f);
	if (game->GetIsPauseGame() == 1) pauseGameSprite->Draw((SCREEN_WIDTH - 20)/2, posHudY - 120, 1.0f);
	int speedIndex = 0;
	speedIndex = (int)((mario->GetSpeed() - MARIO_WALKING_SPEED) / marioSpeed_sub) - 1;
	if (speedIndex < 0) speedIndex = 0;
	marioSpeed[speedIndex]->Draw(posHudX - 31, posHudY - 4, 1.0f);
	for (int i = 0; i < 3; i++)
	{
		gadgetsSprite[i]->Draw(posHudX + 52 + i * 26, posHudY, 1.0f);
	}
	RECT rect;
	SetRect(&rect, 0, 175, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (game->GetFont() != NULL)
		game->GetFont()->DrawTextA(game->GetSpriteHandler(), information.c_str(), -1, &rect, DT_LEFT, D3DXCOLOR(255 / 255, 255 / 255, 255 / 255, 100));
}

void CPlayer::UpdateIndex()
{
	CDataManager::getInstance()->GetData(id_world, coin, life, point, gadgetsList);
	this->changeAlert = CDataManager::getInstance()->changeAlert;
	if (changeAlert == 1)
	{
		gadgetsSprite.clear();
		for (int i = 0; i < 3; i++)
		{
			int idGadget = gadgetsList[i];
			gadgetsSprite.push_back(sprites->Get(ID_SPRITE_GADGET + idGadget));
		}
		CDataManager::getInstance()->changeAlert = 0;
	}
}