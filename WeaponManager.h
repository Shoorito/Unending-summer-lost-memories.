#pragma once
#include "cocos2d.h"
#include "EnumList.h"

USING_NS_CC;

class C_PlayerWeapon;

class C_WeaponManager : public Node
{
public:
	// INFO : "WeaponManager" ��������.
	// @return = m_pInstance(singleton Type)
	static C_WeaponManager* create();

	// INFO : "WeaponManager" ��������.
	// @return = m_pInstance(singleton Type)
	inline static C_WeaponManager* getInstance() { return m_pInstance; }
public:
	// INFO : �Է��� Ÿ���� ���� ������ ��ȯ�մϴ�.
	// @param  = eType >> USE_TYPE
	// @return = m_arWeaponCount[TYPE] >> WEAPON_COUNT_BY_TYPE 
	inline const int& getWeaponCount(const E_WEAPON_TYPE& eType)
	{
		return m_arWeaponCount[static_cast<int>(eType)];
	}

	// INFO : ���� �÷��̾��� ���� ���� ���θ� ��ȯ�մϴ�.
	// �ش� ������� ��ȯ�Ǵ� ���� ���� ���� �÷��̾ ������ �������� �Ұ������� �� �� �ֽ��ϴ�.
	// @return = m_isAttackable >> IS_ATTACKABLE
	inline const bool& getAttackable()
	{ 
		return m_isAttackable;
	}
public:
	// INFO : �÷��̾��� ���� ���� ���θ� �����մϴ�.
	// �Ұ������� �������� ��� �÷��̾�� ������ �Ұ��������ϴ�.
	// @param = isAttackable >> IS_ATTACKABLE
	inline void setAttackable(const bool isAttackable)
	{ 
		m_isAttackable = isAttackable;
	}

	// INFO : �Է��� Ÿ�Կ� �ش��ϴ� ������ �ؽ��ĸ� ��� �����մϴ�.
	// @param = eType		>> WEAPON_TYPE
	// @param = strFile		>> TEXTURE_ROUTE + TEXTURE_NAME
	// @param = recTexture	>> TEXTURE_RECT_SIZE
	void setWeapon
	(
		const E_WEAPON_TYPE& eType,
		const std::string& strFile,
		const Rect& recTexture = Rect::ZERO
	);

	// INFO : "WeaponManager"�� Ȱ��ȭ ���θ� �����մϴ�.
	// ��Ȱ��ȭ ��ų��� �÷��̾�� ������ �Ұ��մϴ�.
	// @param = isEnabled >> MANAGER_IS_ENABLED
	void setEnabled(const bool isEnabled);
public:
	// INFO : �÷��̾ ��� ������ ������ ������ �Է��� �μ���ŭ ������ŵ�ϴ�.
	// "nCount"�� �Է��� ������ŭ �Է��� "eType"�� ���Ⱑ �����մϴ�.
	// @param = eType  >> WEAPON_TYPE
	// @param = nCount >> ADD_COUNT
	void createWeapon(const E_WEAPON_TYPE& eType, const int nCount);

	// INFO : �Է��� Ÿ���� �÷��̾� ���⸦ �Է��� �ؽ��ķ� �����մϴ�.
	// �ش� ����� ���� �������̰� ���� �� �����Դϴ�.
	// @param = strFile >> TEXTURE_ROUTE + TEXTURE_NAME
	// @param = eType   >> WEAPON_TYPE
	void setWeaponFile(const std::string& strFile, const E_WEAPON_TYPE& eType);

	// INFO : �Է��� Ÿ���� �÷��̾� ���� �ؽ��Ŀ��� ��� �� ������ �����մϴ�.
	// �ش� ����� ���� �������̰� ���� �� �����Դϴ�.
	// @param = recWeapon >> USE_TEXTURE_RECT_SIZE
	// @param = eType	  >> WEAPON_TYPE
	void setWeaponRect(const Rect& recWeapon, const E_WEAPON_TYPE& eType);
public:
	// INFO : �Է��� Ÿ���� ���� ��ü�� �߰��մϴ�.
	// @WARNING �ش� ������� �߰��� ���� ��ü�� �ؽ���, ��� ������ ������ ���� �ʽ��ϴ�.
	// @param = eType >> WEAPON_TYPE
	void addWeapon(const E_WEAPON_TYPE& eType);

	// INFO : �Է��� Ÿ���� ���� ��ü�� �����մϴ�.
	// @param = eType >> WEAPON_TYPE
	void removeWeapon(const E_WEAPON_TYPE& eType);
public:
	// INFO : ���� Ȱ��ȭ�Ǿ� �ִ� ������� ��� �Ͻ����� ��ŵ�ϴ�.
	void allPause();
	
	// INFO : ���� �Ͻ����� �Ǿ� �ִ� ������� ��� �簳 ��ŵ�ϴ�.
	// �ش� �Լ��δ� "��Ȱ��ȭ"��ü������ Ȱ��ȭ �� �� �����ϴ�.
	void allResume();
private:
	// INFO : "Node" Ŭ������ "init"�Լ��� �������̵� �� �Լ��Դϴ�.
	// Ŭ�������� �����ϴ� �ɹ� ������ �ʱ�ȭ�� ����մϴ�.
	// @return = IS_INITIALIZE
	bool init() override;

	// INFO : Ŭ���� ������ ���Ǵ� ���� ��ɵ��� �̸� ����/���� �� �� ����մϴ�.
	// ���� �ÿ��� ���Ǵ� ������ ���մϴ�.
	void preset();

	// INFO : Ű�Է� �� ȣ��Ǵ� "�ַ� ����� ������Ʈ ����"�Դϴ�.
	// �ش� �Լ��� ���� "�ַ� ����"�� �߻� �˴ϴ�.
	void updateMainWeapon();

	// INFO : Ű�Է� �� ȣ��Ǵ� "���� ����� ������Ʈ ����"�Դϴ�.
	// �ش� �Լ��� ���� "���� ����"�� ������ ��ġ���� �߻� �˴ϴ�.
	void updateSubWeapon();
private:
	// INFO : ���� Ȱ��ȭ, �߻� Ű �Էµ��� �����ϴ� "Node"�� "Update"�Լ��� �������̵� �Լ��Դϴ�.
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