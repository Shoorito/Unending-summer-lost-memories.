#pragma once
#include "cocos2d.h"
#include "EnumList.h"

using namespace cocos2d;

class C_Enemy : public Sprite
{
public:
	static C_Enemy* create();
public:
	inline const float& getHP()
	{ 
		return m_fHP; 
	}

	inline const int& getUpdateCount()
	{
		return m_nUpdateCount;
	}

	inline const int& getAttackType()
	{
		return m_nAttackType;
	}

	inline const E_ENEMY_TYPE& getType()
	{
		return m_eType;
	}

	inline const bool& isEnabled()
	{
		return m_isEnabled;
	}
public:
	Repeat* getAnimation(const int nPosition);
public:
	inline void setType(const E_ENEMY_TYPE& eType)
	{
		m_eType = eType;
	}
public:
	void addAnimationWithFiles(const std::vector<std::string>& vecFiles, const float fDelay);
	void addAnimationWithAtlas(const std::string& strFile, const Rect& recSize, const int nCount, const float fDelay);
public:
	virtual void setHP(const float fHP);
	void setAttackType(const int nType);
	virtual void setEnabled(const bool isEnabled);
public:
	void startAnimation(const int nType);
public:
	virtual void setTextureWithRect(const std::string& strFile, const Rect& recSprite);
private:
	bool init() override;
	void preset();
	void update(float fDelay);
private:
	bool m_isEnabled;
private:
	E_ENEMY_TYPE m_eType;
private:
	std::vector<Repeat*> m_vecAnim;
private:
	float m_fHP;
private:
	int m_nAttackType;
	int	m_nUpdateCount;
private:
	C_Enemy() {}
	virtual ~C_Enemy() {}
	C_Enemy(C_Enemy&) = delete;
	C_Enemy operator=(C_Enemy&) = delete;
};