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
	// INFO : "PlayerController" 생성구문.
	// @return = m_pInstance(singleton Type)
	static C_PlayerController* create();

	// INFO : "PlayerController" 참조구문.
	// @return = m_pInstance(singleton Type)
	static C_PlayerController* getInstance() { return m_pInstance; }
public:
	// INFO : "PlayerController"의 활성화 여부를 설정합니다.
	// 비활성화 시킬경우 플레이어 기체 조작이 불가능합니다.
	// @param = isEnabled >> MANAGER_IS_ENABLED
	void setEnabled(const bool isEnabled);
public:
	// INFO : 플레이어 기체에 입력한 텍스쳐를 적용합니다.
	// @param = strTexture >> TEXTURE_ROUTE + TEXTURE_NAME
	void setTexture(const std::string& strTexture) override;

	// INFO : 적 개체의 이미지(Sprite)를 입력한 인수에 맞게 설정합니다.
	// @param = strFile   >> PLAYER_TEXTURE_ROUTE + TEXTURE_NAME
	// @param = recTarget >> PLAYER_USE_RECT
	void setTextureWithRect(const std::string& strTexture, const Rect& recSprite);

	// INFO : "Sprite"개체의 크기를 조정하는 함수로 오버라이드 함수입니다.
	// 플레이어 이동 영역에 대한 업데이트가 이루어집니다.
	// @param = fScale >> TEXTURE_SCALE
	void setScale(const float fScale);

	// INFO : 플레이어의 이동 속도를 지정합니다.
	// @param = fSpeed >> PLAYER_SPEED
	void setSpeed(const float fSpeed);
public:
	// INFO : 플레이어 기체의 "저속 이동 모드"를 활성화/비활성화 할 수 있습니다.
	// @param = isEnabled >> SLOW_MODE_IS_ENABLED
	void setSlowMode(const bool isEnabled);
private:
	// INFO : "Sprite"의 "init"함수를 오버라이드 한 형태입니다.
	// @return = is_Initialize_Success >> IS_INITIALIZE_SUCCESS
	bool init() override;
private:
	// INFO : 클래스 내에서 사용되는 여럿 기능들을 미리 지정/설정 할 때 사용합니다.
	// 생성 시에만 사용되니 재사용을 금합니다.
	void preset();

	// INFO : 슬로우 모드 액션에 관련한 요소를 미리 설정합니다.
	void presetBySlowmode();

	// INFO : 이동 이벤트에 관련한 정보를 미리 설정합니다.
	void presetByMoveAdder();

	// INFO : 플레이어의 이동에 대한 이동 가능 지역에 대한 정보를 갱신합니다.
	void updateMovement();

	// INFO : 플레이어의 "SlowMode"시 등장하는 이펙트 또는 표식의 위치 정보를 갱신합니다.
	// 현재는 큰 기능은 아닙니다.
	void updateSlowmode();
private:
	// INFO : "Sprite"의 "update"함수의 오버라이드 함수입니다.
	// 플레이어 기체의 이동에 관련한 사항을 갱신합니다.
	// @param = fDelay >> UPDATE_DELAY
	void update(float fDelay) override;

	// INFO : 플레이어 기체의 이동에 대한 갱신 함수입니다.
	// "update"함수에서 불립니다.
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