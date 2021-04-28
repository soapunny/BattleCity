#include "FileManager.h"
#include "CommonFunction.h"
#include "TileMapTool.h"

void FileManager::SaveStage(string fileName, int stageNum)
{
    string szfileName = "Save/saveMapData";
    szfileName += to_string(stageNum) + ".map";

    DWORD writeenBytes;
    HANDLE hFile = CreateFile(szfileName.c_str(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    /*void**/
    WriteFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y, &writeenBytes, NULL);

    CloseHandle(hFile);
}

void FileManager::LoadStage(string fileName, int stageNum)
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
