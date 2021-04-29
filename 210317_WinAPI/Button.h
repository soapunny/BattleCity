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
	//void (*func_pointer)(int); //�Լ� ������ ����

public:
	HRESULT Init(const char* fileName, int posX, int posY);
	virtual HRESULT Init();			// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();			// �޸� ����
	virtual void Update();			// ������ ������ ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ������ ��� (�̹���, �ؽ�Ʈ ��)

	void SetFunc(func_t func, int funcArg)
	{
		this->func = func; this->func_arg = funcArg;
	}
	//void SetFunc(void (*func_t)(int)) { this->func_t = func_t; }

	virtual ~Button() {};
};
