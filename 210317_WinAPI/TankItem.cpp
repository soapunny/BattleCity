#include "TankItem.h"

HRESULT TankItem::Init()
{
	img = ImageManager::GetSingleton()->FindImage("TankItem"); // 탱크가 강화한다.

	pos.x = 0;
	pos.y = 0;
	isActivated = false;
	isInitialized = false; // 랜덤 값이 부여가가 됐는지 확인 
	timer = 0.0f;
	itemType = ITEM_TYPE::TANK_ITEM;

	return S_OK;
}
