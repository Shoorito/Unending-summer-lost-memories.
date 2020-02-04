#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class C_Timer;
class C_ProgressBar;

class C_BossUI : public Node
{
public:
	static C_BossUI* create();
	inline static C_BossUI* getInstance() { return m_pInstance; }
public:
	inline Label* getBossName()		 { return m_pBossName; }
	inline C_ProgressBar* getHPBar() { return m_pHPBar; }
	inline C_Timer* getTimer()		 { return m_pTimer; }
public:
	const int& getTimerTime() const;
public:
	void spellAct(const int nListNum, const int nPosition);
	void spellBreak();
public:
	void setSpellCount(const int nCount);
	void setSpellTimer(const int nCount);
	void setSpellTimerWithArray(const int nCount);
	void hpBarBreak();
public:
	void presetBoss();
	void endBoss();
	void presetMiddleBoss();
public:
	void updateHPBar(const int nType);
private:
	bool init() override;
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