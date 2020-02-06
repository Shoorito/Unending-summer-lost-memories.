#pragma once
#include "cocos2d.h"

USING_NS_CC;

class C_FieldManager : public Node
{
public:
	// INFO : "FieldManager" ��������.
	// @return = m_pInstance(singleton Type)
	static C_FieldManager* create();

	// INFO : "FieldManager" ��������.
	// @return = m_pInstance(singleton Type)
	static inline C_FieldManager* getInstance() { return m_pInstance; }
public:
	// INFO : �� ��ü�� ��ȯ�ϴ� �������� ����ϴ� ��带 ��ȯ�մϴ�.
	// �ش� ��带 ���� �� ��ü�� ��ȯ�ϴ� ������ ȣ��˴ϴ�.
	// @return = m_pStageEventNode >> STAGE_ENEMY_SUMMONER
	inline Node* getScheduleNode() { return m_pStageEventNode; }
public:
	// INFO : "update"�Լ��� "m_isUpdate"�� ���� �����ְ� ���� ��� �ش� ���� "false"�� �ǵ����ϴ�.
	// "pause"�� ���� ������� "update"�Լ��� �����ְ� �� ��쿡�� ������ �ʽ��ϴ�.
	void unDelay();

	// INFO : ������ Ŭ���� ���� ��� �ߵ��Ǵ� �̺�Ʈ �����Դϴ�.
	// �ַ� ��ȭ�̺�Ʈ�� �ߵ���Ű�ų� ���� ���������� �̾��ִ� �뵵�� ���Դϴ�.
	void callGameClear();

	// INFO : ������ �����̳� ������ ������ ���� ���� �÷��̾��� ü���� 0�� ���� ��� �ߵ��˴ϴ�.
	// �ش� �������� ���� ���� �� ��� "HighScore"���� ������ ������� �ʽ��ϴ�.
	void callGameOver();
public:
	// INFO : �ش� Ŭ���� �� �̺�Ʈ�� �����Ű�� ī��Ʈ�� ������ ������ �ٲߴϴ�.
	// �ַ� �׽�Ʈ�� ���� ����ϴ� ����̹Ƿ�, ���� ���ӿ����� ������ �ʽ��ϴ�.
	// @param = nCount >> EVENT_COUNT
	void setEventCount(const int nCount);

	// INFO : ���� �÷��̾ ���� ���� ���������� ���� ���� �������������� ���� ���θ� �����մϴ�.
	// �ش� ������ "�ʵ� �̺�Ʈ"�� ������ �ֹǷ� ���� �������� �ٸ� �Լ��μ� ������Ѿ� �մϴ�.
	// @param = isStage >> IS_NOW_BOSS_STAGE
	void setNowBossStage(const bool isStage);

	// INFO : �ʵ� ���� ��ü�� Ȱ��ȭ/��Ȱ��ȭ ��ŵ�ϴ�.
	// @WARNING �ش� ����� ����ϸ� �ʵ��� ��� �̺�Ʈ�� ���߹Ƿ� �����ؾ� �մϴ�.
	// @param = isEnabled >> FIELD_IS_ENABLED
	void setEnabled(const bool isEnabled);
public:

	// INFO : ���� �ʵ� ���� �̺�Ʈ�� Ȱ��ȭ �Ǿ��ִ����� ���� ��ȯ�մϴ�.
	// @return = m_isEnabled >> IS_EVENT_ENABLED
	inline const bool& isEnabled() { return m_isEnabled; }

	// INFO : ���� �ʵ� ���������� ���� �������������� ���� ��ȯ�մϴ�.
	// @return = m_isNowBossStage >> IS_BOSS_STAGE
	inline const bool& isNowBossStage() { return m_isNowBossStage; }
private:
	// INFO : "Node"��ü�� "init"�Լ��� �������̵��� �Լ��Դϴ�.
	// �ɹ� ���� �ʱ�ȭ �̿��� �۾��� �ϰ� ���� �ʽ��ϴ�.
	// @return = isInitializeSuccess = IS_SUCCESS?
	bool init() override;

	// INFO : "preset~"�Լ����� ��Ƴ��� �����Լ��Դϴ�.
	void preset();

	// INFO : �̺�Ʈ�� �Լ� ������ �迭�� �̸� �����س��� �뵵�� �Լ��Դϴ�.
	void presetFuncs();

	// INFO : �ߺ��� ���� "preset"�Լ��Դϴ�.
	// �ߺ����� ������ ���� �׼��� �̸� ������ ���ҽ��ϴ�.
	// ���� ���������� �þ�� ���� ���� �� ������ �Լ��Դϴ�.
	void presetMiddleBossAct();
private:
	// INFO : �������� ���Խ� �߻��ϴ� �������� ���� Ÿ��Ʋ �׼��Լ��Դϴ�.
	// �� �Լ��� ����ϸ� ���� ��ġ�� ���������� �ش��ϴ� �̹���(Sprite)�� ���� �׼��� �߻��մϴ�.
	void callTitleEvent();

	// INFO : �������� ���� �� �� ����ϴ� ������� ������ ����ȭ ���¸� �����մϴ�.
	// �ַ� ��ȭ�� ���� �׼��� ������ ����մϴ�.
	void callBossFight();
private:
	// INFO : �ش� �Լ��� ��� �� ��� Ŭ����(�̺�Ʈ) ��ü�� �Ͻ� ���� ��ŵ�ϴ�.
	// �ַ� �Ͻ����� �˾��� ��� �� ����մϴ�.
	void allPause();
private:
	// INFO : �̺�Ʈ �� �Լ����Դϴ�.
	// �Լ������ͷ� ����Ͽ� �ַ� ����մϴ�.
	// ������Ʈ �Լ����� ������ �̺�Ʈ ���� ���� �� ��� ȣ��˴ϴ�.
	void event01();
	void event02();
	void event03();
	void event04();
	void event05();
	void event06();
	void event07();
	void event08();
private:
	// INFO : �� ��ü ��ȯ�� ������ �Լ��Դϴ�.
	// �ʵ��� �Ϲ����� ���� �����ٷ��� �̿��� ��ȯ�� �� ���˴ϴ�.
	// @param = fDelay >> FUNCTION_CALL_DELAY
	void summonEnemy01(float fDelay);
	void summonEnemy02(float fDelay);
	void summonEnemy03(float fDelay);
	void summonEnemy04(float fDelay);
private:
	// INFO : �ʵ忡�� �Ͼ�� ������Ʈ �̺�Ʈ�� �Ѱ��ϴ� "update"�̺�Ʈ �Լ��Դϴ�.
	// "preset" �Լ� �������� �����ٷ��� ȣ��Ǿ� ���˴ϴ�.
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