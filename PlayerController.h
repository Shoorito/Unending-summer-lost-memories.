#pragma once
#include "cocos2d.h"

USING_NS_CC;

static const Vec4 g_vecPlayerMovement{ 290.0f, 990.0f, 695.0f, 25.0f };

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
	// INFO : "PlayerController" ��������.
	// @return = m_pInstance(singleton Type)
	static C_PlayerController* create();

	// INFO : "PlayerController" ��������.
	// @return = m_pInstance(singleton Type)
	static C_PlayerController* getInstance() { return m_pInstance; }
public:
	// INFO : "PlayerController"�� Ȱ��ȭ ���θ� �����մϴ�.
	// ��Ȱ��ȭ ��ų��� �÷��̾� ��ü ������ �Ұ����մϴ�.
	// @param = isEnabled >> MANAGER_IS_ENABLED
	void setEnabled(const bool isEnabled);
public:
	// INFO : �÷��̾� ��ü�� �Է��� �ؽ��ĸ� �����մϴ�.
	// @param = strTexture >> TEXTURE_ROUTE + TEXTURE_NAME
	void setTexture(const std::string& strTexture) override;

	// INFO : �� ��ü�� �̹���(Sprite)�� �Է��� �μ��� �°� �����մϴ�.
	// @param = strFile   >> PLAYER_TEXTURE_ROUTE + TEXTURE_NAME
	// @param = recTarget >> PLAYER_USE_RECT
	void setTextureWithRect(const std::string& strTexture, const Rect& recSprite);

	// INFO : "Sprite"��ü�� ũ�⸦ �����ϴ� �Լ��� �������̵� �Լ��Դϴ�.
	// �÷��̾� �̵� ������ ���� ������Ʈ�� �̷�����ϴ�.
	// @param = fScale >> TEXTURE_SCALE
	void setScale(const float fScale);

	// INFO : �÷��̾��� �̵� �ӵ��� �����մϴ�.
	// @param = fSpeed >> PLAYER_SPEED
	void setSpeed(const float fSpeed);
public:
	// INFO : �÷��̾� ��ü�� "���� �̵� ���"�� Ȱ��ȭ/��Ȱ��ȭ �� �� �ֽ��ϴ�.
	// @param = isEnabled >> SLOW_MODE_IS_ENABLED
	void setSlowMode(const bool isEnabled);
private:
	// INFO : "Sprite"�� "init"�Լ��� �������̵� �� �����Դϴ�.
	// @return = is_Initialize_Success >> IS_INITIALIZE_SUCCESS
	bool init() override;
private:
	// INFO : Ŭ���� ������ ���Ǵ� ���� ��ɵ��� �̸� ����/���� �� �� ����մϴ�.
	// ���� �ÿ��� ���Ǵ� ������ ���մϴ�.
	void preset();

	// INFO : ���ο� ��� �׼ǿ� ������ ��Ҹ� �̸� �����մϴ�.
	void presetBySlowmode();

	// INFO : �̵� �̺�Ʈ�� ������ ������ �̸� �����մϴ�.
	void presetByMoveAdder();

	// INFO : �÷��̾��� �̵��� ���� �̵� ���� ������ ���� ������ �����մϴ�.
	void updateMovement();

	// INFO : �÷��̾��� "SlowMode"�� �����ϴ� ����Ʈ �Ǵ� ǥ���� ��ġ ������ �����մϴ�.
	// ����� ū ����� �ƴմϴ�.
	void updateSlowmode();
private:
	// INFO : "Sprite"�� "update"�Լ��� �������̵� �Լ��Դϴ�.
	// �÷��̾� ��ü�� �̵��� ������ ������ �����մϴ�.
	// @param = fDelay >> UPDATE_DELAY
	void update(float fDelay) override;

	// INFO : �÷��̾� ��ü�� �̵��� ���� ���� �Լ��Դϴ�.
	// "update"�Լ����� �Ҹ��ϴ�.
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