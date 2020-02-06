#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class C_EnemyPatterns
{
public:
	// INFO : "EnemyPatterns" 생성구문.
	// @return = m_pInstance(singleton Type)
	static C_EnemyPatterns* create();

	// INFO : "EnemyPatterns" 참조구문.
	// @return = m_pInstance(singleton Type)
	inline static C_EnemyPatterns* getInstance() { return m_pInstance; }
public:
	// INFO : 일반적인 원형 탄막 패턴입니다.
	// 시작 각도에 따라 플레이어를 향하게 할 수도 있으며, 보편적이며 익숙한 원형 탄막 패턴을 만듭니다.
	// "NWay"를 1개로 고정하면 일반적인 "Way-탄"처럼 사용 할 수 있습니다.
	// @param = vecStartpos   >> ATTACK_START_POSITION
	// @param = nWayCount	  >> ATTACK_WAY_NUMBER
	// @param = fStartAngle   >> ATTACK_START_ANGLE
	// @param = fSpeed		  >> DANMAKU_MOVE_SPEED
	// @param = fScale		  >> DANMAKU_SCALE
	// @param = recUseTexture >> DANMAKU_USE_TEXTURE_RECT
	void circleNWay
	(
		const Vec2& vecStartpos,
		const int	nWayCount,
		const float fStartAngle,
		const float fSpeed,
		const float fScale,
		const Rect& recUseTexture
	);

	// INFO : 소환수 소환 패턴입니다.
	// 해당 패턴을 호출 시 정해진 "Animation"을 가진 적 개체가 등장하며 함수내에 지정된 타입의 공격을 진행합니다.
	// 해당 패턴으로 생성 된 적은 아이템을 드롭하지 않으며 점수를 얻지 못합니다.
	// @param = vecSummonpos >> START_POSITION
	void summon(const Vec2& vecSummonpos);

	// INFO : 일종 거리 이동후 탄막이 비대하게 커지는 패턴입니다.
	// 해당 패턴과 다른 패턴을 섞어서 사용 하면 매우 어려워지거나, 방어가 불가능한 패턴이 될 수 있습니다.
	// 보다 세부적인 설정을 할 수 있게끔 개편 될 예정입니다.
	// @param = vecStartpos	  >> START_POSITION
	// @param = fAngle		  >> DANMAKU_MOVE_ANGLE
	// @param = fSpeed		  >> DANMAKU_MOVE_SPEED
	// @param = recUseTexture >> DANMAKU_USE_TEXTURE_RECT
	void aimingBoom
	(
		const Vec2& vecStartpos,
		const float fAngle,
		const float fSpeed,
		const Rect& recUseTexture
	);
private:
	static C_EnemyPatterns* m_pInstance;
private:
	C_EnemyPatterns() {}
	~C_EnemyPatterns() {}
	C_EnemyPatterns(C_EnemyPatterns&) = delete;
	C_EnemyPatterns operator=(C_EnemyPatterns&) = delete;
};