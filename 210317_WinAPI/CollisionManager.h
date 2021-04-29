#pragma once
#include "config.h"
#include "Singleton.h"
#include <vector>

class Missile;
class Item;
class Tank;
class TileInfo;
class CollisionManager : public Singleton<CollisionManager>
{
private:
	map<string, vector<Missile*>* > mMissileStorage;
	map<string, vector<Item*>* > mItemStorage;
	map<string, vector<Tank*>* > mTankStorage;
	//���� Ÿ�� ���� ���丮���� ��������

public:
	void AddMissiles(string key, vector<Missile*>* vNewMissiles);
	Missile* RemoveMissiles(string key);
	void CheckCollision();

	CollisionManager();
};

