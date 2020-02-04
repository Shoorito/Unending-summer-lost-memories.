#pragma once

enum class E_WEAPON_TYPE
{
	E_NORMAL = 0,
	E_SUB = 1,
	E_MAX = 2
};

enum class E_ENEMY_TYPE
{
	E_NORMAL	= 0,
	E_BOSS		= 1,
	E_SUMMONER	= 2,
	E_MAX		= 3
};

enum class E_USE_TYPE
{
	E_NOT_USED	= 0,
	E_USED		= 1,
	E_MAX		= 2
};

enum class E_PATTERN
{
	E_CIRCLE_NWAY,
	E_FOLLOW_PLAYER,
	E_FOLLOW_AND_NWAY,
	E_SUMMON,
	E_AIMING_BOOM,
	E_AIMING_BULLET,
	E_AIMING_PLAYER,
	E_MAX
};

enum class E_DANMAKU
{
	E_CIRCLE,
	E_SPADE,
	E_MAX
};

enum class E_ITEM_TYPE
{
	E_UP_HP,
	E_UP_MP,
	E_UP_EXP,
	E_UP_SCORE,
	E_MAX
};