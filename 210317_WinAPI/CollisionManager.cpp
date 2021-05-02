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
        
        //애니메이션 프레임 계산
        ShowAnimation();

        //화면 끝에서의 미사일 충돌
        CheckMissileOut();

        //미사일과 미사일의 충돌 체크
        CheckMissileMissileCollision();

        //미사일과 탱크의 충돌 체크
        for (int i = 0; i < vTankStorage->size(); i++)//탱크 각각 돌리고
        {
            CheckMissileTankCollision(i);
        }

        //탱크와 탱크의 충돌 체크
        CheckTankTankCollision();

        //탱크와 타일의 충돌 체크
        CheckTankTileCollision();

        //미사일과 타일과의 충돌 체크
        CheckMissileTileCollision();

        //플레이어와 아이템과의 충돌 체크
    }
}

//프레임 넘기기
void CollisionManager::ShowAnimation()
{
    //충돌 애니메이션
    for (list<CollisionData>::iterator it = collisionBuffer.begin(); it != collisionBuffer.end();)
    {
        it->timer += TimerManager::GetSingleton()->GetElapsedTime();

        //작은 충돌
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
        //큰 충돌
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

//미사일 vs 외벽 충돌 체크
void CollisionManager::CheckMissileOut()
{
    vector<Missile*>* tmpVMissiles = nullptr;
    for (int i = 0; i < vTankStorage->size(); i++)
    {
        if (mMissileStorage.find((*vTankStorage)[i]->GetName()) != mMissileStorage.end())
            tmpVMissiles = mMissileStorage.at((*vTankStorage)[i]->GetName()); //미사일 더미를 이름으로 꺼내옴
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

//미사일 vs 탱크 충돌 체크
void CollisionManager::CheckMissileTankCollision(int i)
{
    if ((*vTankStorage)[i]->GetAlive()) {
        for (map<string, vector<Missile*>* >::iterator it = mMissileStorage.begin(); it != mMissileStorage.end();)
        {//미사일 더미 돌리면서
            if ((*it).first != (*vTankStorage)[i]->GetName()) {//자신의 미사일더미가 아닌 것만
                for (int j = 0; j < (*it).second->size(); j++)//각각의 미사일 백터들을 돌리면서
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
    else //미사일 맵에서 죽은 플레이어의 미사일이 수명이 다했으면 지워주기
    {
        map<string, vector<Missile*>* >::iterator it = mMissileStorage.find((*vTankStorage)[i]->GetName());
        if (it == mMissileStorage.end()) return; //해당 탱크의 미사일 더미가 미사일저장소에 올라와 있지 않으면 return
        for (auto lpMissiles : *(*it).second) {//미사일 묶음을 돌리면서
            if (lpMissiles->GetIsFired())//미사일이 하나라도 살아았으면
                return;
        }

        //미사일이 다 소멸됐으면
        mMissileStorage.erase(mMissileStorage.find((*vTankStorage)[i]->GetName()));//해당 미사일 더미 삭제
        return;
    }
}

//미사일 vs 미사일 충돌 체크
void CollisionManager::CheckMissileMissileCollision()
{
    vector<Missile*>* tmpVMissiles1 = nullptr;
    vector<Missile*>* tmpVMissiles2 = nullptr;
    for (int i = 0; i < vTankStorage->size() - 1; i++)
    {
        if (mMissileStorage.find((*vTankStorage)[i]->GetName()) != mMissileStorage.end())
            tmpVMissiles1 = mMissileStorage.at((*vTankStorage)[i]->GetName()); //미사일 더미를 이름으로 꺼내옴
        else continue;
        //map에서 미사일 백터들을 하나씩 꺼내서 비교한다.
        for (int j = i + 1; j < vTankStorage->size(); j++)
        {
            if (mMissileStorage.find((*vTankStorage)[j]->GetName()) != mMissileStorage.end())
                tmpVMissiles2 = mMissileStorage.at((*vTankStorage)[j]->GetName()); //미사일 더미를 이름으로 꺼내옴
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

//탱크 vs 탱크 충돌 체크
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

//탱크 vs 타일 충돌 체크
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
                    //TODO 탱크가 뒤로 밀려나게 처리
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
                        //TODO 탱크가 미끄러지게 처리
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
                            //TODO 탱크가 멈추게 처리
                            tank->ChangeIntoNormalState();
                        }
                    }
                }
            }
        }
    }
}

//미사일 vs 타일 충돌 체크
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


