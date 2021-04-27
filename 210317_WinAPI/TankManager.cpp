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

    vTanks[15]->SetAlive(true); //테스트용으로 하나만 살려놓는다.

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

void TankManager::Update()
{
    for (int i = 0; i < vTanks.size(); i++)
    {
        if(vTanks[i]->GetAlive())
            vTanks[i]->Update();
    }
}

void TankManager::Render(HDC hdc)
{
    for (int i = 0; i < vTanks.size(); i++)
    {
        if (vTanks[i]->GetAlive())
            vTanks[i]->Render(hdc);
    }
}
