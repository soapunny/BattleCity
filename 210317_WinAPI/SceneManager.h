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
	

	HRESULT Init();			// 멤버 변수의 초기화, 메모리 할당
	void Release();			// 메모리 해제
	void Update();			// 프레임 단위로 게임 로직 실행 (데이터 변동)
	void Render(HDC hdc);	// 프레임 단위로 출력 (이미지, 텍스트 등)

	GameNode* AddScene(string key, GameNode* scene);
	HRESULT ChangeScene(string key);
};

