#pragma once
#include <Windows.h>
#include <string>
#include <time.h>
#include "Character.h"
#include "Map.h"

class GameManager
{
private:
	Character m_Player;
	static GameManager* m_hThis;
public:
	static GameManager* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new GameManager;
		return m_hThis;
	}
	void InitPlayer(HWND hWnd);
	void DrawPlayer(HWND hWnd, HDC hdc)
	{
		m_Player.Draw(hdc);
	}

	GameManager();
	~GameManager();


};

