#include "Map.h"


Map::Map()
{
	m_imoveLen = 0;
	m_ix = 0;
	m_eMapState = BACKGROUND_TRACK;
	m_bControl = true;
	m_iMaxMapDraw = 0;
	m_ix2 = 0;
}

void Map::Init(BACKGROUND Index, int x, int y)
{
	m_pBitMap[BACKGROUND_TRACK] = BitMapManager::GetInstance()->GetImage(IMAGE_BACK_1);
	m_pBitMap[BACKGROUND_BACK1] = BitMapManager::GetInstance()->GetImage(IMAGE_BACK_2);
	m_pBitMap[BACKGROUND_BACK2] = BitMapManager::GetInstance()->GetImage(IMAGE_BACK_3);
	m_pBitMap[BACKGROUND_BACK3] = BitMapManager::GetInstance()->GetImage(IMAGE_BACK_4);
	m_ix = x;
	m_iy = y;
	m_BitMapRect.left = x;
	m_BitMapRect.top = y;
	m_BitMapRect.right = m_BitMapRect.left + m_pBitMap[Index]->GetSize().cx;
	m_BitMapRect.bottom = m_BitMapRect.top + m_pBitMap[Index]->GetSize().cy;
	m_iMaxMapDraw = SIZE_MAPX / m_pBitMap[BACKGROUND_BACK1]->GetSize().cx;
	m_iBackGroundLen = m_pBitMap[BACKGROUND_BACK1]->GetSize().cx * m_iMaxMapDraw;
	m_ix2 = m_ix + m_iBackGroundLen;
}

void Map::MapDraw(HDC hdc)
{
	for (int i = 0; i <= m_iMaxMapDraw; i++)
	{
		m_iy = 100;
		auto x = 66 * i;

		if (i == 7)
		{
			m_pBitMap[BACKGROUND_BACK1]->Draw(hdc, m_ix + x, m_iy, false);
			m_pBitMap[BACKGROUND_BACK1]->Draw(hdc, m_ix2 + x, m_iy, false);
		}
		else
		{
			m_pBitMap[BACKGROUND_BACK2]->Draw(hdc, m_ix + x, m_iy, false);
			m_pBitMap[BACKGROUND_BACK2]->Draw(hdc, m_ix2 + x, m_iy, false);
		}
		m_iy = 165;
		m_pBitMap[BACKGROUND_TRACK]->Draw(hdc, m_ix + x, m_iy, false);
		m_pBitMap[BACKGROUND_TRACK]->Draw(hdc, m_ix2 + x, m_iy, false);
	}

	//for (int i = 0; 2 > i; i++)
	//{
	//	m_ix = icx - m_imoveLen;
	//	if (m_ix / icx == 7)
	//		m_pBitMap[BACKGROUND_BACK1]->Draw(hdc, m_ix, m_iy);
	//	else
	//		m_pBitMap[BACKGROUND_BACK2]->Draw(hdc, m_ix, m_iy);


	//}
	//m_ix += icx - m_imoveLen;
	//for (int i = 0; i < (1200 + m_imoveLen) / 65; i++)
	//{
	//	m_ix = 65 * i - m_imoveLen;
	//	if (iCur % 7 == 0)
	//		m_pBitMap[BACKGROUND_BACK1]->Draw(hdc, m_ix, m_iy);
	//	else
	//		m_pBitMap[BACKGROUND_BACK2]->Draw(hdc, m_ix, m_iy);
	//	iCur++;
	//}
	//m_iy = 165;

	//for (int i = 0; i <= m_iMaxMapDraw; i++)
	//{
	//	auto x = 67 * i;
	//	m_pBitMap[BACKGROUND_TRACK]->Draw(hdc, m_ix + x, m_iy, false);
	//	m_pBitMap[BACKGROUND_TRACK]->Draw(hdc, m_ix2 + x, m_iy, false);
	//}
}

Map::~Map()
{

}