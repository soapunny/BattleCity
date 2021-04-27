#include "WatchItem.h"

HRESULT WatchItem::Init()
{
	img = ImageManager::GetSingleton()->FindImage("WatchItem"); // �����ð� ���� �����.

	pos.x = 0;
	pos.y = 0;
	isActivated = false;
	isInitialized = false; // ���� ���� �ο����� �ƴ��� Ȯ�� 
	timer = 0.0f;
	itemType = ITEM_TYPE::WATCH_ITEM;

	return S_OK;
}
