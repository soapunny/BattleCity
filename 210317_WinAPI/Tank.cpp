#include "CommonFunction.h"
#include "Tank.h"
#include "Missile.h"

HRESULT Tank::Init()
{
	pos.x = WINSIZE_X / 2;
	pos.y = WINSIZE_Y;
	size = 80;
	attackValue = 10;
	name = "��ũ";
	shape = GetRectToCenter(pos.x, pos.y, size, size);

	// ����
	barrelSize = 100;
	barrelEnd.x = pos.x;
	barrelEnd.y = pos.y - barrelSize;
	barrelAngle = 3.14f / 4.0f;

	// �̻���
	missileCount = 300;
	missile = new Missile[missileCount];
	for (int i = 0; i < missileCount; i++)
	{
		missile[i].Init(nullptr);
	}

	//for (int i = 0; i < missileCount; i++)
	//{
	//	missile[i] = new Missile();
	//	missile[i]->Init();
	//}

	//missile = new Missile();
	//missile->Init();

	return S_OK;
}

void Tank::Release()
{
	for (int i = 0; i < missileCount; i++)
	{
		missile[i].Release();
	}
	delete[] missile;

	//for (int i = 0; i < missileCount; i++)
	//{
	//	missile[i]->Release();
	//}
	//delete[] missile;

	//missile->Release();
	//delete missile;
}

void Tank::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown('G'))
	{
		//FireFollowTarget(&enemy[0]);
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown('F'))
	{
		FireSkill_01();
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		Fire();
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LEFT))
	{
		RotateBarrel(0.07f);
	}
	else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RIGHT))
	{
		RotateBarrel(-0.07f);
	}

	// ���� ������ ���� ��ǥ ���
	barrelEnd.x = pos.x + cosf(barrelAngle) * barrelSize;
	barrelEnd.y = pos.y - (sinf(barrelAngle) * barrelSize);

	for (int i = 0; i < missileCount; i++)
	{
		missile[i].Update();
	}
}

void Tank::Render(HDC hdc)
{
	// ����
	Ellipse(hdc, shape.left, shape.top, shape.right, shape.bottom);

	// ����
	MoveToEx(hdc, pos.x, pos.y, NULL);
	LineTo(hdc, barrelEnd.x, barrelEnd.y);

	// �̻���
	for (int i = 0; i < missileCount; i++)
	{
		missile[i].Render(hdc);
	}
}

void Tank::RotateBarrel(float angle)
{
	barrelAngle += angle;
}

void Tank::Move()
{
}

void Tank::Fire()
{
	// �̻��� �߻�
	// ���¸� ����
	for (int i = 0; i < missileCount; i++)
	{
		if (missile[i].GetIsFired() == false)
		{
			missile[i].SetType(Missile::TYPE::Normal);
			missile[i].SetPos(barrelEnd);
			missile[i].SetIsFired(true);
			missile[i].SetAngle(barrelAngle);

			break;
		}
	}
}

void Tank::FireSkill_01()
{
	// 1. �̻����� 36���� ��� ���� ���� �̻� �ö󰡸� 36�������� ������ �Ѵ�.
	int firedCount = 0;
	for (int i = 0; i < missileCount; i++)
	{
		if (firedCount < 36 && missile[i].GetIsFired() == false)
		{
			missile[i].SetType(Missile::TYPE::Skill_01);
			missile[i].SetPos(barrelEnd);
			missile[i].SetIsFired(true);
			missile[i].SetAngle(barrelAngle/* + (firedCount * 0.05f)*/);
			missile[i].SetFireIndex(firedCount);

			firedCount++;
		}
	}

	// 2. �̻����� �ѹ� ��� ���� ���� �̻� �ö󰡸� 36���� ȣ���Ѵ�.
}

void Tank::FireFollowTarget(Enemy* target)
{
	for (int i = 0; i < missileCount; i++)
	{
		if (missile[i].GetIsFired() == false)
		{
			missile[i].SetType(Missile::TYPE::FollowTarget);
			missile[i].SetPos(barrelEnd);
			missile[i].SetIsFired(true);
			missile[i].SetAngle(barrelAngle);
			missile[i].SetTarget(target);

			break;
		}
	}
}

void Tank::Dead()
{
}
