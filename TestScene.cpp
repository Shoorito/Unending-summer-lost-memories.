#include "TestScene.h"
#include "PlayerUI.h"
#include "2DScrollView.h"
#include "ProgressBar.h"
#include "PlayerState.h"
#include "CocosFunctions.h"
#include "ResourceTable.h"
#include "PlayerController.h"
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

	m_pUI = C_PlayerUI::create();

	addChild(m_pKeyManager);
	addChild(m_pScrollView);
	addChild(m_pPlayerController);
	addChild(m_pUI);
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
