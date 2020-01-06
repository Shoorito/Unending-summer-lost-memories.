#pragma once
#include "cocos2d.h"
#include "EnumList.h"

USING_NS_CC;

class C_PlayerWeapon;

class C_WeaponManager : public Node
{
public:
	static C_WeaponManager* create();
	inline static C_WeaponManager* getInstance() { return m_pInstance; }
public:
	inline const int& getWeaponCount(const E_WEAPON_TYPE& eType)
	{
		return m_arWeaponCount[static_cast<int>(eType)];
	}

	inline const bool& getAttackable()
	{ 
		return m_isAttackable;
	}

public:
	inline void setAttackable(const bool isAttackable)
	{ 
		m_isAttackable = isAttackable;
	}

	void setWeapon
	(
		const E_WEAPON_TYPE& eType,
		const std::string& strFile,
		const Rect& recTexture = Rect::ZERO
	);

	void setEnabled(const bool isEnabled);
public:
	void createWeapon(const E_WEAPON_TYPE& eType, const int nCount);
	void setWeaponFile(const std::string& strFile, const E_WEAPON_TYPE& eType);
	void setWeaponRect(const Rect& recWeapon, const E_WEAPON_TYPE& eType);
public:
	void addWeapon(const E_WEAPON_TYPE& eType);
	void removeWeapon(const E_WEAPON_TYPE& eType);
private:
	bool init() override;
	void preset();
	void updateMainWeapon();
	void updateSubWeapon();
private:
	void update(float fDelay);
private:
	bool m_isAttackable;
	bool m_isEnabled;
private:
	int m_nUpdateCount;
	int m_arWeaponCount[static_cast<int>(E_WEAPON_TYPE::E_MAX)]{};
private:
	Rect m_arWeaponRect[static_cast<int>(E_WEAPON_TYPE::E_MAX)]{};
private:
	std::string m_arWeapon[static_cast<int>(E_WEAPON_TYPE::E_MAX)]{};
private:
	std::vector<C_PlayerWeapon*> m_vecWeapon[static_cast<int>(E_WEAPON_TYPE::E_MAX)]{};
private:
	static C_WeaponManager* m_pInstance;
private:
	C_WeaponManager() {}
	virtual ~C_WeaponManager() {}
	C_WeaponManager(C_WeaponManager&) = delete;
	C_WeaponManager operator=(C_WeaponManager&) = delete;
};