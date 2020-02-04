#pragma once
#include <vector>
#include <string>

class C_BossStatus
{
public:
	static C_BossStatus* create();
	inline static C_BossStatus* getInstance() { return m_pInstance; }
public:
	inline const std::string& getBossName()
	{
		return m_strBossName;
	}
	inline const int getBarCount() const
	{
		return static_cast<int>(m_vecBarTypeList.size());
	}
	inline const int& getBarTypeCount(const int nPosition)
	{
		return m_vecBarTypeList[nPosition];
	}
	inline const int& getBarHP(const int nBarType, const int nPosition)
	{
		return m_vecHPList[nBarType][nPosition];
	}
	inline const std::string& getSpellName(const int nSpellType, const int nPosition)
	{
		return m_vecSpellList[nSpellType][nPosition];
	}
public:
	void setBossName(const std::string& strName);
public:
	void addBarType(const int nType);
	void addBarHP(const int nHP, const int nPosition);
	void addSpellName(const std::string& strSpellName, const int nPosition);
public:
	void removeBarType();
	void removeBarHP(const int nPosition);
	void removeSpellName(const int nPosition);
public:
	void clearName();
	void clearBarType();
	void clearBarHP();
	void clearSpellName();
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