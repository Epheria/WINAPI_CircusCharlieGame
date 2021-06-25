#include "Obstacle.h"

Obstacle::Obstacle()
{
	m_bAnim = false;
	m_fTime = 0;
}

void Obstacle::Update(float deltaTime, int x)
{
	m_fTime += deltaTime;
	if (5.5f <= m_fTime)
	{
		if (m_bAnim == false)
			m_bAnim = true;
		else
			m_bAnim = false;
	}

	UpdateMoveLenx(x);
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
	int iCur = 0;
	m_iy = 300;
	for (int i = 0; i < (1200 + m_imoveLen) / 50; i++)
	{
		m_ix = 50 * i - m_imoveLen;
		if (iCur % 15 == 5 && !m_bAnim)
			m_pBitMap[OBS_FIRE1]->Draw(hdc, m_ix, m_iy);
		else if(iCur % 15 == 5 && m_bAnim)
			m_pBitMap[OBS_FIRE2]->Draw(hdc, m_ix, m_iy);
		iCur++;
	}
}

Obstacle::~Obstacle()
{
}