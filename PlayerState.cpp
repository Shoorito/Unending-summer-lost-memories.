#include "PlayerState.h"
#include "PlayerUI.h"
#include "ResourceTable.h"

C_PlayerState* C_PlayerState::m_pInstance = nullptr;

C_PlayerState * C_PlayerState::create()
{
	if (m_pInstance)
	{
		CCLOG(u8"\"PlayerState\"가 이미 생성되어 있습니다.");

		return nullptr;
	}

	m_pInstance = new(std::nothrow) C_PlayerState();

	m_pInstance->init();

	return m_pInstance;
}

void C_PlayerState::setMaxHP(const float fHP)
{
	if (fHP < 0.0f || fHP > 0xffffffff - 1)
		return;

	m_fPlayerMaxHP = fHP;
}

void C_PlayerState::setMaxMP(const float fMP)
{
	if (fMP < 0.0f || fMP > 0xffffffff - 1)
		return;

	m_fPlayerMaxMP = fMP;
}

void C_PlayerState::setMaxEXP(const float fEXP)
{
	if (fEXP < 0.0f || fEXP > 0xffffffff - 1)
		return;

	m_fPlayerMaxEXP = fEXP;
}

void C_PlayerState::setHP(const float fHP)
{
	if (fHP < 0.0f || fHP > 0xffffffff - 1)
		return;

	m_fPlayerHP = fHP;
}

void C_PlayerState::setMP(const float fMP)
{
	if (fMP < 0.0f || fMP > 0xffffffff - 1)
		return;

	m_fPlayerMP = fMP;
}

void C_PlayerState::setEXP(const float fEXP)
{
	if (fEXP < 0.0f || fEXP > 0xffffffff - 1)
		return;

	m_fPlayerEXP = fEXP;
}

void C_PlayerState::setScore(const int nScore)
{
	if (nScore < 0 || m_nScore == g_nScoreLimit)
		return;

	if ((m_nScore + nScore > g_nScoreLimit) || (m_nScore + nScore < 0))
		m_nScore = g_nScoreLimit;
	else
		m_nScore = nScore;

	setHighScore(m_nScore);
}

void C_PlayerState::setHighScore(const int nScore)
{
	if (nScore < 0 || nScore < m_nHighScore)
		return;

	m_nHighScore = nScore;
}

void C_PlayerState::addHP(const float fAdder)
{
	if (m_fPlayerHP + fAdder < 0.0f || m_fPlayerHP + fAdder > 0xffffffff - 1)
		return;

	m_fPlayerHP += fAdder;
}

void C_PlayerState::addMP(const float fAdder)
{
	if (m_fPlayerMP + fAdder < 0.0f || m_fPlayerMP + fAdder > 0xffffffff - 1)
		return;

	m_fPlayerMP += fAdder;
}

void C_PlayerState::addEXP(const float fAdder)
{
	if (m_fPlayerEXP + fAdder < 0.0f || m_fPlayerEXP + fAdder > 0xffffffff - 1)
		return;

	m_fPlayerEXP += fAdder;
}

void C_PlayerState::addScore(const int nScore)
{
	if (m_nScore + nScore < 0 || m_nScore == g_nScoreLimit)
		return;

	if (m_nScore + nScore > g_nScoreLimit || m_nScore + nScore < 0)
		m_nScore = g_nScoreLimit;
	else
		m_nScore += nScore;

	setHighScore(m_nScore);
}

void C_PlayerState::init()
{
	m_fPlayerEXP	= 0.0f;
	m_fPlayerHP		= 0.0f;
	m_fPlayerMP		= 0.0f;
	m_fPlayerMaxHP  = 0.0f;
	m_fPlayerMaxMP  = 0.0f;
	m_fPlayerMaxEXP = 0.0f;
	m_nHighScore	= 0;
	m_nScore		= 0;
}
