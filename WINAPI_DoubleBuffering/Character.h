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
	int m_ix;
	int m_iy;
	RECT m_BitMapRect;
public:
	Character();
	inline BitMap* GetPlayerImage(MOVE_STATUS Index)
	{
		return m_pBitMap[Index];
	}
	void UpdatePosx(int x)
	{
		m_ix += x;
	}
	void UpdatePosy(int y)
	{
		m_iy += y;
	}
	void UpdateStatus(MOVE_STATUS Index)
	{
		m_eCharacterState = Index;
	}
	int GetPosx()
	{
		return m_ix;
	}
	int GetPosy()
	{
		return m_iy;
	}
	void Init(int x, int y);
	void Draw(HDC hdc);
	bool ColliderCheck(POINT point);
	~Character();
};

