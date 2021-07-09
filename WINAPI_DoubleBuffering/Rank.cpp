#include "Rank.h"

Rank::Rank() : m_eCurState(SELECT_DEFUALT), m_iMaxPage(0), m_ctmp(0), m_iCurPageIndex(1), m_fTime(0),
font(CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, (LPCWSTR)"�ü�"))
{
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
	sprintf_s(buf, "%d�� %d�� %d�� %d�� %d�� %d��", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
	return buf;
}

void Rank::SaveRank(int iTotalScore)
{
	RankList.clear();
	std::ofstream fSave;
	fSave.open("Rank.txt", std::ios::app);
	if (fSave.is_open())
	{
		fSave << std::endl;
		fSave << currentDateTime() << "    " << iTotalScore << " ��";
		fSave.close();
	}
}

void Rank::LoadRank()
{
	std::ifstream fLoad;
	std::string line;

	fLoad.open("Rank.txt");
	if(fLoad.is_open())
	{
		while (!fLoad.eof())
		{
			std::getline(fLoad, line);
			RankList.push_back(line);
		}
		fLoad.close();
	}
	m_iMaxPage = RankList.size() / 7 + 1;
}

bool Rank::MenuSelect(float deltaTime)
{
	m_fTime += deltaTime;
	if (0.5f <= m_fTime)
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

		if (GetAsyncKeyState(VK_RETURN) & 0x0001)
		{
			m_eCurState = m_ctmp;
		}
	}

	switch (m_eCurState)
	{
	case SELECT_NEXT:
		if (m_iMaxPage <= m_iCurPageIndex)
			m_iCurPageIndex = m_iMaxPage;
		else
			m_iCurPageIndex++;
		m_eCurState = SELECT_DEFUALT;
		return false;

	case SELECT_PREV:
		if (1 >= m_iCurPageIndex)
			m_iCurPageIndex = 1;
		else
			m_iCurPageIndex--;
		m_eCurState = SELECT_DEFUALT;
		return false;

	case SELECT_EXIT:
		m_ctmp = 0;
		m_iCurPageIndex = 1;
		m_eCurState = 3;
		RankList.clear();
		return true;

	case SELECT_DEFUALT:
		return false;
	}

}

void Rank::RankDraw(HDC hdc)
{
	int index = 1 + (m_iCurPageIndex - 1) * 7;
	std::string page = "<" + std::to_string(m_iCurPageIndex) + ">";

	HFONT oldfont = (HFONT)SelectObject(hdc, font);
	SetTextColor(hdc, RGB(255, 0, 0));
	SetBkColor(hdc, RGB(0, 0, 0));
	const int& iMax = RankList.size();
	TextOutA(hdc, 500, 50, "�ڡ� R a n k �١�", strlen("�ڡ� R a n k �١�"));
	SelectObject(hdc, oldfont);

	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(0, 0, 0));
	for (int i = 0; 7 > i; i++, index++)
	{
		if (index < iMax)
			TextOutA(hdc, 450, 100 + i * 40, RankList[index].c_str(), strlen(RankList[index].c_str()));
		else
			break;
	}

	TextOutA(hdc, 550, 380, page.c_str(), strlen(page.c_str()));
	TextOutA(hdc, 580, 380, " ������", strlen(" ������"));

	TextOutA(hdc, 550, 450, "���� ������", strlen("���� ������"));
	TextOutA(hdc, 550, 530, "���� ������", strlen("���� ������"));
	TextOutA(hdc, 550, 610, "������", strlen("������"));

	m_pBitMap->Draw(hdc, 350, 450 + m_ctmp * 80);
}

Rank::~Rank()
{
	RankList.clear();
	DeleteObject(font);
}