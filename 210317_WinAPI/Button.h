#pragma once
#include "GameNode.h"

/*
	�Լ� ������

	�Լ�(����) ������ : �Լ�(����)�� �޸� �ּҸ� ���� �� �ִ�(������ ������) ����
	�Լ��� �̸��� �Լ��� �޸� �ּ��̴�.

	int a = 10;
	int* pA = &a;

	void Sum(int a, int b);

	void (*funcPointer)(int, int); //�Լ� ������(����) ����, ������ Ÿ���� �׻� ���� �����ش�.
	funcPointer = Sum;
	Sum(10, 20);
	funcPointer(10, 20);

	void Print(void);

	void (*funcPrint)(void);
	funcPrint = Print;			//�Լ�������(����) = �Լ� �ּ�
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
	//void (*func_pointer)(int); //�Լ� ������ ����

public:
	HRESULT Init(const char* fileName, int posX, int posY, POINT frameInfo = POINT{ 0, 0 }, string inputStr = "");
	virtual HRESULT Init();			// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();			// �޸� ����
	virtual void Update();			// ������ ������ ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ������ ��� (�̹���, �ؽ�Ʈ ��)

	void SetFunc(func_pointer func_p, int func_arg) { this->func_p = func_p; this->func_arg = func_arg; }

	virtual ~Button() {}
};