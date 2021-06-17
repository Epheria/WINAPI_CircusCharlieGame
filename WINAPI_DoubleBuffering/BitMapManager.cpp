#pragma warning(disable:4996)
#include "BitMapManager.h"

BitMapManager* BitMapManager::m_hThis = NULL;

BitMapManager::BitMapManager()
{
	//m_parrBitMap = new BitMap[IMAGE_END];
}


void BitMapManager::Init(HWND hWnd)
{
	char buf[256];
	BitMap* tmp;
	HDC hdc = GetDC(hWnd);
	for (int i = IMAGE_BACK_1; i <= IMAGE_END; i++)
	{
		if(i >= IMAGE_BACK_1 && i <= IMAGE_BACK_4)
			sprintf(buf, "Resource//back_%d.bmp", i);
		else if(i == IMAGE_CASH)
			sprintf(buf, "Resource//cash.bmp");
		else if(i >= IMAGE_FIRE_1 && i <= IMAGE_FIRE_2)
			sprintf(buf, "Resource//fire_%d.bmp", i);
		else if (i == IMAGE_GOAL)
			sprintf(buf, "Resource//goal.bmp");
		else if (i >= IMAGE_INTERFACE_1 && i <= IMAGE_INTERFACE_3)
			sprintf(buf, "Resource//interface_%d.bmp", i);
		else if (i >= IMAGE_LITTLERING_1 && i <= IMAGE_LITTLERING_2)
			sprintf(buf, "Resource//littlering_%d.bmp", i);
		else if (i >= IMAGE_MENU_1 && i <= IMAGE_MENU_5)
			sprintf(buf, "Resource//menu_%d.bmp", i);
		else if (i >= IMAGE_PLAYER_1 && i <= IMAGE_PLAYER_6)
			sprintf(buf, "Resource//player_%d.bmp", i);
		else if (i == IMAGE_POINT)
			sprintf(buf, "Resource//point.bmp");
		else if (i >= IMAGE_RING_1 && i <= IMAGE_RING_4)
			sprintf(buf, "Resource//ring_%d.bmp", i);
		else if (i >= IMAGE_TITLE_1 && i <= IMAGE_TITLE_4)
			sprintf(buf, "Resource//title_%d.bmp", i);

		tmp = new BitMap;
		tmp->Init(hdc,buf);
		m_parrBitMap.push_back(tmp);
	}
	ReleaseDC(hWnd, hdc);
}

BitMapManager::~BitMapManager()
{
	for (auto& b : m_parrBitMap)
	{
		delete b;
	}
	//delete[] m_parrBitMap;
}
