#include "PlayerUI.h"
#include "CocosFunctions.h"

C_PlayerUI* C_PlayerUI::m_pInstance = nullptr;

C_PlayerUI * C_PlayerUI::create()
{
	if (m_pInstance)
	{
		CCLOG("PlayerUI is Already.");
		
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

void C_PlayerUI::setGazeConfig(const Color3B & c3bColor, const E_GAZE & eType)
{
}

void C_PlayerUI::setGazeConfig(Sprite * pTexture, const E_GAZE & eType)
{
}

void C_PlayerUI::setScoreLabel(const std::string & strFontFile, const E_SCORE & eType)
{
	m_arScore[static_cast<int>(eType)]->initWithTTF(strFontFile, "", 20.0f);
}

void C_PlayerUI::sortItems(const int nStart, const int nEnd, const float fPadding)
{

}

bool C_PlayerUI::init()
{
	if (!Node::init())
		return false;

	return true;
}

void C_PlayerUI::preset()
{
}

void C_PlayerUI::createItems()
{
	for (int nItem(0); nItem < static_cast<int>(E_UI::E_MAX); nItem++)
	{
		m_arItem[nItem] = Sprite::create();
	}
}

void C_PlayerUI::createGaze()
{
	for (int nGaze(0); nGaze < static_cast<int>(E_GAZE::E_MAX); nGaze++)
	{
	}
}

void C_PlayerUI::createScore()
{
}
