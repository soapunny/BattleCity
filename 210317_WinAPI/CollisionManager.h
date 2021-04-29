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
	vector<Tank*> vTankStorage; //TODO Tank와 Item의 컨테이너를 어떻게??
	vector<Item*> vItemStorage;
	//벽돌 타일 저장 스토리지도 만들어야함

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

