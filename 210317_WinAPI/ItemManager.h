#pragma once
#include "GameNode.h"

class Item;
class ItemManager : public GameNode
{
private:

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
	Item* CreateItem();
};

