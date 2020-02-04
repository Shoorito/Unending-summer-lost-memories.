#include "DanmakuManager.h"
#include "CocosFunctions.h"
#include "Danmaku.h"

C_DanmakuManager * C_DanmakuManager::m_pInstance = nullptr;

C_DanmakuManager * C_DanmakuManager::create()
{
	if (m_pInstance)
	{
		CCLOG(u8"\"DanmakuManager\"가 이미 생성 되어 있습니다.");

		return nullptr;
	}

	m_pInstance = new(std::nothrow) C_DanmakuManager();

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

void C_DanmakuManager::addDanmaku(C_Danmaku * pDanmaku)
{
	pushDanmaku(pDanmaku);
	addChild(pDanmaku);
}

void C_DanmakuManager::pushDanmaku(C_Danmaku * pDanmaku)
{
	E_USE_TYPE eType(E_USE_TYPE::E_NOT_USED);

	eType = pDanmaku->getUseType();

	if (!m_arHead[static_cast<int>(eType)])
	{
		m_arHead[static_cast<int>(eType)] = pDanmaku;
		m_arTail[static_cast<int>(eType)] = pDanmaku;
		m_arCursor[static_cast<int>(eType)] = pDanmaku;

		pDanmaku->setPrev(pDanmaku);
		pDanmaku->setNext(pDanmaku);
	}
	else
	{
		m_arTail[static_cast<int>(eType)]->setNext(pDanmaku);
		m_arHead[static_cast<int>(eType)]->setPrev(pDanmaku);
		pDanmaku->setPrev(m_arTail[static_cast<int>(eType)]);
		pDanmaku->setNext(m_arHead[static_cast<int>(eType)]);

		m_arTail[static_cast<int>(eType)] = pDanmaku;
	}

	m_arCountList[static_cast<int>(eType)]++;
}

void C_DanmakuManager::changeDanmaku(C_Danmaku * pDanmaku)
{
	if (!pDanmaku)
		return;

	E_USE_TYPE arSwap[static_cast<int>(E_USE_TYPE::E_MAX)] { E_USE_TYPE::E_USED, E_USE_TYPE::E_NOT_USED };

	popDanmaku(pDanmaku);

	pDanmaku->setUseType(arSwap[static_cast<int>(pDanmaku->getUseType())]);

	pushDanmaku(pDanmaku);
}

C_Danmaku * C_DanmakuManager::popDanmaku(const E_USE_TYPE eType)
{
	if (!m_arCountList[(int)eType])
		return nullptr;

	C_Danmaku* pResult(m_arCursor[(int)eType]);

	if (m_arCountList[(int)eType] == 1)
	{
		m_arHead[(int)eType] = nullptr;
		m_arTail[(int)eType] = nullptr;
		m_arCursor[(int)eType] = nullptr;
		m_arCountList[(int)eType] = 0;
		pResult->setPrev(nullptr);
		pResult->setNext(nullptr);

		return pResult;
	}

	if (m_arTail[(int)eType] == pResult)
		m_arTail[(int)eType] = pResult->getPrev();

	if (m_arHead[(int)eType] == pResult)
		m_arHead[(int)eType] = pResult->getNext();

	moveCursor(eType);

	pResult->getPrev()->setNext(pResult->getNext());
	pResult->getNext()->setPrev(pResult->getPrev());
	pResult->setNext(nullptr);
	pResult->setPrev(nullptr);

	m_arCountList[(int)eType]--;

	return pResult;
}

C_Danmaku* C_DanmakuManager::popDanmaku(C_Danmaku * pDanmaku)
{
	if (!m_arCountList[static_cast<int>(pDanmaku->getUseType())])
		return nullptr;

	E_USE_TYPE eType(E_USE_TYPE::E_NOT_USED);

	eType = pDanmaku->getUseType();

	if (m_arCountList[static_cast<int>(eType)] == 1)
	{
		m_arHead[static_cast<int>(eType)]		= nullptr;
		m_arTail[static_cast<int>(eType)]		= nullptr;
		m_arCursor[static_cast<int>(eType)]		= nullptr;
		m_arCountList[static_cast<int>(eType)]	= 0;

		pDanmaku->setPrev(nullptr);
		pDanmaku->setNext(nullptr);

		return pDanmaku;
	}

	if (pDanmaku == m_arCursor[static_cast<int>(eType)])
	{
		moveCursor(eType, 1);
	}

	if (m_arTail[static_cast<int>(eType)] == pDanmaku)
		m_arTail[static_cast<int>(eType)] = pDanmaku->getPrev();

	if (m_arHead[static_cast<int>(eType)] == pDanmaku)
		m_arHead[static_cast<int>(eType)] = pDanmaku->getNext();

	pDanmaku->getPrev()->setNext(pDanmaku->getNext());
	pDanmaku->getNext()->setPrev(pDanmaku->getPrev());

	m_arCountList[static_cast<int>(eType)]--;

	return pDanmaku;
}

void C_DanmakuManager::moveCursor(const E_USE_TYPE eType, const int nMoveCount)
{
	if (!m_arCursor[static_cast<int>(eType)])
		return;

	for (int nLoop(0); nLoop < nMoveCount; nLoop++)
	{
		m_arCursor[static_cast<int>(eType)] = m_arCursor[static_cast<int>(eType)]->getNext();
	}
}

void C_DanmakuManager::initCursor(const E_USE_TYPE eType)
{
	m_arCursor[static_cast<int>(eType)] = m_arHead[static_cast<int>(eType)];
}

void C_DanmakuManager::changeDanmakuRect(const Rect & recDanmaku, const E_USE_TYPE eType)
{
	m_arCursor[(int)eType]->getTexture()->setTextureRect(recDanmaku);
}

void C_DanmakuManager::allDisabledDanmaku()
{
	if (!m_arCountList[(int)E_USE_TYPE::E_USED])
		return;

	initCursor(E_USE_TYPE::E_USED);

	for (int nDisabled(0); m_arCursor[(int)E_USE_TYPE::E_USED]; nDisabled++)
	{
		m_arCursor[static_cast<int>(E_USE_TYPE::E_USED)]->removeDanmaku();
		
		changeDanmaku(m_arCursor[static_cast<int>(E_USE_TYPE::E_USED)]);
	}
}

void C_DanmakuManager::allPauseDanmaku()
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

void C_DanmakuManager::allResumeDanmaku()
{
	if (!m_arCountList[(int)E_USE_TYPE::E_USED])
		return;

	initCursor(E_USE_TYPE::E_USED);

	for (int nPaused(0); nPaused < m_arCountList[static_cast<int>(E_USE_TYPE::E_USED)]; nPaused++)
	{
		m_arCursor[static_cast<int>(E_USE_TYPE::E_USED)]->resume();

		moveCursor(E_USE_TYPE::E_USED);
	}
}

bool C_DanmakuManager::init()
{
	if (!Node::init())
		return false;

	return true;
}

void C_DanmakuManager::preset()
{

}
