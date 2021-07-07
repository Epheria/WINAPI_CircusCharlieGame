#include "Character.h"

Character::Character()
{
    m_iJumpDirection = 0;
    m_eDirection = DIRECTION::DIR_IDLE;
    m_fTime = 0;
    m_fDeadTime = 0;
	m_eCharacterState = MOVE_IDLE;
	m_bControl = false;
    m_bIsJump = false;
    m_bAnim = false;
    m_iSjump = 0;
    m_iMovedLength = 0;
    m_iScore = 0;
    m_iLife = 4;
}

void Character::Init(int x, int y)
{
	m_pBitMap[MOVE_FRONT] = BitMapManager::GetInstance()->GetImage(IMAGE_PLAYER_3);
	m_pBitMap[MOVE_IDLE] = BitMapManager::GetInstance()->GetImage(IMAGE_PLAYER_1);
	m_pBitMap[MOVE_BACK] = BitMapManager::GetInstance()->GetImage(IMAGE_PLAYER_2);
	m_pBitMap[MOVE_DIE] = BitMapManager::GetInstance()->GetImage(IMAGE_PLAYER_6);
	m_pBitMap[MOVE_GOAL1] = BitMapManager::GetInstance()->GetImage(IMAGE_PLAYER_4);
	m_pBitMap[MOVE_GOAL2] = BitMapManager::GetInstance()->GetImage(IMAGE_PLAYER_5);
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

#ifdef Debug_Rect
    Rectangle(hdc, m_BitMapRect.left, m_BitMapRect.top, m_BitMapRect.right, m_BitMapRect.bottom);
#endif // Debug_Rect
}

void Character::DrawDie(HDC hdc)
{
    m_pBitMap[MOVE_DIE]->Draw(hdc, m_ix, m_iy);
}

void Character::DrawGoal(HDC hdc)
{
    if (m_bAnim == true)
    {
        m_pBitMap[MOVE_GOAL1]->Draw(hdc, m_ix, m_iy);
    }
    else
    {
        m_pBitMap[MOVE_GOAL2]->Draw(hdc, m_ix, m_iy);
    }
}

void Character::RectUpdate()
{
    m_BitMapRect.left = m_ix + 15;
    m_BitMapRect.top = m_iy + 10;
    m_BitMapRect.right = m_BitMapRect.left + m_pBitMap[MOVE_IDLE]->GetSize().cx - 25;
    m_BitMapRect.bottom = m_BitMapRect.top + m_pBitMap[MOVE_IDLE]->GetSize().cy - 25;
}

void Character::PlayerUpdate(float deltaTime, int iCheck)
{
    int x, y;

    if (m_bIsJump == true)
    {
        x = GetDistx(deltaTime);
        y = GetDisty(deltaTime);

        if (m_iJumpDirection == 1 && m_iy <= 300)
        {
            UpdatePosy(-y);

            if (m_iy <= 180)
                m_iJumpDirection = -1;
        }
        if (m_iJumpDirection == -1 && m_iy >= 170)
        {
            UpdatePosy(y);
            if (m_iy >= 285)
                m_iJumpDirection = 0;
        }

        if (m_iJumpDirection == 0)
        {
            m_iSjump = 0;
            m_bIsJump = false;
        }
    }

    m_fTime += deltaTime;
    if (0.3f <= m_fTime)
    {
        m_fTime = 0;
        if (m_bIsJump == true)
        {
            m_eCharacterState = MOVE_IDLE;
        }

        switch (m_eCharacterState)
        {
        case MOVE_IDLE:
            if (iCheck == 1) m_eCharacterState = MOVE_FRONT;
            else if (iCheck == -1) m_eCharacterState = MOVE_BACK;
            else
                m_eCharacterState = MOVE_IDLE;
            break;
        default:
            m_eCharacterState = MOVE_IDLE;
        }
    }

    if (1.0f <= m_fTime)
    {
        m_fTime = 0;
        if (m_bAnim == false)
            m_bAnim = true;
        else
            m_bAnim = false;
    }
    RectUpdate();
}

bool Character::DeatCheck()
{
    m_iLife--;
    return true;
}

void Character::Reset()
{
    m_iMovedLength = 0;
    m_iJumpDirection = 0;
    m_iScore = 0;
    m_ix = 50;
    m_iy = 285;
}

Character::~Character()
{
}