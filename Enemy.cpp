#include "Enemy.h"
#include "PlayerController.h"
#include "CocosFunctions.h"
#include "EnemyManager.h"
#include "EnemyPatterns.h"
#include "ResourceTable.h"

C_Enemy * C_Enemy::create()
{
	C_Enemy* pEnemy(nullptr);

	pEnemy = new(std::nothrow) C_Enemy();

	if (pEnemy && pEnemy->init())
	{
		pEnemy->preset();
	}
	else
	{
		C_Functions::safeDelete(pEnemy);
	}

	return pEnemy;
}

void C_Enemy::initMovement()
{
	m_fSpinAngle	= 0.0f;
	m_fAngle		= 0.0f;
	m_fSpinRadius	= 0.0f;
	m_isSpinFilped	= false;

	m_vecSpinPivot.setZero();
}

void C_Enemy::addAnimationWithFiles(const std::vector<std::string>& vecFiles, const float fDelay)
{
	if (!static_cast<int>(vecFiles.size()))
		return;

	int			nCount(0);
	C_Enemy*	pEnemy(nullptr);
	Animation*	pAnim(nullptr);
	Animate*	pAnimate(nullptr);
	Repeat*		pRepeat(nullptr);

	pAnim  = Animation::create();
	nCount = static_cast<int>(vecFiles.size());

	pAnim->setDelayPerUnit(fDelay);

	for (int nAnim(0); nAnim < nCount; nAnim++)
	{
		pAnim->addSpriteFrameWithFile(vecFiles[nAnim]);
	}

	pAnimate = Animate::create(pAnim);
	pRepeat  = Repeat::create(pAnimate, -1);

	pRepeat->retain();

	pEnemy->m_vecAnim.emplace_back(pRepeat);
}

void C_Enemy::addAnimationWithAtlas(const std::string & strFile, const Rect & recSize, const int nCount, const float fDelay)
{
	if (strFile == "" || nCount < 1 || fDelay < 0.01f)
		return;

	Rect		recAnim(recSize);
	Animation*	pAnim(nullptr);
	Animate*	pAnimate(nullptr);
	Repeat*		pRepeat(nullptr);

	pAnim = Animation::create();

	pAnim->setDelayPerUnit(fDelay);

	Sprite* pSprite(nullptr);

	pSprite = Sprite::create(strFile);

	for (int nAnim(0); nAnim < nCount; nAnim++)
	{
		pSprite->setTextureRect(recAnim);

		pAnim->addSpriteFrame(pSprite->getSpriteFrame());

		recAnim.setRect
		(
			recAnim.origin.x + recSize.size.width,
			recAnim.origin.y,
			recSize.size.width,
			recSize.size.height
		);
	}

	pAnimate = Animate::create(pAnim);
	pRepeat  = Repeat::create(pAnimate, -1);

	pRepeat->retain();

	m_vecAnim.emplace_back(pRepeat);
}

void C_Enemy::addAnimationWithRects(const Rect & recSize, const int nCount, const float fDelay)
{
	if (recSize.equals(Rect::ZERO) || nCount < 1 || fDelay < 0.01f)
		return;

	Rect		recAnim(recSize);
	Animation*	pAnim(nullptr);
	Animate*	pAnimate(nullptr);
	Repeat*		pRepeat(nullptr);

	pAnim = Animation::create();

	pAnim->setDelayPerUnit(fDelay);
	
	for (int nAnim(0); nAnim < nCount; nAnim++)
	{
		pAnim->addSpriteFrameWithTexture(getTexture(), recAnim);

		recAnim.origin.x += recSize.size.width;
	}

	pAnimate = Animate::create(pAnim);
	pRepeat  = Repeat::create(pAnimate, -1);

	pRepeat->retain();

	m_vecAnim.emplace_back(pRepeat);
}

Repeat * C_Enemy::getAnimation(const int nPosition) const
{
	if (nPosition < 0 || nPosition >= static_cast<int>(m_vecAnim.size()))
	{
		CCLOG(u8"입력한 값이 \"Out of Range\" 입니다.");

		return nullptr;
	}

	return m_vecAnim[nPosition];
}

void C_Enemy::setHP(const int nHP)
{
	if (nHP <= 0)
	{
		m_nHP = 0;

		stopAllActions();
		setEnabled(false);
		C_EnemyManager::getInstance()->changeEnemy(this, E_USE_TYPE::E_NOT_USED);
	}

	m_nHP = nHP;
}

void C_Enemy::addHP(const int nHP)
{
	if (!nHP)
		return;

	if ((m_nHP + nHP) < 0)
	{
		setHP(0);

		return;
	}

	m_nHP += nHP;
}

void C_Enemy::setAttackType(const int nType)
{
	if (nType < 0)
		return;

	m_nAttackType = nType;
}

void C_Enemy::setEnabled(const bool isEnabled)
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

void C_Enemy::startAnimation(const int nType)
{
	int		nSize(0);
	Repeat*	pRepeat(nullptr);

	nSize = static_cast<int>(m_vecAnim.size());

	if (!nSize || nSize < nType || nType < 0)
		return;

	pRepeat = m_vecAnim[nType]->clone();

	pRepeat->retain();

	stopAllActions();
	runAction(pRepeat);
}

void C_Enemy::setSpinMovement(const float fAngle, const float fRadius, const float fStartAngle, const Vec2& vecSpinPivot, const bool isFilped)
{
	m_fAngle	   = fStartAngle;
	m_fSpinAngle   = fAngle;
	m_fSpinRadius  = fRadius;
	m_vecSpinPivot = vecSpinPivot;
	m_isSpinFilped = isFilped;
}

void C_Enemy::setTextureWithRect(const std::string & strFile, const Rect & recSprite)
{
	setTexture(strFile);
	setTextureRect(recSprite);
}

bool C_Enemy::init()
{
	if (!Sprite::init())
		return false;

	m_eType			= E_ENEMY_TYPE::E_NORMAL;
	m_nHP			= 0.0f;
	m_fSpinAngle	= 0.0f;
	m_fAngle		= 0.0f;
	m_fSpinRadius	= 0.0f;
	m_nUpdateCount	= 0;
	m_nAttackType	= 0;
	m_isEnabled		= false;
	m_isSpinFilped  = false;
	m_pPrev			= nullptr;
	m_pNext			= nullptr;

	m_vecAnim.clear();
	m_vecSpinPivot.setZero();

	return true;
}

void C_Enemy::preset()
{
	presetPattern();

	setVisible(false);

	schedule(schedule_selector(C_Enemy::update), 0.01f);

	pause();
}

void C_Enemy::presetPattern()
{
	m_arPattern[0] = &C_Enemy::pattern01;
	m_arPattern[1] = &C_Enemy::pattern02;
	m_arPattern[2] = &C_Enemy::pattern03;
	m_arPattern[3] = &C_Enemy::pattern04;
	m_arPattern[4] = &C_Enemy::pattern05;
	m_arPattern[5] = &C_Enemy::pattern06;
	m_arPattern[6] = &C_Enemy::pattern07;
	m_arPattern[7] = &C_Enemy::pattern08;
}

void C_Enemy::setUpdateCount(const int nCount)
{
	m_nUpdateCount = nCount;
}

void C_Enemy::addUpdateCount(const int nCount)
{
	m_nUpdateCount += nCount;
}

void C_Enemy::update(float fDelay)
{
	if (m_nUpdateCount >= 1000000000)
		m_nUpdateCount = 0;

	if (m_fSpinAngle)
		updateSpinMover();

	(this->*m_arPattern[m_nAttackType])(m_nUpdateCount);

	m_nUpdateCount++;
}

void C_Enemy::updateSpinMover()
{
	if(m_fAngle == m_fSpinAngle)
	{
		m_fSpinAngle	= 0.0f;
		m_fAngle		= 0.0f;
		m_fSpinRadius	= 0.0f;
		m_isSpinFilped  = false;
		m_vecSpinPivot.setZero();

		return;
	}

	setPosition(m_vecSpinPivot);
	addPositionX(cosf(-m_fAngle * 3.141592 / 180.0f) * m_fSpinRadius);
	addPositionY(sinf(-m_fAngle * 3.141592 / 180.0f) * m_fSpinRadius);

	m_fAngle += 1.0f + (-2.0f * m_isSpinFilped);
}

void C_Enemy::pattern01(const int nCount)
{
	if (nCount % 50 != 0)
		return;

	Rect  recDanmaku(Rect::ZERO);
	float fAngle(0.0f);

	fAngle = C_Functions::getHomingAngle(getPosition(), C_PlayerController::getInstance()->getPosition());

	recDanmaku.setRect
	(
		0.0f,
		0.0f,
		g_arDanmakuXSize[static_cast<int>(E_DANMAKU::E_CIRCLE)],
		g_arDanmakuYSize[static_cast<int>(E_DANMAKU::E_CIRCLE)]
	);

	C_EnemyPatterns::getInstance()->circleNWay(getPosition(), 1, fAngle, 4.0f, 0.5f, recDanmaku);
}

void C_Enemy::pattern02(const int nCount)
{
}

void C_Enemy::pattern03(const int nCount)
{
}

void C_Enemy::pattern04(const int nCount)
{
}

void C_Enemy::pattern05(const int nCount)
{
}

void C_Enemy::pattern06(const int nCount)
{
}

void C_Enemy::pattern07(const int nCount)
{
}

void C_Enemy::pattern08(const int nCount)
{
}
