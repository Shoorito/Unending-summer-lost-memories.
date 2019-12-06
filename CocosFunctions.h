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
private:
	C_Functions()  {}
	~C_Functions() {}
	C_Functions(C_Functions&)			  = delete;
	C_Functions operator=(C_Functions&) = delete;
};
