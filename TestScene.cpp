#include "TestScene.h"
#include "2DScroll.h"
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
	m_pScrollView = C_2DScrollView::create("Field_Texture_01.png", 5);

	m_pScrollView->createByTexture("cloud.png", 10, E_SCROLL::E_CLOUD);
	m_pScrollView->createFilterByTexture("Filter.png");
	m_pScrollView->setEnabled(true);
	m_pScrollView->setRotateByCamera(30.0f, 0.0f, 0.0f);
	m_pScrollView->setSpeed(1.0f, E_SCROLL::E_BG);
	m_pScrollView->setSpeed(2.0f, E_SCROLL::E_CLOUD);
	m_pScrollView->setCloudSpawnType(E_CLOUD_TYPE::E_RANDOM);

	Sprite* pSprite(nullptr);

	pSprite = Sprite::create("UI_BG.png");

	pSprite->setPosition(Director::getInstance()->getWinSize() / 2.0f);

	addChild(m_pScrollView);
	addChild(pSprite);
}
