#pragma once
#include "GameNode.h"
//#include "Missile.h"

/*
	is-a ����		��ũ�� ���ӳ���̴�.
	has-a ����		��ũ�� �̻����� ������ �ִ�.
*/

class Enemy;
class Missile;		// ���漱��
class Tank : public GameNode
{
private:
	// �Ӽ� : �������
	FPOINT pos;
	int size;
	float attackValue;
	string name;
	RECT shape;

	// ����
	// ������ ������, ����
	FPOINT barrelEnd;
	int barrelSize;
	float barrelAngle;		// ����	: �� (degree)		0	~ 180	~ 360
							//		: ���� (radian)	0f	~ 3.14f	~ 6.28f

	// �̻���
	int missileCount;
	//Missile* missile[3];	// 1
	Missile* missile;		// 2

public:
	HRESULT Init();
	void Release();		
	void Update();		
	void Render(HDC hdc);

	void RotateBarrel(float angle);
	void Move();
	void Fire();
	void FireSkill_01();
	void FireFollowTarget(Enemy* target);
	void Dead();

	// get, set
	FPOINT GetPos() { return this->pos; }
	int GetMissileCount() { return this->missileCount; }
	Missile* GetMissile() { return this->missile; }
};

