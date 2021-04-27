#include "TileMapManager.h"
#include "TileMapTool.h"

HRESULT TileMapManager::Init()
{
	vTileMaps.push_back(new TileMapTool());
	vTileMaps[0]->Init(); 

	return S_OK;
}

void TileMapManager::Release()
{
    vector<TileMapTool*>::iterator it;
    for (it = vTileMaps.begin(); it != vTileMaps.end(); it++)
    {
        (*it)->Release();  
        delete (*it);
        (*it) = nullptr;
    }
}

void TileMapManager::Update()
{
    vector<TileMapTool*>::iterator it;
    for (it = vTileMaps.begin(); it != vTileMaps.end(); it++)
    { 
        (*it)->Update();
    }
}

void TileMapManager::Render(HDC hdc)
{
    vector<TileMapTool*>::iterator it;
    for (it = vTileMaps.begin(); it != vTileMaps.end(); it++)
    {
        (*it)->Render(hdc);
    }
}
