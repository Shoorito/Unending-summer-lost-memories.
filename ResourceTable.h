#pragma once
#include <string>
#include "EnumList.h"

static const int g_nGaugeColors		= 3;
static const int g_nDifficultyNum	= 3;
static const int g_nCheckSkipNum	= 4;

static const Rect g_recWinArea { 290.0f, 25.0f, 700.0f, 671.0f };

static const int g_arDanmakuXSize[static_cast<int>(E_DANMAKU::E_MAX)]
{
	56, 63
};

static const int g_arDanmakuYSize[static_cast<int>(E_DANMAKU::E_MAX)]
{
	56, 67
};

static const int g_arBonusScore[4]
{
	1250000, 1500000, 2750000, 3750000
};

static const Color3B g_arGaugeColor[g_nGaugeColors]
{
	Color3B(226, 30, 63),
	Color3B(244,116, 61),
	Color3B::WHITE
};

static const Color4B g_arOutlineColor[g_nDifficultyNum]
{
	Color4B::GREEN,
	Color4B::BLUE,
	Color4B::RED
};

static int g_arInitScore[4]
{
	4, 7, 10, 99
};

static int g_arTimerCounts[7]
{
	30, 40, 40, 50, 40, 50, 58
};

static char g_arCheckSkipText[g_nCheckSkipNum]
{
	'\t', '\r', '\n', ' '
};

static std::string g_arDifficulty[g_nDifficultyNum]
{
	"EASY", "NORMAL", "HARD"
};
