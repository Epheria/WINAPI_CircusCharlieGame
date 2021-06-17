#pragma once
#include "BitMap.h"
#include "BitMapManager.h"

enum MOVE_STATUS
{
	MOVE_FRONT,
	MOVE_IDLE,
	MOVE_BACK,
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
	inline BitMap* GetCardImage(MOVE_STATUS Index)
	{
		return m_pBitMap[Index];
	}
	void Init(int x, int y);
	void Draw(HDC hdc);
	bool ColliderCheck(POINT point);
	~Character();
};

