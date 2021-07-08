#pragma once
#include "BitMap.h"
#include "BitMapManager.h"
#include <iostream>
#include <Windows.h>
#include <time.h>
#include <fstream>

class Rank
{
private:
	char m_buf[256];
	std::vector<char*> RankList;
public:
	Rank();
	std::string currentDateTime();
	void SaveRank(int iTotalScore);
	void LoadRank();
	void Swap();
	void RankDraw();
	~Rank();
};

