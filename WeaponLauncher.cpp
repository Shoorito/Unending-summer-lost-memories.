#include "WeaponLauncher.h"
#include "CocosFunctions.h"
#include "KeyEventManager.h"
#include "PlayerController.h"

C_WeaponLauncher * C_WeaponLauncher::m_pInstance = nullptr;

C_WeaponLauncher * C_WeaponLauncher::create(const std::string& strFile)
{
	if (m_pInstance)
	{
		CCLOG(u8"\"WeaponLauncher\"가 이미 생성 되어 있습니다.");

		return nullptr;
	}

	m_pInstance = new(std::nothrow) C_WeaponLauncher();

	if (m_pInstance && m_pInstance->init())
	{
		m_pInstance->setUseTexture(strFile);
		m_pInstance->preset();
	}
	else
	{
		C_Functions::safeDelete(m_pInstance);
	}

	return m_pInstance;
}

Sprite* C_WeaponLauncher::getLauncher(const int nPosition)
{
	if (nPosition < 0 || nPosition >= static_cast<int>(m_vecLaunchers.size()))
		return nullptr;

	return m_vecLaunchers[nPosition];
}

void C_WeaponLauncher::setUseTexture(const std::string & strFile)
{
	if (strFile == "" || m_strTexture == strFile)
		return;

	m_strTexture = strFile;

	for (int nItem(0); nItem < m_nLauncherMaxCount; nItem++)
	{
		m_vecLaunchers[nItem]->setTexture(m_strTexture);
	}
}

void C_WeaponLauncher::setLaunchersPoint(const Vec2 & vecPoint, const int nPosition)
{
	int nSize(0);

	nSize = static_cast<int>(m_vecLauncherPointers.size());

	if (nPosition >= nSize)
	{
		m_vecLauncherPointers[nPosition] = vecPoint;
	}
}

void C_WeaponLauncher::setMaxWeaponCount(const int nCount)
{
	if (nCount < 1 || nCount == m_nLauncherMaxCount)
		return;

	bool isAdder(false);

	isAdder				= m_nLauncherMaxCount < nCount;
	m_nLauncherMaxCount = nCount;

	for (int nCheck(0); nCheck < m_nLauncherMaxCount; nCheck++)
	{
		(this->*m_arLauncherFunc[isAdder])();
	}
}

void C_WeaponLauncher::setWeaponCount(const int nCount)
{
	if (m_nLauncherMaxCount < nCount || nCount < 1 || m_nLauncherCount == nCount)
		return;

	int  arAdder[2]{-1, 1};
	bool isAdd(false);

	isAdd = m_nLauncherCount < nCount;

	for (int nDisable(m_nLauncherCount); nDisable != nCount;)
	{
		m_vecLaunchers[nDisable]->setVisible(isAdd);

		if (isAdd)
			m_vecLaunchers[nDisable]->resume();
		else
			m_vecLaunchers[nDisable]->pause();

		m_nLauncherCount++;

		nDisable += arAdder[isAdd];
	}
	
	updateLauncher();
}

void C_WeaponLauncher::setEnabled(const bool isEnabled)
{
	if (isEnabled == m_isEnabled)
		return;

	m_isEnabled = isEnabled;
	
	setVisible(isEnabled);

	if (m_isEnabled)
	{
		resume();
	}
	else
	{
		pause();
	}
}

bool C_WeaponLauncher::init()
{
	if (!Node::init())
		return false;

	m_isEnabled			 = false;
	m_strTexture		 = "";
	m_nLauncherCount	 = 0;
	m_nLauncherMaxCount  = 0;

	return true;
}

void C_WeaponLauncher::preset()
{
	m_arLauncherFunc[0] = &C_WeaponLauncher::removeLauncher;
	m_arLauncherFunc[1] = &C_WeaponLauncher::addLauncher;

	setMaxWeaponCount(4);
	scheduleUpdate();
}

void C_WeaponLauncher::addLauncher()
{
	if (!static_cast<int>(m_strTexture.size()))
		return;

	Sprite*		pSprite(nullptr);
	RotateBy*	pRotate(nullptr);
	ScaleTo*	pScaleDown(nullptr);
	ScaleTo*	pScaleUp(nullptr);
	Spawn*		pSpawn(nullptr);
	Repeat*		pRepeat(nullptr);

	pSprite		= Sprite::create(m_strTexture);
	pScaleDown	= ScaleTo::create(0.5f, 0.5f);
	pScaleUp	= ScaleTo::create(0.5f, 1.0f);
	pRotate		= RotateBy::create(1.0f, 360.0f);
	pSpawn		= Spawn::create(Sequence::create(pScaleDown, pScaleUp, nullptr), pRotate, nullptr);
	pRepeat		= Repeat::create(pSpawn, -1);

	pSprite->setVisible(false);
	pSprite->runAction(pRepeat);
	pSprite->pause();

	m_vecLaunchers.emplace_back(pSprite);

	addChild(pSprite);
}

void C_WeaponLauncher::removeLauncher()
{
	if (!m_nLauncherCount)
		return;

	Sprite* pRemover(nullptr);

	pRemover = m_vecLaunchers.back();

	pRemover->stopAllActions();

	m_vecLaunchers.pop_back();

	removeChild(pRemover);
}

void C_WeaponLauncher::updateLauncher()
{
	int nSize(0);
	int nAdder(0);
	Sprite* pLauncher(nullptr);

	nSize = static_cast<int>(m_vecLauncherPointers.size());

	if (m_nLauncherCount)
	{
		if (nSize < m_nLauncherCount)
		{
			bool isEven(false);

			isEven = ((m_nLauncherCount % 2) == 0);

			for (int nItem(!isEven); nItem < m_nLauncherCount; nItem += 2)
			{
				for (int nRight(0); nRight < 2; nRight++)
				{
					pLauncher = m_vecLaunchers[nItem + nRight];

					pLauncher->setPosition(C_PlayerController::getInstance()->getPosition());
					pLauncher->addPositionX(-40.0f * (nAdder + 1));
					pLauncher->addPositionX((80.0f * nRight) * (nRight + nAdder));
					pLauncher->addPositionY(30.0f + (-30.0f * (nAdder + 1)));
				}

				nAdder++;
			}

			if (!isEven)
			{
				pLauncher = m_vecLaunchers[0];

				pLauncher->setPosition(C_PlayerController::getInstance()->getPosition());
				pLauncher->addPositionY(50.0f);
			}
		}
		else
		{
			for (int nItem(0); nItem < m_nLauncherCount; nItem++)
			{
				pLauncher = m_vecLaunchers[nItem];

				pLauncher->setPosition(m_vecLauncherPointers[nItem]);
			}
		}
	}
}

void C_WeaponLauncher::update(float dt)
{
	updateLauncher();
}
