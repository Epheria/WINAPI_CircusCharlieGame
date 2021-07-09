#include "GameManager.h"

GameManager* GameManager::m_hThis = NULL;

GameManager::GameManager() : m_Player(new Character), m_BackGround(new Map), m_Menu(new Menu),m_Obstacle(new Obstacle),m_Rank(new Rank),m_ctmp(0), m_CurrSelectState(SELECT_DEFAULT),
    m_iBonusScore(10000), m_bGameOver(false), m_fTime(0), m_fTime2(0)
{
}

void GameManager::Init(HWND hWnd)
{
	m_Player->Init(50, 285);
    m_BackGround->Init(BACKGROUND_TRACK, 0, 0);
    m_Menu->Init(MENU_SELECT, 0, 0);
    m_Obstacle->Init(OBS_FIRE1, 0, 0);
    m_Rank->Init();
}

void GameManager::Update(float deltaTime, int iCheck, HWND g_hwnd)
{
    switch (m_CurrSelectState)
    {
    case SELECT_DEFAULT:
        m_Menu->Update(deltaTime);

        m_fTime2 += deltaTime;
        if (0.5f <= m_fTime2)
        {
            m_fTime2 = 0;

            if (GetAsyncKeyState(VK_UP))
            {
                m_ctmp--;
                if (0 > m_ctmp) m_ctmp = 0;
            }
            else if (GetAsyncKeyState(VK_DOWN))
            {
                m_ctmp++;
                if (2 < m_ctmp) m_ctmp = 2;
            }

            if (GetAsyncKeyState(VK_RETURN))
            {
                m_Rank->LoadRank();
                m_CurrSelectState = m_ctmp;
            }
        }
        break;
    case SELECT_RANK:
        if (m_Rank->MenuSelect(deltaTime))
        {
            m_CurrSelectState = SELECT_DEFAULT;
        }
        break;
    case SELECT_PLAY1:
    case SELECT_PLAY2:
    case SELECT_GOAL:
    {
        int x = m_Player->GetDistx(deltaTime);
        int x_ring = 30 * deltaTime;

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
                iCheck = 1;
                if (false == m_Player->GetJumpStatus())
                {
                    m_Player->UpdateJumpStatus(true);
                }
            }
        }

        m_Obstacle->Update(deltaTime, m_Player->GetMovedLength());

        if (FinalLineCheck(x))
        {
            m_Player->UpdatePosx(x);
            m_Obstacle->UdpateFinalRing(x, x_ring);
        }
        else
        {
            if (m_Player->GetMovedLength() < 0)
            {
                x = 1;
            }
            m_BackGround->UpdateMoveLenx(x);
            m_Obstacle->UpdateMoveLenx(x, x_ring);
        }

        m_Player->UdpateMovedLength(m_BackGround->GetMoveLenx());
        m_Player->PlayerUpdate(deltaTime, iCheck);

        m_BackGround->Update(deltaTime, m_Player->GetMovedLength(), 0, m_iBonusScore, m_Player->GetScore(), m_Player->GetLife(), m_Obstacle->GetGoalCollider());

        if (m_Obstacle->GetGoalCollider())
        {
            m_fTime += deltaTime;
            if (5.0f <= m_fTime)
            {
                if (MessageBox(g_hwnd, L"축하합니다! ok를 누르시면 계속진행됩니다.", L"!!게임 승리!!", MB_OK) == IDOK)
                {
                    m_iTotalScore = m_BackGround->GetTotalScore();
                    m_Rank->SaveRank(m_iTotalScore);
                    m_fTime = 0;
                    m_CurrSelectState = SELECT_DEFAULT;
                    m_Player->Reset();
                    m_BackGround->Reset();
                    m_Obstacle->Reset();
                    m_iBonusScore = 10000;
                    m_Player->ResetLife();
                }
            }
        }
        else
            m_iBonusScore -= deltaTime;

        break;
    }
    case SELECT_GAMEOVER:
        m_fTime += deltaTime;
        
        if (1.5f <= m_fTime)
        {
            m_bGameOver = m_Player->DeatCheck();
            m_fTime = 0;
            m_CurrSelectState = SELECT_PLAY1;
            m_Player->Reset();
            m_BackGround->Reset();
            m_Obstacle->Reset();
            m_iBonusScore = 10000;
        }

        if (m_Player->GetLife() <= 0)
        {
            m_iTotalScore = m_Player->GetScore();
            m_Rank->SaveRank(m_iTotalScore);
            m_CurrSelectState = SELECT_DEFAULT;
            m_Player->ResetLife();
        }

        break;      
    }
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

void GameManager::Draw(float deltaTime, HWND hWnd, HDC hdc)
{
    RECT windowRect;
    GetWindowRect(hWnd, &windowRect);

    HDC backDC = CreateCompatibleDC(hdc);
    HBITMAP backBitmap = CreateDIBSectionRe(hdc, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);
    HBITMAP oldBack = (HBITMAP)SelectObject(backDC, backBitmap);

    switch (m_CurrSelectState)
    {
    case SELECT_DEFAULT:
        m_Menu->Draw(backDC, m_ctmp);
        break;
    case SELECT_RANK:
        m_Rank->RankDraw(backDC);
        break;
    case SELECT_PLAY1:
    case SELECT_PLAY2:
    case SELECT_GOAL:
    case SELECT_GAMEOVER:
    
        char buf[256];
        ZeroMemory(buf, sizeof(buf));

        m_BackGround->MapDraw(backDC);
        m_Obstacle->ObstacleDraw(deltaTime, backDC, m_Player);

        if (m_CurrSelectState == SELECT_GAMEOVER)
            m_Player->DrawDie(backDC);
        else if (m_CurrSelectState == SELECT_GOAL)
            m_Player->DrawGoal(backDC);
        else
            m_Player->Draw(backDC);

        if (true == m_Obstacle->GetGoalCollider())
        {
            m_CurrSelectState = SELECT_GOAL;
            m_BackGround->DrawGoal(backDC);
        }

        if (true == m_Obstacle->GetColliderCheck())
        {
            sprintf_s(buf, "충돌 충돌");
            TextOutA(backDC, 50, 500, buf, strlen(buf));
            m_CurrSelectState = SELECT_GAMEOVER;
        }

        // for debugging
/*sprintf_s(buf, "이동 거리 : %d, 점프 높이 : %d", m_Player->GetMovedLength() , m_Player->GetPosy());
  TextOutA(backDC, 100, 50, buf, strlen(buf));*/
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

    if (m_BackGround->GetMoveLenx() >= 9100)
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
    delete m_Rank;
}