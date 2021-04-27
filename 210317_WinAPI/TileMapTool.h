#pragma once
#include "GameNode.h"

//���� Ÿ�� ����
//��üũ�� 640 * 288


class Image;
class TileMapTool : public GameNode
{
private:
	//sample titile �̹���
	Image* sampleTile;
	TILE_INFO sampleTileInfo[SAMPLE_TILE_X * SAMPLE_TILE_Y];
	RECT rcSample;

	//���� Ÿ�� ����
	TILE_INFO tileInfo[TILE_X * TILE_Y];
	TILE_INFO currTile;
	TILE_INFO startTile;
	RECT rcMain;

	bool isStartTileChosen;
	bool isCurrTileChosen;

public:
	virtual HRESULT Init();			// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();			// �޸� ����
	virtual void Update();			// ������ ������ ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ������ ��� (�̹���, �ؽ�Ʈ ��)

	virtual ~TileMapTool() {};
};

