#include "HelmetItem.h"

HRESULT HelmetItem::Init() // 헬멧 : 일정 시간 동안 마이 탱크의 주변에 배리어가 쳐진 무적 상태가 된다.
{
	img = ImageManager::GetSingleton()->FindImage("HelmetItem");

	pos.x = 0;
	pos.y = 0;
	isActivated = false;
	isInitialized = false; // 랜덤 값이 부여가가 됐는지 확인 
	timer = 0.0f;
	itemType = ITEM_TYPE::HELMET_ITEM;

	return S_OK;
}
