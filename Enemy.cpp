#include "Enemy.h"
#include "CocosFunctions.h"
#include "EnemyManager.h"

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

	for (int nAnim(0); nAnim < nCount; nAnim++)
	{
		Sprite* pSprite(nullptr);

		pSprite = Sprite::create(strFile);
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

	m_vecAnim.emplace_back(pRepeat);
}

Repeat * C_Enemy::getAnimation(const int nPosition)
{
	if (nPosition < 0 || nPosition >= static_cast<int>(m_vecAnim.size()))
	{
		CCLOG(u8"입력한 값이 \"Out of Range\" 입니다.");

		return nullptr;
	}

	return m_vecAnim[nPosition];
}

void C_Enemy::setHP(const float fHP)
{
	if (fHP <= 0.0f)
	{
		m_fHP = 0.0f;

		setEnabled(false);
		C_EnemyManager::getInstance()->changeEnemy(this, E_USE_TYPE::E_NOT_USED);
	}

	m_fHP = fHP;
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
	m_fHP			= 0.0f;
	m_nUpdateCount	= 0;
	m_isEnabled		= false;

	m_vecAnim.clear();

	return true;
}

void C_Enemy::preset()
{
	setVisible(false);
	pause();
}

void C_Enemy::update(float fDelay)
{
	if (m_nUpdateCount >= 1000000000)
		m_nUpdateCount = 0;

	// TODO : 이곳에 탄막 패턴 함수를 넣어주세요.

	m_nUpdateCount++;
}
