#include "StarItem.h"

HRESULT StarItem::Init()
{
	img = ImageManager::GetSingleton()->FindImage("StarItem"); //���� ��ũ�� ��ȭ�ȴ�. ��� �� �ӻ���(2����) 
															   //�� ���� ��ũ(2���� + �ı��� ���� + ȸ�� ��� �ı�).

	pos.x = 0;
	pos.y = 0;
	isActivated = false;
	isInitialized = false; // ���� ���� �ο����� �ƴ��� Ȯ�� 
	timer = 0.0f;
	itemType = ITEM_TYPE::STAR_ITEM;

	return S_OK;
}
