#pragma once
#include "cocos2d.h"

using namespace cocos2d;

enum class E_MENU
{
	E_RETURN_GAME,
	E_RETURN_MENU,
	E_SAVE_REPLAY,
	E_MENUAL,
	E_STAGE_RESTART,
	E_MAX
};

enum class E_KEY
{
	E_UP,
	E_DOWN,
	E_MAX
};

class C_PausePopup : public Sprite
{
public:
	static C_PausePopup* create();
	static C_PausePopup* getInstance() { return m_pInstance; }
public:
	void ready();
public:
	inline Sprite* getTitle() { return m_pTitle; }
public:
	Sprite* getMenuItem(const int nArrayNum);
public:
	void setGameEnd(const bool isEnd);
	void setEnabled(const bool isEnabled);
	void setMenuHeight(const float fHeight);
public:
	void setTitle(const std::string& strFile);
	void addMenuItem(const std::string& strFile);
public:
	void setMenuItem(const std::string& strFile, const int nArrayNum);
private:
	bool init() override;
	void preset();
	void presetMenu();
	void presetGameOverMenu();
	void presetAction();
	void presetCooltimeAct();
private:
	void update(float fDelay) override;
private:
	void updateMenuPositions();
	void updateMenuList(const bool isGameEnd);
	void updateMenu(const int nArrayNum);
private:
	void menuReturnToGame();
	void menuReturnToMenu();
	void menuSaveReplay();
	void menuViewManual();
	void menuStageRestart();
	void menuGameRestart();
private:
	void unDelay();
	void unlock();
	void unlockFieldManager();
private:
	Sprite* m_pTitle;
private:
	std::vector<Sprite*> m_vecMenuItems;
	std::vector<Sprite*> m_vecMenu;
private:
	Sequence* m_pCooltimeAct;
	Sequence* m_pSelectAct;
private:
	int m_nNowCursor;
private:
	float m_fMenuHeight;
private:
	bool m_isEnabled;
	bool m_isGameEnd;
	bool m_isNowUpdate;
private:
	void(C_PausePopup::*m_arEvent[static_cast<int>(E_MENU::E_MAX)])();
private:
	static C_PausePopup* m_pInstance;
private:
	C_PausePopup() {}
	virtual ~C_PausePopup() {}
	C_PausePopup(C_PausePopup&) = delete;
	C_PausePopup operator=(C_PausePopup&) = delete;
};
