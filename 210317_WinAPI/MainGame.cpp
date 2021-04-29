#include "MainGame.h"
#include "Image.h"
#include "BattleScene.h"
#include "MenuScene.h"
#include "LoadingScene.h"
#include "TileMapTool.h"
#include "SceneManager.h"
#include <ctime>

HRESULT MainGame::Init()
{
	srand(time(NULL));
	hdc = GetDC(g_hWnd);

	KeyManager::GetSingleton()->Init();
	ImageManager::GetSingleton()->Init();

	// 이미지를 미리 로드한다
	ImageManager::GetSingleton()->AddImage("Tank",
		"Image/Enemy/Enemy.bmp", 512, 384, 8, 6,
		true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage("MissileDown",
		"Image/Bullet/Missile_Down.bmp", 3, 4, 1, 1,
		true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("MissileUp",
		"Image/Bullet/Missile_Up.bmp", 3, 4, 1, 1,
		true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("MissileLeft",
		"Image/Bullet/Missile_Left.bmp", 4, 3, 1, 1,
		true, RGB(255, 0, 255));
	ImageManager::GetSingleton()->AddImage("MissileRight",
		"Image/Bullet/Missile_Right.bmp", 4, 3, 1, 1,
		true, RGB(255, 0, 255));

	// 메인게임의 초기화 함수
	//hTimer = (HANDLE)SetTimer(g_hWnd, 0, 1, NULL);

	int maxWidth, maxHeight;
	maxWidth = max(WINSIZE_X, TILEMAPTOOLSIZE_X);
	maxHeight = max(WINSIZE_Y, TILEMAPTOOLSIZE_Y);

	// 백버퍼 이미지
	backBuffer = new Image();
	backBuffer->Init(maxWidth, maxHeight);

	ImageManager::GetSingleton()->AddImage(
		"샘플타일", "Image/SamlpTile2.bmp", (512), (64),        //128 16
		SAMPLE_TILE_X, SAMPLE_TILE_Y, true, RGB(255, 0, 255));

	ImageManager::GetSingleton()->AddImage(
		"전투배경", "Image/loadImage.bmp", (1024), (968),        //128 16
		SAMPLE_TILE_X+200, SAMPLE_TILE_Y+200);

	SceneManager::GetSingleton()->AddScene("BattleScene", new BattleScene());
	SceneManager::GetSingleton()->AddScene("MenuScene", new MenuScene());
	SceneManager::GetSingleton()->AddScene("LoadingScene", new LoadingScene());
	SceneManager::GetSingleton()->AddScene("TileMapTool", new TileMapTool());

	SceneManager::GetSingleton()->ChangeScene("MenuScene");

	isInited = true;

	return S_OK;
}

void MainGame::Release()
{
	SceneManager::GetSingleton()->Release();
	KeyManager::GetSingleton()->Release();
	ImageManager::GetSingleton()->Release();

	SAFE_RELEASE(backBuffer);

	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
	SceneManager::GetSingleton()->Update();
}

void MainGame::Render()
{
	HDC hBackDC = backBuffer->GetMemDC();//TODO 씬분리
	
	SceneManager::GetSingleton()->Render(hBackDC);

	// 인사
	TextOut(hBackDC, 20, 20, "MainGame 렌더 중", strlen("MainGame 렌더 중"));
	// 마우스 좌표
	wsprintf(szText, "X : %d, Y : %d", g_ptMouse.x, g_ptMouse.y);
	TextOut(hBackDC, 200, 20, szText, strlen(szText));
	// FPS
	TimerManager::GetSingleton()->Render(hBackDC);

	backBuffer->Render(hdc);
}



LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
	isInited = false;
}

MainGame::~MainGame()
{
}
