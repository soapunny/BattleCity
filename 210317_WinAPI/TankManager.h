#pragma once
#include "GameNode.h"
#include "vector"

class Tank;
class TankFactory;
class TankManager
{
public:
private:
	vector<Tank*> vTanks;
	TankFactory* tankFactory;
	int maxTankSize;

public:
	virtual HRESULT Init();			// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();			// �޸� ����
	virtual void Update();			// ������ ������ ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ������ ��� (�̹���, �ؽ�Ʈ ��)

	virtual ~TankManager() {}
};

