#pragma once
#include <vector>
#include <string>

class C_BossStatus
{
public:
	// INFO : "BossStatus" ��������.
	// @return = m_pInstance(singleton Type)
	static C_BossStatus* create();

	// INFO : "BossStatus" ��������.
	// @return = m_pInstance(singleton Type)
	inline static C_BossStatus* getInstance() { return m_pInstance; }
public:
	// INFO : Ŭ������ ���� �� "BossName"�� ��ȯ�մϴ�.
	// @return = m_strBossName >> BOSS_NAME
	inline const std::string& getBossName()
	{
		return m_strBossName;
	}

	// INFO : ������ ������ "BossStatus"�� ������ ��ȯ�մϴ�.
	// @return = List.size() >> STATUS_LIST_SIZE
	inline const int getBarCount() const
	{
		return static_cast<int>(m_vecBarTypeList.size());
	}

	// INFO : Ŭ������ ������ �ִ� BarTypeList�� [nPosition]��° ���� ��ȯ�մϴ�.
	// �ش� ���� �� ����� ������ ������ �ִ� "HP_BAR"�� ������ �ǹ��մϴ�.
	// @param  = nPosition			>> LIST_ARRAY_POSITION
	// @return = HP_BAR_LIST.size() >> STATUS_LIST_SIZE
	inline const int& getBarTypeCount(const int nPosition)
	{
		return m_vecBarTypeList[nPosition];
	}

	// INFO : Ŭ������ ������ �ִ� ������ "HP"���� ����Ʈ�� [n������][n��°] ���� ��ȯ�մϴ�.
	// @param  = nBarType  >> PAZE_TYPE
	// @param  = nPosition >> ARRAY_NUMBER
	// @return = HP_List[PAZE][POSITION]
	inline const int& getBarHP(const int nBarType, const int nPosition)
	{
		return m_vecHPList[nBarType][nPosition];
	}

	// INFO : Ŭ������ ������ �ִ� ������ "PATTERN_NAME"���� ����Ʈ�� [n������][n��°] ���� ��ȯ�մϴ�.
	// @param  = nSpellType  >> PAZE_TYPE
	// @param  = nPosition	 >> ARRAY_NUMBER
	// @return = Pattern_Name_List[PAZE][POSITION]
	inline const std::string& getSpellName(const int nSpellType, const int nPosition)
	{
		return m_vecSpellList[nSpellType][nPosition];
	}
public:
	// INFO : ������ �̸��� �����մϴ�.
	// @param  = strName  >> BOSS_NAME
	void setBossName(const std::string& strName);
public:
	// INFO : ������ ������ �߰��մϴ�.
	// ������ ���� �߰� �� �Լ� ������ �ش� �������� "HP, SPELLNAME"�� �߰� �� �� �ִ� "VectorList"�� �߰��մϴ�.
	// �ش� �Լ��� �߰� �� ���� "HP"�� ������ ���� "BAR_COUNT"�� �˴ϴ�.
	// @param  = nType  >> IN_PAZE_HP_COUNT
	void addBarType(const int nType);

	// INFO : [nPosition]��° �������� HP_LIST�� ��� �� "HP"�� �߰��մϴ�.
	// @param = nHP >> USE_HP
	// @param = nPosition >> PAZE_NUMBER
	void addBarHP(const int nHP, const int nPosition);

	// INFO : [nPosition]��° �������� SPELL_NAME_LIST�� ��� �� "SPELL_NAME"�� �߰��մϴ�.
	// @param = nHP >> USE_HP
	// @param = nPosition >> PAZE_NUMBER
	void addSpellName(const std::string& strSpellName, const int nPosition);
public:
	// INFO : ������ ���� ������ "LIFO(���Լ���)" ������ �����մϴ�.
	void removeBarType();
public:
	// INFO : "BossName"�� �ʱ�ȭ �մϴ�.(���� 0 ���·� ����)
	void clearName();

	// INFO : ������ ���� ������ �ʱ�ȭ �մϴ�.(���� 0 ���·� ����, ������ ������ ������� ����.)
	// "clear~" �̸� �� �������� �ʱ�ȭ ����� �ǹ��մϴ�.(�κ����� �ʱ�ȭ�� ���� ��� ���)
	void clearBarType();
	void clearBarHP();
	void clearSpellName();

	// INFO : ��� ������ ���� ������ �ʱ�ȭ �մϴ�.
	void clearAllInformation();
private:
	void init();
private:
	std::string m_strBossName;
private:
	std::vector<int> m_vecBarTypeList;
	std::vector<std::vector<int>> m_vecHPList;
	std::vector<std::vector<std::string>> m_vecSpellList;
private:
	static C_BossStatus* m_pInstance;
private:
	C_BossStatus() {}
	virtual ~C_BossStatus() {}
	C_BossStatus(C_BossStatus&) = delete;
	C_BossStatus operator=(C_BossStatus&) = delete;
};