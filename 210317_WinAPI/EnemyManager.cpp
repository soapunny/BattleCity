#include "EnemyManager.h"
#include "Enemy.h"

HRESULT EnemyManager::Init()
{
    // 1) �迭
    //Enemy* enemys = new Enemy[10];
    //for (int i = 0; i < 10; i++)
    //{
    //    enemys[i].Init();
    //}

    // TODO : emplace_back() ���� ����
    // 2) vector push_back()
    //for (int i = 0; i < 10; i++)
    //{
    //    vEnemys.push_back(new Enemy());
    //    vEnemys[i]->Init();
    //}

    // 3) vector resize()
    vEnemys.resize(10);
    for (int i = 0; i < 10; i++)
    {
        //vEnemys.push_back(new Enemy());
        vEnemys[i] = new Enemy();
        vEnemys[i]->Init(150 + (i % 5) * 200, 100 + (i / 5) * 500);
    }


    //// 4) vector reserve()
    //vEnemys.reserve(10);
    //for (int i = 0; i < 10; i++)
    //{
    //    vEnemys.push_back(new Enemy());
    //    vEnemys[i]->Init();
    //}


    return S_OK;
}

void EnemyManager::Release()
{
    // �ݺ���(iterator) : STL �ڷᱸ���� �����ϴ� ������ �޸𸮸� �����ϴ� ��ü
    vector<Enemy*>::iterator it;
    for (it = vEnemys.begin(); it != vEnemys.end(); it++)
    {
        (*it)->Release();   // (*it) -> Enemy* ������Ÿ��Ȯ��
        delete (*it);
        (*it) = nullptr;
    }
}

void EnemyManager::Update()
{
    vector<Enemy*>::iterator it;
    for (it = vEnemys.begin(); it != vEnemys.end(); it++)
    {
        (*it)->Update();
    }
}

void EnemyManager::Render(HDC hdc)
{
    vector<Enemy*>::iterator it;
    for (it = vEnemys.begin(); it != vEnemys.end(); it++)
    {
        (*it)->Render(hdc);
    }
}

void EnemyManager::AddEnemy(int size)
{
    for (int i = 0; i < size; i++)
    {
        vEnemys.push_back(new Enemy());
        vEnemys[vEnemys.size() - 1]->Init();
    }
}
