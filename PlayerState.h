#pragma once
#include "cocos2d.h"

using namespace cocos2d;

enum class E_PLAYER_STATUS
{
	E_MAX_HP,
	E_MAX_MP,
	E_MAX_EXP,
	E_HIGH_SCORE,
	E_ATTACK,
	E_MAX
};

enum class E_GAIN_STAT
{
	E_HP,
	E_MP,
	E_EXP,
	E_SCORE,
	E_MAX
};

class C_PlayerState
{
public:
	static C_PlayerState* create();
	static inline C_PlayerState* getInstance() { return m_pInstance; }
public:
	void setMaxHP	 (const int nHP);
	void setMaxMP	 (const int nMP);
	void setMaxEXP	 (const int nEXP);
public:
	void setHP		 (const int nHP);
	void setMP		 (const int nMP);
	void setEXP		 (const int nEXP);
	void setAttack	 (const int nPower);
	void setScore	 (const int nScore);
	void setLevel	 (const int nLevel);
	void setHighScore(const int nScore);
public:
	void addHP		 (const int nAdder);
	void addMP		 (const int nAdder);
	void addAttack	 (const int nPower);
	void addEXP		 (const int nAdder);
	void addScore	 (const int nAdder);
	void addLevel	 (const int nLevel);
public:
	void addValueByTag(const int nAdd, const int nTag);
public:
	inline const int& getHP() const 
	{ 
		return m_nPlayerHP;
	}

	inline const int& getMP() const
	{ 
		return m_nPlayerMP;
	}

	inline const int& getAttack() const
	{
		return m_nPlayerAttack;
	}

	inline const int& getMaxHP() const
	{ 
		return m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_HP)];
	}

	inline const int& getMaxMP() const
	{ 
		return m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_MP)];
	}

	inline const int& getMaxEXP() const
	{ 
		return m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_EXP)];
	}

	inline const int& getScore() const
	{ 
		return m_nScore;
	}

	inline const int& getEXP() const
	{
		return m_nPlayerEXP;
	}

	inline const int& getLevel() const
	{
		return m_nLevel;
	}

	inline const int& getHighScore() const
	{ 
		return m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_HIGH_SCORE)];
	}
public:
	void savePlayerStatus();
private:
	void init();
	void setup();
	void loadPlayerStatus();
	void readFile(const std::string& strInfo);
private:
	int m_nPlayerHP;
	int m_nPlayerMP;
	int m_nPlayerEXP;
	int m_nPlayerAttack;
	int m_nScore;
	int m_nLevel;
private:
	unsigned int m_nMaxScore;
private:
	int m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX)]{};
private:
	std::string m_strEncryptKey{};
private:
	std::string m_arSaveStatusName[static_cast<int>(E_PLAYER_STATUS::E_MAX)]{};
private:
	void(C_PlayerState::*m_arAddFuncs[static_cast<int>(E_GAIN_STAT::E_MAX)])(const int);
private:
	static C_PlayerState* m_pInstance;
private:
	C_PlayerState() {}
	virtual ~C_PlayerState() {}
	C_PlayerState(C_PlayerState&)			= delete;
	C_PlayerState operator=(C_PlayerState&) = delete;
};