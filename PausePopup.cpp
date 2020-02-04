#include "PausePopup.h"
#include "Timer.h"
#include "BossUI.h"
#include "ItemManager.h"
#include "BossManager.h"
#include "TalkManager.h"
#include "FieldManager.h"
#include "2DScrollView.h"
#include "EnemyManager.h"
#include "WeaponManager.h"
#include "DanmakuManager.h"
#include "CocosFunctions.h"
#include "WeaponLauncher.h"
#include "KeyEventManager.h"
#include "PlayerController.h"

C_PausePopup * C_PausePopup::m_pInstance = nullptr;

C_PausePopup * C_PausePopup::create()
{
	if (m_pInstance)
	{
		CCLOG(u8"\"PausePopup\"가 이미 생성되어 있습니다.");

		return nullptr;
	}

	m_pInstance = new(std::nothrow) C_PausePopup();

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

void C_PausePopup::ready()
{
	if (!static_cast<int>(m_vecMenuItems.size()))
		return;

	if (m_isGameEnd)
		presetGameOverMenu();
	else
		presetMenu();

	if (static_cast<int>(m_vecMenu.size()))
	{
		m_vecMenu[m_nNowCursor]->stopAllActions();
		m_vecMenu[m_nNowCursor]->setColor(Color3B(50, 50, 50));
	}

	updateMenuList(m_isGameEnd);

	m_nNowCursor = 0;

	m_vecMenu[0]->setColor(Color3B::WHITE);
	m_vecMenu[0]->runAction(m_pSelectAct->clone());

	runAction(m_pCooltimeAct->clone());
}

Sprite * C_PausePopup::getMenuItem(const int nArrayNum)
{
	if (nArrayNum < 0 || nArrayNum > static_cast<int>(m_vecMenuItems.size()))
		return nullptr;

	return m_vecMenuItems[nArrayNum];
}

void C_PausePopup::setGameEnd(const bool isEnd)
{
	m_isGameEnd = isEnd;
}

void C_PausePopup::setEnabled(const bool isEnabled)
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

void C_PausePopup::setMenuHeight(const float fHeight)
{
	if (fHeight == 0.0f)
		return;

	m_fMenuHeight = fHeight;
}

void C_PausePopup::setTitle(const std::string & strFile)
{
	if (strFile == "")
		return;

	m_pTitle->setTexture(strFile);
}

void C_PausePopup::addMenuItem(const std::string & strFile)
{
	if (strFile == "")
		return;

	Sprite* pAdd(nullptr);

	pAdd = Sprite::create(strFile);

	pAdd->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	pAdd->setColor(Color3B(50, 50, 50));
	pAdd->setVisible(false);

	m_vecMenuItems.emplace_back(pAdd);

	addChild(pAdd);
}

void C_PausePopup::setMenuItem(const std::string & strFile, const int nArrayNum)
{
	if (strFile == "" || nArrayNum < 0 || nArrayNum > static_cast<int>(m_vecMenuItems.size()))
		return;

	m_vecMenuItems[nArrayNum]->setTexture(strFile);
}

bool C_PausePopup::init()
{
	if (!Node::init())
		return false;

	m_pTitle	  = nullptr;
	m_pSelectAct  = nullptr;
	m_pCooltimeAct = nullptr;
	m_nNowCursor  = 0;
	m_isEnabled	  = false;
	m_isNowUpdate = false;
	m_isGameEnd   = false;

	m_vecMenu.clear();
	m_vecMenuItems.clear();

	return true;
}

void C_PausePopup::preset()
{
	m_pTitle = Sprite::create();

	m_pTitle->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);

	presetMenu();
	presetAction();
	presetCooltimeAct();

	schedule(schedule_selector(C_PausePopup::update), 0.01f);

	pause();
	setVisible(false);

	addChild(m_pTitle);
}

void C_PausePopup::presetMenu()
{
	m_arEvent[0] = &C_PausePopup::menuReturnToGame;
	m_arEvent[1] = &C_PausePopup::menuReturnToMenu;
	m_arEvent[2] = &C_PausePopup::menuSaveReplay;
	m_arEvent[3] = &C_PausePopup::menuViewManual;
	m_arEvent[4] = &C_PausePopup::menuStageRestart;
}

void C_PausePopup::presetGameOverMenu()
{
	m_arEvent[0] = &C_PausePopup::menuReturnToMenu;
	m_arEvent[1] = &C_PausePopup::menuSaveReplay;
	m_arEvent[2] = &C_PausePopup::menuGameRestart;
}

void C_PausePopup::presetAction()
{
	TintTo*   pChangeColor(nullptr);
	TintTo*   pReturnColor(nullptr);
	Sequence* pAction(nullptr);
	Repeat*   pRepeat(nullptr);
	CallFunc* pCallFunc(nullptr);

	pChangeColor = TintTo::create(0.5f, Color3B(244, 178, 35));
	pReturnColor = TintTo::create(0.5f, Color3B::WHITE);
	pAction		 = Sequence::create(pChangeColor, pReturnColor, nullptr);
	pRepeat		 = Repeat::create(pAction, -1);
	pCallFunc	 = CallFunc::create(CC_CALLBACK_0(C_PausePopup::unDelay, this));
	m_pSelectAct = Sequence::create(pCallFunc, pRepeat, nullptr);

	m_pSelectAct->retain();
}

void C_PausePopup::presetCooltimeAct()
{
	CallFunc* pCall(nullptr);
	DelayTime* pDelay(nullptr);

	pCall			= CallFunc::create(CC_CALLBACK_0(C_PausePopup::unDelay, this));
	pDelay			= DelayTime::create(0.02f);
	m_pCooltimeAct  = Sequence::create(pCall, pDelay, nullptr);
	
	m_pCooltimeAct->retain();
}

void C_PausePopup::update(float fDelay)
{
	if (m_isNowUpdate || !m_isEnabled)
		return;

	m_isNowUpdate = true;

	C_KeyEvent_Manager* pManager(nullptr);

	pManager = C_KeyEvent_Manager::getInstance();

	if (pManager->getPushedType(6) == E_KEY_STATE::E_DOWN && !m_isGameEnd)
	{
		menuReturnToGame();

		return;
	}

	if (pManager->getPushedType(149) == E_KEY_STATE::E_DOWN)
	{
		(this->*m_arEvent[m_nNowCursor])();

		return;
	}

	for (int nKey(0); nKey < static_cast<int>(E_KEY::E_MAX); nKey++)
	{
		if (pManager->getPushedType(nKey + 28) == E_KEY_STATE::E_DOWN)
		{
			updateMenu(nKey);

			return;
		}
	}

	m_isNowUpdate = false;
}

void C_PausePopup::updateMenuPositions()
{
	int nMax(0);
	Vec2 vecPosition(Vec2::ZERO);

	nMax		= static_cast<int>(m_vecMenu.size());
	vecPosition = m_pTitle->getPosition() - Vec2(-75.0f, 50.0f);

	for (int nArray(0); nArray < nMax; nArray++)
	{
		m_vecMenu[nArray]->setPosition(vecPosition);

		vecPosition.y += m_fMenuHeight;
	}
}

void C_PausePopup::updateMenuList(const bool isGameEnd)
{
	if (static_cast<int>(m_vecMenuItems.size()) < static_cast<int>(E_MENU::E_STAGE_RESTART))
		return;

	for (int nCount(0); nCount < static_cast<int>(m_vecMenu.size()); nCount++)
	{
		m_vecMenu[nCount]->setVisible(false);
	}

	m_vecMenu.clear();

	if (isGameEnd)
	{
		m_vecMenu.emplace_back(m_vecMenuItems[static_cast<int>(E_MENU::E_RETURN_MENU)]);
		m_vecMenu.emplace_back(m_vecMenuItems[static_cast<int>(E_MENU::E_SAVE_REPLAY)]);
		m_vecMenu.emplace_back(m_vecMenuItems[static_cast<int>(E_MENU::E_STAGE_RESTART)]);
	}
	else
	{
		for (int nCount(0); nCount < static_cast<int>(m_vecMenuItems.size()); nCount++)
		{
			m_vecMenu.emplace_back(m_vecMenuItems[nCount]);
		}
	}

	for (int nCount(0); nCount < static_cast<int>(m_vecMenu.size()); nCount++)
	{
		m_vecMenu[nCount]->setVisible(true);
	}

	updateMenuPositions();
}

void C_PausePopup::updateMenu(const int nArrayNum)
{
	int nCursor(0);
	int arAdder[2]	{ -1, 1 };

	m_vecMenu[m_nNowCursor]->stopAllActions();
	m_vecMenu[m_nNowCursor]->setColor(Color3B(50, 50, 50));

	nCursor = m_nNowCursor + arAdder[nArrayNum];

	if (nCursor > static_cast<int>(m_vecMenu.size() - 1))
		m_nNowCursor = static_cast<int>(E_MENU::E_RETURN_GAME);
	else if (nCursor < 0)
		m_nNowCursor = static_cast<int>(m_vecMenu.size() - 1);
	else
		m_nNowCursor = nCursor;

	m_vecMenu[m_nNowCursor]->setColor(Color3B::WHITE);
	m_vecMenu[m_nNowCursor]->runAction(m_pSelectAct->clone());
}
void C_PausePopup::menuReturnToGame()
{
	DelayTime* pDelay(nullptr);
	CallFunc*  pCall(nullptr);
	CallFunc*  pCallManager(nullptr);
	Sequence*  pSeq(nullptr);

	pDelay		 = DelayTime::create(0.02f);
	pCall		 = CallFunc::create(CC_CALLBACK_0(C_PausePopup::unlock, this));
	pCallManager = CallFunc::create(CC_CALLBACK_0(C_PausePopup::unlockFieldManager, this));
	pSeq		 = Sequence::create(pDelay->clone(), pCall, pDelay->clone(), pCallManager, nullptr);

	setEnabled(false);
	runAction(pSeq);
}

void C_PausePopup::menuReturnToMenu()
{
	unDelay();
}

void C_PausePopup::menuSaveReplay()
{
	unDelay();
}

void C_PausePopup::menuViewManual()
{
	unDelay();
}

void C_PausePopup::menuStageRestart()
{
	unDelay();
}

void C_PausePopup::menuGameRestart()
{
	unDelay();
}

void C_PausePopup::unDelay()
{
	m_isNowUpdate = false;
}

void C_PausePopup::unlock()
{
	C_EnemyManager::getInstance()->resumeAllEnemy(E_ENEMY_TYPE::E_NORMAL);
	C_EnemyManager::getInstance()->resumeAllEnemy(E_ENEMY_TYPE::E_BOSS);
	C_DanmakuManager::getInstance()->allResumeDanmaku();
	C_2DScrollView::getInstance()->resume();
	C_BossManager::getInstance()->getBossUI()->getTimer()->resume();
	C_BossManager::getInstance()->getBossEffect()->resume();
	C_WeaponLauncher::getInstance()->allResume();
	C_WeaponManager::getInstance()->allResume();
	C_WeaponManager::getInstance()->resume();
	C_PlayerController::getInstance()->resume();
	C_ItemManager::getInstance()->allResumeItem();
}

void C_PausePopup::unlockFieldManager()
{
	C_FieldManager::getInstance()->setEnabled(true);
	C_FieldManager::getInstance()->getScheduleNode()->resume();
	C_FieldManager::getInstance()->unDelay();
}

