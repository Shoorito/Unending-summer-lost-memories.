#pragma once
#include "cocos2d.h"
#include "EnumList.h"

using namespace cocos2d;

const float g_fItemWidth  = 32.0f;
const float g_fItemHeight = 32.0f;

const int g_arItemValueMin[2] = { 1, 95000 };
const int g_arItemValueMax[2] = { 5, 120000 };

class C_Item : public Sprite
{
public:
	static C_Item* create();
public:
	inline C_Item* getPrev() const
	{
		return m_pPrev;
	}
	inline C_Item* getNext() const
	{
		return m_pNext;
	}
	inline const E_ITEM_TYPE& getType() const
	{
		return m_eItemType;
	}
	inline const E_USE_TYPE& getUseType() const
	{
		return m_eUseType;
	}
public:
	inline const bool& isEnabled() const
	{
		return m_isEnabled;
	}
	inline const int& getAddValue()
	{
		return m_nAddValue;
	}
public:
	inline void setPrev(C_Item* pDanmaku)
	{
		m_pPrev = pDanmaku;
	}
	inline void setNext(C_Item* pDanmaku)
	{
		m_pNext = pDanmaku;
	}
	inline void setType(const E_ITEM_TYPE& eType)
	{
		m_eItemType = eType;
	}
	inline void setUseType(const E_USE_TYPE& eType)
	{
		m_eUseType = eType;
	}
public:
	void setAddValue(const int nValue);
public:
	void setEnabled(const bool isEnabled);
public:
	void setTextureWithRect(const std::string& strFile, const Rect& recTarget);
public:
	void startShowAct();
private:
	bool init() override;
	void preset();
	void presetStartAct();
	void move();
	void unDelay();
private:
	void update(float fDelay) override;
private:
	int m_nAddValue;
private:
	bool m_isEnabled;
	bool m_isNowActing;
	bool m_isNowUpdate;
private:
	C_Item* m_pPrev;
	C_Item* m_pNext;
private:
	Sequence* m_pStartAct;
private:
	E_USE_TYPE  m_eUseType;
	E_ITEM_TYPE m_eItemType;
private:
	C_Item() {}
	virtual ~C_Item() {}
	C_Item(C_Item&) = delete;
	C_Item operator=(C_Item&) = delete;
};