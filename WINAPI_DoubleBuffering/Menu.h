#pragma once
#include "BitMap.h"
#include "BitMapManager.h"

enum MENU
{
	MENU_1,
	MENU_2,
	MENU_POINT,
	MENU_TITLE1,
	MENU_TITLE2,
	MENU_TITLE3,
	MENU_TITLE4,
	MENU_END
};

class Menu
{
private:
	MENU m_eMenuState;
	BitMap* m_pBitMap[MENU_END];
	int m_imoveLen;
	int m_ix;
	int m_iy;
	bool m_bControl;
	RECT m_BitMapRect;
public:
	Menu();
	BitMap* GetMapImage(MENU Index)
	{
		return m_pBitMap[Index];
	}
	void Init(MENU Index, int x, int y);
	void Draw(HDC hdc);
	void DrawPoint(HDC hdc, int y);
	void DrawMenu(HDC hdc);
	~Menu();
};

