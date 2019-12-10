#include "TestScene.h"
#include "2DScrollView.h"
#include "CocosFunctions.h"
#include "ResourceTable.h"

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

	m_pScrollView	= nullptr;

    return true;
}

void C_TestScene::preset()
{
	/*
	m_pScrollView = C_2DScrollView::create("Field_Texture_01.png", 5);

	m_pScrollView->createByTexture("cloud.png", 10, E_SCROLL::E_CLOUD, 500.0f);
	m_pScrollView->createFilterByTexture("Filter.png");
	m_pScrollView->setEnabled(true);
	m_pScrollView->setRotateByCamera(30.0f, 0.0f, 0.0f);
	m_pScrollView->setSpeed(1.0f, E_SCROLL::E_BG);
	m_pScrollView->setSpeed(0.5f, E_SCROLL::E_CLOUD);
	m_pScrollView->setCloudSpawnType(E_CLOUD_TYPE::E_RANDOM);
	
	Sprite* pSprite(nullptr);

	pSprite = Sprite::create("UI_BG.png");

	pSprite->setPosition(Director::getInstance()->getWinSize() / 2.0f);
	pSprite->init();
	pSprite->setColor(Color3B::RED);
	pSprite->setTextureRect(Rect(0.0f, 0.0f, 50.0f, 50.0f));

	//addChild(m_pScrollView);
	addChild(pSprite);
	*/
	testFunc();
}

void C_TestScene::testFunc()
{
	ClippingNode* pClipNode(nullptr);
	ClippingNode* pClipStencil(nullptr);
	Sprite* pStencil(nullptr);

	pClipStencil = ClippingNode::create();
	pClipNode	 = ClippingNode::create();
	pStencil	 = Sprite::create();
	m_pTarget		 = Sprite::create();

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

void C_TestScene::update(float dt)
{
	m_pTarget->addTextureRect(Rect(0.0f, 0.0f, 1.0f, 1.0f));
}
