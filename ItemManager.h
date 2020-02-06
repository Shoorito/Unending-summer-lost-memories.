#pragma once
#include "cocos2d.h"
#include "EnumList.h"

using namespace cocos2d;

class C_Item;

class C_ItemManager : public Node
{
public:
	// INFO : "ItemManager" ��������.
	// @return = m_pInstance(singleton Type)
	static C_ItemManager* create();

	// INFO : "DanmakuManager" ��������.
	// @return = m_pInstance(singleton Type)
	inline static C_ItemManager* getInstance() { return m_pInstance; }
public:
	// INFO : �Է��� ��� Ÿ�Կ� ���ϴ� �������� ������ ��ȯ�մϴ�.
	// @param  = eType >> "FIND_TYPE"
	// @return = m_arCountList[TYPE] >> "FIND_TYPE_COUNT"
	inline const int& getCount(const E_USE_TYPE& eType) const
	{
		return m_arCountList[static_cast<int>(eType)];
	}

	// INFO : �Է��� ��� Ÿ�Կ� ���ϴ� ������ ����Ʈ�� "Head"�� ��ȯ�մϴ�.
	// @param  = eType >> "FIND_TYPE"
	// @return = m_arHead[TYPE] >> "FIND_TYPE_HEAD"
	inline C_Item* getHead(const E_USE_TYPE& eType) const
	{
		return m_arHead[static_cast<int>(eType)];
	}

	// INFO : �Է��� ��� Ÿ�Կ� ���ϴ� ������ ����Ʈ�� "Tail"�� ��ȯ�մϴ�.
	// @param  = eType >> "FIND_TYPE"
	// @return = m_arTail[TYPE] >> "FIND_TYPE_TAIL"
	inline C_Item* getTail(const E_USE_TYPE& eType) const
	{
		return m_arTail[static_cast<int>(eType)];
	}

	// INFO : �Է��� ��� Ÿ�Կ� ���ϴ� ������ ����Ʈ�� "Cursor"�� ��ȯ�մϴ�.
	// @param  = eType >> "FIND_TYPE"
	// @return = m_arCursor[TYPE] >> "FIND_TYPE_CURSOR"
	inline C_Item* getCursor(const E_USE_TYPE& eType) const
	{
		return m_arCursor[static_cast<int>(eType)];
	}
public:
	// INFO : �Է��� ������ ��ü�� �ش� ��ü�� ������ �ִ� "Ÿ��"�� �ش��ϴ� ����Ʈ�� �߰��ϰ� "addChild"�մϴ�.
	// �� ������ �Է� ��ü�� Ŭ������ "ManagerPool"�� "addChild"�ϱ� ������ "addChild"�� ������ ���� ���
	// "pushItem"�� �̿��Ͻñ� �ٶ��ϴ�.
	// @param  = pItem >> "ADD_TARGET"
	void addItem(C_Item* pItem);

	// INFO : �Է��� ������ ��ü�� �ش� ��ü�� ������ �ִ� "Ÿ��"�� �ش��ϴ� ����Ʈ�� �߰��մϴ�.
	// �� ������ �Է� ��ü�� �ش� Ÿ�� ����Ʈ�� �߰��� �մϴ�.
	// "ManagerPool"�� "addChild" �۾��� ���Ͻô� ��� "addDanmaku" �Լ��� �̿��Ͻñ� �ٶ��ϴ�.
	// @param  = pItem >> "PUSH_TARGET"
	void pushItem(C_Item* pItem);

	// INFO : �Է��� ������ ��ü�� �ش� ��ü�� ������ �ִ� "Ÿ��"�� �ݴ�Ǵ� ��� Ÿ�� ����Ʈ�� �̵���ŵ�ϴ�.
	// ���� ��� �Է��� ��ü�� "NOT_USED" Ÿ���� ������ �־����� ��ü ��� Ÿ���� "USED"�� �����ϰ�
	// "USED"����Ʈ�� �ش� ��ü�� �̵���ŵ�ϴ�.(���� �ִ� ����Ʈ������ ���ŵ˴ϴ�.)
	// @param  = pItem >> "CHANGE_TARGET"
	void changeItem(C_Item* pItem);
public:
	// INFO : �Է��� ������ ��ü�� �ش� ��ü�� ������ �ִ� Ÿ���� ����Ʈ���� �����ϴ�.
	// ��ü�� ������ �ִ� Ÿ���� ������ ������, ���������� �۵��ϴ� ���� Ȯ���ϱ� ���� �ش� ��ü�� ��ȯ�մϴ�.
	// @param  = pItem >> "POP_TARGET"
	// @return = @param >> "INPUT_TARGET"
	C_Item* popItem(C_Item* pItem);

	// INFO : �Է��� Ÿ���� ����Ʈ���� ���� ���߿� ���� ��ü�� �����ϴ�.
	// ��ü�� ������ �ִ� Ÿ���� ������ ������, �ش� ��ü�� ��ȯ�մϴ�.
	// @param  = eType			>> "POP_TYPE"
	// @return = m_arTail[TYPE] >> "INPUT_TYPE_TAIL"
	C_Item* popItem(const E_USE_TYPE eType);
public:
	// INFO : �Է��� Ÿ���� ����Ʈ�� ��ġ�� Ŀ���� ��ġ�� �Է��� ��ġ ��ŭ �̵���ŵ�ϴ�.
	// @param = eType		>> "CURSOR_TYPE"
	// @param = nMoveCount	>> "MOVE_COUNT"
	// @default >> nMoveCount >> 1
	void moveCursor(const E_USE_TYPE eType, const int nMoveCount = 1);

	// INFO : �Է��� Ÿ���� ����Ʈ�� ��ġ�� Ŀ���� ��ġ�� �ش� ����Ʈ�� "Head"�� �����մϴ�.
	// @param = eType >> "CURSOR_TYPE"
	void initCursor(const E_USE_TYPE eType);
public:
	// INFO : ��� ��� ���� �������� ��Ȱ��ȭ ��ŵ�ϴ�.
	// �ش� �������� ��Ȱ��ȭ ��Ų �����۵��� ��� "NOT_USED" ����Ʈ�� �̵��ϸ�
	// �ٽ� Ȱ��ȭ�� �ϰ� "USE" ����Ʈ�� �־��־�� �մϴ�.
	void allDisabledItem();

	// INFO : ��� ��� ���� �������� �Ͻ����� ��ŵ�ϴ�.
	// �ش� �������� �Ͻ����� ��Ų �����۵��� Ŭ���� �� "allResumeItem"�Լ��� ���� ��Ű�� ������ �ٽ�
	// �۵� �ϰ� �� �� �� �ֽ��ϴ�.
	void allPauseItem();

	// INFO : ��� ������� �Ͻ����� �� �������� �ٽ� �۵��ϰ� �մϴ�.
	// "DisabledItem"�� ��Ȱ��ȭ �� �����ۿ��� ����ص� ȿ���� ���� �� �����ϴ�.
	// �ش� ������ "allDisabledItem"�� ������ ������ �ֽñ� �ٶ��ϴ�.
	void allResumeItem();
private:
	// INFO : "Node"�� "init" �Լ��� �������̵� �� �Լ��Դϴ�.
	// ���� �� ���� �� �����Դϴ�.
	bool init() override;

	// INFO : ���� ������� �ʴ� �����Դϴ�.
	void preset();
private:
	C_Item* m_arHead[static_cast<int>(E_USE_TYPE::E_MAX)]{};
	C_Item* m_arTail[static_cast<int>(E_USE_TYPE::E_MAX)]{};
	C_Item* m_arCursor[static_cast<int>(E_USE_TYPE::E_MAX)]{};
private:
	int m_arCountList[static_cast<int>(E_USE_TYPE::E_MAX)]{};
private:
	static C_ItemManager* m_pInstance;
private:
	C_ItemManager() {}
	virtual ~C_ItemManager() {}
	C_ItemManager(C_ItemManager&) = delete;
	C_ItemManager operator=(C_ItemManager&) = delete;
};