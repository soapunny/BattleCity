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
	Image* backBtScene;

	POINT gap;
	RECT rcMain;
public:
	static TILE_INFO tileInfo[TILE_X * TILE_Y];

	HRESULT Init(); 
	void Release();
	void Update();
	void Render(HDC hdc);

	static void SaveStage(int stageNum);
	static void LoadStage(int stageNum);
};