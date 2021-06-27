#pragma once
#include "BitMap.h"
#include "BitMapManager.h"

enum MENU
{
	MENU_SELECT = 0,
	MENU_PLAYER,
	MENU_POINT,
	MENU_TITLE1,
	MENU_STAR1,
	MENU_STAR2,
	MENU_STAR3,
	MENU_END
};

class Menu
{
private:
	MENU m_eMenuState;
	BitMap* m_pBitMap[MENU_END];
	int m_ix;
	int m_iy;
	float m_fTime;
	char m_cAnim;
	void DrawPoint(HDC hdc, char y);
	void DrawMenu(HDC hdc);
	void DrawStar(HDC hdc);
	void StarInfo(HDC hdc, int index , char i, char k);
public:
	Menu();
	void Update(float deltaTime);
	void Init(MENU Index, int x, int y);
	void Draw(HDC hdc, char y);
	~Menu();
};

