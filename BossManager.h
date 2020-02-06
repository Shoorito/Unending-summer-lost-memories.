#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class C_Boss;
class C_BossUI;
class C_BossStatus;
class C_BonusNode;

class C_BossManager : public Node
{
public:
	// INFO : "BossManager" 생성구문.
	// @return = m_pInstance(singleton Type)
	static C_BossManager* create();
	// INFO : "BossManager" 참조구문.
	// @return = m_pInstance(singleton Type)
	inline static C_BossManager* getInstance() { return m_pInstance; }
public:
	// INFO : 매니저가 가지고 있는 "BOSS" 포인터를 반환한다.
	// @return = m_pBoss = BOSS_POINTER
	inline C_Boss* getBoss()
	{ 
		return m_pBoss;
	}

	// INFO : 매니저가 가지고 있는 "BOSS_UI" 포인터를 반환한다.
	// @return = m_pBossUI = BOSS_UI_POINTER
	inline C_BossUI* getBossUI()
	{ 
		return m_pBossUI;
	}

	// INFO : 매니저가 가지고 있는 "BOSS_STATUS" 포인터를 반환한다.
	// @return = m_pBossStatus = BOSS_STATUS_POINTER
	inline C_BossStatus* getBossStatus()
	{ 
		return m_pBossStatus;
	}

	// INFO : 매니저가 가지고 있는 "BONUS_NODE" 포인터를 반환한다.
	// @return = m_pBonusNode = BONUS_NODE_POINTER
	inline C_BonusNode* getScoreBonusNode()
	{
		return m_pBonusNode;
	}

	// INFO : 보스의 이벤트에 사용 되는 파티클 이펙트 포인터를 반환한다.
	// @return = m_pSpellEffect = SPELL_START_EFFECT
	inline ParticleSystemQuad* getSpellEffect()
	{
		return m_pSpellEffect;
	}

	// INFO : 보스의 이벤트에 사용 되는 파티클 이펙트 포인터를 반환한다.
	// @return = m_pSummonEffect = 보스가 소환되어 있는 동안에 한해 영구적 유지
	inline ParticleSystemQuad* getBossEffect()
	{
		return m_pSummonEffect;
	}
public:
	// INFO : 보스의 "StartEventCount"를 초기화합니다.
	void initSetup();

	// INFO : 보스를 "소환"합니다.(전투는 시작하지 않고 보스의 Sprite만 표현 되게끔합니다.)
	void bossSummon();

	// INFO : 보스의 "Start"이벤트 들을 현재 "StartEventCount"에 따라 실행 시키고, "StartEventCount"를 증가시킵니다.
	void bossStart();

	// INFO : 보스전 종료시 사용하는 기능입니다.
	// 클래스에서 관리하는 보스관련 기능들을 모두 비활성화 시킵니다.
	void bossEnd();

	// INFO : 보스가 "패턴"을 시작할 때 사용되는 기능입니다.
	// 미리 제작해 놓은 "패턴 시작 액션"을 발동 시킵니다.
	void showSpellBG();

	// INFO : 보스가 "패턴"을 종료할 때 사용되는 기능입니다.
	// 액션 대상들을 다시 비활성화 시킵니다.
	void hideSpellBG();
public:
	// INFO : 보스가 사용하는 "마법진 이펙트"를 비활성/활성화 하는 기능입니다.
	// @param : isEnabled >> 활성화 여부
	void setMagicCircle(const bool isEnabled);

	// INFO : 보스의 "StartEventCount"를 설정하는 기능입니다.
	// 테스트를 위해 사용하는 기능입니다.
	// @param : nCount >> StartEventCount
	void setStartCount(const int nCount);
private:
	// INFO : "cocos2d-x, Node"의 "init" Override 함수.
	// @return = Whether Initialize Success.
	bool init() override;

	// INFO : "preset"으로 정의 된 기능은 모든 기능의 "preset~"을 호출합니다.
	// "preset~"함수들을 묶어서 한 번에 호출하는 용도의 편의 함수입니다.
	// "preset~"함수들은 "preset"뒤에 붙는 기능을 사용하기 전 미리 생성/설정 하는 기능입니다.
	void preset();
	void presetStartFuncs();
	void presetEffect();
	void presetBoss();
	void presetBossUI();
	void presetBonusNode();
	void presetSpellItems();
	void presetBossStatus();
	void presetMagicCircle();
private:
	// INFO : "boss~"으로 정의 된 기능은 "Boss"의 시작 이벤트들로 사용 됩니다.
	// 해당 함수들은 모두 "함수포인터배열"로 호출되며 이는 "bossStart" 구문에서 확인 할 수 있습니다.
	// @see = bossStart
	void bossShowEffect();
	void bossShow();
	void bossPreFight();
	void bossStartFight();
private:
	C_Boss* m_pBoss;
private:
	C_BossUI* m_pBossUI;
private:
	C_BonusNode* m_pBonusNode;
private:
	C_BossStatus* m_pBossStatus;
private:
	FadeIn* m_pSpellBGFadeIn;
	Sequence* m_pSpellSCGAct;
private:
	Sprite* m_pMagicCircle;
	Sprite* m_pSpellBG;
	Sprite* m_pSpellSCG;
private:
	ParticleSystemQuad* m_pStartParticle;
	ParticleSystemQuad* m_pEndParticle;
	ParticleSystemQuad* m_pSummonEffect;
	ParticleSystemQuad* m_pSpellEffect;
private:
	void(C_BossManager::*m_arStartFunc[4])();
private:
	int m_nStartCount;
private:
	bool m_isEnabled;
private:
	static C_BossManager* m_pInstance;
private:
	C_BossManager() {}
	virtual ~C_BossManager() {}
	C_BossManager(C_BossManager&) = delete;
	C_BossManager operator=(C_BossManager&) = delete;
};