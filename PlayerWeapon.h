#pragma once
#include "cocos2d.h"
#include "EnumList.h"

using namespace cocos2d;

class C_Enemy;

static const float g_fDefaultShotSpeed = 15.0f; // ���� ���Ͽ��� �ҷ��� ��.

class C_PlayerWeapon : public Sprite
{
public:
	// INFO : �÷��̾� ���� ���� �Լ��Դϴ�.
	// @return = pWeapon >> CREATE_WEAPON_POINTER
	static C_PlayerWeapon* create();
public:
	// INFO : ������ Ÿ���� ��ȯ�մϴ�.
	// ���� ����� "�ַ� ����", "���� ����"�� ������ �ֽ��ϴ�.
	// @return m_eWeaponType >> WEAPON_TYPE
	inline const E_WEAPON_TYPE& getType()   { return m_eWeaponType; }

	// INFO : ������ �ӵ��� ��ȯ�մϴ�.(���� �ӵ��� �ƴ� ���� ��ü�� �ӵ��Դϴ�.)
	// @return m_fSpeed >> WEAPON_SPEED
	inline const float&			getSpeed()  { return m_fSpeed; }

	// INFO : ���� ������ Ȱ��ȭ ���θ� ��ȯ�մϴ�.
	// @return m_isEnabled >> WEAPON_IS_ENABLED
	inline const bool&			isEnabled() { return m_isEnabled; }
public:
	// INFO : ������ Ÿ���� �����մϴ�.
	// ���� ����� "�ַ¹���(MAIN_WEAPON)", "��������(SUB_WEAPON)"���� ������ �ֽ��ϴ�.
	// @param = eType >> WEAPON_TYPE
	inline void setType(const E_WEAPON_TYPE& eType) { m_eWeaponType = eType; }
public:
	// INFO : ������ �ӵ��� �����մϴ�.
	// @param = fSpeed >> WEAPON_SPEED
	void setSpeed(const float fSpeed);

	// INFO : ������ Ȱ��ȭ ���θ� �����մϴ�.
	// @param = isEnabled >> WEAPON_IS_ENABLED
	void setEnabled(const bool isEnabled);
public:
	// INFO : ������ �̹���(Sprite)�� �Է��� �μ��� �°� �����մϴ�.
	// @param = strFile    >> WEAPON_TEXTURE_ROUTE + TEXTURE_NAME
	// @param = recTexture >> WEAPON_USE_RECT
	void setTextureWithRect(const std::string& strFile, const Rect& recTexture);
private:
	// INFO : "Sprite"�� "init"�Լ��� �������̵� �� �����Դϴ�.
	// @return = is_Initialize_Success >> IS_INITIALIZE_SUCCESS
	bool init() override;
	void preset();

	// INFO : ���� ���⿡ ����ϴ� ������Ʈ �Լ��Դϴ�.
	// �������⿡ ������ �̺�Ʈ/�׼��� �����մϴ�.
	void updateBySubWeapon();

	// INFO : �ַ� ���⿡ ����ϴ� ������Ʈ �Լ��Դϴ�.
	// �ַ¹��⿡ ������ �̺�Ʈ/�׼��� �����մϴ�.
	void updateByWeapon();
private:
	// INFO : ����� ������ �浹�� �����ϴ� �����Դϴ�.
	// "update"�Լ����� ���˴ϴ�.
	// @return = IS_INTERSECTS_ENEMY
	const bool onIntersectsEnemy();

	// INFO : ���Ⱑ ��� ������ ��Ż ���� �� ���Ǵ� �����Դϴ�.
	// "update"�Լ����� ���˴ϴ�.
	// @return = IS_INTERSECTS_BORDER
	const bool onIntersectsBorder();
private:
	// INFO : ���� �迭(Homing) ���⿡�� ���Ǵ� �����Դϴ�.
	// ���������� ���� ����� ��ġ�� ���� ���� ���Ƶ��� �����߽��ϴ�.
	// @param = pEnemy >> AIMING_ENEMY
	void homing(C_Enemy* pEnemy);
private:
	// INFO : "Sprite" Ŭ������ "update"�Լ��� �������̵� �� �Լ��Դϴ�.
	// ������ �̵�, �浹�� ���� ������ �ð��ֽ��ϴ�.
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