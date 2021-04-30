#include "CommonFunction.h"
#include "Tank.h"
#include "MissileManager.h"
#include "Image.h"


int Tank::tankCnt = 0;

HRESULT Tank::Init()
{
	pos.x = TILESIZE*TILE_X / 2;
	pos.y = TILESIZE * TILE_Y / 2;
	size = 64;
	powerLevel = 1;
	name = "탱크";
	moveSpeed = 1;
	shape = GetRectToCenter(pos.x, pos.y, size, size);
	playerType = PLAYER_TYPE::FIRST_PLAYER;

	moveDirection = MOVE_DIRECTION::UP_WARD;

	// 포신
	barrelSize = size / 2;
	barrelAngle = PI / 2;
	barrelEnd.x = pos.x;
	barrelEnd.y = pos.y + barrelSize;

	// 미사일
	missileManager = new MissileManager();
	missileManager->Init(playerType);

	return S_OK;
}

void Tank::Release()
{
	SAFE_RELEASE(missileManager);
}

void Tank::Update()
{
	if (playerType == PLAYER_TYPE::FIRST_PLAYER)
	{
		MoveP1();
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
		{
			missileManager->Fire(this->barrelEnd, this->barrelAngle, moveDirection);
		}
	}
	else if (playerType == PLAYER_TYPE::SECOND_PLAYER)
	{
		MoveP2();
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_NUMPAD0))
		{
			missileManager->Fire(this->barrelEnd, this->barrelAngle, moveDirection);
		}
	}
	else if (playerType == PLAYER_TYPE::ENEMY_PLAYER)
	{
		MoveRandom();
		FireRandom();
	}

	shape = GetRectToCenter(pos.x, pos.y, size, size);
	missileManager->Update();
}

void Tank::Render(HDC hdc)
{
	// 몸통
	image->FrameRender(hdc, pos.x, pos.y, curFrame.x, curFrame.y, true, 50/64.0f);

	// 포신
	MoveToEx(hdc, pos.x, pos.y, NULL);
	LineTo(hdc, barrelEnd.x, barrelEnd.y);

	// 미사일
	missileManager->Render(hdc);
}

void Tank::MoveP1()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown('W'))
	{
		moveTimer += TimerManager::GetSingleton()->GetElapsedTime();
		if (moveTimer >= 0.1f) {
			if (!(curFrame.x >= MOVE_DIRECTION::UP_WARD && curFrame.x < MOVE_DIRECTION::LEFT_WARD))
			{
				moveDirection = MOVE_DIRECTION::UP_WARD;
				curFrame.x = MOVE_DIRECTION::UP_WARD;
			}
			else
			{
				curFrame.x += 1;
				if (!(curFrame.x >= MOVE_DIRECTION::UP_WARD && curFrame.x < MOVE_DIRECTION::LEFT_WARD))
				{
					curFrame.x = MOVE_DIRECTION::UP_WARD;
				}
			}
			ChangeBarrel(moveDirection);
			pos.y -= moveSpeed;
			if (pos.y < BATTLE_SCENE_START_Y + size / 2)
			{
				pos.y = BATTLE_SCENE_START_Y + size / 2;
			}
			moveTimer = 0.0f;
		}
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown('S'))
	{
		moveTimer += TimerManager::GetSingleton()->GetElapsedTime();
		if (moveTimer >= 0.1f) {
			if (!(curFrame.x >= MOVE_DIRECTION::DOWN_WARD && curFrame.x < MOVE_DIRECTION::RIGHT_WARD))
			{
				moveDirection = MOVE_DIRECTION::DOWN_WARD;
				curFrame.x = MOVE_DIRECTION::DOWN_WARD;
			}
			else
			{
				curFrame.x += 1;
				if (!(curFrame.x >= MOVE_DIRECTION::DOWN_WARD && curFrame.x < MOVE_DIRECTION::RIGHT_WARD))
				{
					curFrame.x = MOVE_DIRECTION::DOWN_WARD;
				}
			}
			ChangeBarrel(moveDirection);
			pos.y += moveSpeed;
			if (pos.y > BATTLE_SCENE_END_Y - size / 2)
			{
				pos.y = BATTLE_SCENE_END_Y - size / 2;
			}
			moveTimer = 0.0f;
		}
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown('A'))
	{
		moveTimer += TimerManager::GetSingleton()->GetElapsedTime();
		if (moveTimer >= 0.1f) {
			if (!(curFrame.x >= MOVE_DIRECTION::LEFT_WARD && curFrame.x < MOVE_DIRECTION::DOWN_WARD))
			{
				moveDirection = MOVE_DIRECTION::LEFT_WARD;
				curFrame.x = MOVE_DIRECTION::LEFT_WARD;
			}
			else
			{
				curFrame.x += 1;
				if (!(curFrame.x >= MOVE_DIRECTION::LEFT_WARD && curFrame.x < MOVE_DIRECTION::DOWN_WARD))
				{
					curFrame.x = MOVE_DIRECTION::LEFT_WARD;
				}
			}
			ChangeBarrel(moveDirection);
			pos.x -= moveSpeed;
			if (pos.x < BATTLE_SCENE_START_X + size / 2)
			{
				pos.x = BATTLE_SCENE_START_X + size / 2;
			}
			moveTimer = 0.0f;
		}
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown('D'))
	{
		moveTimer += TimerManager::GetSingleton()->GetElapsedTime();
		if (moveTimer >= 0.1f) {
			if (!(curFrame.x >= MOVE_DIRECTION::RIGHT_WARD && curFrame.x < MOVE_DIRECTION::END_MOVE_DIRECTION))
			{
				moveDirection = MOVE_DIRECTION::RIGHT_WARD;
				curFrame.x = MOVE_DIRECTION::RIGHT_WARD;
			}
			else
			{
				curFrame.x += 1;
				if (!(curFrame.x >= MOVE_DIRECTION::RIGHT_WARD && curFrame.x < MOVE_DIRECTION::END_MOVE_DIRECTION))
				{
					curFrame.x = MOVE_DIRECTION::RIGHT_WARD;
				}
			}
			ChangeBarrel(moveDirection);
			pos.x += moveSpeed;
			if (pos.x > BATTLE_SCENE_END_X - size / 2)
			{
				pos.x = BATTLE_SCENE_END_X - size / 2;
			}
			moveTimer = 0.0f;
		}
	}
	else
	{
		moveTimer = 0.0f;
	}
}

void Tank::MoveP2()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		moveTimer += TimerManager::GetSingleton()->GetElapsedTime();
		if (moveTimer >= 0.1f) {
			if (!(curFrame.x >= MOVE_DIRECTION::UP_WARD && curFrame.x < MOVE_DIRECTION::LEFT_WARD))
			{
				moveDirection = MOVE_DIRECTION::UP_WARD;
				curFrame.x = MOVE_DIRECTION::UP_WARD;
			}
			else
			{
				curFrame.x += 1;
				if (!(curFrame.x >= MOVE_DIRECTION::UP_WARD && curFrame.x < MOVE_DIRECTION::LEFT_WARD))
				{
					curFrame.x = MOVE_DIRECTION::UP_WARD;
				}
			}
			ChangeBarrel(moveDirection);
			pos.y -= moveSpeed;
			if (pos.y < BATTLE_SCENE_START_Y + size / 2)
			{
				pos.y = BATTLE_SCENE_START_Y + size / 2;
			}
			moveTimer = 0.0f;
		}
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{
		moveTimer += TimerManager::GetSingleton()->GetElapsedTime();
		if (moveTimer >= 0.1f) {
			if (!(curFrame.x >= MOVE_DIRECTION::DOWN_WARD && curFrame.x < MOVE_DIRECTION::RIGHT_WARD))
			{
				moveDirection = MOVE_DIRECTION::DOWN_WARD;
				curFrame.x = MOVE_DIRECTION::DOWN_WARD;
			}
			else
			{
				curFrame.x += 1;
				if (!(curFrame.x >= MOVE_DIRECTION::DOWN_WARD && curFrame.x < MOVE_DIRECTION::RIGHT_WARD))
				{
					curFrame.x = MOVE_DIRECTION::DOWN_WARD;
				}
			}
			ChangeBarrel(moveDirection);
			pos.y += moveSpeed;
			if (pos.y > BATTLE_SCENE_END_Y - size / 2)
			{
				pos.y = BATTLE_SCENE_END_Y - size / 2;
			}
			moveTimer = 0.0f;
		}
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		moveTimer += TimerManager::GetSingleton()->GetElapsedTime();
		if (moveTimer >= 0.1f) {
			if (!(curFrame.x >= MOVE_DIRECTION::LEFT_WARD && curFrame.x < MOVE_DIRECTION::DOWN_WARD))
			{
				moveDirection = MOVE_DIRECTION::LEFT_WARD;
				curFrame.x = MOVE_DIRECTION::LEFT_WARD;
			}
			else
			{
				curFrame.x += 1;
				if (!(curFrame.x >= MOVE_DIRECTION::LEFT_WARD && curFrame.x < MOVE_DIRECTION::DOWN_WARD))
				{
					curFrame.x = MOVE_DIRECTION::LEFT_WARD;
				}
			}
			ChangeBarrel(moveDirection);
			pos.x -= moveSpeed;
			if (pos.x < BATTLE_SCENE_START_X + size / 2)
			{
				pos.x = BATTLE_SCENE_START_X + size / 2;
			}
			moveTimer = 0.0f;
		}
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		moveTimer += TimerManager::GetSingleton()->GetElapsedTime();
		if (moveTimer >= 0.1f) {
			if (!(curFrame.x >= MOVE_DIRECTION::RIGHT_WARD && curFrame.x < MOVE_DIRECTION::END_MOVE_DIRECTION))
			{
				moveDirection = MOVE_DIRECTION::RIGHT_WARD;
				curFrame.x = MOVE_DIRECTION::RIGHT_WARD;
			}
			else
			{
				curFrame.x += 1;
				if (!(curFrame.x >= MOVE_DIRECTION::RIGHT_WARD && curFrame.x < MOVE_DIRECTION::END_MOVE_DIRECTION))
				{
					curFrame.x = MOVE_DIRECTION::RIGHT_WARD;
				}
			}
			ChangeBarrel(moveDirection);
			pos.x += moveSpeed;
			if (pos.x > BATTLE_SCENE_END_X - size / 2)
			{
				pos.x = BATTLE_SCENE_END_X - size / 2;
			}
			moveTimer = 0.0f;
		}
	}
	else
	{
		moveTimer = 0.0f;
	}
}

void Tank::MoveRandom()
{
	moveTimer += TimerManager::GetSingleton()->GetElapsedTime();
	randMoveTimer += TimerManager::GetSingleton()->GetElapsedTime();

	if (randMoveTimer >= 3.0f)
	{
		moveDirection = (MOVE_DIRECTION)((std::rand() % 4) * 2);
		randMoveTimer = 0.0f;
	}

	if (moveTimer >= 0.1f) {

		if (!(curFrame.x >= moveDirection && curFrame.x < moveDirection+2))
		{
			curFrame.x = moveDirection;
		}
		else
		{
			curFrame.x += 1;
			if (!(curFrame.x >= moveDirection && curFrame.x < moveDirection + 2))
			{
				curFrame.x = moveDirection;
			}
		}
		ChangeBarrel(moveDirection);
		moveTimer = 0.0f;

		switch (moveDirection)
		{
		case MOVE_DIRECTION::UP_WARD:
			pos.y -= moveSpeed;
			if (pos.y < BATTLE_SCENE_START_Y + size / 2)
			{
				pos.y = BATTLE_SCENE_START_Y + size / 2;
			}
			break;
		case MOVE_DIRECTION::DOWN_WARD:
			pos.y += moveSpeed;
			if (pos.y > BATTLE_SCENE_END_Y - size / 2)
			{
				pos.y = BATTLE_SCENE_END_Y - size / 2;
			}
			break;
		case MOVE_DIRECTION::LEFT_WARD:
			pos.x -= moveSpeed;
			if (pos.x < BATTLE_SCENE_START_X + size / 2)
			{
				pos.x = BATTLE_SCENE_START_X + size / 2;
			}
			break;
		case MOVE_DIRECTION::RIGHT_WARD:
			pos.x += moveSpeed;
			if (pos.x > BATTLE_SCENE_END_X - size / 2)
			{
				pos.x = BATTLE_SCENE_END_X - size / 2;
			}
			break;
		default:
			return;
		}
	}
}

void Tank::FireRandom()
{
	fireTimer += TimerManager::GetSingleton()->GetElapsedTime();
	if (fireTimer >= 2.0f)
	{
		missileManager->Fire(this->barrelEnd, this->barrelAngle, moveDirection);
		fireTimer = 0.0f;
	}
}

void Tank::ChangeBarrel(MOVE_DIRECTION tankMove)
{
	switch (tankMove)
	{
	case MOVE_DIRECTION::UP_WARD:
		barrelEnd.x = pos.x;
		barrelEnd.y = pos.y - barrelSize;
		barrelAngle = PI / 2;
		break;
	case MOVE_DIRECTION::DOWN_WARD:
		barrelEnd.x = pos.x;
		barrelEnd.y = pos.y + barrelSize;
		barrelAngle = PI*3 / 2;
		break;
	case MOVE_DIRECTION::LEFT_WARD:
		barrelEnd.x = pos.x - barrelSize;
		barrelEnd.y = pos.y;
		barrelAngle = PI;
		break;
	case MOVE_DIRECTION::RIGHT_WARD:
		barrelEnd.x = pos.x + barrelSize;
		barrelEnd.y = pos.y;
		barrelAngle = 0.0f;
		break;
	}
}

void Tank::CheckBorderline()
{
	if (shape.left <= BATTLE_SCENE_START_X) {
		pos.x = BATTLE_SCENE_START_X + size/2;
	}
	else if (shape.right >= BATTLE_SCENE_END_X) {
		pos.x = BATTLE_SCENE_END_X - size / 2;
	}
	else if (shape.top <= BATTLE_SCENE_START_Y)
	{
		pos.y = BATTLE_SCENE_START_Y + size / 2;
	}
	else if (shape.bottom >= BATTLE_SCENE_END_Y)
	{
		pos.y = BATTLE_SCENE_END_Y - size / 2;
	}
}


