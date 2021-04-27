#include "StarItem.h"

HRESULT StarItem::Init()
{
	img = ImageManager::GetSingleton()->FindImage("StarItem"); //마이 탱크가 강화된다. 노멀 → 속사포(2연사) 
															   //→ 슈퍼 탱크(2연사 + 파괴력 증가 + 회색 블록 파괴).

	pos.x = 0;
	pos.y = 0;
	isActivated = false;
	isInitialized = false; // 랜덤 값이 부여가가 됐는지 확인 
	timer = 0.0f;
	itemType = ITEM_TYPE::STAR_ITEM;

	return S_OK;
}
