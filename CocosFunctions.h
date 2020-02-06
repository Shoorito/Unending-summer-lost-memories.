#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class C_Enemy;

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

	// INFO : 입력한 정수 값을 천단위 콤마가 들어간 형태로 String 문자열로 반환합니다.
	// @param = "nTarget"	>> TARGET_NUMBER
	// @param = "strResult" >> RESULT_SAVOR
	static void convertToString(const int& nTarget, std::string& strResult);
	
	// INFO : 입력한 정수 값을 천단위 콤마가 들어간 형태로 String 문자열로 반환합니다.
	// 위 함수와 다르게 값을 복사하여 반환하는 것이 다릅니다.
	// @param  = "nTarget"	 >> TARGET_NUMBER
	// @return = "strResult" >> CONVERT_STRING
	static const std::string convertToString(const int& nTarget);

	// INFO : 입력한 정수의 자릿수를 반환합니다.
	// @param  = "nNumber" >> TARGET_NUMBER
	// @return = "nResult" >> DIGIT_COUNT
	static int getDigits(const int nNumber);

	// INFO : "g_arInitScore"에 지정되어 있는 자릿수에 따른 콤마 갯수를 반환합니다.
	// @param  = "nNumber"		>> TARGET_NUMBER
	// @return = "nCommaCount"	>> COMMA_COUNT
	static int getCommaPosition(const int nNumber);

	// INFO : " 입력한 문자열의 "POSITION"에 콤마가 위치하는가에 대한 여부를 반환합니다.
	// @param  = nPosition >> TEXT_ARRAY_NUMBER
	// @param  = strTarget >> TARGET_TEXT
	// @return = isComma   >> IS_COMMA
	static bool isComma(const int nPosition, const std::string& strTarget);

	// INFO : 입력한 문자가 읽지 않아도 되는 문자인지 구별합니다.
	// @param  = cWord  >> TARGET_WORD
	// @return = isSkip >> IS_SKIP
	static const bool isCheckSkip(const char& cWord);

	// INFO : "PlayerUI"에 사용되는 점수의 자릿수가 변경 될 경우 호출되는 함수입니다.
	// @param = nAdder		>> NEW_SIZE
	// @param = nSize		>> PREV_SIZE
	// @param = nCommaCount	>> COMMA_COUNT
	// @param = strTarget	>> RESULT_OUTPUT_TARGET
	static void updateScoreLength(int nAdder, int nSize, int& nCommaCount, std::string& strTarget);

	// INFO : 입력한 문자열을 정수로 변환합니다.
	// 천단위 콤마가 있어도 변환 가능합니다.
	// @param  = strTarget	>> STRING_TEXT
	// @result = nResult	>> CONVERT_RESULT
	static const int convertToInt(const std::string& strTarget);

	// INFO : 두개의 포인터 위치를 변경합니다.
	// @param = pSrc >> CHANGE_POINTER_01
	// @param = pDst >> CHANGE_POINTER_02
	static void swap(void* pSrc, void* pDst);

	// INFO : 시작 위치에서 끝 위치 까지의 조준 각도를 구합니다.
	// @param  = vecStartpos	>> START_POSITION
	// @param  = vecEndpos		>> END_POSITION
	// @return = fAimingAngle	>> AIMING_ANGLE 
	static const float getHomingAngle(const Vec2& vecStartpos, const Vec2& vecEndpos);

	// INFO : 입력한 적 타겟에게 아이템을 드롭 시킵니다.
	// @param = pTarget >> DROP_TARGET
	static void dropItem(C_Enemy * pTarget);

private:
	C_Functions()  {}
	~C_Functions() {}
	C_Functions(C_Functions&)			  = delete;
	C_Functions operator=(C_Functions&) = delete;
};
