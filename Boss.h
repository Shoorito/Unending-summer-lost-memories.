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
	static C_Boss* create();
public:
	inline const bool& isImmortal()
	{ 
		return m_isImmortal;
	}
	inline const E_BOSS_TYPE& getBossType() { return m_eBossType; }
public:
	void setBossType(const E_BOSS_TYPE& eType);
public:
	void setImmortal(const bool isEnabled);
public:
	void setHP(const int nHP) override;
public:
	void unDelay();
	void spellAct();
	void initStart();
	void setStartStat();
private:
	bool init() override;
	void preset() override;
	void presetPattern() override;
	void presetSpellDelay();
private:
	void update(float fDelay) override;
private:
	void nextHP();
private:
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