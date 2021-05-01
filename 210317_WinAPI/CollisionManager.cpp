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

void CollisionManager::RegisterVTank(vector<Tank*>* vTankStorage)
{
    this->vTankStorage = vTankStorage;
}

Tank* CollisionManager::RemoveTank(Tank* tank)
{
    //lTankStorage.(tank);
    return tank;
}

void CollisionManager::AddItem(Item* item)
{
    vItemStorage->push_back(item);
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
            break;
        case MOVE_DIRECTION::DOWN_WARD:
            tank1->SetMove_Direction(MOVE_DIRECTION::UP_WARD);
            tank1->SetPos(FPOINT{ tank1->GetPos().x, tank1->GetPos().y + yGap });
            break;
        case MOVE_DIRECTION::LEFT_WARD:
            tank1->SetMove_Direction(MOVE_DIRECTION::RIGHT_WARD);
            tank1->SetPos(FPOINT{ tank1->GetPos().x - xGap, tank1->GetPos().y });
            break;
        case MOVE_DIRECTION::RIGHT_WARD:
            tank1->SetMove_Direction(MOVE_DIRECTION::LEFT_WARD);
            tank1->SetPos(FPOINT{ tank1->GetPos().x + xGap, tank1->GetPos().y });
            break;
        }
        switch (tank2->GetMove_Direction())
        {
        case MOVE_DIRECTION::UP_WARD:
            if (tank1->GetMove_Direction() != MOVE_DIRECTION::DOWN_WARD)
                tank2->SetMove_Direction(MOVE_DIRECTION::DOWN_WARD);
            tank2->SetPos(FPOINT{ tank2->GetPos().x, tank2->GetPos().y - yGap });
            break;
        case MOVE_DIRECTION::DOWN_WARD:
            if (tank1->GetMove_Direction() != MOVE_DIRECTION::UP_WARD)
                tank2->SetMove_Direction(MOVE_DIRECTION::UP_WARD);
            tank2->SetPos(FPOINT{ tank2->GetPos().x, tank2->GetPos().y + yGap });
            break;
        case MOVE_DIRECTION::LEFT_WARD:
            if (tank1->GetMove_Direction() != MOVE_DIRECTION::RIGHT_WARD)
                tank2->SetMove_Direction(MOVE_DIRECTION::RIGHT_WARD);
            tank2->SetPos(FPOINT{ tank2->GetPos().x - xGap, tank2->GetPos().y });
            break;
        case MOVE_DIRECTION::RIGHT_WARD:
            if (tank1->GetMove_Direction() != MOVE_DIRECTION::LEFT_WARD)
                tank2->SetMove_Direction(MOVE_DIRECTION::LEFT_WARD);
            tank2->SetPos(FPOINT{ tank2->GetPos().x + xGap, tank2->GetPos().y });
            break;
        }
        tank1->CheckBorderline();
        tank2->CheckBorderline();
    }
}

void CollisionManager::CheckCollision()
{


    /*vector<Missile*> vMissiles;
    mMissileStorage.insert(make_pair("1", &(vMissiles)));*/
    vector<Missile*>* tmpVMissiles1 = nullptr;
    vector<Missile*>* tmpVMissiles2 = nullptr;
    if (mMissileStorage.size() > 1) {
        //�÷��̾� �̻��ϰ� �÷��� && �� �̻����� �浹 üũ
        for (int i = 0; i < vTankStorage->size() - 1; i++)
        {
            if (mMissileStorage.find((*vTankStorage)[i]->GetName()) != mMissileStorage.end())
                tmpVMissiles1 = mMissileStorage.at((*vTankStorage)[i]->GetName()); //�̻��� ���̸� �̸����� ������
            else continue;
            //map���� �̻��� ���͵��� �ϳ��� ������ ���Ѵ�.
            for (int j = i + 1; j < vTankStorage->size(); j++)
            {
                if (mMissileStorage.find((*vTankStorage)[j]->GetName()) != mMissileStorage.end())
                    tmpVMissiles2 = mMissileStorage.at((*vTankStorage)[j]->GetName()); //�̻��� ���̸� �̸����� ������
                else continue;
                if ((*vTankStorage)[i]->GetAlive() && (*vTankStorage)[j]->GetAlive())
                {
                    for (int k = 0; k < tmpVMissiles1->size(); k++) {
                        for (int l = 0; l < tmpVMissiles2->size(); l++) {
                            if ((*tmpVMissiles1)[k]->GetIsFired() && (*tmpVMissiles2)[l]->GetIsFired())
                            {
                                if (IntersectRect(&tmpRect, &((*tmpVMissiles1)[k]->GetShape()), &((*tmpVMissiles2)[l]->GetShape())))//TODO �̻��� RECT ������ֱ�
                                {
                                    (*tmpVMissiles1)[k]->SetIsFired(false);
                                    (*tmpVMissiles2)[l]->SetIsFired(false);
                                }
                            }
                        }
                    }
                }
            }
        }

        //�÷��̾� �̻��ϰ� ������ �浹 üũ
        for (int i = 0; i < vTankStorage->size(); i++)//��ũ ���� ������
        {
            if ((*vTankStorage)[i]->GetAlive()){
                for (map<string, vector<Missile*>* >::iterator it = mMissileStorage.begin(); it != mMissileStorage.end();)
                {//�̻��� ���� �����鼭
                    for (int j = 0; j < (*it).second->size();j++)//������ �̻��� ���͵��� �����鼭
                    {
                        if ((*it).second->at(j)->GetIsFired() && (*vTankStorage)[i]->GetAlive()) {//�ش� �̻����� �߻�� ���°� ��ũ�� ���������
                            if(IntersectRect(&tmpRect, &(*it).second->at(j)->GetShape(), &(*vTankStorage)[i]->GetShape())){
                                (*it).second->at(j)->SetIsFired(false);
                                (*vTankStorage)[i]->SetAlive(false);
                                mMissileStorage.erase(it++);
                                break;
                            }
                        }
                        else if (j = (*it).second->size() - 1)
                        {
                            it++;
                            break;
                        }
                    }
                }
            }
        }

    }


    //�� �̻��ϰ� �÷��̾���� �浹 üũ

    //�÷��̾� �̻��ϰ� ������ �浹 üũ
    
    //�� �̻��ϰ� ������ �浹 üũ

    //��ũ�� ��ũ�� �浹 üũ
    if(vTankStorage->size() > 0)
        for (int i = 0; i < vTankStorage->size()-1; i++)
        {
            for (int j = i + 1; j < vTankStorage->size(); j++)
            {
                if ((*vTankStorage)[i]->GetAlive() && (*vTankStorage)[j]->GetAlive())
                {
                    CheckRect((*vTankStorage)[i], (*vTankStorage)[j]);
                }                       
            }
        }

    //�÷��̾�� �����۰��� �浹 üũ
}


