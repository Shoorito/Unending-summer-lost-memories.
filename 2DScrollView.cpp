#include "2DScrollView.h"
#include "CocosFunctions.h"

C_2DScrollView* C_2DScrollView::m_pInstance = nullptr;

C_2DScrollView * C_2DScrollView::create()
{
	if (m_pInstance)
	{
		CCLOG("ScrollView is Already.");

		return nullptr;
	}

	m_pInstance = new(std::nothrow) C_2DScrollView();

	if (m_pInstance && m_pInstance->init())
	{
		m_pInstance->autorelease();
		m_pInstance->preset();
	}
	else
	{
		C_Functions::safeDelete(m_pInstance);
	}

	return m_pInstance;
}

C_2DScrollView * C_2DScrollView::create(const std::string& strTexture, const int nCount)
{
	if (m_pInstance)
	{
		CCLOG("ScrollView is Already.");

		return nullptr;
	}

	m_pInstance = new(std::nothrow) C_2DScrollView();

	if (m_pInstance && m_pInstance->init())
	{
		m_pInstance->autorelease();
		m_pInstance->preset();
		m_pInstance->createByTexture(strTexture, nCount, E_SCROLL::E_BG);
	}
	else
	{
		C_Functions::safeDelete(m_pInstance);
	}

	return m_pInstance;
}

void C_2DScrollView::setCameraMask(const unsigned short unMaskTag, const bool isApplyChildren)
{
	if ((unMaskTag < 1) || (unMaskTag > static_cast<int>(CameraFlag::USER8)))
	{
		return;
	}

	if (m_pFilter != nullptr)
	{
		m_pFilter->setCameraMask(unMaskTag, isApplyChildren);
	}

	for (int nTypes(0); nTypes < static_cast<int>(E_SCROLL::E_MAX); nTypes++)
	{
		for (int nItems(0); nItems < m_arItemCount[nTypes]; nItems++)
		{
			m_arItemList[nTypes][nItems]->setCameraMask(unMaskTag, isApplyChildren);
		}
	}
}

void C_2DScrollView::setRotateByCamera(const float fXAngle, const float fYAngle, const float fZAngle)
{
	m_vecCameraAngle.set(fXAngle, fYAngle, fZAngle);

	m_pCamera->setRotation3D(m_vecCameraAngle);
}

void C_2DScrollView::setEnabled(const bool isEnabled)
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

void C_2DScrollView::createByTexture(const std::string& strTexture, const int nTextureCount, const E_SCROLL& eType, const float fZpos)
{
	if (strTexture == "" || nTextureCount < 1 || m_arItemCount[static_cast<int>(eType)] > 0)
		return;

	Vec3* pUpdatepos(nullptr);

	while (m_arItemCount[static_cast<int>(eType)] != nTextureCount)
	{
		Sprite* pSprite(nullptr);

		pSprite = Sprite::create(strTexture);
		
		pSprite->setPositionZ(fZpos);

		createItem(pSprite, static_cast<int>(eType));
	}

	pUpdatepos = &m_arUpdatepos[static_cast<int>(eType)];

	pUpdatepos->set(m_arItemList[static_cast<int>(eType)].back()->getPosition3D());
}

void C_2DScrollView::createFilterByTexture(const std::string& strTexture)
{
	if (m_pFilter)
		return;

	m_pFilter = Sprite::create(strTexture);

	m_pFilter->setPosition(Director::getInstance()->getWinSize() / 2.0f);

	addChild(m_pFilter);
}

void C_2DScrollView::createItem(Sprite* pSprite, const int& nType)
{
	bool isFilped(false);

	isFilped = (m_arItemCount[nType] % 2) == 1;

	pSprite->setCameraMask(static_cast<unsigned short>(m_eCameraFlag));
	pSprite->setFlippedX(isFilped);

	if (m_arItemCount[nType] > 0)
	{
		pSprite->setPosition(m_arItemList[nType][m_arItemCount[nType] - 1]->getPosition());
		pSprite->addPosition(0.0f, pSprite->getContentSize().height);
		pSprite->addPosition(0.0f, -5.0f);
	}

	m_arItemList[nType].emplace_back(pSprite);

	addChild(pSprite);

	m_arItemCount[nType]++;
}

void C_2DScrollView::setTextureByRoute(const char* arRoute, const E_SCROLL& eType)
{
	for (int nCount(0); nCount < m_arItemCount[static_cast<int>(eType)]; nCount++)
	{
		m_arItemList[static_cast<int>(eType)][nCount]->setTexture(arRoute);
	}
}

void C_2DScrollView::setTextureCount(const int nTextureCount, const E_SCROLL & eType)
{
	if (nTextureCount < 1 || m_arItemCount[static_cast<int>(eType)] < 1)
		return;

	int nItemCount(m_arItemCount[static_cast<int>(eType)]);

	while (m_arItemCount[static_cast<int>(eType)] != nTextureCount)
	{
		Sprite* pSprite(nullptr);

		if (nItemCount < nTextureCount)
		{
			pSprite = Sprite::createWithSpriteFrame(m_arItemList[static_cast<int>(eType)][0]->getSpriteFrame());

			createItem(pSprite, static_cast<int>(eType));
		}
		else
		{
			pSprite = m_arItemList[static_cast<int>(eType)].back();

			m_arItemList[static_cast<int>(eType)].pop_back();

			removeChild(pSprite);

			m_arItemCount[static_cast<int>(eType)]--;
		}
	}
}

void C_2DScrollView::setUpdateDelay(const float & fDelay)
{
	TimerTargetSelector* pSelector(nullptr);

	m_fDelaytime = fDelay;

	pSelector = getScheduler()->getSchedule(m_selUpdateFunction, this);

	pSelector->setupTimerWithInterval(m_fDelaytime, 0xffffffff - 1, 0.0f);
}

bool C_2DScrollView::init()
{
	if (!Node::init())
		return false;

	m_pCamera			= nullptr;
	m_pFilter			= nullptr;
	m_selUpdateFunction = nullptr;
	m_isNowUpdated		= false;
	m_isEnabled			= false;
	m_fDelaytime		= 0.0f;
	m_fUpdateYpos		= -720.0f;
	m_eCloudType		= E_CLOUD_TYPE::E_NORMAL;
	m_eCameraFlag		= CameraFlag::USER1;

	return true;
}

void C_2DScrollView::onEnter()
{
	Node::onEnter();

	if (!m_isEnabled)
		pause();
	else
		resume();
	
	setVisible(m_isEnabled);
}

void C_2DScrollView::preset()
{
	createCamera();

	m_selUpdateFunction = schedule_selector(C_2DScrollView::update);
	m_fDelaytime		= 0.001f;

	schedule(m_selUpdateFunction, m_fDelaytime);
}

void C_2DScrollView::createCamera()
{
	Size szWinSize(Size::ZERO);
	float fLookXpos(0.0f);
	float fLookYpos(0.0f);

	szWinSize = Director::getInstance()->getWinSize();
	fLookXpos = szWinSize.width / 2.0f;
	fLookYpos = szWinSize.height / 2.0f;
	m_pCamera = Camera::createPerspective(60.0f, szWinSize.width / szWinSize.height, 1.0f, 2000.0f);

	m_pCamera->setCameraFlag(CameraFlag::USER1);
	m_pCamera->setPosition3D(Vec3(0.0f, 0.0f, Director::getInstance()->getZEye() + 100.0f));
	m_pCamera->lookAt(Vec3::ZERO, Vec3(0.0f, 1.0f, 0.0f));

	addChild(m_pCamera);
}

void C_2DScrollView::update(float dt)
{
	if (m_isNowUpdated)
		return;

	m_isNowUpdated = true;

	std::vector<Sprite*>* pVector(nullptr);
	Sprite* pSprite(nullptr);

	pVector = &m_arItemList[static_cast<int>(E_SCROLL::E_BG)];

	for (int nCount(0); nCount < m_arItemCount[static_cast<int>(E_SCROLL::E_BG)]; nCount++)
	{
		pSprite = pVector->at(nCount);

		if (pSprite->getPosition3D().y <= m_fUpdateYpos)
		{
			pSprite->setPosition3D(m_arUpdatepos[static_cast<int>(E_SCROLL::E_BG)]);
		}

		pSprite->addPosition3D(m_arMover[static_cast<int>(E_SCROLL::E_BG)]);
	}

	pVector = &m_arItemList[static_cast<int>(E_SCROLL::E_CLOUD)];

	for (int nCount(0); nCount < m_arItemCount[static_cast<int>(E_SCROLL::E_CLOUD)]; nCount++)
	{
		pSprite = pVector->at(nCount);

		if (pSprite->getPosition3D().y <= m_fUpdateYpos)
		{
			if (m_eCloudType == E_CLOUD_TYPE::E_RANDOM)
			{
				m_arUpdatepos[static_cast<int>(E_SCROLL::E_CLOUD)].x = random(-350.0f, 350.0f);
			}
			else if (m_arUpdatepos[static_cast<int>(E_SCROLL::E_CLOUD)].x != 0.0f)
			{
				m_arUpdatepos[static_cast<int>(E_SCROLL::E_CLOUD)].x = 0.0f;
			}

			pSprite->setPosition3D(m_arUpdatepos[static_cast<int>(E_SCROLL::E_CLOUD)]);
		}

		pSprite->addPosition3D(m_arMover[static_cast<int>(E_SCROLL::E_CLOUD)]);
	}

	m_isNowUpdated = false;
}
