#include "TwoShotItem.h"

HRESULT TwoShotItem::Init()
{
	img = ImageManager::GetSingleton()->FindImage("TwoShotItem"); // 두발씩 쏜다.

	pos.x = 0;
	pos.y = 0;
	isActivated = false;
	isInitialized = false; // 랜덤 값이 부여가가 됐는지 확인 
	timer = 0.0f;
	itemType = ITEM_TYPE::TWO_SHOT_ITEM;

	return S_OK;
}
