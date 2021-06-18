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
	m_Player->Init(10, 400);
}

void GameManager::InitMap(HWND hWnd)
{
	//Map* tmp = new Map;
	for (int x = 0; x < 10; x++)
	{
		m_BackGround->Init(BACKGROUND_TRACK, x * 67, 183);
		m_TrackList.push_back(m_BackGround);
	}
	for (int x = 0; x < 4; x+=3)
	{
		m_BackGround->Init(BACKGROUND_BACK1, x * 65, 116);
		m_BackGroundList.push_back(m_BackGround);
		m_BackGround->Init(BACKGROUND_BACK2, (x+1) * 65, 116);
		m_BackGroundList.push_back(m_BackGround);
		m_BackGround->Init(BACKGROUND_BACK3, (x+2) * 65, 116);
		m_BackGroundList.push_back(m_BackGround);
	} 
	//delete tmp;
}

void GameManager::DrawMap(HDC hdc)
{
	for (auto& a : m_TrackList)
	{
		a->Draw(hdc);
	}
	for (auto& b : m_BackGroundList)
	{
		b->Draw(hdc);
	}
}

GameManager::~GameManager()
{
	delete m_Player;
	delete m_BackGround;
}