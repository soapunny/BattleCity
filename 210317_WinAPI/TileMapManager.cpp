#include "TileMapManager.h"
#include "TileMap.h"

HRESULT TileMapManager::Init()
{
	vTileMaps.push_back(new TileMap());
	vTileMaps[0]->Init(); 

	return S_OK;
}

void TileMapManager::Release()
{
    vector<TileMap*>::iterator it;
    for (it = vTileMaps.begin(); it != vTileMaps.end(); it++)
    {
        (*it)->Release();  
        delete (*it);
        (*it) = nullptr;
    }
}

void TileMapManager::Update()
{
    vector<TileMap*>::iterator it;
    for (it = vTileMaps.begin(); it != vTileMaps.end(); it++)
    { 
        (*it)->Update();
    }
}

void TileMapManager::Render(HDC hdc)
{
    vector<TileMap*>::iterator it;
    for (it = vTileMaps.begin(); it != vTileMaps.end(); it++)
    {
        (*it)->Render(hdc);
    }
}
