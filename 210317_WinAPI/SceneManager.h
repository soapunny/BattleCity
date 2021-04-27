#pragma once
#include "Singleton.h"
#include <Windows.h>
#include <map>
#include <string>
using namespace std;

class GameNode;
class SceneManager : public Singleton<SceneManager>
{
private:
	map<string, GameNode*> mSceneData;

public:
	static GameNode* currentScene;
	static GameNode* loadingScene;
	static GameNode* readyScene;
	

	HRESULT Init();			// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	void Release();			// �޸� ����
	void Update();			// ������ ������ ���� ���� ���� (������ ����)
	void Render(HDC hdc);	// ������ ������ ��� (�̹���, �ؽ�Ʈ ��)

	GameNode* AddScene(string key, GameNode* scene);
	HRESULT ChangeScene(string key);
};

