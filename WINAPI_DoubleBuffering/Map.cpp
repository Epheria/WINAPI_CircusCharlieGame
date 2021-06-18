#include "Map.h"


Map::Map()
{
	m_eMapState = BACKGROUND_TRACK;
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
}

void Map::Draw(HDC hdc)
{
	m_pBitMap[m_eMapState]->Draw(hdc, m_ix, m_iy);
}

Map::~Map()
{

}