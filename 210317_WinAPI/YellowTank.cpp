#include "YellowTank.h"
#include "MissileManager.h"
#include "CommonFunction.h"

HRESULT YellowTank::Init()
{
	pos.x = TILESIZE * TILE_X / 2;
	pos.y = TILESIZE * TILE_Y / 2;
	size = 50;
	powerLevel = 1;
	name = "탱크" + to_string(tankCnt++);
	moveSpeed = 5;
	shape = GetRectToCenter(pos.x, pos.y, size, size);
	playerType = PLAYER_TYPE::FIRST_PLAYER;

	curFrame.x = 0;
	curFrame.y = 5;
	maxFrame.x = 8;
	maxFrame.y = 6;

	image = ImageManager::GetSingleton()->FindImage("Tank");

	// 포신
	barrelSize = size/2;
	barrelAngle = PI / 2;
	barrelEnd.x = pos.x;
	barrelEnd.y = pos.y + barrelSize;

	// 미사일
	missileManager = new MissileManager();
	missileManager->Init(playerType);

	isAlive = false;
	moveTimer = 0.0f;
	randMoveTimer = 0.0f;
	fireTimer = 0.0f;

	return S_OK;
}
