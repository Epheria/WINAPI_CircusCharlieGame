#include "Menu.h"

Menu::Menu()
{
	m_star = 4;
}

void Menu::Init(MENU Index, int x, int y)
{
	int index;
	for (int i = MENU_SELECT; i < MENU_END; i++)
	{
		if (i == 0 || i == 1)
			index = 14;
		else if (i == 2)
			index = 23;
		else
			index = 27;
		m_pBitMap[i] = BitMapManager::GetInstance()->GetImage((IMAGE)(i + index));
	}
	m_ix = x;
	m_iy = y;
}

void Menu::Draw(HDC hdc, char y)
{
	DrawMenu(hdc);
	DrawStar(hdc);
	DrawPoint(hdc, y);
}

void Menu::DrawStar(HDC hdc)
{
	if (m_star >= 6)
	{
		m_star = 4;
	}

	for (int i = 0; i < 16; i++)
	{
		m_pBitMap[(MENU)m_star]->Draw(hdc, 450 + (i * 14), 173);
	}

	/*for (int i = 0; i < 16; i++)
	{
		m_pBitMap[(MENU)m_star]->Draw(hdc, 450 + (i * 14), 173);
		m_pBitMap[(MENU)m_star]->Draw(hdc, 450 + (i * 14), 80);
		if (m_star >= 6)
		{
			m_star = 4;
		}
		m_star++;
	}

	for (int j = 0; j < 6; j++)
	{
		m_pBitMap[(MENU)m_star]->Draw(hdc, 440, 95 + (j * 13));
		m_pBitMap[(MENU)m_star]->Draw(hdc, 670, 95 + (j * 13));
		if (m_star >= 6)
		{
			m_star = 4;
		}
		m_star++;
	}*/

	m_star++;
}

void Menu::DrawMenu(HDC hdc)
{
	m_pBitMap[MENU_TITLE1]->Draw(hdc, 450, 100);
	m_pBitMap[MENU_SELECT]->Draw(hdc, 400, 200);
	m_pBitMap[MENU_PLAYER]->Draw(hdc, 500, 360);
}

void Menu::DrawPoint(HDC hdc, char y)
{
	m_pBitMap[MENU_POINT]->Draw(hdc, 400, 280 + y*80);
}

Menu::~Menu()
{
}