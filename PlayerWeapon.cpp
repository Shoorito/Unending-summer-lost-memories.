#include "PlayerWeapon.h"
#include "CocosFunctions.h"
#include "ResourceTable.h"
#include "PlayScene.h"

C_PlayerWeapon * C_PlayerWeapon::create()
{
	C_PlayerWeapon* pWeapon(nullptr);

	pWeapon = new(std::nothrow) C_PlayerWeapon();

	if (pWeapon && pWeapon->init())
	{
		pWeapon->preset();
	}
	else
	{
		C_Functions::safeDelete(pWeapon);
	}

	return pWeapon;
}

void C_PlayerWeapon::setSpeed(const float fSpeed)
{
	if (fSpeed < 0.1f)
		return;

	m_fSpeed = fSpeed;
}

void C_PlayerWeapon::setEnabled(const bool isEnabled)
{
	if (isEnabled == m_isEnabled)
		return;

	m_isEnabled = isEnabled;

	setVisible(m_isEnabled);

	if (m_isEnabled)
		resume();
	else
		pause();
}

void C_PlayerWeapon::setTextureWithRect(const std::string & strFile, const Rect & recTexture)
{
	setTexture(strFile);
	
	if (!recTexture.equals(Rect::ZERO))
		setTextureRect(recTexture);
}

bool C_PlayerWeapon::init()
{
	if (!Sprite::init())
		return false;

	m_fSpeed	  = g_fDefaultShotSpeed;
	m_isEnabled   = false;
	m_eWeaponType = E_WEAPON_TYPE::E_NORMAL;

	return true;
}

void C_PlayerWeapon::preset()
{
	m_arUpdater[0] = &C_PlayerWeapon::updateByWeapon;
	m_arUpdater[1] = &C_PlayerWeapon::updateBySubWeapon;

	setPosition(-500.0f, -500.0f);
	setVisible(false);

	schedule(schedule_selector(C_PlayerWeapon::update), 0.01f);
	pause();
}

void C_PlayerWeapon::updateBySubWeapon()
{
	addPositionY(m_fSpeed);
}

void C_PlayerWeapon::updateByWeapon()
{
	addPositionY(m_fSpeed);
}

const bool C_PlayerWeapon::onIntersectsEnemy()
{
	return false;
}

const bool C_PlayerWeapon::onIntersectsBorder()
{
	return !C_PlayScene::getInstance()->getWinArea().containsPoint(getPosition());
}

void C_PlayerWeapon::update(float fDelay)
{
	if (onIntersectsEnemy() || onIntersectsBorder())
	{
		setEnabled(false);

		return;
	}

	(this->*m_arUpdater[static_cast<int>(m_eWeaponType)])();
}
