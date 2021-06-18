#pragma once
#include "BitMap.h"
#include "BitMapManager.h"

enum BACKGROUND
{
	BACKGROUND_TRACK,
	BACKGROUND_BACK1,
	BACKGROUND_BACK2,
	BACKGROUND_BACK3,
	BACKGROUND_END
};

class Map
{
private:
	BACKGROUND m_eMapState;
	BitMap* m_pBitMap[BACKGROUND_END];
	int m_ix;
	int m_iy;
	RECT m_BitMapRect;
public:
	Map();
	BitMap* GetMapImage(BACKGROUND Index)
	{
		return m_pBitMap[Index];
	}
	void SetMapState(BACKGROUND Index)
	{
		m_eMapState = Index;
	}
	void Init(BACKGROUND Index, int x, int y);
	void Draw(HDC hdc);
	~Map();
};

