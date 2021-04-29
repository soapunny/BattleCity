#include "CollisionManager.h"
#include "Missile.h"
#include <algorithm>

void CollisionManager::AddMissiles(string key, vector<Missile*>* vNewMissiles)
{
    if (vNewMissiles == nullptr) return;

    mMissileStorage.insert(make_pair(key, vNewMissiles));
}

Missile* CollisionManager::RemoveMissiles(string key)
{
    mMissileStorage.erase(key);

    return nullptr;
}

void CollisionManager::CheckCollision()
{
    //플레이어 미사일과 적 미사일의 충돌 체크
    //플레이어1

    //플레이어2
    for (map<string, vector<Missile*>*>::iterator iter = mMissileStorage.begin();iter != mMissileStorage.end(); iter++)
    {
        //iter->second();
    }

    //플레이어 미사일과 적과의 충돌 체크

    //적 미사일과 플레이어와의 충돌 체크

    //플레이어 미사일과 벽과의 충돌 체크
    
    //적 미사일과 벽과의 충돌 체크

    //플레이어와 아이템과의 충돌 체크
}

CollisionManager::CollisionManager()
{

}
