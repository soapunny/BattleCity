#pragma once
#include "GameNode.h"
#include <vector>

class TileMapTool;
class TileMapManager : public GameNode
{
private:
	vector<TileMapTool*> vTileMaps;

public:
	HRESULT Init(); 
	void Release();
	void Update();
	void Render(HDC hdc);
};

