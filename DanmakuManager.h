#pragma once
#include "cocos2d.h"
#include "EnumList.h"

using namespace cocos2d;

class C_Danmaku;

class C_DanmakuManager : public Node
{
public:
	// INFO : "DanmakuManager" 생성구문.
	// @return = m_pInstance(singleton Type)
	static C_DanmakuManager* create();

	// INFO : "DanmakuManager" 참조구문.
	// @return = m_pInstance(singleton Type)
	inline static C_DanmakuManager* getInstance() { return m_pInstance; }
public:
	// INFO : 입력한 사용 타입에 속하는 탄막의 개수를 반환합니다.
	// @param  = eType >> "FIND_TYPE"
	// @return = m_arCountList[TYPE] >> "FIND_TYPE_COUNT"
	inline const int& getCount(const E_USE_TYPE eType) const
	{
		return m_arCountList[static_cast<int>(eType)];
	}

	// INFO : 입력한 사용 타입에 속하는 탄막 리스트의 "Head"를 반환합니다.
	// @param  = eType >> "FIND_TYPE"
	// @return = m_arHead[TYPE] >> "FIND_TYPE_HEAD"
	inline C_Danmaku* getHead(const E_USE_TYPE eType) const
	{
		return m_arHead[static_cast<int>(eType)];
	}

	// INFO : 입력한 사용 타입에 속하는 탄막 리스트의 "Tail"를 반환합니다.
	// @param  = eType >> "FIND_TYPE"
	// @return = m_arTail[TYPE] >> "FIND_TYPE_TAIL"
	inline C_Danmaku* getTail(const E_USE_TYPE eType) const
	{
		return m_arTail[static_cast<int>(eType)];
	}

	// INFO : 입력한 사용 타입에 속하는 탄막 리스트의 "Cursor"를 반환합니다.
	// @param  = eType >> "FIND_TYPE"
	// @return = m_arCursor[TYPE] >> "FIND_TYPE_CURSOR"
	inline C_Danmaku* getCursor(const E_USE_TYPE& eType) const
	{
		return m_arCursor[static_cast<int>(eType)];
	}
public:
	// INFO : 입력한 탄막 개체를 해당 개체가 가지고 있는 "타입"에 해당하는 리스트에 추가하고 "addChild"합니다.
	// 이 구문은 입력 개체를 클래스의 "ManagerPool"에 "addChild"하기 때문에 "addChild"를 원하지 않을 경우
	// "pushDanmaku"를 이용하시기 바랍니다.
	// @param  = pDanmaku >> "ADD_TARGET"
	void addDanmaku(C_Danmaku* pDanmaku);

	// INFO : 입력한 탄막 개체를 해당 개체가 가지고 있는 "타입"에 해당하는 리스트에 추가합니다.
	// 이 구문은 입력 개체를 해당 타입 리스트에 추가만 합니다.
	// "ManagerPool"에 "addChild" 작업을 원하시는 경우 "addDanmaku" 함수를 이용하시기 바랍니다.
	// @param  = pDanmaku >> "PUSH_TARGET"
	void pushDanmaku(C_Danmaku* pDanmaku);

	// INFO : 입력한 탄막 개체를 해당 개체가 가지고 있는 "타입"에 반대되는 사용 타입 리스트로 이동시킵니다.
	// 예를 들어 입력한 개체가 "NOT_USED" 타입을 가지고 있었으면 개체 사용 타입을 "USED"로 변경하고
	// "USED"리스트로 해당 개체를 이동시킵니다.(원래 있던 리스트에서는 제거됩니다.)
	// @param  = pDanmaku >> "CHANGE_TARGET"
	void changeDanmaku(C_Danmaku* pDanmaku);
public:
	// INFO : 입력한 탄막 개체를 해당 개체가 가지고 있는 타입의 리스트에서 빼냅니다.
	// 개체가 가지고 있던 타입은 변하지 않으며, 정상적으로 작동하는 것을 확인하기 위해 해당 개체를 반환합니다.
	// @param  = pDanmaku >> "POP_TARGET"
	// @return = @param >> "INPUT_TARGET"
	C_Danmaku* popDanmaku(C_Danmaku* pDanmaku);

	// INFO : 입력한 타입의 리스트에서 가장 나중에 들어온 개체를 빼냅니다.
	// 개체가 가지고 있던 타입은 변하지 않으며, 해당 개체를 반환합니다.
	// @param  = eType			>> "POP_TYPE"
	// @return = m_arTail[TYPE] >> "INPUT_TYPE_TAIL"
	C_Danmaku* popDanmaku(const E_USE_TYPE eType);
public:
	// INFO : 입력한 타입의 리스트에 위치한 커서의 위치를 입력한 수치 만큼 이동시킵니다.
	// @param = eType		>> "CURSOR_TYPE"
	// @param = nMoveCount	>> "MOVE_COUNT"
	// @default >> nMoveCount >> 1
	void moveCursor(const E_USE_TYPE eType, const int nMoveCount = 1);

	// INFO : 입력한 타입의 리스트에 위치한 커서의 위치를 해당 리스트의 "Head"로 변경합니다.
	// @param = eType >> "CURSOR_TYPE"
	void initCursor(const E_USE_TYPE eType);
public:
	// INFO : 해당 함수는 현재 커서가 위치한 데이터(탄막)의 "Rect"정보를 변경합니다.
	// 추가 적인 생성을 막기위해 제한된 레퍼런스 데이터 형태로 값을 받습니다.
	// 마찬가지로 다른 데이터의 값을 변경하고 싶은 경우 "moveCursor"기능을 이용하셔야 합니다.
	// @param = recDanmaku	>> "DANMAKU_RECT_SIZE"
	// @param = eType		>> "DANMAKU_TYPE"
	void changeDanmakuRect(const Rect& recDanmaku, const E_USE_TYPE eType);
public:
	// INFO : 모든 사용 중인 탄막을 비활성화 시킵니다.
	// 해당 구문으로 비활성화 시킨 탄막들은 모두 "NOT_USED" 리스트로 이동하며
	// 다시 활성화를 하고 "USE" 리스트에 넣어주어야 합니다.
	void allDisabledDanmaku();

	// INFO : 모든 사용 중인 탄막을 일시정지 시킵니다.
	// 해당 구문으로 일시정지 시킨 탄막은 클래스 내 "allResumeDanmaku"함수를 실행 시키는 것으로 다시
	// 작동 하게 끔 할 수 있습니다.
	void allPauseDanmaku();

	// INFO : 모든 사용중인 일시정지 된 탄막을 다시 작동하게 합니다.
	// "DisabledDanmaku"로 비활성화 된 탄막에는 사용해도 효과를 얻을 수 없습니다.
	// 해당 사항은 "allDisabledDanmaku"의 설명을 참조해 주시기 바랍니다.
	void allResumeDanmaku();
private:
	// INFO : "Node"의 "init" 함수를 오버라이드 한 함수입니다.
	// 형식 상 설계 된 구문입니다.
	bool init() override;

	// INFO : 아직 사용하지 않는 구문입니다.
	void preset();
private:
	C_Danmaku* m_arHead[static_cast<int>(E_USE_TYPE::E_MAX)]{};
	C_Danmaku* m_arTail[static_cast<int>(E_USE_TYPE::E_MAX)]{};
	C_Danmaku* m_arCursor[static_cast<int>(E_USE_TYPE::E_MAX)]{};
private:
	int m_arCountList[static_cast<int>(E_USE_TYPE::E_MAX)]{};
private:
	static C_DanmakuManager* m_pInstance;
private:
	C_DanmakuManager() {}
	virtual ~C_DanmakuManager() {}
	C_DanmakuManager(C_DanmakuManager&) = delete;
	C_DanmakuManager operator=(C_DanmakuManager&) = delete;
};