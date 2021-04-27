#pragma once
#include "GameNode.h"
#include <vector>

class TileMap;
class TileMapManager : public GameNode
{
private:
	vector<TileMap*> vTileMaps;
public:
	HRESULT Init(); 
	void Release();
	void Update();
	void Render(HDC hdc);
};

