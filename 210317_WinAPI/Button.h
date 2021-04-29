#pragma once
#include "GameNode.h"

enum class BUTTON_STATE { 
	BUTTON_NONE, 
	BUTTON_DOWN,
	BUTTON_UP
};

typedef void (*func_t)(int);

class Image;
class Button : public GameNode
{
private:
	BUTTON_STATE state;
	Image* image;
	RECT rc;
	POINT pos;
	POINT frameInfo;

	int func_arg;
	func_t func;
	//void (*func_pointer)(int); //함수 포인터 변수

public:
	HRESULT Init(const char* fileName, int posX, int posY);
	virtual HRESULT Init();			// 멤버 변수의 초기화, 메모리 할당
	virtual void Release();			// 메모리 해제
	virtual void Update();			// 프레임 단위로 게임 로직 실행 (데이터 변동)
	virtual void Render(HDC hdc);	// 프레임 단위로 출력 (이미지, 텍스트 등)

	void SetFunc(func_t func, int funcArg)
	{
		this->func = func; this->func_arg = funcArg;
	}
	//void SetFunc(void (*func_t)(int)) { this->func_t = func_t; }

	virtual ~Button() {};
};
