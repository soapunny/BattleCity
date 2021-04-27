#include "TwoShotItem.h"

HRESULT TwoShotItem::Init()
{
	img = ImageManager::GetSingleton()->FindImage("TwoShotItem"); // �ι߾� ���.

	pos.x = 0;
	pos.y = 0;
	isActivated = false;
	isInitialized = false; // ���� ���� �ο����� �ƴ��� Ȯ�� 
	timer = 0.0f;
	itemType = ITEM_TYPE::TWO_SHOT_ITEM;

	return S_OK;
}
