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
	m_arUIItem[static_cast<int>(eType)]->setTexture(strItem);
}

void C_PlayerUI::setItemByRect(const std::string & strItem, const Rect & recSize, const E_UI & eType)
{
	m_arUIItem[static_cast<int>(eType)]->setTexture(strItem);
	m_arUIItem[static_cast<int>(eType)]->setTextureRect(recSize);
}

void C_PlayerUI::setGaugeConfig(const Color3B & c3bColor, const E_GAUGE & eType)
{
	float fPercent(0.0f);

	fPercent = m_arUIGauge[static_cast<int>(eType)]->getNowGaugeMeterByPer(0);

	m_arUIGauge[static_cast<int>(eType)]->setGauge(c3bColor, fPercent, 0);
}

void C_PlayerUI::setGaugeConfig(const std::string& strFile, const E_GAUGE & eType)
{
	float fPercent(0.0f);

	fPercent = m_arUIGauge[static_cast<int>(eType)]->getNowGaugeMeterByPer(0);

	m_arUIGauge[static_cast<int>(eType)]->setGauge(strFile, fPercent, 0);
}

void C_PlayerUI::setScoreFontFile(const std::string & strFontFile, const E_SCORE & eType)
{
	if (!FileUtils::getInstance()->isFileExist(strFontFile))
	{
		CCLOG("Font load Error...");
		CCLOG(strFontFile.c_str());
		CCLOG(u8"위 폰트 파일이 존재하지 않습니다.");
		return;
	}

	m_arUIScore[static_cast<int>(eType)]->initWithTTF(strFontFile, "", m_nDefaultFontSize);
}

bool C_PlayerUI::init()
{
	if (!Node::init())
		return false;

	m_nUIScore			= 0;
	m_nDefaultFontSize  = 20;

	return true;
}

void C_PlayerUI::preset()
{
	createItems();
	createGauges();
	createScore();

	presetByGauge();
}

void C_PlayerUI::presetByGauge()
{
	C_PlayerState* pState(nullptr);

	pState = C_PlayerState::getInstance();

	m_arUIGauge[static_cast<int>(E_GAUGE::E_HP)]->setGaugeColor(Color3B(255, 0, 0));
	m_arUIGauge[static_cast<int>(E_GAUGE::E_MP)]->setGaugeColor(Color3B(0, 0, 255));
	m_arUIGauge[static_cast<int>(E_GAUGE::E_POWER)]->setGaugeColor(Color3B(127, 0, 255));

	m_arUIGauge[static_cast<int>(E_GAUGE::E_HP)]->setGaugeMaxCost(pState->getMaxHP());
	m_arUIGauge[static_cast<int>(E_GAUGE::E_MP)]->setGaugeMaxCost(pState->getMaxMP());
	m_arUIGauge[static_cast<int>(E_GAUGE::E_POWER)]->setGaugeMaxCost(pState->getMaxEXP());

	m_arUIGauge[static_cast<int>(E_GAUGE::E_POWER)]->setGaugeCost(0.0f);
}

void C_PlayerUI::createItems()
{
	for (int nItem(0); nItem < static_cast<int>(E_UI::E_MAX); nItem++)
	{
		m_arUIItem[nItem] = Sprite::create();
	}
}

void C_PlayerUI::createGauges()
{
	std::string strGaugeTag("PLAYER_UI_Gauge_0");

	for (int nGauge(0); nGauge < static_cast<int>(E_GAUGE::E_MAX); nGauge++)
	{
		m_arUIGauge[nGauge]  = C_ProgressBar::create();
		strGaugeTag		    += static_cast<char>(48 + nGauge + 1);

		m_arUIGauge[nGauge]->setBackground(Color3B(64, 64, 64), Rect(0.0f, 0.0f, 300.0f, 20.0f));
		m_arUIGauge[nGauge]->setBorder(Color3B(244, 178, 35), strGaugeTag, 3.0f);
		m_arUIGauge[nGauge]->createGauges();

		strGaugeTag.pop_back();
		addChild(m_arUIGauge[nGauge]);
	}
}

void C_PlayerUI::createScore()
{
	m_arUIScore[static_cast<int>(E_SCORE::E_NORMAL)] = Label::create();
	m_arUIScore[static_cast<int>(E_SCORE::E_HIGH)]   = Label::create();
}

void C_PlayerUI::updateScore()
{
	int nCount(C_PlayerState::getInstance()->getScore() - m_nUIScore);

	if (nCount)
	{
		int nSize(0);
		int nSqrt(0);
		int nAdder(0);

		nSize = (int)m_strUIScore.size();
		nSqrt = C_Functions::getDigits(nCount);
		nAdder = C_Functions::getCommaPosition(nSqrt) + nSqrt;

		if (nSize < nAdder)
		{
			C_Functions::updateScoreLength(nAdder, nSize, m_nNowUsedComma, m_strUIScore);
		}
		else
		{
			bool isAdded(false);

			for (int nCheck(nSize - nAdder); nCheck == (nSize - nAdder); nCheck--)
			{
				if (C_Functions::isComma(nCheck, m_strUIScore))
				{
					nAdder++;
				}
				else if (m_strUIScore[nCheck] == ('9' + isAdded))
				{
					m_strUIScore[nCheck] = '0';

					if (!nCheck)
					{
						nCheck = 999999;

						C_Functions::updateScoreLength(nSqrt + 1, nSize, m_nNowUsedComma, m_strUIScore);
					}
					else
					{
						m_strUIScore[nCheck - 1 - C_Functions::isComma(nCheck - 1, m_strUIScore)] += 1;
						isAdded = true;
					}

					nAdder++;
				}
				else if (!isAdded)
				{
					m_strUIScore[nCheck] += 1;
				}
			}
		}

		m_nUIScore += pow(10, nSqrt - 1);

		if (m_nUIScore > C_PlayerState::getInstance()->getHighScore())
		{
			C_PlayerState::getInstance()->setHighScore(m_nUIScore);
			m_arUIScore[static_cast<int>(E_SCORE::E_HIGH)]->setString(m_strUIScore);
		}

		m_arUIScore[static_cast<int>(E_SCORE::E_NORMAL)]->setString(m_strUIScore);
	}
}
