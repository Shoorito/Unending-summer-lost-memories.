#pragma once
#include "cocos2d.h"

USING_NS_CC;

class C_FieldManager : public Node
{
public:
	// INFO : "FieldManager" 생성구문.
	// @return = m_pInstance(singleton Type)
	static C_FieldManager* create();

	// INFO : "FieldManager" 참조구문.
	// @return = m_pInstance(singleton Type)
	static inline C_FieldManager* getInstance() { return m_pInstance; }
public:
	// INFO : 적 개체를 소환하는 스케줄을 담당하는 노드를 반환합니다.
	// 해당 노드를 통해 적 개체를 소환하는 구문이 호출됩니다.
	// @return = m_pStageEventNode >> STAGE_ENEMY_SUMMONER
	inline Node* getScheduleNode() { return m_pStageEventNode; }
public:
	// INFO : "update"함수를 "m_isUpdate"를 통해 멈춰있게 했을 경우 해당 값을 "false"로 되돌립니다.
	// "pause"와 같은 기능으로 "update"함수를 멈춰있게 한 경우에는 통하지 않습니다.
	void unDelay();

	// INFO : 보스를 클리어 했을 경우 발동되는 이벤트 구문입니다.
	// 주로 대화이벤트를 발동시키거나 다음 스테이지로 이어주는 용도로 쓰입니다.
	void callGameClear();

	// INFO : 몬스터의 공격이나 모종의 이유로 게임 도중 플레이어의 체력이 0이 됐을 경우 발동됩니다.
	// 해당 구문으로 게임 오버 된 경우 "HighScore"등의 정보가 저장되지 않습니다.
	void callGameOver();
public:
	// INFO : 해당 클래스 내 이벤트를 실행시키는 카운트를 지정한 값으로 바꿉니다.
	// 주로 테스트를 위해 사용하는 기능이므로, 실제 게임에서는 사용되지 않습니다.
	// @param = nCount >> EVENT_COUNT
	void setEventCount(const int nCount);

	// INFO : 현재 플레이어가 진행 중인 스테이지에 대해 보스 스테이지인지에 대한 여부를 지정합니다.
	// 해당 구문은 "필드 이벤트"에 영향을 주므로 실제 보스전은 다른 함수로서 실행시켜야 합니다.
	// @param = isStage >> IS_NOW_BOSS_STAGE
	void setNowBossStage(const bool isStage);

	// INFO : 필드 관리 개체를 활성화/비활성화 시킵니다.
	// @WARNING 해당 기능을 사용하면 필드의 모든 이벤트가 멈추므로 주의해야 합니다.
	// @param = isEnabled >> FIELD_IS_ENABLED
	void setEnabled(const bool isEnabled);
public:

	// INFO : 현재 필드 관리 이벤트가 활성화 되어있는지에 대해 반환합니다.
	// @return = m_isEnabled >> IS_EVENT_ENABLED
	inline const bool& isEnabled() { return m_isEnabled; }

	// INFO : 현재 필드 스테이지가 보스 스테이지인지에 대해 반환합니다.
	// @return = m_isNowBossStage >> IS_BOSS_STAGE
	inline const bool& isNowBossStage() { return m_isNowBossStage; }
private:
	// INFO : "Node"개체의 "init"함수를 오버라이드한 함수입니다.
	// 맴버 변수 초기화 이외의 작업은 하고 있지 않습니다.
	// @return = isInitializeSuccess = IS_SUCCESS?
	bool init() override;

	// INFO : "preset~"함수들을 모아놓은 편의함수입니다.
	void preset();

	// INFO : 이벤트용 함수 포인터 배열을 미리 지정해놓는 용도의 함수입니다.
	void presetFuncs();

	// INFO : 중보스 전용 "preset"함수입니다.
	// 중보스가 등장할 때의 액션을 미리 생성해 놓았습니다.
	// 추후 스테이지가 늘어남에 따라 개편 될 예정의 함수입니다.
	void presetMiddleBossAct();
private:
	// INFO : 스테이지 진입시 발생하는 스테이지 정보 타이틀 액션함수입니다.
	// 이 함수를 사용하면 현재 위치한 스테이지에 해당하는 이미지(Sprite)에 대한 액션이 발생합니다.
	void callTitleEvent();

	// INFO : 보스전이 시작 될 때 사용하는 기능으로 보스의 무적화 상태를 해제합니다.
	// 주로 대화나 등장 액션이 끝나고 사용합니다.
	void callBossFight();
private:
	// INFO : 해당 함수에 등록 된 모든 클래스(이벤트) 개체를 일시 정지 시킵니다.
	// 주로 일시정지 팝업을 띄울 때 사용합니다.
	void allPause();
private:
	// INFO : 이벤트 용 함수들입니다.
	// 함수포인터로 등록하여 주로 사용합니다.
	// 업데이트 함수에서 지정한 이벤트 값이 충족 될 경우 호출됩니다.
	void event01();
	void event02();
	void event03();
	void event04();
	void event05();
	void event06();
	void event07();
	void event08();
private:
	// INFO : 적 개체 소환용 스케줄 함수입니다.
	// 필드의 일반적인 적을 스케줄러를 이용해 소환할 때 사용됩니다.
	// @param = fDelay >> FUNCTION_CALL_DELAY
	void summonEnemy01(float fDelay);
	void summonEnemy02(float fDelay);
	void summonEnemy03(float fDelay);
	void summonEnemy04(float fDelay);
private:
	// INFO : 필드에서 일어나는 업데이트 이벤트를 총괄하는 "update"이벤트 함수입니다.
	// "preset" 함수 구문에서 스케줄러로 호출되어 사용됩니다.
	// @param = fDelay >> FUNCTION_CALL_DELAY
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