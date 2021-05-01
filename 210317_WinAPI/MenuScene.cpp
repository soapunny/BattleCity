#include "MenuScene.h"
#include "Image.h"
#include "SceneManager.h"

HRESULT MenuScene::Init()
{
	menuScene = new Image();
	menuScene->Init("Image/Title.bmp", WINSIZE_X, WINSIZE_Y);

	selectIcon = new Image();
	selectIcon->Init("Image/selectIcon.bmp", 30, 30);

	g_currentMenu = MENU::P1;

	return S_OK;
}

void MenuScene::Release()
{
	SAFE_RELEASE(selectIcon);
	SAFE_RELEASE(menuScene);
}

void MenuScene::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_UP))
	{	
		switch (g_currentMenu)
		{
		case P2:
			g_currentMenu = MENU::P1;
			break;
		case CONSTRUCTION:
			g_currentMenu = MENU::P2;
			break;
		}
	}
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_DOWN))
	{	
		switch (g_currentMenu)
		{
		case P1:
			g_currentMenu = MENU::P2;
			break;
		case P2:
			g_currentMenu = MENU::CONSTRUCTION;
			break;
		}
	}

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RETURN))
	{
		if (g_currentMenu == MENU::P1)
		{
			SceneManager::GetSingleton()->ChangeScene("LoadingScene");
		}
		else if (g_currentMenu == MENU::P2)
		{
			SceneManager::GetSingleton()->ChangeScene("LoadingScene");
		}
		else if (g_currentMenu == MENU::CONSTRUCTION)
		{
			SceneManager::GetSingleton()->ChangeScene("TileMapTool");
		}
	}
}

void MenuScene::Render(HDC hdc)
{
	if (menuScene)
	{
		PatBlt(hdc, 0, 0,
			TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y, WHITENESS);
		menuScene->Render(hdc);
	}

	if (selectIcon)
	{
		selectIcon->Render(hdc, 320, 405 + (g_currentMenu * 53));
	}
}

// 아이콘 성공하고나서
// 3번째거 엔터시에 맵 수정하는곳