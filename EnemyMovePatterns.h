#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class C_Enemy;

class C_Enemy_Mover_Lib
{
public:
	// INFO : "Enemy_Mover_Library" ��������.
	// @return = m_pInstance(singleton Type)
	static C_Enemy_Mover_Lib* create();

	// INFO : "Enemy_Mover_Library" ��������.
	// @return = m_pInstance(singleton Type)
	inline static C_Enemy_Mover_Lib* getInstance() { return m_pInstance; }
public:
	// INFO : �ʵ� 1���� ����ϴ� 90���� ���ư��� �̵��ϴ� ���� �Լ� �Դϴ�.
	// ���� �Ʒ��� �����ϴٰ� ���� 90��(isFilped�� -90��)�� ���ư��� �̵��ϴ� ���� Ư¡�Դϴ�.
	// �ش� �Լ��� ����Ͽ� �� ��ü�� �����Ͻ� �� �ֽ��ϴ�.
	// @param = pTarget		 >> TARGET_ENEMY
	// @param = nAnimType	 >> USE_ANIMATION_TYPE
	// @param = nPatternType >> USE_ATTACK_TYPE
	// @param = isFilped	 >> IS_FILP_MOVE?
	void enemyMoveAct01(C_Enemy* pTarget, const int nAnimType, const int nPatternType, const bool isFilped);
	
	// INFO : �Ϲ������� ���Ǵ� Y_AXIS����� �Ʒ��� �̵��ϴ� �׼��Դϴ�.
	// ���� ���� �������� ������ �� �� �ְԲ� ���� �� �����Դϴ�.
	// �ش� �Լ��� ����Ͽ� �� ��ü�� �����Ͻ� �� �ֽ��ϴ�.
	// @param = pTarget		 >> TARGET_ENEMY
	// @param = nAnimType	 >> USE_ANIMATION_TYPE
	// @param = nPatternType >> USE_ATTACK_TYPE
	void enemyMoveAct02(C_Enemy* pTarget, const int nAnimType, const int nPatternType);
private:
	// INFO : �� ��ü�� "� �"������ �����ִ� ���� �Լ��Դϴ�.
	// �ַ� "CallFunc"�Լ��� ����� ȣ���մϴ�.
	// ��� ����� ���ؼ� "C_Enemy"Ŭ������ "updateSpinMover" ����.
	// @param = pTarget		 >> TARGET_ENEMY(static_cast�� �̿��Ͽ� ��ȯ�Ͽ� ����ϴ� ���� ��õ)
	// @param = fAngle		 >> MOVE_ANGLE
	// @param = fRadius		 >> MOVE_RADIUS
	// @param = fStartAngle  >> START_MOVE_ANGLE
	// @param = vecSpinPivot >> SPIN_PIVOT
	// @param = isFilped	 >> FILP_ACT?(�ַ� ��������� ����.)
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
	// INFO : �Է� ���� ��ü�� ��� ����(setEnabled(false))��Ű�� �Լ��Դϴ�.
	// �ַ� "CallFunc"�׼��� ���� �� ��ü�� ��������� ����մϴ�.
	// @param = pTarget >> TARGET_ENEMY(static_cast<C_Enemy>�� ���)
	void disableEnemy(Ref* pTarget);
private:
	static C_Enemy_Mover_Lib* m_pInstance;
private:
	C_Enemy_Mover_Lib() {}
	virtual ~C_Enemy_Mover_Lib() {}
	C_Enemy_Mover_Lib(C_Enemy_Mover_Lib&) = delete;
	C_Enemy_Mover_Lib operator=(C_Enemy_Mover_Lib&) = delete;
};