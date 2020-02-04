#include "Danmaku.h"
#include "PausePopup.h"
#include "PlayerState.h"
#include "FieldManager.h"
#include "ResourceTable.h"
#include "CocosFunctions.h"
#include "DanmakuManager.h"
#include "PlayerController.h"

C_Danmaku * C_Danmaku::create()
{
	C_Danmaku* pDanmaku(nullptr);

	pDanmaku = new(std::nothrow) C_Danmaku();

	if (pDanmaku && pDanmaku->init())
	{
		pDanmaku->preset();
	}
	else
	{
		C_Functions::safeDelete(pDanmaku);
	}
	
	return pDanmaku;
}

void C_Danmaku::setDamage(const int nDamage)
{
	if (nDamage < 0)
		return;

	m_nDamage = nDamage;
}

void C_Danmaku::setAngle(const float fAngle)
{
	m_fAngle = fAngle;
}

void C_Danmaku::setSpeed(const float fSpeed)
{
	m_fSpeed = fSpeed;
}

void C_Danmaku::removeDanmaku()
{
	if (m_isEnabled)
	{
		m_isEnabled = false;

		m_pTexture->setVisible(false);
		m_pDeleteTexture->setVisible(true);

		m_pDeleteTexture->runAction(m_pScaleDown->clone());
		runAction(m_pRemoveAct->clone());
	}
	else
	{
		pause();
		setVisible(false);
		m_pTexture->setVisible(true);
		m_pDeleteTexture->setVisible(false);
		m_pDeleteTexture->setScale(1.0f);
	}
}

void C_Danmaku::addAngle(const float fAddAngle)
{
	if (!fAddAngle)
		return;

	m_fAngle += fAddAngle;
}

void C_Danmaku::setEnabled(const bool isEnabled)
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

void C_Danmaku::setTextureWithRect(const std::string & strFile, const Rect & recTarget)
{
	m_pTexture->setTexture(strFile);
	m_pTexture->setTextureRect(recTarget);
}

bool C_Danmaku::init()
{
	if (!Node::init())
		return false;

	m_fAngle		 = 0.0f;
	m_fSpeed		 = 0.0f;
	m_nDamage		 = 0;
	m_isEnabled		 = false;
	m_pPrev			 = nullptr;
	m_pNext			 = nullptr;
	m_pDeleteTexture = nullptr;
	m_pRemoveAct	 = nullptr;
	m_pTexture		 = nullptr;
	m_eNowUseType	 = E_USE_TYPE::E_NOT_USED;

	return true;
}

void C_Danmaku::preset()
{
	m_pTexture		 = Sprite::create();
	m_pDeleteTexture = Sprite::create("DanmakuDeleteTexture.png");

	setVisible(false);
	m_pDeleteTexture->setVisible(false);

	presetRemoveAct();

	schedule(schedule_selector(C_Danmaku::update), 0.01f);
	pause();

	addChild(m_pTexture);
	addChild(m_pDeleteTexture);
}

void C_Danmaku::presetRemoveAct()
{
	DelayTime* pDelay(nullptr);
	CallFunc*  pFunc(nullptr);

	pDelay		 = DelayTime::create(0.6f);
	pFunc		 = CallFunc::create(CC_CALLBACK_0(C_Danmaku::removeDanmaku, this));
	m_pRemoveAct = Sequence::create(pDelay, pFunc, nullptr);
	m_pScaleDown = ScaleTo::create(0.5f, 0.0f);

	m_pRemoveAct->retain();
	m_pScaleDown->retain();
}

void C_Danmaku::move()
{
	m_pTexture->setRotation(m_fAngle - 90.0f);
	m_pTexture->addPositionX(cosf(-m_fAngle * 3.141592 / 180.0f) * m_fSpeed);
	m_pTexture->addPositionY(sinf(-m_fAngle * 3.141592 / 180.0f) * m_fSpeed);
	m_pDeleteTexture->setPosition(m_pTexture->getPosition());
}

const bool C_Danmaku::onIntersectsBorder()
{
	return !g_recWinArea.containsPoint(m_pTexture->getPosition());
}

const bool C_Danmaku::onIntersectsPlayer()
{
	C_PlayerController* pPlayer(nullptr);

	pPlayer = C_PlayerController::getInstance();

	if (pPlayer->getBoundingBox().containsPoint(m_pTexture->getPosition()))
	{
		int nPlayerHP(0);

		nPlayerHP = C_PlayerState::getInstance()->getHP() - m_nDamage;

		if(nPlayerHP < 1)
		{
			C_PlayerState::getInstance()->setHP(0);
			C_PlayerController::getInstance()->setEnabled(false);
			C_FieldManager::getInstance()->callGameOver();
		}
		else
		{
			C_PlayerState::getInstance()->addHP(-m_nDamage);
		}

		return true;
	}
	else
	{
		return false;
	}
}

void C_Danmaku::update(float fDelay)
{
	if (!m_isEnabled)
		return;

	if (onIntersectsBorder() || onIntersectsPlayer())
	{
		setEnabled(false);

		C_DanmakuManager::getInstance()->changeDanmaku(this);
	}

	move();
}
