#pragma once
#include "GameNode.h"
#include <vector>

class Enemy;
class Missile;
class MissileManager : public GameNode
{
private:
	vector<Missile*> vMissiles;
	int maxMissileCnt;
	int currMissileCnt;

public:
	HRESULT Init(PLAYER_TYPE playerType);
	void Release();
	void Update();
	void Render(HDC hdc);

	void Fire(FPOINT startPos,float angle, MOVE_DIRECTION moveDirection);
	inline vector<Missile*>* GetVMissiles() { return &vMissiles; }
};

