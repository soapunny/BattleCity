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

	float createTimer;

public:
	virtual HRESULT Init();			// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();			// �޸� ����
	virtual void Update(int currStage);		// ������ ������ ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ������ ��� (�̹���, �ؽ�Ʈ ��)

	void CreateEnemyTank(STAGE_TYPE stage);

	virtual ~TankManager() {}
};

