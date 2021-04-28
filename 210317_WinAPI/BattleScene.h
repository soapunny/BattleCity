#pragma once
#include "GameNode.h"

//기존 MainGame 클래스의 내용을 이동

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
	virtual HRESULT Init();		// 오버라이딩 : 다형성
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	void CheckCollision();
	virtual ~BattleScene() {}
	
	void LoadStage(int stageNum);
};

