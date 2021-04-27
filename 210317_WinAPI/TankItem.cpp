#include "TankItem.h"

HRESULT TankItem::Init()
{
	img = ImageManager::GetSingleton()->FindImage("TankItem"); // ��ũ�� ��ȭ�Ѵ�.

	pos.x = 0;
	pos.y = 0;
	isActivated = false;
	isInitialized = false; // ���� ���� �ο����� �ƴ��� Ȯ�� 
	timer = 0.0f;
	itemType = ITEM_TYPE::TANK_ITEM;

	return S_OK;
}
