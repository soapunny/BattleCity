#include "Button.h"
#include "Image.h"
#include "TileMapTool.h"

/*
	실습1. 버튼 이미지를 세이브, 로드에 맞게 수정
	실습2. 스테이지를 전환할 수 있는 버튼을 추가로 생성
	실습3. 추가된 버튼(스테이지 전환)이 정상 동작하도록 코드 구현
*/

HRESULT Button::Init(const char* fileName, int posX, int posY, POINT frameInfo, string inputStr)
{
	
	this->inputStr = inputStr;
	
	this->frameInfo = frameInfo;
	state = BUTTON_STATE::BUTTON_NONE;
	image = ImageManager::GetSingleton()->FindImage(fileName);
	//image = ImageManager::GetSingleton()->AddImage("버튼", "Image/button.bmp", 122, 62, 1, 2);
	if (image == nullptr)
	{
		string warningText = string(fileName) + "가 존재 하지 않습니다";
		MessageBox(g_hWnd, warningText.c_str(), "경고", MB_OK);
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

			//버튼 기능 수행 : 세이브, 로드
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
