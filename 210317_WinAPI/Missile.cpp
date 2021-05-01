#pragma once
#include "Missile.h"
#include "CommonFunction.h"
#include "Image.h"

HRESULT Missile::LoadImage()
{
	// �̹���
	imgDown = ImageManager::GetSingleton()->FindImage("MissileDown");
	if (imgDown == nullptr)
	{
		MessageBox(g_hWnd,
			"MissileDown�� �ش��ϴ� �̹����� �߰����� �ʾ���!", "���", MB_OK);
		return E_FAIL;
	}
	imgUp = ImageManager::GetSingleton()->FindImage("MissileUp");
	if (imgUp == nullptr)
	{
		MessageBox(g_hWnd,
			"MissileUp�� �ش��ϴ� �̹����� �߰����� �ʾ���!", "���", MB_OK);
		return E_FAIL;
	}
	imgLeft = ImageManager::GetSingleton()->FindImage("MissileLeft");
	if (imgLeft == nullptr)
	{
		MessageBox(g_hWnd,
			"MissileLeft�� �ش��ϴ� �̹����� �߰����� �ʾ���!", "���", MB_OK);
		return E_FAIL;
	}
	imgRight = ImageManager::GetSingleton()->FindImage("MissileRight");
	if (imgRight == nullptr)
	{
		MessageBox(g_hWnd,
			"MissileRight�� �ش��ϴ� �̹����� �߰����� �ʾ���!", "���", MB_OK);
		return E_FAIL;
	}
	return S_OK;
}

HRESULT Missile::Init(PLAYER_TYPE playerType)
{
	this->playerType = playerType;
	moveDirection = MOVE_DIRECTION::UP_WARD;

	pos = {-100, -100};
	moveSpeed = 200.0f;
	size = 16;
	shape = { 0, 0, 0, 0 };
	damage = 1;
	angle = 0.0f;
	isFired = false;

	return LoadImage();
}

void Missile::Release()
{
}

void Missile::Update()
{
	// ��ġ �̵�
	if (isFired)
	{
		Move();
	}

	shape.left = pos.x - size / 2;
	shape.top = pos.y - size / 2;
	shape.right = pos.x + size / 2;
	shape.bottom = pos.y + size / 2;
}

void Missile::Render(HDC hdc)
{
	if (isFired)
	{
		if(moveDirection == MOVE_DIRECTION::UP_WARD)
		{ 
			imgUp->FrameRender(hdc, pos.x, pos.y, 0, 0, true, 4.0f);
		}
		else if (moveDirection == MOVE_DIRECTION::LEFT_WARD)
		{
			imgLeft->FrameRender(hdc, pos.x, pos.y, 0, 0, true, 4.0f);
		}
		else if (moveDirection == MOVE_DIRECTION::DOWN_WARD)
		{
			imgDown->FrameRender(hdc, pos.x, pos.y, 0, 0, true, 4.0f);
		}
		else if (moveDirection == MOVE_DIRECTION::RIGHT_WARD)
		{
			imgRight->FrameRender(hdc, pos.x, pos.y, 0, 0, true, 4.0f);
		}
		//Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);
	}
}

void Missile::Move()
{
	float elapsedTime = TimerManager::GetSingleton()->GetElapsedTime();
	pos.x += cosf(angle) * moveSpeed * elapsedTime;
	pos.y -= sinf(angle) * moveSpeed * elapsedTime;
}

void Missile::SetIsFired(bool isFired)
{
	this->isFired = isFired;
}
