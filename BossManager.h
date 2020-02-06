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
	// INFO : "BossManager" ��������.
	// @return = m_pInstance(singleton Type)
	static C_BossManager* create();
	// INFO : "BossManager" ��������.
	// @return = m_pInstance(singleton Type)
	inline static C_BossManager* getInstance() { return m_pInstance; }
public:
	// INFO : �Ŵ����� ������ �ִ� "BOSS" �����͸� ��ȯ�Ѵ�.
	// @return = m_pBoss = BOSS_POINTER
	inline C_Boss* getBoss()
	{ 
		return m_pBoss;
	}

	// INFO : �Ŵ����� ������ �ִ� "BOSS_UI" �����͸� ��ȯ�Ѵ�.
	// @return = m_pBossUI = BOSS_UI_POINTER
	inline C_BossUI* getBossUI()
	{ 
		return m_pBossUI;
	}

	// INFO : �Ŵ����� ������ �ִ� "BOSS_STATUS" �����͸� ��ȯ�Ѵ�.
	// @return = m_pBossStatus = BOSS_STATUS_POINTER
	inline C_BossStatus* getBossStatus()
	{ 
		return m_pBossStatus;
	}

	// INFO : �Ŵ����� ������ �ִ� "BONUS_NODE" �����͸� ��ȯ�Ѵ�.
	// @return = m_pBonusNode = BONUS_NODE_POINTER
	inline C_BonusNode* getScoreBonusNode()
	{
		return m_pBonusNode;
	}

	// INFO : ������ �̺�Ʈ�� ��� �Ǵ� ��ƼŬ ����Ʈ �����͸� ��ȯ�Ѵ�.
	// @return = m_pSpellEffect = SPELL_START_EFFECT
	inline ParticleSystemQuad* getSpellEffect()
	{
		return m_pSpellEffect;
	}

	// INFO : ������ �̺�Ʈ�� ��� �Ǵ� ��ƼŬ ����Ʈ �����͸� ��ȯ�Ѵ�.
	// @return = m_pSummonEffect = ������ ��ȯ�Ǿ� �ִ� ���ȿ� ���� ������ ����
	inline ParticleSystemQuad* getBossEffect()
	{
		return m_pSummonEffect;
	}
public:
	// INFO : ������ "StartEventCount"�� �ʱ�ȭ�մϴ�.
	void initSetup();

	// INFO : ������ "��ȯ"�մϴ�.(������ �������� �ʰ� ������ Sprite�� ǥ�� �ǰԲ��մϴ�.)
	void bossSummon();

	// INFO : ������ "Start"�̺�Ʈ ���� ���� "StartEventCount"�� ���� ���� ��Ű��, "StartEventCount"�� ������ŵ�ϴ�.
	void bossStart();

	// INFO : ������ ����� ����ϴ� ����Դϴ�.
	// Ŭ�������� �����ϴ� �������� ��ɵ��� ��� ��Ȱ��ȭ ��ŵ�ϴ�.
	void bossEnd();

	// INFO : ������ "����"�� ������ �� ���Ǵ� ����Դϴ�.
	// �̸� ������ ���� "���� ���� �׼�"�� �ߵ� ��ŵ�ϴ�.
	void showSpellBG();

	// INFO : ������ "����"�� ������ �� ���Ǵ� ����Դϴ�.
	// �׼� ������ �ٽ� ��Ȱ��ȭ ��ŵ�ϴ�.
	void hideSpellBG();
public:
	// INFO : ������ ����ϴ� "������ ����Ʈ"�� ��Ȱ��/Ȱ��ȭ �ϴ� ����Դϴ�.
	// @param : isEnabled >> Ȱ��ȭ ����
	void setMagicCircle(const bool isEnabled);

	// INFO : ������ "StartEventCount"�� �����ϴ� ����Դϴ�.
	// �׽�Ʈ�� ���� ����ϴ� ����Դϴ�.
	// @param : nCount >> StartEventCount
	void setStartCount(const int nCount);
private:
	// INFO : "cocos2d-x, Node"�� "init" Override �Լ�.
	// @return = Whether Initialize Success.
	bool init() override;

	// INFO : "preset"���� ���� �� ����� ��� ����� "preset~"�� ȣ���մϴ�.
	// "preset~"�Լ����� ��� �� ���� ȣ���ϴ� �뵵�� ���� �Լ��Դϴ�.
	// "preset~"�Լ����� "preset"�ڿ� �ٴ� ����� ����ϱ� �� �̸� ����/���� �ϴ� ����Դϴ�.
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
	// INFO : "boss~"���� ���� �� ����� "Boss"�� ���� �̺�Ʈ��� ��� �˴ϴ�.
	// �ش� �Լ����� ��� "�Լ������͹迭"�� ȣ��Ǹ� �̴� "bossStart" �������� Ȯ�� �� �� �ֽ��ϴ�.
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