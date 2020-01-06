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
	void testKeyEvent();
	void testScroll();
	void testController();
	void testWeaponLauncher();
	void testWeaponManager();
	void testHoming();
private:
	void update(float dt);
private:
	class C_2DScrollView*		m_pScrollView;
	class C_ProgressBar*		m_pProgress;
	class C_PlayerState*		m_pPlayerState;
	class C_PlayerController*	m_pPlayerController;
	class C_PlayerUI*			m_pUI;
	class C_KeyEvent_Manager*	m_pKeyManager;
	class C_WeaponLauncher*		m_pWLauncher;
	class C_PlayScene*			m_pPlayScene;
	class C_WeaponManager*		m_pWeaponManager;
private:
	Sprite* m_pTarget;
	Sprite* m_pCharacter;
	Sprite* m_pWeapon;
private:
	float m_fPositionX;
	float m_fPositionY;
private:
	static C_TestScene* m_pInstance;
};
