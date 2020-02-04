#include "EnemyPatterns.h"
#include "AudioEngine.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "Danmaku.h"
#include "DanmakuManager.h"

using namespace experimental;

C_EnemyPatterns * C_EnemyPatterns::m_pInstance = nullptr;

C_EnemyPatterns * C_EnemyPatterns::create()
{
	if (m_pInstance)
	{
		CCLOG(u8"이미 \"C_EnemyPatterns\"가 생성되어 있습니다.");

		return nullptr;
	}

	m_pInstance = new(std::nothrow) C_EnemyPatterns();

	return m_pInstance;
}

void C_EnemyPatterns::circleNWay(const Vec2& vecStartpos, const int nWayCount, const float fStartAngle, const float fSpeed, const float fScale, const Rect& recUseTexture)
{
	float fAngle(0.0f);
	C_DanmakuManager* pManager(nullptr);

	pManager = C_DanmakuManager::getInstance();
	fAngle	 = fStartAngle;

	for (int nWay(0); nWay < nWayCount; nWay++)
	{
		C_Danmaku*	pTarget(nullptr);
		Sprite*		pTexture(nullptr);

		pTarget  = pManager->popDanmaku(E_USE_TYPE::E_NOT_USED);
		pTexture = pTarget->getTexture();

		if (!pTarget)
			return;

		pTarget->setUseType(E_USE_TYPE::E_USED);
		
		pManager->pushDanmaku(pTarget);

		pTexture->setPosition(vecStartpos);
		pTexture->setTextureRect(recUseTexture);
		pTexture->setScale(fScale);
		pTarget->setSpeed(fSpeed);
		pTarget->setAngle(fAngle);
		pTarget->setEnabled(true);

		fAngle += 360.0f / static_cast<float>(nWayCount);
	}

	//AudioEngine::play2d("se_tan00.mp3", false, 0.01f);
}

void C_EnemyPatterns::summon(const Vec2& vecSummonpos)
{
	C_Enemy* pEnemy(nullptr);
	C_EnemyManager* pManager(nullptr);

	pManager = C_EnemyManager::getInstance();
	pEnemy	 = pManager->getCursor(E_USE_TYPE::E_NOT_USED);

	pEnemy->setType(E_ENEMY_TYPE::E_SUMMONER);

	pEnemy->setPosition(vecSummonpos.x + random(-300, 300), vecSummonpos.y);
	pEnemy->setAttackType(0);
	pEnemy->setHP(300.0f);

	pManager->changeEnemy(pEnemy, E_USE_TYPE::E_NOT_USED);
}

void C_EnemyPatterns::aimingBoom(const Vec2& vecStartpos, const float fAngle, const float fSpeed, const Rect& recUseTexture)
{
	C_DanmakuManager* pManager(nullptr);
	C_Danmaku* pTarget(nullptr);
	DelayTime* pDelay(nullptr);
	ScaleTo*   pScale(nullptr);
	Sequence*  pSequance(nullptr);

	pManager  = C_DanmakuManager::getInstance();
	pTarget   = pManager->getCursor(E_USE_TYPE::E_NOT_USED);
	pDelay	  = DelayTime::create(1.5f);
	pScale	  = ScaleTo::create(1.0f, 3.0f);
	pSequance = Sequence::create(pDelay, pScale, nullptr);

	pTarget->setPosition(vecStartpos);
	pTarget->setScale(0.5f);
	pTarget->setAngle(fAngle);
	pTarget->setSpeed(fSpeed);
	pTarget->getTexture()->setTextureRect(recUseTexture);
	pTarget->runAction(pSequance);

	AudioEngine::play2d("se_boon01.mp3", false, 0.1f);
}
