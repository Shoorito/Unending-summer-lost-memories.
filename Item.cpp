#include "Item.h"
#include "PlayerState.h"
#include "ItemManager.h"
#include "CocosFunctions.h"
#include "PlayerController.h"

C_Item * C_Item::create()
{
	C_Item* pItem(nullptr);

	pItem = new(std::nothrow) C_Item();

	if (pItem && pItem->init())
	{
		pItem->preset();
	}
	else
	{
		C_Functions::safeDelete(pItem);
	}

	return pItem;
}

void C_Item::setAddValue(const int nValue)
{
	if (!nValue)
		return;

	m_nAddValue = nValue;
}

void C_Item::setEnabled(const bool isEnabled)
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

void C_Item::setTextureWithRect(const std::string & strFile, const Rect & recTarget)
{
	setTexture(strFile);
	setTextureRect(recTarget);
}

void C_Item::startShowAct()
{
	m_isNowUpdate = true;
	runAction(m_pStartAct->clone());
}

bool C_Item::init()
{
	if (!Sprite::init())
		return false;

	m_nAddValue		= 0;
	m_pPrev			= nullptr;
	m_pNext			= nullptr;
	m_pStartAct		= nullptr;
	m_isEnabled		= false;
	m_isNowUpdate	= false;
	m_isNowActing	= false;
	m_eUseType		= E_USE_TYPE::E_NOT_USED;
	m_eItemType		= E_ITEM_TYPE::E_UP_HP;

	return true;
}

void C_Item::preset()
{
	setVisible(false);

	presetStartAct();

	schedule(static_cast<SEL_SCHEDULE>(&C_Item::update), 0.01f);
	pause();
}

void C_Item::presetStartAct()
{
	Spawn*	  pSpawn(nullptr);
	RotateBy* pRotate(nullptr);
	MoveBy*   pMoveUp(nullptr);
	CallFunc* pCallUndelay(nullptr);

	pRotate		 = RotateBy::create(0.5f, 360.0f);
	pMoveUp		 = MoveBy::create(pRotate->getDuration(), Vec2(0.0f, 75.0f));
	pCallUndelay = CallFunc::create(CC_CALLBACK_0(C_Item::unDelay, this));
	pSpawn		 = Spawn::create(pRotate, pMoveUp, nullptr);
	m_pStartAct  = Sequence::create(pSpawn, pCallUndelay, nullptr);

	m_pStartAct->retain();
}

void C_Item::move()
{
	if (m_isNowActing)
		return;

	float fShotAngle(0.0f);
	C_PlayerController* pPlayer(nullptr);

	pPlayer = C_PlayerController::getInstance();

	fShotAngle = atan2f
	(
		getPositionY() - pPlayer->getPositionY(),
		pPlayer->getPositionX() - getPositionX()
	);

	addPositionX(cosf(-fShotAngle) * 10.0f);
	addPositionY(sinf(-fShotAngle) * 10.0f);
}

void C_Item::unDelay()
{
	m_isNowUpdate = false;
}

void C_Item::update(float fDelay)
{
	if (!m_isEnabled || m_isNowUpdate)
		return;

	m_isNowUpdate = true;

	if (C_PlayerController::getInstance()->getBoundingBox().containsPoint(getPosition()))
	{
		if (m_eUseType == E_USE_TYPE::E_USED)
		{
			C_ItemManager::getInstance()->changeItem(this);
		}

		stopAllActions();
		setEnabled(false);

		C_PlayerState::getInstance()->addValueByTag(m_nAddValue, static_cast<int>(m_eItemType));

		return;
	}

	move();

	m_isNowUpdate = false;
}
