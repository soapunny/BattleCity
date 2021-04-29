#include "Button.h"
#include "Image.h"
#include "TileMapTool.h"

/*
	�ǽ�1. ��ư �̹����� ���̺�, �ε忡 �°� ����
	�ǽ�2. ���������� ��ȯ�� �� �ִ� ��ư�� �߰��� ����
	�ǽ�3. �߰��� ��ư(�������� ��ȯ)�� ���� �����ϵ��� �ڵ� ����
*/

HRESULT Button::Init(const char* fileName, int posX, int posY, POINT frameInfo, string inputStr)
{
	
	this->inputStr = inputStr;
	
	this->frameInfo = frameInfo;
	state = BUTTON_STATE::BUTTON_NONE;
	image = ImageManager::GetSingleton()->FindImage(fileName);
	//image = ImageManager::GetSingleton()->AddImage("��ư", "Image/button.bmp", 122, 62, 1, 2);
	if (image == nullptr)
	{
		string warningText = string(fileName) + "�� ���� ���� �ʽ��ϴ�";
		MessageBox(g_hWnd, warningText.c_str(), "���", MB_OK);
	}

	pos.x = posX;
	pos.y = posY;

	rc.left = pos.x - image->GetFrameWidth()/2;
	rc.top = pos.y - image->GetFrameHeight()/2;
	rc.right = rc.left + image->GetFrameWidth();
	rc.bottom = rc.top + image->GetFrameHeight();

	func_p = nullptr; // TileMapTool::Save;


	return S_OK;
}

HRESULT Button::Init()
{
	return E_FAIL;
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
		else if (state == BUTTON_STATE::BUTTON_DOWN && KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
		{
			state = BUTTON_STATE::BUTTON_UP;

			//��ư ��� ���� : ���̺�, �ε�
			func_p(func_arg);
		}
	}
	else
	{
		state = BUTTON_STATE::BUTTON_NONE;
	}
}

void Button::Render(HDC hdc)
{
	SetBkMode(hdc, TRANSPARENT);
	switch (state)
	{
	case BUTTON_STATE::BUTTON_NONE:
	case BUTTON_STATE::BUTTON_UP:
		image->FrameRender(hdc, pos.x, pos.y, image->GetFrameWidth(), image->GetFrameHeight(), frameInfo.x, 0, frameInfo.x, 0, true);
		if(inputStr != "") TextOut(hdc, pos.x - image->GetFrameWidth()/2, pos.y, inputStr.c_str(), inputStr.length());
		break;
	case BUTTON_STATE::BUTTON_DOWN:
		image->FrameRender(hdc, pos.x, pos.y, image->GetFrameWidth(), image->GetFrameHeight(), frameInfo.x, 1, frameInfo.x, 1, true);
		if (inputStr != "") TextOut(hdc, pos.x - image->GetFrameWidth() / 2, pos.y, inputStr.c_str(), inputStr.length());
		break;
	}
}
