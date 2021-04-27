#include "Item.h"

HRESULT Item::Init() // 아이템 기본 정보 
{
	return E_NOTIMPL;
}

void Item::Release()
{
}

void Item::Update()
{
	timer += TimerManager::GetSingleton()->GetElapsedTime();
	if (timer >= 10.0f)
	{
		isActivated = true;
		timer = 0.0f;
	}
	if (isActivated)
	{
		if (!isInitialized)
		{
			pos.x = rand() % TILE_X * TILE_SIZE;
			pos.y = rand() % TILE_Y * TILE_SIZE;

			isInitialized = true;
		}
	}
	else 
		isInitialized = false;
	

}

void Item::Render(HDC hdc)
{
}



