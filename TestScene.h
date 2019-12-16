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
private:
	void update(float dt);
private:
	class C_2DScrollView* m_pScrollView;
	class C_ProgressBar* m_pProgress;
private:
	int m_nNowpos;
	Sprite* m_pTarget;
private:
	static C_TestScene* m_pInstance;
};
