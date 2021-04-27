#pragma once
#include "GameNode.h"

//샘플 타일 정보
//전체크기 640 * 288


class Image;
class TileMapTool : public GameNode
{
private:
	//sample titile 이미지
	Image* sampleTile;
	TILE_INFO sampleTileInfo[SAMPLE_TILE_X * SAMPLE_TILE_Y];
	RECT rcSample;

	//메인 타일 정보
	TILE_INFO tileInfo[TILE_X * TILE_Y];
	TILE_INFO currTile;
	TILE_INFO startTile;
	RECT rcMain;

	bool isStartTileChosen;
	bool isCurrTileChosen;

public:
	virtual HRESULT Init();			// 멤버 변수의 초기화, 메모리 할당
	virtual void Release();			// 메모리 해제
	virtual void Update();			// 프레임 단위로 게임 로직 실행 (데이터 변동)
	virtual void Render(HDC hdc);	// 프레임 단위로 출력 (이미지, 텍스트 등)

	virtual ~TileMapTool() {};
};

