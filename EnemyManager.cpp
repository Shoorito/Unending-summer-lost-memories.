#include "EnemyManager.h"
#include "Enemy.h"
#include "ResourceTable.h"
#include "CocosFunctions.h"

C_EnemyManager * C_EnemyManager::m_pInstance = nullptr;

C_EnemyManager * C_EnemyManager::create()
{
	if (m_pInstance)
	{
		CCLOG(u8"\"WeaponManager\"가 이미 생성 되어 있습니다.");

		return nullptr;
	}

	m_pInstance = new(std::nothrow) C_EnemyManager();

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

void C_EnemyManager::addEnemy(C_Enemy * pEnemy, const E_USE_TYPE & eType)
{
	pushEnemy(pEnemy, eType);

	addChild(pEnemy);
}

void C_EnemyManager::pushEnemy(C_Enemy * pEnemy, const E_USE_TYPE & eType)
{
	if (!m_arHead[static_cast<int>(eType)])
	{
		m_arHead[static_cast<int>(eType)] = pEnemy;
		m_arTail[static_cast<int>(eType)] = pEnemy;
		m_arCursor[static_cast<int>(eType)] = pEnemy;

		pEnemy->setPrev(pEnemy);
		pEnemy->setNext(pEnemy);
	}
	else
	{
		m_arTail[static_cast<int>(eType)]->setNext(pEnemy);
		m_arHead[static_cast<int>(eType)]->setPrev(pEnemy);
		pEnemy->setPrev(m_arTail[static_cast<int>(eType)]);
		pEnemy->setNext(m_arHead[static_cast<int>(eType)]);

		m_arTail[static_cast<int>(eType)] = pEnemy;
	}

	m_arCountList[static_cast<int>(eType)]++;
}

void C_EnemyManager::changeEnemy(C_Enemy * pEnemy, const E_USE_TYPE & eChangeType)
{
	if (!pEnemy)
		return;

	E_USE_TYPE arSwap[static_cast<int>(E_USE_TYPE::E_MAX)]
	{
		E_USE_TYPE::E_USED, E_USE_TYPE::E_NOT_USED 
	};

	popEnemy(pEnemy, arSwap[static_cast<int>(eChangeType)]);
	pushEnemy(pEnemy, eChangeType);
}

void C_EnemyManager::popEnemy(C_Enemy * pEnemy, const E_USE_TYPE & eType)
{
	if (!m_arCountList[static_cast<int>(eType)])
		return;

	if (m_arCountList[static_cast<int>(eType)] < 2)
	{
		m_arHead[static_cast<int>(eType)]		= nullptr;
		m_arTail[static_cast<int>(eType)]		= nullptr;
		m_arCursor[static_cast<int>(eType)]		= nullptr;
		m_arCountList[static_cast<int>(eType)]	= 0;

		pEnemy->setPrev(nullptr);
		pEnemy->setNext(nullptr);

		return;
	}

	if (pEnemy == m_arCursor[static_cast<int>(eType)])
	{
		moveCursor(eType, 1);
	}

	if (m_arHead[static_cast<int>(eType)] == pEnemy)
		m_arHead[static_cast<int>(eType)] = pEnemy->getNext();
	if (m_arTail[static_cast<int>(eType)] == pEnemy)
		m_arTail[static_cast<int>(eType)] = pEnemy->getPrev();

	pEnemy->getPrev()->setNext(pEnemy->getNext());
	pEnemy->getNext()->setPrev(pEnemy->getPrev());

	pEnemy->setNext(nullptr);
	pEnemy->setPrev(nullptr);

	m_arCountList[static_cast<int>(eType)]--;
}

void C_EnemyManager::disabledAllEnemy(const E_ENEMY_TYPE & eType)
{
	if (!m_arCountList[(int)E_USE_TYPE::E_USED])
		return;

	int nSize(0);
	C_Enemy* pEnemy(nullptr);

	initCursor(E_USE_TYPE::E_USED);

	nSize = m_arCountList[static_cast<int>(E_USE_TYPE::E_USED)];

	for (int nEnemy(0); nEnemy < nSize; nEnemy++)
	{
		pEnemy = m_arCursor[(int)E_USE_TYPE::E_USED];

		if (pEnemy->getType() == eType)
		{
			pEnemy->setEnabled(false);
			changeEnemy(pEnemy, E_USE_TYPE::E_NOT_USED);
		}
		else
		{
			moveCursor(E_USE_TYPE::E_USED);
		}
	}
}

void C_EnemyManager::pauseAllEnemy(const E_ENEMY_TYPE & eType)
{
	if (!m_arCountList[(int)E_USE_TYPE::E_USED])
		return;

	int nSize(0);
	C_Enemy* pEnemy(nullptr);

	initCursor(E_USE_TYPE::E_USED);

	nSize = m_arCountList[static_cast<int>(E_USE_TYPE::E_USED)];

	for (int nEnemy(0); nEnemy < nSize; nEnemy++)
	{
		pEnemy = m_arCursor[(int)E_USE_TYPE::E_USED];

		if (pEnemy->getType() == eType)
		{
			pEnemy->pause();
		}
		else
		{
			moveCursor(E_USE_TYPE::E_USED);
		}
		
		moveCursor(E_USE_TYPE::E_USED);
	}
}

void C_EnemyManager::resumeAllEnemy(const E_ENEMY_TYPE & eType)
{
	if (!m_arCountList[(int)E_USE_TYPE::E_USED])
		return;

	int nSize(0);
	C_Enemy* pEnemy(nullptr);

	initCursor(E_USE_TYPE::E_USED);

	nSize = m_arCountList[static_cast<int>(E_USE_TYPE::E_USED)];

	for (int nEnemy(0); nEnemy < nSize; nEnemy++)
	{
		pEnemy = m_arCursor[(int)E_USE_TYPE::E_USED];

		if (pEnemy->getType() == eType)
		{
			pEnemy->resume();
		}
		else
		{
			moveCursor(E_USE_TYPE::E_USED);
		}

		moveCursor(E_USE_TYPE::E_USED);
	}
}

C_Enemy * C_EnemyManager::getImmediateEnemy(const Vec2 & pCharacterPos)
{
	float	 fMin(9999.0f);
	C_Enemy* pResult(nullptr);

	if (!m_arHead[(int)E_USE_TYPE::E_USED])
		return nullptr;

	initCursor(E_USE_TYPE::E_USED);

	for (int nEnemy(0); nEnemy < m_arCountList[(int)E_USE_TYPE::E_USED]; nEnemy++)
	{
		float	 fNowData(0.0f);
		C_Enemy* pTarget(nullptr);

		pTarget = m_arCursor[static_cast<int>(E_USE_TYPE::E_USED)];

		if (g_recWinArea.containsPoint(pTarget->getPosition()))
		{
			fNowData += fabsf(pTarget->getPositionX() - pCharacterPos.x);
			fNowData += fabsf(pTarget->getPositionY() - pCharacterPos.y);

			if (fNowData < fMin)
			{
				fMin	= fNowData;
				pResult = m_arCursor[(int)E_USE_TYPE::E_USED];
			}
		}

		moveCursor(E_USE_TYPE::E_USED);
	}

	return pResult;
}

void C_EnemyManager::initCursor(const E_USE_TYPE& eType)
{
	m_arCursor[static_cast<int>(eType)] = m_arHead[static_cast<int>(eType)];
}

void C_EnemyManager::moveCursor(const E_USE_TYPE& eType, const int nMove)
{
	if (!m_arCursor[static_cast<int>(eType)])
		return;

	for (int nLoop(0); nLoop < nMove; nLoop++)
	{
		m_arCursor[static_cast<int>(eType)] = m_arCursor[static_cast<int>(eType)]->getNext();
	}
}

bool C_EnemyManager::init()
{
	if (!Node::init())
		return false;

	return true;
}

void C_EnemyManager::preset()
{

}
