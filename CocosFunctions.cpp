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

	for (int nText(0); nText < static_cast<int>(strText.size()); nText++)
	{
		strResult.push_back(strText[nText] ^ strEncrypt[nText]);
	}
}
