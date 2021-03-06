#include "CocosFunctions.h"
#include "ResourceTable.h"
#include "Item.h"
#include "Boss.h"
#include "Enemy.h"
#include "ItemManager.h"
#include "platform/CCPlatformConfig.h"
#include "platform/CCPlatformMacros.h"

void C_Functions::safeDelete(void * pDeletePointer)
{
	if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		delete pDeletePointer;

		pDeletePointer = nullptr;
	}
	else
	{
		CC_SAFE_DELETE(pDeletePointer);
	}
}

void C_Functions::encryptText(std::string & strTarget, const std::string & strEncrypt)
{
	if (!static_cast<int>(strTarget.size()) < !static_cast<int>(strEncrypt.size()))
		return;

	int nTargetSize(0);
	int nCryptSize(0);
	int nCodeCount(0);

	nTargetSize = static_cast<int>(strTarget.size());
	nCryptSize  = static_cast<int>(strEncrypt.size());

	for (int nText(0); nText < nTargetSize; nText++)
	{
		if (!isCheckSkip(strTarget[nText]))
		{
			if (nCodeCount == nCryptSize)
				nCodeCount = 0;

			strTarget[nText] = strTarget[nText] ^ strEncrypt[nCodeCount];

			nCodeCount++;
		}
	}
}

void C_Functions::convertToString(const int & nTarget, std::string & strResult)
{
	int nPreSize(0);
	int nNowSize(0);
	int nPosition(1);

	strResult = std::to_string(nTarget);
	nPreSize  = static_cast<int>(strResult.size());

	for (int nCount(0); nPreSize >= g_arInitScore[nCount]; nCount++)
	{
		strResult.push_back('0');
	}

	nNowSize = static_cast<int>(strResult.size());

	for (int nCount(1); nCount <= nNowSize; nCount++)
	{
		if (nCount % 4 == 0)
		{
			strResult[nNowSize - nCount] = ',';
		}
		else
		{
			strResult[nNowSize - nCount] = strResult[nPreSize - nPosition];

			nPosition++;
		}
	}
}

const std::string C_Functions::convertToString(const int & nTarget)
{
	int nPreSize(0);
	int nNowSize(0);
	int nPosition(1);
	std::string strResult("");

	strResult = std::to_string(nTarget);
	nPreSize = static_cast<int>(strResult.size());

	for (int nCount(0); nPreSize >= g_arInitScore[nCount]; nCount++)
	{
		strResult.push_back('0');
	}

	nNowSize = static_cast<int>(strResult.size());

	for (int nCount(1); nCount <= nNowSize; nCount++)
	{
		if (nCount % 4 == 0)
		{
			strResult[nNowSize - nCount] = ',';
		}
		else
		{
			strResult[nNowSize - nCount] = strResult[nPreSize - nPosition];

			nPosition++;
		}
	}

	return strResult;
}

int C_Functions::getDigits(const int nNumber)
{
	int nDivide(0);
	int nRemain(0);
	int nResult(1);

	nRemain = nNumber % 10; // >> ex. 123456 >> 6
	nDivide = nNumber / 10; // >> ex. 123456 >> 12345

	while (!nRemain)
	{
		nRemain = nDivide % 10; // >> ex. 123456 >> 6
		nDivide /= 10; // >> ex. 123456 >> 12345

		nResult++;
	}

	return nResult;
}

int C_Functions::getCommaPosition(const int nNumber)
{
	int nComma(0);

	while ((nNumber + nComma) >= g_arInitScore[nComma])
	{
		nComma++;
	}

	return nComma;
}

bool C_Functions::isComma(const int nPosition, const std::string & strTarget)
{
	return strTarget[nPosition] == ',';
}

const bool C_Functions::isCheckSkip(const char & cWord)
{
	for (int nCheck(0); nCheck < g_nCheckSkipNum; nCheck++)
	{
		if (cWord == g_arCheckSkipText[nCheck])
			return true;
	}

	return false;
}

void C_Functions::updateScoreLength(int nAdder, int nSize, int & nCommaCount, std::string & strTarget)
{
	int nNowSize(0);

	for (int nText(0); nText < (nAdder - nSize); nText++)
	{
		strTarget.push_back('0');
	}

	nNowSize = static_cast<int>(strTarget.size()) - 1;
	nSize -= 1;

	for (int nText(0); nText <= nSize; nText++)
	{
		strTarget[nNowSize - nText] = strTarget[nSize - nText];
	}

	nSize++;

	for (int nAdd(nNowSize - nSize); nAdd >= 0; nAdd--)
	{
		if ((nNowSize - nAdd + 1) >= g_arInitScore[nCommaCount])
		{
			strTarget[nAdd] = ',';
			nCommaCount++;
		}
		else
		{
			strTarget[nAdd] = '0';
		}
	}

	strTarget[0] = '1';
}

const int C_Functions::convertToInt(const std::string & strTarget)
{
	int nSize(0);
	int nResult(0);
	
	nSize = strTarget.size();

	for (int nCheck(0); nCheck < nSize; nCheck++)
	{
		nResult *= 10;
		nResult += static_cast<int>(strTarget[nCheck] - '0');
	}
	
	return nResult;
}

void C_Functions::swap(void * pSrc, void * pDst)
{
	void* pTemp(nullptr);

	pTemp = pSrc;

	pSrc = pDst;
	
	pDst = pTemp;
}

const float C_Functions::getHomingAngle(const Vec2& vecStartpos, const Vec2& vecEndpos)
{
	return atan2f(vecStartpos.y - vecEndpos.y, vecEndpos.x - vecStartpos.x) * 180.0f / 3.141592f;
}

void C_Functions::dropItem(C_Enemy * pTarget)
{
	int arDrop[static_cast<int>(E_ITEM_TYPE::E_MAX)]{};
	E_ENEMY_TYPE eEnemyType(E_ENEMY_TYPE::E_NORMAL);
	C_ItemManager* pManager(nullptr);

	pManager = C_ItemManager::getInstance();
	eEnemyType = pTarget->getType();

	if (eEnemyType == E_ENEMY_TYPE::E_BOSS)
	{
		C_Boss* pBoss(nullptr);

		pBoss = static_cast<C_Boss*>(pTarget);

		if (pBoss->getBossType() == E_BOSS_TYPE::E_NORMAL)
		{
			arDrop[static_cast<int>(E_ITEM_TYPE::E_UP_HP)] = 10;
			arDrop[static_cast<int>(E_ITEM_TYPE::E_UP_MP)] = 10;
			arDrop[static_cast<int>(E_ITEM_TYPE::E_UP_EXP)] = 10;
			arDrop[static_cast<int>(E_ITEM_TYPE::E_UP_SCORE)] = 20;
		}
		else
		{
			arDrop[static_cast<int>(E_ITEM_TYPE::E_UP_HP)] = 5;
			arDrop[static_cast<int>(E_ITEM_TYPE::E_UP_MP)] = 5;
			arDrop[static_cast<int>(E_ITEM_TYPE::E_UP_EXP)] = 10;
			arDrop[static_cast<int>(E_ITEM_TYPE::E_UP_SCORE)] = 20;
		}
	}
	else if (eEnemyType == E_ENEMY_TYPE::E_NORMAL)
	{
		arDrop[static_cast<int>(E_ITEM_TYPE::E_UP_HP)] = 1;
		arDrop[static_cast<int>(E_ITEM_TYPE::E_UP_MP)] = 1;
		arDrop[static_cast<int>(E_ITEM_TYPE::E_UP_EXP)] = 1;
		arDrop[static_cast<int>(E_ITEM_TYPE::E_UP_SCORE)] = 1;
	}

	for (int nType(0); nType < static_cast<int>(E_ITEM_TYPE::E_MAX); nType++)
	{
		for (int nItemNum(0); nItemNum < arDrop[nType]; nItemNum++)
		{
			C_Item*	pItem(nullptr);

			pItem = pManager->popItem(E_USE_TYPE::E_NOT_USED);

			if (!pItem)
			{
				return;
			}

			pItem->setUseType(E_USE_TYPE::E_USED);
			pItem->setType(static_cast<E_ITEM_TYPE>(nType));
			pItem->setAddValue
			(
				random
				(
					g_arItemValueMin[nType > static_cast<int>(E_ITEM_TYPE::E_UP_EXP)],
					g_arItemValueMax[nType > static_cast<int>(E_ITEM_TYPE::E_UP_EXP)]
				)
			);

			pItem->setTextureRect
			(
				Rect
				(
					g_fItemWidth * static_cast<float>(nType),
					0.0f,
					g_fItemWidth,
					g_fItemHeight
				)
			);

			pItem->setPosition(pTarget->getPosition());
			pItem->addPosition(random(-100.0f, 100.0f), random(-100.0f, 100.0f));
			pItem->setEnabled(true);
			pItem->startShowAct();

			pManager->pushItem(pItem);
		}
	}
}
