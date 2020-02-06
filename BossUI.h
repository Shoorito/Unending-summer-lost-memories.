#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class C_Timer;
class C_ProgressBar;

class C_BossUI : public Node
{
public:
	// INFO : "BossUI" ��������.
	// @return = m_pInstance(singleton Type)
	static C_BossUI* create();

	// INFO : "BossUI" ��������.
	// @return = m_pInstance(singleton Type)
	inline static C_BossUI* getInstance() { return m_pInstance; }
public:
	// INFO : "BossUI"�� ������ �ִ� "BossName"�� ��ȯ�մϴ�.(�ٸ� Ŭ���� ���� ȥ���� ����)
	// @return = Boss_Name
	inline Label* getBossName()		 { return m_pBossName; }

	// INFO : "BossUI"�� ������ �ִ� "Boss_HPBar"�� ��ȯ�մϴ�.
	// @return = Boss_HPBar
	inline C_ProgressBar* getHPBar() { return m_pHPBar; }

	// INFO : "BossUI"�� ������ �ִ� "Timer"�� ��ȯ�մϴ�.
	// @return = Boss_Timer
	inline C_Timer* getTimer()		 { return m_pTimer; }
public:
	// INFO : "Boss_Timer"�� ������ �ִ� ���� ���� �ð� ������ ��ȯ�մϴ�.
	// @return = Timer->getNowTime()
	const int& getTimerTime() const;
public:
	// INFO : �Է��� �μ��� �ش��ϴ� "Boss_Spell_Name"�� ��Ÿ���� �׼��� �����մϴ�.
	// @param = nListNum  >> PAZE_NUMBER
	// @param = nPosition >> ARRAY_NUMBER
	void spellAct(const int nListNum, const int nPosition);

	// INFO : ���� ���� �� "Boss_Spell_Name"�� ������ 0���� ����� �ִ� ���� �Լ��Դϴ�.
	void spellBreak();
public:
	// INFO : ȭ�鿡 ǥ�� �� ���� "PAZE" ���� ǥ���ϴ� �̹����� ������ �����մϴ�.
	// �ش� �Լ��� ������ ���� �������� ������ �����ϸ�, �� �� ������� ȿ���� ������ �۵��մϴ�.
	// @param = nCount >> PAZE_IMG_COUNT
	void setSpellCount(const int nCount);

	// INFO : "BOSS_UI"�� �ִ� "Timer"�� ���� �ð��� �����մϴ�.
	// Ÿ�̸Ӱ� ����Ǿ� ���Ǵ� ���̶� ���� ���� �˴ϴ�.
	// @param = nCount >> TIMER_COUNT
	void setSpellTimer(const int nCount);

	// INFO : ��������(g_arTimerCounts)���� ���� �ð��� �����մϴ�.(ResourceTable.h ����)
	// ���� Ÿ�̸Ӵ� �ð��� ���� ���������� �� ����� ���� ������ �̿��մϴ�.
	// �׷��� �߾�ȭ ���迡 ���� �ʰ�, ��뿡�� ��ȣ�ϴٴ� ������ �־� ���� ������ �����Դϴ�.
	// @param = nCount >> g_arTimerCount[nCount]
	void setSpellTimerWithArray(const int nCount);

	// INFO : ������ "PAZE" ���Ľ� ��� �Ǵ� �������� ȭ�鿡 ǥ�õǴ� ���� "PAZE"���� �ϳ��� ��Ȱ��ȭ �մϴ�.
	// ��Ȱ��ȭ �������� �ش� �̹����� �׼��� ������� ���� �ڿ������� ������Բ� �մϴ�.
	void hpBarBreak();
public:
	// INFO : �������� ���۵Ǳ� �� �ڿ������� �����ϰԲ� �����ִ� �׼��� �����ŵ�ϴ�.
	void presetBoss();

	// INFO : ������ ���� �� ���Ǵ� �������� �ַ� �ܺ� Ŭ�������� ȣ���մϴ�.
	// ���� �� ȭ�鿡 ǥ���Ǿ� �ִ� "BOSS_UI"�� ��Ȱ��ȭ ��ŵ�ϴ�.
	void endBoss();

	// INFO : �ߺ����� �� ����ϴ� �������� ������ ���� ���ð��� �ٸ��� �۵��ϵ��� �մϴ�.
	// �ϰ����� ������ "presetBoss"�� ����մϴ�.
	void presetMiddleBoss();
public:
	// INFO : ������ Ÿ���� ����� �ش��ϴ� ü�¹� ���·� "BOSS_UI::HP_BAR"�� �缳�� �˴ϴ�.
	// �ַ� ���� ������ �غ��� �� ����մϴ�.
	// @param = nType >> PAZE_TYPE
	void updateHPBar(const int nType);
private:
	// INFO : "cocos2d-x, Node"�� "init" Override �Լ�.
	// @return = Whether Initialize Success.
	bool init() override;

	// INFO : "preset"���� ���� �� ����� ��� ����� "preset~"�� ȣ���մϴ�.
	// "preset~"�Լ����� ��� �� ���� ȣ���ϴ� �뵵�� ���� �Լ��Դϴ�.
	// "preset~"�Լ����� "preset"�ڿ� �ٴ� ����� ����ϱ� �� �̸� ����/���� �ϴ� ����Դϴ�.
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