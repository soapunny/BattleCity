#include "MissileManager.h"
#include "Missile.h"

HRESULT MissileManager::Init(PLAYER_TYPE playerType)
{
    maxMissileCnt = 5;
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
    for (auto lpMissile : vMissiles)
    {
        if (lpMissile->GetIsFired())
        {
            lpMissile->Update();
        }
    }
}

void MissileManager::Render(HDC hdc)
{
    for (auto lpMissile : vMissiles)
    {
        if(lpMissile->GetIsFired())
        { 
            lpMissile->Render(hdc);
        }
    }
}

void MissileManager::Fire(FPOINT startPos, float angle, MOVE_DIRECTION moveDirection)
{
    for (Missile* lpMissile : vMissiles)
    {
        if (! (lpMissile->GetIsFired()))
        {
            lpMissile->SetIsFired(true);
            lpMissile->SetPos(startPos);
            lpMissile->SetAngle(angle);
            lpMissile->SetMoveDirection(moveDirection);
            break;
        }
    }
}
