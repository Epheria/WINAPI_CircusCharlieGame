#include "GameManager.h"

GameManager* GameManager::m_hThis = NULL;

GameManager::GameManager()
{
	m_Player = new Character;
	m_BackGround = new Map;
    m_Menu = new Menu;
    m_Obstacle = new Obstacle;
    m_ctmp = 0;
    m_CurrSelectState = 0;
}

void GameManager::Init(HWND hWnd)
{
	//BitMapManager::GetInstance()->Init(hWnd);
	m_Player->Init(50, 285);
    m_BackGround->Init(BACKGROUND_TRACK, 0, 0);
    m_Menu->Init(MENU_SELECT, 0, 0);
    m_Obstacle->Init(OBS_FIRE1, 0, 0);
}

void GameManager::Update(float deltaTime, int iCheck)
{
    switch (m_CurrSelectState)
    {
    case SELECT_MAINMENU:
        m_Menu->Update(deltaTime);
        if (GetAsyncKeyState(VK_UP))
        {
            m_ctmp--;
            if (0 > m_ctmp) m_ctmp = 0;
        }
        else if (GetAsyncKeyState(VK_DOWN))
        {
            m_ctmp++;
            if (1 < m_ctmp) m_ctmp = 1;
        }

        if (GetAsyncKeyState(VK_RETURN))
        {
            m_CurrSelectState = m_ctmp;
        }
        break;
    case SELECT_PLAY:
    {
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
            }
        }
        //if (m_BackGround->GetMoveLenx() <= 3900)
        //    m_BackGround->UpdateMoveLenx(x);
        //else
        //    m_Player->UpdatePosx(x);

        if (FinalLineCheck(x))
            m_Player->UpdatePosx(x);
        else
            m_BackGround->UpdateMoveLenx(x);
        
        m_Obstacle->Update(deltaTime, x);

        m_Player->UdpateMovedLength(m_BackGround->GetMoveLenx());
        m_Player->PlayerUpdate(deltaTime, iCheck);
    }
    break;
    }

    /*if (m_BackGround->GetMoveLenx() >= 8000)
    {

    }*/

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
    RECT windowRect;
    GetWindowRect(hWnd, &windowRect);

    HDC backDC = CreateCompatibleDC(hdc);
    HBITMAP backBitmap = CreateDIBSectionRe(hdc, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);
    HBITMAP oldBack = (HBITMAP)SelectObject(backDC, backBitmap);
    switch (m_CurrSelectState)
    {
    case SELECT_MAINMENU:
        m_Menu->Draw(backDC, m_ctmp);
        break;
    case SELECT_PLAY:
    
        char buf[256];
        ZeroMemory(buf, sizeof(buf));

        m_BackGround->MapDraw(backDC);
        m_Obstacle->ObstacleDraw(backDC);
        m_Player->Draw(backDC);
        
        sprintf_s(buf, "이동 거리 : %d, 점프 높이 : %d", m_Player->GetMovedLength() , m_Player->GetPosy());
        TextOutA(backDC, 100, 50, buf, strlen(buf));

    
        break;
    }
    BitBlt(hdc, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, backDC, 0, 0, SRCCOPY);
    SelectObject(backDC, oldBack);
    DeleteObject(backBitmap);
    DeleteObject(backDC);
}

bool GameManager::FinalLineCheck(int x)
{
    if (m_Player->GetPosx() < 50)
    {
        m_Player->SetPosx(50);
        return false;
    }

    if (m_BackGround->GetMoveLenx() >= 3900)
        return true;
    else
    {
        return false;
    }
}

GameManager::~GameManager()
{
	delete m_Player;
	delete m_BackGround;
    delete m_Menu;
    delete m_Obstacle;
}