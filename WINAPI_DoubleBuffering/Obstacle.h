#pragma once
#include "BitMap.h"
#include "BitMapManager.h"
#include "Character.h"

enum OBSTACLE
{
	OBS_FIRE1,
	OBS_FIRE2,
	OBS_LITTLERING1,
	OBS_LITTLERING2,
	OBS_RING1,
	OBS_RING2,
	OBS_RING3,
	OBS_RING4,
	OBS_CASH,
	OBS_GOAL,
	OBS_END
};

//#define Debug_Rect

class Obstacle
{
private:
	BitMap* m_pBitMap[OBS_END];
	RECT m_BitMapRect;
	RECT m_GoalRect;
	RECT m_ScoreRect;
	float m_fTime;
	int m_imoveLen;
	int m_iPlayerMovedLen;
	int m_iBackGroundLen;
	int m_iMaxMapDraw;
	int m_ix;
	int m_ix2;
	int m_iRingx;
	int m_iRingx2;
	int m_iy;
	bool m_bAnim;
	bool m_bCollider;
	bool m_bIsGoal;
	bool m_bColliderScore[4];
	RECT m_Recttmp;
public:
	Obstacle();
	void UdpateFinalRing(int x, int x_ring)
	{
		m_iRingx -= x_ring;
		m_iRingx2 -= x_ring;
	}
	void UpdateMoveLenx(int x, int x_ring)
	{
		m_ix -= x;
		m_ix2 -= x;
		m_imoveLen += x;

		m_iRingx -= x_ring + x;
		m_iRingx2 -= x_ring + x;

		m_iy = 300;

		if (0 < x)
		{
			if (m_ix <= -(m_iBackGroundLen))
			{
				m_ix = m_ix2 + m_iBackGroundLen;
				for (int i = 0; i < 2; i++)
					m_bColliderScore[i] = false;
			}
			if (m_ix2 <= -(m_iBackGroundLen))
			{
				m_ix2 = m_ix + m_iBackGroundLen;
				for (int i = 0; i < 2; i++)
					m_bColliderScore[i] = false;
			}
		}
		else if (0 > x)
		{
			if (m_ix >= (m_iBackGroundLen))
			{
				m_ix = m_ix2 - m_iBackGroundLen;
			}
			if (m_ix2 >= (m_iBackGroundLen))
			{
				m_ix2 = m_ix - m_iBackGroundLen;
			}
		}
	}
	bool GetColliderCheck()
	{
		return m_bCollider;
	}
	bool GetGoalCollider()
	{
		return m_bIsGoal;
	}
	void Update(float deltaTime, int iPlayerMovedLen);
	void Init(OBSTACLE Index, int x, int y);
	void RectUpdate(float deltaTime, HDC hdc, int x, Character* Player);
	void ObstacleDraw(float deltaTime, HDC hdc, Character* Player);
	void ColliderCheck(Character* Player);
	void ColliderGoalCheck(Character* Player);
	void ColliderScoreCheck(float deltaTime, Character* Player, int index);
	void SetRect(RECT& rect, int left, int right, int top, int bottom);
	void Reset();
	~Obstacle();
};
