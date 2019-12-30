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
	void testScroll();
private:
	class C_2DScrollView* m_pScrollView;
	class C_ProgressBar*  m_pProgress;
	class C_PlayerState*  m_pPlayerState;
	class C_PlayerUI*	  m_pUI;
private:
	Sprite* m_pTarget;
private:
	static C_TestScene* m_pInstance;
};
