#pragma once
#pragma warning(disable:4996)
#include <Windows.h>
#include <string>
#include <time.h>
#include <vector>
#include "Character.h"
#include "Map.h"
#include "Menu.h"

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
	Menu* m_Menu;
	static GameManager* m_hThis;
public:
	static GameManager* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new GameManager;
		return m_hThis;
	}
	int ShowMenu(HWND hWnd, HDC hdc);
	HBITMAP CreateDIBSectionRe(HDC hdc, int width, int height);
	void Update(float deltaTime, int iCheck);
	void Draw(HWND hWnd, HDC hdc);
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
	Menu* GetMenu()
	{
		return m_Menu;
	}
	GameManager();
	~GameManager();


};

