#pragma once
#include "TilemapTool.h"
#include "Image.h"
#include "SceneManager.h"
#include "FileManager.h"
#include "CommonFunction.h"
#include "Button.h"

Button* TileMapTool::btnSave = nullptr;
Button* TileMapTool::btnLoad = nullptr;

HRESULT TileMapTool::Init()
{
    SetClientRect(g_hWnd, TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y);//Ŭ���̾�Ʈ ȭ�� ������

    sampleTile = ImageManager::GetSingleton()->FindImage("����Ÿ��");
    hSelectedBrush = (HBRUSH)GetStockObject(NULL_BRUSH);

    //���� ������ ù��° �������� �ε�
    FileManager::GetSingleton()->Init();
    FileManager::GetSingleton()->LoadStage(STAGE_TYPE::FIRST_STAGE + 1);

    // ���� ���� ��Ʈ ����
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
        }
    }

    btnSave = new Button();
    btnSave->Init("�����ư", TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + 50, TILEMAPTOOLSIZE_Y - 200);
    btnSave->SetFunc(FileManager::GetSingleton()->SaveStage, 1);

    btnLoad = new Button();
    btnLoad->Init("�ҷ������ư", TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + 150, TILEMAPTOOLSIZE_Y - 200);
    btnLoad->SetFunc(FileManager::GetSingleton()->LoadStage, 1);

    stageBt_01 = new Button();
    stageBt_01->Init("stage1", TILEMAPTOOLSIZE_X - sampleTile->GetWidth() - 20, TILEMAPTOOLSIZE_Y - 400);
    stageBt_01->SetFunc(SetChangeStage, 1);

    stageBt_02 = new Button();      
    stageBt_02->Init("stage2", TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + 80, TILEMAPTOOLSIZE_Y - 400);
    stageBt_02->SetFunc(SetChangeStage, 2);

    stageBt_03 = new Button();
    stageBt_03->Init("stage3", TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + 180, TILEMAPTOOLSIZE_Y - 400);
    stageBt_03->SetFunc(SetChangeStage, 3);

    mainChangeOn = true;
    startTest = true;

    return S_OK;
}

void TileMapTool::Release()
{
    SAFE_RELEASE(btnSave);
    SAFE_RELEASE(btnLoad);
    SAFE_RELEASE(stageBt_01);
    SAFE_RELEASE(stageBt_02);
    SAFE_RELEASE(stageBt_03);
    FileManager::GetSingleton()->Release();
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

    // ���� ���� ���
    rcMain.left = 0;
    rcMain.top = 0;
    rcMain.right = rcMain.left + ((TILESIZE * TILE_X) * 1.5);
    rcMain.bottom = rcMain.top + ((TILESIZE * TILE_Y) * 1.5);

    // ���� ���� ���
    rcSample.left = TILEMAPTOOLSIZE_X - sampleTile->GetWidth();
    rcSample.top = 0;
    rcSample.right = TILEMAPTOOLSIZE_X;
    rcSample.bottom = sampleTile->GetHeight();

    if (PtInRect(&rcMain, g_ptMouse))
    {
        // ���콺 ���� ��ư Ŭ���� ��ǥ ���
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON)
            || KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
        {
            mainChangeOn = true;

            for (int i = 0; i < TILE_X * TILE_Y; i++)
            {
                if (PtInRect(&(FileManager::tileInfo[i].rcTile), g_ptMouse))
                {
                    //selectedFrameX = i % TILE_X;
                    //selectedFrameY = i / TILE_X;

                    FileManager::tileInfo[i].frameX = ptStartSelectedFrame.x;
                    FileManager::tileInfo[i].frameY = ptStartSelectedFrame.y;
                    FileManager::tileInfo[i].type = (TILE_TYPE)(FileManager::tileInfo[i].frameX/2 + (FileManager::tileInfo[i].frameY/2 * TILE_TYPE::SIZE_OF_TILE_TYPE/2));

                    for (int j = 0; j <= ptEndSelectedFrame.y - ptStartSelectedFrame.y; j++)
                    {
                        for (int k = 0; k <= ptEndSelectedFrame.x - ptStartSelectedFrame.x; k++)
                        {
                            if ((i % TILE_X) + k >= TILE_X) continue;
                            if ((i / TILE_X) + j >= TILE_Y) continue;

                            FileManager::tileInfo[i + j * TILE_X + k].frameX = ptStartSelectedFrame.x + k;
                            FileManager::tileInfo[i + j * TILE_X + k].frameY = ptStartSelectedFrame.y + j;
                            FileManager::tileInfo[i + j * TILE_X + k].type
                                = (TILE_TYPE)(FileManager::tileInfo[i + j * TILE_X + k].frameX / 2 + (FileManager::tileInfo[i + j * TILE_X + k].frameY / 2 * TILE_TYPE::SIZE_OF_TILE_TYPE / 2));
                        }
                    }

                    break;
                }
            }
        }
        else
        {
            mainChangeOn = false;
        }
    }
    else if (PtInRect(&rcSample, g_ptMouse))
    {
        // ���콺 ���� ��ư Ŭ���� ��ǥ ���
        if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
        {
            mainChangeOn = true;
            // 2) ���콺 ��ǥ�� �ε��� ���
            int posX = g_ptMouse.x - rcSample.left;
            int posY = g_ptMouse.y - rcSample.top;
            ptStartSelectedFrame.x = posX / TILESIZE;
            ptStartSelectedFrame.y = posY / TILESIZE;

            ptSelected[0] = g_ptMouse;
        }
        else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
        {
            mainChangeOn = true;
            int posX = g_ptMouse.x - rcSample.left;
            int posY = g_ptMouse.y - rcSample.top;
            ptEndSelectedFrame.x = posX / TILESIZE;
            ptEndSelectedFrame.y = posY / TILESIZE;

            // ���ÿ��� �ʱ�ȭ
            ptSelected[0].x = -1;
            ptSelected[0].y = -1;
            ptSelected[1].x = -1;
            ptSelected[1].y = -1;
        }
        else if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
        {
            mainChangeOn = true;
            ptSelected[1] = g_ptMouse;
        }
        else
        {
            mainChangeOn = false;
        }
    }
}

void TileMapTool::Render(HDC hdc)
{
    //��� ����
    if (mainChangeOn == true)
    {
        PatBlt(hdc, 0, 0, TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y, WHITENESS);
    }

    //���� Ÿ�� �׸���
    for (int i = 0; i < TILE_X * TILE_Y; i++)
    {
        sampleTile->FrameRender(hdc,
            FileManager::tileInfo[i].rcTile.left,
            FileManager::tileInfo[i].rcTile.top,
            FileManager::tileInfo[i].frameX,
            FileManager::tileInfo[i].frameY,
            false, 1.5);
    }

    // ����Ÿ�� �׸���
    sampleTile->Render(hdc, TILEMAPTOOLSIZE_X - sampleTile->GetWidth(), 0);

    // ���� ���� ǥ��
    hOldSelectedBrush = (HBRUSH)SelectObject(hdc, hSelectedBrush);
    Rectangle(hdc, ptSelected[0].x, ptSelected[0].y, ptSelected[1].x, ptSelected[1].y);
    SelectObject(hdc, hOldSelectedBrush);

    // UI Button
    if (btnSave)    btnSave->Render(hdc);
    if (btnLoad)    btnLoad->Render(hdc);

    if (stageBt_01)    stageBt_01->Render(hdc);
    if (stageBt_02)    stageBt_02->Render(hdc);
    if (stageBt_03)    stageBt_03->Render(hdc);
    
    // ���õ� Ÿ��
    if (ptStartSelectedFrame.x == ptEndSelectedFrame.x &&
        ptStartSelectedFrame.y == ptEndSelectedFrame.y)
    {
        sampleTile->FrameRender(hdc,
            TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + 50,
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
                    TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + 50,
                    sampleTile->GetHeight() + 50,
                    ptStartSelectedFrame.x + j, ptStartSelectedFrame.y + i, false, 1);

            }
        }
    }
}

void TileMapTool::SetChangeStage(int key)
{
    btnSave->SetFunc(FileManager::GetSingleton()->SaveStage, key);
    btnLoad->SetFunc(FileManager::GetSingleton()->LoadStage, key);
}