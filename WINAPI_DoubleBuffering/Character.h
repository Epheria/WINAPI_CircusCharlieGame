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

class Character
{
private:
	MOVE_STATUS m_eCharacterState;
	BitMap* m_pBitMap[MOVE_END];
	int m_iTime;
	//int m_iCheckMoveStatus;
	int m_ix;
	int m_iy;
	int m_iJumpDirection;
	int m_iDirection;
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
	bool GetControlState()
	{
		return m_bControl;
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
		return m_iDirection;
	}
	int GetDistx(float deltaTime)
	{
		return 100 * deltaTime;
	}
	int GetDisty(float deltaTime)
	{
		return 80 * deltaTime;
	}
	void UpdateDirection(int iDirection)
	{
		m_iDirection = iDirection;
	}
	void PlayerUpdate(float deltaTime);
	void Init(int x, int y);
	void Draw(HDC hdc);
	bool ColliderCheck(POINT point);
	~Character();
};

