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
	// INFO : "Boss" 생성구문.
	// @return = 함수 내에서 동적 할당한 "Boss Pointer".
	static C_Boss* create();
public:
	// INFO : "BOSS"의 무적화 상태 여부가 반환되는 구문.
	// @return = C_Boss::m_isImmortal >> IS_IMMORTAL
	inline const bool& isImmortal()
	{ 
		return m_isImmortal;
	}

	// INFO : "BOSS"의 "TYPE"을 반환하는 구문.
	// @return = C_Boss::m_eBossType >> BOSS_TYPE
	inline const E_BOSS_TYPE& getBossType() { return m_eBossType; }
public:
	// INFO : "BOSS"의 "TYPE"을 설정하는 구문.
	// @param = eType >> BOSS_TYPE
	void setBossType(const E_BOSS_TYPE& eType);
public:
	// INFO : "BOSS"의 무적 상태를 설정하는 구문.
	// @param = isEnabled >> BOSS_IMMORTAL
	void setImmortal(const bool isEnabled);
public:
	// INFO : "BOSS"의 체력을 설정하는 구문.
	// @param : nHP >> BOSS_HP
	void setHP(const int nHP) override;
public:
	// INFO : "BOSS"의 무적화를 풀고 "Update"가 되게끔 변경해주는 편의함수.
	void unDelay();

	// INFO : 현재 "PAZE"에 맞게, 정해놓은 "SpellAct"를 발생시킨다.
	void spellAct();

	// INFO : 보스전과 관련 된 이벤트 변수들을 초기 값으로 초기화한다.
	void initStart();

	// INFO : 보스의 체력을 "BossStatus"에 지정된 초기 체력([0, 0]번째 체력)으로 설정한다.
	void setStartHP();
private:
	// INFO : "Enemy" 클래스의 "init"구문을 "override"한 함수.
	// @return = Whether Initialize Success.
	bool init() override;

	// INFO : "Enemy" 클래스의 "preset"구문을 "override"한 함수.
	void preset() override;

	// INFO : "Enemy" 클래스의 "presetPattern"구문을 "override"한 함수.
	void presetPattern() override;

	// INFO : 패턴이 격파 된 후 다음 패턴으로 넘어가기 까지의 딜레이 타임 액션을 미리 생성하는 구문.
	void presetSpellDelay();
private:
	// INFO : "Enemy" 클래스의 "update"구문을 "override"한 함수.
	void update(float fDelay) override;
private:
	// INFO : "Boss"의 지정된 HP가 0이 되면 실행되는 구문으로 다음 HP, 패턴등이 결정된다.
	void nextHP();
private:
	// INFO : "Boss"가 사용하는 공격 패턴의 구문으로 "m_arPattern" 함수 배열 포인터로 호출이 된다.
	// 인수인 "nUpdateCount"는 직접 넣어주는 값이 아닌 맴버 변수인 "m_nUpdateCount"를 사용한다.
	// "nUpdateCount"에 들어온 값에 제한 구문을 사용하여 발동 간격을 지정하여 사용한다.
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