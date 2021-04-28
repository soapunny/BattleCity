#include "LoadingScene.h"
#include "Image.h"
#include "SceneManager.h"

HRESULT LoadingScene::Init()
{
	loadScene = new Image();
	loadScene->Init("Image/loadImage.bmp", WINSIZE_X, WINSIZE_Y);

	
	stageImg = new Image();
	stageImg->Init("Image/Stage.bmp", 60, 30);

	
	stageNum = new Image();
	stageNum->Init("Image/Number.bmp", 40, 14);

	return S_OK;
}

void LoadingScene::Release()
{
	SAFE_RELEASE(stageImg);
	SAFE_RELEASE(loadScene);	
	SAFE_RELEASE(stageNum);
}

void LoadingScene::Update()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_RETURN))
	{
		SceneManager::GetSingleton()->ChangeScene("BattleScene");
	}
}

void LoadingScene::Render(HDC hdc)
{
	if (loadScene)
	{
		loadScene->Render(hdc);
	}

	if (stageImg)
	{
		stageImg->Render(hdc, WINSIZE_X / 2 - 50, WINSIZE_Y / 2);
	}

	if (stageNum)
	{
		stageNum->FrameRender(hdc, WINSIZE_X / 2 + 50, WINSIZE_Y / 2,
			1, 1, false);
	}
}
