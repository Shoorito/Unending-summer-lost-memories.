#include "TestScene.h"
#include "2DScrollView.h"
#include "ProgressBar.h"
#include "CocosFunctions.h"
#include "ResourceTable.h"
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

	m_pScrollView = nullptr;
	m_nNowpos = 0;

    return true;
}

void C_TestScene::preset()
{
	testProgress();
	scheduleUpdate();

	addChild(C_KeyEvent_Manager::create());
}

void C_TestScene::testFunc()
{
	ClippingNode* pClipNode(nullptr);
	ClippingNode* pClipStencil(nullptr);
	Sprite* pStencil(nullptr);

	pClipStencil = ClippingNode::create();
	pClipNode	 = ClippingNode::create();
	pStencil	 = Sprite::create();
	m_pTarget	 = Sprite::create();

	pClipNode->setStencil(m_pTarget);
	pClipStencil->setStencil(pStencil);

	pClipNode->setPosition(640.0f, 360.0f);

	pClipNode->setAnchorPoint(Vec2(0.5f, 0.5f));
	pClipStencil->setAnchorPoint(Vec2(0.5f, 0.5f));
	pClipStencil->setInverted(true);

	pClipStencil->addChild(m_pTarget);
	pClipNode->addChild(pClipStencil);
	addChild(pClipNode);

	m_pTarget->setColor(Color3B::RED);
	
	pStencil->setTextureRect(Rect(0.0f, 0.0f, 100.0f, 100.0f));
	m_pTarget->setTextureRect(Rect(0.0f, 0.0f, 106.0f, 106.0f));
}

void C_TestScene::testScroll()
{
	m_pScrollView = C_2DScrollView::create("Field_Texture_01.png", 5);

	m_pScrollView->createByTexture("cloud.png", 10, E_SCROLL::E_CLOUD, 300.0f);
	m_pScrollView->createFilterByTexture("Filter.png");
	m_pScrollView->setEnabled(true);
	m_pScrollView->setRotateByCamera(30.0f, 0.0f, 0.0f);
	m_pScrollView->setSpeed(1.0f, E_SCROLL::E_BG);
	m_pScrollView->setSpeed(1.5f, E_SCROLL::E_CLOUD);
	m_pScrollView->setCloudSpawnType(E_CLOUD_TYPE::E_RANDOM);

	Sprite* pSprite(nullptr);

	pSprite = Sprite::create("UI_BG.png");

	pSprite->setPosition(Director::getInstance()->getWinSize() / 2.0f);

	addChild(m_pScrollView);
	addChild(pSprite);
}

void C_TestScene::testProgress()
{
	m_pProgress = C_ProgressBar::create();

	m_pProgress->setBackground(Color3B(64, 64, 64), Rect(0.0f, 0.0f, 300.0f, 25.0f));
	m_pProgress->setBorder(Color3B(244, 178, 35), "TEST_PROGRESS", 3.0f);
	m_pProgress->createGauges(10);

	for (int nProgressHP(0); nProgressHP < 10; nProgressHP++)
	{
		m_pProgress->setGaugeMaxCost(500.0f, nProgressHP);
	}

	m_pProgress->setGauge(Color3B::WHITE,	10.0f, 0);
	m_pProgress->setGauge(Color3B::YELLOW,	10.0f, 1);
	m_pProgress->setGauge(Color3B::MAGENTA,	10.0f, 2);
	m_pProgress->setGauge(Color3B::RED,		10.0f, 3);
	m_pProgress->setGauge(Color3B::WHITE,	10.0f, 4);
	m_pProgress->setGauge(Color3B::BLUE,		10.0f, 5);
	m_pProgress->setGauge(Color3B::GRAY,		10.0f, 6);
	m_pProgress->setGauge(Color3B::GREEN,	10.0f, 7);
	m_pProgress->setGauge(Color3B::ORANGE,	10.0f, 8);
	m_pProgress->setGauge(Color3B::BLACK,	10.0f, 9);

	m_pProgress->setPosition(640.0f, 360.0f);
	m_pProgress->setContentSize(600.0f, 30.0f);
	m_pProgress->setPreloadGauge(15);

	for (int nProgressHP(10); nProgressHP < 15; nProgressHP++)
	{
		m_pProgress->setGaugeMaxCost(500.0f, nProgressHP);
	}

	m_pProgress->setUseGaugeCount(15);

	m_nNowpos = m_pProgress->getGaugeCount() - 1;

	addChild(m_pProgress);
}

void C_TestScene::update(float dt)
{

}
