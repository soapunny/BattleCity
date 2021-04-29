#include "CollisionManager.h"
#include "Missile.h"
#include <algorithm>
#include "Tank.h"

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

void CollisionManager::AddTank(Tank* tank)
{
    vTankStorage.push_back(tank);
}

Tank* CollisionManager::RemoveTank(Tank* tank)
{
    //lTankStorage.(tank);
    return tank;
}

void CollisionManager::AddItem(Item* item)
{
    vItemStorage.push_back(item);
}

Item* CollisionManager::RemoveItem(Item* item)
{
    //lItemStorage.remove(item);
    return item;
}

void CollisionManager::CheckRect(Tank* tank1, Tank* tank2)
{
    if (IntersectRect(&tmpRect, &tank1->GetShape(), &tank2->GetShape()))
    {
        int yGap = tmpRect.bottom - tmpRect.top;
        int xGap = tmpRect.right - tmpRect.left;
        switch (tank1->GetMove_Direction())
        {
        case MOVE_DIRECTION::UP_WARD:
            tank1->SetMove_Direction(MOVE_DIRECTION::DOWN_WARD);
            tank1->SetPos(FPOINT{ tank1->GetPos().x, tank1->GetPos().y - yGap });
            tank2->SetPos(FPOINT{ tank2->GetPos().x, tank2->GetPos().y + yGap });
            break;
        case MOVE_DIRECTION::DOWN_WARD:
            tank1->SetMove_Direction(MOVE_DIRECTION::UP_WARD);
            tank1->SetPos(FPOINT{ tank1->GetPos().x, tank1->GetPos().y + yGap });
            tank2->SetPos(FPOINT{ tank2->GetPos().x, tank2->GetPos().y - yGap });
            break;
        case MOVE_DIRECTION::LEFT_WARD:
            tank1->SetMove_Direction(MOVE_DIRECTION::RIGHT_WARD);
            tank1->SetPos(FPOINT{ tank1->GetPos().x - xGap, tank1->GetPos().y });
            tank2->SetPos(FPOINT{ tank2->GetPos().x + xGap, tank2->GetPos().y });
            break;
        case MOVE_DIRECTION::RIGHT_WARD:
            tank1->SetMove_Direction(MOVE_DIRECTION::LEFT_WARD);
            tank1->SetPos(FPOINT{ tank1->GetPos().x + xGap, tank1->GetPos().y });
            tank2->SetPos(FPOINT{ tank2->GetPos().x - xGap, tank2->GetPos().y });
            break;
        }
    }
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

    //탱크와 탱크의 충돌 체크
    if(vTankStorage.size() > 0)
        for (int i = 0; i < vTankStorage.size()-1; i++)
        {
            for (int j = i + 1; j < vTankStorage.size(); j++)
            {
                CheckRect(vTankStorage[i], vTankStorage[j]);
               
            }
        }

    //플레이어와 아이템과의 충돌 체크
}


CollisionManager::CollisionManager()
{

}
