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
	// 해당 함수는 현재 커서가 위치한 데이터(탄막)의 "Rect"정보를 변경합니다.
	// 추가 적인 생성을 막기위해 제한된 레퍼런스 데이터 형태로 값을 받습니다.
	// 마찬가지로 다른 데이터의 값을 변경하고 싶은 경우 "moveCursor"기능을 이용하셔야 합니다.
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