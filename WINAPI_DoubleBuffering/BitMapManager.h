#pragma once
#include"BitMap.h"
#include<vector>

enum IMAGE
{
	IMAGE_START = 0,
	IMAGE_BACK_1,
	IMAGE_BACK_2,
	IMAGE_BACK_3,
	IMAGE_BACK_4,
	IMAGE_CASH,
	IMAGE_FIRE_1,
	IMAGE_FIRE_2,
	IMAGE_GOAL,
	IMAGE_INTERFACE_1,
	IMAGE_INTERFACE_2,
	IMAGE_INTERFACE_3,
	IMAGE_LITTLERING_1,
	IMAGE_LITTLERING_2,
	IMAGE_MENU_1,
	IMAGE_MENU_2,
	IMAGE_MENU_3,
	IMAGE_MENU_4,
	IMAGE_MENU_5,
	IMAGE_PLAYER_1,
	IMAGE_PLAYER_2,
	IMAGE_PLAYER_3,
	IMAGE_PLAYER_4,
	IMAGE_PLAYER_5,
	IMAGE_PLAYER_6,
	IMAGE_POINT,
	IMAGE_RING_1,
	IMAGE_RING_2,
	IMAGE_RING_3,
	IMAGE_RING_4,
	IMAGE_TITLE_1,
	IMAGE_TITLE_2,
	IMAGE_TITLE_3,
	IMAGE_TITLE_4,
	IMAGE_END
};

class BitMapManager
{
private:
	std::vector<BitMap*> m_parrBitMap;
	static BitMapManager* m_hThis;
public:
	static BitMapManager* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new BitMapManager;
		return m_hThis;
	}
	BitMap* GetImage(IMAGE index)
	{
		auto temp = m_parrBitMap[index];
		return m_parrBitMap[index];
	}
	BitMapManager();
	void Init(HWND hWnd);
	~BitMapManager();
};

