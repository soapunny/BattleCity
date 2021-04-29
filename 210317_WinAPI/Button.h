#pragma once
#include "GameNode.h"

/*
	함수 포인터

	함수(변수) 포인터 : 함수(변수)의 메모리 주소를 담을 수 있는(값으로 가지는) 변수
	함수의 이름이 함수의 메모리 주소이다.

	int a = 10;
	int* pA = &a;

	void Sum(int a, int b);

	void (*funcPointer)(int, int); //함수 포인터(변수) 선언, 데이터 타입은 항상 같게 맞춰준다.
	funcPointer = Sum;
	Sum(10, 20);
	funcPointer(10, 20);

	void Print(void);

	void (*funcPrint)(void);
	funcPrint = Print;			//함수포인터(변수) = 함수 주소
	funcPrint();
*/

typedef	void (*func_pointer)(int);

enum class BUTTON_STATE { 
	BUTTON_NONE, 
	BUTTON_DOWN,
	BUTTON_UP
};

class Image;
class Button : public GameNode
{
private:
	BUTTON_STATE state;
	Image* image;
	RECT rc;
	POINT pos;
	POINT frameInfo;

	string inputStr;

	int func_arg;
	func_pointer func_p;
	//void (*func_pointer)(int); //함수 포인터 변수

public:
	HRESULT Init(const char* fileName, int posX, int posY, POINT frameInfo = POINT{ 0, 0 }, string inputStr = "");
	virtual HRESULT Init();			// 멤버 변수의 초기화, 메모리 할당
	virtual void Release();			// 메모리 해제
	virtual void Update();			// 프레임 단위로 게임 로직 실행 (데이터 변동)
	virtual void Render(HDC hdc);	// 프레임 단위로 출력 (이미지, 텍스트 등)

	void SetFunc(func_pointer func_p, int func_arg) { this->func_p = func_p; this->func_arg = func_arg; }

	virtual ~Button() {}
};