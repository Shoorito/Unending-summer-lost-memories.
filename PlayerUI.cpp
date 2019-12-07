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

void C_PlayerUI::setItemByRect(const std::string & strFileName, const Rect & recSize, const E_UI & eType)
{
}

void C_PlayerUI::setGaze(C_ProgressBar * pGaze, const E_GAZE & eType)
{
}

void C_PlayerUI::setScoreLabel(const std::string & strFontFile, const E_SCORE & eType)
{
}

void C_PlayerUI::sortItems(const int nStart, const int nEnd)
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
}

void C_PlayerUI::createScore()
{
}
