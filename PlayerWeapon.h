#pragma once
#include "cocos2d.h"
#include "EnumList.h"

using namespace cocos2d;

class C_Enemy;

static const float g_fDefaultShotSpeed = 15.0f; // 추후 파일에서 불러올 값.

class C_PlayerWeapon : public Sprite
{
public:
	// INFO : 플레이어 무기 생성 함수입니다.
	// @return = pWeapon >> CREATE_WEAPON_POINTER
	static C_PlayerWeapon* create();
public:
	// INFO : 무기의 타입을 반환합니다.
	// 현재 무기는 "주력 무기", "보조 무기"로 나뉘어 있습니다.
	// @return m_eWeaponType >> WEAPON_TYPE
	inline const E_WEAPON_TYPE& getType()   { return m_eWeaponType; }

	// INFO : 무기의 속도를 반환합니다.(공격 속도가 아닌 무기 자체의 속도입니다.)
	// @return m_fSpeed >> WEAPON_SPEED
	inline const float&			getSpeed()  { return m_fSpeed; }

	// INFO : 현재 무기의 활성화 여부를 반환합니다.
	// @return m_isEnabled >> WEAPON_IS_ENABLED
	inline const bool&			isEnabled() { return m_isEnabled; }
public:
	// INFO : 무기의 타입을 설정합니다.
	// 현재 무기는 "주력무기(MAIN_WEAPON)", "보조무기(SUB_WEAPON)"으로 나뉘어 있습니다.
	// @param = eType >> WEAPON_TYPE
	inline void setType(const E_WEAPON_TYPE& eType) { m_eWeaponType = eType; }
public:
	// INFO : 무기의 속도를 설정합니다.
	// @param = fSpeed >> WEAPON_SPEED
	void setSpeed(const float fSpeed);

	// INFO : 무기의 활성화 여부를 설정합니다.
	// @param = isEnabled >> WEAPON_IS_ENABLED
	void setEnabled(const bool isEnabled);
public:
	// INFO : 무기의 이미지(Sprite)를 입력한 인수에 맞게 설정합니다.
	// @param = strFile    >> WEAPON_TEXTURE_ROUTE + TEXTURE_NAME
	// @param = recTexture >> WEAPON_USE_RECT
	void setTextureWithRect(const std::string& strFile, const Rect& recTexture);
private:
	// INFO : "Sprite"의 "init"함수를 오버라이드 한 형태입니다.
	// @return = is_Initialize_Success >> IS_INITIALIZE_SUCCESS
	bool init() override;
	void preset();

	// INFO : 보조 무기에 사용하는 업데이트 함수입니다.
	// 보조무기에 정해진 이벤트/액션을 수행합니다.
	void updateBySubWeapon();

	// INFO : 주력 무기에 사용하는 업데이트 함수입니다.
	// 주력무기에 정해진 이벤트/액션을 수행합니다.
	void updateByWeapon();
private:
	// INFO : 무기와 적과의 충돌을 구분하는 구문입니다.
	// "update"함수에서 사용됩니다.
	// @return = IS_INTERSECTS_ENEMY
	const bool onIntersectsEnemy();

	// INFO : 무기가 사용 범위를 이탈 했을 때 사용되는 구문입니다.
	// "update"함수에서 사용됩니다.
	// @return = IS_INTERSECTS_BORDER
	const bool onIntersectsBorder();
private:
	// INFO : 유도 계열(Homing) 무기에서 사용되는 구문입니다.
	// 지속적으로 가장 가까운 위치의 적을 향해 날아도록 설정했습니다.
	// @param = pEnemy >> AIMING_ENEMY
	void homing(C_Enemy* pEnemy);
private:
	// INFO : "Sprite" 클래스의 "update"함수를 오버라이드 한 함수입니다.
	// 무기의 이동, 충돌에 대한 갱신을 맡고있습니다.
	// @param = fDelay >> UPDATE_DELAY
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