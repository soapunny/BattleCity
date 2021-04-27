#pragma once
#include "GameNode.h"

class TileMapTool;
class Image;
enum TILEMAPTYPE { GROUND, BROWNBRICK, GRAYBRICK, 
					FOREST, RIVER, ICEFILED };	// ¶¥, º®µ¹, ½£, °­, ¾óÀ½¶¥
class TileMap : public GameNode
{
private:
	TILEMAPTYPE tileType;

public:
	HRESULT Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

