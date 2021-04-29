#include "TankManager.h"
#include "TankFactory.h"
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
    }
    CreateEnemyTank(STAGE_TYPE(currStage));
}

void TankManager::Render(HDC hdc)
{
    for (int i = 0; i < vTanks.size(); i++)
    {
        if (vTanks[i]->GetAlive())
            vTanks[i]->Render(hdc);
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
                    break;
                }
            }
            createTimer = 0.0f;

        }
    }
}
