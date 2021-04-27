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
    if (iter != mSceneData.end())//�ش� ���� �̹� ������
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
    else if (iter->second == currentScene)//�ٲٷ��� ���� ���� ���̸�
    {
        return S_OK;
    }
    else if(SUCCEEDED(iter->second->Init()))// -> ���߿� �ε������� �ٲ������, init()�� ��
    {
        // ���� ��-> Ÿ��Ʋ��
        // �ٲ� ��-> ��Ʋ ��
        if (currentScene)
        {
            currentScene->Release();    //���� ũ�Ⱑ �ʹ� ũ�� �ڿ� ��ȯ�� �� �������, ������ ���� �޸𸮿� �÷ȴ� ���ȴٸ� �ݺ��ؼ� �ӵ��� ���ϵȴ�.
        }
        currentScene = iter->second;
        return S_OK;
    }

    return E_FAIL;
}
