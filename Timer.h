#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class C_Timer : public Label
{
public:
	static C_Timer* create();
public:
	inline const int& getNowTime() { return m_nCount; }
public:
	inline const bool& isEnabled() { return m_isEnabled; }
public:
	void startTimer(const unsigned int nTime);
	void stopTimer();
	void setTimer(const unsigned int nTime);
	void setEnabled(const bool isEnabled);
private:
	bool init() override;
	void preset();
private:
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