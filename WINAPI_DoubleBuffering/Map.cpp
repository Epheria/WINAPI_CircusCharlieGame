#include "Map.h"


Map::Map()
{
	m_imoveLen = 0;
	m_ix = 0;
	m_eMapState = BACKGROUND_TRACK;
	m_bControl = true;
	m_iMaxMapDraw = 0;
	m_ix2 = 0;
	m_iBonusScore = 10000;
	m_iScore = 0;
	iCur = 0;
	m_fTime = 0;
	m_bAnim = false;
	m_bIsGoal = false;
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

	m_iPlayerMovedLen = MovedLen;
	m_iBonusScore = iBonusScore;
	m_iScore = pScore;
	m_iLife = pLife;
	m_bIsGoal = flag;
}

void Map::MapDraw(HDC hdc)
{
	char buf[256];
	ZeroMemory(buf, sizeof(buf));

	m_pBitMap[BACKGROUND_INTERFACE]->Draw(hdc, 200, 20);
	sprintf_s(buf, "Score : %d", m_iScore);
	TextOutA(hdc, 400, 40, buf, strlen(buf));
	ZeroMemory(buf, sizeof(buf));
	sprintf_s(buf, "BonusScore : %d", m_iBonusScore);
	TextOutA(hdc, 700, 40, buf, strlen(buf));

	for (int i = 0; i < m_iLife; i++)
	{
		m_pBitMap[BACKGROUND_LIFE]->Draw(hdc, 850 + i * 15, 50);
	}

	for (int i = 0; i < MeterList.size(); i+=2)
	{
		m_pBitMap[BACKGROUND_METER]->Draw(hdc, m_ix, 350);
		//TextOutA(hdc, m_ix +10, 355, MeterList[i], strlen(MeterList[i]));
	}
	for (int i = 1; i < MeterList.size(); i+=2)
	{
		m_pBitMap[BACKGROUND_METER]->Draw(hdc, m_ix2, 350);
		//TextOutA(hdc, m_ix2 + 10, 355, MeterList[i], strlen(MeterList[i]));
	}

	for (int i = 0; i <= m_iMaxMapDraw; i++)
	{
		m_iy = 100;
		auto x = 66 * i;

		//if (i == 1)
		//{
		//	ZeroMemory(buf, sizeof(buf));
		//	sprintf_s(buf, "%d", m_iMeter);
		//	m_pBitMap[BACKGROUND_METER]->Draw(hdc, m_ix + x, 350);
		//	TextOutA(hdc, m_ix + x + 10, 355, buf, strlen(buf));

		//	ZeroMemory(buf, sizeof(buf));
		//	sprintf_s(buf, "%d", m_iMeter2);
		//	m_pBitMap[BACKGROUND_METER]->Draw(hdc, m_ix2 + x, 350);
		//	TextOutA(hdc, m_ix2 + x + 10, 355, buf, strlen(buf));
		//}

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

	//for (int i = 0; 2 > i; i++)
	//{
	//	m_ix = icx - m_imoveLen;
	//	if (m_ix / icx == 7)
	//		m_pBitMap[BACKGROUND_BACK1]->Draw(hdc, m_ix, m_iy);
	//	else
	//		m_pBitMap[BACKGROUND_BACK2]->Draw(hdc, m_ix, m_iy);


	//}
	//m_ix += icx - m_imoveLen;
	//for (int i = 0; i < (1200 + m_imoveLen) / 65; i++)
	//{
	//	m_ix = 65 * i - m_imoveLen;
	//	if (iCur % 7 == 0)
	//		m_pBitMap[BACKGROUND_BACK1]->Draw(hdc, m_ix, m_iy);
	//	else
	//		m_pBitMap[BACKGROUND_BACK2]->Draw(hdc, m_ix, m_iy);
	//	iCur++;
	//}
	//m_iy = 165;

	//for (int i = 0; i <= m_iMaxMapDraw; i++)
	//{
	//	auto x = 67 * i;
	//	m_pBitMap[BACKGROUND_TRACK]->Draw(hdc, m_ix + x, m_iy, false);
	//	m_pBitMap[BACKGROUND_TRACK]->Draw(hdc, m_ix2 + x, m_iy, false);
	//}
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
	sprintf_s(buf, "! ! �� �� ! !");
	TextOutA(hdc, 400, 40, buf, strlen(buf));
	sprintf_s(buf, "TotalScore : %d", iTotalScore);
	TextOutA(hdc, 700, 40, buf, strlen(buf));
}

Map::~Map()
{

}