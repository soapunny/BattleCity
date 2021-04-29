#pragma once
#include "GameNode.h"

class MissileManager;		// 전방선언
class Image;
class Tank : public GameNode
{
public:
	enum TANK_TYPE { WHITE_TANK, YELLOW_TANK, GREEN_TANK, PURPLE_TANK, END_TANK_TYPE };
protected:
	// 속성 : 멤버변수
	FPOINT pos;
	int size;
	float powerLevel;
	int moveSpeed;
	string name;
	RECT shape;
	Image* image;
	bool isAlive;

	PLAYER_TYPE playerType;
	MOVE_DIRECTION moveDirection;

	// 포신
	// 포신의 시작점, 끝점
	FPOINT barrelEnd;
	int barrelSize;
	float barrelAngle;		

	POINT curFrame;
	POINT maxFrame;

	// 미사일
	MissileManager* missileManager;		// 2

	//타이머
	float moveTimer;
	float randMoveTimer;
	float fireTimer;

public:

	virtual HRESULT Init();
	virtual void Release();		
	virtual void Update();		
	virtual void Render(HDC hdc);

	virtual void MoveP1();
	virtual void MoveP2();
	virtual void MoveRandom();
	virtual void FireRandom();
	virtual void ChangeBarrel(MOVE_DIRECTION tankMove);

	// get, set
	FPOINT GetPos() { return this->pos; }
	MissileManager* GetMissileManager() { return this->missileManager; }
	inline void SetAlive(bool isAlive) { this->isAlive = isAlive; }
	inline bool GetAlive() { return this->isAlive; }

	inline void SetPlayerType(PLAYER_TYPE playerType) { this->playerType = playerType; }
};

