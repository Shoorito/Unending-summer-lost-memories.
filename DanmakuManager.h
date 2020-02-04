#pragma once
#include "cocos2d.h"
#include "EnumList.h"

using namespace cocos2d;

class C_Danmaku;

class C_DanmakuManager : public Node
{
public:
	static C_DanmakuManager* create();
	inline static C_DanmakuManager* getInstance() { return m_pInstance; }
public:
	inline const int& getCount(const E_USE_TYPE eType) const
	{
		return m_arCountList[static_cast<int>(eType)];
	}
	inline C_Danmaku* getHead(const E_USE_TYPE eType) const
	{
		return m_arHead[static_cast<int>(eType)];
	}
	inline C_Danmaku* getTail(const E_USE_TYPE eType) const
	{
		return m_arTail[static_cast<int>(eType)];
	}
	inline C_Danmaku* getCursor(const E_USE_TYPE& eType) const
	{
		return m_arCursor[static_cast<int>(eType)];
	}
public:
	void addDanmaku(C_Danmaku* pDanmaku);
	void pushDanmaku(C_Danmaku* pDanmaku);
	void changeDanmaku(C_Danmaku* pDanmaku);
public:
	C_Danmaku* popDanmaku(C_Danmaku* pDanmaku);
	C_Danmaku* popDanmaku(const E_USE_TYPE eType);
public:
	void moveCursor(const E_USE_TYPE eType, const int nMoveCount = 1);
	void initCursor(const E_USE_TYPE eType);
public:
	// �ش� �Լ��� ���� Ŀ���� ��ġ�� ������(ź��)�� "Rect"������ �����մϴ�.
	// �߰� ���� ������ �������� ���ѵ� ���۷��� ������ ���·� ���� �޽��ϴ�.
	// ���������� �ٸ� �������� ���� �����ϰ� ���� ��� "moveCursor"����� �̿��ϼž� �մϴ�.
	void changeDanmakuRect(const Rect& recDanmaku, const E_USE_TYPE eType);
public:
	void allDisabledDanmaku();
	void allPauseDanmaku();
	void allResumeDanmaku();
private:
	bool init() override;
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