#include "Timer.h"
#include "Boss.h"
#include "BossManager.h"
#include "CocosFunctions.h"
#include "AudioEngine.h"

using namespace experimental;

C_Timer * C_Timer::create()
{
	C_Timer* pTimer(nullptr);

	pTimer = new(std::nothrow) C_Timer();

	if (pTimer && pTimer->init())
	{
		pTimer->preset();
	}
	else
	{
		C_Functions::safeDelete(pTimer);
	}

	return pTimer;
}

void C_Timer::startTimer(const unsigned int nTime)
{
	enableOutline(Color4B(0, 0, 0, 0));
	setTimer(nTime);
	setEnabled(true);
}

void C_Timer::stopTimer()
{
	enableOutline(Color4B(0, 0, 0, 0));
	setEnabled(false);
	setTimer(0);
}

void C_Timer::setTimer(const unsigned int nTime)
{
	std::string strTime("");

	m_nCount = nTime;

	if (m_nCount < 10)
		strTime += '0';

	if (m_nCount < 10 && m_nCount > 0)
	{
		if (m_nCount <= 5)
		{
			enableOutline(Color4B(255, 0, 0, 255), 2);
			//AudioEngine::play2d("se_time_under_05.mp3", false, 0.1f);
		}
		else
		{
			enableOutline(Color4B(244, 178, 35, 255), 2);
			//AudioEngine::play2d("se_time_under_10.mp3", false, 0.1f);
		}
	}

	strTime += std::to_string(m_nCount);

	setString(strTime);
}

void C_Timer::setEnabled(const bool isEnabled)
{
	if (m_isEnabled == isEnabled)
		return;

	m_isEnabled = isEnabled;

	setVisible(m_isEnabled);

	if (m_isEnabled)
		resume();
	else
		pause();
}

bool C_Timer::init()
{
	if (!Node::init())
		return false;

	m_nCount	= 0;
	m_isEnabled = false;

	return true;
}

void C_Timer::preset()
{
	schedule(schedule_selector(C_Timer::update), 1.0f);
	
	pause();
	setVisible(false);
}

void C_Timer::update(float fDelay)
{
	if (m_nCount < 1)
	{
		stopTimer();

		C_BossManager::getInstance()->getBoss()->setHP(0.0f);

		return;
	}

	setTimer(m_nCount);

	m_nCount--;
}
