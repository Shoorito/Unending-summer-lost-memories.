#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class C_EnemyPatterns
{
public:
	// INFO : "EnemyPatterns" ��������.
	// @return = m_pInstance(singleton Type)
	static C_EnemyPatterns* create();

	// INFO : "EnemyPatterns" ��������.
	// @return = m_pInstance(singleton Type)
	inline static C_EnemyPatterns* getInstance() { return m_pInstance; }
public:
	// INFO : �Ϲ����� ���� ź�� �����Դϴ�.
	// ���� ������ ���� �÷��̾ ���ϰ� �� ���� ������, �������̸� �ͼ��� ���� ź�� ������ ����ϴ�.
	// "NWay"�� 1���� �����ϸ� �Ϲ����� "Way-ź"ó�� ��� �� �� �ֽ��ϴ�.
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

	// INFO : ��ȯ�� ��ȯ �����Դϴ�.
	// �ش� ������ ȣ�� �� ������ "Animation"�� ���� �� ��ü�� �����ϸ� �Լ����� ������ Ÿ���� ������ �����մϴ�.
	// �ش� �������� ���� �� ���� �������� ������� ������ ������ ���� ���մϴ�.
	// @param = vecSummonpos >> START_POSITION
	void summon(const Vec2& vecSummonpos);

	// INFO : ���� �Ÿ� �̵��� ź���� ����ϰ� Ŀ���� �����Դϴ�.
	// �ش� ���ϰ� �ٸ� ������ ��� ��� �ϸ� �ſ� ��������ų�, �� �Ұ����� ������ �� �� �ֽ��ϴ�.
	// ���� �������� ������ �� �� �ְԲ� ���� �� �����Դϴ�.
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