#pragma once
#include "cocos2d.h"
#include "EnumList.h"

using namespace cocos2d;

class C_Danmaku : public Node
{
public:
	static C_Danmaku* create();
public:
	inline C_Danmaku* getPrev() const
	{
		return m_pPrev;
	}
	inline C_Danmaku* getNext() const
	{
		return m_pNext;
	}
	inline Sprite* getTexture() const
	{
		return m_pTexture;
	}
public:
	inline const int& getDamage() const
	{
		return m_nDamage;
	}
	inline const float& getAngle() const
	{
		return m_fAngle;
	}
	inline const float& getSpeed() const
	{
		return m_fSpeed;
	}
	inline const E_USE_TYPE& getUseType() const
	{
		return m_eNowUseType;
	}
public:
	inline const bool& isEnabled() const
	{
		return m_isEnabled;
	}
public:
	inline void setPrev(C_Danmaku* pDanmaku)
	{
		m_pPrev = pDanmaku;
	}
	inline void setNext(C_Danmaku* pDanmaku)
	{
		m_pNext = pDanmaku;
	}
	inline void setUseType(E_USE_TYPE eType)
	{
		m_eNowUseType = eType;
	}
public:
	void setDamage(const int nDamage);
	void setAngle(const float fAngle);
	void setSpeed(const float fSpeed);
public:
	void removeDanmaku();
public:
	void addAngle(const float fAddAngle);
public:
	void setEnabled(const bool isEnabled);
public:
	void setTextureWithRect(const std::string& strFile, const Rect& recTarget);
private:
	bool init() override;
	void preset();
	void presetRemoveAct();
	void move();
private:
	const bool onIntersectsBorder();
	const bool onIntersectsPlayer();
private:
	void update(float fDelay) override;
private:
	bool m_isEnabled;
private:
	int m_nDamage;
private:
	float m_fAngle;
	float m_fSpeed;
private:
	C_Danmaku* m_pPrev;
	C_Danmaku* m_pNext;
private:
	Sprite* m_pTexture;
	Sprite* m_pDeleteTexture;
private:
	Sequence* m_pRemoveAct;
	ScaleTo*  m_pScaleDown;
private:
	E_USE_TYPE m_eNowUseType;
private:
	C_Danmaku() {}
	virtual ~C_Danmaku() {}
	C_Danmaku(C_Danmaku&) = delete;
	C_Danmaku operator=(C_Danmaku&) = delete;
};