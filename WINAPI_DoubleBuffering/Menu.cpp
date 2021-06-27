#include "Menu.h"

Menu::Menu()
{
	m_fTime = 0;
	m_cAnim = 0;
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

void Menu::Update(float deltaTime)
{
	m_fTime += deltaTime;
	if (0.5f <= m_fTime)
	{
		m_fTime = 0;

		if (m_cAnim == 0)
			m_cAnim = 1;
		else if (m_cAnim == 1)
			m_cAnim = 2;
		else if (m_cAnim == 2)
			m_cAnim = 0;
	}
}

void Menu::Draw(HDC hdc, char y)
{
	DrawMenu(hdc);
	DrawStar(hdc);
	DrawPoint(hdc, y);
}

void Menu::DrawStar(HDC hdc)
{
	char j = 0 , k = 0;

	for (int i = 0; i < 16; i++)
	{
		if (j > 2)
			j = 0;
		if (k > 5)
			k = 0;

		if (j == 0)
		{
			if (m_cAnim == 0)
				StarInfo(hdc, 4, i, k);
			else if (m_cAnim == 1)
				StarInfo(hdc, 5, i, k);
			else if (m_cAnim == 2)
				StarInfo(hdc, 6, i, k);
		}
		else if(j == 1)
		{
			if (m_cAnim == 1)
				StarInfo(hdc, 4, i, k);
			else if (m_cAnim == 2)
				StarInfo(hdc, 5, i, k);
			else if (m_cAnim == 0)
				StarInfo(hdc, 6, i, k);
		}
		else if(j == 2)
		{
			if (m_cAnim == 2)
				StarInfo(hdc, 4, i, k);
			else if (m_cAnim == 0)
				StarInfo(hdc, 5, i, k);
			else if (m_cAnim == 1)
				StarInfo(hdc, 6, i, k);
		}
		j++;
		k++;
	}
}

void Menu::StarInfo(HDC hdc, int index, char i, char k)
{
	m_pBitMap[index]->Draw(hdc, 450 + (i * 14), 173);
	m_pBitMap[index]->Draw(hdc, 660 - (i * 14), 80);

	m_pBitMap[index]->Draw(hdc, 440, 95 + (k * 13));
	m_pBitMap[index]->Draw(hdc, 670, 160 - (k * 13));
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