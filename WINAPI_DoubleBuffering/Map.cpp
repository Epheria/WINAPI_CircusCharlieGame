#include "Map.h"


Map::Map() : m_imoveLen(0), m_ix(0), m_ix2(0), m_iMaxMapDraw(0), m_iBonusScore(10000), m_iScore(0), m_fTime(0), m_bAnim(false), m_bIsGoal(false)
{
	MeterCreate();
}

void Map::Init(BACKGROUND Index, int x, int y)
{
	m_pBitMap[BACKGROUND_TRACK] = BitMapManager::GetInstance()->GetImage(IMAGE_BACK_1);
	m_pBitMap[BACKGROUND_BACK1] = BitMapManager::GetInstance()->GetImage(IMAGE_BACK_2);
	m_pBitMap[BACKGROUND_BACK2] = BitMapManager::GetInstance()->GetImage(IMAGE_BACK_3);
	m_pBitMap[BACKGROUND_BACK3] = BitMapManager::GetInstance()->GetImage(IMAGE_BACK_4);
	m_pBitMap[BACKGROUND_GOAL] = BitMapManager::GetInstance()->GetImage(IMAGE_GOAL);
	m_pBitMap[BACKGROUND_INTERFACE] = BitMapManager::GetInstance()->GetImage(IMAGE_INTERFACE_1);
	m_pBitMap[BACKGROUND_LIFE] = BitMapManager::GetInstance()->GetImage(IMAGE_INTERFACE_2);
	m_pBitMap[BACKGROUND_METER] = BitMapManager::GetInstance()->GetImage(IMAGE_INTERFACE_3);
	m_ix = x;
	m_iy = y;
	m_iMaxMapDraw = SIZE_MAPX / m_pBitMap[BACKGROUND_BACK1]->GetSize().cx;
	m_iBackGroundLen = m_pBitMap[BACKGROUND_BACK1]->GetSize().cx * m_iMaxMapDraw;
	m_ix2 = m_ix + m_iBackGroundLen;
}

void Map::Update(float deltaTime, int MovedLen, int Life, int iBonusScore, int pScore, int pLife, bool flag)
{
	m_fTime += deltaTime;
	if (1.0f <= m_fTime)
	{
		m_fTime = 0;
		if (m_bAnim == false)
			m_bAnim = true;
		else
			m_bAnim = false;
	}

	m_iBonusScore = iBonusScore;
	m_iScore = pScore;
	m_iLife = pLife;
	m_bIsGoal = flag;
}

void Map::MapDraw(HDC hdc)
{
	char buf[256];
	ZeroMemory(buf, sizeof(buf));
	std::string stmp;

	m_pBitMap[BACKGROUND_INTERFACE]->Draw(hdc, 200, 20);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(0, 0, 0));
	sprintf_s(buf, "Score : %d", m_iScore);
	TextOutA(hdc, 400, 40, buf, strlen(buf));
	ZeroMemory(buf, sizeof(buf));
	sprintf_s(buf, "BonusScore : %d", m_iBonusScore);
	TextOutA(hdc, 700, 40, buf, strlen(buf));

	for (int i = 0; i < m_iLife; i++)
	{
		m_pBitMap[BACKGROUND_LIFE]->Draw(hdc, 850 + i * 15, 50);
	}

	for (int i = 0; i < MeterList.size(); i++)
	{
			stmp = std::to_string(MeterList[i]);
			m_pBitMap[BACKGROUND_METER]->Draw(hdc, 10 + 1070 * i - m_imoveLen, 350);
			TextOutA(hdc, 30 + 1070 * i - m_imoveLen, 355, stmp.c_str(), strlen(stmp.c_str()));
	}
	
	for (int i = 0; i <= m_iMaxMapDraw; i++)
	{
		m_iy = 100;
		auto x = 66 * i;

		if (i == 7)
			m_pBitMap[BACKGROUND_BACK1]->Draw(hdc, m_ix + x, m_ix2 + x, m_iy, false);
		else
		{
			if (m_bIsGoal == true && m_bAnim == true)
				m_pBitMap[BACKGROUND_BACK2]->Draw(hdc, m_ix + x, m_ix2 + x, m_iy, false);
			else if (m_bIsGoal == true && m_bAnim == false)
				m_pBitMap[BACKGROUND_BACK3]->Draw(hdc, m_ix + x - 2, m_ix2 + x - 2, m_iy + 2, false);
			else if (m_bIsGoal == false)
				m_pBitMap[BACKGROUND_BACK2]->Draw(hdc, m_ix + x, m_ix2 + x, m_iy, false);
		}
		m_iy = 165;
		m_pBitMap[BACKGROUND_TRACK]->Draw(hdc, m_ix + x, m_ix2 + x, m_iy, false);
	}
}

void Map::MeterCreate()
{
	char buf[10];

	for (int i = 0; i < 10; i++)
	{
		ZeroMemory(buf, sizeof(buf));

		sprintf_s(buf, "%d", (10 - i) * 10);

		MeterList.push_back((10 - i) * 10);
	}
}

void Map::Reset()
{
	m_imoveLen = 0;
	m_ix = 0;
	m_ix2 = m_ix + m_iBackGroundLen;
}

void Map::DrawGoal(HDC hdc)
{
	int iTotalScore = m_iBonusScore + m_iScore;
	char buf[256];
	ZeroMemory(buf, sizeof(buf));

	m_pBitMap[BACKGROUND_INTERFACE]->Draw(hdc, 200, 20);
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(0, 0, 0));
	sprintf_s(buf, "! ! ?? ?? ! !       ");
	TextOutA(hdc, 400, 40, buf, strlen(buf));
	sprintf_s(buf, "TotalScore : %d ", iTotalScore);
	TextOutA(hdc, 700, 40, buf, strlen(buf));
}

Map::~Map()
{

}