#include "TestScene.h"
#include "PlayerUI.h"
#include "PlayScene.h"
#include "2DScrollView.h"
#include "ProgressBar.h"
#include "PlayerState.h"
#include "CocosFunctions.h"
#include "ResourceTable.h"
#include "PlayerController.h"
#include "WeaponLauncher.h"
#include "WeaponManager.h"
#include "KeyEventManager.h"

USING_NS_CC;

C_TestScene* C_TestScene::m_pInstance = nullptr;

C_TestScene* C_TestScene::create()
{
	if (m_pInstance)
	{
		CCLOG(u8"이미 메인 씬이 생성되어 있습니다.");

		return nullptr;
	}

	m_pInstance = new(std::nothrow) C_TestScene();

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

bool C_TestScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

	m_pScrollView  = nullptr;
	m_pUI = nullptr;

    return true;
}

void C_TestScene::preset()
{
	if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		FileUtils::getInstance()->setWritablePath("C:/cocos2d-x-3.17.1/tools/cocos2d-console/bin/test01/Resources/");
	}
	
	m_pPlayerState = C_PlayerState::create();

	testKeyEvent();
	testScroll();
	testController();
	testWeaponLauncher();
	testWeaponManager();

	m_pUI = C_PlayerUI::create();

	addChild(m_pKeyManager);
	addChild(m_pScrollView);
	addChild(m_pWeaponManager);
	addChild(m_pPlayerController);
	addChild(m_pWLauncher);
	addChild(m_pUI);
	

	m_pPlayScene = C_PlayScene::create();
	/*
	m_pTarget = Sprite::create("Player.png");
	m_pWeapon = Sprite::create("bullet.png");

	m_fPositionX = 400.0f;
	m_fPositionY = 100.0f;

	m_pTarget->setPosition(640.0f, 650.0f);
	m_pWeapon->setPosition(m_fPositionX, m_fPositionY);

	addChild(m_pWeapon);
	addChild(m_pTarget);
	*/
	addChild(m_pPlayScene);

	schedule(schedule_selector(C_TestScene::update), 0.01f);
}

void C_TestScene::testKeyEvent()
{
	m_pKeyManager = C_KeyEvent_Manager::create();

	m_pKeyManager->setEnabled(true);
}

void C_TestScene::testScroll()
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

void C_TestScene::testController()
{
	m_pPlayerController = C_PlayerController::create();
	
	m_pPlayerController->setTexture("Player.png");
	m_pPlayerController->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	m_pPlayerController->setPosition(640.0f, 360.0f);
	m_pPlayerController->setEnabled(true);
}

void C_TestScene::testWeaponLauncher()
{
	m_pWLauncher = C_WeaponLauncher::create("Launcher.png");

	m_pWLauncher->setMaxWeaponCount(9);
	m_pWLauncher->setWeaponCount(1);
}

void C_TestScene::testWeaponManager()
{
	m_pWeaponManager = C_WeaponManager::create();

	m_pWeaponManager->setWeaponFile("bullet.png", E_WEAPON_TYPE::E_NORMAL);
	m_pWeaponManager->setWeaponFile("SlowMode_Colision.png", E_WEAPON_TYPE::E_SUB);

	m_pWeaponManager->createWeapon(E_WEAPON_TYPE::E_NORMAL, 500);
	m_pWeaponManager->createWeapon(E_WEAPON_TYPE::E_SUB, 500);

	m_pWeaponManager->setEnabled(true);
}

void C_TestScene::testHoming()
{
	float fMoverX(0.0f);
	float fMoverY(0.0f);
	float fShotAngle(0.0f);
	float fRotation(0.0f);

	fMoverX		= m_pTarget->getPositionX();
	fMoverY		= m_pTarget->getPositionY();
	fShotAngle	= atan2f(m_pWeapon->getPositionY() - fMoverY, fMoverX - m_pWeapon->getPositionX());
	fRotation	= fShotAngle * 180.0f / 3.141592f;
	
	m_pWeapon->setRotation(fRotation + 90.0f);
	m_pWeapon->addPositionX(cosf(-fShotAngle) * 1.0f);
	m_pWeapon->addPositionY(sinf(-fShotAngle) * 1.0f);
}

void C_TestScene::update(float dt)
{
	//testHoming();
}
