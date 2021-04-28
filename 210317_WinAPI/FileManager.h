#pragma once
#include "Singleton.h"
#include <string>
#include "config.h"

using namespace std;

class TileMapTool;
class FileManager : public Singleton<FileManager>
{
private:
	TILE_INFO tileInfo[TILE_X * TILE_Y];
public:
	void SaveStage(string fileName, int stageNum);
	void LoadStage(string fileName, int stageNum);
};

