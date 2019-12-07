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
	// WARNING! ��ȣŰ�� �ݵ�� ��ȣȭ ��󺸴� ���ų� �����ϸ�, �� �� ��ȣȭ�� �ؽ�Ʈ�� �ݵ�� ��ȣȭ �� Ű�� �����ؾ� �մϴ�.
	// WARNING! ���� ����� ���� "string"�� "clear"�����̾�� �մϴ�.
	// @param "strText" = "encrypt Target"
	// @param "strEncrypt" = "encrypt Text"
	// @param "strResult" = "result save target"
	static void encryptText(const std::string& strText, const std::string& strEncrypt, std::string& strResult);
private:
	C_Functions()  {}
	~C_Functions() {}
	C_Functions(C_Functions&)			  = delete;
	C_Functions operator=(C_Functions&) = delete;
};
