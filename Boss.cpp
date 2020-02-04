#include "Boss.h"
#include "CocosFunctions.h"
#include "BossStatus.h"
#include "BossManager.h"
#include "AudioEngine.h"
#include "BossUI.h"
#include "ProgressBar.h"
#include "DanmakuManager.h"
#include "EnemyPatterns.h"
#include "PlayerController.h"
#include "PlayerState.h"
#include "BonusNode.h"
#include "TalkManager.h"
#include "ResourceTable.h"

using namespace experimental;

C_Boss * C_Boss::create()
{
	C_Boss* pBoss(nullptr);

	pBoss = new(std::nothrow) C_Boss();

	if (pBoss && pBoss->init())
	{
		pBoss->preset();
	}
	else
	{
		C_Functions::safeDelete(pBoss);
	}

	return pBoss;
}

void C_Boss::setBossType(const E_BOSS_TYPE & eType)
{
	m_eBossType = eType;
}

void C_Boss::setImmortal(const bool isEnabled)
{
	if (isEnabled == m_isImmortal)
		return;

	m_isImmortal = isEnabled;
}

void C_Boss::setHP(const int nHP)
{
	if (m_isImmortal)
		return;

	C_ProgressBar* pHPBar(nullptr);
	C_BossStatus*  pStatus(nullptr);

	pStatus = C_BossStatus::getInstance();
	pHPBar  = C_BossUI::getInstance()->getHPBar();

	if (nHP <= 0)
	{
		m_isImmortal = true;

		pHPBar->setGaugeCost(0.0f, pStatus->getBarTypeCount(m_nHPCount) - m_nHPPosition - 1);

		C_BossUI::getInstance()->spellBreak();
		C_BossManager::getInstance()->hideSpellBG();

		C_DanmakuManager::getInstance()->allDisabledDanmaku();

		nextHP();
		
		return;
	}

	C_Enemy::setHP(nHP);
	
	pHPBar->setGaugeCost(C_Enemy::getHP(), pStatus->getBarTypeCount(m_nHPCount) - m_nHPPosition - 1);
}

bool C_Boss::init()
{
	if (!C_Enemy::init())
		return false;

	m_nHPCount		= 0;
	m_nHPPosition	= 0;
	m_nScoreCount	= 0;
	m_eBossType		= E_BOSS_TYPE::E_NORMAL;
	m_isImmortal	= true;
	m_isUpdate		= false;
	m_isAddScore	= false;
	m_pDelayAct		= nullptr;
	m_recUseDanmaku = Rect::ZERO;

	return true;
}

void C_Boss::preset()
{
	presetPattern();
	presetSpellDelay();

	schedule(schedule_selector(C_Boss::update), 0.01f);
	setVisible(false);
	pause();
}

void C_Boss::presetPattern()
{
	m_arPattern[0] = &C_Boss::pattern01;
	m_arPattern[1] = &C_Boss::pattern02;
	m_arPattern[2] = &C_Boss::pattern03;
	m_arPattern[3] = &C_Boss::pattern04;
	m_arPattern[4] = &C_Boss::pattern05;
	m_arPattern[5] = &C_Boss::pattern06;
	m_arPattern[6] = &C_Boss::pattern07;
}

void C_Boss::presetSpellDelay()
{
	CallFunc*  pFunc(nullptr);
	CallFunc*  pSpellFunc(nullptr);
	DelayTime* pDelay(nullptr);

	pFunc		= CallFunc::create(CC_CALLBACK_0(C_Boss::unDelay, this));
	pSpellFunc	= CallFunc::create(CC_CALLBACK_0(C_Boss::spellAct, this));
	pDelay		= DelayTime::create(3.0f);
	m_pDelayAct = Sequence::create(pDelay->clone(), pSpellFunc, pDelay->clone(), pFunc, nullptr);

	m_pDelayAct->retain();
}

void C_Boss::update(float fDelay)
{
	C_BossManager::getInstance()->getBossEffect()->setPosition(getPosition());
	
	if (m_isImmortal)
		return;

	if (getUpdateCount() >= 1000000000)
		setUpdateCount(0);

	(this->*m_arPattern[getAttackType()])(getUpdateCount());

	addUpdateCount(1);
}

void C_Boss::setStartStat()
{
	C_BossStatus* pStatus(nullptr);

	pStatus = C_BossStatus::getInstance();

	if (pStatus->getBarCount() && pStatus->getBarTypeCount(0) && pStatus->getBarHP(0, 0))
	{
		C_Enemy::setHP(pStatus->getBarHP(0, 0));
	}
	else
	{
		setEnabled(false);
		CCLOG("BOSS_HP_SETTING_ERROR..");
	}
}

void C_Boss::nextHP()
{
	if (m_isUpdate)
		return;

	std::string   strScore("");
	C_BossStatus* pStatus(nullptr);

	m_isUpdate	   = true;
	pStatus		   = C_BossStatus::getInstance();
	m_nHPPosition += 1;

	if (pStatus->getBarTypeCount(m_nHPCount) == m_nHPPosition)
	{
		m_nHPPosition = 0;
		m_nHPCount++;

		C_BossUI::getInstance()->updateHPBar(m_nHPCount);
		C_BossUI::getInstance()->hpBarBreak();
	}

	if (m_isAddScore)
	{
		if (C_BossUI::getInstance()->getTimerTime())
		{
			C_Functions::dropItem(this);
			C_PlayerState::getInstance()->addScore(g_arBonusScore[m_nScoreCount]);
		
			C_BonusNode::getInstance()->showScore(true, g_arBonusScore[m_nScoreCount]);
		}
		else
		{
			C_BonusNode::getInstance()->showScore(false, 0);
		}

		CCLOG(strScore.c_str());

		m_nScoreCount++;
	}

	if (m_nHPCount == pStatus->getBarCount())
	{
		C_BossManager::getInstance()->bossEnd();
		C_Enemy::setHP(0.0f);

		CCLOG("BOSS_CLEAR!");

		return;
	}

	C_Enemy::setHP(pStatus->getBarHP(m_nHPCount, m_nHPPosition));

	setAttackType(getAttackType() + 1);
	C_BossUI::getInstance()->setSpellTimerWithArray(getAttackType());

	runAction(m_pDelayAct->clone());

	m_isUpdate = false;
}

void C_Boss::unDelay()
{
	setUpdateCount(0);

	m_isImmortal = false;
}

void C_Boss::spellAct()
{
	if (C_BossStatus::getInstance()->getSpellName(m_nHPCount, m_nHPPosition) == u8"Non_Spell")
	{
		m_isAddScore = false;

		return;
	}

	C_BossManager::getInstance()->getSpellEffect()->start();
	C_BossManager::getInstance()->showSpellBG();
	C_BossUI::getInstance()->spellAct(m_nHPCount, m_nHPPosition);

	m_isAddScore = true;
}

void C_Boss::initStart()
{
	m_nHPPosition	= 0;
	m_nHPCount		= 0;
	m_nScoreCount	= 0;
	m_isUpdate		= false;
	m_isImmortal	= true;
}

void C_Boss::pattern01(const int nUpdateCount)
{
	if (nUpdateCount % 5 == 0)
	{
		float fAngle(0.0f);

		fAngle = C_Functions::getHomingAngle(getPosition(), C_PlayerController::getInstance()->getPosition());
		fAngle += random(0.0f, 180.0f);

		m_recUseDanmaku.setRect
		(
			0.0f,
			g_arDanmakuYSize[static_cast<int>(E_DANMAKU::E_CIRCLE)],
			g_arDanmakuXSize[static_cast<int>(E_DANMAKU::E_SPADE)],
			g_arDanmakuYSize[static_cast<int>(E_DANMAKU::E_SPADE)]
		);

		C_EnemyPatterns::getInstance()->circleNWay(getPosition(), 10, fAngle, random(1.0f, 5.0f), 0.5f, m_recUseDanmaku);

		//CCLOG(u8"CALL_PATTERN_01");
	}
}

void C_Boss::pattern02(const int nUpdateCount)
{
	if (nUpdateCount % 5 == 0)
	{
		float fAngle(0.0f);

		fAngle = C_Functions::getHomingAngle(getPosition(), C_PlayerController::getInstance()->getPosition());
		//fAngle += random(0.0f, 100.0f);

		m_recUseDanmaku.setRect
		(
			0.0f,
			g_arDanmakuYSize[static_cast<int>(E_DANMAKU::E_CIRCLE)],
			g_arDanmakuXSize[static_cast<int>(E_DANMAKU::E_SPADE)],
			g_arDanmakuYSize[static_cast<int>(E_DANMAKU::E_SPADE)]
		);

		C_EnemyPatterns::getInstance()->circleNWay(getPosition(), 4, fAngle, 3.0f, 0.5f, m_recUseDanmaku);

		//CCLOG(u8"CALL_PATTERN_02");
	}
}

void C_Boss::pattern03(const int nUpdateCount)
{
	//CCLOG(u8"CALL_PATTERN_03");
}

void C_Boss::pattern04(const int nUpdateCount)
{
	//CCLOG(u8"CALL_PATTERN_04");
}

void C_Boss::pattern05(const int nUpdateCount)
{
	//CCLOG(u8"CALL_PATTERN_05");
}

void C_Boss::pattern06(const int nUpdateCount)
{
	//CCLOG(u8"CALL_PATTERN_06");
}

void C_Boss::pattern07(const int nUpdateCount)
{
	//CCLOG(u8"CALL_PATTERN_07");
}
