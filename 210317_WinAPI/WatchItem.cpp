#include "WatchItem.h"

HRESULT WatchItem::Init()
{
	img = ImageManager::GetSingleton()->FindImage("WatchItem"); // 일정시간 적이 멈춘다.

	pos.x = 0;
	pos.y = 0;
	isActivated = false;
	isInitialized = false; // 랜덤 값이 부여가가 됐는지 확인 
	timer = 0.0f;
	itemType = ITEM_TYPE::WATCH_ITEM;

	return S_OK;
}
