#include "BitMap.h"



BitMap::BitMap()
{
}

void BitMap::Init(HDC hdc,char* FileName)
{
	MemDC = CreateCompatibleDC(hdc);
	m_BitMap = (HBITMAP)LoadImageA(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_OldBitMap = (HBITMAP)SelectObject(MemDC, m_BitMap);
	BITMAP BitMap_Info;
	GetObject(m_BitMap, sizeof(BitMap_Info), &BitMap_Info);
	m_Size.cx = BitMap_Info.bmWidth;
	m_Size.cy = BitMap_Info.bmHeight;
}
void BitMap::Draw(HDC hdc, int x, int x2, int y, bool isAlpha)
{
	switch (isAlpha)
	{
	case true: 
		TransparentBlt(hdc, x, y, m_Size.cx, m_Size.cy, MemDC, 0, 0, m_Size.cx, m_Size.cy, RGB(255, 0, 255));
		TransparentBlt(hdc, x2, y, m_Size.cx, m_Size.cy, MemDC, 0, 0, m_Size.cx, m_Size.cy, RGB(255, 0, 255)); break;
	default: 
		BitBlt(hdc, x, y, m_Size.cx, m_Size.cy, MemDC, 0, 0, SRCCOPY);
		BitBlt(hdc, x2, y, m_Size.cx, m_Size.cy, MemDC, 0, 0, SRCCOPY); break;
	}
}
void BitMap::Draw(HDC hdc, int x, int y)
{
	TransparentBlt(hdc, x, y, m_Size.cx, m_Size.cy, MemDC, 0, 0, m_Size.cx, m_Size.cy, RGB(255, 0, 255));
}
void BitMap::DrawBackGround(HDC hdc, int x, int y)
{
	StretchBlt(hdc, x, y, m_Size.cx * 10, m_Size.cy * 10, MemDC, 0, 0, m_Size.cx * 8.5f, m_Size.cy * 8.5f, SRCCOPY);
}
BitMap::~BitMap()
{
	SelectObject(MemDC, m_OldBitMap);
	DeleteObject(m_BitMap);
	DeleteDC(MemDC);
}
