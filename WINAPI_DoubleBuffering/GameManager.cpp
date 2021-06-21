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

GameManager::~GameManager()
{
	delete m_Player;
	delete m_BackGround;
}