#include "EnemyMovePatterns.h"
#include "Enemy.h"
#include "EnemyManager.h"

C_Enemy_Mover_Lib * C_Enemy_Mover_Lib::m_pInstance = nullptr;

C_Enemy_Mover_Lib * C_Enemy_Mover_Lib::create()
{
	if (m_pInstance)
	{
		CCLOG(u8"이미 \"C_Enemy_Mover_Lib\"가 생성되어 있습니다.");

		return nullptr;
	}

	m_pInstance = new(std::nothrow) C_Enemy_Mover_Lib();

	return m_pInstance;
}

void C_Enemy_Mover_Lib::enemyMoveAct01(C_Enemy * pTarget, const int nAnimType, const int nPatternType, const bool isFilped)
{
	MoveBy*		pMover01(nullptr);
	MoveBy*		pMover02(nullptr);
	CallFuncN*	pCallAngleMover(nullptr);
	CallFuncN*	pCallDisable(nullptr);
	DelayTime*	pDelay(nullptr);
	Sequence*	pSeq(nullptr);
	float		fMoveXpos(0.0f);
	float		fMoveYpos(0.0f);

	fMoveXpos = -400.0f + (800.0f * isFilped);
	fMoveYpos = -320.0f;

	pMover01		= MoveBy::create(1.0f, Vec2(0.0f, fMoveYpos));
	pMover02		= MoveBy::create(1.0f, Vec2(fMoveXpos, 0.0f));
	pCallAngleMover = CallFuncN::create
	(
		CC_CALLBACK_1
		(
			C_Enemy_Mover_Lib::spinMovement,
			this,
			450.0f + (-720.0f * isFilped),
			200.0f,
			0.0f + (180.0f * isFilped),
			pTarget->getPosition() + Vec2(fMoveXpos / 2.0f, fMoveYpos),
			isFilped
		)
	);

	pCallDisable = CallFuncN::create(CC_CALLBACK_1(C_Enemy_Mover_Lib::disableEnemy, this));
	pDelay		 = DelayTime::create(4.5f);

	pSeq = Sequence::create(pMover01, pCallAngleMover, pDelay, pMover02, pCallDisable, nullptr);

	pTarget->setAttackType(nPatternType);
	pTarget->startAnimation(nAnimType);
	pTarget->runAction(pSeq);
}

void C_Enemy_Mover_Lib::enemyMoveAct02(C_Enemy * pTarget, const int nAnimType, const int nPatternType)
{
	MoveBy*		pMove01(nullptr);
	DelayTime*	pDelay(nullptr);
	CallFuncN*  pUnload(nullptr);
	MoveTo*		pMove02(nullptr);
	Sequence*   pSequance(nullptr);

	pMove01   = MoveBy::create(1.0f, Vec2(0.0f, -360.0f));
	pMove02   = MoveTo::create(3.0f, Vec2(pTarget->getPositionX(), -20.0f));
	pUnload   = CallFuncN::create(CC_CALLBACK_1(C_Enemy_Mover_Lib::disableEnemy, this));
	pDelay	  = DelayTime::create(1.0f);
	pSequance = Sequence::create(pMove01, pDelay, pMove02, pUnload, nullptr);

	pTarget->setAttackType(nPatternType);
	pTarget->startAnimation(nAnimType);
	pTarget->runAction(pSequance);
}

void C_Enemy_Mover_Lib::spinMovement(Ref * pTarget, const float fAngle, const float fRadius, const float fStartAngle, const Vec2 & vecSpinPivot, const bool isFilped)
{
	C_Enemy* pEnemy(nullptr);

	pEnemy = static_cast<C_Enemy*>(pTarget);

	pEnemy->setSpinMovement(fAngle, fRadius, fStartAngle, vecSpinPivot, isFilped);
}

void C_Enemy_Mover_Lib::disableEnemy(Ref * pTarget)
{
	C_Enemy* pEnemy(nullptr);

	pEnemy = static_cast<C_Enemy*>(pTarget);

	pEnemy->stopAllActions();
	pEnemy->setEnabled(false);

	C_EnemyManager::getInstance()->changeEnemy(pEnemy, E_USE_TYPE::E_NOT_USED);
}
