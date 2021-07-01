#pragma once
#include <Windows.h>
#include <string>
#include <time.h>
#include <vector>
#include "Character.h"
#include "Map.h"
#include "Menu.h"
#include "Obstacle.h"

enum SELECT
{
	SELECT_MAINMENU,
	SELECT_PLAY
};

class GameManager
{
private:
	Character* m_Player;
	Map* m_BackGround;
	Menu* m_Menu;
	Obstacle* m_Obstacle;
	char m_CurrSelectState;
	char m_ctmp;
	static GameManager* m_hThis;
public:
	static GameManager* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new GameManager;
		return m_hThis;
	}
	void Update(float deltaTime, int iCheck);
	void Draw(HWND hWnd, HDC hdc);
	void Init(HWND hWnd);
	bool FinalLineCheck(int x);
	HBITMAP CreateDIBSectionRe(HDC hdc, int width, int height);
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
	Menu* GetMenu()
	{
		return m_Menu;
	}
	GameManager();
	~GameManager();
};

