#pragma once
#include "cocos2d.h"
#include "EnumList.h"

using namespace cocos2d;

class C_Enemy : public Sprite
{
public:
	static C_Enemy* create();
public:
	inline const int& getHP() const
	{ 
		return m_nHP; 
	}

	inline const int& getUpdateCount() const
	{
		return m_nUpdateCount;
	}

	inline const int& getAttackType() const
	{
		return m_nAttackType;
	}

	inline const E_ENEMY_TYPE& getType() const
	{
		return m_eType;
	}

	inline const bool& isEnabled() const
	{
		return m_isEnabled;
	}

	inline C_Enemy* getPrev() const
	{
		return m_pPrev;
	}

	inline C_Enemy* getNext() const
	{
		return m_pNext;
	}
public:
	Repeat* getAnimation(const int nPosition) const;
public:
	inline void setType(const E_ENEMY_TYPE& eType)
	{
		m_eType = eType;
	}
	inline void setPrev(C_Enemy* pEnemy)
	{
		m_pPrev = pEnemy;
	}
	inline void setNext(C_Enemy* pEnemy)
	{
		m_pNext = pEnemy;
	}
public:
	void initMovement();
public:
	void addAnimationWithFiles(const std::vector<std::string>& vecFiles, const float fDelay);
	void addAnimationWithAtlas(const std::string& strFile, const Rect& recSize, const int nCount, const float fDelay);
	void addAnimationWithRects(const Rect& recSize, const int nCount, const float fDelay);
public:
	virtual void setHP(const int nHP);
	virtual void addHP(const int nHP);
	virtual void setEnabled(const bool isEnabled);
public:
	void setAttackType(const int nType);
public:
	void startAnimation(const int nType);
	void setSpinMovement(const float fAngle, const float fRadius, const float fStartAngle, const Vec2& vecSpinPivot, const bool isFilped);
public:
	void setTextureWithRect(const std::string& strFile, const Rect& recSprite);
protected:
	virtual bool init() override;
	virtual void preset();
	virtual void presetPattern();
protected:
	void setUpdateCount(const int nCount);
	void addUpdateCount(const int nCount);
private:
	virtual void update(float fDelay);
private:
	void updateSpinMover();
private:
	void pattern01(const int nCount);
	void pattern02(const int nCount);
	void pattern03(const int nCount);
	void pattern04(const int nCount);
	void pattern05(const int nCount);
	void pattern06(const int nCount);
	void pattern07(const int nCount);
	void pattern08(const int nCount);
private:
	void(C_Enemy::*m_arPattern[8])(const int);
private:
	std::vector<Repeat*> m_vecAnim;
private:
	E_ENEMY_TYPE m_eType;
private:
	C_Enemy* m_pPrev;
	C_Enemy* m_pNext;
private:
	bool m_isEnabled;
	bool m_isSpinFilped;
private:
	int m_nHP;
	int m_nAttackType;
	int	m_nUpdateCount;
private:
	float m_fSpinAngle;
	float m_fAngle;
	float m_fSpinRadius;
	Vec2  m_vecSpinPivot;
protected:
	C_Enemy() {}
	virtual ~C_Enemy() {}
	C_Enemy(C_Enemy&) = delete;
	C_Enemy operator=(C_Enemy&) = delete;
};