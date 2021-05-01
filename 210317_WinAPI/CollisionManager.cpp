#include "CollisionManager.h"
#include "Missile.h"
#include "Image.h"
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

    vector<Missile*>* tmpVMissiles1 = nullptr;
    vector<Missile*>* tmpVMissiles2 = nullptr;
    if (mMissileStorage.size() > 0) {
        //�浹 �ִϸ��̼�
        for (list<CollisionData>::iterator it = collisionBuffer.begin(); it != collisionBuffer.end();)
        {
            it->timer += TimerManager::GetSingleton()->GetElapsedTime();

            //���� �浹
            if(it->explosionType == EXPLOSION_TYPE::SMALL_EXPLOSION){
                if (it->timer >= 0.3f) {
                    it->currFrame.x += 1;
                    if (it->currFrame.x >= boomEffect->GetImageInfo()->maxFrameX)
                    {
                        it->currFrame.y += 1;
                        it->currFrame.x = 0;
                        if (it->currFrame.y >= boomEffect->GetImageInfo()->maxFrameY) {
                            it->currFrame.y = 0;
                            it = collisionBuffer.erase(it);
                            continue;
                        }
                    }
                    it->timer = 0.0f;
                }
            }
            //ū �浹
            else if (it->explosionType == EXPLOSION_TYPE::HUGE_EXPLOSION)
            {
                if (it->timer >= 0.5f) {
                    it->currFrame.x += 1;
                    if (it->currFrame.x >= bigBoomEffect->GetImageInfo()->maxFrameX)
                    {
                        it->currFrame.y += 1;
                        it->currFrame.x = 0;
                        if (it->currFrame.y >= bigBoomEffect->GetImageInfo()->maxFrameY) {
                            it->currFrame.y = 0;
                            it = collisionBuffer.erase(it);
                            continue;
                        }
                    }
                    it->timer = 0.0f;
                }
            }

            it++;
        }

        //ȭ�� �������� �̻��� �浹
        for (int i = 0; i < vTankStorage->size(); i++)
        {
            if (mMissileStorage.find((*vTankStorage)[i]->GetName()) != mMissileStorage.end())
                tmpVMissiles1 = mMissileStorage.at((*vTankStorage)[i]->GetName()); //�̻��� ���̸� �̸����� ������
            else continue;
            for(Missile* missile : *tmpVMissiles1){
                if(missile->GetIsFired())
                {
                    if (missile->GetPos().x < BATTLE_SCENE_START_X || missile->GetPos().y < BATTLE_SCENE_START_Y 
                        || missile->GetPos().x > BATTLE_SCENE_END_X || missile->GetPos().y > BATTLE_SCENE_END_Y)
                    {
                        missile->SetIsFired(false);
                        AddCollisionBuffer(missile->GetPos());
                    }
                }
            }
        }

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

                                    AddCollisionBuffer(FPOINT{ ((*tmpVMissiles1)[k]->GetPos().x + (*tmpVMissiles2)[l]->GetPos().x)/2.0f
                                        , ((*tmpVMissiles1)[k]->GetPos().y + (*tmpVMissiles2)[l]->GetPos().y)/2.0f });
                                }
                            }
                        }
                    }
                }
            }
        }

        //�̻��ϰ� ��ũ�� �浹 üũ
        for (int i = 0; i < vTankStorage->size(); i++)//��ũ ���� ������
        {
            CheckMissileTankCollision(i);
        }

        //��ũ�� ��ũ�� �浹 üũ
        if (vTankStorage->size() > 0)
            for (int i = 0; i < vTankStorage->size() - 1; i++)
            {
                for (int j = i + 1; j < vTankStorage->size(); j++)
                {
                    if ((*vTankStorage)[i]->GetAlive() && (*vTankStorage)[j]->GetAlive())
                    {
                        CheckRect((*vTankStorage)[i], (*vTankStorage)[j]);
                    }
                }
            }


        //�̻��ϰ� Ÿ�ϰ��� �浹 üũ

        //�÷��̾�� �����۰��� �浹 üũ

    }
}

void CollisionManager::CheckMissileTankCollision(int i)
{
    if ((*vTankStorage)[i]->GetAlive()) {
        for (map<string, vector<Missile*>* >::iterator it = mMissileStorage.begin(); it != mMissileStorage.end();)
        {//�̻��� ���� �����鼭
            if ((*it).first != (*vTankStorage)[i]->GetName()) {
                for (int j = 0; j < (*it).second->size(); j++)//������ �̻��� ���͵��� �����鼭
                {
                    if ((*it).second->at(j)->GetIsFired() && IntersectRect(&tmpRect, &(*it).second->at(j)->GetShape(), &(*vTankStorage)[i]->GetShape())) {
                        (*it).second->at(j)->SetIsFired(false);
                        (*vTankStorage)[i]->SetAlive(false);
                        AddCollisionBuffer((*vTankStorage)[i]->GetPos(), EXPLOSION_TYPE::HUGE_EXPLOSION);
                        return;
                    }
                    else if (j == (*it).second->size() - 1)
                    {
                        it++;
                        break;
                    }
                }
            }
            else
            {
                it++;
            }
        }
    }
    else //�̻��� �ʿ��� ���� �÷��̾��� �̻����� ������ �������� �����ֱ�
    {
        bool hasGone = true;
        map<string, vector<Missile*>* >::iterator it = mMissileStorage.find( (*vTankStorage)[i]->GetName());
        if (it == mMissileStorage.end()) return; //�ش� ��ũ�� �̻��� ���̰� �̻�������ҿ� �ö�� ���� ������ return
        for (auto lpMissiles : *(*it).second){//�̻��� ������ �����鼭
            if (lpMissiles->GetIsFired())//�̻����� �ϳ��� ��ƾ�����
            {
                hasGone = false;
            }
        }
        if (hasGone)//�̻����� �� �Ҹ������
        {
            mMissileStorage.erase(mMissileStorage.find((*vTankStorage)[i]->GetName()));//�ش� �̻��� ���� ����
            return;
        }

    }
}

HRESULT CollisionManager::Init()
{
    vTankStorage = nullptr;
    vItemStorage = nullptr;

    boomEffect = ImageManager::GetSingleton()->FindImage("BoomEffect");
    bigBoomEffect = ImageManager::GetSingleton()->FindImage("BigBoomEffect");

    return S_OK;
}

void CollisionManager::Render(HDC hdc)
{
    for(auto collisionData : collisionBuffer)
    {
        if(collisionData.explosionType == EXPLOSION_TYPE::SMALL_EXPLOSION)
            boomEffect->FrameRender(hdc, collisionData.pos.x, collisionData.pos.y, collisionData.currFrame.x, collisionData.currFrame.y, true);
        if (collisionData.explosionType == EXPLOSION_TYPE::HUGE_EXPLOSION)
            bigBoomEffect->FrameRender(hdc, collisionData.pos.x, collisionData.pos.y, collisionData.currFrame.x, collisionData.currFrame.y, true);
    }
}


