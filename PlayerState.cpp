#include "PlayerState.h"
#include "PlayerUI.h"
#include "ResourceTable.h"
#include "CocosFunctions.h"
#include "WeaponLauncher.h"

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

void C_PlayerState::setMaxHP(const int nHP)
{
	if (nHP < 0 || static_cast<unsigned int>(nHP) > m_nMaxScore)
		return;

	m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_HP)] = nHP;
}

void C_PlayerState::setMaxMP(const int nMP)
{
	if (nMP < 0 || static_cast<unsigned int>(nMP) > m_nMaxScore)
		return;

	m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_MP)] = nMP;
}

void C_PlayerState::setMaxEXP(const int nEXP)
{
	if (nEXP < 0 || static_cast<unsigned int>(nEXP) > m_nMaxScore)
		return;

	m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_EXP)] = nEXP;
}

void C_PlayerState::setAttack(const int nPower)
{
	if (nPower < 0)
		return;

	if (static_cast<unsigned int>(nPower) > m_nMaxScore)
	{
		m_nPlayerAttack = m_nMaxScore;

		return;
	}

	m_nPlayerAttack = nPower;
}

void C_PlayerState::setHP(const int nHP)
{
	if (nHP < 0)
		return;

	if (nHP > m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_HP)])
	{
		m_nPlayerHP = m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_HP)];

		return;
	}

	m_nPlayerHP = nHP;
}

void C_PlayerState::setMP(const int nMP)
{
	if (nMP < 0)
		return;

	if (nMP > m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_MP)])
	{
		m_nPlayerMP = m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_MP)];

		return;
	}

	m_nPlayerMP = nMP;
}

void C_PlayerState::setEXP(const int nEXP)
{
	if (nEXP < 0 || m_nLevel >= C_WeaponLauncher::getInstance()->getMaxLauncherCount())
		return;

	m_nPlayerEXP = nEXP;

	while (m_nPlayerEXP >= m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_EXP)])
	{
		addLevel(1);

		m_nPlayerEXP -= m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_EXP)];
	}
}

void C_PlayerState::setScore(const int nScore)
{
	if (m_nScore == m_nMaxScore)
		return;

	if (static_cast<unsigned int>(nScore) > m_nMaxScore)
	{
		m_nScore = m_nMaxScore;
	}
	else
	{
		m_nScore = nScore;
	}
}

void C_PlayerState::setLevel(const int nLevel)
{
	if (nLevel < 1)
	{
		m_nLevel = 1;

		C_WeaponLauncher::getInstance()->setWeaponCount(m_nLevel);

		return;
	}

	if (nLevel > C_WeaponLauncher::getInstance()->getMaxLauncherCount())
	{
		m_nLevel = C_WeaponLauncher::getInstance()->getMaxLauncherCount();
	}
	else
	{
		m_nLevel = nLevel;
	}

	C_WeaponLauncher::getInstance()->setWeaponCount(m_nLevel);
}

void C_PlayerState::setHighScore(const int nScore)
{
	if (nScore < m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_HIGH_SCORE)])
		return;

	m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_HIGH_SCORE)] = nScore;
}

void C_PlayerState::addHP(const int nAdder)
{
	if (m_nPlayerHP + nAdder >= m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_HP)])
	{
		m_nPlayerHP = m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_HP)];

		return;
	}

	m_nPlayerHP += nAdder;
}

void C_PlayerState::addMP(const int nAdder)
{
	if (m_nPlayerMP + nAdder > m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_MP)])
	{
		m_nPlayerMP = m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_MP)];

		return;
	}

	m_nPlayerMP += nAdder;
}

void C_PlayerState::addAttack(const int nPower)
{
	if (m_nPlayerAttack == m_nMaxScore)
		return;

	if (static_cast<unsigned int>(m_nPlayerAttack + nPower) > m_nMaxScore)
	{
		m_nPlayerAttack = m_nMaxScore;

		return;
	}
		
	m_nPlayerAttack += nPower;
}

void C_PlayerState::addEXP(const int nAdder)
{
	if (nAdder < 1)
		return;

	m_nPlayerEXP += nAdder;

	while (m_nPlayerEXP >= m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_EXP)])
	{
		addLevel(1);

		m_nPlayerEXP -= m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_EXP)];
	}
}

void C_PlayerState::addScore(const int nScore)
{
	if (m_nScore == m_nMaxScore)
		return;

	if (static_cast<unsigned int>(m_nScore + nScore) > m_nMaxScore)
	{
		m_nScore = m_nMaxScore;

		return;
	}
	
	m_nScore += nScore;
}

void C_PlayerState::addLevel(const int nLevel)
{
	if (m_nLevel == C_WeaponLauncher::getInstance()->getMaxLauncherCount())
		return;

	if (m_nLevel + nLevel > C_WeaponLauncher::getInstance()->getMaxLauncherCount())
	{
		m_nLevel = C_WeaponLauncher::getInstance()->getMaxLauncherCount();
	}
	else
	{
		m_nLevel += nLevel;
	}

	C_WeaponLauncher::getInstance()->setWeaponCount(m_nLevel);
}

void C_PlayerState::addValueByTag(const int nAdd, const int nTag)
{
	(this->*m_arAddFuncs[nTag])(nAdd);
}

void C_PlayerState::init()
{
	m_nPlayerEXP	= 0;
	m_nPlayerHP		= 0;
	m_nPlayerMP		= 0;
	m_nScore		= 0;
	m_nLevel		= 1;
	m_nPlayerAttack = 0;
	m_nMaxScore		= 0x7fffffff;
	m_strEncryptKey = u8"델루나의사장장만월은구찬성을사랑한다.";

	m_arSaveStatusName[static_cast<int>(E_PLAYER_STATUS::E_MAX_HP)]		= "INIT_HP";
	m_arSaveStatusName[static_cast<int>(E_PLAYER_STATUS::E_MAX_MP)]		= "INIT_MP";
	m_arSaveStatusName[static_cast<int>(E_PLAYER_STATUS::E_MAX_EXP)]	= "INIT_EXP";
	m_arSaveStatusName[static_cast<int>(E_PLAYER_STATUS::E_HIGH_SCORE)] = "INIT_HIGHSCORE";
	m_arSaveStatusName[static_cast<int>(E_PLAYER_STATUS::E_ATTACK)]		= "INIT_ATTACK";

	m_arAddFuncs[static_cast<int>(E_GAIN_STAT::E_HP)]	 = &C_PlayerState::addHP;
	m_arAddFuncs[static_cast<int>(E_GAIN_STAT::E_MP)]	 = &C_PlayerState::addMP;
	m_arAddFuncs[static_cast<int>(E_GAIN_STAT::E_EXP)]	 = &C_PlayerState::addEXP;
	m_arAddFuncs[static_cast<int>(E_GAIN_STAT::E_SCORE)] = &C_PlayerState::addScore;
}

void C_PlayerState::setup()
{
	FileUtils* pUtils(nullptr);

	pUtils = FileUtils::getInstance();

	if (pUtils->isFileExist(pUtils->getWritablePath() + "PLAYER_FILE.magu"))
	{
		loadPlayerStatus();
	}
	else
	{
		m_nPlayerHP		= 100;
		m_nPlayerMP		= 10;
		m_nPlayerAttack = 10;

		m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_HP)]		= m_nPlayerHP;
		m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_MP)]		= m_nPlayerMP;
		m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_EXP)]	= 100;
		m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_HIGH_SCORE)] = 100000;
		m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_ATTACK)]		= m_nPlayerAttack;

		savePlayerStatus();
	}
}

void C_PlayerState::loadPlayerStatus()
{
	FileUtils*  pUtil(nullptr);
	std::string strData("");

	pUtil = FileUtils::getInstance();
	
	strData = pUtil->getStringFromFile(pUtil->getWritablePath() + "PLAYER_FILE.magu");

	C_Functions::encryptText(strData, m_strEncryptKey);

	readFile(strData);
}

void C_PlayerState::readFile(const std::string & strInfo)
{
	int nSize(0);
	int nCursor(0);
	int nStatusNum(0);
	std::string strExtract("");

	nSize = strInfo.size();

	while((nCursor != nSize) && (static_cast<int>(E_PLAYER_STATUS::E_MAX) != nStatusNum))
	{
		if (strInfo[nCursor] == '=')
		{
			nCursor++;

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

	for (int nItem(0); nItem < static_cast<int>(E_PLAYER_STATUS::E_MAX); nItem++)
	{
		strSaveInfo += m_arSaveStatusName[nItem];
		strSaveInfo += " = ";
		strSaveInfo += std::to_string(m_arSaveStatus[nItem]);
		strSaveInfo += "\r\n";
	}

	C_Functions::encryptText(strSaveInfo, m_strEncryptKey);

	pUtil->writeStringToFile(strSaveInfo, pUtil->getWritablePath() + "PLAYER_FILE.magu");
}
