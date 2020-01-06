#include "PlayScene.h"
#include "CocosFunctions.h"

C_PlayScene * C_PlayScene::m_pInstance = nullptr;

C_PlayScene * C_PlayScene::create()
{
	if (m_pInstance)
	{
		CCLOG(u8"\"PlayScene\"은 이미 생성되어 있는 \"싱글톤 계열 클래스\"입니다.");
		CCLOG(u8"해당 클래스는 다중 생성 할 수 없습니다.");

		return nullptr;
	}

	m_pInstance = new(std::nothrow) C_PlayScene();

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

bool C_PlayScene::init()
{
	if (!Layer::init())
		return false;

	m_recWinArea = Rect::ZERO;

	return true;
}

void C_PlayScene::preset()
{
	m_recWinArea.setRect(290.0f, 25.0f, 700.0f, 670.0f);
}
