#include "SceneManager.h"
#include "GameNode.h"
#include "TileMapTool.h"

GameNode* SceneManager::currentScene = nullptr;
GameNode* SceneManager::loadingScene = nullptr;
GameNode* SceneManager::readyScene = nullptr;

HRESULT SceneManager::Init()
{
    return S_OK;
}

void SceneManager::Release()
{
    map<string, GameNode*>::iterator iter = mSceneData.begin();
    for (iter; iter != mSceneData.end(); iter++)
    {
        if (iter->second)
        {
            SAFE_RELEASE(iter->second);
        }
    }
    mSceneData.clear();

    ReleaseSingleton();
}

void SceneManager::Update()
{
    currentScene->Update();
}

void SceneManager::Render(HDC hdc)
{
    if(currentScene)
    {
        currentScene->Render(hdc);
    }
}

GameNode* SceneManager::AddScene(string key, GameNode* scene)
{
    if (scene == nullptr)
    {
        return nullptr;
    }
    map<string, GameNode*>::iterator iter = mSceneData.find(key);
    if (iter != mSceneData.end())//해당 씬이 이미 있으면
    {
        return iter->second;
    }

    //mSceneData.insert(make_pair(key, scene));
    mSceneData.insert(pair<string, GameNode*>(key, scene));
    return scene;
}

HRESULT SceneManager::ChangeScene(string key)
{
    map<string, GameNode*>::iterator iter = mSceneData.find(key);
    if (iter == mSceneData.end())
    {
        return E_FAIL;
    }
    else if (iter->second == currentScene)//바꾸려는 씬이 현재 씬이면
    {
        return S_OK;
    }
    else if(SUCCEEDED(iter->second->Init()))// -> 나중에 로딩씬으로 바꿔줘야함, init()을 함
    {
        // 현재 씬-> 타이틀씬
        // 바꿀 씬-> 배틀 씬
        if (currentScene)
        {
            currentScene->Release();    //씬의 크기가 너무 크면 자원 반환을 꼭 해줘야함, 단점은 자주 메모리에 올렸다 내렸다를 반복해서 속도가 저하된다.
        }
        currentScene = iter->second;
        return S_OK;
    }

    return E_FAIL;
}
