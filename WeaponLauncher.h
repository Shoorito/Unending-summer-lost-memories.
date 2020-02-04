#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class C_WeaponLauncher : public Node
{
public:
	static C_WeaponLauncher* create(const std::string& strFile);
public:
	inline static C_WeaponLauncher* getInstance() { return m_pInstance; }
public:
	inline const int& getLauncherCount()
	{ 
		return m_nLauncherCount;
	}
	inline const int& getMaxLauncherCount()
	{
		return m_nLauncherMaxCount;
	}
public:
	void allPause();
	void allResume();
public:
	Sprite* getLauncher(const int nPosition);
public:
	void setUseTexture(const std::string& strFile);
	void setLaunchersPoint(const Vec2& vecPoint, const int nPosition);
	void setMaxWeaponCount(const int nCount);
	void setWeaponCount(const int nCount);
	void setEnabled(const bool isEnabled);
private:
	bool init() override;
private:
	void preset();
	void addLauncher();
	void removeLauncher();
	void updateLauncher();
private:
	void update(float dt);
private:
	std::vector<Sprite*> m_vecLaunchers{};
	std::vector<Vec2>    m_vecLauncherPointers{};
private:
	void(C_WeaponLauncher::*m_arLauncherFunc[2])();
private:
	std::string m_strTexture;
private:
	int m_nLauncherCount;
	int m_nLauncherMaxCount;
private:
	bool m_isEnabled;
private:
	static C_WeaponLauncher* m_pInstance;
private:
	C_WeaponLauncher() {}
	virtual ~C_WeaponLauncher() {}
	C_WeaponLauncher(C_WeaponLauncher&) = delete;
	C_WeaponLauncher operator=(C_WeaponLauncher&) = delete;
};