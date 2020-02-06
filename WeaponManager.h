#pragma once
#include "cocos2d.h"
#include "EnumList.h"

USING_NS_CC;

class C_PlayerWeapon;

class C_WeaponManager : public Node
{
public:
	// INFO : "WeaponManager" 생성구문.
	// @return = m_pInstance(singleton Type)
	static C_WeaponManager* create();

	// INFO : "WeaponManager" 참조구문.
	// @return = m_pInstance(singleton Type)
	inline static C_WeaponManager* getInstance() { return m_pInstance; }
public:
	// INFO : 입력한 타입의 무기 개수를 반환합니다.
	// @param  = eType >> USE_TYPE
	// @return = m_arWeaponCount[TYPE] >> WEAPON_COUNT_BY_TYPE 
	inline const int& getWeaponCount(const E_WEAPON_TYPE& eType)
	{
		return m_arWeaponCount[static_cast<int>(eType)];
	}

	// INFO : 현재 플레이어의 공격 가능 여부를 반환합니다.
	// 해당 기능으로 반환되는 값에 따라 현재 플레이어가 공격이 가능한지 불가능한지 알 수 있습니다.
	// @return = m_isAttackable >> IS_ATTACKABLE
	inline const bool& getAttackable()
	{ 
		return m_isAttackable;
	}
public:
	// INFO : 플레이어의 공격 가능 여부를 설정합니다.
	// 불가능으로 설정했을 경우 플레이어는 공격이 불가능해집니다.
	// @param = isAttackable >> IS_ATTACKABLE
	inline void setAttackable(const bool isAttackable)
	{ 
		m_isAttackable = isAttackable;
	}

	// INFO : 입력한 타입에 해당하는 무기의 텍스쳐를 모두 변경합니다.
	// @param = eType		>> WEAPON_TYPE
	// @param = strFile		>> TEXTURE_ROUTE + TEXTURE_NAME
	// @param = recTexture	>> TEXTURE_RECT_SIZE
	void setWeapon
	(
		const E_WEAPON_TYPE& eType,
		const std::string& strFile,
		const Rect& recTexture = Rect::ZERO
	);

	// INFO : "WeaponManager"의 활성화 여부를 설정합니다.
	// 비활성화 시킬경우 플레이어는 공격이 불가합니다.
	// @param = isEnabled >> MANAGER_IS_ENABLED
	void setEnabled(const bool isEnabled);
public:
	// INFO : 플레이어가 사용 가능한 무기의 개수를 입력한 인수만큼 증가시킵니다.
	// "nCount"로 입력한 개수만큼 입력한 "eType"의 무기가 증가합니다.
	// @param = eType  >> WEAPON_TYPE
	// @param = nCount >> ADD_COUNT
	void createWeapon(const E_WEAPON_TYPE& eType, const int nCount);

	// INFO : 입력한 타입의 플레이어 무기를 입력한 텍스쳐로 변경합니다.
	// 해당 기능은 보다 직관적이게 개편 될 예정입니다.
	// @param = strFile >> TEXTURE_ROUTE + TEXTURE_NAME
	// @param = eType   >> WEAPON_TYPE
	void setWeaponFile(const std::string& strFile, const E_WEAPON_TYPE& eType);

	// INFO : 입력한 타입의 플레이어 무기 텍스쳐에서 사용 할 공간을 변경합니다.
	// 해당 기능은 보다 직관적이게 개편 될 예정입니다.
	// @param = recWeapon >> USE_TEXTURE_RECT_SIZE
	// @param = eType	  >> WEAPON_TYPE
	void setWeaponRect(const Rect& recWeapon, const E_WEAPON_TYPE& eType);
public:
	// INFO : 입력한 타입의 무기 개체를 추가합니다.
	// @WARNING 해당 기능으로 추가한 무기 개체는 텍스쳐, 사용 공간이 정해져 있지 않습니다.
	// @param = eType >> WEAPON_TYPE
	void addWeapon(const E_WEAPON_TYPE& eType);

	// INFO : 입력한 타입의 무기 개체를 제거합니다.
	// @param = eType >> WEAPON_TYPE
	void removeWeapon(const E_WEAPON_TYPE& eType);
public:
	// INFO : 현재 활성화되어 있는 무기들을 모두 일시정지 시킵니다.
	void allPause();
	
	// INFO : 현재 일시정지 되어 있는 무기들을 모두 재개 시킵니다.
	// 해당 함수로는 "비활성화"개체까지는 활성화 할 수 없습니다.
	void allResume();
private:
	// INFO : "Node" 클래스의 "init"함수를 오버라이드 한 함수입니다.
	// 클래스에서 관리하는 맴버 변수의 초기화를 담당합니다.
	// @return = IS_INITIALIZE
	bool init() override;

	// INFO : 클래스 내에서 사용되는 여럿 기능들을 미리 지정/설정 할 때 사용합니다.
	// 생성 시에만 사용되니 재사용을 금합니다.
	void preset();

	// INFO : 키입력 시 호출되는 "주력 무기용 업데이트 구문"입니다.
	// 해당 함수를 통해 "주력 무기"가 발사 됩니다.
	void updateMainWeapon();

	// INFO : 키입력 시 호출되는 "보조 무기용 업데이트 구문"입니다.
	// 해당 함수를 통해 "보조 무기"가 정해진 위치에서 발사 됩니다.
	void updateSubWeapon();
private:
	// INFO : 무기 활성화, 발사 키 입력등을 관리하는 "Node"의 "Update"함수의 오버라이드 함수입니다.
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