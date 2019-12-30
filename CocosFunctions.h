#pragma once
#include "cocos2d.h"

using namespace cocos2d;

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
