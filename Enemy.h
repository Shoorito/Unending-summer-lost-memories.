#pragma once
#include "cocos2d.h"
#include "EnumList.h"

using namespace cocos2d;

class C_Enemy : public Sprite
{
public:
	// INFO : "Enemy" 생성구문.
	// @return = 함수 내에서 동적 할당한 "Enemy Pointer".
	static C_Enemy* create();
public:
	// INFO : 적 개체의 "HP"를 반환합니다.
	// @return = m_nHP >> ENEMY_HP
	inline const int& getHP() const
	{ 
		return m_nHP; 
	}

	// INFO : 적 개체의 실시간 갱신 값을 반환합니다.
	// 주로 "update"함수에서 패턴등을 발생 시킬 때 사용됩니다.
	// @return m_nUpdateCount >> UPDATE_COUNT
	inline const int& getUpdateCount() const
	{
		return m_nUpdateCount;
	}

	// INFO : 적 개체의 공격 타입을 반환합니다.
	// 플레이어 공격용 함수 포인터 배열에서 사용합니다.
	// @return m_nAttackType >> ENEMY_ATTACK_TYPE
	inline const int& getAttackType() const
	{
		return m_nAttackType;
	}

	// INFO : 적 개체 타입을 반환합니다.
	// 해당 타입으로 보스와 구별도 가능하며 보스가 소환한 소환개체와도 구별이 가능합니다.
	// @return m_eType >> ENEMY_TYPE
	inline const E_ENEMY_TYPE& getType() const
	{
		return m_eType;
	}

	// INFO : 클래스의 활성화 여부를 반환합니다.
	// @return = m_isEnabled >> NOW_IS_ENABLED
	inline const bool& isEnabled() const
	{
		return m_isEnabled;
	}

	// INFO : 양방향 연결 리스트에 이용되는 "Prev"부분의 포인터를 반환합니다.
	// 해당 클래스가 이용되는 양방향 연결 리스트에 대해서 알고 싶으시면 "EnemyManager"클래스를 참고하세요.
	// @return = m_pPrev >> PREV_LINK
	inline C_Enemy* getPrev() const
	{
		return m_pPrev;
	}

	// INFO : 양방향 연결 리스트에 이용되는 "Next"부분의 포인터를 반환합니다.
	// 해당 클래스가 이용되는 양방향 연결 리스트에 대해서 알고 싶으시면 "EnemyManager"클래스를 참고하세요.
	// @return = m_pNext >> NEXT_LINK
	inline C_Enemy* getNext() const
	{
		return m_pNext;
	}
public:
	// INFO : 해당 적 개체에서 사용하는 애니메이션 액션을 반환합니다.
	// 적 개체가 사용하는 애니메이션이 다수 일 경우도 있기에 인수를 통해 가져오기 원하는
	// 애니메이션을 지정해주어야 합니다.
	// @param  = nPosition >> ARRAY_NUM
	// @return = m_vecAnim >> ANIMATION_ARRAY[ARRAY_NUM]
	Repeat* getAnimation(const int nPosition) const;
public:
	// INFO : 적 개체의 타입을 설정할 수 있습니다.
	// 적 개체의 타입에 따라 여럿 값이 변합니다.
	// @param = eType >> ENEMY_TYPE
	inline void setType(const E_ENEMY_TYPE& eType)
	{
		m_eType = eType;
	}
	// INFO : 양방향 리스트에 이용되는 "Prev"를 정할 수 있는 구문입니다.
	// @WARNING 적 개체를 "원형 양방향 연결 리스트"에서 사용할 경우 반드시 지정해주어야 예외적인 경우가 생기지 않습니다.
	// @param = pEnemy >> PREV_ENEMY
	inline void setPrev(C_Enemy* pEnemy)
	{
		m_pPrev = pEnemy;
	}

	// INFO : 양방향 리스트에 이용되는 "Next"를 정할 수 있는 구문입니다.
	// @WARNING 적 개체를 "원형 양방향 연결 리스트"에서 사용할 경우 반드시 지정해주어야 예외적인 경우가 생기지 않습니다.
	// @param = pEnemy >> NEXT_ENEMY
	inline void setNext(C_Enemy* pEnemy)
	{
		m_pNext = pEnemy;
	}
public:
	// INFO : 적 개체의 이동, 곡선 운동에 사용되는 변수들을 모두 초기화합니다.
	// 적 개체의 곡선 이동 후 사용하면 이동 예외를 방지 할 수 있습니다.
	void initMovement();
public:
	// INFO : 적 개체가 사용 할 애니메이션 액션을 파일 목록을 통해서 지정 할 수 있습니다.
	// 애니메이션의 딜레이 타임을 설정해 원하는 속도로 재생 할 수 있습니다.
	// @param = vecFiles >> "'FILE_ROUTE + FILE_NAME' LIST"
	// @param = fDelay	 >> DELAY_TIME
	void addAnimationWithFiles(const std::vector<std::string>& vecFiles, const float fDelay);

	// INFO : 적 개체가 사용 할 애니메이션 액션을 아틀라스 이미지(Atlas Image)를 통해서 지정 할 수 있습니다.
	// 단일 파일의 "RECT"를 지정하고, 애니메이션 파일의 개수를 지정 할 수 있는 점에서 보다 세부적인 설정이 가능합니다.
	// @param = strFile  >> FILE_ROUTE + FILE_NAME
	// @param = recSize  >> ANIMATION_TEXTURE_SIZE
	// @param = nCount	 >> ANIMATION_TEXTURE_COUNT
	// @param = fDelay	 >> DELAY_TIME
	void addAnimationWithAtlas(const std::string& strFile, const Rect& recSize, const int nCount, const float fDelay);
	
	// INFO : 적 개체에 아틀라스 이미지(Atlas Image)가 이미 텍스쳐로 지정되있을 경우 사용하는 기능입니다.
	// @param = recSize  >> ANIMATION_TEXTURE_SIZE
	// @param = nCount	 >> ANIMATION_TEXTURE_COUNT
	// @param = fDelay	 >> DELAY_TIME
	void addAnimationWithRects(const Rect& recSize, const int nCount, const float fDelay);
public:
	// INFO : 적 개체의 "HP"를 설정할 수 있습니다.
	// @WARNING = '0'으로 지정할 경우 적 개체가 소멸된 것으로 간주되어 소멸 할 수 있으니 주의해야 합니다.
	// @param   = nHP >> ENEMY_HP
	virtual void setHP(const int nHP);

	// INFO : 적 개체의 "HP"를 더하거나 뺄 때 사용하는 편의 함수입니다.
	// @param = nHP >> (PREV_ENEMY_HP + ADD_HP)
	virtual void addHP(const int nHP);

	// INFO : 적 개체를 활성화/비활성화 시킵니다.
	// @param = isEnabled >> ITEM_IS_ENABLED
	virtual void setEnabled(const bool isEnabled);
public:
	// INFO : 적 개체의 공격 타입을 설정합니다.
	// 플레이어 공격용 함수 포인터 배열에서 사용합니다.
	// @param = nType >> ATTACK_TYPE
	void setAttackType(const int nType);
public:
	// INFO : 현재 개체내 저장 된 애니메이션 액션 중 입력한 인수에 해당하는 위치에 있는 애니메이션을 재생합니다.
	// @param = nType >> PLAY_TYPE_ANIMATION
	void startAnimation(const int nType);

	// INFO : 적 개체의 곡선 운동용 인수들을 설정합니다.
	// 해당 기능으로 설정 된 인수들은 "update"함수를 통해 작동합니다.
	// @param = fAngle		 >> MOVE_ANGLE
	// @param = fRadius		 >> MOVE_PIVOT_RADIUS
	// @param = fStartAngle  >> MOVE_PIVOT_START_ANGLE,
	// @param = vecSpinPivot >> MOVE_PIVOT
	// @param = isFilp		 >> MOVE_IS_FILP
	void setSpinMovement(const float fAngle, const float fRadius, const float fStartAngle, const Vec2& vecSpinPivot, const bool isFilped);
public:
	// INFO : 적 개체의 이미지(Sprite)를 입력한 인수에 맞게 설정합니다.
	// @param = strFile   >> ENEMY_TEXTURE_ROUTE + TEXTURE_NAME
	// @param = recTarget >> ENEMY_USE_RECT
	void setTextureWithRect(const std::string& strFile, const Rect& recSprite);
protected:
	virtual bool init() override;
	virtual void preset();
	// INFO : 함수 포인터 배열에 패턴 목록을 미리 지정합니다.
	virtual void presetPattern();
protected:
	// INFO : 실시간 갱신 값을 임의로 지정합니다.
	// @param : nCount >> UPDATE_COUNT
	void setUpdateCount(const int nCount);

	// INFO : 실시간 갱신 값을 입력한 값 만큼 더하거나 뺍니다.
	// @param : nCount >> PREV_UPDATE_COUNT + ADD_COUNT
	void addUpdateCount(const int nCount);
private:
	// INFO : "Sprite"의 "update"함수를 오버라이드 한 함수입니다.
	// 실시간 이동 및 공격 이벤트를 담당합니다.
	// @param : 해당 함수가 불리는 간격을 가져옵니다, 사용되지는 않습니다.
	virtual void update(float fDelay);
private:
	// INFO : "Update"함수에서 사용되는 적 개체의 곡선형 이동 업데이트 함수입니다.
	void updateSpinMover();
private:
	// INFO : "Enemy"가 사용하는 공격 패턴의 구문으로 "m_arPattern" 함수 배열 포인터로 호출 됩니다.
	// 인수인 "nUpdateCount"는 직접 넣어주는 값이 아닌 맴버 변수인 "m_nUpdateCount"가 사용됩니다.
	// "nUpdateCount"에 들어온 값에 제한 구문을 사용하여 발동 간격을 지정합니다.
	void pattern01(const int nCount);
	void pattern02(const int nCount);
	void pattern03(const int nCount);
	void pattern04(const int nCount);
	void pattern05(const int nCount);
	void pattern06(const int nCount);
	void pattern07(const int nCount);
	void pattern08(const int nCount);
private:
	void(C_Enemy::*m_arPattern[8])(const int);
private:
	std::vector<Repeat*> m_vecAnim;
private:
	E_ENEMY_TYPE m_eType;
private:
	C_Enemy* m_pPrev;
	C_Enemy* m_pNext;
private:
	bool m_isEnabled;
	bool m_isSpinFilped;
private:
	int m_nHP;
	int m_nAttackType;
	int	m_nUpdateCount;
private:
	float m_fSpinAngle;
	float m_fAngle;
	float m_fSpinRadius;
	Vec2  m_vecSpinPivot;
protected:
	C_Enemy() {}
	virtual ~C_Enemy() {}
	C_Enemy(C_Enemy&) = delete;
	C_Enemy operator=(C_Enemy&) = delete;
};