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

	// 작은링, 큰링 두개의 위치가 0이되면 다시 맵의 오른쪽 끝에 그려주기
	if (0 >= m_iRingx)
	{
		m_iRingx = SIZE_MAPX;
	}
	if (0 >= m_iRingx2)
	{
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

	for (int i = 0; i < 6; i++) // 불 단지 2개, 화염 링 위쪽 & 아래쪽
	{
		switch (i)
		{
		case 0:
			m_BitMapRect.left = m_ix + x;
			m_BitMapRect.top = m_iy + 10;
			m_BitMapRect.right = m_BitMapRect.left + m_pBitMap[OBS_FIRE1]->GetSize().cx;
			m_BitMapRect.bottom = m_BitMapRect.top + m_pBitMap[OBS_FIRE1]->GetSize().cy - 10;
			break;
		case 1:
			m_BitMapRect.left = m_ix2 + x;
			m_BitMapRect.top = m_iy + 10;
			m_BitMapRect.right = m_BitMapRect.left + m_pBitMap[OBS_FIRE1]->GetSize().cx;
			m_BitMapRect.bottom = m_BitMapRect.top + m_pBitMap[OBS_FIRE1]->GetSize().cy - 10;
			break;
		case 2:
			m_BitMapRect.left = m_iRingx + 10;
			m_BitMapRect.top = 170;
			m_BitMapRect.right = m_BitMapRect.left + m_pBitMap[OBS_RING1]->GetSize().cx * 2.0f - 10;
			m_BitMapRect.bottom = 190;
			break;
		case 3:
			m_BitMapRect.left = m_iRingx + 10;
			m_BitMapRect.top = 280;
			m_BitMapRect.right = m_BitMapRect.left + m_pBitMap[OBS_RING1]->GetSize().cx * 2.0f - 20;
			m_BitMapRect.bottom = 300;
			break;
		case 4:
			m_BitMapRect.left = m_iRingx2 + 10;
			m_BitMapRect.top = 170;
			m_BitMapRect.right = m_BitMapRect.left + m_pBitMap[OBS_LITTLERING1]->GetSize().cx * 2.0f - 10;
			m_BitMapRect.bottom = 190;
			break;
		case 5:
			m_BitMapRect.left = m_iRingx2 + 10;
			m_BitMapRect.top = 265;
			m_BitMapRect.right = m_BitMapRect.left + m_pBitMap[OBS_LITTLERING1]->GetSize().cx * 2.0f - 20;
			m_BitMapRect.bottom = 275;
			break;
		}

		ColliderCheck(Player);
		if (m_bCollider == true)
			return;

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
	m_iRingx2 = SIZE_MAPX + 500;
}

void Obstacle::ObstacleDraw(HDC hdc, RECT Player)
{
	OBSTACLE STATE;

	for (int i = 0; i < m_iMaxMapDraw; i++)
	{
		m_iy = 300;
		auto x = 50 * i;
		if (i == 7)
		{
			STATE = m_bAnim ? OBS_FIRE1 : OBS_FIRE2;
			RectUpdate(hdc, x, Player);
			m_pBitMap[STATE]->Draw(hdc, m_ix + x, m_iy, true);
			m_pBitMap[STATE]->Draw(hdc, m_ix2 + x, m_iy, true);
		}
		//if (i == 7 && m_bAnim)
		//{
		//	RectUpdate(hdc, x, Player);
		//	m_pBitMap[OBS_FIRE1]->Draw(hdc, m_ix + x, m_iy, true);
		//	m_pBitMap[OBS_FIRE1]->Draw(hdc, m_ix2 + x, m_iy, true);
		//}
		//else if (i == 7 && !m_bAnim)
		//{
		//	RectUpdate(hdc, x, Player);
		//	m_pBitMap[OBS_FIRE2]->Draw(hdc, m_ix + x, m_iy, true);
		//	m_pBitMap[OBS_FIRE2]->Draw(hdc, m_ix2 + x, m_iy, true);
		//}

		m_iy = 170;
		STATE = m_bAnim ? OBS_RING1 : OBS_RING3;
		m_pBitMap[STATE]->Draw(hdc, m_iRingx, m_iy, true);
		m_pBitMap[STATE + 1]->Draw(hdc, m_iRingx + 26, m_iy, true);

		m_iy = 170;
		m_pBitMap[OBS_LITTLERING1]->Draw(hdc, m_iRingx2, m_iy, true);
		m_pBitMap[OBS_LITTLERING2]->Draw(hdc, m_iRingx2 + 26, m_iy, true);
	}
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