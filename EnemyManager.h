#pragma once
#include "cocos2d.h"
#include "EnumList.h"

using namespace cocos2d;

class C_Enemy;

class C_EnemyManager : public Node
{
public:
	// INFO : "EnemyManager" 생성구문.
	// @return = m_pInstance(singleton Type)
	static C_EnemyManager* create();

	// INFO : "EnemyManager" 참조구문.
	// @return = m_pInstance(singleton Type)
	inline static C_EnemyManager* getInstance() { return m_pInstance; }
public:
	// INFO : 입력한 사용 타입에 속하는 적 개체의 개수를 반환합니다.
	// @param  = eType >> "FIND_TYPE"
	// @return = m_arCountList[TYPE] >> "FIND_TYPE_COUNT"
	inline const int& getCount(const E_USE_TYPE& eType)
	{
		return m_arCountList[static_cast<int>(eType)];
	}

	// INFO : 입력한 사용 타입에 속하는 적 개체 리스트의 "Head"를 반환합니다.
	// @param  = eType >> "FIND_TYPE"
	// @return = m_arHead[TYPE] >> "FIND_TYPE_HEAD"
	inline C_Enemy* getHead(const E_USE_TYPE& eType)
	{
		return m_arHead[static_cast<int>(eType)];
	}

	// INFO : 입력한 사용 타입에 속하는 적 개체 리스트의 "Tail"를 반환합니다.
	// @param  = eType >> "FIND_TYPE"
	// @return = m_arTail[TYPE] >> "FIND_TYPE_TAIL"
	inline C_Enemy* getTail(const E_USE_TYPE& eType)
	{
		return m_arTail[static_cast<int>(eType)];
	}

	// INFO : 입력한 사용 타입에 속하는 적 개체 리스트의 "Cursor"를 반환합니다.
	// @param  = eType >> "FIND_TYPE"
	// @return = m_arCursor[TYPE] >> "FIND_TYPE_CURSOR"
	inline C_Enemy* getCursor(const E_USE_TYPE& eType)
	{
		return m_arCursor[static_cast<int>(eType)];
	}
public:
	// INFO : 입력한 적 개체를 입력한 "타입"에 해당하는 리스트에 추가하고 "addChild"합니다.
	// 이 구문은 입력 개체를 클래스의 "ManagerPool"에 "addChild"하기 때문에 "addChild"를 원하지 않을 경우
	// "pushItem"를 이용하시기 바랍니다.
	// @param  = pEnemy >> "ADD_TARGET"
	// @param  = eType  >> "ADD_TYPE"
	void addEnemy(C_Enemy* pEnemy, const E_USE_TYPE& eType);

	// INFO : 입력한 적 개체를 입력한 "타입"에 해당하는 리스트에 추가합니다.
	// 이 구문은 입력 개체를 해당 타입 리스트에 추가만 합니다.
	// "ManagerPool"에 "addChild" 작업을 원하시는 경우 "addEnemy" 함수를 이용하시기 바랍니다.
	// @param  = pEnemy >> "PUSH_TARGET"
	// @param  = eType  >> "PUSH_TYPE"
	void pushEnemy(C_Enemy* pEnemy, const E_USE_TYPE& eType);

	// INFO : 입력한 아이템 개체를 입력한 "타입"으로 교체합니다.
	// 예를 들어 입력한 개체가 "NOT_USED" 타입을 가지고 있었으면 개체 사용 타입을 "USED"로 변경하고
	// "USED"리스트로 해당 개체를 이동시킵니다.(원래 있던 리스트에서는 제거됩니다.)
	// @param  = pEnemy >> "CHANGE_TARGET"
	// @param  = eChangeType >> "CHANGE_TYPE"
	void changeEnemy(C_Enemy* pEnemy, const E_USE_TYPE& eChangeType);

	// INFO : 입력한 아이템 개체를 입력한 타입의 리스트에서 빼냅니다.
	// 개체가 가지고 있던 타입은 변하지 않으며, 정상적으로 작동하는 것을 확인하기 위해 해당 개체를 반환합니다.
	// @param  = pEnemy >> "POP_TARGET"
	// @param  = eType  >> "TARGET_TYPE"
	// @return = pEnemy >> "INPUT_TARGET"
	void popEnemy(C_Enemy* pEnemy, const E_USE_TYPE& eType);
public:
	// INFO : 지정한 타입의 적 개체들을 비활성화 시킵니다.
	// 해당 기능으로 비활성화 된 기능들은 일일히 다시 리스트에 등록해야 합니다.
	// @param = eType >> "DISABLED_ENEMY_TYPE"
	void disabledAllEnemy(const E_ENEMY_TYPE& eType);

	// INFO : 지정한 타입의 적 개체들을 일시정지 시킵니다.
	// 해당 구문으로 일시정지 시킨 개체들은 클래스 내 "resumeAllEnemy"함수를 실행 시키는 것으로 다시
	// 작동 하게 끔 할 수 있습니다.
	void pauseAllEnemy(const E_ENEMY_TYPE& eType);

	// INFO : 지정한 타입의 일시정지 된 적 개체들을 다시 작동하게 합니다.
	// "disabledAllEnemy"로 비활성화 된 아이템에는 사용해도 효과를 얻을 수 없습니다.
	// 해당 사항은 "disabledAllEnemy"의 설명을 참조해 주시기 바랍니다.
	void resumeAllEnemy(const E_ENEMY_TYPE& eType);
public:
	// INFO : 입력한 위치 기준으로 가장 가까운 위치에 있는 적 개체를 반환합니다.
	// @param  = vecCharacterPos >> "PIVOT_POSITION_TARGET"
	// @return = ImmediateEnemy  >> "IMMEDIATE_ENEMY_BY_INPUT_TARGET"
	C_Enemy* getImmediateEnemy(const Vec2& vecCharacterPos);
public:
	// INFO : 입력한 타입의 리스트에 위치한 커서의 위치를 해당 리스트의 "Head"로 변경합니다.
	// @param = eType >> "CURSOR_TYPE"
	void initCursor(const E_USE_TYPE& eType);

	// INFO : 입력한 타입의 리스트에 위치한 커서의 위치를 입력한 수치 만큼 이동시킵니다.
	// @param = eType >> "CURSOR_TYPE"
	// @param = nMove >> "MOVE_COUNT"
	// @default >> nMove >> 1
	void moveCursor(const E_USE_TYPE& eType, const int nMove = 1);
private:
	// INFO : "Node"의 "init" 함수를 오버라이드 한 함수입니다.
	// 아직 사용되지 않습니다.
	bool init();

	// INFO : 아직 사용되지 않습니다.
	void preset();
private:
	C_Enemy* m_arHead[static_cast<int>(E_USE_TYPE::E_MAX)]{};
	C_Enemy* m_arTail[static_cast<int>(E_USE_TYPE::E_MAX)]{};
	C_Enemy* m_arCursor[static_cast<int>(E_USE_TYPE::E_MAX)]{};
private:
	int m_arCountList[static_cast<int>(E_USE_TYPE::E_MAX)]{};
public:
	static C_EnemyManager* m_pInstance;
private:
	C_EnemyManager() {}
	~C_EnemyManager() {}
	C_EnemyManager(C_EnemyManager&) = delete;
	C_EnemyManager operator=(C_EnemyManager&) = delete;
};