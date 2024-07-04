#include "Player.h"
#include "DataManager.h"

CPlayer::CPlayer(float x, float y):CGameObject(x,y)
{
	information = "";
	sprite = CSprites::GetInstance()->Get(ID_SPRITE_PLAYER_STATUS);
	id_scene = 0;
	coin = 0;
	life = 0;
	point = 0;
	time = 0;
}

CPlayer::~CPlayer(){}

void CPlayer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	UpdateIndex();
	string point_str = to_string(point);
	while (point_str.length() < 7) point_str = "0" + point_str;

	string time_str = to_string(time);
	while (time_str.length() < 3) time_str = "0" + time_str;

	string scene_str = to_string(id_scene);

	string life_str = to_string(life);

	string coin_str = to_string(coin);
	while (coin_str.length() < 2) coin_str = "0" + coin_str;

	information = "                         "+scene_str +"                             " + coin_str + "\n";
	information += "                         "+life_str +" " + point_str + "       " + time_str + "\n";
	CGameObject::Update(dt, coObjects);
}

void CPlayer::Render()
{
	sprite->Draw(x, y);
	RECT rect;
	SetRect(&rect, 0, 175, SCREEN_WIDTH, 240);
	if (game->GetFont() != NULL)
		game->GetFont()->DrawTextA(game->GetSpriteHandler(), information.c_str(), -1, &rect, DT_LEFT, D3DXCOLOR(255 / 255, 255 / 255, 255 / 255, 100));
}

void CPlayer::UpdateIndex()
{
	CDataManager::getInstance()->GetData(id_scene, coin, life, point, time);
}
