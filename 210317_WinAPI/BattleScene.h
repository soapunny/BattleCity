#pragma once
#include "GameNode.h"

//���� MainGame Ŭ������ ������ �̵�

class PlayerShip;
class TankManager;
class EnemyManager;
class Image;
class BattleScene : public GameNode
{
private:
	Image* bin;

	TankManager* tankManager;
	EnemyManager* enemyMgr;
	PlayerShip* playerShip;
public:

	virtual HRESULT Init();		// �������̵� : ������
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void CheckCollision();
	virtual ~BattleScene() {}
};

