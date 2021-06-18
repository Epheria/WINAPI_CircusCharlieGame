#include "Character.h"

Character::Character()
{
	m_eCharacterState = MOVE_IDLE;
}

void Character::Init(int x, int y)
{
	m_pBitMap[MOVE_FRONT] = BitMapManager::GetInstance()->GetImage(IMAGE_PLAYER_3);
	m_pBitMap[MOVE_IDLE] = BitMapManager::GetInstance()->GetImage(IMAGE_PLAYER_1);
	m_pBitMap[MOVE_BACK] = BitMapManager::GetInstance()->GetImage(IMAGE_PLAYER_2);
	m_ix = x;
	m_iy = y;
	m_BitMapRect.left = x;
	m_BitMapRect.top = y;
	m_BitMapRect.right = m_BitMapRect.left + m_pBitMap[MOVE_IDLE]->GetSize().cx;
	m_BitMapRect.bottom = m_BitMapRect.top + m_pBitMap[MOVE_IDLE]->GetSize().cy;
}

void Character::Draw(HDC hdc)
{
	m_pBitMap[m_eCharacterState]->Draw(hdc, m_ix, m_iy);
}

bool Character::ColliderCheck(POINT point)
{
	return true;
}

Character::~Character()
{
}