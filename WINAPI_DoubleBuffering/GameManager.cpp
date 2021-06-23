#include "GameManager.h"

GameManager* GameManager::m_hThis = NULL;

GameManager::GameManager()
{
	m_Player = new Character;
	m_BackGround = new Map;
    m_Menu = new Menu;
}

int GameManager::ShowMenu(HWND hWnd, HDC hdc)
{
    RECT windowRect;
    GetWindowRect(hWnd, &windowRect);

    HDC backDC = CreateCompatibleDC(hdc);
    HBITMAP backBitmap = CreateDIBSectionRe(hdc, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);
    HBITMAP oldBack = (HBITMAP)SelectObject(backDC, backBitmap);

    m_Menu->DrawMenu(backDC);
    m_Menu->DrawPoint(backDC, 0);

    BitBlt(hdc, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, backDC, 0, 0, SRCCOPY);
    SelectObject(backDC, oldBack);
    DeleteObject(backBitmap);
    DeleteObject(backDC);

    if (GetKeyState(VK_RIGHT))
    {
        return 1;
    }
    else if (GetKeyState(VK_ESCAPE))
        return 2;
}

void GameManager::InitPlayer(HWND hWnd)
{
	//BitMapManager::GetInstance()->Init(hWnd);
	m_Player->Init(50, 285);
}

void GameManager::InitMap(HWND hWnd)
{
	m_BackGround->Init(BACKGROUND_TRACK, 0, 0);
	m_Menu->Init(MENU_1, 0, 0);
}

void GameManager::Update(float deltaTime, int iCheck)
{
    /*if (m_BackGround->GetMoveLenx() >= 8000)
    {

    }*/
    int x = m_Player->GetDistx(deltaTime);

    if (!m_Player->GetJumpStatus())
    {
        if (GetAsyncKeyState(VK_RIGHT))
        {
            m_Player->UpdateDirection(DIR_RIGHT);
            iCheck = 1;
        }
        else if (GetAsyncKeyState(VK_LEFT))
        {
            m_Player->UpdateDirection(DIR_LEFT);
            iCheck = -1;

            //if (m_BackGround->GetMoveLenx() <= 0)
            //{
            //    x = 0;
            //}
        }
        else
        {
            iCheck = 0;
            m_Player->UpdateDirection(DIR_IDLE);
        }


        if (GetAsyncKeyState(VK_SPACE))
        {
            if (false == m_Player->GetJumpStatus())
            {
                m_Player->UpdateJumpStatus(true);
            }

            //if (m_Player->GetDirection() == DIR_RIGHT)
            //    m_Player->UpdateSjump(DIR_RIGHT);
            //else if (m_Player->GetDirection() == DIR_LEFT)
            //    m_Player->UpdateSjump(DIR_LEFT);
        }
    }

    m_BackGround->UpdateMoveLenx(x);
    //if (DIR_RIGHT == m_Player->GetSjump())
    //    m_BackGround->UpdateMoveLenx(x);
    //else if(DIR_LEFT == m_Player->GetSjump())
    //    m_BackGround->UpdateMoveLenx(-x);

    m_Player->PlayerUpdate(deltaTime, iCheck);
}

HBITMAP GameManager::CreateDIBSectionRe(HDC hdc, int width, int height)
{
    BITMAPINFO bm_info;
    ZeroMemory(&bm_info.bmiHeader, sizeof(BITMAPINFOHEADER));
    bm_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bm_info.bmiHeader.biBitCount = 24;
    bm_info.bmiHeader.biWidth = width;
    bm_info.bmiHeader.biHeight = height;
    bm_info.bmiHeader.biPlanes = 1;

    LPVOID pBits;
    return CreateDIBSection(hdc, &bm_info, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
}

void GameManager::Draw(HWND hWnd, HDC hdc)
{
    char buf[256];
    ZeroMemory(buf, sizeof(buf));
    RECT windowRect;
    GetWindowRect(hWnd, &windowRect);

    HDC backDC = CreateCompatibleDC(hdc);
    HBITMAP backBitmap = CreateDIBSectionRe(hdc, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);
    HBITMAP oldBack = (HBITMAP)SelectObject(backDC, backBitmap);

    m_BackGround->MapDraw(backDC);
    m_Player->Draw(backDC);

    sprintf(buf, "이동 거리 : %d", m_BackGround->GetMoveLenx());
    TextOutA(backDC, 100, 50, buf, strlen(buf));

    BitBlt(hdc, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, backDC, 0, 0, SRCCOPY);
    SelectObject(backDC, oldBack);
    DeleteObject(backBitmap);
    DeleteObject(backDC);
}

GameManager::~GameManager()
{
	delete m_Player;
	delete m_BackGround;
    delete m_Menu;
}