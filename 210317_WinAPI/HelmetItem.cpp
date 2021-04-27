#include "HelmetItem.h"

HRESULT HelmetItem::Init() // ��� : ���� �ð� ���� ���� ��ũ�� �ֺ��� �踮� ���� ���� ���°� �ȴ�.
{
	img = ImageManager::GetSingleton()->FindImage("HelmetItem");

	pos.x = 0;
	pos.y = 0;
	isActivated = false;
	isInitialized = false; // ���� ���� �ο����� �ƴ��� Ȯ�� 
	timer = 0.0f;
	itemType = ITEM_TYPE::HELMET_ITEM;

	return S_OK;
}
