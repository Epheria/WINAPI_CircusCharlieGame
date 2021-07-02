#include "Obstacle.h"

Obstacle::Obstacle()
{
	m_bAnim = false;
	m_bCollider = false;
	m_fTime = 0;
}

void Obstacle::Update(float deltaTime)
{
	m_fTime += deltaTime;
	if (1.0f <= m_fTime)
	{
		m_fTime = 0;
		if (m_bAnim == false)
			m_bAnim = true;
		else
			m_bAnim = false;
	}
	if (0 >= m_iRingx)
	{
		// 시간 x 위치값으로

		m_iRingx = SIZE_MAPX;
		m_iRingx2 = SIZE_MAPX;
	}


	/*m_fTime += deltaTime;
	if (5.0f <= m_fTime)
	{
		m_fTime = 0;

		m_iRingx = SIZE_MAPX;
		m_iRingx2 = SIZE_MAPX;
	}*/
}

void Obstacle::RectUpdate(HDC hdc, int x, RECT Player)
{
	// RECT 한개로 FOR 문돌려서  할 수 있음

//	m_BitMapRect.left = m_ix + x;
//	m_BitMapRect.top = m_iy;
//	m_BitMapRect.right = m_BitMapRect.left + m_pBitMap[OBS_FIRE1]->GetSize().cx;
//	m_BitMapRect.bottom = m_BitMapRect.top + m_pBitMap[OBS_FIRE1]->GetSize().cy;
//
//	m_BitMapRect.left = m_ix2 + x;
//	m_BitMapRect.top = m_iy;
//	m_BitMapRect.right = m_BitMapRect.left + m_pBitMap[OBS_FIRE1]->GetSize().cx;
//	m_BitMapRect.bottom = m_BitMapRect.top + m_pBitMap[OBS_FIRE1]->GetSize().cy;
//
//#ifdef Debug_Rect
//	Rectangle(hdc, m_BitMapRect.left + 5, m_BitMapRect.top + 5, m_BitMapRect.right - 5, m_BitMapRect.bottom);
//#endif // Debug_Rect

	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			m_BitMapRect.left = m_ix + x;
			m_BitMapRect.top = m_iy;
			m_BitMapRect.right = m_BitMapRect.left + m_pBitMap[OBS_FIRE1]->GetSize().cx;
			m_BitMapRect.bottom = m_BitMapRect.top + m_pBitMap[OBS_FIRE1]->GetSize().cy;
			ColliderCheck(Player);
			if(m_bCollider == true)
				return;
			break;
		case 1:
			m_BitMapRect.left = m_ix2 + x;
			m_BitMapRect.top = m_iy;
			m_BitMapRect.right = m_BitMapRect.left + m_pBitMap[OBS_FIRE1]->GetSize().cx;
			m_BitMapRect.bottom = m_BitMapRect.top + m_pBitMap[OBS_FIRE1]->GetSize().cy;
			ColliderCheck(Player);
			if (m_bCollider == true)
				return;
			break;
		case 2:
			m_BitMapRect.left = m_iRingx;
			m_BitMapRect.top = 170;
			m_BitMapRect.right = m_BitMapRect.left + m_pBitMap[OBS_RING1]->GetSize().cx * 2.0f;
			m_BitMapRect.bottom = 190;
			ColliderCheck(Player);
			if (m_bCollider == true)
				return;
			break;
		case 3:
			m_BitMapRect.left = m_iRingx + 5;
			m_BitMapRect.top = 280;
			m_BitMapRect.right = m_BitMapRect.left + m_pBitMap[OBS_RING1]->GetSize().cx * 2.0f - 5;
			m_BitMapRect.bottom = 300;
			ColliderCheck(Player);
			if (m_bCollider == true)
				return;
			break;
		}

#ifdef Debug_Rect
		Rectangle(hdc, m_BitMapRect.left + 5, m_BitMapRect.top + 5, m_BitMapRect.right - 5, m_BitMapRect.bottom);
#endif // Debug_Rect
	}

}

void Obstacle::Init(OBSTACLE Index, int x, int y)
{
	int index;
	for (int i = OBS_FIRE1; i < OBS_END; i++)
	{
		if (i == 0 || i == 1)
			index = 6;
		else if (i == 2 || i == 3)
			index = 10;
		else
			index = 22;
		m_pBitMap[i] = BitMapManager::GetInstance()->GetImage((IMAGE)(i + index));

	}
	m_ix = x;
	m_iy = y;
	m_iMaxMapDraw = SIZE_MAPX / m_pBitMap[OBS_FIRE1]->GetSize().cx;
	m_iBackGroundLen = m_pBitMap[OBS_FIRE1]->GetSize().cx * m_iMaxMapDraw;
	m_ix2 = m_ix + m_iBackGroundLen;

	m_iRingx = SIZE_MAPX;
	m_iRingx2 = SIZE_MAPX;
}

void Obstacle::ObstacleDraw(HDC hdc, RECT Player)
{
	//for (int i = 0; 2 > i; i++)
	//{
	//	m_ix = (i * m_pBitMap[0]->GetSize().cx * 15) + 250 - m_imoveLen;
	//	RectUpdate();
	//	m_pBitMap[OBS_FIRE1]->Draw(hdc, m_ix, m_iy);
	//}

	for (int i = 0; i < m_iMaxMapDraw; i++)
	{
		m_iy = 300;
		auto x = 50 * i;

		if (i == 7 && m_bAnim)
		{
			RectUpdate(hdc, x, Player);
			m_pBitMap[OBS_FIRE1]->Draw(hdc, m_ix + x, m_iy, true);
			m_pBitMap[OBS_FIRE1]->Draw(hdc, m_ix2 + x, m_iy, true);
		}
		else if (i == 7 && !m_bAnim)
		{
			RectUpdate(hdc, x, Player);
			m_pBitMap[OBS_FIRE2]->Draw(hdc, m_ix + x, m_iy, true);
			m_pBitMap[OBS_FIRE2]->Draw(hdc, m_ix2 + x, m_iy, true);
		}


		m_iy = 170;
		if (m_bAnim)
		{
			m_pBitMap[OBS_RING1]->Draw(hdc, m_iRingx, m_iy, true);
			m_pBitMap[OBS_RING2]->Draw(hdc, m_iRingx + 26, m_iy, true);
		}
		else if (!m_bAnim)
		{
			m_pBitMap[OBS_RING3]->Draw(hdc, m_iRingx, m_iy, true);
			m_pBitMap[OBS_RING4]->Draw(hdc, m_iRingx + 26, m_iy, true);
		}
		//RectUpdate(hdc, x);
	}

	//m_pBitMap[OBS_RING1]->Draw(hdc, m_iRingx2, m_iy, true);
	//m_pBitMap[OBS_RING2]->Draw(hdc, m_iRingx2 + 26, m_iy, true);


	/*int iCur = ((1200 + m_imoveLen) / 50) - 1;
	for (int i = ((1200 + m_imoveLen) / 50) - 1; i >= 0; i--, iCur--)
	{
		m_ix = 50 * i - m_imoveLen;
		if (iCur % 15 == 5 && !m_bAnim)
		{
			RectUpdate();
			m_pBitMap[OBS_FIRE1]->Draw(hdc, m_ix, m_iy);
		}
		else if (iCur % 15 == 5 && m_bAnim)
		{
			RectUpdate();
			m_pBitMap[OBS_FIRE2]->Draw(hdc, m_ix, m_iy);
		}*/

}



void Obstacle::ColliderCheck(RECT Player)
{
	if (IntersectRect(&m_Recttmp, &m_BitMapRect, &Player))
	{
		m_bCollider = true;
	}
	else
		m_bCollider = false;
}

Obstacle::~Obstacle()
{
}