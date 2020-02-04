#pragma once
#include "cocos2d.h"

USING_NS_CC;

class C_FieldManager : public Node
{
public:
	static C_FieldManager* create();
	static inline C_FieldManager* getInstance() { return m_pInstance; }
public:
	inline Node* getScheduleNode() { return m_pStageEventNode; }
public:
	void unDelay();
	void callGameOver();
public:
	void setEventCount(const int nCount);
	void setNowBossStage(const bool isStage);
	void setEnabled(const bool isEnabled);
public:
	inline const bool& isEnabled() { return m_isEnabled; }
	inline const bool& isNowBossStage() { return m_isNowBossStage; }
private:
	bool init() override;
	void preset();
	void presetFuncs();
	void presetMiddleBossAct();
private:
	void callTitleEvent();
	void callBossFight();
private:
	void allPause();
private:
	void event01();
	void event02();
	void event03();
	void event04();
	void event05();
	void event06();
public:
	void event07();
	void event08();
	void event09();
private:
	void summonEnemy01(float fDelay);
	void summonEnemy02(float fDelay);
	void summonEnemy03(float fDelay);
	void summonEnemy04(float fDelay);
private:
	void update(float fDelay);
private:
	bool m_isEnabled;
	bool m_isUpdate;
	bool m_isNowBossStage;
private:
	int m_nEventCount;
	int m_nNowEventType;
	int m_arEventTimes[8]{ 200, 1000, 1800, 2400, 3100, 5500, 6500, 6700 };
private:
	Sprite* m_pStageTitle;
	Sprite* m_pStageSubTitle;
private:
	Sequence* m_pMiddleBossAct;
private:
	Node* m_pStageEventNode;
private:
	void(C_FieldManager::*m_arEventFunc[8])();
private:
	static C_FieldManager* m_pInstance;
private:
	C_FieldManager() {}
	~C_FieldManager() {}
	C_FieldManager(C_FieldManager&) = delete;
	C_FieldManager operator=(C_FieldManager&) = delete;
};