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
	static C_BossManager* create();
	inline static C_BossManager* getInstance() { return m_pInstance; }
public:
	inline C_Boss* getBoss()
	{ 
		return m_pBoss;
	}
	inline C_BossUI* getBossUI()
	{ 
		return m_pBossUI;
	}
	inline C_BossStatus* getBossStatus()
	{ 
		return m_pBossStatus;
	}
	inline C_BonusNode* getScoreBonusNode()
	{
		return m_pBonusNode;
	}
	inline ParticleSystemQuad* getSpellEffect()
	{
		return m_pSpellEffect;
	}
	inline ParticleSystemQuad* getBossEffect()
	{
		return m_pSummonEffect;
	}
public:
	void initSetup();
	void bossSummon();
	void bossStart();
	void bossEnd();
	void showSpellBG();
	void hideSpellBG();
public:
	void setMagicCircle(const bool isEnabled);
	void setStartCount(const int nCount);
private:
	bool init() override;
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