#include "CommonFunction.h"
#include "Tank.h"
#include "MissileManager.h"
#include "Image.h"

HRESULT Tank::Init()
{
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y;
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
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		missileManager->Fire(this->barrelEnd, this->barrelAngle, moveDirection);
	}

	if (playerType >= PLAYER_TYPE::FIRST_PLAYER && playerType <= PLAYER_TYPE::SECOND_PLAYER)
	{
		Move();
	}
	else if (playerType == PLAYER_TYPE::ENEMY_PLAYER)
	{
		MoveRandom();
	}

	missileManager->Update();
}

void Tank::Render(HDC hdc)
{
	// 몸통
	image->FrameRender(hdc, pos.x, pos.y, curFrame.x, curFrame.y, true);

	// 포신
	MoveToEx(hdc, pos.x, pos.y, NULL);
	LineTo(hdc, barrelEnd.x, barrelEnd.y);

	// 미사일
	missileManager->Render(hdc);
}

void Tank::Move()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown('W'))
	{
		moveTimer += TimerManager::GetSingleton()->GetElapsedTime();
		if(moveTimer >= 0.1f){
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
			if(pos.y < size / 2)
			{
				pos.y = size / 2;
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
			if (pos.y > WINSIZE_Y - size / 2)
			{
				pos.y = WINSIZE_Y - size / 2;
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
			if (pos.x < size / 2)
			{
				pos.x = size / 2;
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
			if (pos.x > WINSIZE_X - size / 2)
			{
				pos.x = WINSIZE_X - size / 2;
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


