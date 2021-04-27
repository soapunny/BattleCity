#include "GrenadeItem.h"

HRESULT GrenadeItem::Init() // ����ź : ȭ����� �� ��ũ�� �����Ų��.
{
	// �̹��� ����
	img = ImageManager::GetSingleton()->FindImage("GrenadeItem");

	pos.x = 0;
	pos.y = 0;
	isActivated = false;
	isInitialized = false; // ���� ���� �ο����� �ƴ��� Ȯ�� 
	timer = 0.0f;
	itemType = ITEM_TYPE::GRENADE_ITEM;

	return S_OK;
}


