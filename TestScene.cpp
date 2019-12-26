#include "TestScene.h"
#include "PlayerUI.h"
#include "2DScrollView.h"
#include "ProgressBar.h"
#include "PlayerState.h"
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

	m_pScrollView  = nullptr;
	m_pTestScore   = nullptr;
	m_nTestScore   = 0;
	m_nNowUsedComa = 0;
	m_strTestScore = "";

    return true;
}

void C_TestScene::preset()
{
	if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	{
		FileUtils::getInstance()->setWritablePath("C:/cocos2d-x-3.17.1/tools/cocos2d-console/bin/test01/Resources/");
	}
	/*
	testProgress();
	scheduleUpdate();


	addChild(C_KeyEvent_Manager::create());
	*/

	C_PlayerState::create()->setScore(9999999999);

	m_strTestScore = "0";
	m_nTestScore   = 0;
	m_pTestScore   = Label::createWithTTF(m_strTestScore, "fonts/NotoSansCJKkr-Bold.otf", 25);

	m_pTestScore->setPosition(640.0f, 360.0f);
	m_pTestScore->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);

	//testPlayerUI();

	addChild(m_pTestScore);

	schedule(schedule_selector(C_TestScene::update), 0.1f);
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

	addChild(m_pProgress);
}

void C_TestScene::testPlayerUI()
{
	std::string strCode(u8"호텔델루나의장만월사장은구찬성지배인을좋아한다.");
	std::string strFileInfo("");
	std::string strResult("");
	int nCodeCount(0);

	strFileInfo = FileUtils::getInstance()->getStringFromFile("PLAYER_FILE.txt");

	C_Functions::encryptText(strFileInfo, strCode, strResult);

	strFileInfo.clear();
	strFileInfo = FileUtils::getInstance()->getWritablePath() + "PLAYER_FILE.txt";

	FileUtils::getInstance()->writeStringToFile(strResult, strFileInfo);
}

bool C_TestScene::testIsComa(const int nPosition)
{
	return m_strTestScore[nPosition] == ',';
}

void C_TestScene::testUpdateLength(int nAdder, int nSize)
{
	int nChange(0);
	int nComaCount(0);
	std::string strTemp("");

	for (int nText(0); nText < nAdder; nText++)
	{
		strTemp.push_back('0');
	}

	strTemp[0]	= '1';
	nChange		= static_cast<int>(strTemp.size());

	for (int nChanged(0); nChange > g_arInitScore[nChanged]; nChanged++)
	{
		strTemp[nChange - g_arInitScore[nChanged]] = ',';
		nComaCount++;
	}

	nChange--;
	nSize--;

	for (int nLoop(0); nLoop <= nSize; nLoop++)
	{
		if (m_strTestScore[nSize - nLoop] != ',')
		{
			strTemp[nChange - nLoop] = m_strTestScore[nSize - nLoop];
		}
	}

	m_strTestScore = strTemp;
	m_nNowUsedComa = nComaCount;
}

int C_TestScene::testPosComa(const int nSqrt)
{
	int nComa(0);

	while((nSqrt + nComa >= g_arInitScore[nComa]))
	{
		nComa++;
	}

	return nComa;
}

int C_TestScene::testDigits(const int nNumber)
{
	int nDivide(0);
	int nRemain(0);
	int nResult(1);

	nRemain = nNumber % 10; // >> ex. 123456 >> 6
	nDivide = nNumber / 10; // >> ex. 123456 >> 12345

	while (!nRemain)
	{
		nRemain = nDivide % 10; // >> ex. 123456 >> 6
		nDivide /= 10; // >> ex. 123456 >> 12345

		nResult++;
	}

	return nResult;
}

void C_TestScene::update(float dt)
{
	int nCount(C_PlayerState::getInstance()->getScore() - m_nTestScore);

	if (nCount)
	{
		int nSize(0);
		int nSqrt(0);
		int nAdder(0);

		nSqrt  = testDigits(nCount); // 1 => 1, 10 => 2, 100 => 3, 1000 => 4
		nSize  = (int)m_strTestScore.size();
		nAdder = testPosComa(nSqrt) + nSqrt;

		if (nSize < nAdder)
		{
			testUpdateLength(nAdder, nSize);
		}
		else
		{
			bool isAdded(false);

			for (int nCheck(nSize - nAdder); nCheck == (nSize - nAdder); nCheck--)
			{
				if (testIsComa(nCheck))
				{
					nAdder++;
				}
				else if (m_strTestScore[nCheck] == ('9' + isAdded))
				{
					m_strTestScore[nCheck] = '0';

					if (!nCheck)
					{
						nCheck = 999999;

						testUpdateLength(nSqrt + 1, nSize);
					}
					else
					{
						m_strTestScore[nCheck - 1 - testIsComa(nCheck - 1)] += 1;
						isAdded = true;
					}

					nAdder++;
				}
				else if(!isAdded)
				{
					m_strTestScore[nCheck] += 1;
				}
			}
		}

		m_nTestScore += pow(10, nSqrt - 1);

		m_pTestScore->setString(m_strTestScore);
	}
}
