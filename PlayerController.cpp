#include "PlayerController.h"
#include "CocosFunctions.h"
#include "ResourceTable.h"
#include "KeyEventManager.h"

C_PlayerController * C_PlayerController::m_pInstance = nullptr;

C_PlayerController * C_PlayerController::create()
{
	if (m_pInstance)
	{
		CCLOG(u8"\"PlayerController\"가 이미 생성되어 있습니다.");
		CCLOG(u8"이 클래스는 \"다중 생성\"이 불가합니다.");

		return nullptr;
	}
	
	m_pInstance = new(std::nothrow) C_PlayerController();

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

void C_PlayerController::setEnabled(const bool isEnabled)
{
	m_isEnabled = isEnabled;

	setVisible(m_isEnabled);

	if (m_isEnabled)
		resume();
	else
		pause();
}

void C_PlayerController::setTexture(const std::string & strTexture)
{
	Sprite::setTexture(strTexture);

	updateMovement();
	updateSlowmode();
}

void C_PlayerController::setTextureWithRect(const std::string& strTexture, const Rect & recSprite)
{
	Sprite::setTexture(strTexture);
	Sprite::setTextureRect(recSprite);

	updateMovement();
	updateSlowmode();
}

void C_PlayerController::setScale(const float fScale)
{
	Sprite::setScale(fScale);

	updateMovement();
}

void C_PlayerController::setSpeed(const float fSpeed)
{
	if (!fSpeed)
		return;

	m_arSpeed[0] = -fSpeed;
	m_arSpeed[1] = fSpeed;
}

void C_PlayerController::setSlowMode(const bool isEnabled)
{
	m_isPushedShift = isEnabled;
	m_arSpeed[0]	= -m_arShiftPushed[m_isPushedShift];
	m_arSpeed[1]	= m_arShiftPushed[m_isPushedShift];

	m_pSlowMode->setVisible(m_isPushedShift);
	m_pSlowModeSpiner->setVisible(m_isPushedShift);

	if (isEnabled)
		m_pSlowModeSpiner->resume();
	else
		m_pSlowModeSpiner->pause();
}

bool C_PlayerController::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	m_isEnabled		  = false;
	m_isPushedShift   = false;
	m_pSlowMode		  = nullptr;
	m_pSlowModeSpiner = nullptr;

	return true;
}

void C_PlayerController::preset()
{
	presetBySlowmode();
	presetByMoveAdder();
	scheduleUpdate();
	setSlowMode(false);
}

void C_PlayerController::presetBySlowmode()
{
	RotateBy* pRotateAct(nullptr);
	Repeat*   pRepeater(nullptr);

	m_pSlowMode		  = Sprite::create("SlowMode_Colision.png");
	m_pSlowModeSpiner = Sprite::create("slowMode.png");
	pRotateAct		  = RotateBy::create(1.0f, 360.0f);
	pRepeater		  = Repeat::create(pRotateAct, -1);

	m_pSlowMode->setVisible(false);

	m_pSlowModeSpiner->setVisible(false);
	m_pSlowModeSpiner->setScale(0.5f);
	m_pSlowModeSpiner->setOpacity(200.0f);

	addChild(m_pSlowMode, 2);
	addChild(m_pSlowModeSpiner, 2);

	m_pSlowModeSpiner->runAction(pRepeater);
}

void C_PlayerController::presetByMoveAdder()
{
	m_arMoveAdder[0] = &_position.x;
	m_arMoveAdder[1] = &_position.y;
}

void C_PlayerController::updateMovement()
{
	float fWidth(0.0f);
	float fHeight(0.0f);

	fWidth  = getContentSize().width / 2.0f;
	fHeight = getContentSize().height / 2.0f;

	m_arMovement[static_cast<int>(E_MOVEMENT::E_LEFT)]	 = g_vecPlayerMovement.x + fWidth;
	m_arMovement[static_cast<int>(E_MOVEMENT::E_RIGHT)]  = g_vecPlayerMovement.y - fWidth;
	m_arMovement[static_cast<int>(E_MOVEMENT::E_UP)]	 = g_vecPlayerMovement.z - fHeight;
	m_arMovement[static_cast<int>(E_MOVEMENT::E_DOWN)]	 = g_vecPlayerMovement.w + fHeight;
}

void C_PlayerController::updateSlowmode()
{
	m_pSlowMode->setPosition(getContentSize() / 2.0f);
	m_pSlowModeSpiner->setPosition(m_pSlowMode->getPosition());
}

void C_PlayerController::update(float fDelay)
{
	C_KeyEvent_Manager* pManager(nullptr);
	bool arKey[2]{ false, true };

	pManager = C_KeyEvent_Manager::getInstance();

	for (int nKey(0); nKey < 4; nKey++)
	{
		if (pManager->getPushedType(nKey + 26) == E_KEY_STATE::E_PUSH)
		{
			bool isAdderKey((nKey % 2 == 1) != (nKey / 2));

			if ((*m_arMoveAdder[nKey / 2] < m_arMovement[nKey]) == arKey[isAdderKey])
			{
				*m_arMoveAdder[nKey / 2] += m_arSpeed[isAdderKey];

				updateMove();
			}
		}
	}

	if (pManager->getPushedType(12) == E_KEY_STATE::E_PUSH)
		setSlowMode(true);
	else if (pManager->getPushedType(12) == E_KEY_STATE::E_UP)
		setSlowMode(false);
}

void C_PlayerController::updateMove()
{
	_transformUpdated		 = true;
	_transformDirty			 = true;
	_inverseDirty			 = true;
	_usingNormalizedPosition = false;
}
