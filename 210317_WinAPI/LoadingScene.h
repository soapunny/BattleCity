#pragma once
#include "GameNode.h"

class Image;
class LoadingScene : public GameNode
{
private:
	Image* loadScene;
	Image* stageImg;
	Image* stageNum;

	float loadingTimer;
public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

