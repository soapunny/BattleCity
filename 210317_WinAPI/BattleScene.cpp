#pragma once
#include "BattleScene.h"
#include "TankManager.h"
#include "Image.h"
#include "FileManager.h"
#include "TileMapTool.h"
#include "CollisionManager.h"

HRESULT BattleScene::Init()
{
	FileManager::GetSingleton()->Init();
	CollisionManager::GetSingleton()->Init();

	tankManager = new TankManager();
	tankManager->Init();

	stageNum = STAGE_TYPE::FIRST_STAGE;
	FileManager::GetSingleton()->LoadStage(stageNum+1);

	return S_OK;
}

void BattleScene::Release()
{
	SAFE_RELEASE(tankManager);
	FileManager::GetSingleton()->Release();
	CollisionManager::GetSingleton()->Release();
}

void BattleScene::Update()
{
	if (tankManager)
	{
		tankManager->Update(stageNum);
	}
	float currTime1 = TimerManager::GetSingleton()->GetCurrTime();

	if (FileManager::GetSingleton())
	{
		//FileManager::GetSingleton()->Update();
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
	{
		stageNum++;
		if (stageNum >= STAGE_TYPE::END_OF_STAGE_TYPE)
			stageNum = STAGE_TYPE::FIRST_STAGE;

		FileManager::GetSingleton()->LoadStage(stageNum + 1);
	}

	CollisionManager::GetSingleton()->CheckCollision();
}

void BattleScene::Render(HDC hdc)
{

	if (FileManager::GetSingleton())
	{
		//FileManager::GetSingleton()->LoadStage(stageNum);
		FileManager::GetSingleton()->Render(hdc);
	}

	if (tankManager)
	{
		tankManager->Render(hdc);
	}

	CollisionManager::GetSingleton()->Render(hdc);
}