#include "BossManager.h"
#include "Boss.h"
#include "BossUI.h"
#include "BossStatus.h"
#include "BonusNode.h"
#include "EnemyManager.h"
#include "TalkManager.h"
#include "FieldManager.h"
#include "CocosFunctions.h"

C_BossManager * C_BossManager::m_pInstance = nullptr;

C_BossManager * C_BossManager::create()
{
	if (m_pInstance)
	{
		CCLOG(u8"\"BossStatus\"가 이미 생성 되어 있습니다.");

		return nullptr;
	}

	m_pInstance = new(std::nothrow) C_BossManager();

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

void C_BossManager::initSetup()
{
	m_nStartCount = 0;
}

void C_BossManager::bossSummon()
{	
	bossStart();

	m_pStartParticle->setPosition(m_pBoss->getPosition());
	m_pStartParticle->setVisible(true);
	m_pStartParticle->start();
}

void C_BossManager::bossStart()
{
	(this->*m_arStartFunc[m_nStartCount])();

	m_nStartCount++;
}

void C_BossManager::bossEnd()
{
	if (m_pBoss->getBossType() == E_BOSS_TYPE::E_NORMAL)
	{
		C_TalkManager::getInstance()->endTalkEvent();
	}

	m_pBoss->setEnabled(false);
	
	m_pSummonEffect->setVisible(false);
	m_pSummonEffect->stop();
	
	m_pEndParticle->setPosition(m_pBoss->getPosition());
	m_pEndParticle->setVisible(true);
	m_pEndParticle->start();
	
	setMagicCircle(false);

	m_pSpellBG->setVisible(false);

	C_BossUI::getInstance()->endBoss();
	C_FieldManager::getInstance()->setNowBossStage(false);
	C_EnemyManager::getInstance()->popEnemy(m_pBoss, E_USE_TYPE::E_USED);
}

void C_BossManager::showSpellBG()
{
	m_pSpellBG->setVisible(true);
	m_pSpellSCG->setPosition(1280.0f, 720.0f);

	m_pSpellSCG->runAction(m_pSpellSCGAct->clone());
	m_pSpellBG->runAction(m_pSpellBGFadeIn->clone());
}

void C_BossManager::hideSpellBG()
{
	m_pSpellBG->setOpacity(0);
	m_pSpellBG->setVisible(false);
}

void C_BossManager::setMagicCircle(const bool isEnabled)
{
	m_pMagicCircle->setVisible(isEnabled);
	m_pMagicCircle->setPosition(m_pBoss->getPosition());

	if (isEnabled)
		m_pMagicCircle->resume();
	else
		m_pMagicCircle->pause();
}

void C_BossManager::setStartCount(const int nCount)
{
	if (nCount < 0)
		return;

	m_nStartCount = nCount;
}

bool C_BossManager::init()
{
	if (!Node::init())
		return false;

	m_pBoss			 = nullptr;
	m_pBossUI		 = nullptr;
	m_pSpellBG		 = nullptr;
	m_pSpellSCG		 = nullptr;
	m_pBossStatus	 = nullptr;
	m_pSpellSCGAct	 = nullptr;
	m_pStartParticle = nullptr;
	m_pEndParticle	 = nullptr;
	m_pSummonEffect  = nullptr;
	m_pSpellEffect	 = nullptr;
	m_pMagicCircle	 = nullptr;
	m_pSpellBGFadeIn = nullptr;
	m_nStartCount	 = 0;
	m_isEnabled		 = false;

	return true;
}

void C_BossManager::preset()
{
	presetSpellItems();
	presetStartFuncs();
	presetBossStatus();
	presetBonusNode();
	presetMagicCircle();
	presetBoss();
	presetBossUI();
	presetEffect();
	
	addChild(m_pSpellBG);
	addChild(m_pEndParticle);
	addChild(m_pSummonEffect);
	addChild(m_pMagicCircle);
	addChild(m_pSpellEffect);
	addChild(m_pBoss);
	addChild(m_pStartParticle);
	addChild(m_pSpellSCG);
	addChild(m_pBossUI);
	addChild(m_pBonusNode);
}

void C_BossManager::presetStartFuncs()
{
	m_arStartFunc[0] = &C_BossManager::bossShowEffect;
	m_arStartFunc[1] = &C_BossManager::bossShow;
	m_arStartFunc[2] = &C_BossManager::bossPreFight;
	m_arStartFunc[3] = &C_BossManager::bossStartFight;
}

void C_BossManager::presetEffect()
{
	m_pStartParticle = ParticleSystemQuad::create("boss_start.plist");
	m_pEndParticle	 = ParticleSystemQuad::create("boss_end.plist");
	m_pSummonEffect  = ParticleSystemQuad::create("boss_effect_01.plist");
	m_pSpellEffect	 = ParticleSystemQuad::create("spell_effect.plist");

	m_pStartParticle->setPosition(m_pBoss->getPosition());
	m_pEndParticle->setPosition(m_pBoss->getPosition());
	m_pSummonEffect->setPosition(m_pBoss->getPosition());
	m_pSpellEffect->setPosition(m_pBoss->getPosition());

	m_pStartParticle->setVisible(false);
	m_pEndParticle->setVisible(false);
	m_pSummonEffect->setVisible(false);
	m_pSpellEffect->setVisible(false);

	m_pStartParticle->stop();
	m_pEndParticle->stop();
	m_pSummonEffect->stop();
	m_pSpellEffect->stop();
}

void C_BossManager::presetBoss()
{
	m_pBoss = C_Boss::create();

	m_pBoss->setType(E_ENEMY_TYPE::E_BOSS);
}

void C_BossManager::presetBossUI()
{
	m_pBossUI = C_BossUI::create();
}

void C_BossManager::presetBonusNode()
{
	m_pBonusNode = C_BonusNode::create();

	m_pBonusNode->hideScore();
	m_pBonusNode->setFontFile(u8"fonts/NotoSansCJKkr-Bold.otf");
	m_pBonusNode->getScoreLabel()->enableOutline(Color4B::BLACK, 2);
}

void C_BossManager::presetSpellItems()
{
	MoveBy* pMove01(nullptr);
	MoveBy* pMove02(nullptr);
	MoveBy* pMove03(nullptr);
	Hide*	pHide(nullptr);
	Show*	pShow(nullptr);

	pMove01 = MoveTo::create(0.5f, Vec2(640.0f, 375.0f));
	pMove02 = MoveTo::create(1.5f, Vec2(590.0f, 325.0f));
	pMove03 = MoveTo::create(0.5f, Vec2(-250.0f, -200.0f));
	pHide	= Hide::create();
	pShow	= Show::create();

	m_pSpellBG		 = Sprite::create("Boss_Spell_BG.png");
	m_pSpellSCG		 = Sprite::create("Ayeon_SCG.png");
	m_pSpellBGFadeIn = FadeIn::create(1.0f);
	m_pSpellSCGAct	 = Sequence::create(pShow, pMove01, pMove02, pMove03, pHide, nullptr);

	m_pSpellBG->setPosition(Director::getInstance()->getWinSize() / 2.0f);
	m_pSpellBG->setOpacity(0);
	m_pSpellBG->setVisible(false);

	m_pSpellSCG->setVisible(false);
	m_pSpellSCG->setPosition(1280.0f, 720.0f);

	m_pSpellBGFadeIn->retain();
	m_pSpellSCGAct->retain();
}

void C_BossManager::presetBossStatus()
{
	m_pBossStatus = C_BossStatus::create();
}

void C_BossManager::presetMagicCircle()
{
	RotateBy* pRotate(nullptr);
	Repeat*   pRepeat(nullptr);
	ScaleTo*  pScaleUp(nullptr);
	ScaleTo*  pScaleDown(nullptr);
	Sequence* pScaleAct(nullptr);
	Repeat*   pScaleRepeat(nullptr);
	Spawn*	  pAct(nullptr);

	m_pMagicCircle = Sprite::create("Magic_Circle.png");

	pRotate		 = RotateBy::create(1.0f, 360.0f);
	pRepeat		 = Repeat::create(pRotate, -1);
	pScaleUp	 = ScaleTo::create(1.0f, 1.5f);
	pScaleDown	 = ScaleTo::create(1.0f, 0.5f);
	pScaleAct	 = Sequence::create(pScaleUp, pScaleDown, nullptr);
	pScaleRepeat = Repeat::create(pScaleAct, -1);
	pAct		 = Spawn::create(pRepeat, pScaleRepeat, nullptr);

	m_pMagicCircle->setVisible(false);
	m_pMagicCircle->setScale(0.1f);
	m_pMagicCircle->runAction(pAct);
	m_pMagicCircle->pause();
}

void C_BossManager::bossShowEffect()
{
	CallFunc*  pStartEvent(nullptr);
	DelayTime* pDelay(nullptr);
	Sequence*  pSeq(nullptr);

	pStartEvent = CallFunc::create(CC_CALLBACK_0(C_BossManager::bossStart, this));
	pDelay		= DelayTime::create(2.0f);
	pSeq		= Sequence::create(pDelay, pStartEvent, nullptr);

	//AudioEngine::play2d("se_ch02.mp3", false, 0.1f);

	runAction(pSeq);
}

void C_BossManager::bossShow()
{
	m_pBoss->setEnabled(true);
}

void C_BossManager::bossPreFight()
{
	m_pBoss->initStart();
	m_pBoss->setStartStat();

	m_pSummonEffect->setVisible(true);
	m_pSummonEffect->start();

	setMagicCircle(true);
}

void C_BossManager::bossStartFight()
{
	m_pSpellEffect->setPosition(m_pBoss->getPosition());
	m_pSpellEffect->setVisible(true);

	m_pBoss->spellAct();
	m_pBoss->unDelay();

	m_pBossUI->setSpellTimerWithArray(0);

	C_EnemyManager::getInstance()->pushEnemy(m_pBoss, E_USE_TYPE::E_USED);
}
