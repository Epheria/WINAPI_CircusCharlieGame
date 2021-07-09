#pragma once
#pragma warning(disable:4996)
#include "BitMap.h"
#include "BitMapManager.h"
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <fstream>

enum SELRANK
{
	SELECT_NEXT,
	SELECT_PREV,
	SELECT_EXIT,
	SELECT_DEFUALT
};

class Rank
{
private:
	BitMap* m_pBitMap;
	int m_iMaxPage;
	char m_ctmp;
	int m_iCurPageIndex;
	char m_eCurState;
	char m_buf[256];
	float m_fTime;
	HFONT font;
	std::vector<std::string> RankList;
public:
	Rank();
	std::string currentDateTime();
	void SaveRank(int iTotalScore);
	void LoadRank();
	bool MenuSelect(float dletaTime);
	void RankDraw(HDC hdc);
	void Init();
	~Rank();
};

