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
	// INFO : "PlayerState" 생성구문.
	// @return = m_pInstance(singleton Type)
	static C_PlayerState* create();

	// INFO : "PlayerState" 참조구문.
	// @return = m_pInstance(singleton Type)
	static inline C_PlayerState* getInstance() { return m_pInstance; }
public:
	// INFO : 플레이어의 최대 체력을 설정합니다.
	// 최대 체력을 설정하는 것은 현재 체력을 설정하는 것과 별개입니다.
	// 체력 설정은 "setHP"함수를 참고하시기 바랍니다.
	// @param = nHP >> PLAYER_MAX_HP
	void setMaxHP	 (const int nHP);
	// INFO : 플레이어의 최대 마나를 설정합니다.
	// 최대 마나를 설정하는 것은 현재 마나를 설정하는 것과 별개입니다.
	// 마나 설정은 "setMP"함수를 참고하시기 바랍니다.
	// @param = nMP >> PLAYER_MAX_MP
	void setMaxMP	 (const int nMP);

	// INFO : 플레이어의 최대 경험치를 설정합니다.
	// 최대 경험치를 설정하는 것은 현재 경험치를 설정하는 것과 별개입니다.
	// 경험치 설정은 "setEXP"함수를 참고하시기 바랍니다.
	// @param = nEXP >> PLAYER_MAX_EXP
	void setMaxEXP	 (const int nEXP);
public:
	// INFO : 플레이어의 현재 체력을 설정합니다.
	// 플레이어의 체력은 최대 체력보다 높게 설정 할 수 없습니다.
	// @param = nHP >> PLAYER_HP
	void setHP		 (const int nHP);
	// INFO : 플레이어의 현재 마나를 설정합니다.
	// 플레이어의 마나는 최대 마나보다 높게 설정 할 수 없습니다.
	// @param = nMP >> PLAYER_MP
	void setMP		 (const int nMP);

	// INFO : 플레이어의 현재 경험치를 설정합니다.
	// 플레이어의 경험치는 최대 경험치 수치를 넘을 수 없으며, 넘었을 경우 레벨로 치환됩니다.
	// @param = nEXP >> PLAYER_EXP
	void setEXP		 (const int nEXP);

	// INFO : 플레이어의 공격력을 설정합니다.
	// 플레이어의 공격력은 "0x7fffffff"보다 높게 설정할 수 없습니다.
	// 플레이어의 공격력은 플레이어가 발사하는 무기 하나를 기준으로 잡습니다.
	// @param = nPower >> PLAYER_DAMAGE
	void setAttack	 (const int nPower);

	// INFO : 플레이어의 점수를 설정합니다.
	// 플레이어의 최대 점수와 연동되어 있지 않는 점을 유의하시기 바랍니다.
	// @param = nScore >> PLAYER_SCORE
	void setScore	 (const int nScore);

	// INFO : 플레이어의 레벨을 설정합니다.
	// 해당 함수로 정해진 레벨에 따라 플레이어의 보조무기 개수가 결정됩니다.
	// @param = nLevel >> PLAYER_LEVEL
	void setLevel	 (const int nLevel);

	// INFO : 플레이어의 최대 점수를 설정합니다.
	// @param = nScore >> PLAYER_HIGH_SCORE
	void setHighScore(const int nScore);
public:
	// INFO : 플레이어의 체력을 더하거나 뺍니다.
	// 플레이어의 체력은 최대 체력을 넘을 수 없습니다.
	// @param = nAdder >> PREV_PLAYER_HP + ADD_HP
	void addHP		 (const int nAdder);

	// INFO : 플레이어의 마나를 더하거나 뺍니다.
	// 플레이어의 마나는 최대 마나를 넘을 수 없습니다.
	// @param = nAdder >> PREV_PLAYER_MP + ADD_MP
	void addMP		 (const int nAdder);

	// INFO : 플레이어의 공격력을 더하거나 뺍니다.
	// 플레이어의 공격력은 최대 수치(0x7fffffff)를 넘을 수 없습니다.
	// @param = nAdder >> PREV_PLAYER_DAMAGE + ADD_DAMAGE
	void addAttack	 (const int nPower);

	// INFO : 플레이어의 경험치를 더하거나 뺍니다.
	// 플레이어의 경험치는 최대 경험치 수치를 넘을 수 없으며, 넘었을 경우 레벨로 치환됩니다.
	// @param = nAdder >> PREV_PLAYER_EXP + ADD_EXP
	void addEXP		 (const int nAdder);

	// INFO : 플레이어의 점수를 더하거나 뺍니다.
	// 플레이어의 점수는 최대 수치(0x7fffffff)를 넘거나 0이하의 값이 될 수 없습니다.
	// @param = nAdder >> PREV_PLAYER_SCORE + ADD_SCORE
	void addScore	 (const int nAdder);

	// INFO : 플레이어의 레벨을 더하거나 뺍니다.
	// 플레이어 레벨은 최대 수치(0x7fffffff)까지 설정할 수도 있으나 실질적으로 최대 보조무기 갯수를 넘어서면
	// 의미가 없습니다.(공격력의 증가가 이루어지지 않습니다.)
	// @param = nLevel >> PREV_PLAYER_LEVEL + ADD_LEVEL
	void addLevel	 (const int nLevel);
public:
	// INFO : 입력한 값에 따라 플레이어의 스테이터스 수치를 변화시킵니다.
	// 입력한 태그에 맞는 함수 포인터(스테이터스 함수)를 통해 수치를 증가, 하락 시킵니다.
	// @param = nAdd >> ADD_VALUE
	// @param = nTag >> STATUS_TYPE
	void addValueByTag(const int nAdd, const int nTag);
public:
	// INFO : 플레이어의 현재 체력을 반환합니다.
	// @return m_nPlayerHP >> PLAYER_HP
	inline const int& getHP() const 
	{ 
		return m_nPlayerHP;
	}

	// INFO : 플레이어의 현재 마나를 반환합니다.
	// @return m_nPlayerMP >> PLAYER_MP
	inline const int& getMP() const
	{ 
		return m_nPlayerMP;
	}

	// INFO : 플레이어의 현재 공격력을 반환합니다.
	// @return m_nPlayerAttack >> PLAYER_DAMAGE
	inline const int& getAttack() const
	{
		return m_nPlayerAttack;
	}

	// INFO : 플레이어의 최대 체력을 반환합니다.
	// @return m_nPlayerMaxHP >> PLAYER_MAX_HP
	inline const int& getMaxHP() const
	{ 
		return m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_HP)];
	}

	// INFO : 플레이어의 최대 마나를 반환합니다.
	// @return m_nPlayerMaxMP >> PLAYER_MAX_MP
	inline const int& getMaxMP() const
	{ 
		return m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_MP)];
	}

	// INFO : 플레이어의 최대 경험치량을 반환합니다.
	// @return m_nPlayerMaxEXP >> PLAYER_MAX_EXP
	inline const int& getMaxEXP() const
	{ 
		return m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_EXP)];
	}

	// INFO : 플레이어의 현재 점수(최대점수X)를 반환합니다.
	// @return m_nScore >> PLAYER_NOW_SCORE
	inline const int& getScore() const
	{ 
		return m_nScore;
	}


	// INFO : 플레이어의 현재 경험치량을 반환합니다.
	// @return m_nPlayerEXP >> PLAYER_NOW_EXP
	inline const int& getEXP() const
	{
		return m_nPlayerEXP;
	}

	// INFO : 플레이어의 현재 레벨을 반환합니다.
	// @return m_nLevel >> PLAYER_LEVEL
	inline const int& getLevel() const
	{
		return m_nLevel;
	}

	// INFO : 플레이어의 최대 스코어를 반환합니다.
	// @return m_nHighScore >> PLAYER_HIGH_SCORE
	inline const int& getHighScore() const
	{ 
		return m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_HIGH_SCORE)];
	}
public:
	// INFO : 플레이어의 저장 가능한 스텟을 지정 된 외부 파일에 저장합니다.
	// 패치에 따라 여럿 사항이 변할 수 있는 함수입니다.
	void savePlayerStatus();
private:
	// INFO : 맴버 변수 초기화용 함수입니다.
	void init();

	// INFO : 클래스 맴버 들에 대해서 값을 미리 설정 할 필요가 있는 값들에 대해
	// 값을 미리 설정하고, 외부파일에서 값을 불러옵니다.
	void setup();

	// INFO : 외부에 있는 플레이어 저장 파일의 암호화를 풀고 해당 파일을 읽어들여
	// 플레이어 스테이터스에 적용 시킵니다.
	// 차후 패치 될 수 있는 함수입니다.
	void loadPlayerStatus();

	// INFO : 외부 플레이어 저장 파일의 정보를 클래스 맴버 변수에 옮기는 역할을 하는 함수입니다.
	// 암호화가 풀린 상태에서 값을 옮깁니다.
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