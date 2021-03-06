#pragma once
#include "BitMap.h"
#include "BitMapManager.h"

enum BACKGROUND
{
	BACKGROUND_TRACK,
	BACKGROUND_BACK1,
	BACKGROUND_BACK2,
	BACKGROUND_BACK3,
	BACKGROUND_GOAL,
	BACKGROUND_INTERFACE,
	BACKGROUND_LIFE,
	BACKGROUND_METER,
	BACKGROUND_END
};

class Map
{
private:
	BitMap* m_pBitMap[BACKGROUND_END];
	std::vector<int> MeterList;
	int m_imoveLen;
	int m_iBackGroundLen;
	int m_ix;
	int m_ix2;
	int m_iy;
	int m_iMaxMapDraw;
	int m_iMeter, m_iMeter2;
	int m_iBonusScore;
	int m_iScore;
	int m_iLife;
	float m_fTime;
	bool m_bAnim;
	bool m_bIsGoal;
public:
	Map();
	int GetMoveLenx()
	{
		return m_imoveLen;
	}
	int GetTotalScore()
	{
		return m_iBonusScore + m_iScore;
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
}
	void Init(BACKGROUND Index, int x, int y);
	void Update(float deltaTime, int MovedLen, int Life, int iBonusScore, int pScore, int pLife, bool m_bIsGoal);
	void MeterCreate();
	void MapDraw(HDC hdc);
	void DrawGoal(HDC hdc);
	void Reset();
	~Map();
};
