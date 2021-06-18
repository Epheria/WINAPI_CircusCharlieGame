#pragma once
#include <Windows.h>
#include <string>
#include <time.h>
#include <vector>
#include "Character.h"
#include "Map.h"

class GameManager
{
private:
	Character* m_Player;
	Map* m_BackGround;
	std::vector<Map*> m_BackGroundList;
	std::vector<Map*> m_TrackList;
	static GameManager* m_hThis;
public:
	static GameManager* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new GameManager;
		return m_hThis;
	}
	void InitPlayer(HWND hWnd);
	void InitMap(HWND hWnd);
	void DrawMap(HDC hdc);
	//void DrawPlayer(HWND hWnd, HDC hdc)
	//{
	//	m_Player->Draw(hdc, Index);
	//}
	Character* GetPlayer()
	{
		return m_Player;
	}
	Map* GetBackGround()
	{
		return m_BackGround;
	}
	GameManager();
	~GameManager();


};

