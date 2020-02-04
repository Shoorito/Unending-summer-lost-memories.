#include "FieldManager.h"
#include "EnemyManager.h"
#include "BossManager.h"
#include "BossStatus.h"
#include "BossUI.h"
#include "Boss.h"
#include "Timer.h"
#include "ProgressBar.h"
#include "ResourceTable.h"
#include "CocosFunctions.h"
#include "TalkManager.h"
#include "PausePopup.h"
#include "2DScrollView.h"
#include "ItemManager.h"
#include "KeyEventManager.h"
#include "DanmakuManager.h"
#include "PlayerWeapon.h"
#include "WeaponManager.h"
#include "WeaponLauncher.h"
#include "PlayerController.h"
#include "EnemyMovePatterns.h"

C_FieldManager * C_FieldManager::m_pInstance = nullptr;

C_FieldManager * C_FieldManager::create()
{
	if (m_pInstance)
	{
		CCLOG(u8"\"PlayerState\"가 이미 생성되어 있습니다.");

		return nullptr;
	}

	m_pInstance = new(std::nothrow) C_FieldManager();

	if (m_pInstance && m_pInstance->init())
	{
		m_pInstance->preset();
	}
	else
	{
		C_Functions::safeDelete(m_pInstance);
	}

	return m_pInstance;
}

void C_FieldManager::unDelay()
{
	m_isUpdate = false;
}

void C_FieldManager::callGameOver()
{
	allPause();
	setEnabled(false);

	C_PausePopup::getInstance()->setTitle("DefeatedMenuTitle.png");
	C_PausePopup::getInstance()->setGameEnd(true);
	C_PausePopup::getInstance()->setEnabled(true);
	C_PausePopup::getInstance()->ready();
}

void C_FieldManager::setEventCount(const int nCount)
{
	if (nCount < 0)
		return;

	while (nCount > m_arEventTimes[m_nNowEventType])
	{
		m_nNowEventType++;
	}

	m_nEventCount = nCount;
}

void C_FieldManager::setNowBossStage(const bool isStage)
{
	m_isNowBossStage = isStage;
}

void C_FieldManager::setEnabled(const bool isEnabled)
{
	if (m_isEnabled == isEnabled)
		return;

	m_isEnabled = isEnabled;

	setVisible(m_isEnabled);

	if (m_isEnabled)
		resume();
	else
		pause();
}

bool C_FieldManager::init()
{
	if (!Node::init())
		return false;

	m_isUpdate		  = false;
	m_isEnabled		  = false;
	m_isNowBossStage  = false;
	m_nEventCount	  = 0;
	m_nNowEventType   = 0;
	m_pStageTitle	  = nullptr;
	m_pStageSubTitle  = nullptr;
	m_pMiddleBossAct  = nullptr;
	m_pStageEventNode = nullptr;

	return true;
}

void C_FieldManager::preset()
{
	presetFuncs();
	presetMiddleBossAct();

	m_pStageTitle	  = Sprite::create("Stage_Title.png");
	m_pStageSubTitle  = Sprite::create("SubTitle.png");
	m_pStageEventNode = Node::create();

	m_pStageTitle->setVisible(false);
	m_pStageSubTitle->setVisible(false);
	m_pStageTitle->setOpacity(0);
	m_pStageSubTitle->setOpacity(0);

	schedule(schedule_selector(C_FieldManager::update), 0.01f);

	pause();
	setVisible(false);

	addChild(m_pStageEventNode);
	addChild(m_pStageTitle);
	addChild(m_pStageSubTitle);
}

void C_FieldManager::presetFuncs()
{
	m_arEventFunc[0] = &C_FieldManager::event01;
	m_arEventFunc[1] = &C_FieldManager::event02;
	m_arEventFunc[2] = &C_FieldManager::event03;
	m_arEventFunc[3] = &C_FieldManager::event04;
	m_arEventFunc[4] = &C_FieldManager::event05;
	m_arEventFunc[5] = &C_FieldManager::event06;
	m_arEventFunc[6] = &C_FieldManager::event07;
	m_arEventFunc[7] = &C_FieldManager::event08;
}

void C_FieldManager::presetMiddleBossAct()
{
	MoveTo*		pMove(nullptr);
	DelayTime*  pDelay(nullptr);
	CallFunc*	pFunc(nullptr);

	pMove  = MoveTo::create(3.0f, Vec2(640.0f, 480.0f));
	pDelay = DelayTime::create(2.0f);
	pFunc  = CallFunc::create(CC_CALLBACK_0(C_FieldManager::callBossFight, this));
	m_pMiddleBossAct = Sequence::create(pMove, pDelay, pFunc, nullptr);

	m_pMiddleBossAct->retain();
}

void C_FieldManager::callTitleEvent()
{
	FadeIn*    pFadeIn(nullptr);
	FadeOut*   pFadeOut(nullptr);
	DelayTime* pDelay(nullptr);
	Hide*	   pHide(nullptr);
	Sequence*  pSeqTitle(nullptr);
	Sequence*  pSeqSub(nullptr);

	pHide	  = Hide::create();
	pFadeIn	  = FadeIn::create(1.0f);
	pFadeOut  = FadeOut::create(1.0f);
	pDelay	  = DelayTime::create(2.0f);
	pSeqTitle = Sequence::create(pFadeIn->clone(), pDelay->clone(), pDelay->clone(), pFadeOut->clone(), pHide->clone(), nullptr);
	pSeqSub	  = Sequence::create(pDelay->clone(), pFadeIn->clone(), pDelay->clone(), pFadeOut->clone(), pHide->clone(), nullptr);

	m_pStageTitle->setVisible(true);
	m_pStageSubTitle->setVisible(true);

	m_pStageTitle->setPosition(640.0f, 500.0f);
	m_pStageSubTitle->setPosition(m_pStageTitle->getPosition());
	m_pStageSubTitle->addPositionY(-60.0f);

	m_pStageTitle->runAction(pSeqTitle);
	m_pStageSubTitle->runAction(pSeqSub);
}

void C_FieldManager::callBossFight()
{
	C_Boss* pBoss(nullptr);

	pBoss = C_BossManager::getInstance()->getBoss();

	pBoss->unDelay();
	pBoss->spellAct();
}

void C_FieldManager::allPause()
{
	setEnabled(false);

	m_pStageEventNode->pause();

	C_EnemyManager::getInstance()->pauseAllEnemy(E_ENEMY_TYPE::E_NORMAL);
	C_EnemyManager::getInstance()->pauseAllEnemy(E_ENEMY_TYPE::E_BOSS);
	C_DanmakuManager::getInstance()->allPauseDanmaku();
	C_2DScrollView::getInstance()->pause();
	C_BossManager::getInstance()->getBossUI()->getTimer()->pause();
	C_BossManager::getInstance()->getBossEffect()->pause();
	C_WeaponLauncher::getInstance()->allPause();
	C_WeaponManager::getInstance()->allPause();
	C_WeaponManager::getInstance()->pause();
	C_ItemManager::getInstance()->allPauseItem();
	C_PlayerController::getInstance()->pause();

	C_PausePopup::getInstance()->setEnabled(true);
	C_PausePopup::getInstance()->ready();
}

void C_FieldManager::event01()
{
	m_pStageEventNode->schedule(schedule_selector(C_FieldManager::summonEnemy01), 0.5f, 10, 0.5f);

	unDelay();
}

void C_FieldManager::event02()
{
	m_pStageEventNode->schedule(schedule_selector(C_FieldManager::summonEnemy02), 0.5f, 10, 0.5f);

	unDelay();
}

void C_FieldManager::event03()
{
	callTitleEvent();

	unDelay();
}

void C_FieldManager::event04()
{
	m_pStageEventNode->schedule(schedule_selector(C_FieldManager::summonEnemy03), 0.5f, 16, 0.0f);

	unDelay();
}

void C_FieldManager::event05()
{
	m_pStageEventNode->schedule(schedule_selector(C_FieldManager::summonEnemy01), 0.5f, 12, 0.5f);
	m_pStageEventNode->schedule(schedule_selector(C_FieldManager::summonEnemy02), 0.5f, 12, 0.5f);

	unDelay();
}

void C_FieldManager::event06()
{
	m_pStageEventNode->schedule(schedule_selector(C_FieldManager::summonEnemy04), 0.5f, 3, 0.0f);

	unDelay();
}

void C_FieldManager::event07()
{
	C_BossStatus*	pStatus(nullptr);
	C_Boss*			pMiddleBoss(nullptr);
	C_BossUI*		pUI(nullptr);

	m_isNowBossStage = true;

	pUI			= C_BossUI::getInstance();
	pStatus		= C_BossStatus::getInstance();
	pMiddleBoss = C_BossManager::getInstance()->getBoss();

	pStatus->clearAllInformation();
	pStatus->setBossName("Another World's Fairy");
	pStatus->addBarType(1);
	pStatus->addBarHP(5000, 0);
	pStatus->addSpellName(u8"Non_Spell", 0);

	pUI->setVisible(true);
	pUI->presetMiddleBoss();

	pMiddleBoss->setType(E_ENEMY_TYPE::E_BOSS);
	pMiddleBoss->setBossType(E_BOSS_TYPE::E_MIDDLE);
	pMiddleBoss->initStart();
	pMiddleBoss->setStartStat();
	pMiddleBoss->setPosition(640.0f, 700.0f);
	pMiddleBoss->setTextureWithRect("middleBoss.png", Rect(0.0f, 0.0f, 100.0f, 87.0f));
	pMiddleBoss->addAnimationWithRects(Rect(0.0f, 0.0f, 100.0f, 87.0f), 5, 0.2f);
	pMiddleBoss->startAnimation(0);
	pMiddleBoss->setEnabled(true);
	pMiddleBoss->runAction(m_pMiddleBossAct->clone());

	C_BossManager::getInstance()->getBossEffect()->setVisible(true);
	C_BossManager::getInstance()->getBossEffect()->start();

	C_EnemyManager::getInstance()->pushEnemy(pMiddleBoss, E_USE_TYPE::E_USED);
}

void C_FieldManager::event08()
{
	C_ProgressBar* pHpBar(nullptr);
	C_BossStatus*  pStatus(nullptr);
	C_BossUI*	   pBossUI(nullptr);
	C_Boss*		   pBoss(nullptr);

	m_isNowBossStage = true;

	pBossUI = C_BossUI::getInstance();
	pStatus = C_BossStatus::getInstance();
	pHpBar  = C_BossUI::getInstance()->getHPBar();
	pBoss	= C_BossManager::getInstance()->getBoss();

	pStatus->clearAllInformation();
	pStatus->setBossName(u8"Ayeon Myeong");

	pStatus->addBarType(2);
	pStatus->addBarType(2);
	pStatus->addBarType(3);

	pStatus->addBarHP(3000, 0);
	pStatus->addBarHP(5000, 0);
	pStatus->addBarHP(3000, 1);
	pStatus->addBarHP(5000, 1);
	pStatus->addBarHP(3000, 2);
	pStatus->addBarHP(5000, 2);
	pStatus->addBarHP(7000, 2);

	pStatus->addSpellName(u8"Non_Spell", 0);
	pStatus->addSpellName(u8"『수부』사방향 조준 수포", 0);
	pStatus->addSpellName(u8"Non_Spell", 1);
	pStatus->addSpellName(u8"『조작』뿌린대로 거두리라", 1);
	pStatus->addSpellName(u8"Non_Spell", 2);
	pStatus->addSpellName(u8"『조작』어떤 인어의 벡터 반사", 2);
	pStatus->addSpellName(u8"『환상』인어 환상조곡", 2);

	pBossUI->setSpellCount(pStatus->getBarCount() - 1);
	pBossUI->getBossName()->enableOutline(Color4B::BLUE, 2);
	pBossUI->setVisible(true);
	pBossUI->presetBoss();

	pHpBar->setUseGaugeCount(pStatus->getBarTypeCount(0));
	pHpBar->setGaugeMaxCost(pStatus->getBarHP(0, 0), 1);
	pHpBar->setGaugeMaxCost(pStatus->getBarHP(0, 1), 0);
	pHpBar->setGaugeColor(g_arGaugeColor[2], 1);
	pHpBar->setGaugeColor(g_arGaugeColor[1], 0);

	pBoss->initStart();
	pBoss->setStartStat();
	pBoss->stopAllActions();
	pBoss->setTexture("Boss.png");
	pBoss->setPosition(640.0f, 550.0f);
	pBoss->setBossType(E_BOSS_TYPE::E_NORMAL);

	C_BossManager::getInstance()->initSetup();
	C_TalkManager::getInstance()->startTalkEvent();
}

void C_FieldManager::event09()
{
	allPause();
	setEnabled(false);

	C_PausePopup::getInstance()->setTitle("PracticeMenuTitle.png");
	C_PausePopup::getInstance()->setGameEnd(true);
	C_PausePopup::getInstance()->setEnabled(true);
	C_PausePopup::getInstance()->ready();
}

void C_FieldManager::summonEnemy01(float fDelay)
{
	C_Enemy* pEnemy(nullptr);

	pEnemy = C_EnemyManager::getInstance()->getCursor(E_USE_TYPE::E_NOT_USED);

	C_EnemyManager::getInstance()->changeEnemy(pEnemy, E_USE_TYPE::E_USED);

	pEnemy->initMovement();
	pEnemy->stopAllActions();

	pEnemy->setHP(100.0f);
	pEnemy->setPosition(450.0f, 730.0f);
	pEnemy->setEnabled(true);

	C_Enemy_Mover_Lib::getInstance()->enemyMoveAct01(pEnemy, 0, 0, false);
}

void C_FieldManager::summonEnemy02(float fDelay)
{
	C_Enemy* pEnemy(nullptr);

	pEnemy = C_EnemyManager::getInstance()->getCursor(E_USE_TYPE::E_NOT_USED);

	C_EnemyManager::getInstance()->changeEnemy(pEnemy, E_USE_TYPE::E_USED);

	pEnemy->initMovement();
	pEnemy->stopAllActions();

	pEnemy->setHP(100.0f);
	pEnemy->setPosition(830.0f, 730.0f);
	pEnemy->setEnabled(true);

	C_Enemy_Mover_Lib::getInstance()->enemyMoveAct01(pEnemy, 1, 0, true);
}

void C_FieldManager::summonEnemy03(float fDelay)
{
	C_Enemy* pEnemy(nullptr);

	pEnemy = C_EnemyManager::getInstance()->getCursor(E_USE_TYPE::E_NOT_USED);

	C_EnemyManager::getInstance()->changeEnemy(pEnemy, E_USE_TYPE::E_USED);

	pEnemy->initMovement();
	pEnemy->stopAllActions();

	pEnemy->setHP(200.0f);
	pEnemy->setPosition(350.0f + random(0.0f, 300.0f), 730.0f);
	pEnemy->setEnabled(true);

	C_Enemy_Mover_Lib::getInstance()->enemyMoveAct02(pEnemy, 2, 1);
}

void C_FieldManager::summonEnemy04(float fDelay)
{
	for (int nEnemy(0); nEnemy < 2; nEnemy++)
	{
		C_Enemy* pEnemy(nullptr);

		pEnemy = C_EnemyManager::getInstance()->getCursor(E_USE_TYPE::E_NOT_USED);

		C_EnemyManager::getInstance()->changeEnemy(pEnemy, E_USE_TYPE::E_USED);

		pEnemy->initMovement();
		pEnemy->stopAllActions();

		pEnemy->setHP(300.0f);
		pEnemy->setPosition(350.0f, 730.0f);
		pEnemy->addPositionX(380.0f * nEnemy);
		pEnemy->setEnabled(true);

		C_Enemy_Mover_Lib::getInstance()->enemyMoveAct02(pEnemy, 3, 2);
	}
}

void C_FieldManager::update(float fDelay)
{
	if (!m_isEnabled || m_isUpdate)
		return;

	m_isUpdate = true;

	if(C_KeyEvent_Manager::getInstance()->getPushedType(6) == E_KEY_STATE::E_DOWN)
	{
		allPause();

		return;
	}

	if (m_isNowBossStage)
	{
		m_isUpdate = false;

		return;
	}

	if (m_nEventCount == m_arEventTimes[m_nNowEventType])
	{
		(this->*m_arEventFunc[m_nNowEventType])();
		
		m_nNowEventType++;
	}

	m_nEventCount++;
	m_isUpdate = false;
}
