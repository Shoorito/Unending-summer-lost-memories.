#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class C_Enemy;

class C_Enemy_Mover_Lib
{
public:
	static C_Enemy_Mover_Lib* create();
	inline static C_Enemy_Mover_Lib* getInstance() { return m_pInstance; }
public:
	void enemyMoveAct01(C_Enemy* pTarget, const int nAnimType, const int nPatternType, const bool isFilped);
	void enemyMoveAct02(C_Enemy* pTarget, const int nAnimType, const int nPatternType);
private:
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
	void disableEnemy(Ref* pTarget);
private:
	static C_Enemy_Mover_Lib* m_pInstance;
private:
	C_Enemy_Mover_Lib() {}
	virtual ~C_Enemy_Mover_Lib() {}
	C_Enemy_Mover_Lib(C_Enemy_Mover_Lib&) = delete;
	C_Enemy_Mover_Lib operator=(C_Enemy_Mover_Lib&) = delete;
};