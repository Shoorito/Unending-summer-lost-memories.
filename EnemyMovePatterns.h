#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class C_Enemy;

class C_Enemy_Mover_Lib
{
public:
	// INFO : "Enemy_Mover_Library" 생성구문.
	// @return = m_pInstance(singleton Type)
	static C_Enemy_Mover_Lib* create();

	// INFO : "Enemy_Mover_Library" 참조구문.
	// @return = m_pInstance(singleton Type)
	inline static C_Enemy_Mover_Lib* getInstance() { return m_pInstance; }
public:
	// INFO : 필드 1에서 사용하는 90도로 돌아가며 이동하는 패턴 함수 입니다.
	// 적이 아래로 강하하다가 도중 90도(isFilped시 -90도)로 돌아가며 이동하는 것이 특징입니다.
	// 해당 함수를 사용하여 적 개체에 적용하실 수 있습니다.
	// @param = pTarget		 >> TARGET_ENEMY
	// @param = nAnimType	 >> USE_ANIMATION_TYPE
	// @param = nPatternType >> USE_ATTACK_TYPE
	// @param = isFilped	 >> IS_FILP_MOVE?
	void enemyMoveAct01(C_Enemy* pTarget, const int nAnimType, const int nPatternType, const bool isFilped);
	
	// INFO : 일반적으로 사용되는 Y_AXIS기반의 아래로 이동하는 액션입니다.
	// 추후 좀더 세부적인 설정을 할 수 있게끔 변경 할 예정입니다.
	// 해당 함수를 사용하여 적 개체에 적용하실 수 있습니다.
	// @param = pTarget		 >> TARGET_ENEMY
	// @param = nAnimType	 >> USE_ANIMATION_TYPE
	// @param = nPatternType >> USE_ATTACK_TYPE
	void enemyMoveAct02(C_Enemy* pTarget, const int nAnimType, const int nPatternType);
private:
	// INFO : 적 개체의 "곡선 운동"설정을 도와주는 편의 함수입니다.
	// 주로 "CallFunc"함수를 사용해 호출합니다.
	// 사용 용법에 대해선 "C_Enemy"클래스의 "updateSpinMover" 참고.
	// @param = pTarget		 >> TARGET_ENEMY(static_cast를 이용하여 변환하여 사용하는 것을 추천)
	// @param = fAngle		 >> MOVE_ANGLE
	// @param = fRadius		 >> MOVE_RADIUS
	// @param = fStartAngle  >> START_MOVE_ANGLE
	// @param = vecSpinPivot >> SPIN_PIVOT
	// @param = isFilped	 >> FILP_ACT?(주로 사용하지는 않음.)
	void spinMovement
	(
		Ref* pTarget,
		const float fAngle,
		const float fRadius,
		const float fStartAngle,
		const Vec2& vecSpinPivot,
		const bool isFilped
	);
private:
	// INFO : 입력 받은 개체를 사용 해제(setEnabled(false))시키는 함수입니다.
	// 주로 "CallFunc"액션을 통한 적 개체의 사용해제에 사용합니다.
	// @param = pTarget >> TARGET_ENEMY(static_cast<C_Enemy>로 사용)
	void disableEnemy(Ref* pTarget);
private:
	static C_Enemy_Mover_Lib* m_pInstance;
private:
	C_Enemy_Mover_Lib() {}
	virtual ~C_Enemy_Mover_Lib() {}
	C_Enemy_Mover_Lib(C_Enemy_Mover_Lib&) = delete;
	C_Enemy_Mover_Lib operator=(C_Enemy_Mover_Lib&) = delete;
};