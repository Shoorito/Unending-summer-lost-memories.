#include "ItemManager.h"
#include "Item.h"
#include "CocosFunctions.h"

C_ItemManager * C_ItemManager::m_pInstance = nullptr;

C_ItemManager * C_ItemManager::create()
{
	if (m_pInstance)
	{
		CCLOG(u8"\"ItemManager\"가 이미 생성 되어 있습니다.");

		return nullptr;
	}

	m_pInstance = new(std::nothrow) C_ItemManager();

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

void C_ItemManager::addItem(C_Item * pItem)
{
	pushItem(pItem);
	addChild(pItem);
}

void C_ItemManager::pushItem(C_Item * pItem)
{
	E_USE_TYPE eType(E_USE_TYPE::E_NOT_USED);

	eType = pItem->getUseType();

	if (!m_arHead[static_cast<int>(eType)])
	{
		m_arHead[static_cast<int>(eType)]   = pItem;
		m_arTail[static_cast<int>(eType)]	= pItem;
		m_arCursor[static_cast<int>(eType)] = pItem;

		pItem->setPrev(pItem);
		pItem->setNext(pItem);
	}
	else
	{
		m_arTail[static_cast<int>(eType)]->setNext(pItem);
		m_arHead[static_cast<int>(eType)]->setPrev(pItem);

		pItem->setPrev(m_arTail[static_cast<int>(eType)]);
		pItem->setNext(m_arHead[static_cast<int>(eType)]);

		m_arTail[static_cast<int>(eType)] = pItem;
	}

	m_arCountList[static_cast<int>(eType)]++;
}

void C_ItemManager::changeItem(C_Item * pItem)
{
	if (!pItem)
		return;

	E_USE_TYPE arSwap[static_cast<int>(E_USE_TYPE::E_MAX)]{ E_USE_TYPE::E_USED, E_USE_TYPE::E_NOT_USED };

	popItem(pItem);

	pItem->setUseType(arSwap[static_cast<int>(pItem->getUseType())]);

	pushItem(pItem);
}

C_Item * C_ItemManager::popItem(C_Item * pItem)
{
	if (!m_arCountList[static_cast<int>(pItem->getUseType())])
		return nullptr;

	E_USE_TYPE eType(E_USE_TYPE::E_NOT_USED);

	eType = pItem->getUseType();

	if (m_arCountList[static_cast<int>(eType)] == 1)
	{
		m_arHead[static_cast<int>(eType)]		= nullptr;
		m_arTail[static_cast<int>(eType)]		= nullptr;
		m_arCursor[static_cast<int>(eType)]		= nullptr;
		m_arCountList[static_cast<int>(eType)]	= 0;

		pItem->setPrev(nullptr);
		pItem->setNext(nullptr);

		return pItem;
	}

	if (pItem == m_arCursor[static_cast<int>(eType)])
	{
		moveCursor(eType);
	}

	if (m_arTail[static_cast<int>(eType)] == pItem)
		m_arTail[static_cast<int>(eType)] =  pItem->getPrev();

	if (m_arHead[static_cast<int>(eType)] == pItem)
		m_arHead[static_cast<int>(eType)] =  pItem->getNext();

	pItem->getPrev()->setNext(pItem->getNext());
	pItem->getNext()->setPrev(pItem->getPrev());

	m_arCountList[static_cast<int>(eType)]--;

	return pItem;
}

C_Item * C_ItemManager::popItem(const E_USE_TYPE eType)
{
	if (!m_arCountList[static_cast<int>(eType)])
		return nullptr;

	C_Item* pResult(m_arCursor[static_cast<int>(eType)]);

	if (m_arCountList[static_cast<int>(eType)] == 1)
	{
		m_arHead[static_cast<int>(eType)]		= nullptr;
		m_arTail[static_cast<int>(eType)]		= nullptr;
		m_arCursor[static_cast<int>(eType)]		= nullptr;
		m_arCountList[static_cast<int>(eType)]	= 0;

		pResult->setPrev(nullptr);
		pResult->setNext(nullptr);

		return pResult;
	}

	if (m_arTail[static_cast<int>(eType)] == pResult)
		m_arTail[static_cast<int>(eType)] = pResult->getPrev();

	if (m_arHead[static_cast<int>(eType)] == pResult)
		m_arHead[static_cast<int>(eType)] = pResult->getNext();

	moveCursor(eType);

	pResult->getPrev()->setNext(pResult->getNext());
	pResult->getNext()->setPrev(pResult->getPrev());
	pResult->setNext(nullptr);
	pResult->setPrev(nullptr);

	m_arCountList[static_cast<int>(eType)]--;

	return pResult;
}

void C_ItemManager::moveCursor(const E_USE_TYPE eType, const int nMoveCount)
{
	if (!m_arCursor[static_cast<int>(eType)])
		return;

	for (int nLoop(0); nLoop < nMoveCount; nLoop++)
	{
		m_arCursor[static_cast<int>(eType)] = m_arCursor[static_cast<int>(eType)]->getNext();
	}
}

void C_ItemManager::initCursor(const E_USE_TYPE eType)
{
	m_arCursor[static_cast<int>(eType)] = m_arHead[static_cast<int>(eType)];
}

void C_ItemManager::allDisabledItem()
{
	if (!m_arCountList[static_cast<int>(E_USE_TYPE::E_USED)])
		return;

	initCursor(E_USE_TYPE::E_USED);

	for (int nDisabled(0); m_arCursor[static_cast<int>(E_USE_TYPE::E_USED)]; nDisabled++)
	{
		m_arCursor[static_cast<int>(E_USE_TYPE::E_USED)]->setPosition(-500.0f, -500.0f);
		m_arCursor[static_cast<int>(E_USE_TYPE::E_USED)]->stopAllActions();
		m_arCursor[static_cast<int>(E_USE_TYPE::E_USED)]->setEnabled(false);

		changeItem(m_arCursor[static_cast<int>(E_USE_TYPE::E_USED)]);
	}
}

void C_ItemManager::allPauseItem()
{
	if (!m_arCountList[(int)E_USE_TYPE::E_USED])
		return;

	initCursor(E_USE_TYPE::E_USED);

	for (int nPaused(0); nPaused < m_arCountList[static_cast<int>(E_USE_TYPE::E_USED)]; nPaused++)
	{
		m_arCursor[static_cast<int>(E_USE_TYPE::E_USED)]->pause();

		moveCursor(E_USE_TYPE::E_USED);
	}
}

void C_ItemManager::allResumeItem()
{
	if (!m_arCountList[static_cast<int>(E_USE_TYPE::E_USED)])
		return;

	initCursor(E_USE_TYPE::E_USED);

	for (int nResumed(0); nResumed < m_arCountList[static_cast<int>(E_USE_TYPE::E_USED)]; nResumed++)
	{
		m_arCursor[static_cast<int>(E_USE_TYPE::E_USED)]->resume();

		moveCursor(E_USE_TYPE::E_USED);
	}
}

bool C_ItemManager::init()
{
	if (!Node::init())
		return false;

	return true;
}

void C_ItemManager::preset()
{

}
