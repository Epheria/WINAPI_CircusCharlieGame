#include "Obstacle.h"

Obstacle::Obstacle() : m_bAnim(false), m_fTime(0), m_imoveLen(0), m_bCollider(false), m_bIsGoal(false)
{
	for (int i = 0; i < 4; i++)
		m_bColliderScore[i] = false;
}

void Obstacle::Init(OBSTACLE Index, int x, int y)
{
	m_pBitMap[OBS_FIRE1] = BitMapManager::GetInstance()->GetImage(IMAGE_FIRE_1);
	m_pBitMap[OBS_FIRE2] = BitMapManager::GetInstance()->GetImage(IMAGE_FIRE_2);
	m_pBitMap[OBS_LITTLERING1] = BitMapManager::GetInstance()->GetImage(IMAGE_LITTLERING_1);
	m_pBitMap[OBS_LITTLERING2] = BitMapManager::GetInstance()->GetImage(IMAGE_LITTLERING_2);
	m_pBitMap[OBS_RING1] = BitMapManager::GetInstance()->GetImage(IMAGE_RING_1);
	m_pBitMap[OBS_RING2] = BitMapManager::GetInstance()->GetImage(IMAGE_RING_2);
	m_pBitMap[OBS_RING3] = BitMapManager::GetInstance()->GetImage(IMAGE_RING_3);
	m_pBitMap[OBS_RING4] = BitMapManager::GetInstance()->GetImage(IMAGE_RING_4);
	m_pBitMap[OBS_CASH] = BitMapManager::GetInstance()->GetImage(IMAGE_CASH);
	m_pBitMap[OBS_GOAL] = BitMapManager::GetInstance()->GetImage(IMAGE_GOAL);

	m_ix = x;
	m_iy = y;
	m_iMaxMapDraw = SIZE_MAPX / m_pBitMap[OBS_FIRE1]->GetSize().cx;
	m_iBackGroundLen = m_pBitMap[OBS_FIRE1]->GetSize().cx * m_iMaxMapDraw;
	m_ix2 = m_ix + m_iBackGroundLen;

	m_iRingx = SIZE_MAPX;
	m_iRingx2 = SIZE_MAPX + 500;
}

void Obstacle::Update(float deltaTime, int iPlayerMovedLen)
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
	if (m_bIsGoal == false)
	{
		if (0 >= m_iRingx)
		{
			m_iRingx = SIZE_MAPX;
			m_bColliderScore[2] = false;
		}
		if (0 >= m_iRingx2)
		{
			m_iRingx2 = SIZE_MAPX;
			m_bColliderScore[3] = false;
		}
	}

	m_iPlayerMovedLen = iPlayerMovedLen;
}

void Obstacle::SetRect(RECT& rect, int left, int right, int top, int bottom)
{
	rect.left = left;
	rect.right = left + right;
	rect.top = top;
	rect.bottom = top + bottom;
}

void Obstacle::RectUpdate(float deltaTime, HDC hdc, int x, Character* Player)
{
	if (m_imoveLen >= 9100)
	{
		SetRect(m_GoalRect, 1000, 100, 300, 100);
		ColliderGoalCheck(Player);
		if (m_bIsGoal == true)
			return;
#ifdef Debug_Rect
		Rectangle(hdc, m_GoalRect.left + 5, m_GoalRect.top + 5, m_GoalRect.right - 5, m_GoalRect.bottom);
#endif // Debug_Rect
	}

	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			SetRect(m_ScoreRect, m_ix + 150, 10, 240, 40);
			break;
		case 1:
			SetRect(m_ScoreRect, m_ix2 + 150, 10, 240, 40);
			break;
		case 2:
			SetRect(m_ScoreRect, m_iRingx + 10, 10, 210, 40);
			break;
		case 3:
			SetRect(m_ScoreRect, m_iRingx2 + 10, 10, 210, 40);
			break;
		}

		if(m_bColliderScore[i] == false)
			ColliderScoreCheck(deltaTime, Player, i);

#ifdef Debug_Rect
			Rectangle(hdc, m_ScoreRect.left, m_ScoreRect.top, m_ScoreRect.right, m_ScoreRect.bottom);
#endif // Debug_Rect
	}

	for (int i = 0; i < 4; i++) // 불 단지 2개, 화염 링 위쪽 & 아래쪽
	{
		switch (i)
		{
		case 0:
			SetRect(m_BitMapRect, m_ix + 150, 50 , m_iy + 10, 40);
			break;
		case 1:
			SetRect(m_BitMapRect, m_ix2 + 150, 50, m_iy + 10, 40);
			break;
		case 2:
			SetRect(m_BitMapRect, m_iRingx + 10, 22, 280, 20);
			break;
		case 3:
			SetRect(m_BitMapRect, m_iRingx2 + 10, 22, 265, 10);
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

void Obstacle::ObstacleDraw(float deltaTime, HDC hdc, Character* Player)
{
	char buf[256];
	ZeroMemory(buf, sizeof(buf));

	OBSTACLE STATE;
	if (m_imoveLen >= 9100)
		m_pBitMap[OBS_GOAL]->Draw(hdc, 1000, 300);

	for (int i = 0; i < m_iMaxMapDraw; i++)
	{
		m_iy = 300;
		auto x = 50 * i;
		if (i == 3)
		{
			STATE = m_bAnim ? OBS_FIRE1 : OBS_FIRE2;
			m_pBitMap[STATE]->Draw(hdc, m_ix + x, m_iy);
			m_pBitMap[STATE]->Draw(hdc, m_ix2 + x, m_iy);
			RectUpdate(deltaTime, hdc, x, Player);
		}
		if (m_bIsGoal == false)
		{
			m_iy = 170;
			STATE = m_bAnim ? OBS_RING1 : OBS_RING3;
			m_pBitMap[STATE]->Draw(hdc, m_iRingx, m_iy);
			m_pBitMap[STATE + 1]->Draw(hdc, m_iRingx + 26, m_iy);

			m_iy = 170;
			m_pBitMap[OBS_LITTLERING1]->Draw(hdc, m_iRingx2, m_iy);
			m_pBitMap[OBS_LITTLERING2]->Draw(hdc, m_iRingx2 + 26, m_iy);

			if (m_bColliderScore[3] == false)
				m_pBitMap[OBS_CASH]->Draw(hdc, m_iRingx2 + 10, m_iy + 20);
		}
	}
}

void Obstacle::ColliderCheck(Character* Player)
{
	RECT tmp = Player->GetRect();
	if (IntersectRect(&m_Recttmp, &m_BitMapRect, &tmp))
	{
		m_bCollider = true;
	}
	else
		m_bCollider = false;
}

void Obstacle::ColliderGoalCheck(Character* Player)
{
	RECT tmp = Player->GetRect();
	if (IntersectRect(&m_Recttmp, &m_GoalRect, &tmp))
	{
		m_bIsGoal = true;
	}
	else
		m_bIsGoal = false;
}

void Obstacle::ColliderScoreCheck(float deltaTime, Character* Player, int index)
{
	RECT tmp = Player->GetRect();
	if (IntersectRect(&m_Recttmp, &m_ScoreRect, &tmp))
	{
		m_bColliderScore[index] = true;
		
		if(m_bColliderScore[3] == true)
			Player->PlusScore(200);
		else
			Player->PlusScore(100);
	}
}

void Obstacle::Reset()
{
	m_imoveLen = 0;
	m_ix = 0;
	m_ix2 = m_ix + m_iBackGroundLen;

	m_iRingx = SIZE_MAPX;
	m_iRingx2 = SIZE_MAPX + 500;
	for (int i = 0; i < 4; i++)
		m_bColliderScore[i] = false;
	m_bIsGoal = false;
}

Obstacle::~Obstacle()
{
}