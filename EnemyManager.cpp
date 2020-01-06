#include "EnemyManager.h"
#include "CocosFunctions.h"

C_EnemyManager * C_EnemyManager::m_pInstance = nullptr;

C_EnemyManager * C_EnemyManager::create()
{
	if (m_pInstance)
	{
		CCLOG(u8"\"WeaponManager\"가 이미 생성 되어 있습니다.");

		return nullptr;
	}

	m_pInstance = new(std::nothrow) C_EnemyManager();

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

bool C_EnemyManager::init()
{
	if (!Node::init())
		return false;

	for (int nVector(0); nVector < static_cast<int>(E_USE_TYPE::E_MAX); nVector++)
	{
		m_arEnemyList[nVector].clear();
	}

	return true;
}

void C_EnemyManager::preset()
{

}
