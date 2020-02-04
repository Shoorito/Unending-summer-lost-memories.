#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class C_EnemyPatterns
{
public:
	static C_EnemyPatterns* create();
	inline static C_EnemyPatterns* getInstance() { return m_pInstance; }
public:
	void circleNWay
	(
		const Vec2& vecStartpos,
		const int nWayCount,
		const float fStartAngle,
		const float fSpeed,
		const float fScale,
		const Rect& recUseTexture
	);
	void aimingNWay
	(
		const Vec2& vecStartpos,
		const int nWay,
		const float fStartAngle,
		const float fAddAngle,
		const float fSpeed,
		const Rect& recUseTexture
	);
	void summon(const Vec2& vecSummonpos);
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