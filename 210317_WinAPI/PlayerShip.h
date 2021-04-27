#pragma once
#include "GameNode.h"

class Image;
class PlayerShip : public GameNode
{
private:
	Image* image;
	FPOINT pos;
	float moveSpeed;	// 초당 이동거리

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

