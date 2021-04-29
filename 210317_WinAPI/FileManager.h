#pragma once
#include "Singleton.h"
#include <string>
#include "config.h"

using namespace std;

class Image;
class TileMapTool;
class FileManager : public Singleton<FileManager>
{
private:
	Image* sampleTile;
	TILE_INFO tileInfo[TILE_X * TILE_Y];

	TileMapTool* tileMapTool;
	RECT rcMain;
public:
	HRESULT Init(); 
	void Release();
	void Update();
	void Render(HDC hdc);

	void SaveStage(int stageNum);
	void LoadStage(int stageNum);
};