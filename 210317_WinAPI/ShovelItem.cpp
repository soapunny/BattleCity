#include "ShovelItem.h"

HRESULT ShovelItem::Init() //�����ð� ���� ��ɺ� �ֺ��� ���� ȸ�� ������� ���ϸ�, 
						   //�ð���� �Ŀ� ��ɺ� �ֺ��� ���� ȸ���ȴ�. 
{
	img = ImageManager::GetSingleton()->FindImage("ShovelItem"); 

	pos.x = 0;
	pos.y = 0;
	isActivated = false;
	isInitialized = false; // ���� ���� �ο����� �ƴ��� Ȯ�� 
	timer = 0.0f;
	itemType = ITEM_TYPE::SHOVEL_ITEM;

	return S_OK;
}
