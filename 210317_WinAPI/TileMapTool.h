#pragma once
#include "GameNode.h"

class Button;
class Image;
class Button;
class TileMapTool : public GameNode
{
private:
	// 샘플 타일 이미지
	Image* sampleTile;
	TILE_INFO sampleTileInfo[SAMPLE_TILE_X * SAMPLE_TILE_Y];
	RECT rcSample;

	RECT rcMain;

	POINT ptStartSelectedFrame;
	POINT ptEndSelectedFrame;

	POINT ptSelected[2];
	HBRUSH hSelectedBrush;
	HBRUSH hOldSelectedBrush;

	// UI button
	static Button* btnSave;
	static Button* btnLoad;

	Button* stageBt_01;
	Button* stageBt_02;
	Button* stageBt_03;

	bool mainChangeOn;
	bool startTest;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render(HDC hdc);

	static void SetChangeStage(int key);

	virtual ~TileMapTool() {};
};

