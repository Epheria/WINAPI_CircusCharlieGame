#include "Menu.h"

Menu::Menu()
{
}

void Menu::Init(MENU Index, int x, int y)
{
	int index;
	for (int i = MENU_1; i < MENU_END; i++)
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
	m_BitMapRect.left = x;
	m_BitMapRect.top = y;
	m_BitMapRect.right = m_BitMapRect.left + m_pBitMap[Index]->GetSize().cx;
	m_BitMapRect.bottom = m_BitMapRect.top + m_pBitMap[Index]->GetSize().cy;
}

void Menu::Draw(HDC hdc)
{
	m_pBitMap[m_eMenuState]->Draw(hdc, m_ix, m_iy);
}

void Menu::DrawMenu(HDC hdc)
{
	m_pBitMap[MENU_TITLE1]->Draw(hdc, 450, 100);
	m_pBitMap[MENU_1]->Draw(hdc, 450, 200);
	m_pBitMap[MENU_2]->Draw(hdc, 450, 220);
}

void Menu::DrawPoint(HDC hdc, int y)
{
	m_pBitMap[MENU_POINT]->Draw(hdc, 450, 350 + y);
}

Menu::~Menu()
{
}