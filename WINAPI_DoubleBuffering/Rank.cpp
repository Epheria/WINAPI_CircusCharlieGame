#include "Rank.h"

Rank::Rank()
{
	m_iMaxPage = 0;
	m_ctmp = 0;
	m_cCurPageIndex = 1;
	m_fTime = 0;
	ZeroMemory(m_buf, sizeof(m_buf));
}

void Rank::Init()
{
	m_pBitMap = BitMapManager::GetInstance()->GetImage(IMAGE_POINT);
}

std::string Rank::currentDateTime()
{
	SYSTEMTIME time;
	char buf[256];
	GetLocalTime(&time);
	sprintf_s(buf, "%d년 %d월 %d일 %d시 %d분 %d초", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	return buf;
}

void Rank::SaveRank(int iTotalScore)
{
	std::ofstream fSave;
	fSave.open("Rank.txt", std::ios::app);
	if (fSave.is_open())
	{
		fSave << currentDateTime() << " " << iTotalScore << " 점";
		fSave << std::endl;
		fSave.close();
	}
}

void Rank::LoadRank()
{
	std::ifstream fLoad;
	char* tmp;
	std::string line;

	fLoad.open("Rank.txt");
	if(fLoad.is_open())
	{
		while (!fLoad.eof())
		{
			std::getline(fLoad, line);
			tmp = new char[line.size() + 1];
			strcpy(tmp, line.c_str());
			RankList.push_back(tmp);
		}
		fLoad.close();
	}
	m_iMaxPage = RankList.size() / 7 + 1;
}

bool Rank::MenuSelect(float deltaTime)
{
	m_fTime += deltaTime;
	if (1.0f <= m_fTime)
	{
		m_fTime = 0;

		if (GetAsyncKeyState(VK_UP))
		{
			m_ctmp--;
			if (0 > m_ctmp) m_ctmp = 0;
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			m_ctmp++;
			if (2 < m_ctmp) m_ctmp = 2;
		}

		if (GetAsyncKeyState(VK_RETURN))
		{
			m_eCurState = m_ctmp;
		}
	}

	switch (m_eCurState)
	{
	case SELECT_NEXT:
		if (m_iMaxPage < m_cCurPageIndex)
			m_cCurPageIndex = m_iMaxPage;
		else
			m_cCurPageIndex++;
		return false;

	case SELECT_PREV:
		if (1 > m_cCurPageIndex)
			m_cCurPageIndex = 1;
		else
			m_cCurPageIndex--;
		return false;

	case SELECT_EXIT:
		m_ctmp = 0;
		m_cCurPageIndex = 1;
		return true;
	}
}

void Rank::RankDraw(HDC hdc)
{
	//int index;
	int iMax = RankList.size();

	for (int i = 0; i < 2; i++)
	{
		TextOutA(hdc, 200, 100 + i * 40, RankList[i], sizeof(RankList[i]));
	}

	TextOutA(hdc, 300, 450, "다음 페이지", sizeof("다음 페이지"));
	TextOutA(hdc, 300, 530, "이전 페이지", sizeof("이전 페이지"));
	TextOutA(hdc, 300, 610, "나가기", sizeof("나가기"));

	m_pBitMap->Draw(hdc, 200, 400 + m_ctmp * 80);
}

Rank::~Rank()
{
	for (std::vector<char*>::iterator iter = RankList.begin(); iter != RankList.end(); iter++)
		delete[] * iter;

	RankList.clear();
}