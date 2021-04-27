#pragma once

class Tank;
enum TANK_TYPE;
class TankFactory
{
public:
	virtual Tank* CreateTank(TANK_TYPE tankType);
};

