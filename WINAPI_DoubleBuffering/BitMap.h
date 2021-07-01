#pragma once
#include<Windows.h>
#include<string>

enum MAPSIZE
{
	SIZE_MAPX = 1100,
	SIZE_MAPY = 700,
	SIZE_BACKX = 65,
	SIZE_BACKY = 66
};

class BitMap
{
private:
	HDC MemDC;
	HBITMAP m_BitMap;
	HBITMAP m_OldBitMap;
	SIZE m_Size;
public:
	void Init(HDC hdc,char* FileName);
	void Draw(HDC hdc, int x, int y, bool isAlpha = true);
	void DrawBackGround(HDC hdc, int x, int y);
	inline SIZE GetSize()
	{
		return m_Size;
	}
	BitMap();
	~BitMap();
};

