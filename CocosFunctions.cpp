#include "CocosFunctions.h"
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