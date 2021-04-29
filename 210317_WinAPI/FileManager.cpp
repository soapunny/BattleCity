#include "FileManager.h"
#include "Image.h"
#include "CommonFunction.h"
#include "TileMapTool.h"

HRESULT FileManager::Init()
{
    SetClientRect(g_hWnd, TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y);

    sampleTile = ImageManager::GetSingleton()->FindImage("샘플타일");

    backBtScene = ImageManager::GetSingleton()->FindImage("전투배경");

    // 메인 공간 렉트 설정
    for (int i = 0; i < TILE_Y; i++)
    {
        for (int j = 0; j < TILE_X; j++)
        {
            tileInfo[i * TILE_X + j].frameX = 0;
            tileInfo[i * TILE_X + j].frameY = 0;

            tileInfo[i * TILE_X + j].rcTile.left = TILESIZE * j * 1.5;
            tileInfo[i * TILE_X + j].rcTile.top = TILESIZE * i * 1.5;
            tileInfo[i * TILE_X + j].rcTile.right =
                tileInfo[i * TILE_X + j].rcTile.left + (TILESIZE * 1.5);
            tileInfo[i * TILE_X + j].rcTile.bottom =
                tileInfo[i * TILE_X + j].rcTile.top + (TILESIZE * 1.5);
        }
    }

    return S_OK;
}

void FileManager::Release()
{
    ReleaseSingleton();
}

void FileManager::Update()
{
    // 메인 영역 계산
    rcMain.left = 0;
    rcMain.top = 0;
    rcMain.right = rcMain.left + ((TILESIZE * TILE_X));
    rcMain.bottom = rcMain.top + ((TILESIZE * TILE_Y));
}

void FileManager::Render(HDC hdc)
{
    PatBlt(hdc, 0, 0, TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y, WHITENESS);

    if (backBtScene)
    {
        backBtScene->Render(hdc);
    }
    for (int i = 0; i < TILE_X * TILE_Y; i++)
    {
        sampleTile->FrameRender(hdc,
            tileInfo[i].rcTile.left + 50,
            tileInfo[i].rcTile.top + 50,
            tileInfo[i].frameX,
            tileInfo[i].frameY,
            false, 1.5);
    }
}

void FileManager::SaveStage(int stageNum)
{
    string szfileName = "Save/saveMapData";
    szfileName += to_string(stageNum) + ".map";

    DWORD writeenBytes;
    HANDLE hFile = CreateFile(szfileName.c_str(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    /*void**/
    WriteFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &writeenBytes, NULL);

    CloseHandle(hFile);
}

void FileManager::LoadStage(int stageNum)
{
    string szfileName = "Save/saveMapData";
    szfileName += to_string(stageNum) + ".map";

    DWORD readBytes;
    HANDLE hFile = CreateFile(szfileName.c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    /*void**/
    if (ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &readBytes, NULL))
    {

    }
    else
    {
        MessageBox(g_hWnd, "저장파일 로드 실패", "실패", MB_OK);
    }

    CloseHandle(hFile);
}
