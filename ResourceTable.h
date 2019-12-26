#pragma once
#include <string>

static const int g_nScoreLimit = 2111111111;

static std::string g_strUpperByScore[3]
{
	"1,000",
	"1,000,000",
	"1,000,000,000"
};

static int g_arScoreUpper[3]
{
	999,
	999999,
	999999999
};

static int g_arInitScore[4]
{
	4, 8, 12, 99
};