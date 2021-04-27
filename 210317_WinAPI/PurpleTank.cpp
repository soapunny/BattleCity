#include "PurpleTank.h"
#include "MissileManager.h"
#include "CommonFunction.h"

HRESULT PurpleTank::Init()
{
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y;
	size = 64;
	powerLevel = 1;
	name = "탱크";
	moveSpeed = 5;
	shape = GetRectToCenter(pos.x, pos.y, size, size);
	playerType = PLAYER_TYPE::FIRST_PLAYER;

	curFrame.x = 0;
	curFrame.y = 1;
	maxFrame.x = 8;
	maxFrame.y = 6;

	image = ImageManager::GetSingleton()->FindImage("Tank");

	// 포신
	barrelSize = size / 2;
	barrelAngle = PI / 2;
	barrelEnd.x = pos.x;
	barrelEnd.y = pos.y + barrelSize;

	// 미사일
	missileManager = new MissileManager();
	missileManager->Init(playerType);

	isAlive = false;
	moveTimer = 0.0f;

	return S_OK;
}
