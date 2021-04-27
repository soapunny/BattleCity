#include "BattleScene.h"
#include "TankManager.h"
#include "Missile.h"
#include "Image.h"


HRESULT BattleScene::Init()
{
	bin = new Image();
	bin->Init("Image/backGround_01.bmp", WINSIZE_X, WINSIZE_Y);

	tankManager = new TankManager();
	tankManager->Init();

	return S_OK;
}

void BattleScene::Release()
{
	SAFE_RELEASE(bin);
	SAFE_RELEASE(tankManager);
}

void BattleScene::Update()
{
	if (tankManager)
	{
		tankManager->Update();
	}

	float currTime1 = TimerManager::GetSingleton()->GetCurrTime();
}

void BattleScene::Render(HDC hdc)
{
	if (bin)
	{
		bin->Render(hdc/*, -100, 100*/);
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