#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class C_WeaponLauncher : public Node
{
public:
	// INFO : "WeaponLauncher" 생성구문.
	// @return = m_pInstance(singleton Type)
	static C_WeaponLauncher* create(const std::string& strFile);
public:
	// INFO : "WeaponLauncher" 참조구문.
	// @return = m_pInstance(singleton Type)
	inline static C_WeaponLauncher* getInstance() { return m_pInstance; }
public:
	// INFO : 현재 활성화 된 보조무기 발사체의 개수를 반환합니다.
	// @return m_nLauncherCount >> ENABLED_LAUNCHER_COUNT
	inline const int& getLauncherCount()
	{ 
		return m_nLauncherCount;
	}
	
	// INFO : 현재 최대로 사용 할 수 있는 보조무기 발사체의 갯수를 반환합니다.
	// 해당 함수로 반환되는 값은 "최대로 활성화 가능한 값"이지 "현재 활성화 된 개수"가 아닙니다.
	// @return m_nLauncherMaxCount >> MAX_USABLE_LAUNCHER
	inline const int& getMaxLauncherCount()
	{
		return m_nLauncherMaxCount;
	}
public:
	// INFO : 현재 사용중인 모든 발사체를 일시정지 시킵니다.
	void allPause();

	// INFO : "allPause"이전 사용했던 모든 발사체를 재가동 시킵니다.
	void allResume();
public:
	// INFO : 입력한 위치에 있는 발사체 이미지(Sprite)를 반환합니다.
	// @param = nPosition >> LAUNCHER_ARRAY_NUMBER
	Sprite* getLauncher(const int nPosition);
public:
	// INFO : 발사체로 사용 할 단일 이미지(Sprite)를 지정합니다.
	// @param = strFile >> USE_FILE_ROUTE + FILE_NAME
	void setUseTexture(const std::string& strFile);

	// INFO : 지정한 위치에 있는 발사체의 소환 위치를 정할 수 있습니다.
	// 해당 위치로 지정된 발사체는 플레이어 기준 상대 좌표로 입력한 위치에 고정됩니다.
	// @param = vecPoint  >> SUMMON_POSITION_BY_PLAYER
	// @param = nPosition >> LAUNCHER_ARRAY_NUMBER
	void setLaunchersPoint(const Vec2& vecPoint, const int nPosition);

	// INFO : 최대로 사용 할 수 있는 발사체의 개수를 정합니다.
	// 현재 사용 할 개수를 정하고 싶다면 "setWeaponCount"함수를 사용해야 합니다.
	// @param = nCount >> MAX_USABLE_LAUNCHER
	void setMaxWeaponCount(const int nCount);

	// INFO : 사용 할 발사체의 개수를 정합니다.
	// 최대로 사용 할 개수를 늘리고 싶다면 "setMaxWeaponCount"함수를 이용하셔야 합니다.
	// @param = nCount >> NOW_USE_LAUNCHER_COUNT
	void setWeaponCount(const int nCount);

	// INFO : 발사체 관리 클래스의 활성화 여부를 정합니다.
	// 해당 기능으로 비활성화 시킬 경우 "보조 무기"의 사용은 불가해지나 다른 작업은 가능합니다.
	// @param = isEnabled >> MANAGER_IS_ENABLED
	void setEnabled(const bool isEnabled);
private:
	// INFO : "Node" 클래스의 "init"함수를 오버라이드 한 함수입니다.
	// 클래스에서 관리하는 맴버 변수의 초기화를 담당합니다.
	// @return = IS_INITIALIZE
	bool init() override;
private:
	// INFO : 클래스 내에서 사용되는 여럿 기능들을 미리 지정/설정 할 때 사용합니다.
	// 생성 시에만 사용되니 재사용을 금합니다.
	void preset();

	// INFO : 클래스 내에서 사용하는 "발사체 추가 함수"입니다.
	// 해당 함수는 클래스 내 기능 "setMaxWeaponCount"에서 발사체 개수를 늘릴 때 사용됩니다.
	void addLauncher();

	// INFO : 클래스 내에서 사용하는 "발사체 감소 함수"입니다.
	// 해당 함수는 클래스 내 기능 "setMaxWeaponCount"에서 발사체 개수를 줄일 때 사용됩니다.
	void removeLauncher();

	// INFO : 발사체들의 업데이트 함수입니다.
	// 위치정보나 발사 정보를 갱신하며 "update"함수에서 플레이어가 키를 눌렀을 경우 발동됩니다.
	void updateLauncher();
private:
	// INFO : "Node" 클래스의 "update"함수를 오버라이드 한 함수입니다.
	// 발사체들의 발사, 위치정보 갱신등을 관리합니다.
	// @param = fDelay >> UPDATE_DELAY
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