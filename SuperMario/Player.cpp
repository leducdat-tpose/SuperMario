#include "Player.h"
#include "DataManager.h"

CPlayer::CPlayer(float x, float y):CGameObject(x,y)
{
	information = "";
	sprite = CSprites::GetInstance()->Get(ID_SPRITE_PLAYER_STATUS);
	id_world = 0;
	coin = 0;
	life = 0;
	point = 0;
	time = 0;
}

CPlayer::~CPlayer(){}

void CPlayer::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	UpdateIndex();
	UpdatePosition();
	string point_str = to_string(point);
	while (point_str.length() < 7) point_str = "0" + point_str;

	string time_str = to_string(time);
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
	LPTEXTURE hud = CTextures::GetInstance()->Get(ID_TEX_MAP);
	sprite->Draw(x, y);
	RECT rect;
	SetRect(&rect, 0, 175, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (game->GetFont() != NULL)
		game->GetFont()->DrawTextA(game->GetSpriteHandler(), information.c_str(), -1, &rect, DT_LEFT, D3DXCOLOR(255 / 255, 255 / 255, 255 / 255, 100));
	//D3DXVECTOR3 p(x, y, 0);

	//float cx, cy;
	//CGame::GetInstance()->GetCamPos(cx, cy);

	//CGame::GetInstance()->Draw(x - cx, y - cy, hud, &rect, 0.5, 1, 1);
}

void CPlayer::UpdateIndex()
{
	CDataManager::getInstance()->GetData(id_world, coin, life, point, time);
}

void CPlayer::UpdatePosition()
{
	float cx, cy;
	game->GetCamPos(cx, cy);
	//x = 150 + cx - (int)cx % 16;
	//y = 185 + cy - (int)cy % 16;
	x = 150 + cx;
	y = 185 + cy;
}