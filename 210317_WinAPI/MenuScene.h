#pragma once
#include "GameNode.h"

class Image;
class MenuScene : public GameNode
{
private:
	Image* menuScene;
	Image* selectIcon;

	int selectNum;
	int moveIcon;

public:
	HRESULT Init(); 
	void Release();
	void Update();
	void Render(HDC hdc);
};

