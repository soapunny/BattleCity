#pragma once
#include "GameNode.h"

class Image;
enum MENU { P1, P2, CONSTRUCTION };
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

