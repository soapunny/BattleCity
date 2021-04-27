#pragma once
#include "ItemManager.h"
class Item : public ItemManager
{
protected:
	
	enum ITEM_TYPE { STAR_ITEM, GRENADE_ITEM, SHOVEL_ITEM, WATCH_ITEM, HELMET_ITEM, TANK_ITEM, TWO_SHOT_ITEM, END_ITEM_TYPE };
	
	bool isActivated;
	bool isInitialized;
	float timer;
	POINT pos;
	ITEM_TYPE itemType;
	
	Image* img;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);
};

