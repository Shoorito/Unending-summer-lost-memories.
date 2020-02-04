#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class C_PlayScene : public Scene
{
public:
	static C_PlayScene* create();
	static inline C_PlayScene* getInstance() { return m_pInstance; }
private:
    bool init() override;
	void preset();
private:
	void testFieldManager();
private:
	void createItem();
	void createPopup();
	void createEnemy();
	void createScroll();
	void createDanmaku();
	void createController();
	void createTalkManager();
	void createWeaponManager();
	void createWeaponLauncher();
private:
	void callEvent();
private:
	class C_TalkManager*		m_pTalkManager;
	class C_KeyEvent_Manager*	m_pKeyManager;
	class C_EnemyManager*		m_pEnemyManager;
	class C_BossManager*		m_pBossManager;
	class C_WeaponManager*		m_pWeaponManager;
	class C_DanmakuManager*		m_pDanmakuManager;
	class C_Enemy_Mover_Lib*	m_pEnemyMovePattern;
private:
	class C_PlayerUI*			m_pUI;
	class C_2DScrollView*		m_pScrollView;
	class C_PlayerState*		m_pPlayerState;
	class C_PlayerController*	m_pPlayerController;
	class C_WeaponLauncher*		m_pWLauncher;
	class C_ItemManager*		m_pItemManager;
private:
	class C_PausePopup*			m_pPopup;
	class C_FieldManager*		m_pFieldManager;
private:
	static C_PlayScene* m_pInstance;
};
