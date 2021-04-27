#include "GrenadeItem.h"

HRESULT GrenadeItem::Init() // 수류탄 : 화면상의 적 탱크를 전멸시킨다.
{
	// 이미지 저장
	img = ImageManager::GetSingleton()->FindImage("GrenadeItem");

	pos.x = 0;
	pos.y = 0;
	isActivated = false;
	isInitialized = false; // 랜덤 값이 부여가가 됐는지 확인 
	timer = 0.0f;
	itemType = ITEM_TYPE::GRENADE_ITEM;

	return S_OK;
}


