#include "BattleScene.h"
#include "TankManager.h"
#include "Image.h"
#include "FileManager.h"
#include "TileMapTool.h"

HRESULT BattleScene::Init()
{
	FileManager::GetSingleton()->Init();

	tankManager = new TankManager();
	tankManager->Init();

	stageNum = 1;

	return S_OK;
}

void BattleScene::Release()
{
	SAFE_RELEASE(tankManager);
	FileManager::GetSingleton()->Release();
}

void BattleScene::Update()
{
	if (tankManager)
	{
		tankManager->Update(stageNum - 1);
	}
	float currTime1 = TimerManager::GetSingleton()->GetCurrTime();

	if (FileManager::GetSingleton())
	{
		FileManager::GetSingleton()->Update();
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
	{
		stageNum++;
		if (stageNum >= 4)
			stageNum = 1;
	}


	CheckCollision();
}

void BattleScene::Render(HDC hdc)
{

	//FileManager::GetSingleton()->LoadStage(stageNum);
	if (FileManager::GetSingleton())
	{
		FileManager::GetSingleton()->LoadStage(stageNum);
		FileManager::GetSingleton()->Render(hdc);
	}

	if (tankManager)
	{
		tankManager->Render(hdc);
	}
}

void BattleScene::CheckCollision()
{
	// 利 <-> 攀农 固荤老 
	float distance;
	FPOINT enemyPos;
	FPOINT missilePos;
	float x, y;
	int r1, r2;
	//Missile* missileArray = tank->GetMissile();

	/*for (int i = 0; i < enemyCount; i++)
	{
		if (enemy[i].GetIsAlive() == false)	continue;

		for (int j = 0; j < tank->GetMissileCount(); j++)
		{
			if (missileArray[j].GetIsFired() == false)	continue;

			enemyPos = enemy[i].GetPos();
			missilePos = missileArray[j].GetPos();

			x = enemyPos.x - missilePos.x;
			y = enemyPos.y - missilePos.y;

			distance = sqrtf(x * x + y * y);

			r1 = enemy[i].GetSize() / 2;
			r2 = missileArray[j].GetSize() / 2;

			if (distance <= r1 + r2)
			{
				enemy[i].SetIsAlive(false);
				missileArray[j].SetIsFired(false);
				break;
			}
		}
	}*/

	// 利 <-> 攀农

	// 利 固荤老 <-> 攀农

	// 利 固荤老 <-> 攀农 固荤老
}