#include "WeaponManager.h"
#include "CocosFunctions.h"
#include "KeyEventManager.h"
#include "PlayerWeapon.h"
#include "WeaponLauncher.h"
#include "PlayerController.h"

C_WeaponManager * C_WeaponManager::m_pInstance = nullptr;

C_WeaponManager * C_WeaponManager::create()
{
	if (m_pInstance)
	{
		CCLOG(u8"\"WeaponManager\"가 이미 생성 되어 있습니다.");

		return nullptr;
	}

	m_pInstance = new(std::nothrow) C_WeaponManager();

	if (m_pInstance && m_pInstance->init())
	{
		m_pInstance->preset();
	}
	else
	{
		C_Functions::safeDelete(m_pInstance);
	}

	return m_pInstance;
}

void C_WeaponManager::setWeapon(const E_WEAPON_TYPE& eType, const std::string& strFile, const Rect& recTexture)
{
	int nSize(0);

	nSize = m_vecWeapon[static_cast<int>(eType)].size();
	m_arWeapon[static_cast<int>(eType)]		= strFile;
	m_arWeaponRect[static_cast<int>(eType)] = recTexture;

	for (int nCount(0); nCount < nSize; nCount++)
	{
		m_vecWeapon[static_cast<int>(eType)][nCount]->setTextureWithRect(strFile, recTexture);
	}
}

void C_WeaponManager::setEnabled(const bool isEnabled)
{
	if (isEnabled == m_isEnabled)
		return;

	if (m_isEnabled)
		resume();
	else
		pause();
}

void C_WeaponManager::createWeapon(const E_WEAPON_TYPE & eType, const int nCount)
{
	for (int nWeapon(0); nWeapon < nCount; nWeapon++)
	{
		addWeapon(eType);
	}
}

void C_WeaponManager::setWeaponFile(const std::string & strFile, const E_WEAPON_TYPE& eType)
{
	if (strFile == "")
		return;

	m_arWeapon[static_cast<int>(eType)] = strFile;
}

void C_WeaponManager::setWeaponRect(const Rect & recWeapon, const E_WEAPON_TYPE& eType)
{
	if (recWeapon.equals(Rect::ZERO))
		return;

	m_arWeaponRect[static_cast<int>(eType)] = recWeapon;
}

void C_WeaponManager::addWeapon(const E_WEAPON_TYPE & eType)
{
	C_PlayerWeapon* pWeapon(nullptr);

	pWeapon = C_PlayerWeapon::create();

	pWeapon->setType(eType);
	pWeapon->setEnabled(false);
	pWeapon->setTextureWithRect
	(
		m_arWeapon[static_cast<int>(eType)], m_arWeaponRect[static_cast<int>(eType)]
	);
	
	addChild(pWeapon);

	m_vecWeapon[static_cast<int>(eType)].emplace_back(pWeapon);
}

void C_WeaponManager::removeWeapon(const E_WEAPON_TYPE & eType)
{
	C_PlayerWeapon* pWeapon(nullptr);

	pWeapon = m_vecWeapon[static_cast<int>(eType)].back();

	m_vecWeapon[static_cast<int>(eType)].pop_back();

	removeChild(pWeapon);
}

void C_WeaponManager::allPause()
{
	for (int nType(0); nType < static_cast<int>(E_WEAPON_TYPE::E_MAX); nType++)
	{
		for (int nWeapon(0); nWeapon < static_cast<int>(m_vecWeapon[nType].size()); nWeapon++)
		{
			if (m_vecWeapon[nType][nWeapon]->isEnabled())
			{
				m_vecWeapon[nType][nWeapon]->pause();
			}
		}
	}
}

void C_WeaponManager::allResume()
{
	for (int nType(0); nType < static_cast<int>(E_WEAPON_TYPE::E_MAX); nType++)
	{
		for (int nWeapon(0); nWeapon < static_cast<int>(m_vecWeapon[nType].size()); nWeapon++)
		{
			if (m_vecWeapon[nType][nWeapon]->isEnabled())
			{
				m_vecWeapon[nType][nWeapon]->resume();
			}
		}
	}
}

bool C_WeaponManager::init()
{
	if (!Node::init())
		return false;

	m_isAttackable = true;
	m_nUpdateCount = 0;

	return true;
}

void C_WeaponManager::preset()
{
	schedule(schedule_selector(C_WeaponManager::update), 0.01f);
	pause();
}

void C_WeaponManager::updateMainWeapon()
{
	if (m_nUpdateCount % 10)
		return;

	C_PlayerController* pPlayer(nullptr);

	pPlayer = C_PlayerController::getInstance();

	for (int nWeapon(0); nWeapon < 2; nWeapon++)
	{
		if (!static_cast<int>(m_vecWeapon[0].size()))
			return;

		if (m_arWeaponCount[static_cast<int>(E_WEAPON_TYPE::E_NORMAL)] >= static_cast<int>(m_vecWeapon[0].size()))
			m_arWeaponCount[static_cast<int>(E_WEAPON_TYPE::E_NORMAL)] = 0;

		C_PlayerWeapon* pWeapon(nullptr);

		pWeapon = m_vecWeapon[0][m_arWeaponCount[static_cast<int>(E_WEAPON_TYPE::E_NORMAL)]];

		pWeapon->setPosition(pPlayer->getPosition());
		pWeapon->addPosition(-15.0f + (nWeapon * 30.0f), 30.0f);
		pWeapon->setEnabled(true);

		m_arWeaponCount[static_cast<int>(E_WEAPON_TYPE::E_NORMAL)]++;
	}
}

void C_WeaponManager::updateSubWeapon()
{
	if (m_nUpdateCount % 10)
		return;

	C_WeaponLauncher* pLauncher(nullptr);

	pLauncher = C_WeaponLauncher::getInstance();

	for (int nWeapon(0); nWeapon < C_WeaponLauncher::getInstance()->getLauncherCount(); nWeapon++)
	{
		if (!static_cast<int>(m_vecWeapon[1].size()))
			return;

		if (m_arWeaponCount[static_cast<int>(E_WEAPON_TYPE::E_SUB)] >= static_cast<int>(m_vecWeapon[1].size()))
			m_arWeaponCount[static_cast<int>(E_WEAPON_TYPE::E_SUB)] = 0;

		C_PlayerWeapon* pWeapon(nullptr);

		pWeapon = m_vecWeapon[1][m_arWeaponCount[static_cast<int>(E_WEAPON_TYPE::E_SUB)]];

		pWeapon->setPosition(pLauncher->getLauncher(nWeapon)->getPosition());
		pWeapon->setEnabled(true);

		m_arWeaponCount[static_cast<int>(E_WEAPON_TYPE::E_SUB)]++;
	}
}

void C_WeaponManager::update(float fDelay)
{
	if (m_nUpdateCount >= 1000000000)
		m_nUpdateCount = 0;

	if (C_KeyEvent_Manager::getInstance()->getPushedType(149) == E_KEY_STATE::E_PUSH)
	{
		updateMainWeapon();
		updateSubWeapon();
	}

	m_nUpdateCount++;
}
