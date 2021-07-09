#pragma once
#include "Character.h"
#include "Map.h"
#include "Menu.h"
#include "Obstacle.h"
#include "Rank.h"

enum SELECT
{
	SELECT_DEFAULT = -1,
	SELECT_PLAY1,
	SELECT_PLAY2,
	SELECT_RANK,
	SELECT_GOAL,
	SELECT_GAMEOVER
};

class GameManager
{
private:
	Character* m_Player;
	Map* m_BackGround;
	Menu* m_Menu;
	Obstacle* m_Obstacle;
	Rank* m_Rank;
	char m_CurrSelectState;
	char m_ctmp;
	int m_iBonusScore;
	int m_iTotalScore;
	float m_fTime, m_fTime2;
	bool m_bGameOver;
	static GameManager* m_hThis;
public:
	static GameManager* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new GameManager;
		return m_hThis;
	}
	void Update(float deltaTime, int iCheck, HWND g_hwnd);
	void Draw(float deltaTime, HWND hWnd, HDC hdc);
	void Init(HWND hWnd);
	bool FinalLineCheck(int x);
	HBITMAP CreateDIBSectionRe(HDC hdc, int width, int height);
	GameManager();
	~GameManager();
};

