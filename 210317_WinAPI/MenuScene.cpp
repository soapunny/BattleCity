#include "MenuScene.h"
#include "Image.h"
#include "SceneManager.h"

HRESULT MenuScene::Init()
{
	menuScene = new Image();
	menuScene->Init("Image/Title.bmp", WINSIZE_X, WINSIZE_Y);

	selectIcon = new Image();
	selectIcon->Init("Image/selectIcon.bmp", 30, 30);

	selectNum = 0;
	moveIcon = 0;

	return S_OK;
}

void MenuScene::Release()
{
	SAFE_RELEASE(selectIcon);
	SAFE_RELEASE(menuScene);
}

void MenuScene::Update()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_UP))
	{
		selectNum = 0;
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{	
		selectNum = 2;
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RETURN))
	{
		if (moveIcon == 106)
		{
			SceneManager::GetSingleton()->ChangeScene("TileMapTool");
		}
	}
}

void MenuScene::Render(HDC hdc)
{
	if (menuScene)
	{
		menuScene->Render(hdc);
	}

	if (selectIcon)
	{
		if (selectNum == 1) moveIcon = 53;
		if (selectNum == 2) moveIcon = 106;

		selectIcon->Render(hdc, 320, 405 + moveIcon/*(selectNum * 53)*/);
	}
}

// 아이콘 성공하고나서
// 3번째거 엔터시에 맵 수정하는곳