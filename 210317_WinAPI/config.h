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
#define TILEMAPTOOLSIZE_X	1620
#define TILEMAPTOOLSIZE_Y	1080

#define PI			3.141592f
#define DegToRad(x)	((x) * PI / 180.0f)
#define SAFE_DELETE(p) { if (p) { delete p; p = nullptr; } }
#define SAFE_RELEASE(p) { if (p) { p->Release(); delete p; p = nullptr; } }

// 샘플 타일 정보
// 640 * 288
#define SAMPLE_TILE_X	(16)	// 8
#define SAMPLE_TILE_Y	(2)		// 1
#define TILESIZE		32		// 16

// 메인 그리기 공간 정보
#define	TILE_X			((16))
#define	TILE_Y			((16))

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

//typedef tagFPoint FPOINT2;
//typedef tagFPoint* PFPOINT2;

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;