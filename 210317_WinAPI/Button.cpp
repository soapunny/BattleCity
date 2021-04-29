#include "Button.h"
#include "Image.h"
#include "TilemapTool.h"

/*
	�ǽ�1. ��ư �̹����� ���̺�, �ε忡 �°� ����
	�ǽ�2. ���������� ������ �� �ִ� ��ư�� �߰��� ����
	�ǽ�3. �߰��� ��ư(�������� ��ȯ)�� ���� �����ϵ��� �ڵ� ����
*/

HRESULT Button::Init(const char* fileName, int posX, int posY /* ��ư ��� */)
{
	state = BUTTON_STATE::BUTTON_NONE;
	image = ImageManager::GetSingleton()->FindImage(fileName);
	if (image == nullptr)
	{
		string warningText = string(fileName) + "�� ����!!";
		MessageBox(g_hWnd, warningText.c_str(), "����", MB_OK);
		return E_FAIL;
	}

	pos.x = posX;
	pos.y = posY;

	rc.left = pos.x - image->GetFrameWidth() / 2;
	rc.top = pos.y - image->GetFrameHeight() / 2;
	rc.right = rc.left + image->GetFrameWidth();
	rc.bottom = rc.top + image->GetFrameHeight();

	func = nullptr;// TilemapTool::Save;

	return S_OK;
}

HRESULT Button::Init()
{
	return E_NOTIMPL;
}

void Button::Release()
{

}

void Button::Update()
{
	if (PtInRect(&rc, g_ptMouse))
	{
		if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
		{
			state = BUTTON_STATE::BUTTON_DOWN;
		}
		else if (state == BUTTON_STATE::BUTTON_DOWN &&
			KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
		{
			state = BUTTON_STATE::BUTTON_UP;

			// ��ư ��� ���� : ���̺�, �ε�
			func(func_arg);
		}
	}
	else
	{
		state = BUTTON_STATE::BUTTON_NONE;
	}
}

void Button::Render(HDC hdc)
{
	switch (state)
	{
	case BUTTON_STATE::BUTTON_NONE:
	case BUTTON_STATE::BUTTON_UP:
		image->FrameRender(hdc, pos.x, pos.y, 0, 0, true);
		break;
	case BUTTON_STATE::BUTTON_DOWN:
		image->FrameRender(hdc, pos.x, pos.y, 0, 1, true);
		break;
	}
}
