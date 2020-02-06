#pragma once
#include <vector>
#include <string>

class C_BossStatus
{
public:
	// INFO : "BossStatus" 생성구문.
	// @return = m_pInstance(singleton Type)
	static C_BossStatus* create();

	// INFO : "BossStatus" 참조구문.
	// @return = m_pInstance(singleton Type)
	inline static C_BossStatus* getInstance() { return m_pInstance; }
public:
	// INFO : 클래스에 지정 된 "BossName"을 반환합니다.
	// @return = m_strBossName >> BOSS_NAME
	inline const std::string& getBossName()
	{
		return m_strBossName;
	}

	// INFO : 페이즈 단위의 "BossStatus"의 개수를 반환합니다.
	// @return = List.size() >> STATUS_LIST_SIZE
	inline const int getBarCount() const
	{
		return static_cast<int>(m_vecBarTypeList.size());
	}

	// INFO : 클래스가 가지고 있는 BarTypeList의 [nPosition]번째 값을 반환합니다.
	// 해당 값은 한 페이즈에 보스가 가지고 있는 "HP_BAR"의 개수를 의미합니다.
	// @param  = nPosition			>> LIST_ARRAY_POSITION
	// @return = HP_BAR_LIST.size() >> STATUS_LIST_SIZE
	inline const int& getBarTypeCount(const int nPosition)
	{
		return m_vecBarTypeList[nPosition];
	}

	// INFO : 클래스가 가지고 있는 보스의 "HP"값을 리스트의 [n페이즈][n번째] 값을 반환합니다.
	// @param  = nBarType  >> PAZE_TYPE
	// @param  = nPosition >> ARRAY_NUMBER
	// @return = HP_List[PAZE][POSITION]
	inline const int& getBarHP(const int nBarType, const int nPosition)
	{
		return m_vecHPList[nBarType][nPosition];
	}

	// INFO : 클래스가 가지고 있는 보스의 "PATTERN_NAME"값을 리스트의 [n페이즈][n번째] 값을 반환합니다.
	// @param  = nSpellType  >> PAZE_TYPE
	// @param  = nPosition	 >> ARRAY_NUMBER
	// @return = Pattern_Name_List[PAZE][POSITION]
	inline const std::string& getSpellName(const int nSpellType, const int nPosition)
	{
		return m_vecSpellList[nSpellType][nPosition];
	}
public:
	// INFO : 보스의 이름을 지정합니다.
	// @param  = strName  >> BOSS_NAME
	void setBossName(const std::string& strName);
public:
	// INFO : 페이즈 단위를 추가합니다.
	// 페이즈 단위 추가 시 함수 내에서 해당 페이즈의 "HP, SPELLNAME"을 추가 할 수 있는 "VectorList"를 추가합니다.
	// 해당 함수에 추가 된 값은 "HP"의 페이즈 단위 "BAR_COUNT"가 됩니다.
	// @param  = nType  >> IN_PAZE_HP_COUNT
	void addBarType(const int nType);

	// INFO : [nPosition]번째 페이즈의 HP_LIST에 사용 할 "HP"를 추가합니다.
	// @param = nHP >> USE_HP
	// @param = nPosition >> PAZE_NUMBER
	void addBarHP(const int nHP, const int nPosition);

	// INFO : [nPosition]번째 페이즈의 SPELL_NAME_LIST에 사용 할 "SPELL_NAME"를 추가합니다.
	// @param = nHP >> USE_HP
	// @param = nPosition >> PAZE_NUMBER
	void addSpellName(const std::string& strSpellName, const int nPosition);
public:
	// INFO : 페이즈 단위 정보를 "LIFO(후입선출)" 순으로 제거합니다.
	void removeBarType();
public:
	// INFO : "BossName"을 초기화 합니다.(길이 0 상태로 만듬)
	void clearName();

	// INFO : 페이즈 단위 정보를 초기화 합니다.(길이 0 상태로 만듬, 데이터 공간은 사라지지 않음.)
	// "clear~" 이름 뒤 정보들은 초기화 대상을 의미합니다.(부분적인 초기화를 원할 경우 사용)
	void clearBarType();
	void clearBarHP();
	void clearSpellName();

	// INFO : 모든 페이즈 단위 정보를 초기화 합니다.
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