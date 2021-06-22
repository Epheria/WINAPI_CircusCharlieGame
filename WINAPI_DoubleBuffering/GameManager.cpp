#include "GameManager.h"

GameManager* GameManager::m_hThis = NULL;

GameManager::GameManager()
{
	m_Player = new Character;
	m_BackGround = new Map;
}

void GameManager::InitPlayer(HWND hWnd)
{
	//BitMapManager::GetInstance()->Init(hWnd);
	m_Player->Init(50, 285);
}

void GameManager::InitMap(HWND hWnd)
{
	m_BackGround->Init(BACKGROUND_TRACK, 0, 0);
}

void GameManager::Update(float deltaTime)
{
    /*if (m_BackGround->GetMoveLenx() >= 8000)
    {

    }*/
    int x = m_Player->GetDistx(deltaTime);

    if (GetAsyncKeyState(VK_RIGHT) && false == m_Player->GetJumpStatus())
    {
        m_Player->UpdateDirection(DIR_RIGHT);
        m_BackGround->UpdateMoveLenx(x);
    }
    else if (GetAsyncKeyState(VK_LEFT) && false == m_Player->GetJumpStatus())
    {
        m_Player->UpdateDirection(DIR_LEFT);

        if (m_BackGround->GetMoveLenx() <= 0)
            x = 0;

        m_BackGround->UpdateMoveLenx(-x);
    }
    else
        m_Player->UpdateDirection(DIR_IDLE);


    if (GetAsyncKeyState(VK_SPACE))
    {
        if (false == m_Player->GetJumpStatus())
        {
            m_Player->UpdateJumpStatus(true);
        }

        if (m_Player->GetDirection() == DIR_RIGHT)
            m_BackGround->UpdateMoveLenx(x);
        else if (m_Player->GetDirection() == DIR_LEFT)
            m_BackGround->UpdateMoveLenx(-x);
    }

    m_Player->PlayerUpdate(deltaTime);
}



void GameManager::Draw(HDC backDC, char buf[])
{
   m_BackGround->MapDraw(backDC);
   m_Player->Draw(backDC);

   sprintf(buf, "이동 거리 : %d", m_BackGround->GetMoveLenx());
   TextOutA(backDC, 100, 50, buf, strlen(buf));
}

GameManager::~GameManager()
{
	delete m_Player;
	delete m_BackGround;
}