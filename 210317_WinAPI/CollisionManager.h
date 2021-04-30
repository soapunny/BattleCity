#pragma once
#include "config.h"
#include "Singleton.h"
#include <vector>

class Missile;
class Item;
class Tank;
class CollisionManager : public Singleton<CollisionManager>
{
private:
	Tank* player1;
	Tank* player2;

	map<string, vector<Missile*>* > mMissileStorage;
	vector<Tank*>* vTankStorage; //TODO Tank와 Item의 컨테이너를 어떻게??
	vector<Item*>* vItemStorage;
	//벽돌 타일 저장 스토리지도 만들어야함

	RECT tmpRect;

public:
	void AddMissiles(string key, vector<Missile*>* vNewMissiles);
	Missile* RemoveMissiles(string key);
	void RegisterVTank(vector<Tank*>* vTankStorage);
	Tank* RemoveTank(Tank* tank);
	void AddItem(Item* item);
	Item* RemoveItem(Item* item);

	inline void SetPlayer1(Tank* player1) { this->player1 = player1; }
	inline void SetPlayer2(Tank* player2) { this->player2 = player2; }

	void CheckRect(Tank* tank1, Tank* tank2);

	void CheckCollision();
};

