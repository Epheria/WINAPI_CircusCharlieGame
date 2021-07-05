#pragma once
#include "BitMap.h"
#include "BitMapManager.h"

enum MOVE_STATUS
{
	MOVE_FRONT,
	MOVE_IDLE,
	MOVE_BACK,
	MOVE_DIE,
	MOVE_END
};

enum DIRECTION
{
	DIR_RIGHT = 1,
	DIR_IDLE = 0,
	DIR_LEFT = -1
};

#define Debug_Rect

class Character
{
private:
	MOVE_STATUS m_eCharacterState;
	BitMap* m_pBitMap[MOVE_END];
	float m_fTime;
	float m_fDeadTime;
	//int m_iCheckMoveStatus;
	int m_iMovedLength;
	int m_ix;
	int m_iy;
	int m_iJumpDirection;
	DIRECTION m_eDirection;
	int m_iSjump;
	int m_iLife;
	int m_iScore;
	bool m_bIsJump;
	bool m_bControl;
	RECT m_BitMapRect;
	RECT m_Recttmp;

	void UpdatePosy(int y)
	{
		m_iy += y;

		if (m_iy <= 180)
			m_iy = 180;
		if (m_iy >= 285)
			m_iy = 285;
	}
public:
	Character();
	inline BitMap* GetPlayerImage(MOVE_STATUS Index)
	{
		return m_pBitMap[Index];
	}
	void UpdateControlState(bool flag)
	{
		m_bControl = flag;
	}
	void UpdateCharStatus(MOVE_STATUS State)
	{
		m_eCharacterState = State;
	}
	bool GetControlState()
	{
		return m_bControl;
	}
	void UpdateSjump(int dir)
	{
		m_iSjump = dir;
	}
	int GetSjump()
	{
		return m_iSjump;
	}
	void UpdatePosx(int x)
	{
		m_ix += x;
		if (m_ix >= 1000)
			m_ix = 1000;
	}
	void UpdateJumpStatus(bool flag)
	{
		m_bIsJump = flag;
		m_iJumpDirection = 1;
	}
	bool GetJumpStatus()
	{
		return m_bIsJump;
	}
	void SetPosx(int x)
	{
		m_ix = x;
	}
	int GetPosx()
	{
		return m_ix;
	}
	int GetPosy()
	{
		return m_iy;
	}
	int GetDirection()
	{
		return m_eDirection;
	}
	int GetDistx(float deltaTime)
	{
		switch (GetDirection())
		{
		case DIRECTION::DIR_LEFT: return -(100 * deltaTime);
		case DIRECTION::DIR_RIGHT: return (100 * deltaTime);
		default: return 0;
		}
	}
	int GetDisty(float deltaTime)
	{
		return 80 * deltaTime;
	}
	void UpdateDirection(DIRECTION dir)
	{
		m_eDirection = dir;
	}
	void UdpateMovedLength(int x)
	{
		m_iMovedLength = x + m_ix;
	}
	int GetMovedLength()
	{
		return m_iMovedLength;
	}
	int GetScore()
	{
		return m_iScore;
	}
	void PlusScore(int iScore)
	{
		m_iScore += iScore;
	}
	void ResetLife()
	{
		m_iLife = 4;
	}
	int GetLife()
	{
		return m_iLife;
	}
	RECT GetRect()
	{
		return m_BitMapRect;
	}
	void RectUpdate();
	void PlayerUpdate(float deltaTime, int iCheck);
	void Init(int x, int y);
	void Reset();
	void Draw(HDC hdc);
	void DrawDie(HDC hdc);
	bool DeatCheck();
	~Character();
};

