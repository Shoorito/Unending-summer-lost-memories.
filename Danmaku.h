#pragma once
#include "cocos2d.h"
#include "EnumList.h"

using namespace cocos2d;

class C_Danmaku : public Node
{
public:
	// INFO : "Danmaku" 생성구문.
	// @return = 함수 내에서 동적 할당한 "Danmaku Pointer".
	static C_Danmaku* create();
public:
	// INFO : 양방향 연결 리스트에 이용되는 "Prev"부분의 포인터를 반환합니다.
	// 해당 클래스가 이용되는 양방향 연결 리스트에 대해서 알고 싶으시면 "DanmakuManager"클래스를 참고하세요.
	// @return = m_pPrev >> PREV_LINK
	inline C_Danmaku* getPrev() const
	{
		return m_pPrev;
	}

	// INFO : 양방향 연결 리스트에 이용되는 "Next"부분의 포인터를 반환합니다.
	// 해당 클래스가 이용되는 양방향 연결 리스트에 대해서 알고 싶으시면 "DanmakuManager"클래스를 참고하세요.
	// @return = m_pNext >> NEXT_LINK
	inline C_Danmaku* getNext() const
	{
		return m_pNext;
	}

	// INFO : 탄막에 사용되는 이미지 파일을 반환합니다.
	// 이미지의 충돌, 사이즈 변화와 같이 직접적인 이벤트는 이 함수를 통해 처리합니다.
	// @return = m_pTexture >> DANMAKU_SPRITE
	inline Sprite* getTexture() const
	{
		return m_pTexture;
	}
public:
	// INFO : 탄막이 플레이어에게 주는 데미지를 반환합니다.
	// @return = m_nDamage >> DANMAKU_DAMAGE
	inline const int& getDamage() const
	{
		return m_nDamage;
	}

	// INFO : 탄막의 현재 각도를 반환합니다.
	// 이동에 사용되는 값입니다.
	// @return = m_fAngle >> DANMAKU_ANGLE
	inline const float& getAngle() const
	{
		return m_fAngle;
	}

	// INFO : 탄막의 속도를 반환합니다.
	// 이동에 사용되는 값입니다.
	// @return = m_fSpeed >> DANMAKU_SPEED
	inline const float& getSpeed() const
	{
		return m_fSpeed;
	}

	// INFO : 탄막의 "사용 여부"를 반환합니다.
	// 사용 여부는 "enum class E_USE_TYPE" 을 참고하세요.
	// 사용의 개념은 "활성화"의 개념과 다릅니다.
	// @return = m_eNowUseType >> DANMAKU_IS_NOW_USE?
	inline const E_USE_TYPE& getUseType() const
	{
		return m_eNowUseType;
	}
public:
	// INFO : 탄막의 "활성화 여부"를 반환합니다.
	// "활성화"는 탄막의 실시간 이벤트/이동의 여부를 알 수 있게 해주는 정보입니다.
	// "활성화" 상태라고 해도 "탄막 매니저 풀"에 담겨있지 않으면 재사용이 불가하기 때문에
	// 사용 시에는 반드시 "탄막 매니저 풀"에 넣고 사용해야 합니다.
	// @return = m_isEnabled >> DANMAKU_IS_ENABLED
	inline const bool& isEnabled() const
	{
		return m_isEnabled;
	}
public:
	// INFO : 양방향 리스트에 이용되는 "Prev"를 정할 수 있는 구문입니다.
	// @WARNING 탄막을 "원형 양방향 연결 리스트"에서 사용할 경우 반드시 지정해주어야 예외적인 경우가 생기지 않습니다.
	// @param = pDanmaku >> PREV_DANMAKU
	inline void setPrev(C_Danmaku* pDanmaku)
	{
		m_pPrev = pDanmaku;
	}

	// INFO : 양방향 리스트에 이용되는 "Next"를 정할 수 있는 구문입니다.
	// @WARNING 탄막을 "원형 양방향 연결 리스트"에서 사용할 경우 반드시 지정해주어야 예외적인 경우가 생기지 않습니다.
	// @param = pDanmaku >> NEXT_DANMAKU
	inline void setNext(C_Danmaku* pDanmaku)
	{
		m_pNext = pDanmaku;
	}

	// INFO : 탄막의 사용 여부를 설정 할 수 있습니다.
	// 해당 요소에 대한 설명은 "getUseType" 함수를 참고하시기 바랍니다.
	// @param = eType >> DANMAKU_USE_TYPE
	inline void setUseType(E_USE_TYPE eType)
	{
		m_eNowUseType = eType;
	}
public:
	// INFO : 탄막이 플레이어에게 줄 데미지를 설정 할 수 있습니다.
	// @param = nDamage >> DANMAKU_DAMAGE
	void setDamage(const int nDamage);

	// INFO : 탄막의 각도를 설정 할 수 있습니다.
	// @param = fAngle >> DANMAKU_ANGLE
	void setAngle(const float fAngle);

	// INFO : 탄막의 이동 속도를 설정 할 수 있습니다.
	// @param = fSpeed >> DANMAKU_SPEED
	void setSpeed(const float fSpeed);
public:
	// INFO : 탄막의 제거 이벤트를 발생 시킵니다.
	// @WARNING 이 함수로 탄막의 개체가 실제로 사라지는 것은 아닙니다.
	// 탄막이 게임 내 이유로 지워지게 될 경우 이 함수를 호출하면 삭제 이벤트를 발생 시키도록 작성했습니다.
	void removeDanmaku();
public:
	// INFO : 탄막의 각도를 더하거나 빼주는 용도의 편의 함수입니다.
	// @param = fAddAngle >> DANMAKU_ANGLE + ADD_ANGLE
	void addAngle(const float fAddAngle);
public:
	// INFO : 탄막을 활성화/비활성화 시킵니다.
	// @param = isEnabled >> DANMAKU_IS_ENABLED
	void setEnabled(const bool isEnabled);
public:
	// INFO : 탄막의 이미지(Sprite)를 입력한 인수에 맞게 설정합니다.
	// @param = strFile   >> DANMKAU_TEXTURE_ROUTE + TEXTURE_NAME
	// @param = recTarget >> DANMAKU_USE_RECT
	void setTextureWithRect(const std::string& strFile, const Rect& recTarget);
private:
	// INFO : "Node"의 "init" 함수를 오버라이드 한 함수입니다.
	// 맴버 변수의 초기화 이외 작업은 없습니다.
	bool init() override;
	void preset();
	void presetRemoveAct();
	// INFO : "Update"함수에서 호출마다 탄막을 이동시키는 구문입니다.
	void move();
private:
	// INFO : 게임 내 영역을 벗어난 것을 알리는 함수입니다.
	// 주로 "update"구문에서 사용하며, 이 값이 "TRUE"가 되면 해당 탄막은 비활성화 됩니다.
	// @return = IS_INTERSECTS_BORDER
	const bool onIntersectsBorder();

	// INFO : 플레이어와 충돌 한 것을 알리는 함수입니다.
	// 주로 "update"구문에서 사용하며, 이 값이 "TRUE"가 되면 해당 탄막은 비활성화 됩니다.
	// @return = IS_INTERSECTS_PLAYER
	const bool onIntersectsPlayer();
private:
	// INFO : "Node"의 "update"함수를 오버라이드 한 함수입니다.
	// 실시간 이동 및 충돌 이벤트를 담당합니다.
	// @param : 해당 함수가 불리는 간격을 가져옵니다, 사용되지는 않습니다.
	void update(float fDelay) override;
private:
	bool m_isEnabled;
private:
	int m_nDamage;
private:
	float m_fAngle;
	float m_fSpeed;
private:
	C_Danmaku* m_pPrev;
	C_Danmaku* m_pNext;
private:
	Sprite* m_pTexture;
	Sprite* m_pDeleteTexture;
private:
	Sequence* m_pRemoveAct;
	ScaleTo*  m_pScaleDown;
private:
	E_USE_TYPE m_eNowUseType;
private:
	C_Danmaku() {}
	virtual ~C_Danmaku() {}
	C_Danmaku(C_Danmaku&) = delete;
	C_Danmaku operator=(C_Danmaku&) = delete;
};