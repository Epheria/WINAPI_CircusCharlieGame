#include "Rank.h"

Rank::Rank()
{
	ZeroMemory(m_buf, sizeof(m_buf));
}

std::string Rank::currentDateTime()
{
	//time_t now = time(0);
	//struct tm tstruct;
	//char buf[80];
	//tstruct = *localtime(&now);
	//strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	//return buf;
	return 0;
}

void Rank::SaveRank(int iTotalScore)
{
	std::ofstream fSave;
	fSave.open("Rank.txt", std::ios::app);
	if (fSave.is_open())
	{
		fSave << std::endl;
		fSave << currentDateTime() << " " << iTotalScore << " Á¡";
		fSave.close();
	}
}

void Rank::LoadRank()
{
	std::ifstream fLoad;
	if(fLoad.is_open())
	{
		while (!fLoad.eof())
		{
			fLoad >> m_buf;
			RankList.push_back(m_buf);
		}
		fLoad.close();
	}

}

void Rank::Swap()
{

}

void Rank::RankDraw()
{

}

Rank::~Rank()
{
}