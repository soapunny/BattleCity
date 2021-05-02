#pragma once
#include "config.h"
#include "Singleton.h"
#include <vector>
#include <list>

enum EXPLOSION_TYPE{SMALL_EXPLOSION, HUGE_EXPLOSION, SIZE_OF_EXPLOSION};
typedef struct _collision_data
{
	FPOINT pos; 
	POINT currFrame;
	float timer;
	EXPLOSION_TYPE explosionType;

	_collision_data()
	{
		pos.x = 0.0f;
		pos.y = 0.0f;
		currFrame.x = 0;
		currFrame.y = 0;
		timer = 0.0f;
		explosionType = EXPLOSION_TYPE::SMALL_EXPLOSION;
	}
	
}CollisionData;

class Missile;
class Item;
class Tank;
class CollisionManager : public Singleton<CollisionManager>
{
private:
	Tank* player1;
	Tank* player2;

	Image* boomEffect;
	Image* bigBoomEffect;
	list<CollisionData> collisionBuffer;

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
	void RegisterVItem(vector<Item*>* vItemStorage);
	Item* RemoveItem(Item* item);

	inline void SetPlayer1(Tank* player1) { this->player1 = player1; }
	inline void SetPlayer2(Tank* player2) { this->player2 = player2; }

	void CheckRect(Tank* tank1, Tank* tank2);

	void CheckCollision();
	void CheckMissileOut();
	void CheckMissileTankCollision(int i);
	void CheckMissileMissileCollision();
	void CheckTankTankCollision();
	void CheckTankTileCollision();
	void CheckMissileTileCollision();
	void ShowAnimation();

	inline void AddCollisionBuffer(FPOINT pos, EXPLOSION_TYPE explosionType = EXPLOSION_TYPE::SMALL_EXPLOSION)
	{
		CollisionData collisionData; collisionData.pos = pos; collisionData.explosionType = explosionType;  collisionBuffer.push_back(collisionData);
	}

	HRESULT Init();
	void Render(HDC hdc);
	void Release();
};

