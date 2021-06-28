#include "Obstacle.h"

Obstacle::Obstacle()
{
	m_bAnim = false;
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
}

void Obstacle::RectUpdate()
{
	m_BitMapRect.left = m_ix;
	m_BitMapRect.top = m_iy;
	m_BitMapRect.right = m_BitMapRect.left + m_pBitMap[OBS_FIRE1]->GetSize().cx;
	m_BitMapRect.bottom = m_BitMapRect.top + m_pBitMap[OBS_FIRE1]->GetSize().cy;
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
}

void Obstacle::ObstacleDraw(HDC hdc)
{
	//for (int i = 0; 2 > i; i++)
	//{
	//	m_ix = (i * m_pBitMap[0]->GetSize().cx * 15) + 250 - m_imoveLen;
	//	RectUpdate();
	//	m_pBitMap[OBS_FIRE1]->Draw(hdc, m_ix, m_iy);
	//}

	int iCur = ((1200 + m_imoveLen) / 50) - 1;
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
		}
	}

#ifdef Debug_Rect
	Rectangle(hdc, m_BitMapRect.left, m_BitMapRect.top, m_BitMapRect.right, m_BitMapRect.bottom);
#endif // Debug_Rect
}

bool Obstacle::ColliderCheck(RECT Player)
{

	return IntersectRect(&m_Recttmp, &m_BitMapRect, &Player);
}

Obstacle::~Obstacle()
{
}