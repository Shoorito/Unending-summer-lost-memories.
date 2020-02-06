#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class C_Timer : public Label
{
public:
	// INFO : 타이머 생성 함수입니다.
	// @return = pTimer >> CREATE_TIMER_POINTER
	static C_Timer* create();
public:
	// INFO : 타이머의 현재 남은 시간을 반환합니다.
	// @return = m_nCount >> REMAIN_TIME
	inline const int& getNowTime() { return m_nCount; }
public:
	// INFO : 클래스의 활성화 여부를 반환합니다.
	// @return = m_isEnabled >> IS_ENABLED
	inline const bool& isEnabled() { return m_isEnabled; }
public:
	// INFO : 타이머를 시작하도록 도와주는 함수입니다.
	// 입력한 시간으로 타이머를 시작합니다.
	// @param = nTime >> START_TIME
	void startTimer(const int nTime);

	// INFO : 타이머를 종료 시킵니다.
	// 입력한 시간에 관계없이 해당 함수를 실행시키면 타이머는 강제로 '0'초 상태로 종료됩니다.
	void stopTimer();

	// INFO : 타이머의 시간을 설정합니다.
	// 타이머의 현재 활성화 여부에 관계없이 시간 설정이 가능하며
	// 타이머가 활성화 되어 있다면 설정한 시간에서 다시 흐릅니다.
	// @param = nTime >> SET_TIME
	void setTimer(const int nTime);

	// INFO : 클래스를 활성화/비활성화 시킵니다.
	// @param = isEnabled >> CLASS_IS_ENABLED
	void setEnabled(const bool isEnabled);
private:
	// INFO : "Label"의 "init"을 오버라이드 한 함수입니다.
	// 클래스에서 관리하는 맴버 변수들의 초기화를 맡고 있습니다.
	bool init() override;
	void preset();
private:
	// INFO : "Label"의 "update"함수를 오버라이드 했습니다.
	// 타이머의 시각적으로 표시 되는 요소와 값을 갱신합니다.
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