#include "TalkManager.h"
#include "FieldManager.h"
#include "BossManager.h"
#include "WeaponManager.h"
#include "CocosFunctions.h"
#include "KeyEventManager.h"
#include "PlayerController.h"

C_TalkManager * C_TalkManager::m_pInstance = nullptr;

C_TalkManager * C_TalkManager::create()
{
	if (m_pInstance)
	{
		CCLOG(u8"\"TalkManager\"가 이미 생성되어 있습니다.");

		return nullptr;
	}

	m_pInstance = new(std::nothrow) C_TalkManager();

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

void C_TalkManager::removeRetainMember()
{
	m_pPlayerAct->release();
	m_pTalkBoxAct->release();
	m_pDialougeAct->release();
	m_arMoveAct[0]->release();
	m_arMoveAct[1]->release();
	m_arMoveAct[2]->release();
	m_arMoveAct[3]->release();
}

void C_TalkManager::startTalkEvent()
{
	m_arSCG[0]->setOpacity(0);
	m_arSCG[0]->setPosition(240.0f, -25.0f);
	m_arSCG[0]->setVisible(true);
	m_arSCG[0]->setTextureRect(Rect(Vec2::ZERO, m_arSCGSizes[0]));

	m_arSCG[1]->setPosition(1040.0f, -25.0f);
	m_arSCG[1]->setTextureRect(Rect(Vec2::ZERO, m_arSCGSizes[1]));

	m_pTextbox->setPosition(290.0f, 161.0f);
	m_pTextbox->setScale(0.01f);

	m_pDialouge->setOpacity(0);
	m_pDialouge->setPosition(300.0f, 155.0f);

	m_pTextbox->runAction(m_pTalkBoxAct->clone());
	m_arSCG[0]->runAction(m_pPlayerAct->clone());

	setEnabled(true);

	pause();
	C_WeaponManager::getInstance()->pause();
	C_PlayerController::getInstance()->pause();
}

void C_TalkManager::endTalkEvent()
{
	DelayTime*	pDelay(nullptr);
	CallFunc*	pCall(nullptr);
	Sequence*	pSeq(nullptr);

	pDelay	= DelayTime::create(1.0f);
	pCall	= CallFunc::create(CC_CALLBACK_0(C_TalkManager::unDelay, this));
	pSeq	= Sequence::create(pDelay, pCall, nullptr);

	writeDialouge();
	setEnabled(true);
	C_WeaponManager::getInstance()->pause();
	C_PlayerController::getInstance()->pause();

	runAction(pSeq);

	m_nPageNumber++;
}

void C_TalkManager::setPageNumber(const int nNumber)
{
	if (nNumber < 0)
		return;

	m_nPageNumber = nNumber;
}

void C_TalkManager::addEventCount(const int nCount)
{
	if (nCount < 0)
		return;

	m_vecEventCounter.emplace_back(nCount);
}

void C_TalkManager::setEventCount(const int nCount, const int nArrayNum)
{
	if (nArrayNum < 0 || nArrayNum >= static_cast<int>(m_vecEventCounter.size()) || nCount < 0)
		return;

	m_vecEventCounter[nArrayNum] = nCount;
}

void C_TalkManager::setEnabled(const bool isEnabled)
{
	if (isEnabled == m_isEnabled)
		return;

	m_isEnabled = isEnabled;

	setVisible(m_isEnabled);

	if (m_isEnabled)
		resume();
	else
		pause();
}

void C_TalkManager::setTalkOutline(const Color4B & colorOutline, const int nArrayNum)
{
	if (nArrayNum < 0)
		return;

	m_vecOutlineColors[nArrayNum] = colorOutline;
}

void C_TalkManager::setDialogueAct(const float fDelay)
{
	if (fDelay < 0.01f)
		return;

	m_pDialougeAct->setDuration(fDelay);
}

void C_TalkManager::setSCGMoveAct(const Vec2 & vecMovement, const int nArrayNum)
{
	m_arMoveAct[nArrayNum]->setEndPosition(vecMovement);
}

void C_TalkManager::setTextBox(const std::string & strFile)
{
	if (strFile == "")
		return;

	m_pTextbox->setTexture(strFile);
}

void C_TalkManager::setSCGAtlas(const std::string & strFile, const Size & szTexture, const int nType)
{
	m_arSCG[nType]->setTexture(strFile);
	m_arSCGSizes[nType] = szTexture;
}

void C_TalkManager::setDialogueFont(const std::string & strFonts)
{
	if (strFonts == "")
		return;

	m_pDialouge->initWithTTF("", strFonts, m_nFontSize);
}

void C_TalkManager::presetDialouge(const std::string & strFileData)
{
	if (!FileUtils::getInstance()->isFileExist(strFileData))
		return;

	int			nSize(0);
	std::string strData(u8"");
	std::string strLine(u8"");
	bool		isLineChecked(false);
	bool		isTextChecked(false);
	char		arCheck[2]{'{', '}'};

	strData = FileUtils::getInstance()->getStringFromFile(strFileData);
	nSize   = static_cast<int>(strData.size());
	
	for (int nPosition(0); nPosition < nSize; nPosition++)
	{
		int	nArrayNum(0);

		if (strData[nPosition] == arCheck[isLineChecked])
		{
			isLineChecked = true;
			nPosition++;
		}

		while (isLineChecked)
		{
			if (strData[nPosition] == arCheck[isLineChecked])
			{
				isLineChecked = false;
			}

			if (strData[nPosition] == '\"')
			{
				if (isTextChecked)
				{
					isTextChecked = false;
					
					m_arTextSource[nArrayNum]->emplace_back(strLine);
					
					nArrayNum++;
				}
				else
				{
					isTextChecked = true;

					strLine.clear();

					nPosition++;
				}
			}

			if (isTextChecked)
			{
				strLine += static_cast<unsigned char>(strData[nPosition]);
			}

			nPosition++;
		}
	}
}

bool C_TalkManager::init()
{
	if (!Node::init())
		return false;

	m_pTextbox		= nullptr;
	m_pDialouge		= nullptr;
	m_pDialougeAct	= nullptr;
	m_pTalkBoxAct	= nullptr;
	m_pPlayerAct	= nullptr;
	m_nEventCount	= 0;
	m_nPageNumber	= 0;
	m_nPrevSCG		= 0;
	m_nPrevType		= 0;
	m_nFontSize		= 20;
	m_isEnabled		= false;
	m_isNowReading	= false;
	
	m_vecDialogueTarget.clear();
	m_vecOutlineColors.clear();
	m_vecDialogueList.clear();
	m_vecEventCounter.clear();
	m_vecSCGNumber.clear();
	
	return true;
}

void C_TalkManager::preset()
{
	presetFuncs();
	presetItems();
	presetActions();

	schedule(schedule_selector(C_TalkManager::update), 0.01f);

	pause();
	setVisible(false);

	addChild(m_arSCG[0]);
	addChild(m_arSCG[1]);
	addChild(m_pTextbox);
	addChild(m_pDialouge);
}

void C_TalkManager::presetFuncs()
{
	m_arEventFunc[0] = &C_TalkManager::event01;
	m_arEventFunc[1] = &C_TalkManager::event02;
	m_arEventFunc[2] = &C_TalkManager::event03;
	m_arEventFunc[3] = &C_TalkManager::event04;
	m_arEventFunc[4] = &C_TalkManager::event05;
}

void C_TalkManager::presetItems()
{
	m_arSCG[0]	 = Sprite::create();
	m_arSCG[1]	 = Sprite::create();
	m_pTextbox	 = Sprite::create();
	m_pDialouge  = Label::create();

	m_vecOutlineColors.emplace_back(Color4B(224, 104, 61, 255));
	m_vecOutlineColors.emplace_back(Color4B::RED);
	m_vecOutlineColors.emplace_back(Color4B(128, 128, 128, 255));

	m_pTextbox->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	m_pDialouge->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	m_arSCG[1]->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	m_arSCG[0]->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);

	m_arSCG[0]->setOpacity(0);
	m_arSCG[1]->setOpacity(0);
	m_pDialouge->setOpacity(0);

	m_arSCG[0]->setVisible(false);
	m_arSCG[1]->setVisible(false);
}

void C_TalkManager::presetActions()
{
	FadeIn* pFadeIn(nullptr);
	CallFunc* pCall(nullptr);

	pFadeIn = FadeIn::create(1.0f);
	pCall   = CallFunc::create(CC_CALLBACK_0(C_TalkManager::unDelay, this));

	m_pDialougeAct = Sequence::create(pFadeIn, pCall, nullptr);
	m_arMoveAct[0] = MoveTo::create(1.0f, Vec2(240.0f, -25.0f));
	m_arMoveAct[1] = MoveTo::create(1.0f, Vec2(290.0f, 25.0f));
	m_arMoveAct[2] = MoveTo::create(1.0f, Vec2(1040.0f, -25.0f));
	m_arMoveAct[3] = MoveTo::create(1.0f, Vec2(990.0f, 25.0f));

	presetStartActions();

	m_pDialougeAct->retain();
	m_arMoveAct[0]->retain();
	m_arMoveAct[1]->retain();
	m_arMoveAct[2]->retain();
	m_arMoveAct[3]->retain();
}

void C_TalkManager::presetStartActions()
{
	DelayTime*	pDelay(nullptr);
	ScaleTo*	pXScaleUp(nullptr);
	ScaleTo*	pYScaleUp(nullptr);
	CallFunc*	pCallPage(nullptr);
	CallFunc*	pCallEvent(nullptr);
	Spawn*		pSpawn(nullptr);

	pXScaleUp	  = ScaleTo::create(1.0f, 1.0f, 0.01f);
	pYScaleUp	  = ScaleTo::create(1.0f, 1.0f, 1.0f);
	m_pTalkBoxAct = Sequence::create(pXScaleUp, pYScaleUp, nullptr);

	pDelay		  = DelayTime::create(pXScaleUp->getDuration() + pYScaleUp->getDuration());
	pSpawn		  = Spawn::create(m_pDialougeAct->clone(), m_arMoveAct[1]->clone(), nullptr);
	pCallPage	  = CallFunc::create(CC_CALLBACK_0(C_TalkManager::writeDialouge, this));
	pCallEvent	  = CallFunc::create(CC_CALLBACK_0(C_TalkManager::enableEvent, this));
	m_pPlayerAct  = Sequence::create(pDelay, pSpawn, pCallPage, pCallEvent, nullptr);

	m_pPlayerAct->retain();
	m_pTalkBoxAct->retain();
}

void C_TalkManager::update(float fDelay)
{
	if (!C_FieldManager::getInstance()->isEnabled())
		return;

	ParticleSystemQuad* pChangeEffect(nullptr);

	pChangeEffect = static_cast<ParticleSystemQuad*>(getChildByName("Form_Change"));

	if (pChangeEffect)
	{
		pChangeEffect->setPosition(m_arSCG[1]->getPosition());
		pChangeEffect->addPosition(-m_arSCGSizes[0].width / 2.0f, m_arSCGSizes[1].height / 2.0f);
	}

	if (m_isNowReading)
		return;

	if (C_KeyEvent_Manager::getInstance()->getPushedType(149) == E_KEY_STATE::E_DOWN)
	{
		if (m_nPageNumber == static_cast<int>(m_vecDialogueList.size()))
		{
			setEnabled(false);
			C_FieldManager::getInstance()->callGameClear();
			return;
		}

		m_isNowReading = true;

		if (m_nPageNumber == m_vecEventCounter[m_nEventCount])
		{
			(this->*m_arEventFunc[m_nEventCount])();

			m_nEventCount++;

			return;
		}

		writeDialouge();

		m_nPageNumber++;

		return;
	}
}

void C_TalkManager::unDelay()
{
	m_isNowReading = false;
}

void C_TalkManager::formChange()
{
	m_arSCG[1]->setTextureRect(Rect(Vec2(m_arSCGSizes[1].width, 0.0f), m_arSCGSizes[1]));
	
	unDelay();
}

void C_TalkManager::enableEvent()
{
	m_nPageNumber  = 1;
	m_isNowReading = false;

	resume();
}

void C_TalkManager::writeDialouge()
{
	int  nNowSCG(0);
	int  nSCGType(0);
	bool arSwap[2]{ true, false };

	nNowSCG  = C_Functions::convertToInt(m_vecDialogueTarget[m_nPageNumber]) - 1;
	nSCGType = C_Functions::convertToInt(m_vecSCGNumber[m_nPageNumber]) - 1;

	m_pDialouge->setOpacity(0);
	m_pDialouge->stopAllActions();
	m_pDialouge->setString(m_vecDialogueList[m_nPageNumber]);
	m_pDialouge->enableOutline(m_vecOutlineColors[nNowSCG], 2);
	m_pDialouge->runAction(m_pDialougeAct->clone());

	if (m_nPrevSCG == nNowSCG && m_nPrevType == nSCGType)
		return;

	m_arSCG[nNowSCG]->stopAllActions();
	m_arSCG[arSwap[nNowSCG]]->stopAllActions();

	m_arSCG[nNowSCG]->setOpacity(255);
	m_arSCG[arSwap[nNowSCG]]->setOpacity(200);

	if (nSCGType > 0)
	{
		Rect recSize(Rect::ZERO);

		recSize = Rect(Vec2(m_arSCGSizes[nNowSCG].width * nSCGType, 0.0f), m_arSCGSizes[nNowSCG]);

		m_arSCG[nNowSCG]->setTextureRect(recSize);
	}

	m_arSCG[0]->runAction(m_arMoveAct[arSwap[nNowSCG]]->clone());
	m_arSCG[1]->runAction(m_arMoveAct[nNowSCG + 2]->clone());

	m_nPrevSCG  = nNowSCG;
	m_nPrevType = nSCGType;
}

void C_TalkManager::event01()
{
	Spawn*	   pSpawn(nullptr);
	Sequence*  pSeq(nullptr);
	CallFunc*  pWriteFunc(nullptr);
	CallFunc*  pUnDelayFunc(nullptr);
	DelayTime* pDelay(nullptr);

	pDelay		 = DelayTime::create(3.0f);
	pWriteFunc	 = CallFunc::create(CC_CALLBACK_0(C_TalkManager::writeDialouge, this));
	pUnDelayFunc = CallFunc::create(CC_CALLBACK_0(C_TalkManager::unDelay, this));
	pSpawn		 = Spawn::create(m_pDialougeAct->clone(), m_arMoveAct[3]->clone(), nullptr);
	pSeq		 = Sequence::create(pDelay, pSpawn, pUnDelayFunc, nullptr);

	m_arSCG[1]->setOpacity(0);
	m_arSCG[1]->setPosition(1040.0f, -25.0f);
	m_arSCG[1]->setVisible(true);
	m_arSCG[1]->runAction(pSeq);

	C_BossManager::getInstance()->bossSummon();
}

void C_TalkManager::event02()
{
	DelayTime* pDelay(nullptr);
	CallFunc*  pFunc(nullptr);
	Sequence*  pSeq(nullptr);
	ParticleSystemQuad* pChangeEffect(nullptr);

	pChangeEffect = ParticleSystemQuad::create("Form_Change.plist");
	pDelay		  = DelayTime::create(2.0f);
	pFunc		  = CallFunc::create(CC_CALLBACK_0(C_TalkManager::formChange, this));
	pSeq		  = Sequence::create(pDelay, pFunc, nullptr);

	pChangeEffect->setName("Form_Change");
	pChangeEffect->setPosition(m_arSCG[1]->getPosition());
	pChangeEffect->addPosition(-m_arSCGSizes[0].width / 2.0f, m_arSCGSizes[1].height / 2.0f);
	pChangeEffect->runAction(pSeq);

	addChild(pChangeEffect);
}

void C_TalkManager::event03()
{
	setEnabled(false);
	C_BossManager::getInstance()->bossStart();
	C_BossManager::getInstance()->bossStart();
	C_WeaponManager::getInstance()->resume();
	C_PlayerController::getInstance()->resume();
}

void C_TalkManager::event04()
{
	ParticleSystemQuad* pChangeEffect(nullptr);

	pChangeEffect = static_cast<ParticleSystemQuad*>(getChildByName("Form_Change"));

	pChangeEffect->initWithFile("boss_remove.plist");
	pChangeEffect->start();

	writeDialouge();

	m_nPageNumber++;
}

void C_TalkManager::event05()
{
	ParticleSystemQuad* pChangeEffect(nullptr);

	pChangeEffect = static_cast<ParticleSystemQuad*>(getChildByName("Form_Change"));

	pChangeEffect->stop();

	m_arSCG[1]->setVisible(false);

	unDelay();
}
