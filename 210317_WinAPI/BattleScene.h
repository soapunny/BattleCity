#pragma once
#include "GameNode.h"

//기존 MainGame 클래스의 내용을 이동

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
	virtual HRESULT Init();		// 오버라이딩 : 다형성
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	virtual ~BattleScene() {}
};

