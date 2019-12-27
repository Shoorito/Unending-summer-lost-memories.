#include "PlayerState.h"
#include "PlayerUI.h"
#include "CocosFunctions.h"
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
	m_pInstance->setup();

	return m_pInstance;
}

void C_PlayerState::setMaxHP(const int fHP)
{
	if (fHP < 0.0f || fHP > 0xffffffff - 1)
		return;

	m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_HP)] = fHP;
}

void C_PlayerState::setMaxMP(const int fMP)
{
	if (fMP < 0.0f || fMP > g_nScoreLimit)
		return;

	m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_MP)] = fMP;
}

void C_PlayerState::setMaxEXP(const int fEXP)
{
	if (fEXP < 0.0f || fEXP > g_nScoreLimit)
		return;

	m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_EXP)] = fEXP;
}

void C_PlayerState::setHP(const int fHP)
{
	if (fHP < 0.0f || fHP > g_nScoreLimit)
		return;

	m_nPlayerHP = fHP;
}

void C_PlayerState::setMP(const int fMP)
{
	if (fMP < 0.0f || fMP > g_nScoreLimit)
		return;

	m_nPlayerMP = fMP;
}

void C_PlayerState::setEXP(const int fEXP)
{
	if (fEXP < 0.0f || fEXP > g_nScoreLimit)
		return;

	m_nPlayerEXP = fEXP;
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
	if (nScore < 0 || nScore < m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_HIGH_SCORE)])
		return;

	m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_HIGH_SCORE)] = nScore;
}

void C_PlayerState::addHP(const int fAdder)
{
	if (m_nPlayerHP + fAdder < 0.0f || m_nPlayerHP + fAdder > g_nScoreLimit)
		return;

	m_nPlayerHP += fAdder;
}

void C_PlayerState::addMP(const int fAdder)
{
	if (m_nPlayerMP + fAdder < 0.0f || m_nPlayerMP + fAdder > g_nScoreLimit)
		return;

	m_nPlayerMP += fAdder;
}

void C_PlayerState::addEXP(const int fAdder)
{
	if (m_nPlayerEXP + fAdder < 0.0f || m_nPlayerEXP + fAdder > g_nScoreLimit)
		return;

	m_nPlayerEXP += fAdder;
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
	m_nPlayerEXP	= 0;
	m_nPlayerHP		= 0;
	m_nPlayerMP		= 0;
	m_nScore		= 0;
}

void C_PlayerState::setup()
{
	FileUtils* pUtils(nullptr);

	pUtils = FileUtils::getInstance();

	if (pUtils->isFileExist(pUtils->getWritablePath() + "PLAYER_FILE.txt"))
	{
		loadPlayerStatus();
	}
	else
	{
		m_nPlayerHP	= 50;
		m_nPlayerMP	= 10;

		m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_HP)]		= m_nPlayerHP;
		m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_MP)]		= m_nPlayerMP;
		m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_EXP)]	= 0;
		m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_HIGH_SCORE)] = 100000;

		savePlayerStatus();
	}
}

void C_PlayerState::loadPlayerStatus()
{
	FileUtils*  pUtil(nullptr);
	std::string strData("");

	pUtil = FileUtils::getInstance();
	
	strData = pUtil->getStringFromFile(pUtil->getWritablePath() + "PLAYER_FILE.txt");

	C_Functions::encryptText(strData, g_strEncryptKey);

	readFile(strData);
}

void C_PlayerState::readFile(const std::string & strInfo)
{
	int nSize(0);
	int nCursor(0);
	int nStatusNum(0);
	std::string strExtract("");

	nSize = strInfo.size();

	while(nCursor == nSize)
	{
		if (strInfo[nCursor] == '=')
		{
			while (strInfo[nCursor] != '\n')
			{
				if (!C_Functions::isCheckSkip(strInfo[nCursor]))
				{
					strExtract += strInfo[nCursor];
				}

				nCursor++;
			}

			m_arSaveStatus[nStatusNum] = C_Functions::convertToInt(strExtract);

			strExtract.clear();

			nStatusNum++;
		}
		else
		{
			nCursor++;
		}
	}
}

void C_PlayerState::savePlayerStatus()
{
	FileUtils*  pUtil(nullptr);
	std::string strSaveInfo("");

	pUtil		 = FileUtils::getInstance();
	strSaveInfo += "<PLAYER_SHEET>\n";
	strSaveInfo += '\n';

	for (int nItem(0); nItem < g_nStatusNum; nItem++)
	{
		strSaveInfo += g_arSaveStatus[nItem];
		strSaveInfo += " = ";
		strSaveInfo += std::to_string(m_arSaveStatus[nItem]);
		strSaveInfo += '\n';
	}

	C_Functions::encryptText(strSaveInfo, g_strEncryptKey);

	pUtil->writeStringToFile(strSaveInfo, pUtil->getWritablePath() + "PLAYER_FILE.txt");
}
