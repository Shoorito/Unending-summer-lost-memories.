#pragma once
#include "cocos2d.h"

USING_NS_CC;

class C_2DScrollView;

class C_TestScene : public Scene
{
public:
	static C_TestScene* create();
	static inline C_TestScene* getInstance() { return m_pInstance; }
private:
    bool init() override;
	void preset();
	void testFunc();
	void testScroll();
	void testProgress();
	void testPlayerUI();
	bool testIsComa(const int nPosition);
	void testUpdateLength(int nAdder, int nSize);
	int  testPosComa(const int nSqrt);
	int	 testDigits(const int nNumber);
private:
	void update(float dt);
private:
	class C_2DScrollView* m_pScrollView;
	class C_ProgressBar*  m_pProgress;
private:
	int m_nTestScore;
	int m_nNowUsedComa;
	Sprite* m_pTarget;
	Label* m_pTestScore;
	std::string m_strTestScore;
private:
	static C_TestScene* m_pInstance;
};
