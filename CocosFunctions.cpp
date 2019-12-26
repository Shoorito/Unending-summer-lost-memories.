#include "CocosFunctions.h"
#include "ResourceTable.h"
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

void C_Functions::encryptText(const std::string & strText, const std::string & strEncrypt, std::string & strResult)
{
	if (static_cast<int>(strText.size()) < static_cast<int>(strEncrypt.size()))
		return;

	if (&strText == &strResult)
		return;

	int nCodeCount(0);

	for (int nText(0); nText < static_cast<int>(strText.size()); nText++)
	{
		if (!(strText[nText] == ' ' || strText[nText] == '\t' || strText[nText] == '\n' || strText[nText] == '\r'))
		{
			if (nCodeCount >= static_cast<int>(strEncrypt.size()))
				nCodeCount = 0;

			strResult.push_back(strText[nText] ^ strEncrypt[nCodeCount]);

			nCodeCount++;
		}
		else
		{
			strResult.push_back(strText[nText]);
		}
	}
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
