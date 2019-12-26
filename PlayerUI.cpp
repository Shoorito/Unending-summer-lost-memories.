#include "PlayerUI.h"
#include "PlayerState.h"
#include "ProgressBar.h"
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

void C_PlayerUI::setItem(const std::string& strItem, const E_UI & eType)
{
	m_arItem[static_cast<int>(eType)]->setTexture(strItem);
}

void C_PlayerUI::setItemByRect(const std::string & strItem, const Rect & recSize, const E_UI & eType)
{
	m_arItem[static_cast<int>(eType)]->setTexture(strItem);
	m_arItem[static_cast<int>(eType)]->setTextureRect(recSize);
}

void C_PlayerUI::setGaugeConfig(const Color3B & c3bColor, const E_GAUGE & eType)
{
	float fPercent(0.0f);

	fPercent = m_arGauge[static_cast<int>(eType)]->getNowGaugeMeterByPer(0);

	m_arGauge[static_cast<int>(eType)]->setGauge(c3bColor, fPercent, 0);
}

void C_PlayerUI::setGaugeConfig(Sprite * pTexture, const E_GAUGE & eType)
{
}

void C_PlayerUI::setScoreFont(const std::string & strFontFile, const E_SCORE & eType)
{
	if (!FileUtils::getInstance()->isFileExist(strFontFile))
	{
		CCLOG("Font load Error...");
		CCLOG(strFontFile.c_str());
		CCLOG(u8"위 폰트 파일이 존재하지 않습니다.");
		return;
	}

	m_arScore[static_cast<int>(eType)]->initWithTTF(strFontFile, "", m_nDefaultFontSize);
}

void C_PlayerUI::sortItems(const int nStart, const int nEnd, const float fPadding)
{

}

bool C_PlayerUI::init()
{
	if (!Node::init())
		return false;

	m_nScore			= 0;
	m_nHighScore		= 0;
	m_nDefaultFontSize  = 20;

	return true;
}

void C_PlayerUI::preset()
{
	loadScore();

	createItems();
	createGauges();
	createScore();

	presetByGauge();
}

void C_PlayerUI::presetByGauge()
{
	C_PlayerState* pState(nullptr);

	pState = C_PlayerState::getInstance();

	m_arGauge[static_cast<int>(E_GAUGE::E_HP)]->setGaugeColor(Color3B(255, 0, 0));
	m_arGauge[static_cast<int>(E_GAUGE::E_MP)]->setGaugeColor(Color3B(0, 0, 255));
	m_arGauge[static_cast<int>(E_GAUGE::E_POWER)]->setGaugeColor(Color3B(127, 0, 255));

	m_arGauge[static_cast<int>(E_GAUGE::E_HP)]->setGaugeMaxCost(pState->getMaxHP());
	m_arGauge[static_cast<int>(E_GAUGE::E_MP)]->setGaugeMaxCost(pState->getMaxMP());
	m_arGauge[static_cast<int>(E_GAUGE::E_POWER)]->setGaugeMaxCost(pState->getMaxEXP());

	m_arGauge[static_cast<int>(E_GAUGE::E_POWER)]->setGaugeCost(0.0f);
}

void C_PlayerUI::createItems()
{
	for (int nItem(0); nItem < static_cast<int>(E_UI::E_MAX); nItem++)
	{
		m_arItem[nItem] = Sprite::create();
	}
}

void C_PlayerUI::createGauges()
{
	std::string strGaugeTag("PLAYER_UI_Gauge_0");

	for (int nGauge(0); nGauge < static_cast<int>(E_GAUGE::E_MAX); nGauge++)
	{
		m_arGauge[nGauge]  = C_ProgressBar::create();
		strGaugeTag		  += std::to_string(nGauge + 1);

		m_arGauge[nGauge]->setBackground(Color3B(64, 64, 64), Rect(0.0f, 0.0f, 300.0f, 20.0f));
		m_arGauge[nGauge]->setBorder(Color3B(244, 178, 35), strGaugeTag, 3.0f);
		m_arGauge[nGauge]->createGauges();

		strGaugeTag.pop_back();
		addChild(m_arGauge[nGauge]);
	}
}

void C_PlayerUI::createScore()
{
	m_arScore[static_cast<int>(E_SCORE::E_NORMAL)] = Label::create();
	m_arScore[static_cast<int>(E_SCORE::E_HIGH)]   = Label::create();
}

void C_PlayerUI::loadScore()
{
	std::string strTemp("");
	FileUtils* pFileManager(nullptr);

	pFileManager = FileUtils::getInstance();

	if (pFileManager->isFileExist("Score.txt"))
	{
		strTemp = pFileManager->getStringFromFile("Score.txt");

		if (strTemp == "")
		{
			loadByFirst();
			return;
		}

		std::string strFileInfo("");

		C_Functions::encryptText(strTemp, u8"드라마호텔델루나의엔딩은열린엔딩이지만그래도좋았다", strFileInfo);
	
		for (int nExtract(12); nExtract < static_cast<int>(strFileInfo.size()); nExtract++)
		{
			if (strFileInfo[nExtract] == '\n')
			{
				nExtract = 0xffffffff - 1;
			}
			else
			{
				m_nHighScore *= 10;
				m_nHighScore += static_cast<int>(strFileInfo[nExtract]) - 48;
			}
		}
	}
	else
	{
		loadByFirst();
	}
}

void C_PlayerUI::loadByFirst()
{
	std::string strFirst("");
	std::string strFileInfo("");
	FileUtils*  pFileManager(nullptr);

	strFirst	 = "HighScore : 100000\n";
	m_nHighScore = 100000;

	C_Functions::encryptText(strFirst, u8"드라마호텔델루나의엔딩은열린엔딩이지만그래도좋았다", strFileInfo);

	pFileManager->writeStringToFile(strFileInfo, pFileManager->getWritablePath() + "Score.txt");
}

void C_PlayerUI::upperValue()
{
}
