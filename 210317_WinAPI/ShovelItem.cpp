#include "ShovelItem.h"

HRESULT ShovelItem::Init() //일정시간 동안 사령부 주변의 벽이 회색 블록으로 변하며, 
						   //시간경과 후엔 사령부 주변의 벽도 회복된다. 
{
	img = ImageManager::GetSingleton()->FindImage("ShovelItem"); 

	pos.x = 0;
	pos.y = 0;
	isActivated = false;
	isInitialized = false; // 랜덤 값이 부여가가 됐는지 확인 
	timer = 0.0f;
	itemType = ITEM_TYPE::SHOVEL_ITEM;

	return S_OK;
}
