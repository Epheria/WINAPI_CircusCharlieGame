#include "GameManager.h"

GameManager* GameManager::m_hThis = NULL;

GameManager::GameManager()
{
}

void GameManager::InitPlayer(HWND hWnd)
{
	//BitMapManager::GetInstance()->Init(hWnd);
	m_Player.Init(100, 100);
}

GameManager::~GameManager()
{
}