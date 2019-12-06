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
private:
	C_Functions()  {}
	~C_Functions() {}
	C_Functions(C_Functions&)			  = delete;
	C_Functions operator=(C_Functions&) = delete;
};
