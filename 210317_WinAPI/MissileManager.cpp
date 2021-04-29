#include "MissileManager.h"
#include "Missile.h"

HRESULT MissileManager::Init(PLAYER_TYPE playerType)
{
    currMissileCnt = 1;
    maxMissileCnt = 2;
    vMissiles.resize(maxMissileCnt);
    for (int i = 0; i < vMissiles.size(); i++)
    {
        vMissiles[i] = new Missile();
        vMissiles[i]->Init(playerType);
    }

    return S_OK;
}

void MissileManager::Release()
{
    for (auto lpMissile : vMissiles)
    {
        SAFE_RELEASE(lpMissile);
    }
}

void MissileManager::Update()
{
    for (int i = 0; i < currMissileCnt; i++)
    {
        if (vMissiles[i]->GetIsFired())
        {
            vMissiles[i]->Update();
        }
    }
}

void MissileManager::Render(HDC hdc)
{
    for (int i = 0; i < currMissileCnt; i++)
    {
        if(vMissiles[i]->GetIsFired())
        { 
            vMissiles[i]->Render(hdc);
        }
    }
}

void MissileManager::Fire(FPOINT startPos, float angle, MOVE_DIRECTION moveDirection)
{
    for (int i = 0; i < currMissileCnt; i++)
    {
        if (! (vMissiles[i]->GetIsFired()))
        {
            vMissiles[i]->SetIsFired(true);
            vMissiles[i]->SetPos(startPos);
            vMissiles[i]->SetAngle(angle);
            vMissiles[i]->SetMoveDirection(moveDirection);
            break;
        }
    }
}
