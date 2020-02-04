#include "BossUI.h"
#include "CocosFunctions.h"
#include "ProgressBar.h"
#include "Timer.h"
#include "BossStatus.h"
#include "ResourceTable.h"

C_BossUI * C_BossUI::m_pInstance = nullptr;

C_BossUI * C_BossUI::create()
{
	if (m_pInstance)
	{
		CCLOG(u8"\"BossUI\"가 이미 생성 되어 있습니다.");

		return nullptr;
	}

	m_pInstance = new(std::nothrow) C_BossUI();

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

const int & C_BossUI::getTimerTime() const
{
	return m_pTimer->getNowTime();
}

void C_BossUI::spellAct(const int nListNum, const int nPosition)
{
	m_pSpellName->setString(C_BossStatus::getInstance()->getSpellName(nListNum, nPosition));
	m_pSpellName->addPositionY(-50.0f);
	m_pSpellName->runAction(m_pSpellStartAct->clone());
}

void C_BossUI::spellBreak()
{
	m_pSpellName->setOpacity(0);
}

void C_BossUI::setSpellCount(const int nCount)
{
	if (nCount == m_nSpellCount)
		return;

	int arAdder[2]{ -1, 1 };

	for (int nSpell(m_nSpellCount); nSpell != nCount;)
	{
		if (nCount > m_nSpellCount)
		{
			Sprite* pAdd(nullptr);

			pAdd = Sprite::create("SpellCount.png");

			pAdd->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
			pAdd->setPosition(m_pBossName->getPosition());
			pAdd->addPositionY(-55.0f);
			pAdd->addPositionX(pAdd->getContentSize().width * static_cast<float>(nSpell));
			pAdd->addPositionX(5.0f * static_cast<float>(nSpell));

			addChild(pAdd);

			m_vecSpellCount.emplace_back(pAdd);
		}
		else
		{
			Sprite* pRemover(nullptr);

			pRemover = m_vecSpellCount[m_nSpellCount - 1];

			m_vecSpellCount.pop_back();

			removeChild(pRemover);
		}

		nSpell += arAdder[nCount > m_nSpellCount];
		m_nSpellCount = nSpell;
	}
}

void C_BossUI::setSpellTimer(const int nCount)
{
	m_pTimer->startTimer(nCount);
}

void C_BossUI::setSpellTimerWithArray(const int nCount)
{
	m_pTimer->startTimer(g_arTimerCounts[nCount]);
}

void C_BossUI::hpBarBreak()
{
	if (!m_nSpellCount)
		return;

	m_vecSpellCount[m_nSpellCount - 1]->runAction(m_pSpellBreakAct->clone());

	m_nSpellCount--;
}

void C_BossUI::presetBoss()
{
	FadeIn* pFade(nullptr);
	C_BossStatus* pStatus(nullptr);

	pFade	= FadeIn::create(0.75f);
	pStatus = C_BossStatus::getInstance();

	pFade->retain();
	
	for (int nSpell(0); nSpell < m_nSpellCount; nSpell++)
	{
		m_vecSpellCount[nSpell]->setOpacity(0);
		m_vecSpellCount[nSpell]->setVisible(true);
		m_vecSpellCount[nSpell]->runAction(pFade->clone());
	}
	
	m_pBossName->setString(pStatus->getBossName());
	m_pBossName->setOpacity(0);
	m_pBossName->setVisible(true);
	m_pBossName->runAction(pFade->clone());

	m_pHPBar->fadeInAction(0.75f);

	pFade->release();
}

void C_BossUI::endBoss()
{
	setVisible(false);
	m_pBossName->setVisible(false);
	m_pHPBar->setVisible(false);
	m_pTimer->stopTimer();
}

void C_BossUI::presetMiddleBoss()
{
	C_BossStatus* pStatus(nullptr);

	pStatus = C_BossStatus::getInstance();

	m_pBossName->enableOutline(Color4B::RED, 2);
	m_pHPBar->setUseGaugeCount(1);
	m_pHPBar->setGaugeMaxCost(pStatus->getBarHP(0, 0), 0);
	m_pHPBar->setGaugeColor(Color3B::WHITE);
	m_pTimer->startTimer(50);

	presetBoss();
}

void C_BossUI::updateHPBar(const int nType)
{
	int nHPBarNum(0);
	C_BossStatus* pBossStat(nullptr);
	
	pBossStat = C_BossStatus::getInstance();

	if (pBossStat->getBarCount() <= nType)
		return;

	nHPBarNum = pBossStat->getBarTypeCount(nType);

	m_pHPBar->setUseGaugeCount(nHPBarNum);

	for (int nFirst(0); nFirst < nHPBarNum; nFirst++)
	{
		m_pHPBar->setGaugeMaxCost(pBossStat->getBarHP(nType, nFirst), nHPBarNum - nFirst - 1);
		m_pHPBar->setGaugeColor(g_arGaugeColor[g_nGaugeColors - 1 - nFirst], nHPBarNum - nFirst - 1);
	}

	m_pHPBar->sortGauges();
}

bool C_BossUI::init()
{
	if (!Node::init())
		return false;

	m_pBossName		 = nullptr;
	m_pSpellName	 = nullptr;
	m_pHPBar		 = nullptr;
	m_pTimer		 = nullptr;
	m_pSpellBreakAct = nullptr;
	m_pSpellStartAct = nullptr;
	m_nFontSize		 = 20;
	m_nSpellCount	 = 0;

	m_vecSpellCount.clear();

	return true;
}

void C_BossUI::preset()
{
	presetName();
	presetTimer();
	presetHPBar();
	presetSpellCount();
	presetSpellbreck();
	presetSpellStart();
	presetSpellName();

	setVisible(false);

	for (int nSpell(0); nSpell < m_nSpellCount; nSpell++)
	{
		addChild(m_vecSpellCount[nSpell]);
	}

	addChild(m_pBossName);
	addChild(m_pTimer);
	addChild(m_pSpellName);
	addChild(m_pHPBar);
}

void C_BossUI::presetName()
{
	m_pBossName = Label::createWithTTF("", "fonts/NotoSansCJKkr-Bold.otf", m_nFontSize);

	m_pBossName->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	m_pBossName->setPosition(295.0f, 680.0f);
	m_pBossName->setVisible(false);
}

void C_BossUI::presetTimer()
{
	m_pTimer = C_Timer::create();

	m_pTimer->initWithTTF("", "fonts/NotoSansCJKkr-Bold.otf", 25.0f);
	m_pTimer->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	m_pTimer->setPosition(m_pBossName->getPosition());
	m_pTimer->addPositionX(690.0f);
	m_pTimer->setEnabled(false);
}

void C_BossUI::presetHPBar()
{
	std::string strGaugeTag("");
	C_BossStatus* pBossStat(nullptr);

	m_pHPBar	= C_ProgressBar::create();
	pBossStat	= C_BossStatus::getInstance();
	strGaugeTag = "BOSS_HPBAR";

	m_pHPBar->setVisible(false);
	m_pHPBar->setBackground(Color3B(64, 64, 64), Rect(0.0f, 0.0f, 217.0f, 20.0f));
	m_pHPBar->setBorder(Color3B(244, 178, 35), strGaugeTag, 3.0f);
	m_pHPBar->createGauges(3);
	
	m_pHPBar->setContentSize(680.0f, 15.0f);
	m_pHPBar->setPosition(640.0f, m_pBossName->getPositionY());
	m_pHPBar->addPositionY(-30.0f);
	m_pHPBar->sortGauges();
}

void C_BossUI::presetSpellName()
{
	m_pSpellName = Label::createWithTTF("", "fonts/NotoSansCJKkr-Bold.otf", m_nFontSize);

	m_pSpellName->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	m_pSpellName->setPosition(m_pTimer->getPosition());
	m_pSpellName->addPositionY(-55.0f);
	m_pSpellName->setOpacity(0);
}

void C_BossUI::presetSpellCount()
{
	int nSpellNum(0);
	Sprite* pSpellCount(nullptr);

	nSpellNum = C_BossStatus::getInstance()->getBarCount();

	for (int nSpell(0); nSpell < nSpellNum - 1; nSpell++)
	{
		pSpellCount = Sprite::create("SpellCount.png");
		
		pSpellCount->setVisible(false);
		pSpellCount->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		pSpellCount->setPosition(m_pBossName->getPosition());
		pSpellCount->addPositionY(-55.0f);
		pSpellCount->addPositionX(pSpellCount->getContentSize().width * static_cast<float>(nSpell));
		pSpellCount->addPositionX(5.0f * static_cast<float>(nSpell));

		m_vecSpellCount.emplace_back(pSpellCount);

		m_nSpellCount++;
	}
}

void C_BossUI::presetSpellbreck()
{
	FadeOut* pOut(nullptr);
	ScaleTo* pScaleUp(nullptr);
	
	pOut			 = FadeOut::create(0.5f);
	pScaleUp		 = ScaleTo::create(0.5f, 2.5f);
	m_pSpellBreakAct = Spawn::create(pOut, pScaleUp, nullptr);

	m_pSpellBreakAct->retain();
}

void C_BossUI::presetSpellStart()
{
	MoveBy* pMove(nullptr);
	FadeIn* pFade(nullptr);

	pMove = MoveBy::create(1.0f, Vec2(0.0f, 50.0f));
	pFade = FadeIn::create(1.0f);
	m_pSpellStartAct = Spawn::create(pMove, pFade, nullptr);

	m_pSpellStartAct->retain();
}
