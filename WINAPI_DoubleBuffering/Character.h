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

class Character
{
private:
	MOVE_STATUS m_eCharacterState;
	BitMap* m_pBitMap[MOVE_END];
	float m_fTime;
	//int m_iCheckMoveStatus;
	int m_ix;
	int m_iy;
	int m_iJumpDirection;
	DIRECTION m_eDirection;
	int m_iSjump;
	bool m_bIsJump;
	bool m_bControl;
	RECT m_BitMapRect;
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
	}
	void UpdatePosy(int y)
	{
		m_iy += y;
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
	void PlayerUpdate(float deltaTime, int iCheck);
	void Init(int x, int y);
	void Draw(HDC hdc);
	bool ColliderCheck(POINT point);
	~Character();
};

