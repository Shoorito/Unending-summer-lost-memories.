#pragma once
#include "cocos2d.h"

USING_NS_CC;

enum class E_MOVEMENT
{
	E_LEFT,
	E_RIGHT,
	E_UP,
	E_DOWN,
	E_MAX
};

class C_PlayerController : public Sprite
{
public:
	static C_PlayerController* create();
	static C_PlayerController* getInstance() { return m_pInstance; }
public:
	void setEnabled(const bool isEnabled);
public:
	void setTexture(const std::string& strTexture) override;
	void setTextureWithRect(const std::string& strTexture, const Rect& recSprite);
	void setScale(const float fScale);
	void setSpeed(const float fSpeed);
public:
	void setSlowMode(const bool isEnabled);
private:
	bool init() override;
private:
	void preset();
	void presetBySlowmode();
	void presetByMoveAdder();
	void updateMovement();
	void updateSlowmode();
private:
	void update(float fDelay) override;
	void updateMove();
private:
	bool m_isEnabled;
	bool m_isPushedShift;
private:
	float m_arShiftPushed[2]{  8.0f, 2.0f };
	float m_arSpeed[2]		{ -0.5f, 0.5f };
	float m_arMovement[static_cast<int>(E_MOVEMENT::E_MAX)]{};
private:
	float* m_arMoveAdder[2]{};
private:
	Sprite* m_pSlowMode;
	Sprite* m_pSlowModeSpiner;
private:
	static C_PlayerController* m_pInstance;
private:
	C_PlayerController() {}
	~C_PlayerController() {}
	C_PlayerController(C_PlayerController&) = delete;
	C_PlayerController operator=(C_PlayerController&) = delete;
};