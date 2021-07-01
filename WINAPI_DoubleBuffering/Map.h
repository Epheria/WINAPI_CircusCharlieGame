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
	int m_imoveLen;
	int m_iBackGroundLen;
	int m_ix;
	int m_ix2;
	int m_iy;
	int m_iMaxMapDraw;
	bool m_bControl;
	RECT m_BitMapRect;
public:
	Map();
	void SetMapState(BACKGROUND Index)
	{
		m_eMapState = Index;
	}
	void UpdateControlState(bool flag)
	{
		m_bControl = flag;
	}
	bool GetControlState()
	{
		return m_bControl;
	}
	int GetMoveLenx()
	{
		return m_imoveLen;
	}
	void UpdateMoveLenx(int x)
	{
		m_imoveLen += x;
		m_ix -= x;
		m_ix2 -= x;

		if (0 < x)
		{
			if (m_ix <= -(m_iBackGroundLen))
			{
				m_ix = m_ix2 + m_iBackGroundLen;
			}
			if (m_ix2 <= -(m_iBackGroundLen))
			{
				m_ix2 = m_ix + m_iBackGroundLen;
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

		//if (m_imoveLen <= 0)
		//	m_imoveLen = 0;
		//if (m_imoveLen >= 5000)
		//	m_imoveLen = 5000;
	}
	void Init(BACKGROUND Index, int x, int y);
	void MapDraw(HDC hdc);
	~Map();
};
