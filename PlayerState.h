#pragma once
#include "cocos2d.h"

using namespace cocos2d;

enum class E_PLAYER_STATUS
{
	E_MAX_HP,
	E_MAX_MP,
	E_MAX_EXP,
	E_HIGH_SCORE,
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
	void setScore	 (const int nScore);
	void setHighScore(const int nScore);
public:
	void addHP		 (const int nAdder);
	void addMP		 (const int nAdder);
	void addEXP		 (const int nAdder);
	void addScore	 (const int nAdder);
public:
	inline const int& getHP() const 
	{ 
		return m_nPlayerHP;
	}

	inline const int& getMP() const
	{ 
		return m_nPlayerMP;
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
private:
	int m_nScore;
private:
	int m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX)]{};
private:
	static C_PlayerState* m_pInstance;
private:
	C_PlayerState() {}
	virtual ~C_PlayerState() {}
	C_PlayerState(C_PlayerState&)			= delete;
	C_PlayerState operator=(C_PlayerState&) = delete;
};