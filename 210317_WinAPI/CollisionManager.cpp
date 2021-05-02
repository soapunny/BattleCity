#pragma once
#include "CollisionManager.h"
#include "FileManager.h"
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

void CollisionManager::RegisterVItem(vector<Item*>* vItemStorage)
{
    this->vItemStorage = vItemStorage;
}

Item* CollisionManager::RemoveItem(Item* item)
{
    //lItemStorage.remove(item);
    return item;
}


void CollisionManager::CheckCollision()
{
    if (mMissileStorage.size() > 0) {
        
        //�ִϸ��̼� ������ ���
        ShowAnimation();

        //ȭ�� �������� �̻��� �浹
        CheckMissileOut();

        //�̻��ϰ� �̻����� �浹 üũ
        CheckMissileMissileCollision();

        //�̻��ϰ� ��ũ�� �浹 üũ
        for (int i = 0; i < vTankStorage->size(); i++)//��ũ ���� ������
        {
            CheckMissileTankCollision(i);
        }

        //��ũ�� ��ũ�� �浹 üũ
        CheckTankTankCollision();

        //��ũ�� Ÿ���� �浹 üũ
        CheckTankTileCollision();

        //�̻��ϰ� Ÿ�ϰ��� �浹 üũ
        CheckMissileTileCollision();

        //�÷��̾�� �����۰��� �浹 üũ
    }
}

//������ �ѱ��
void CollisionManager::ShowAnimation()
{
    //�浹 �ִϸ��̼�
    for (list<CollisionData>::iterator it = collisionBuffer.begin(); it != collisionBuffer.end();)
    {
        it->timer += TimerManager::GetSingleton()->GetElapsedTime();

        //���� �浹
        if (it->explosionType == EXPLOSION_TYPE::SMALL_EXPLOSION) {
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
}

//�̻��� vs �ܺ� �浹 üũ
void CollisionManager::CheckMissileOut()
{
    vector<Missile*>* tmpVMissiles = nullptr;
    for (int i = 0; i < vTankStorage->size(); i++)
    {
        if (mMissileStorage.find((*vTankStorage)[i]->GetName()) != mMissileStorage.end())
            tmpVMissiles = mMissileStorage.at((*vTankStorage)[i]->GetName()); //�̻��� ���̸� �̸����� ������
        else continue;
        for (Missile* missile : *tmpVMissiles) {
            if (missile->GetIsFired())
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
}

//�̻��� vs ��ũ �浹 üũ
void CollisionManager::CheckMissileTankCollision(int i)
{
    if ((*vTankStorage)[i]->GetAlive()) {
        for (map<string, vector<Missile*>* >::iterator it = mMissileStorage.begin(); it != mMissileStorage.end();)
        {//�̻��� ���� �����鼭
            if ((*it).first != (*vTankStorage)[i]->GetName()) {//�ڽ��� �̻��ϴ��̰� �ƴ� �͸�
                for (int j = 0; j < (*it).second->size(); j++)//������ �̻��� ���͵��� �����鼭
                {
                    if ((*it).second->at(j)->GetIsFired() && IntersectRect(&tmpRect, &(*it).second->at(j)->GetShape(), &(*vTankStorage)[i]->GetShape())) {
                        (*it).second->at(j)->SetIsFired(false);
                        (*vTankStorage)[i]->SetAlive(false);
                        AddCollisionBuffer((*it).second->at(j)->GetPos());
                        AddCollisionBuffer((*vTankStorage)[i]->GetPos(), EXPLOSION_TYPE::HUGE_EXPLOSION);
                        return;
                    }
                }
            }
            it++;
        }
    }
    else //�̻��� �ʿ��� ���� �÷��̾��� �̻����� ������ �������� �����ֱ�
    {
        map<string, vector<Missile*>* >::iterator it = mMissileStorage.find((*vTankStorage)[i]->GetName());
        if (it == mMissileStorage.end()) return; //�ش� ��ũ�� �̻��� ���̰� �̻�������ҿ� �ö�� ���� ������ return
        for (auto lpMissiles : *(*it).second) {//�̻��� ������ �����鼭
            if (lpMissiles->GetIsFired())//�̻����� �ϳ��� ��ƾ�����
                return;
        }

        //�̻����� �� �Ҹ������
        mMissileStorage.erase(mMissileStorage.find((*vTankStorage)[i]->GetName()));//�ش� �̻��� ���� ����
        return;
    }
}

//�̻��� vs �̻��� �浹 üũ
void CollisionManager::CheckMissileMissileCollision()
{
    vector<Missile*>* tmpVMissiles1 = nullptr;
    vector<Missile*>* tmpVMissiles2 = nullptr;
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
            for (int k = 0; k < tmpVMissiles1->size(); k++) {
                for (int l = 0; l < tmpVMissiles2->size(); l++) {
                    if ((*tmpVMissiles1)[k]->GetIsFired() && (*tmpVMissiles2)[l]->GetIsFired()
                        && IntersectRect(&tmpRect, &((*tmpVMissiles1)[k]->GetShape()), &((*tmpVMissiles2)[l]->GetShape())))
                    {
                        (*tmpVMissiles1)[k]->SetIsFired(false);
                        (*tmpVMissiles2)[l]->SetIsFired(false);

                        AddCollisionBuffer(FPOINT{ ((*tmpVMissiles1)[k]->GetPos().x + (*tmpVMissiles2)[l]->GetPos().x) / 2.0f
                            , ((*tmpVMissiles1)[k]->GetPos().y + (*tmpVMissiles2)[l]->GetPos().y) / 2.0f });

                    }
                }
            }
        }
    }
}

//��ũ vs ��ũ �浹 üũ
void CollisionManager::CheckTankTankCollision()
{
    if (vTankStorage->size() > 0) {
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
    }
}
void CollisionManager::CheckRect(Tank* tank1, Tank* tank2)
{
    if (IntersectRect(&tmpRect, &tank1->GetShape(), &tank2->GetShape()))
    {
        if (tank1->GetMove_Direction() == MOVE_DIRECTION::LEFT_WARD || tank1->GetMove_Direction() == MOVE_DIRECTION::RIGHT_WARD)
        {
            if (tank1->GetPos().x <= tank2->GetPos().x)
            {
                tank1->SetPos(FPOINT{ tank1->GetPos().x - tank1->GetMoveSpeed(), tank1->GetPos().y });
            }
            else if (tank1->GetPos().x > tank2->GetPos().x)
            {
                tank1->SetPos(FPOINT{ tank1->GetPos().x + tank1->GetMoveSpeed(), tank1->GetPos().y });
            }
        }
        else
        {
            if (tank1->GetPos().y <= tank2->GetPos().y)
            {
                tank1->SetPos(FPOINT{ tank1->GetPos().x, tank1->GetPos().y - tank1->GetMoveSpeed() });
            }
            else if (tank1->GetPos().y > tank2->GetPos().y)
            {
                tank1->SetPos(FPOINT{ tank1->GetPos().x, tank1->GetPos().y + tank1->GetMoveSpeed() });
            }
        }

        if (tank2->GetMove_Direction() == MOVE_DIRECTION::LEFT_WARD || tank2->GetMove_Direction() == MOVE_DIRECTION::RIGHT_WARD)
        {
            if (tank2->GetPos().x <= tank1->GetPos().x)
            {
                tank2->SetPos(FPOINT{ tank2->GetPos().x - tank2->GetMoveSpeed(), tank2->GetPos().y });
            }
            else if (tank2->GetPos().x > tank1->GetPos().x)
            {
                tank2->SetPos(FPOINT{ tank2->GetPos().x + tank2->GetMoveSpeed(), tank2->GetPos().y });
            }
        }
        else
        {
            if (tank2->GetPos().y <= tank1->GetPos().y)
            {
                tank2->SetPos(FPOINT{ tank2->GetPos().x, tank2->GetPos().y - tank2->GetMoveSpeed() });
            }
            else if (tank2->GetPos().y > tank1->GetPos().y)
            {
                tank2->SetPos(FPOINT{ tank2->GetPos().x, tank2->GetPos().y + tank2->GetMoveSpeed() });
            }
        }

        tank1->CheckBorderline();
        tank2->CheckBorderline();
    }
}

//��ũ vs Ÿ�� �浹 üũ
void CollisionManager::CheckTankTileCollision()
{
    for (int i = 0; i < TILE_X * TILE_Y; i++){
        if( (FileManager::tileInfo+i)->type != TILE_TYPE::GRASS_TILE && (FileManager::tileInfo + i)->type != TILE_TYPE::ROAD_TILE && (FileManager::tileInfo + i)->type != TILE_TYPE::ICE_TILE )
        {
            for(Tank* tank : *vTankStorage)
            {
                if( tank->GetAlive() && IntersectRect(&tmpRect, &((FileManager::tileInfo + i)->rcTile), &(tank->GetShape()) ) )
                {
                    float xGap = tmpRect.right - tmpRect.left;
                    float yGap = tmpRect.bottom - tmpRect.top;
                    //TODO ��ũ�� �ڷ� �з����� ó��
                    if (tank->GetPos().x <= (FileManager::tileInfo + i)->rcTile.left && yGap >= xGap)
                    {
                        tank->SetPos(FPOINT{ tank->GetPos().x - xGap, tank->GetPos().y });
                    }
                    else if (tank->GetPos().x >= (FileManager::tileInfo + i)->rcTile.right && yGap >= xGap)
                    {
                        tank->SetPos(FPOINT{ tank->GetPos().x + xGap, tank->GetPos().y });
                    }
                    else if (tank->GetPos().y <= (FileManager::tileInfo + i)->rcTile.top && yGap <= xGap)
                    {
                        tank->SetPos(FPOINT{ tank->GetPos().x, tank->GetPos().y - yGap });
                    }
                    else if (tank->GetPos().y >= (FileManager::tileInfo + i)->rcTile.bottom && yGap <= xGap)
                    {
                        tank->SetPos(FPOINT{ tank->GetPos().x, tank->GetPos().y + yGap });
                    }
                }
            }        
        }
        else  if ((FileManager::tileInfo + i)->type == TILE_TYPE::ICE_TILE)
        {
            for (Tank* tank : *vTankStorage)
            {
                if (tank->GetAlive())
                {
                    if (IntersectRect(&tmpRect, &((FileManager::tileInfo + i)->rcTile), &(tank->GetShape())))
                    {
                        //TODO ��ũ�� �̲������� ó��
                        tank->ChangeIntoSlipperyState();
                    }
                }
            }
        }
        else  if ((FileManager::tileInfo + i)->type == TILE_TYPE::ROAD_TILE || (FileManager::tileInfo + i)->type == TILE_TYPE::GRASS_TILE)
        {
            for (Tank* tank : *vTankStorage)
            {
                if (tank->GetAlive())
                {
                    if (IntersectRect(&tmpRect, &((FileManager::tileInfo + i)->rcTile), &(tank->GetShape())))
                    {
                        float xGap = abs(tmpRect.right - tmpRect.left);
                        float yGap = abs(tmpRect.bottom - tmpRect.top);
                        if(xGap >= tank->GetSize()/2 && yGap >= tank->GetSize()/2){
                            //TODO ��ũ�� ���߰� ó��
                            tank->ChangeIntoNormalState();
                        }
                    }
                }
            }
        }
    }
}

//�̻��� vs Ÿ�� �浹 üũ
void CollisionManager::CheckMissileTileCollision()
{
    for (int i = 0; i < TILE_X * TILE_Y; i++) {
        if ( (FileManager::tileInfo + i)->type == TILE_TYPE::BRICK_TILE || (FileManager::tileInfo + i)->type == TILE_TYPE::WALL_TILE || (FileManager::tileInfo + i)->type == TILE_TYPE::COMMAND_CENTER_TILE)
        {
            for (auto mMissilePair : mMissileStorage)
            {
                for (auto lpMissile : *mMissilePair.second)
                {
                    if (lpMissile->GetIsFired() && IntersectRect(&tmpRect, &lpMissile->GetShape(), &(FileManager::tileInfo + i)->rcTile) )
                    {
                        if( (FileManager::tileInfo + i)->type == TILE_TYPE::BRICK_TILE )
                        {
                            (FileManager::tileInfo + i)->type = TILE_TYPE::ROAD_TILE;
                            (FileManager::tileInfo + i)->frameX = 0;
                            (FileManager::tileInfo + i)->frameY = 0;
                        }
                        lpMissile->SetIsFired(false);
                        AddCollisionBuffer(FPOINT{ lpMissile->GetPos().x, lpMissile->GetPos().y });
                    }
                }
            }
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
    for(const auto& collisionData : collisionBuffer)
    {
        if(collisionData.explosionType == EXPLOSION_TYPE::SMALL_EXPLOSION)
            boomEffect->FrameRender(hdc, collisionData.pos.x, collisionData.pos.y, collisionData.currFrame.x, collisionData.currFrame.y, true);
        if (collisionData.explosionType == EXPLOSION_TYPE::HUGE_EXPLOSION)
            bigBoomEffect->FrameRender(hdc, collisionData.pos.x, collisionData.pos.y, collisionData.currFrame.x, collisionData.currFrame.y, true);
    }
}

void CollisionManager::Release()
{
    ReleaseSingleton();
}


