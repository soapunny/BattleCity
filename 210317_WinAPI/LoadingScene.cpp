#pragma once
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
	SAFE_RELEASE(loadScene);
	SAFE_RELEASE(stageImg);
	SAFE_RELEASE(stageNum);
}

void LoadingScene::Update()
{
	loadingTimer += TimerManager::GetSingleton()->GetElapsedTime();

	if (loadingTimer >= 3.0f)
	{
		SceneManager::GetSingleton()->ChangeScene("BattleScene");
		loadingTimer = 0.0f;
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
