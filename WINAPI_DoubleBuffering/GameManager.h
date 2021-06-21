#pragma once
#include <Windows.h>
#include <string>
#include <time.h>
#include <vector>
#include "Character.h"
#include "Map.h"

enum MAPSIZE
{
	SIZE_MAPX = 1100,
	SIZE_MAPY = 700,
	SIZE_BACKX = 65,
	SIZE_BACKY = 66
};

class GameManager
{
private:
	Character* m_Player;
	Map* m_BackGround;
	static GameManager* m_hThis;
public:
	static GameManager* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new GameManager;
		return m_hThis;
	}
	void Update(LONGLONG checkTime, LONGLONG limitTime);
	void InitPlayer(HWND hWnd);
	void InitMap(HWND hWnd);
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

