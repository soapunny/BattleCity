#pragma once
#include "GameNode.h"

//���� Ÿ�� ����
//��üũ�� 640 * 288
#define SAMPLE_TILE_X	20
#define SAMPLE_TILE_Y	9
#define TILE_SIZE		32

//���� �׸��� ���� ����
#define TILE_X			20
#define TILE_Y			20

class Image;
class Button;
class TileMapTool : public GameNode
{
private:
	//sample titile �̹���
	Image* sampleTile;
	TILE_INFO sampleTileInfo[SAMPLE_TILE_X * SAMPLE_TILE_Y];
	RECT rcSample;

	//���� Ÿ�� ����
	static TILE_INFO tileInfo[TILE_X * TILE_Y];
	TILE_INFO currTile;
	TILE_INFO startTile;
	RECT rcMain;

	bool isStartTileChosen;
	bool isCurrTileChosen;

	static Button* btnSave;
	static Button* btnLoad;
	
	Button* btnStage1;
	Button* btnStage2;
	Button* btnStage3;


public:
	virtual HRESULT Init();			// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();			// �޸� ����
	virtual void Update();			// ������ ������ ���� ���� ���� (������ ����)
	virtual void Render(HDC hdc);	// ������ ������ ��� (�̹���, �ؽ�Ʈ ��)

	static void Save(int key); //static�� Ŭ������ ��������� ���� Data ������ ���� ����
	static void Load(int key);
	static void ChangeStage(int key);

	virtual ~TileMapTool() {};
};

