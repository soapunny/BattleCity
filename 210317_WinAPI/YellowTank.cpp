#pragma once
#include "YellowTank.h"
#include "MissileManager.h"
#include "CommonFunction.h"

HRESULT YellowTank::Init()
{
	pos.x = BATTLE_SCENE_END_X - 50;
	pos.y = BATTLE_SCENE_END_Y - 25;
	size = 48;
	powerLevel = 1;
	name = "��ũ" + to_string(tankCnt++);
	moveSpeed = 5;
	shape = GetRectToCenter(pos.x, pos.y, size, size);
	playerType = PLAYER_TYPE::FIRST_PLAYER;

	curFrame.x = 0;
	curFrame.y = 5;
	maxFrame.x = 8;
	maxFrame.y = 6;

	image = ImageManager::GetSingleton()->FindImage("Tank");

	// ����
	barrelSize = size/2;
	barrelAngle = PI / 2;
	barrelEnd.x = pos.x;
	barrelEnd.y = pos.y + barrelSize;

	// �̻���
	missileManager = new MissileManager();
	missileManager->Init(playerType);

	isAlive = false;
	moveTimer = 0.0f;
	randMoveTimer = 0.0f;
	fireTimer = 0.0f;

	return S_OK;
}
