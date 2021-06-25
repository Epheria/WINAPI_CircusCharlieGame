#pragma once
#include "BitMap.h"
#include "BitMapManager.h"

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
	OBS_END
};

class Obstacle
{
private:
	OBSTACLE m_eObstacleState;
	BitMap* m_pBitMap[OBS_END];
	float m_fTime;
	int m_imoveLen;
	int m_ix;
	int m_iy;
	bool m_bAnim;
public:
	Obstacle();
	void UpdateMoveLenx(int x)
	{
		m_imoveLen += x;
		if (m_imoveLen <= 0)
			m_imoveLen = 0;
		if (m_imoveLen >= 5000)
			m_imoveLen = 5000;
	}
	void Update(float deltaTime, int x);
	void Init(OBSTACLE Index, int x, int y);
	void ObstacleDraw(HDC hdc);
	~Obstacle();
};
