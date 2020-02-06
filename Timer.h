#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class C_Timer : public Label
{
public:
	// INFO : Ÿ�̸� ���� �Լ��Դϴ�.
	// @return = pTimer >> CREATE_TIMER_POINTER
	static C_Timer* create();
public:
	// INFO : Ÿ�̸��� ���� ���� �ð��� ��ȯ�մϴ�.
	// @return = m_nCount >> REMAIN_TIME
	inline const int& getNowTime() { return m_nCount; }
public:
	// INFO : Ŭ������ Ȱ��ȭ ���θ� ��ȯ�մϴ�.
	// @return = m_isEnabled >> IS_ENABLED
	inline const bool& isEnabled() { return m_isEnabled; }
public:
	// INFO : Ÿ�̸Ӹ� �����ϵ��� �����ִ� �Լ��Դϴ�.
	// �Է��� �ð����� Ÿ�̸Ӹ� �����մϴ�.
	// @param = nTime >> START_TIME
	void startTimer(const int nTime);

	// INFO : Ÿ�̸Ӹ� ���� ��ŵ�ϴ�.
	// �Է��� �ð��� ������� �ش� �Լ��� �����Ű�� Ÿ�̸Ӵ� ������ '0'�� ���·� ����˴ϴ�.
	void stopTimer();

	// INFO : Ÿ�̸��� �ð��� �����մϴ�.
	// Ÿ�̸��� ���� Ȱ��ȭ ���ο� ������� �ð� ������ �����ϸ�
	// Ÿ�̸Ӱ� Ȱ��ȭ �Ǿ� �ִٸ� ������ �ð����� �ٽ� �帨�ϴ�.
	// @param = nTime >> SET_TIME
	void setTimer(const int nTime);

	// INFO : Ŭ������ Ȱ��ȭ/��Ȱ��ȭ ��ŵ�ϴ�.
	// @param = isEnabled >> CLASS_IS_ENABLED
	void setEnabled(const bool isEnabled);
private:
	// INFO : "Label"�� "init"�� �������̵� �� �Լ��Դϴ�.
	// Ŭ�������� �����ϴ� �ɹ� �������� �ʱ�ȭ�� �ð� �ֽ��ϴ�.
	bool init() override;
	void preset();
private:
	// INFO : "Label"�� "update"�Լ��� �������̵� �߽��ϴ�.
	// Ÿ�̸��� �ð������� ǥ�� �Ǵ� ��ҿ� ���� �����մϴ�.
	// @param fDelay >> UPDATE_DELAY
	void update(float fDelay) override;
private:
	int m_nCount;
private:
	bool m_isEnabled;
private:
	C_Timer() {}
	virtual ~C_Timer() {}
	C_Timer(C_Timer&) = delete;
	C_Timer operator=(C_Timer&) = delete;
};