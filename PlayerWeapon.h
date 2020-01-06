#pragma once
#include "cocos2d.h"
#include "EnumList.h"

using namespace cocos2d;

class C_PlayerWeapon : public Sprite
{
public:
	static C_PlayerWeapon* create();
public:
	inline const E_WEAPON_TYPE& getType()   { return m_eWeaponType; }
	inline const float&			getSpeed()  { return m_fSpeed; }
	inline const bool&			isEnabled() { return m_isEnabled; }
public:
	inline void setType(const E_WEAPON_TYPE& eType) { m_eWeaponType = eType; }
public:
	void setSpeed(const float fSpeed);
	void setEnabled(const bool isEnabled);
public:
	void setTextureWithRect(const std::string& strFile, const Rect& recTexture);
private:
	bool init() override;
	void preset();
	void updateBySubWeapon();
	void updateByWeapon();
private:
	const bool onIntersectsEnemy();
	const bool onIntersectsBorder();
private:
	void homing(C_Enemy* pEnemy);
private:
	void update(float fDelay);
private:
	void(C_PlayerWeapon::*m_arUpdater[2])();
private:
	E_WEAPON_TYPE m_eWeaponType;
private:
	float m_fSpeed;
	bool  m_isEnabled;
private:
	C_PlayerWeapon() {}
	virtual ~C_PlayerWeapon() {}
	C_PlayerWeapon(C_PlayerWeapon&) = delete;
	C_PlayerWeapon operator=(C_PlayerWeapon&) = delete;
};