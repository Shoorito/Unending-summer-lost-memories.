#include "PlayScene.h"
#include "PlayerUI.h"
#include "2DScrollView.h"
#include "ProgressBar.h"
#include "PlayerState.h"
#include "CocosFunctions.h"
#include "ResourceTable.h"
#include "PlayerController.h"
#include "WeaponLauncher.h"
#include "WeaponManager.h"
#include "KeyEventManager.h"
#include "DanmakuManager.h"
#include "EnemyMovePatterns.h"
#include "FieldManager.h"
#include "TalkManager.h"
#include "Danmaku.h"
#include "EnemyManager.h"
#include "BossManager.h"
#include "BossUI.h"
#include "Boss.h"
#include "Timer.h"
#include "PausePopup.h"
#include "Item.h"
#include "ItemManager.h"

USING_NS_CC;

C_PlayScene* C_PlayScene::m_pInstance = nullptr;

C_PlayScene* C_PlayScene::create()
{
	if (m_pInstance)
	{
		CCLOG(u8"이미 메인 씬이 생성되어 있습니다.");

		return nullptr;
	}

	m_pInstance = new(std::nothrow) C_PlayScene();

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

bool C_PlayScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

	m_pUI				= nullptr;
	m_pPopup			= nullptr;
	m_pWLauncher		= nullptr;
	m_pKeyManager		= nullptr;
	m_pScrollView		= nullptr;
	m_pTalkManager		= nullptr;
	m_pBossManager		= nullptr;
	m_pPlayerState		= nullptr;
	m_pItemManager		= nullptr;
	m_pEnemyManager		= nullptr;
	m_pFieldManager		= nullptr;
	m_pWeaponManager	= nullptr;
	m_pDanmakuManager	= nullptr;
	m_pEnemyMovePattern = nullptr;
	m_pPlayerController = nullptr;
	
    return true;
}

void C_PlayScene::preset()
{
	if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		FileUtils::getInstance()->setWritablePath("C:/cocos2d-x-3.17.1/tools/cocos2d-console/bin/create01/Resources/");
	}
	
	m_pPlayerState		= C_PlayerState::create();
	m_pKeyManager		= C_KeyEvent_Manager::create();
	m_pEnemyMovePattern = C_Enemy_Mover_Lib::create();

	createScroll();
	createController();
	createWeaponLauncher();
	createWeaponManager();

	m_pUI			  = C_PlayerUI::create();
	m_pEnemyManager   = C_EnemyManager::create();
	m_pDanmakuManager = C_DanmakuManager::create();
	m_pItemManager	  = C_ItemManager::create();
	m_pBossManager	  = C_BossManager::create();
	m_pFieldManager	  = C_FieldManager::create();

	createItem();
	createEnemy();
	createDanmaku();
	createTalkManager();
	createPopup();

	m_pUI->setEnabled(true);
	m_pKeyManager->setEnabled(true);

	addChild(m_pKeyManager);
	addChild(m_pScrollView);
	addChild(m_pFieldManager);
	addChild(m_pBossManager);
	addChild(m_pDanmakuManager);
	addChild(m_pItemManager);
	addChild(m_pWeaponManager);
	addChild(m_pEnemyManager);
	addChild(m_pPlayerController);
	addChild(m_pWLauncher);
	addChild(m_pTalkManager);
	addChild(m_pPopup);
	addChild(m_pUI);

	testFieldManager();
}

void C_PlayScene::testFieldManager()
{
	CallFunc*	pCall(nullptr);
	DelayTime*	pDelay(nullptr);
	Sequence*	pSequence(nullptr);

	pCall		= CallFunc::create(std::bind(&C_PlayScene::callEvent, this));
	pDelay		= DelayTime::create(0.1f);
	pSequence	= Sequence::create(pDelay, pCall, nullptr);

	runAction(pSequence);
}

void C_PlayScene::createItem()
{
	for (int nItem(0); nItem < 500; nItem++)
	{
		C_Item* pItem(nullptr);

		pItem = C_Item::create();
		
		pItem->setScale(0.6f);
		pItem->setTextureWithRect("Item_32x32.png", Rect(0.0f, 0.0f, 32.0f, 32.0f));

		m_pItemManager->addItem(pItem);
	}
}

void C_PlayScene::createPopup()
{
	m_pPopup = C_PausePopup::create();

	m_pPopup->setTitle("PauseMenuTitle.png");
	m_pPopup->setTexture("Popup_BG.png");
	m_pPopup->addMenuItem("PauseMenu/ReturnToGame.png");
	m_pPopup->addMenuItem("PauseMenu/ReturnToMenu.png");
	m_pPopup->addMenuItem("PauseMenu/SaveReplay.png");
	m_pPopup->addMenuItem("PauseMenu/Manual.png");
	m_pPopup->addMenuItem("PauseMenu/StageRestart.png");
	m_pPopup->setMenuHeight(-60.0f);
	m_pPopup->getTitle()->setPosition(300.0f, 428.0f);
}

void C_PlayScene::createEnemy()
{
	for (int nEnemy(0); nEnemy < 50; nEnemy++)
	{
		C_Enemy* pEnemy(nullptr);

		pEnemy = C_Enemy::create();

		pEnemy->setTextureWithRect("Enemy_Fairy.png", Rect(0.0f, 0.0f, 60.0f, 54.0f));

		pEnemy->addAnimationWithRects(Rect(0.0f, 0.0f, 60.0f, 54.0f), 5, 0.2f);
		pEnemy->addAnimationWithRects(Rect(0.0f, 54.0f, 60.0f, 54.0f), 5, 0.2f);
		pEnemy->addAnimationWithRects(Rect(0.0f, 108.0f, 60.0f, 54.0f), 5, 0.2f);
		pEnemy->addAnimationWithRects(Rect(0.0f, 162.0f, 60.0f, 54.0f), 5, 0.2f);

		m_pEnemyManager->addEnemy(pEnemy, E_USE_TYPE::E_NOT_USED);
	}
}

void C_PlayScene::createDanmaku()
{
	for (int nDanmaku(0); nDanmaku < 2000; nDanmaku++)
	{
		C_Danmaku* pDanmaku(nullptr);

		pDanmaku = C_Danmaku::create();

		pDanmaku->setDamage(1);
		pDanmaku->setTextureWithRect("Danmaku.png", Rect(0.0f, 0.0f, 56.0f, 56.0f));

		m_pDanmakuManager->addDanmaku(pDanmaku);
	}
}

void C_PlayScene::createScroll()
{
	m_pScrollView = C_2DScrollView::create("Field_Texture_01.png", 6);

	m_pScrollView->createByTexture("cloud.png", 10, E_SCROLL::E_CLOUD, 200.0f);
	m_pScrollView->createFilterByTexture("Filter.png");
	m_pScrollView->setEnabled(true);
	m_pScrollView->setRotateByCamera(30.0f, 0.0f, 0.0f);
	m_pScrollView->setSpeed(1.0f, E_SCROLL::E_BG);
	m_pScrollView->setSpeed(1.0f, E_SCROLL::E_CLOUD);
	m_pScrollView->setCloudSpawnType(E_CLOUD_TYPE::E_NORMAL);
}

void C_PlayScene::createController()
{
	m_pPlayerController = C_PlayerController::create();
	
	m_pPlayerController->setTexture("Player.png");
	m_pPlayerController->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	m_pPlayerController->setPosition(640.0f, 100.0f);
	m_pPlayerController->setEnabled(true);
}

void C_PlayScene::createWeaponLauncher()
{
	m_pWLauncher = C_WeaponLauncher::create("Launcher.png");

	m_pWLauncher->setMaxWeaponCount(4);
	m_pWLauncher->setWeaponCount(1);
}

void C_PlayScene::callEvent()
{
	m_pFieldManager->setEnabled(true);
}

void C_PlayScene::createWeaponManager()
{
	m_pWeaponManager = C_WeaponManager::create();

	m_pWeaponManager->setWeaponFile("bullet.png", E_WEAPON_TYPE::E_NORMAL);
	m_pWeaponManager->setWeaponFile("SlowMode_Colision.png", E_WEAPON_TYPE::E_SUB);

	m_pWeaponManager->createWeapon(E_WEAPON_TYPE::E_NORMAL, 500);
	m_pWeaponManager->createWeapon(E_WEAPON_TYPE::E_SUB, 500);

	m_pWeaponManager->setEnabled(true);
}

void C_PlayScene::createTalkManager()
{
	m_pTalkManager = C_TalkManager::create();

	m_pTalkManager->addEventCount(4);
	m_pTalkManager->addEventCount(11);
	m_pTalkManager->addEventCount(22);
	m_pTalkManager->addEventCount(40);
	m_pTalkManager->addEventCount(45);
	m_pTalkManager->addEventCount(999999999);
	m_pTalkManager->setTextBox("TextBox.png");
	m_pTalkManager->setSCGAtlas("Player_SCG.png", Size(259.0f, 522.0f), 0);
	m_pTalkManager->setSCGAtlas("BossSCG.png", Size(652.0f, 627.0f), 1);
	m_pTalkManager->setDialogueFont("fonts/NotoSansCJKkr-Bold.otf");
	m_pTalkManager->presetDialouge("Stage_01_Dialogue.txt");
}
