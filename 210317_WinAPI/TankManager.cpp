#include "TankManager.h"
#include "TankFactory.h"
#include "MissileManager.h"
#include "CollisionManager.h"
#include "Tank.h"


HRESULT TankManager::Init()
{
    maxTankSize = 5;
    vTanks.resize(maxTankSize * Tank::TANK_TYPE::END_TANK_TYPE);

    tankFactory = new TankFactory();
    for (int i = 0; i < vTanks.size(); i++)
    {
        vTanks[i] = tankFactory->CreateTank((TANK_TYPE)(i / maxTankSize));
        vTanks[i]->Init();
    }


    vTanks[Tank::TANK_TYPE::GREEN_TANK * maxTankSize]->SetAlive(true); //첫번째 플레이어
    vTanks[Tank::TANK_TYPE::GREEN_TANK * maxTankSize]->SetPlayerType(PLAYER_TYPE::FIRST_PLAYER);

    CollisionManager::GetSingleton()->AddMissiles(vTanks[Tank::TANK_TYPE::GREEN_TANK * maxTankSize]->GetName()
        , vTanks[Tank::TANK_TYPE::GREEN_TANK * maxTankSize]->GetMissileManager()->GetVMissiles());

    //2인 플레이일 경우
    if(g_currentMenu == MENU::P2){
        vTanks[Tank::TANK_TYPE::YELLOW_TANK * maxTankSize]->SetAlive(true); //두번째 플레이어
        vTanks[Tank::TANK_TYPE::YELLOW_TANK * maxTankSize]->SetPlayerType(PLAYER_TYPE::SECOND_PLAYER);

        CollisionManager::GetSingleton()->AddMissiles(vTanks[Tank::TANK_TYPE::YELLOW_TANK * maxTankSize]->GetName()
            , vTanks[Tank::TANK_TYPE::YELLOW_TANK * maxTankSize]->GetMissileManager()->GetVMissiles());
    }

    CollisionManager::GetSingleton()->RegisterVTank(&vTanks);//탱크들 CollisionManager에 저장

    createTimer = 0.0f;
    return S_OK;
}

void TankManager::Release()
{
    for (int i = 0; i < vTanks.size(); i++)
    {
        SAFE_RELEASE(vTanks[i]);
    }
    vTanks.clear();

    delete tankFactory;
}

void TankManager::Update(int currStage)
{
    for (int i = 0; i < vTanks.size(); i++)
    {
        if(vTanks[i]->GetAlive())
            vTanks[i]->Update();
        if (vTanks[i]->GetMissileManager())
            vTanks[i]->GetMissileManager()->Update();
    }
    CreateEnemyTank(STAGE_TYPE(currStage));
}

void TankManager::Render(HDC hdc)
{
    for (int i = 0; i < vTanks.size(); i++)
    {
        if (vTanks[i]->GetAlive())
            vTanks[i]->Render(hdc);
        if (vTanks[i]->GetMissileManager())
            vTanks[i]->GetMissileManager()->Render(hdc);
    }
}

void TankManager::CreateEnemyTank(STAGE_TYPE stage)
{
    createTimer += TimerManager::GetSingleton()->GetElapsedTime();

    if(stage == STAGE_TYPE::FIRST_STAGE){
        if(createTimer >= 5.0f)
        { 
            for(int i = Tank::TANK_TYPE::WHITE_TANK*5; i < Tank::TANK_TYPE::YELLOW_TANK*5; i++){
                if(! vTanks[i]->GetAlive()){
                    vTanks[i]->SetAlive(true); //테스트용으로 하나만 살려놓는다.
                    vTanks[i]->SetPlayerType(PLAYER_TYPE::ENEMY_PLAYER);
                    vTanks[i]->SetPos(FPOINT{ TILESIZE * TILE_X / 2, TILESIZE * TILE_Y / 2 });

                    CollisionManager::GetSingleton()->AddMissiles(vTanks[i]->GetName(), vTanks[i]->GetMissileManager()->GetVMissiles());
                    break;
                }
            }
            createTimer = 0.0f;

        }
    }
}
