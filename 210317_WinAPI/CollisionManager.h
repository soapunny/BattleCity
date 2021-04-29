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
	vector<Tank*> vTankStorage; //TODO Tank�� Item�� �����̳ʸ� ���??
	vector<Item*> vItemStorage;
	//���� Ÿ�� ���� ���丮���� ��������

public:
	void AddMissiles(string key, vector<Missile*>* vNewMissiles);
	Missile* RemoveMissiles(string key);
	void AddTank(vector<Tank*>* vNewTanks);
	Missile* RemoveTank(Tank* tank);
	void AddItem(Item* vNewItems);
	Missile* RemoveItem(string key);

	void CheckCollision();

	CollisionManager();
};

