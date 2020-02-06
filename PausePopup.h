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
	// INFO : "PausePopup" 생성구문.
	// @return = m_pInstance(singleton Type)
	static C_PausePopup* create();

	// INFO : "PausePopup" 참조구문.
	// @return = m_pInstance(singleton Type)
	static C_PausePopup* getInstance() { return m_pInstance; }
public:
	// INFO : 클래스 팝업을 사용하기 위한 준비 함수입니다.
	// 주로 사용 전 호출하며, 호출하지 않으면 사용 전 적용 한 사항들이 적용되지 않습니다.
	void ready();
public:
	// INFO : 팝업에서 사용하는 타이틀 이미지(Sprite)를 반환합니다.
	// @return = m_pTitle >> TITLE_SPRITE
	inline Sprite* getTitle() { return m_pTitle; }
public:
	// INFO : 입력한 위치에 있는 "메뉴 아이템(Sprite)"를 반환합니다.
	// 실제 메뉴 아이템이 아닌 메뉴 아이템으로 사용되는 Sprite 개체입니다.
	// @param  = nArrayNum >> ARRAY_NUMBER
	// @return = m_vecMenuItems[nArrayNum] >> ARRAY_MENU_ITEM
	Sprite* getMenuItem(const int nArrayNum);
public:
	// INFO : 게임이 종료 된 상태에서 사용되는지에 대해 설정합니다.
	// 게임 종료시 표기되는 메뉴의 종류가 다르기에 게임 종료시에는 반드시 사용해야 합니다.
	// 해당 함수로 지정한 사항은 위에 개재된 "ready"함수를 통해 갱신을 해주어야 합니다.
	// @param = isEnd >> NOW_GAME_END?
	void setGameEnd(const bool isEnd);

	// INFO : 팝업 관리 개체를 활성화/비활성화 시킵니다.
	// @param = isEnabled >> POPUP_IS_ENABLED
	void setEnabled(const bool isEnabled);

	// INFO : 메뉴 간 세로축 간격을 지정합니다.
	// 해당 함수로 지정한 사항은 위에 개재된 "ready"함수를 통해 갱신을 해주어야 합니다.
	// @param = fHeight >> MENU_HEIGHT
	void setMenuHeight(const float fHeight);
public:
	// INFO : 메뉴의 타이틀로 사용되는 이미지(Sprite)를 지정합니다.
	// @param = strFile >> TEXTURE_ROUTE + TEXTURE_NAME
	void setTitle(const std::string& strFile);

	// INFO : 메뉴에 사용 될 메뉴 아이템(MenuItem)을 추가합니다.
	// 해당 함수로는 이미지만 생성되는 것이 아닌 메뉴 아이템으로서 리스트에 추가됩니다.
	// 추가 사항을 적용하기 위해선 "ready"함수를 사용해야 합니다.
	// @param = strFile >> TEXTURE_ROUTE + TEXTURE_NAME
	void addMenuItem(const std::string& strFile);
public:
	// INFO : 기존에 사용하던 메뉴 아이템(MenuItem)의 이미지(Sprite)를 변경합니다.
	// @param = strFile   >> TEXTURE_ROUTE + TEXTURE_NAME
	// @param = nArrayNum >> MENUITEM_ARRAY_NUMBER
	void setMenuItem(const std::string& strFile, const int nArrayNum);
private:
	// INFO : Sprite 유형의 "init" 오버라이드 함수입니다.
	// 맴버변수들의 초기화를 맡고 있습니다.
	// @return = is_initialize = IS_INITIALIZE?
	bool init() override;

	// INFO : "preset~"함수들을 모아놓은 편의함수입니다.
	void preset();

	// INFO : 일반적인 메뉴상태의 함수 포인터 개체들을 설정해주는 함수입니다.
	// 기존의 "preset"함수들과 다르게 게임 실행 중에도 사용됩니다.
	void presetMenu();

	// INFO : 모종의 이유로 게임이 종료 됐을 때 함수 포인터 개체들을 설정하는 함수입니다.
	// 기존의 "preset"함수들과 다르게 게임 실행 중에도 사용됩니다.
	void presetGameOverMenu();

	// INFO : 플레이어가 선택한 메뉴에 적용되는 액션의 "preset"함수입니다.
	void presetAction();

	// INFO : 메뉴 커서 이동 또는 메뉴 비활성화시 "동시성 문제"를 해결하기 위해 사용하는 함수입니다.
	// 주로 "CallFunc"액션으로 호출됩니다.
	void presetCooltimeAct();
private:
	// INFO : 키입력, 메뉴의 이동등을 관리하는 업데이트 함수입니다.
	// @param = fDelay >> CALL_DELAY
	void update(float fDelay) override;
private:
	// INFO : 메뉴의 위치들을 갱신합니다.
	// 주로 메뉴의 개수나 여럿 변경 사항이 적용 될 때 사용됩니다.
	void updateMenuPositions();

	// INFO : 메뉴의 유형(게임 종료 시 메뉴인가 아닌가에 대해)에 따라 메뉴를 총괄 변경해주는 함수입니다.
	// @param = isGameEnd >> IS_GAME_END_MENU?
	void updateMenuList(const bool isGameEnd);

	// INFO : 메뉴 커서가 이동 했을 경우 이동한 메뉴와 이전에 위치했던 메뉴에 대해 변화를 주는 용도의 함수입니다.
	// @param = nArrayNum >> MENU_TYPE
	void updateMenu(const int nArrayNum);
private:
	// INFO : "게임으로 되돌아가기"용 메뉴 구문입니다.
	// 해당 함수 포인터가 지정된 메뉴를 선택한 상태에서 "Z"키를 누르면 실행됩니다.
	void menuReturnToGame();

	// INFO : "메인 메뉴로 되돌아가기"용 메뉴 구문입니다.
	// 해당 함수 포인터가 지정된 메뉴를 선택한 상태에서 "Z"키를 누르면 실행됩니다.
	void menuReturnToMenu();

	// INFO : "리플레이 데이터 저장"용 메뉴 구문입니다.
	// 해당 함수 포인터가 지정된 메뉴를 선택한 상태에서 "Z"키를 누르면 실행됩니다.
	void menuSaveReplay();

	// INFO : "메뉴얼 보기"용 메뉴 구문입니다.
	// 해당 함수 포인터가 지정된 메뉴를 선택한 상태에서 "Z"키를 누르면 실행됩니다.
	void menuViewManual();

	// INFO : "해당 스테이지부터 재시작"용 메뉴 구문입니다.
	// 해당 함수 포인터가 지정된 메뉴를 선택한 상태에서 "Z"키를 누르면 실행됩니다.
	void menuStageRestart();

	// INFO : "처음 스테이지부터 재시작"용 메뉴 구문입니다.
	// 해당 함수 포인터가 지정된 메뉴를 선택한 상태에서 "Z"키를 누르면 실행됩니다.
	void menuGameRestart();
private:
	// INFO : "update"함수를 "m_isUpdate"를 통해 멈춰있게 했을 경우 해당 값을 "false"로 되돌립니다.
	// "pause"와 같은 기능으로 "update"함수를 멈춰있게 한 경우에는 통하지 않습니다.
	void unDelay();
	
	// INFO : "FieldManager"에서 일시 정지시킨 기능들을 다시 재개시킵니다.
	void unlock();
	
	// INFO : "unlock"구문 실행 시 "FieldManager"와의 "동시성 문제"를 방지하기 위해 만든 호출용 함수입니다.
	// "Cooltime"액션에서 호출됩니다.
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
