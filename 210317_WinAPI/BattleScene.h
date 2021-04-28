#pragma once
#include "GameNode.h"

//���� MainGame Ŭ������ ������ �̵�

class PlayerShip;
class Tank;
class EnemyManager;
class Image;
class BattleScene : public GameNode
{
private:
	Image* battleStage;

	Tank* tank;
	EnemyManager* enemyMgr;
	PlayerShip* playerShip;

	int stageNum;

public:
	virtual HRESULT Init();		// �������̵� : ������
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void CheckCollision();
	virtual ~BattleScene() {}
	
	void LoadStage(int stageNum);
};

