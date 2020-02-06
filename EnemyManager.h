#pragma once
#include "cocos2d.h"
#include "EnumList.h"

using namespace cocos2d;

class C_Enemy;

class C_EnemyManager : public Node
{
public:
	// INFO : "EnemyManager" ��������.
	// @return = m_pInstance(singleton Type)
	static C_EnemyManager* create();

	// INFO : "EnemyManager" ��������.
	// @return = m_pInstance(singleton Type)
	inline static C_EnemyManager* getInstance() { return m_pInstance; }
public:
	// INFO : �Է��� ��� Ÿ�Կ� ���ϴ� �� ��ü�� ������ ��ȯ�մϴ�.
	// @param  = eType >> "FIND_TYPE"
	// @return = m_arCountList[TYPE] >> "FIND_TYPE_COUNT"
	inline const int& getCount(const E_USE_TYPE& eType)
	{
		return m_arCountList[static_cast<int>(eType)];
	}

	// INFO : �Է��� ��� Ÿ�Կ� ���ϴ� �� ��ü ����Ʈ�� "Head"�� ��ȯ�մϴ�.
	// @param  = eType >> "FIND_TYPE"
	// @return = m_arHead[TYPE] >> "FIND_TYPE_HEAD"
	inline C_Enemy* getHead(const E_USE_TYPE& eType)
	{
		return m_arHead[static_cast<int>(eType)];
	}

	// INFO : �Է��� ��� Ÿ�Կ� ���ϴ� �� ��ü ����Ʈ�� "Tail"�� ��ȯ�մϴ�.
	// @param  = eType >> "FIND_TYPE"
	// @return = m_arTail[TYPE] >> "FIND_TYPE_TAIL"
	inline C_Enemy* getTail(const E_USE_TYPE& eType)
	{
		return m_arTail[static_cast<int>(eType)];
	}

	// INFO : �Է��� ��� Ÿ�Կ� ���ϴ� �� ��ü ����Ʈ�� "Cursor"�� ��ȯ�մϴ�.
	// @param  = eType >> "FIND_TYPE"
	// @return = m_arCursor[TYPE] >> "FIND_TYPE_CURSOR"
	inline C_Enemy* getCursor(const E_USE_TYPE& eType)
	{
		return m_arCursor[static_cast<int>(eType)];
	}
public:
	// INFO : �Է��� �� ��ü�� �Է��� "Ÿ��"�� �ش��ϴ� ����Ʈ�� �߰��ϰ� "addChild"�մϴ�.
	// �� ������ �Է� ��ü�� Ŭ������ "ManagerPool"�� "addChild"�ϱ� ������ "addChild"�� ������ ���� ���
	// "pushItem"�� �̿��Ͻñ� �ٶ��ϴ�.
	// @param  = pEnemy >> "ADD_TARGET"
	// @param  = eType  >> "ADD_TYPE"
	void addEnemy(C_Enemy* pEnemy, const E_USE_TYPE& eType);

	// INFO : �Է��� �� ��ü�� �Է��� "Ÿ��"�� �ش��ϴ� ����Ʈ�� �߰��մϴ�.
	// �� ������ �Է� ��ü�� �ش� Ÿ�� ����Ʈ�� �߰��� �մϴ�.
	// "ManagerPool"�� "addChild" �۾��� ���Ͻô� ��� "addEnemy" �Լ��� �̿��Ͻñ� �ٶ��ϴ�.
	// @param  = pEnemy >> "PUSH_TARGET"
	// @param  = eType  >> "PUSH_TYPE"
	void pushEnemy(C_Enemy* pEnemy, const E_USE_TYPE& eType);

	// INFO : �Է��� ������ ��ü�� �Է��� "Ÿ��"���� ��ü�մϴ�.
	// ���� ��� �Է��� ��ü�� "NOT_USED" Ÿ���� ������ �־����� ��ü ��� Ÿ���� "USED"�� �����ϰ�
	// "USED"����Ʈ�� �ش� ��ü�� �̵���ŵ�ϴ�.(���� �ִ� ����Ʈ������ ���ŵ˴ϴ�.)
	// @param  = pEnemy >> "CHANGE_TARGET"
	// @param  = eChangeType >> "CHANGE_TYPE"
	void changeEnemy(C_Enemy* pEnemy, const E_USE_TYPE& eChangeType);

	// INFO : �Է��� ������ ��ü�� �Է��� Ÿ���� ����Ʈ���� �����ϴ�.
	// ��ü�� ������ �ִ� Ÿ���� ������ ������, ���������� �۵��ϴ� ���� Ȯ���ϱ� ���� �ش� ��ü�� ��ȯ�մϴ�.
	// @param  = pEnemy >> "POP_TARGET"
	// @param  = eType  >> "TARGET_TYPE"
	// @return = pEnemy >> "INPUT_TARGET"
	void popEnemy(C_Enemy* pEnemy, const E_USE_TYPE& eType);
public:
	// INFO : ������ Ÿ���� �� ��ü���� ��Ȱ��ȭ ��ŵ�ϴ�.
	// �ش� ������� ��Ȱ��ȭ �� ��ɵ��� ������ �ٽ� ����Ʈ�� ����ؾ� �մϴ�.
	// @param = eType >> "DISABLED_ENEMY_TYPE"
	void disabledAllEnemy(const E_ENEMY_TYPE& eType);

	// INFO : ������ Ÿ���� �� ��ü���� �Ͻ����� ��ŵ�ϴ�.
	// �ش� �������� �Ͻ����� ��Ų ��ü���� Ŭ���� �� "resumeAllEnemy"�Լ��� ���� ��Ű�� ������ �ٽ�
	// �۵� �ϰ� �� �� �� �ֽ��ϴ�.
	void pauseAllEnemy(const E_ENEMY_TYPE& eType);

	// INFO : ������ Ÿ���� �Ͻ����� �� �� ��ü���� �ٽ� �۵��ϰ� �մϴ�.
	// "disabledAllEnemy"�� ��Ȱ��ȭ �� �����ۿ��� ����ص� ȿ���� ���� �� �����ϴ�.
	// �ش� ������ "disabledAllEnemy"�� ������ ������ �ֽñ� �ٶ��ϴ�.
	void resumeAllEnemy(const E_ENEMY_TYPE& eType);
public:
	// INFO : �Է��� ��ġ �������� ���� ����� ��ġ�� �ִ� �� ��ü�� ��ȯ�մϴ�.
	// @param  = vecCharacterPos >> "PIVOT_POSITION_TARGET"
	// @return = ImmediateEnemy  >> "IMMEDIATE_ENEMY_BY_INPUT_TARGET"
	C_Enemy* getImmediateEnemy(const Vec2& vecCharacterPos);
public:
	// INFO : �Է��� Ÿ���� ����Ʈ�� ��ġ�� Ŀ���� ��ġ�� �ش� ����Ʈ�� "Head"�� �����մϴ�.
	// @param = eType >> "CURSOR_TYPE"
	void initCursor(const E_USE_TYPE& eType);

	// INFO : �Է��� Ÿ���� ����Ʈ�� ��ġ�� Ŀ���� ��ġ�� �Է��� ��ġ ��ŭ �̵���ŵ�ϴ�.
	// @param = eType >> "CURSOR_TYPE"
	// @param = nMove >> "MOVE_COUNT"
	// @default >> nMove >> 1
	void moveCursor(const E_USE_TYPE& eType, const int nMove = 1);
private:
	// INFO : "Node"�� "init" �Լ��� �������̵� �� �Լ��Դϴ�.
	// ���� ������ �ʽ��ϴ�.
	bool init();

	// INFO : ���� ������ �ʽ��ϴ�.
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