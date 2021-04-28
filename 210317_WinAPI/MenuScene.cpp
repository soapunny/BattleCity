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
		switch (selectNum)
		{
		case P2:
			selectNum = P1;
			break;
		case CONSTRUCTION:
			selectNum = P2;
			break;
		}
	}
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_DOWN))
	{	
		switch (selectNum)
		{
		case P1:
			selectNum = P2;
			break;
		case P2:
			selectNum = CONSTRUCTION;
			break;
		}
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RETURN))
	{
		if (selectNum == P1)
		{
			SceneManager::GetSingleton()->ChangeScene("LoadingScene");
		}

		if (selectNum == CONSTRUCTION)
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
		selectIcon->Render(hdc, 320, 405 + selectNum * 53);
	}
}

// 아이콘 성공하고나서
// 3번째거 엔터시에 맵 수정하는곳