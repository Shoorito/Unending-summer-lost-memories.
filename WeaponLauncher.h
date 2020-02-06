#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class C_WeaponLauncher : public Node
{
public:
	// INFO : "WeaponLauncher" ��������.
	// @return = m_pInstance(singleton Type)
	static C_WeaponLauncher* create(const std::string& strFile);
public:
	// INFO : "WeaponLauncher" ��������.
	// @return = m_pInstance(singleton Type)
	inline static C_WeaponLauncher* getInstance() { return m_pInstance; }
public:
	// INFO : ���� Ȱ��ȭ �� �������� �߻�ü�� ������ ��ȯ�մϴ�.
	// @return m_nLauncherCount >> ENABLED_LAUNCHER_COUNT
	inline const int& getLauncherCount()
	{ 
		return m_nLauncherCount;
	}
	
	// INFO : ���� �ִ�� ��� �� �� �ִ� �������� �߻�ü�� ������ ��ȯ�մϴ�.
	// �ش� �Լ��� ��ȯ�Ǵ� ���� "�ִ�� Ȱ��ȭ ������ ��"���� "���� Ȱ��ȭ �� ����"�� �ƴմϴ�.
	// @return m_nLauncherMaxCount >> MAX_USABLE_LAUNCHER
	inline const int& getMaxLauncherCount()
	{
		return m_nLauncherMaxCount;
	}
public:
	// INFO : ���� ������� ��� �߻�ü�� �Ͻ����� ��ŵ�ϴ�.
	void allPause();

	// INFO : "allPause"���� ����ߴ� ��� �߻�ü�� �簡�� ��ŵ�ϴ�.
	void allResume();
public:
	// INFO : �Է��� ��ġ�� �ִ� �߻�ü �̹���(Sprite)�� ��ȯ�մϴ�.
	// @param = nPosition >> LAUNCHER_ARRAY_NUMBER
	Sprite* getLauncher(const int nPosition);
public:
	// INFO : �߻�ü�� ��� �� ���� �̹���(Sprite)�� �����մϴ�.
	// @param = strFile >> USE_FILE_ROUTE + FILE_NAME
	void setUseTexture(const std::string& strFile);

	// INFO : ������ ��ġ�� �ִ� �߻�ü�� ��ȯ ��ġ�� ���� �� �ֽ��ϴ�.
	// �ش� ��ġ�� ������ �߻�ü�� �÷��̾� ���� ��� ��ǥ�� �Է��� ��ġ�� �����˴ϴ�.
	// @param = vecPoint  >> SUMMON_POSITION_BY_PLAYER
	// @param = nPosition >> LAUNCHER_ARRAY_NUMBER
	void setLaunchersPoint(const Vec2& vecPoint, const int nPosition);

	// INFO : �ִ�� ��� �� �� �ִ� �߻�ü�� ������ ���մϴ�.
	// ���� ��� �� ������ ���ϰ� �ʹٸ� "setWeaponCount"�Լ��� ����ؾ� �մϴ�.
	// @param = nCount >> MAX_USABLE_LAUNCHER
	void setMaxWeaponCount(const int nCount);

	// INFO : ��� �� �߻�ü�� ������ ���մϴ�.
	// �ִ�� ��� �� ������ �ø��� �ʹٸ� "setMaxWeaponCount"�Լ��� �̿��ϼž� �մϴ�.
	// @param = nCount >> NOW_USE_LAUNCHER_COUNT
	void setWeaponCount(const int nCount);

	// INFO : �߻�ü ���� Ŭ������ Ȱ��ȭ ���θ� ���մϴ�.
	// �ش� ������� ��Ȱ��ȭ ��ų ��� "���� ����"�� ����� �Ұ������� �ٸ� �۾��� �����մϴ�.
	// @param = isEnabled >> MANAGER_IS_ENABLED
	void setEnabled(const bool isEnabled);
private:
	// INFO : "Node" Ŭ������ "init"�Լ��� �������̵� �� �Լ��Դϴ�.
	// Ŭ�������� �����ϴ� �ɹ� ������ �ʱ�ȭ�� ����մϴ�.
	// @return = IS_INITIALIZE
	bool init() override;
private:
	// INFO : Ŭ���� ������ ���Ǵ� ���� ��ɵ��� �̸� ����/���� �� �� ����մϴ�.
	// ���� �ÿ��� ���Ǵ� ������ ���մϴ�.
	void preset();

	// INFO : Ŭ���� ������ ����ϴ� "�߻�ü �߰� �Լ�"�Դϴ�.
	// �ش� �Լ��� Ŭ���� �� ��� "setMaxWeaponCount"���� �߻�ü ������ �ø� �� ���˴ϴ�.
	void addLauncher();

	// INFO : Ŭ���� ������ ����ϴ� "�߻�ü ���� �Լ�"�Դϴ�.
	// �ش� �Լ��� Ŭ���� �� ��� "setMaxWeaponCount"���� �߻�ü ������ ���� �� ���˴ϴ�.
	void removeLauncher();

	// INFO : �߻�ü���� ������Ʈ �Լ��Դϴ�.
	// ��ġ������ �߻� ������ �����ϸ� "update"�Լ����� �÷��̾ Ű�� ������ ��� �ߵ��˴ϴ�.
	void updateLauncher();
private:
	// INFO : "Node" Ŭ������ "update"�Լ��� �������̵� �� �Լ��Դϴ�.
	// �߻�ü���� �߻�, ��ġ���� ���ŵ��� �����մϴ�.
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