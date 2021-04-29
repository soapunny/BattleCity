// config.h

#pragma once
#pragma comment(lib, "Winmm.lib")

#include <Windows.h>
#include <string>
#include <ctime>
#include <bitset>
#include <map>

using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimerManager.h"

#define WINSIZE_X	1080
#define WINSIZE_Y	720
#define TILEMAPTOOLSIZE_X	1300
#define TILEMAPTOOLSIZE_Y	730

#define PI			3.141592f
#define DegToRad(x)	((x) * PI / 180.0f)
#define SAFE_DELETE(p) { if (p) { delete p; p = nullptr; } }
#define SAFE_RELEASE(p) { if (p) { p->Release(); delete p; p = nullptr; } }

// 샘플 타일 정보
// 640 * 288
#define SAMPLE_TILE_X	(16)	// 16
#define SAMPLE_TILE_Y	(2)		// 2
#define TILESIZE		32		// 32

// 메인 그리기 공간 정보
#define	TILE_X			((16))	// 16
#define	TILE_Y			((16))	// 16

// 배틀씬 맵 범위
#define BATTLE_SCENE_START_X 50
#define BATTLE_SCENE_START_Y 50
#define BATTLE_SCENE_END_X 815
#define BATTLE_SCENE_END_Y 815

typedef struct tagFPoint
{
	float x;
	float y;
} FPOINT, *PFPOINT;

typedef struct tagTile
{
	RECT rcTile;
	int frameX;
	int frameY;
}TILE_INFO;

enum PLAYER_TYPE { FIRST_PLAYER, SECOND_PLAYER, ENEMY_PLAYER, END_PLAYER_TYPE };
enum MOVE_DIRECTION { UP_WARD = 0, LEFT_WARD = 2, DOWN_WARD = 4, RIGHT_WARD = 6, END_MOVE_DIRECTION = 8 };
enum STAGE_TYPE{FIRST_STAGE, SECOND_STAGE, THIRD_STAGE, FINAL_STAGE, END_OF_STAGE_TYPE};

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;