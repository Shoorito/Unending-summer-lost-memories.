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
	// WARNING! 암호키는 반드시 암호화 대상보다 같거나 길어야하며, 한 번 암호화된 텍스트는 반드시 암호화 한 키로 해제해야 합니다.
	// WARNING! 또한 결과를 넣을 "string"은 "clear"상태이어야 합니다.
	// @param "strText" = "encrypt Target"
	// @param "strEncrypt" = "encrypt Text"
	// @param "strResult" = "result save target"
	static void encryptText(const std::string& strText, const std::string& strEncrypt, std::string& strResult);

	static int getDigits(const int nNumber);

	static int getCommaPosition(const int nNumber);

	static bool isComma(const int nPosition, const std::string& strTarget);

	static void updateScoreLength(int nAdder, int nSize, int& nCommaCount, std::string& strTarget);
private:
	C_Functions()  {}
	~C_Functions() {}
	C_Functions(C_Functions&)			  = delete;
	C_Functions operator=(C_Functions&) = delete;
};
