#include "PlayScene.h"
#include "CocosFunctions.h"

C_PlayScene * C_PlayScene::m_pInstance = nullptr;

C_PlayScene * C_PlayScene::create()
{
	if (m_pInstance)
	{
		CCLOG(u8"\"PlayScene\"�� �̹� �����Ǿ� �ִ� \"�̱��� �迭 Ŭ����\"�Դϴ�.");
		CCLOG(u8"�ش� Ŭ������ ���� ���� �� �� �����ϴ�.");

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
