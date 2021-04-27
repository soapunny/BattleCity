#pragma once
#include "GameNode.h"

class Image;
class PlayerShip : public GameNode
{
private:
	Image* image;
	FPOINT pos;
	float moveSpeed;	// �ʴ� �̵��Ÿ�

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

