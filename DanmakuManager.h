#pragma once
#include "cocos2d.h"
#include "EnumList.h"

using namespace cocos2d;

class C_Danmaku;

class C_DanmakuManager : public Node
{
public:
	// INFO : "DanmakuManager" ��������.
	// @return = m_pInstance(singleton Type)
	static C_DanmakuManager* create();

	// INFO : "DanmakuManager" ��������.
	// @return = m_pInstance(singleton Type)
	inline static C_DanmakuManager* getInstance() { return m_pInstance; }
public:
	// INFO : �Է��� ��� Ÿ�Կ� ���ϴ� ź���� ������ ��ȯ�մϴ�.
	// @param  = eType >> "FIND_TYPE"
	// @return = m_arCountList[TYPE] >> "FIND_TYPE_COUNT"
	inline const int& getCount(const E_USE_TYPE eType) const
	{
		return m_arCountList[static_cast<int>(eType)];
	}

	// INFO : �Է��� ��� Ÿ�Կ� ���ϴ� ź�� ����Ʈ�� "Head"�� ��ȯ�մϴ�.
	// @param  = eType >> "FIND_TYPE"
	// @return = m_arHead[TYPE] >> "FIND_TYPE_HEAD"
	inline C_Danmaku* getHead(const E_USE_TYPE eType) const
	{
		return m_arHead[static_cast<int>(eType)];
	}

	// INFO : �Է��� ��� Ÿ�Կ� ���ϴ� ź�� ����Ʈ�� "Tail"�� ��ȯ�մϴ�.
	// @param  = eType >> "FIND_TYPE"
	// @return = m_arTail[TYPE] >> "FIND_TYPE_TAIL"
	inline C_Danmaku* getTail(const E_USE_TYPE eType) const
	{
		return m_arTail[static_cast<int>(eType)];
	}

	// INFO : �Է��� ��� Ÿ�Կ� ���ϴ� ź�� ����Ʈ�� "Cursor"�� ��ȯ�մϴ�.
	// @param  = eType >> "FIND_TYPE"
	// @return = m_arCursor[TYPE] >> "FIND_TYPE_CURSOR"
	inline C_Danmaku* getCursor(const E_USE_TYPE& eType) const
	{
		return m_arCursor[static_cast<int>(eType)];
	}
public:
	// INFO : �Է��� ź�� ��ü�� �ش� ��ü�� ������ �ִ� "Ÿ��"�� �ش��ϴ� ����Ʈ�� �߰��ϰ� "addChild"�մϴ�.
	// �� ������ �Է� ��ü�� Ŭ������ "ManagerPool"�� "addChild"�ϱ� ������ "addChild"�� ������ ���� ���
	// "pushDanmaku"�� �̿��Ͻñ� �ٶ��ϴ�.
	// @param  = pDanmaku >> "ADD_TARGET"
	void addDanmaku(C_Danmaku* pDanmaku);

	// INFO : �Է��� ź�� ��ü�� �ش� ��ü�� ������ �ִ� "Ÿ��"�� �ش��ϴ� ����Ʈ�� �߰��մϴ�.
	// �� ������ �Է� ��ü�� �ش� Ÿ�� ����Ʈ�� �߰��� �մϴ�.
	// "ManagerPool"�� "addChild" �۾��� ���Ͻô� ��� "addDanmaku" �Լ��� �̿��Ͻñ� �ٶ��ϴ�.
	// @param  = pDanmaku >> "PUSH_TARGET"
	void pushDanmaku(C_Danmaku* pDanmaku);

	// INFO : �Է��� ź�� ��ü�� �ش� ��ü�� ������ �ִ� "Ÿ��"�� �ݴ�Ǵ� ��� Ÿ�� ����Ʈ�� �̵���ŵ�ϴ�.
	// ���� ��� �Է��� ��ü�� "NOT_USED" Ÿ���� ������ �־����� ��ü ��� Ÿ���� "USED"�� �����ϰ�
	// "USED"����Ʈ�� �ش� ��ü�� �̵���ŵ�ϴ�.(���� �ִ� ����Ʈ������ ���ŵ˴ϴ�.)
	// @param  = pDanmaku >> "CHANGE_TARGET"
	void changeDanmaku(C_Danmaku* pDanmaku);
public:
	// INFO : �Է��� ź�� ��ü�� �ش� ��ü�� ������ �ִ� Ÿ���� ����Ʈ���� �����ϴ�.
	// ��ü�� ������ �ִ� Ÿ���� ������ ������, ���������� �۵��ϴ� ���� Ȯ���ϱ� ���� �ش� ��ü�� ��ȯ�մϴ�.
	// @param  = pDanmaku >> "POP_TARGET"
	// @return = @param >> "INPUT_TARGET"
	C_Danmaku* popDanmaku(C_Danmaku* pDanmaku);

	// INFO : �Է��� Ÿ���� ����Ʈ���� ���� ���߿� ���� ��ü�� �����ϴ�.
	// ��ü�� ������ �ִ� Ÿ���� ������ ������, �ش� ��ü�� ��ȯ�մϴ�.
	// @param  = eType			>> "POP_TYPE"
	// @return = m_arTail[TYPE] >> "INPUT_TYPE_TAIL"
	C_Danmaku* popDanmaku(const E_USE_TYPE eType);
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
	// INFO : �ش� �Լ��� ���� Ŀ���� ��ġ�� ������(ź��)�� "Rect"������ �����մϴ�.
	// �߰� ���� ������ �������� ���ѵ� ���۷��� ������ ���·� ���� �޽��ϴ�.
	// ���������� �ٸ� �������� ���� �����ϰ� ���� ��� "moveCursor"����� �̿��ϼž� �մϴ�.
	// @param = recDanmaku	>> "DANMAKU_RECT_SIZE"
	// @param = eType		>> "DANMAKU_TYPE"
	void changeDanmakuRect(const Rect& recDanmaku, const E_USE_TYPE eType);
public:
	// INFO : ��� ��� ���� ź���� ��Ȱ��ȭ ��ŵ�ϴ�.
	// �ش� �������� ��Ȱ��ȭ ��Ų ź������ ��� "NOT_USED" ����Ʈ�� �̵��ϸ�
	// �ٽ� Ȱ��ȭ�� �ϰ� "USE" ����Ʈ�� �־��־�� �մϴ�.
	void allDisabledDanmaku();

	// INFO : ��� ��� ���� ź���� �Ͻ����� ��ŵ�ϴ�.
	// �ش� �������� �Ͻ����� ��Ų ź���� Ŭ���� �� "allResumeDanmaku"�Լ��� ���� ��Ű�� ������ �ٽ�
	// �۵� �ϰ� �� �� �� �ֽ��ϴ�.
	void allPauseDanmaku();

	// INFO : ��� ������� �Ͻ����� �� ź���� �ٽ� �۵��ϰ� �մϴ�.
	// "DisabledDanmaku"�� ��Ȱ��ȭ �� ź������ ����ص� ȿ���� ���� �� �����ϴ�.
	// �ش� ������ "allDisabledDanmaku"�� ������ ������ �ֽñ� �ٶ��ϴ�.
	void allResumeDanmaku();
private:
	// INFO : "Node"�� "init" �Լ��� �������̵� �� �Լ��Դϴ�.
	// ���� �� ���� �� �����Դϴ�.
	bool init() override;

	// INFO : ���� ������� �ʴ� �����Դϴ�.
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