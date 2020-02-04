#include "PlayerUI.h"
#include "PlayerState.h"
#include "ProgressBar.h"
#include "ResourceTable.h"
#include "CocosFunctions.h"

C_PlayerUI* C_PlayerUI::m_pInstance = nullptr;

C_PlayerUI * C_PlayerUI::create()
{
	if (m_pInstance)
	{
		CCLOG("PlayerUI is Already.");
		
		return nullptr;
	}

	if (!C_PlayerState::getInstance())
	{
		CCLOG(u8"아직 \"PlayerState\"가 생성되지 않았습니다. \n 다시 시도해 주십시오.");
		
		return nullptr;
	}

	m_pInstance = new(std::nothrow) C_PlayerUI();

	if (m_pInstance && m_pInstance->init())
	{
		m_pInstance->autorelease();
		m_pInstance->preset();

		return m_pInstance;
	}
	else
	{
		C_Functions::safeDelete(m_pInstance);

		return nullptr;
	}
}

void C_PlayerUI::setItem(const std::string& strItem, const E_UI_IMG & eType)
{
	m_arUIItem[static_cast<int>(eType)]->setTexture(strItem);
}

void C_PlayerUI::setItemByRect(const std::string & strItem, const Rect & recSize, const E_UI_IMG & eType)
{
	m_arUIItem[static_cast<int>(eType)]->setTexture(strItem);
	m_arUIItem[static_cast<int>(eType)]->setTextureRect(recSize);
}

void C_PlayerUI::setGaugeConfig(const Color3B & c3bColor, const E_UI_GAUGE & eType)
{
	float fPercent(0.0f);

	fPercent = m_arUIGauge[static_cast<int>(eType)]->getNowGaugeMeterByPer(0);

	m_arUIGauge[static_cast<int>(eType)]->setGauge(c3bColor, fPercent, 0);
}

void C_PlayerUI::setGaugeConfig(const std::string& strFile, const E_UI_GAUGE & eType)
{
	float fPercent(0.0f);

	fPercent = m_arUIGauge[static_cast<int>(eType)]->getNowGaugeMeterByPer(0);

	m_arUIGauge[static_cast<int>(eType)]->setGauge(strFile, fPercent, 0);
}

void C_PlayerUI::setScoreFontFile(const std::string & strFontFile, const E_UI_TITLE & eType)
{
	if (!FileUtils::getInstance()->isFileExist(strFontFile))
	{
		CCLOG("Font load Error...");
		CCLOG(strFontFile.c_str());
		CCLOG(u8"위 폰트 파일이 존재하지 않습니다.");
		return;
	}

	m_arUITitle[static_cast<int>(eType)]->initWithTTF(strFontFile, "", m_nDefaultFontSize);
}

void C_PlayerUI::setEnabled(const bool isEnabled)
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

bool C_PlayerUI::init()
{
	if (!Node::init())
		return false;

	m_nUIScore			= 0;
	m_nNowUsedComma		= 0;
	m_nUIDifficulty		= 0;
	m_nDefaultFontSize  = 20;
	m_strUIScore		= "0";
	m_isEnabled			= false;

	return true;
}

void C_PlayerUI::preset()
{
	createItems();
	createGauges();
	createLabel();

	presetByItems();
	presetByGauge();
	presetByLabel();

	schedule(schedule_selector(C_PlayerUI::update), 0.05f);

	pause();
	setVisible(false);
}

void C_PlayerUI::presetByGauge()
{
	C_PlayerState* pState(nullptr);

	pState = C_PlayerState::getInstance();

	m_arUIGauge[static_cast<int>(E_UI_GAUGE::E_HP)]->setGaugeColor(Color3B::RED);
	m_arUIGauge[static_cast<int>(E_UI_GAUGE::E_MP)]->setGaugeColor(Color3B::BLUE);
	m_arUIGauge[static_cast<int>(E_UI_GAUGE::E_EXP)]->setGaugeColor(Color3B(127, 0, 255));

	m_arUIGauge[static_cast<int>(E_UI_GAUGE::E_HP)]->setGaugeMaxCost(pState->getMaxHP());
	m_arUIGauge[static_cast<int>(E_UI_GAUGE::E_MP)]->setGaugeMaxCost(pState->getMaxMP());
	m_arUIGauge[static_cast<int>(E_UI_GAUGE::E_EXP)]->setGaugeMaxCost(pState->getMaxEXP());

	m_arUIGauge[static_cast<int>(E_UI_GAUGE::E_EXP)]->setGaugeCost(0.0f);

	m_arUIGauge[static_cast<int>(E_UI_GAUGE::E_HP)]->setPosition(1135.0f, 485.0f);
	m_arUIGauge[static_cast<int>(E_UI_GAUGE::E_MP)]->setPosition(1135.0f, 435.0f);
	m_arUIGauge[static_cast<int>(E_UI_GAUGE::E_EXP)]->setPosition(1135.0f, 385.0f);
}

void C_PlayerUI::presetByItems()
{
	float fXpos(0.0f);
	float fYpos(0.0f);

	fXpos = Director::getInstance()->getWinSize().width  / 2.0f;
	fYpos = Director::getInstance()->getWinSize().height / 2.0f;

	m_arUIItem[static_cast<int>(E_UI_IMG::E_BG)]->setTexture("UI_BG.png");
	m_arUIItem[static_cast<int>(E_UI_IMG::E_LOGO)]->setTexture("UI_Logo.png");

	m_arUIItem[static_cast<int>(E_UI_IMG::E_BG)]->setPosition(fXpos, fYpos);
	m_arUIItem[static_cast<int>(E_UI_IMG::E_LOGO)]->setPosition(1135.0f, 200.0f);
}

void C_PlayerUI::presetByLabel()
{
	std::string strHighScore("");

	for (int nLabel(0); nLabel < static_cast<int>(E_UI_TITLE::E_MAX); nLabel++)
	{
		m_arUITitle[nLabel]->initWithTTF("", "fonts/NotoSansCJKkr-Bold.otf", static_cast<float>(m_nDefaultFontSize));
	}

	for (int nScore(0); nScore < static_cast<int>(E_UI_SCORE::E_MAX); nScore++)
	{
		m_arUIScore[nScore]->initWithTTF("", "fonts/NotoSansCJKkr-Bold.otf", static_cast<float>(m_nDefaultFontSize));
	}

	C_Functions::convertToString(C_PlayerState::getInstance()->getHighScore(), strHighScore);

	m_arUITitle[static_cast<int>(E_UI_TITLE::E_DIFFICULTY)]->setString(g_arDifficulty[m_nUIDifficulty]);
	m_arUITitle[static_cast<int>(E_UI_TITLE::E_HIGHSCORE)]->setString("HIGHSCORE");
	m_arUITitle[static_cast<int>(E_UI_TITLE::E_SCORE)]->setString("SCORE");
	m_arUITitle[static_cast<int>(E_UI_TITLE::E_HP)]->setString("HP");
	m_arUITitle[static_cast<int>(E_UI_TITLE::E_MP)]->setString("MP");
	m_arUITitle[static_cast<int>(E_UI_TITLE::E_EXP)]->setString("EXP");

	m_arUIScore[static_cast<int>(E_UI_SCORE::E_SCORE)]->setString("0");
	m_arUIScore[static_cast<int>(E_UI_SCORE::E_HIGHSCORE)]->setString(strHighScore);

	m_arUITitle[static_cast<int>(E_UI_TITLE::E_DIFFICULTY)]->setTTFSize(25.0f);

	m_arUIScore[static_cast<int>(E_UI_SCORE::E_SCORE)]->setTTFSize(25.0f);
	m_arUIScore[static_cast<int>(E_UI_SCORE::E_HIGHSCORE)]->setTTFSize(25.0f);

	m_arUITitle[static_cast<int>(E_UI_TITLE::E_DIFFICULTY)]->setPosition(1135.0f, 675.0f);
	m_arUITitle[static_cast<int>(E_UI_TITLE::E_HIGHSCORE)]->setPosition(1135.0f, 635.0f);
	m_arUITitle[static_cast<int>(E_UI_TITLE::E_SCORE)]->setPosition(1135.0f, 570.0f);
	m_arUITitle[static_cast<int>(E_UI_TITLE::E_HP)]->setPosition(1135.0f, 510.0f);
	m_arUITitle[static_cast<int>(E_UI_TITLE::E_MP)]->setPosition(1135.0f, 460.0f);
	m_arUITitle[static_cast<int>(E_UI_TITLE::E_EXP)]->setPosition(1135.0f, 410.0f);

	m_arUIScore[static_cast<int>(E_UI_SCORE::E_HIGHSCORE)]->setPosition(1135.0f, 602.5f);
	m_arUIScore[static_cast<int>(E_UI_SCORE::E_SCORE)]->setPosition(1135.0f, 540.0f);

	m_arUITitle[static_cast<int>(E_UI_TITLE::E_DIFFICULTY)]->enableOutline(g_arOutlineColor[m_nUIDifficulty], 3);
}

void C_PlayerUI::createItems()
{
	for (int nItem(0); nItem < static_cast<int>(E_UI_IMG::E_MAX); nItem++)
	{
		m_arUIItem[nItem] = Sprite::create();

		addChild(m_arUIItem[nItem]);
	}
}

void C_PlayerUI::createGauges()
{
	std::string strGaugeTag("PLAYER_UI_Gauge_0");

	for (int nGauge(0); nGauge < static_cast<int>(E_UI_GAUGE::E_MAX); nGauge++)
	{
		m_arUIGauge[nGauge]  = C_ProgressBar::create();
		strGaugeTag		    += static_cast<char>(48 + nGauge + 1);

		m_arUIGauge[nGauge]->setBackground(Color3B(64, 64, 64), Rect(0.0f, 0.0f, 217.0f, 20.0f));
		m_arUIGauge[nGauge]->setBorder(Color3B(244, 178, 35), strGaugeTag, 3.0f);
		m_arUIGauge[nGauge]->createGauges();

		strGaugeTag.pop_back();
		addChild(m_arUIGauge[nGauge]);
	}

	m_arUIGauge[static_cast<int>(E_UI_GAUGE::E_HP)]->setGaugeMaxCost(C_PlayerState::getInstance()->getHP());
	m_arUIGauge[static_cast<int>(E_UI_GAUGE::E_MP)]->setGaugeMaxCost(C_PlayerState::getInstance()->getMP());
	m_arUIGauge[static_cast<int>(E_UI_GAUGE::E_EXP)]->setGaugeMaxCost(C_PlayerState::getInstance()->getMaxEXP());
	m_arUIGauge[static_cast<int>(E_UI_GAUGE::E_EXP)]->setGaugeCost(0);
}

void C_PlayerUI::createLabel()
{
	for (int nLabel(0); nLabel < static_cast<int>(E_UI_TITLE::E_MAX); nLabel++)
	{
		m_arUITitle[nLabel] = Label::create();

		addChild(m_arUITitle[nLabel]);
	}

	for (int nScore(0); nScore < static_cast<int>(E_UI_SCORE::E_MAX); nScore++)
	{
		m_arUIScore[nScore] = Label::create();
	
		addChild(m_arUIScore[nScore]);
	}
}

void C_PlayerUI::update(float fDelay)
{
	updateScore();
	updatePlayerStatus();
}

void C_PlayerUI::updateScore()
{
	int nCount(C_PlayerState::getInstance()->getScore() - m_nUIScore);

	if (nCount)
	{
		int nSqrt(0);

		nSqrt = C_Functions::getDigits(nCount);

		m_nUIScore += pow(10, nSqrt - 1);

		C_Functions::convertToString(m_nUIScore, m_strUIScore);

		if (m_nUIScore > C_PlayerState::getInstance()->getHighScore())
		{
			C_PlayerState::getInstance()->setHighScore(m_nUIScore);
			m_arUIScore[static_cast<int>(E_UI_SCORE::E_HIGHSCORE)]->setString(m_strUIScore);
		}

		m_arUIScore[static_cast<int>(E_UI_SCORE::E_SCORE)]->setString(m_strUIScore);
	}
}

void C_PlayerUI::updatePlayerStatus()
{
	C_PlayerState* pStatus(nullptr);

	pStatus = C_PlayerState::getInstance();

	m_arUIGauge[static_cast<int>(E_UI_GAUGE::E_HP)]->setGaugeCost(pStatus->getHP());
	m_arUIGauge[static_cast<int>(E_UI_GAUGE::E_MP)]->setGaugeCost(pStatus->getMP());
	m_arUIGauge[static_cast<int>(E_UI_GAUGE::E_EXP)]->setGaugeCost(pStatus->getEXP());
}
