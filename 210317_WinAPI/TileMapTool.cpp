#include "TileMapTool.h"
#include "CommonFunction.h"
#include "Image.h"

//과제 1. 선택한 이미지 3배로 아래 출력
//과제 3. 드래그로 타일을 다중 선택 & 과제 2와 동일하게 이미지 변경
HRESULT TileMapTool::Init()
{
    SetClientRect(g_hWnd, TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y);

    sampleTile = ImageManager::GetSingleton()->AddImage("샘플타일", "Image/maptiles.bmp", 640, 288, SAMPLE_TILE_X, SAMPLE_TILE_Y, false, NULL);

    for (int i = 0; i < TILE_Y; i++)
    {
        for (int j = 0; j < TILE_X; j++)
        {
            tileInfo[i * TILE_Y + j].frameX = 3;
            tileInfo[i * TILE_Y + j].frameY = 0;

            tileInfo[i * TILE_Y + j].rcTile.left = TILE_SIZE * j;
            tileInfo[i * TILE_Y + j].rcTile.right 
                = tileInfo[i * TILE_Y + j].rcTile.left + TILE_SIZE;
            tileInfo[i * TILE_Y + j].rcTile.top = TILE_SIZE * i;
            tileInfo[i * TILE_Y + j].rcTile.bottom 
                = tileInfo[i * TILE_Y + j].rcTile.top + TILE_SIZE;
        }
    }

    for (int i = 0; i < SAMPLE_TILE_Y; i++)
    {
        for (int j = 0; j < SAMPLE_TILE_X; j++)
        {
            SetRect(&sampleTileInfo[i * SAMPLE_TILE_X + j].rcTile,
                TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (TILE_SIZE * j),
                (TILE_SIZE * i),
                TILEMAPTOOLSIZE_X - sampleTile->GetWidth() + (TILE_SIZE * j) + TILE_SIZE,
                (TILE_SIZE * i) + TILE_SIZE
            );

            sampleTileInfo[i * SAMPLE_TILE_X + j].frameX = j;
            sampleTileInfo[i * SAMPLE_TILE_X + j].frameY = i;
        }
    }

    return S_OK;
}

void TileMapTool::Release()
{

}

void TileMapTool::Update()
{
    //메인 영역 계산
    rcMain.left = 0;
    rcMain.right = rcMain.left + TILE_SIZE * TILE_X;
    rcMain.top = 0;
    rcMain.bottom = rcMain.top + TILE_SIZE * TILE_Y;

    //샘플 영역 계산
    rcSample.left = TILEMAPTOOLSIZE_X - sampleTile->GetWidth();
    rcSample.right = TILEMAPTOOLSIZE_X;
    rcSample.top = 0;
    rcSample.bottom = sampleTile->GetHeight();

    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
    {
        if (PtInRect(&rcSample, g_ptMouse))
        {
            startTile.frameX = (g_ptMouse.x - rcSample.left) / TILE_SIZE;
            startTile.frameY = (g_ptMouse.y) / TILE_SIZE;
        }
    }
    if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
    {
        if (PtInRect(&rcSample, g_ptMouse))
        {
            currTile.frameX = (g_ptMouse.x - rcSample.left) / TILE_SIZE;
            currTile.frameY = (g_ptMouse.y) / TILE_SIZE;

            int tmpFrame = 0;
            if (currTile.frameX < startTile.frameX)
            {
                tmpFrame = currTile.frameX;
                currTile.frameX = startTile.frameX;
                startTile.frameX = tmpFrame;
            }
            if (currTile.frameY < startTile.frameY)
            {
                tmpFrame = currTile.frameY;
                currTile.frameY = startTile.frameY;
                startTile.frameY = tmpFrame;
            }
        }
    }
    if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
    {
        if (PtInRect(&rcSample, g_ptMouse))
        {
            currTile.frameX = (g_ptMouse.x - rcSample.left) / TILE_SIZE;
            currTile.frameY = (g_ptMouse.y) / TILE_SIZE;
        }
        else if (PtInRect(&rcMain, g_ptMouse))
        {
            for (int i = 0; i <= currTile.frameY - startTile.frameY; i++)
            {
                for (int j = 0; j <= currTile.frameX - startTile.frameX; j++)
                {
                    if (g_ptMouse.x / TILE_SIZE + j < TILE_X && g_ptMouse.y / TILE_SIZE + i < TILE_Y)
                    {
                        tileInfo[(g_ptMouse.y / TILE_SIZE + i) * TILE_Y + g_ptMouse.x / TILE_SIZE + j].frameX = startTile.frameX + j;
                        tileInfo[(g_ptMouse.y / TILE_SIZE + i) * TILE_Y + g_ptMouse.x / TILE_SIZE + j].frameY = startTile.frameY + i;
                    }
                }
            }
        }
    }
}

void TileMapTool::Render(HDC hdc)
{
    HPEN hPen = CreatePen(PS_DASH, 2, RGB(0, 0, 0));
    HPEN hOPen = (HPEN)SelectObject(hdc, hPen);

    PatBlt(hdc, 0, 0, TILEMAPTOOLSIZE_X, TILEMAPTOOLSIZE_Y, WHITENESS); //흰색으로 패턴 복사
    sampleTile->Render(hdc, TILEMAPTOOLSIZE_X - sampleTile->GetWidth(), 0);

    for (int i = 0; i < TILE_Y; i++)
    {
        for (int j = 0; j < TILE_X; j++)
        {
            sampleTile->FrameRender(hdc
                , tileInfo[i * TILE_Y + j].rcTile.left
                , tileInfo[i * TILE_Y + j].rcTile.top
                , tileInfo[i * TILE_Y + j].frameX
                , tileInfo[i * TILE_Y + j].frameY
            );
        }
    }
    hPen = (HPEN)SelectObject(hdc, hOPen); // 기존의 펜 선택 
    DeleteObject( hPen ); // 생성한 펜 삭제

    if (currTile.frameX == startTile.frameX && currTile.frameY == startTile.frameY) {//선택한 타일이 한개일 때
        sampleTile->FrameRender(hdc, TILEMAPTOOLSIZE_X - sampleTile->GetWidth(), sampleTile->GetHeight() + 100,
            TILE_SIZE * 3, TILE_SIZE * 3, startTile.frameX, startTile.frameY, currTile.frameX, currTile.frameY);
    }
    else//선택한 타일이 여러개일 때
    {
        POINT tmpStartTile;
        POINT tmpEndTile;
        tmpStartTile.x = 0;
        tmpStartTile.y = 0;
        tmpEndTile.x = 0;
        tmpEndTile.y = 0;

        if (currTile.frameX >= startTile.frameX && currTile.frameY >= startTile.frameY)
        {
            tmpStartTile.x = startTile.frameX;
            tmpStartTile.y = startTile.frameY;
            tmpEndTile.x = currTile.frameX;
            tmpEndTile.y = currTile.frameY;
        }
        else if (currTile.frameX <= startTile.frameX && currTile.frameY >= startTile.frameY)
        {
            tmpStartTile.x = currTile.frameX;
            tmpStartTile.y = startTile.frameY;
            tmpEndTile.x = startTile.frameX;
            tmpEndTile.y = currTile.frameY;
        }
        else if (currTile.frameX >= startTile.frameX && currTile.frameY <= startTile.frameY)
        {
            tmpStartTile.x = startTile.frameX;
            tmpStartTile.y = currTile.frameY;
            tmpEndTile.x = currTile.frameX;
            tmpEndTile.y = startTile.frameY;
        }
        else if (currTile.frameX <= startTile.frameX && currTile.frameY <= startTile.frameY)
        {
            tmpStartTile.x = currTile.frameX;
            tmpStartTile.y = currTile.frameY;
            tmpEndTile.x = startTile.frameX;
            tmpEndTile.y = startTile.frameY;
        }

        sampleTile->FrameRender(hdc, TILEMAPTOOLSIZE_X - sampleTile->GetWidth(), sampleTile->GetHeight() + 100,
            TILE_SIZE * (tmpEndTile.x - tmpStartTile.x + 1), TILE_SIZE * (tmpEndTile.y - tmpStartTile.y + 1), tmpStartTile.x, tmpStartTile.y, tmpEndTile.x, tmpEndTile.y);
    }
}
