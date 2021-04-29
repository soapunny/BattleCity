#include "TilemapTool.h"
#include "Image.h"
#include "SceneManager.h"
#include "CommonFunction.h"
#include "Button.h"

TILE_INFO TileMapTool::tileInfo[TILE_X * TILE_Y];
Button* TileMapTool::btnSave = nullptr;
Button* TileMapTool::btnLoad = nullptr;

HRESULT TileMapTool::Init()
{
    SetClientRect(g_hWnd, TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y);

    sampleTile = ImageManager::GetSingleton()->FindImage("샘플타일");
    hSelectedBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

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

    // 샘플 공간 렉트 설정
    for (int i = 0; i < SAMPLE_TILE_Y; i++)
    {
        for (int j = 0; j < SAMPLE_TILE_X; j++)
        {
            SetRect(&sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile,
                TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (TILESIZE * j),
                (TILESIZE * i),
                TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (TILESIZE * j) + TILESIZE,
                (TILESIZE * i) + TILESIZE);

            sampleTileInfo[i * SAMPLE_TILE_X + j].frameX = j;
            sampleTileInfo[i * SAMPLE_TILE_X + j].frameY = i;

            //sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.left =
            //    TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (TILESIZE * j);
            //sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.top = (TILESIZE * i);
            //sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.right =
            //    sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.left + TILESIZE;
            //sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.bottom =
            //    sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile.top + TILESIZE;
        }
    }

    // UI Button
    ImageManager::GetSingleton()->AddImage("저장버튼", "Image/SaveButton.bmp",
        60, 130, 1, 2);
    ImageManager::GetSingleton()->AddImage("불러오기버튼", "Image/LoadButton.bmp",
        60, 130, 1, 2);

    ImageManager::GetSingleton()->AddImage("stage1", "Image/stageBt_01.bmp",
        100, 92, 1, 2);
    ImageManager::GetSingleton()->AddImage("stage2", "Image/stageBt_02.bmp",
        100, 92, 1, 2);
    ImageManager::GetSingleton()->AddImage("stage3", "Image/stageBt_03.bmp",
        100, 92, 1, 2);

    btnSave = new Button();
    btnSave->Init("저장버튼", TILEMAPTOOLSIZE_X - sampleTile->GetWidth() - 170,
        TILEMAPTOOLSIZE_Y - 300);
    btnSave->SetFunc(Save, 1);

    btnLoad = new Button();
    btnLoad->Init("불러오기버튼", TILEMAPTOOLSIZE_X - sampleTile->GetWidth(),
        TILEMAPTOOLSIZE_Y - 300);
    btnLoad->SetFunc(Load, 1);

    stageBt_01 = new Button();
    stageBt_01->Init("stage1", TILEMAPTOOLSIZE_X - sampleTile->GetWidth() - 200,
        TILEMAPTOOLSIZE_Y - 200);
    stageBt_01->SetFunc(SetChangeStage, 1);

    stageBt_02 = new Button();      
    stageBt_02->Init("stage2", TILEMAPTOOLSIZE_X - sampleTile->GetWidth() - 100,
        TILEMAPTOOLSIZE_Y - 200);
    stageBt_02->SetFunc(SetChangeStage, 2);

    stageBt_03 = new Button();
    stageBt_03->Init("stage3", TILEMAPTOOLSIZE_X - sampleTile->GetWidth(),
        TILEMAPTOOLSIZE_Y - 200);
    stageBt_03->SetFunc(SetChangeStage, 3);

    return S_OK;
}

void TileMapTool::Release()
{
    SAFE_RELEASE(btnSave);
    SAFE_RELEASE(btnLoad);
    SAFE_RELEASE(stageBt_01);
    SAFE_RELEASE(stageBt_02);
    SAFE_RELEASE(stageBt_03);
}

void TileMapTool::Update()
{
    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_BACK))
    {
        SceneManager::GetSingleton()->ChangeScene("MenuScene");
    }
    if (btnSave)    btnSave->Update();
    if (btnLoad)    btnLoad->Update();
    if (stageBt_01)    stageBt_01->Update();
    if (stageBt_02)    stageBt_02->Update();
    if (stageBt_03)    stageBt_03->Update();

    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_CONTROL))
    {
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F1))
        {
            Load(1);
        }
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F2))
        {
            Load(2);
        }
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F3))
        {
            Load(3);
        }
    }
    else
    {
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F1))
        {
            Save(1);
        }
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F2))
        {
            Save(2);
        }
        else if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_F3))
        {
            Save(3);
        }
    }

    // 메인 영역 계산
    rcMain.left = 0;
    rcMain.top = 0;
    rcMain.right = rcMain.left + ((TILESIZE * TILE_X) * 1.5);
    rcMain.bottom = rcMain.top + ((TILESIZE * TILE_Y) * 1.5);

    // 샘플 영역 계산
    rcSample.left = TILEMAPTOOLSIZE_X - sampleTile->GetWidth();
    rcSample.top = 0;
    rcSample.right = TILEMAPTOOLSIZE_X;
    rcSample.bottom = sampleTile->GetHeight();

    if (PtInRect(&rcMain, g_ptMouse))
    {
        // 마우스 왼쪽 버튼 클릭시 좌표 사용
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON)
            || KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
        {
            for (int i = 0; i < TILE_X * TILE_Y; i++)
            {
                if (PtInRect(&(tileInfo[i].rcTile), g_ptMouse))
                {
                    //selectedFrameX = i % TILE_X;
                    //selectedFrameY = i / TILE_X;

                    tileInfo[i].frameX = ptStartSelectedFrame.x;
                    tileInfo[i].frameY = ptStartSelectedFrame.y;

                    for (int j = 0; j <= ptEndSelectedFrame.y - ptStartSelectedFrame.y; j++)
                    {
                        for (int k = 0; k <= ptEndSelectedFrame.x - ptStartSelectedFrame.x; k++)
                        {
                            if ((i % TILE_X) + k >= TILE_X) continue;
                            if ((i / TILE_X) + j >= TILE_Y) continue;

                            tileInfo[i + j * TILE_X + k].frameX = ptStartSelectedFrame.x + k;
                            tileInfo[i + j * TILE_X + k].frameY = ptStartSelectedFrame.y + j;
                        }
                    }

                    break;
                }
            }
        }
    }
    else if (PtInRect(&rcSample, g_ptMouse))
    {
        // 마우스 왼쪽 버튼 클릭시 좌표 사용
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
        {
            // 2) 마우스 좌표로 인덱스 계산
            int posX = g_ptMouse.x - rcSample.left;
            int posY = g_ptMouse.y - rcSample.top;
            ptStartSelectedFrame.x = posX / TILESIZE;
            ptStartSelectedFrame.y = posY / TILESIZE;

            ptSelected[0] = g_ptMouse;

            //// 1) 모든 타일을 반복하면서 렉트충돌 확인
            //for (int i = 0; i < SAMPLE_TILE_X * SAMPLE_TILE_Y; i++)
            //{
            //    if (PtInRect(&(sampleTileInfo[i].rcTile), g_ptMouse))
            //    {
            //        ptStartSelectedFrame.x = i % SAMPLE_TILE_X;
            //        ptStartSelectedFrame.y = i / SAMPLE_TILE_X;

            //        break;
            //    }
            //}
        }
        else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
        {
            int posX = g_ptMouse.x - rcSample.left;
            int posY = g_ptMouse.y - rcSample.top;
            ptEndSelectedFrame.x = posX / TILESIZE;
            ptEndSelectedFrame.y = posY / TILESIZE;

            // 선택영역 초기화
            ptSelected[0].x = -1;
            ptSelected[0].y = -1;
            ptSelected[1].x = -1;
            ptSelected[1].y = -1;
        }
        else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
        {
            ptSelected[1] = g_ptMouse;
        }
    }

}

void TileMapTool::Render(HDC hdc)
{
    PatBlt(hdc, 0, 0,
        TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y, WHITENESS);

    // 샘플타일 전체
    sampleTile->Render(hdc, TILEMAPTOOLSIZE_X - sampleTile->GetWidth(), 0);

    // 선택 영역 표시
    hOldSelectedBrush = (HBRUSH)SelectObject(hdc, hSelectedBrush);
    Rectangle(hdc, ptSelected[0].x, ptSelected[0].y, ptSelected[1].x, ptSelected[1].y);
    SelectObject(hdc, hOldSelectedBrush);

    // UI Button
    if (btnSave)    btnSave->Render(hdc);
    if (btnLoad)    btnLoad->Render(hdc);

    if (stageBt_01)    stageBt_01->Render(hdc);
    if (stageBt_02)    stageBt_02->Render(hdc);
    if (stageBt_03)    stageBt_03->Render(hdc);

    // 메인영역 전체
    for (int i = 0; i < TILE_X * TILE_Y; i++)
    {
        sampleTile->FrameRender(hdc,
            tileInfo[i].rcTile.left,
            tileInfo[i].rcTile.top,
            tileInfo[i].frameX,
            tileInfo[i].frameY, 
            false, 1.5f);
    }

    // 선택된 타일
    if (ptStartSelectedFrame.x == ptEndSelectedFrame.x &&
        ptStartSelectedFrame.y == ptEndSelectedFrame.y)
    {
        sampleTile->FrameRender(hdc,
            TILEMAPTOOLSIZE_X - sampleTile->GetWidth(),
            sampleTile->GetHeight() + 50,
            ptStartSelectedFrame.x, ptStartSelectedFrame.y, false, 3);
    }
    else
    {
        for (int i = 0; i <= ptEndSelectedFrame.y - ptStartSelectedFrame.y; i++)
        {
            for (int j = 0; j <= ptEndSelectedFrame.x - ptStartSelectedFrame.x; j++)
            {
                sampleTile->FrameRender(hdc,
                    TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (j * TILESIZE),
                    sampleTile->GetHeight() + 50 + (i * TILESIZE),
                    ptStartSelectedFrame.x + j, ptStartSelectedFrame.y + i, false, 1);

            }
        }
    }

}

/*
    실습1. F1, F2, F3  각 키를 눌렀을 때
    Save/saveMapData1.map, Save/saveMapData2.map, Save/saveMapData3.map
    각 각 파일에 저장될 수 있도록 코드 구현

    실습2. 로드는 Ctrl + F1, ...
*/

void TileMapTool::Save(int stageNum)
{
    string fileName = "Save/saveMapData";  // 1.map";
    fileName += to_string(stageNum) + ".map";

    DWORD writtenBytes;
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_WRITE, 0,
        0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    /*void**/
    WriteFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y,
        &writtenBytes, NULL);

    CloseHandle(hFile);
}

void TileMapTool::Load(int stageNum)
{
    string fileName = "Save/saveMapData";  // 1.map";
    fileName += to_string(stageNum) + ".map";

    DWORD readBytes;
    HANDLE hFile = CreateFile(fileName.c_str(), GENERIC_READ, 0,
        0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    /*void**/
    if (ReadFile(hFile, tileInfo, sizeof(TILE_INFO) * TILE_X * TILE_Y,
        &readBytes, NULL))
    {

    }
    else
    {
        MessageBox(g_hWnd, "저장파일 로드 실패", "실패", MB_OK);
    }

    CloseHandle(hFile);
}

void TileMapTool::SetChangeStage(int key)
{
    btnSave->SetFunc(Save, key);
    btnLoad->SetFunc(Load, key);
}

/*
    실습1. F1, F2, F3 각 키를 눌렀을 때
    Save/saveMapData1
    Save/saveMapData2
    Save/saveMapData3
    각각에 저장이 될 수 있도록 코드 구현

    실습2.
    로드는 Ctrl + F1, Ctrl + F2, Ctrl + F3...
*/