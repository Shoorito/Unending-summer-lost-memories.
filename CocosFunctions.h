#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class C_Functions
{
public:
	// INFO 기존 cocos2d-x의 삭제 구문을 C++ 유형으로 변형한 것.
	// 매크로는 이상 발생의 원인을 제공하기 때문에 현재 지원되는 운영체제들은 함수에서 해결하도록 함.
	// 현재 지원되는 OS : WINDOWS
	// 목록, 리스트를 삭제할 때는 이 기능이 아닌 Array버전 함수를 사용하여야 한다.
	static void safeDelete(void* pDeletePointer);

	// INFO! 파일 암호화 설정/해제 함수입니다. 
	// PATCHED! 2019-12-27
	// 이제 "strEncrypt"의 길이에 상관 없이 암호화가 가능합니다.
	// 또한 이제 입력한 "strTarget"에 암호화가 적용됩니다.
	// @param "strTarget"	= "encrypt Target"
	// @param "strEncrypt"	= "encrypt Text"
	static void encryptText(std::string& strTarget, const std::string& strEncrypt);

	static void convertToString(const int nTarget, std::string& strResult);

	static int getDigits(const int nNumber);

	static int getCommaPosition(const int nNumber);

	static bool isComma(const int nPosition, const std::string& strTarget);

	static const bool isCheckSkip(const char& cWord);

	static void updateScoreLength(int nAdder, int nSize, int& nCommaCount, std::string& strTarget);

	static const int convertToInt(const std::string& strTarget);
private:
	C_Functions()  {}
	~C_Functions() {}
	C_Functions(C_Functions&)			  = delete;
	C_Functions operator=(C_Functions&) = delete;
};
