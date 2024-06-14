#include "Teleport.h"

void CTeleport::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - TELEPORT_BBOX_WIDTH / 2;
	t = y - TELEPORT_BBOX_HEIGHT / 2;
	r = l + TELEPORT_BBOX_WIDTH;
	b = t + TELEPORT_BBOX_HEIGHT;
}
void CTeleport::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

}
void CTeleport::Render()
{
	RenderBoundingBox();
}
void CTeleport::OnCollisionWith(LPCOLLISIONEVENT e)
{

}

void CTeleport::Teleport(float marioPosX, float marioPosY)
{
	int idScene = CGame::GetInstance()->GetCurrentScene()->GetId();
	CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
	switch (idScene)
	{
	case SCENE_1:
		if (2248 < marioPosX && marioPosX < 2280 && 72 < marioPosY && marioPosY < 104)
			mario->SetPosition(2104.0f, 480.0f);
		else if(2312 < marioPosX && marioPosX < 2344 && 448 < marioPosY && marioPosY < 472)
			mario->SetPosition(2328.0f, 352.0f);
		break;
	}
}