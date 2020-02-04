#pragma once
#include "cocos2d.h"
#include "EnumList.h"

using namespace cocos2d;

class C_Item;

class C_ItemManager : public Node
{
public:
	static C_ItemManager* create();
	inline static C_ItemManager* getInstance() { return m_pInstance; }
public:
	inline const int& getCount(const E_USE_TYPE& eType) const
	{
		return m_arCountList[static_cast<int>(eType)];
	}
	inline C_Item* getHead(const E_USE_TYPE& eType) const
	{
		return m_arHead[static_cast<int>(eType)];
	}
	inline C_Item* getTail(const E_USE_TYPE& eType) const
	{
		return m_arTail[static_cast<int>(eType)];
	}
	inline C_Item* getCursor(const E_USE_TYPE& eType) const
	{
		return m_arCursor[static_cast<int>(eType)];
	}
public:
	void addItem(C_Item* pItem);
	void pushItem(C_Item* pItem);
	void changeItem(C_Item* pItem);
public:
	C_Item* popItem(C_Item* pItem);
	C_Item* popItem(const E_USE_TYPE eType);
public:
	void moveCursor(const E_USE_TYPE eType, const int nMoveCount = 1);
	void initCursor(const E_USE_TYPE eType);
public:
	void allDisabledItem();
	void allPauseItem();
	void allResumeItem();
private:
	bool init() override;
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