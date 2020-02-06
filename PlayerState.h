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
	// INFO : "PlayerState" ��������.
	// @return = m_pInstance(singleton Type)
	static C_PlayerState* create();

	// INFO : "PlayerState" ��������.
	// @return = m_pInstance(singleton Type)
	static inline C_PlayerState* getInstance() { return m_pInstance; }
public:
	// INFO : �÷��̾��� �ִ� ü���� �����մϴ�.
	// �ִ� ü���� �����ϴ� ���� ���� ü���� �����ϴ� �Ͱ� �����Դϴ�.
	// ü�� ������ "setHP"�Լ��� �����Ͻñ� �ٶ��ϴ�.
	// @param = nHP >> PLAYER_MAX_HP
	void setMaxHP	 (const int nHP);
	// INFO : �÷��̾��� �ִ� ������ �����մϴ�.
	// �ִ� ������ �����ϴ� ���� ���� ������ �����ϴ� �Ͱ� �����Դϴ�.
	// ���� ������ "setMP"�Լ��� �����Ͻñ� �ٶ��ϴ�.
	// @param = nMP >> PLAYER_MAX_MP
	void setMaxMP	 (const int nMP);

	// INFO : �÷��̾��� �ִ� ����ġ�� �����մϴ�.
	// �ִ� ����ġ�� �����ϴ� ���� ���� ����ġ�� �����ϴ� �Ͱ� �����Դϴ�.
	// ����ġ ������ "setEXP"�Լ��� �����Ͻñ� �ٶ��ϴ�.
	// @param = nEXP >> PLAYER_MAX_EXP
	void setMaxEXP	 (const int nEXP);
public:
	// INFO : �÷��̾��� ���� ü���� �����մϴ�.
	// �÷��̾��� ü���� �ִ� ü�º��� ���� ���� �� �� �����ϴ�.
	// @param = nHP >> PLAYER_HP
	void setHP		 (const int nHP);
	// INFO : �÷��̾��� ���� ������ �����մϴ�.
	// �÷��̾��� ������ �ִ� �������� ���� ���� �� �� �����ϴ�.
	// @param = nMP >> PLAYER_MP
	void setMP		 (const int nMP);

	// INFO : �÷��̾��� ���� ����ġ�� �����մϴ�.
	// �÷��̾��� ����ġ�� �ִ� ����ġ ��ġ�� ���� �� ������, �Ѿ��� ��� ������ ġȯ�˴ϴ�.
	// @param = nEXP >> PLAYER_EXP
	void setEXP		 (const int nEXP);

	// INFO : �÷��̾��� ���ݷ��� �����մϴ�.
	// �÷��̾��� ���ݷ��� "0x7fffffff"���� ���� ������ �� �����ϴ�.
	// �÷��̾��� ���ݷ��� �÷��̾ �߻��ϴ� ���� �ϳ��� �������� ����ϴ�.
	// @param = nPower >> PLAYER_DAMAGE
	void setAttack	 (const int nPower);

	// INFO : �÷��̾��� ������ �����մϴ�.
	// �÷��̾��� �ִ� ������ �����Ǿ� ���� �ʴ� ���� �����Ͻñ� �ٶ��ϴ�.
	// @param = nScore >> PLAYER_SCORE
	void setScore	 (const int nScore);

	// INFO : �÷��̾��� ������ �����մϴ�.
	// �ش� �Լ��� ������ ������ ���� �÷��̾��� �������� ������ �����˴ϴ�.
	// @param = nLevel >> PLAYER_LEVEL
	void setLevel	 (const int nLevel);

	// INFO : �÷��̾��� �ִ� ������ �����մϴ�.
	// @param = nScore >> PLAYER_HIGH_SCORE
	void setHighScore(const int nScore);
public:
	// INFO : �÷��̾��� ü���� ���ϰų� ���ϴ�.
	// �÷��̾��� ü���� �ִ� ü���� ���� �� �����ϴ�.
	// @param = nAdder >> PREV_PLAYER_HP + ADD_HP
	void addHP		 (const int nAdder);

	// INFO : �÷��̾��� ������ ���ϰų� ���ϴ�.
	// �÷��̾��� ������ �ִ� ������ ���� �� �����ϴ�.
	// @param = nAdder >> PREV_PLAYER_MP + ADD_MP
	void addMP		 (const int nAdder);

	// INFO : �÷��̾��� ���ݷ��� ���ϰų� ���ϴ�.
	// �÷��̾��� ���ݷ��� �ִ� ��ġ(0x7fffffff)�� ���� �� �����ϴ�.
	// @param = nAdder >> PREV_PLAYER_DAMAGE + ADD_DAMAGE
	void addAttack	 (const int nPower);

	// INFO : �÷��̾��� ����ġ�� ���ϰų� ���ϴ�.
	// �÷��̾��� ����ġ�� �ִ� ����ġ ��ġ�� ���� �� ������, �Ѿ��� ��� ������ ġȯ�˴ϴ�.
	// @param = nAdder >> PREV_PLAYER_EXP + ADD_EXP
	void addEXP		 (const int nAdder);

	// INFO : �÷��̾��� ������ ���ϰų� ���ϴ�.
	// �÷��̾��� ������ �ִ� ��ġ(0x7fffffff)�� �Ѱų� 0������ ���� �� �� �����ϴ�.
	// @param = nAdder >> PREV_PLAYER_SCORE + ADD_SCORE
	void addScore	 (const int nAdder);

	// INFO : �÷��̾��� ������ ���ϰų� ���ϴ�.
	// �÷��̾� ������ �ִ� ��ġ(0x7fffffff)���� ������ ���� ������ ���������� �ִ� �������� ������ �Ѿ��
	// �ǹ̰� �����ϴ�.(���ݷ��� ������ �̷������ �ʽ��ϴ�.)
	// @param = nLevel >> PREV_PLAYER_LEVEL + ADD_LEVEL
	void addLevel	 (const int nLevel);
public:
	// INFO : �Է��� ���� ���� �÷��̾��� �������ͽ� ��ġ�� ��ȭ��ŵ�ϴ�.
	// �Է��� �±׿� �´� �Լ� ������(�������ͽ� �Լ�)�� ���� ��ġ�� ����, �϶� ��ŵ�ϴ�.
	// @param = nAdd >> ADD_VALUE
	// @param = nTag >> STATUS_TYPE
	void addValueByTag(const int nAdd, const int nTag);
public:
	// INFO : �÷��̾��� ���� ü���� ��ȯ�մϴ�.
	// @return m_nPlayerHP >> PLAYER_HP
	inline const int& getHP() const 
	{ 
		return m_nPlayerHP;
	}

	// INFO : �÷��̾��� ���� ������ ��ȯ�մϴ�.
	// @return m_nPlayerMP >> PLAYER_MP
	inline const int& getMP() const
	{ 
		return m_nPlayerMP;
	}

	// INFO : �÷��̾��� ���� ���ݷ��� ��ȯ�մϴ�.
	// @return m_nPlayerAttack >> PLAYER_DAMAGE
	inline const int& getAttack() const
	{
		return m_nPlayerAttack;
	}

	// INFO : �÷��̾��� �ִ� ü���� ��ȯ�մϴ�.
	// @return m_nPlayerMaxHP >> PLAYER_MAX_HP
	inline const int& getMaxHP() const
	{ 
		return m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_HP)];
	}

	// INFO : �÷��̾��� �ִ� ������ ��ȯ�մϴ�.
	// @return m_nPlayerMaxMP >> PLAYER_MAX_MP
	inline const int& getMaxMP() const
	{ 
		return m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_MP)];
	}

	// INFO : �÷��̾��� �ִ� ����ġ���� ��ȯ�մϴ�.
	// @return m_nPlayerMaxEXP >> PLAYER_MAX_EXP
	inline const int& getMaxEXP() const
	{ 
		return m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_MAX_EXP)];
	}

	// INFO : �÷��̾��� ���� ����(�ִ�����X)�� ��ȯ�մϴ�.
	// @return m_nScore >> PLAYER_NOW_SCORE
	inline const int& getScore() const
	{ 
		return m_nScore;
	}


	// INFO : �÷��̾��� ���� ����ġ���� ��ȯ�մϴ�.
	// @return m_nPlayerEXP >> PLAYER_NOW_EXP
	inline const int& getEXP() const
	{
		return m_nPlayerEXP;
	}

	// INFO : �÷��̾��� ���� ������ ��ȯ�մϴ�.
	// @return m_nLevel >> PLAYER_LEVEL
	inline const int& getLevel() const
	{
		return m_nLevel;
	}

	// INFO : �÷��̾��� �ִ� ���ھ ��ȯ�մϴ�.
	// @return m_nHighScore >> PLAYER_HIGH_SCORE
	inline const int& getHighScore() const
	{ 
		return m_arSaveStatus[static_cast<int>(E_PLAYER_STATUS::E_HIGH_SCORE)];
	}
public:
	// INFO : �÷��̾��� ���� ������ ������ ���� �� �ܺ� ���Ͽ� �����մϴ�.
	// ��ġ�� ���� ���� ������ ���� �� �ִ� �Լ��Դϴ�.
	void savePlayerStatus();
private:
	// INFO : �ɹ� ���� �ʱ�ȭ�� �Լ��Դϴ�.
	void init();

	// INFO : Ŭ���� �ɹ� �鿡 ���ؼ� ���� �̸� ���� �� �ʿ䰡 �ִ� ���鿡 ����
	// ���� �̸� �����ϰ�, �ܺ����Ͽ��� ���� �ҷ��ɴϴ�.
	void setup();

	// INFO : �ܺο� �ִ� �÷��̾� ���� ������ ��ȣȭ�� Ǯ�� �ش� ������ �о�鿩
	// �÷��̾� �������ͽ��� ���� ��ŵ�ϴ�.
	// ���� ��ġ �� �� �ִ� �Լ��Դϴ�.
	void loadPlayerStatus();

	// INFO : �ܺ� �÷��̾� ���� ������ ������ Ŭ���� �ɹ� ������ �ű�� ������ �ϴ� �Լ��Դϴ�.
	// ��ȣȭ�� Ǯ�� ���¿��� ���� �ű�ϴ�.
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