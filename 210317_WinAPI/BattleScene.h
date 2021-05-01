#pragma once
#include "GameNode.h"

//���� MainGame Ŭ������ ������ �̵�

class TankManager;
class Image;
class FileManager;
class BattleScene : public GameNode
{
private:
	Image* battleStage;
	TankManager* tankManager;

	int stageNum;

public:
	virtual HRESULT Init();		// �������̵� : ������
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual ~BattleScene() {}
};

