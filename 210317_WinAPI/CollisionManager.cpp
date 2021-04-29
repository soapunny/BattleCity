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
    //�÷��̾� �̻��ϰ� �� �̻����� �浹 üũ
    //�÷��̾�1

    //�÷��̾�2
    for (map<string, vector<Missile*>*>::iterator iter = mMissileStorage.begin();iter != mMissileStorage.end(); iter++)
    {
        //iter->second();
    }

    //�÷��̾� �̻��ϰ� ������ �浹 üũ

    //�� �̻��ϰ� �÷��̾���� �浹 üũ

    //�÷��̾� �̻��ϰ� ������ �浹 üũ
    
    //�� �̻��ϰ� ������ �浹 üũ

    //�÷��̾�� �����۰��� �浹 üũ
}

CollisionManager::CollisionManager()
{

}
