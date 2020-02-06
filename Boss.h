#pragma once
#include "cocos2d.h"
#include "Enemy.h"

enum class E_BOSS_TYPE
{
	E_MIDDLE,
	E_NORMAL,
	E_MAX
};

using namespace cocos2d;

class C_Boss : public C_Enemy
{
public:
	// INFO : "Boss" ��������.
	// @return = �Լ� ������ ���� �Ҵ��� "Boss Pointer".
	static C_Boss* create();
public:
	// INFO : "BOSS"�� ����ȭ ���� ���ΰ� ��ȯ�Ǵ� ����.
	// @return = C_Boss::m_isImmortal >> IS_IMMORTAL
	inline const bool& isImmortal()
	{ 
		return m_isImmortal;
	}

	// INFO : "BOSS"�� "TYPE"�� ��ȯ�ϴ� ����.
	// @return = C_Boss::m_eBossType >> BOSS_TYPE
	inline const E_BOSS_TYPE& getBossType() { return m_eBossType; }
public:
	// INFO : "BOSS"�� "TYPE"�� �����ϴ� ����.
	// @param = eType >> BOSS_TYPE
	void setBossType(const E_BOSS_TYPE& eType);
public:
	// INFO : "BOSS"�� ���� ���¸� �����ϴ� ����.
	// @param = isEnabled >> BOSS_IMMORTAL
	void setImmortal(const bool isEnabled);
public:
	// INFO : "BOSS"�� ü���� �����ϴ� ����.
	// @param : nHP >> BOSS_HP
	void setHP(const int nHP) override;
public:
	// INFO : "BOSS"�� ����ȭ�� Ǯ�� "Update"�� �ǰԲ� �������ִ� �����Լ�.
	void unDelay();

	// INFO : ���� "PAZE"�� �°�, ���س��� "SpellAct"�� �߻���Ų��.
	void spellAct();

	// INFO : �������� ���� �� �̺�Ʈ �������� �ʱ� ������ �ʱ�ȭ�Ѵ�.
	void initStart();

	// INFO : ������ ü���� "BossStatus"�� ������ �ʱ� ü��([0, 0]��° ü��)���� �����Ѵ�.
	void setStartHP();
private:
	// INFO : "Enemy" Ŭ������ "init"������ "override"�� �Լ�.
	// @return = Whether Initialize Success.
	bool init() override;

	// INFO : "Enemy" Ŭ������ "preset"������ "override"�� �Լ�.
	void preset() override;

	// INFO : "Enemy" Ŭ������ "presetPattern"������ "override"�� �Լ�.
	void presetPattern() override;

	// INFO : ������ ���� �� �� ���� �������� �Ѿ�� ������ ������ Ÿ�� �׼��� �̸� �����ϴ� ����.
	void presetSpellDelay();
private:
	// INFO : "Enemy" Ŭ������ "update"������ "override"�� �Լ�.
	void update(float fDelay) override;
private:
	// INFO : "Boss"�� ������ HP�� 0�� �Ǹ� ����Ǵ� �������� ���� HP, ���ϵ��� �����ȴ�.
	void nextHP();
private:
	// INFO : "Boss"�� ����ϴ� ���� ������ �������� "m_arPattern" �Լ� �迭 �����ͷ� ȣ���� �ȴ�.
	// �μ��� "nUpdateCount"�� ���� �־��ִ� ���� �ƴ� �ɹ� ������ "m_nUpdateCount"�� ����Ѵ�.
	// "nUpdateCount"�� ���� ���� ���� ������ ����Ͽ� �ߵ� ������ �����Ͽ� ����Ѵ�.
	void pattern01(const int nUpdateCount);
	void pattern02(const int nUpdateCount);
	void pattern03(const int nUpdateCount);
	void pattern04(const int nUpdateCount);
	void pattern05(const int nUpdateCount);
	void pattern06(const int nUpdateCount);
	void pattern07(const int nUpdateCount);
private:
	void(C_Boss::*m_arPattern[7])(const int) {};
private:
	int m_nHPCount;
	int m_nHPPosition;
	int m_nScoreCount;
private:
	bool m_isImmortal;
	bool m_isUpdate;
	bool m_isAddScore;
private:
	E_BOSS_TYPE m_eBossType;
private:
	Rect m_recUseDanmaku;
private:
	Sequence* m_pDelayAct;
private:
	C_Boss() {}
	virtual ~C_Boss() {}
	C_Boss(C_Boss&) = delete;
	C_Boss operator=(C_Boss&) = delete;
};