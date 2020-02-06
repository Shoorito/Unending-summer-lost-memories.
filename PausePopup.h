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
	// INFO : "PausePopup" ��������.
	// @return = m_pInstance(singleton Type)
	static C_PausePopup* create();

	// INFO : "PausePopup" ��������.
	// @return = m_pInstance(singleton Type)
	static C_PausePopup* getInstance() { return m_pInstance; }
public:
	// INFO : Ŭ���� �˾��� ����ϱ� ���� �غ� �Լ��Դϴ�.
	// �ַ� ��� �� ȣ���ϸ�, ȣ������ ������ ��� �� ���� �� ���׵��� ������� �ʽ��ϴ�.
	void ready();
public:
	// INFO : �˾����� ����ϴ� Ÿ��Ʋ �̹���(Sprite)�� ��ȯ�մϴ�.
	// @return = m_pTitle >> TITLE_SPRITE
	inline Sprite* getTitle() { return m_pTitle; }
public:
	// INFO : �Է��� ��ġ�� �ִ� "�޴� ������(Sprite)"�� ��ȯ�մϴ�.
	// ���� �޴� �������� �ƴ� �޴� ���������� ���Ǵ� Sprite ��ü�Դϴ�.
	// @param  = nArrayNum >> ARRAY_NUMBER
	// @return = m_vecMenuItems[nArrayNum] >> ARRAY_MENU_ITEM
	Sprite* getMenuItem(const int nArrayNum);
public:
	// INFO : ������ ���� �� ���¿��� ���Ǵ����� ���� �����մϴ�.
	// ���� ����� ǥ��Ǵ� �޴��� ������ �ٸ��⿡ ���� ����ÿ��� �ݵ�� ����ؾ� �մϴ�.
	// �ش� �Լ��� ������ ������ ���� ����� "ready"�Լ��� ���� ������ ���־�� �մϴ�.
	// @param = isEnd >> NOW_GAME_END?
	void setGameEnd(const bool isEnd);

	// INFO : �˾� ���� ��ü�� Ȱ��ȭ/��Ȱ��ȭ ��ŵ�ϴ�.
	// @param = isEnabled >> POPUP_IS_ENABLED
	void setEnabled(const bool isEnabled);

	// INFO : �޴� �� ������ ������ �����մϴ�.
	// �ش� �Լ��� ������ ������ ���� ����� "ready"�Լ��� ���� ������ ���־�� �մϴ�.
	// @param = fHeight >> MENU_HEIGHT
	void setMenuHeight(const float fHeight);
public:
	// INFO : �޴��� Ÿ��Ʋ�� ���Ǵ� �̹���(Sprite)�� �����մϴ�.
	// @param = strFile >> TEXTURE_ROUTE + TEXTURE_NAME
	void setTitle(const std::string& strFile);

	// INFO : �޴��� ��� �� �޴� ������(MenuItem)�� �߰��մϴ�.
	// �ش� �Լ��δ� �̹����� �����Ǵ� ���� �ƴ� �޴� ���������μ� ����Ʈ�� �߰��˴ϴ�.
	// �߰� ������ �����ϱ� ���ؼ� "ready"�Լ��� ����ؾ� �մϴ�.
	// @param = strFile >> TEXTURE_ROUTE + TEXTURE_NAME
	void addMenuItem(const std::string& strFile);
public:
	// INFO : ������ ����ϴ� �޴� ������(MenuItem)�� �̹���(Sprite)�� �����մϴ�.
	// @param = strFile   >> TEXTURE_ROUTE + TEXTURE_NAME
	// @param = nArrayNum >> MENUITEM_ARRAY_NUMBER
	void setMenuItem(const std::string& strFile, const int nArrayNum);
private:
	// INFO : Sprite ������ "init" �������̵� �Լ��Դϴ�.
	// �ɹ��������� �ʱ�ȭ�� �ð� �ֽ��ϴ�.
	// @return = is_initialize = IS_INITIALIZE?
	bool init() override;

	// INFO : "preset~"�Լ����� ��Ƴ��� �����Լ��Դϴ�.
	void preset();

	// INFO : �Ϲ����� �޴������� �Լ� ������ ��ü���� �������ִ� �Լ��Դϴ�.
	// ������ "preset"�Լ���� �ٸ��� ���� ���� �߿��� ���˴ϴ�.
	void presetMenu();

	// INFO : ������ ������ ������ ���� ���� �� �Լ� ������ ��ü���� �����ϴ� �Լ��Դϴ�.
	// ������ "preset"�Լ���� �ٸ��� ���� ���� �߿��� ���˴ϴ�.
	void presetGameOverMenu();

	// INFO : �÷��̾ ������ �޴��� ����Ǵ� �׼��� "preset"�Լ��Դϴ�.
	void presetAction();

	// INFO : �޴� Ŀ�� �̵� �Ǵ� �޴� ��Ȱ��ȭ�� "���ü� ����"�� �ذ��ϱ� ���� ����ϴ� �Լ��Դϴ�.
	// �ַ� "CallFunc"�׼����� ȣ��˴ϴ�.
	void presetCooltimeAct();
private:
	// INFO : Ű�Է�, �޴��� �̵����� �����ϴ� ������Ʈ �Լ��Դϴ�.
	// @param = fDelay >> CALL_DELAY
	void update(float fDelay) override;
private:
	// INFO : �޴��� ��ġ���� �����մϴ�.
	// �ַ� �޴��� ������ ���� ���� ������ ���� �� �� ���˴ϴ�.
	void updateMenuPositions();

	// INFO : �޴��� ����(���� ���� �� �޴��ΰ� �ƴѰ��� ����)�� ���� �޴��� �Ѱ� �������ִ� �Լ��Դϴ�.
	// @param = isGameEnd >> IS_GAME_END_MENU?
	void updateMenuList(const bool isGameEnd);

	// INFO : �޴� Ŀ���� �̵� ���� ��� �̵��� �޴��� ������ ��ġ�ߴ� �޴��� ���� ��ȭ�� �ִ� �뵵�� �Լ��Դϴ�.
	// @param = nArrayNum >> MENU_TYPE
	void updateMenu(const int nArrayNum);
private:
	// INFO : "�������� �ǵ��ư���"�� �޴� �����Դϴ�.
	// �ش� �Լ� �����Ͱ� ������ �޴��� ������ ���¿��� "Z"Ű�� ������ ����˴ϴ�.
	void menuReturnToGame();

	// INFO : "���� �޴��� �ǵ��ư���"�� �޴� �����Դϴ�.
	// �ش� �Լ� �����Ͱ� ������ �޴��� ������ ���¿��� "Z"Ű�� ������ ����˴ϴ�.
	void menuReturnToMenu();

	// INFO : "���÷��� ������ ����"�� �޴� �����Դϴ�.
	// �ش� �Լ� �����Ͱ� ������ �޴��� ������ ���¿��� "Z"Ű�� ������ ����˴ϴ�.
	void menuSaveReplay();

	// INFO : "�޴��� ����"�� �޴� �����Դϴ�.
	// �ش� �Լ� �����Ͱ� ������ �޴��� ������ ���¿��� "Z"Ű�� ������ ����˴ϴ�.
	void menuViewManual();

	// INFO : "�ش� ������������ �����"�� �޴� �����Դϴ�.
	// �ش� �Լ� �����Ͱ� ������ �޴��� ������ ���¿��� "Z"Ű�� ������ ����˴ϴ�.
	void menuStageRestart();

	// INFO : "ó�� ������������ �����"�� �޴� �����Դϴ�.
	// �ش� �Լ� �����Ͱ� ������ �޴��� ������ ���¿��� "Z"Ű�� ������ ����˴ϴ�.
	void menuGameRestart();
private:
	// INFO : "update"�Լ��� "m_isUpdate"�� ���� �����ְ� ���� ��� �ش� ���� "false"�� �ǵ����ϴ�.
	// "pause"�� ���� ������� "update"�Լ��� �����ְ� �� ��쿡�� ������ �ʽ��ϴ�.
	void unDelay();
	
	// INFO : "FieldManager"���� �Ͻ� ������Ų ��ɵ��� �ٽ� �簳��ŵ�ϴ�.
	void unlock();
	
	// INFO : "unlock"���� ���� �� "FieldManager"���� "���ü� ����"�� �����ϱ� ���� ���� ȣ��� �Լ��Դϴ�.
	// "Cooltime"�׼ǿ��� ȣ��˴ϴ�.
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
