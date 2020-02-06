#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class C_Timer;
class C_ProgressBar;

class C_BossUI : public Node
{
public:
	// INFO : "BossUI" 생성구문.
	// @return = m_pInstance(singleton Type)
	static C_BossUI* create();

	// INFO : "BossUI" 참조구문.
	// @return = m_pInstance(singleton Type)
	inline static C_BossUI* getInstance() { return m_pInstance; }
public:
	// INFO : "BossUI"가 가지고 있는 "BossName"을 반환합니다.(다른 클래스 정보 혼동에 주의)
	// @return = Boss_Name
	inline Label* getBossName()		 { return m_pBossName; }

	// INFO : "BossUI"가 가지고 있는 "Boss_HPBar"를 반환합니다.
	// @return = Boss_HPBar
	inline C_ProgressBar* getHPBar() { return m_pHPBar; }

	// INFO : "BossUI"가 가지고 있는 "Timer"를 반환합니다.
	// @return = Boss_Timer
	inline C_Timer* getTimer()		 { return m_pTimer; }
public:
	// INFO : "Boss_Timer"가 가지고 있는 현재 남은 시각 정보를 반환합니다.
	// @return = Timer->getNowTime()
	const int& getTimerTime() const;
public:
	// INFO : 입력한 인수에 해당하는 "Boss_Spell_Name"을 나타내는 액션을 실행합니다.
	// @param = nListNum  >> PAZE_NUMBER
	// @param = nPosition >> ARRAY_NUMBER
	void spellAct(const int nListNum, const int nPosition);

	// INFO : 패턴 격파 후 "Boss_Spell_Name"의 투명도를 0으로 만들어 주는 편의 함수입니다.
	void spellBreak();
public:
	// INFO : 화면에 표시 될 남은 "PAZE" 값을 표현하는 이미지의 개수를 설정합니다.
	// 해당 함수로 설정한 값은 보스전에 들어가기전 설정하며, 그 후 사라지는 효과는 별개로 작동합니다.
	// @param = nCount >> PAZE_IMG_COUNT
	void setSpellCount(const int nCount);

	// INFO : "BOSS_UI"에 있는 "Timer"의 남은 시간을 설정합니다.
	// 타이머가 실행되어 사용되는 중이라도 값이 적용 됩니다.
	// @param = nCount >> TIMER_COUNT
	void setSpellTimer(const int nCount);

	// INFO : 전역변수(g_arTimerCounts)으로 남은 시간을 설정합니다.(ResourceTable.h 참고)
	// 기존 타이머는 시간을 직접 정해주지만 이 방법은 전역 변수를 이용합니다.
	// 그러나 중앙화 설계에 맞지 않고, 사용에도 모호하다는 단점이 있어 추후 삭제될 예정입니다.
	// @param = nCount >> g_arTimerCount[nCount]
	void setSpellTimerWithArray(const int nCount);

	// INFO : 보스의 "PAZE" 격파시 사용 되는 구문으로 화면에 표시되는 남은 "PAZE"값을 하나씩 비활성화 합니다.
	// 비활성화 과정에서 해당 이미지에 액션을 실행시켜 보다 자연스럽게 사라지게끔 합니다.
	void hpBarBreak();
public:
	// INFO : 보스전이 시작되기 전 자연스럽게 등장하게끔 도와주는 액션을 실행시킵니다.
	void presetBoss();

	// INFO : 보스전 종료 시 사용되는 구문으로 주로 외부 클래스에서 호출합니다.
	// 실행 시 화면에 표현되어 있는 "BOSS_UI"를 비활성화 시킵니다.
	void endBoss();

	// INFO : 중보스전 시 사용하는 구문으로 기존의 보스 세팅과는 다르게 작동하도록 합니다.
	// 일관적인 동작은 "presetBoss"와 비슷합니다.
	void presetMiddleBoss();
public:
	// INFO : 지정한 타입의 페이즈에 해당하는 체력바 형태로 "BOSS_UI::HP_BAR"가 재설정 됩니다.
	// 주로 다음 패턴을 준비할 때 사용합니다.
	// @param = nType >> PAZE_TYPE
	void updateHPBar(const int nType);
private:
	// INFO : "cocos2d-x, Node"의 "init" Override 함수.
	// @return = Whether Initialize Success.
	bool init() override;

	// INFO : "preset"으로 정의 된 기능은 모든 기능의 "preset~"을 호출합니다.
	// "preset~"함수들을 묶어서 한 번에 호출하는 용도의 편의 함수입니다.
	// "preset~"함수들은 "preset"뒤에 붙는 기능을 사용하기 전 미리 생성/설정 하는 기능입니다.
	void preset();
	void presetName();
	void presetTimer();
	void presetHPBar();
	void presetSpellName();
	void presetSpellCount();
	void presetSpellbreck();
	void presetSpellStart();
private:
	Label* m_pBossName;
	Label* m_pSpellName;
private:
	C_ProgressBar* m_pHPBar;
private:
	C_Timer* m_pTimer;
private:
	std::vector<Sprite*> m_vecSpellCount;
private:
	Spawn* m_pSpellBreakAct;
	Spawn* m_pSpellStartAct;
private:
	int m_nFontSize;
	int m_nSpellCount;
private:
	static C_BossUI* m_pInstance;
private:
	C_BossUI() {}
	virtual ~C_BossUI() {}
	C_BossUI(C_BossUI&) = delete;
	C_BossUI operator=(C_BossUI&) = delete;
};