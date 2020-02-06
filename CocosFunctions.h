#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class C_Enemy;

class C_Functions
{
public:
	// INFO ���� cocos2d-x�� ���� ������ C++ �������� ������ ��.
	// ��ũ�δ� �̻� �߻��� ������ �����ϱ� ������ ���� �����Ǵ� �ü������ �Լ����� �ذ��ϵ��� ��.
	// ���� �����Ǵ� OS : WINDOWS
	// ���, ����Ʈ�� ������ ���� �� ����� �ƴ� Array���� �Լ��� ����Ͽ��� �Ѵ�.
	static void safeDelete(void* pDeletePointer);

	// INFO! ���� ��ȣȭ ����/���� �Լ��Դϴ�. 
	// PATCHED! 2019-12-27
	// ���� "strEncrypt"�� ���̿� ��� ���� ��ȣȭ�� �����մϴ�.
	// ���� ���� �Է��� "strTarget"�� ��ȣȭ�� ����˴ϴ�.
	// @param "strTarget"	= "encrypt Target"
	// @param "strEncrypt"	= "encrypt Text"
	static void encryptText(std::string& strTarget, const std::string& strEncrypt);

	// INFO : �Է��� ���� ���� õ���� �޸��� �� ���·� String ���ڿ��� ��ȯ�մϴ�.
	// @param = "nTarget"	>> TARGET_NUMBER
	// @param = "strResult" >> RESULT_SAVOR
	static void convertToString(const int& nTarget, std::string& strResult);
	
	// INFO : �Է��� ���� ���� õ���� �޸��� �� ���·� String ���ڿ��� ��ȯ�մϴ�.
	// �� �Լ��� �ٸ��� ���� �����Ͽ� ��ȯ�ϴ� ���� �ٸ��ϴ�.
	// @param  = "nTarget"	 >> TARGET_NUMBER
	// @return = "strResult" >> CONVERT_STRING
	static const std::string convertToString(const int& nTarget);

	// INFO : �Է��� ������ �ڸ����� ��ȯ�մϴ�.
	// @param  = "nNumber" >> TARGET_NUMBER
	// @return = "nResult" >> DIGIT_COUNT
	static int getDigits(const int nNumber);

	// INFO : "g_arInitScore"�� �����Ǿ� �ִ� �ڸ����� ���� �޸� ������ ��ȯ�մϴ�.
	// @param  = "nNumber"		>> TARGET_NUMBER
	// @return = "nCommaCount"	>> COMMA_COUNT
	static int getCommaPosition(const int nNumber);

	// INFO : " �Է��� ���ڿ��� "POSITION"�� �޸��� ��ġ�ϴ°��� ���� ���θ� ��ȯ�մϴ�.
	// @param  = nPosition >> TEXT_ARRAY_NUMBER
	// @param  = strTarget >> TARGET_TEXT
	// @return = isComma   >> IS_COMMA
	static bool isComma(const int nPosition, const std::string& strTarget);

	// INFO : �Է��� ���ڰ� ���� �ʾƵ� �Ǵ� �������� �����մϴ�.
	// @param  = cWord  >> TARGET_WORD
	// @return = isSkip >> IS_SKIP
	static const bool isCheckSkip(const char& cWord);

	// INFO : "PlayerUI"�� ���Ǵ� ������ �ڸ����� ���� �� ��� ȣ��Ǵ� �Լ��Դϴ�.
	// @param = nAdder		>> NEW_SIZE
	// @param = nSize		>> PREV_SIZE
	// @param = nCommaCount	>> COMMA_COUNT
	// @param = strTarget	>> RESULT_OUTPUT_TARGET
	static void updateScoreLength(int nAdder, int nSize, int& nCommaCount, std::string& strTarget);

	// INFO : �Է��� ���ڿ��� ������ ��ȯ�մϴ�.
	// õ���� �޸��� �־ ��ȯ �����մϴ�.
	// @param  = strTarget	>> STRING_TEXT
	// @result = nResult	>> CONVERT_RESULT
	static const int convertToInt(const std::string& strTarget);

	// INFO : �ΰ��� ������ ��ġ�� �����մϴ�.
	// @param = pSrc >> CHANGE_POINTER_01
	// @param = pDst >> CHANGE_POINTER_02
	static void swap(void* pSrc, void* pDst);

	// INFO : ���� ��ġ���� �� ��ġ ������ ���� ������ ���մϴ�.
	// @param  = vecStartpos	>> START_POSITION
	// @param  = vecEndpos		>> END_POSITION
	// @return = fAimingAngle	>> AIMING_ANGLE 
	static const float getHomingAngle(const Vec2& vecStartpos, const Vec2& vecEndpos);

	// INFO : �Է��� �� Ÿ�ٿ��� �������� ��� ��ŵ�ϴ�.
	// @param = pTarget >> DROP_TARGET
	static void dropItem(C_Enemy * pTarget);

private:
	C_Functions()  {}
	~C_Functions() {}
	C_Functions(C_Functions&)			  = delete;
	C_Functions operator=(C_Functions&) = delete;
};
