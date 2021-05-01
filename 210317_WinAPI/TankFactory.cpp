#pragma once
#include "TankFactory.h"
#include "YellowTank.h"
#include "WhiteTank.h"
#include "GreenTank.h"
#include "PurpleTank.h"

Tank* TankFactory::CreateTank(TANK_TYPE tankType)
{
    switch (tankType)
    {
    case Tank::TANK_TYPE::WHITE_TANK:
        return new WhiteTank();
    case Tank::TANK_TYPE::YELLOW_TANK:
        return new YellowTank();
    case Tank::TANK_TYPE::GREEN_TANK:
        return new GreenTank();
    case Tank::TANK_TYPE::PURPLE_TANK:
        return new PurpleTank();
    }

    return nullptr;
}
