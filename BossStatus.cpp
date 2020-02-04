#include "BossStatus.h"
#include "CocosFunctions.h"

C_BossStatus * C_BossStatus::m_pInstance = nullptr;

C_BossStatus * C_BossStatus::create()
{
	if (m_pInstance)
	{
		CCLOG(u8"\"BossStatus\"가 이미 생성 되어 있습니다.");

		return nullptr;
	}

	m_pInstance = new(std::nothrow) C_BossStatus();

	if (m_pInstance)
	{
		m_pInstance->init();
	}
	else
	{
		C_Functions::safeDelete(m_pInstance);
	}

	return m_pInstance;
}

void C_BossStatus::setBossName(const std::string & strName)
{
	if (strName == "" || strName == m_strBossName)
		return;

	m_strBossName = strName;
}

void C_BossStatus::addBarType(const int nType)
{
	if (nType < 1)
		return;

	m_vecBarTypeList.emplace_back(nType);
	m_vecHPList.emplace_back(std::vector<int>());
	m_vecSpellList.emplace_back(std::vector<std::string>());
}

void C_BossStatus::addBarHP(const int nHP, const int nPosition)
{
	if (nHP < 1 || nPosition < 0)
		return;

	if (nPosition >= static_cast<int>(m_vecHPList.size()))
		return;

	m_vecHPList[nPosition].emplace_back(nHP);
}

void C_BossStatus::addSpellName(const std::string & strSpellName, const int nPosition)
{
	if (strSpellName == "" || nPosition < 0)
		return;

	if (nPosition >= static_cast<int>(m_vecSpellList.size()))
		return;

	m_vecSpellList[nPosition].emplace_back(strSpellName);
}

void C_BossStatus::removeBarType()
{
	m_vecBarTypeList.pop_back();
}

void C_BossStatus::removeBarHP(const int nPosition)
{
	if (nPosition >= static_cast<int>(m_vecHPList.size()))
		return;

	m_vecHPList[nPosition].pop_back();
}

void C_BossStatus::removeSpellName(const int nPosition)
{
	if (nPosition >= static_cast<int>(m_vecSpellList.size()))
		return;

	m_vecSpellList[nPosition].pop_back();
}

void C_BossStatus::clearName()
{
	m_strBossName.clear();
}

void C_BossStatus::clearBarType()
{
	m_vecBarTypeList.clear();
}

void C_BossStatus::clearBarHP()
{
	m_vecHPList.clear();
}

void C_BossStatus::clearSpellName()
{
	m_vecSpellList.clear();
}

void C_BossStatus::clearAllInformation()
{
	clearName();
	clearBarHP();
	clearBarType();
	clearSpellName();
}

void C_BossStatus::init()
{
	m_strBossName = "";

	m_vecHPList.clear();
	m_vecSpellList.clear();
	m_vecBarTypeList.clear();
}
