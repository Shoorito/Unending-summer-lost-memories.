#pragma once
#include "cocos2d.h"

USING_NS_CC;

enum class E_KEY_STATE
{
	E_NONE,
	E_DOWN,
	E_PUSH,
	E_UP
};

class C_KeyEvent_Manager : public Node
{
public:
	// INFO : "KeyEvent_Manager" 생성구문.
	// @return = m_pInstance(singleton Type)
	static C_KeyEvent_Manager* create();

	// INFO : "KeyEvent_Manager" 참조구문.
	// @return = m_pInstance(singleton Type)
	static C_KeyEvent_Manager* getInstance() { return m_pInstance; }
public:
	// INFO : 인수로 입력한 키의 현재 상태를 반환합니다.
	// 키의 상태는 해당 매니저에서 정한 "DOWN", "PUSH", "UP"으로 구분됩니다.
	// @param  = nKey >> KEY_TYPE(원래 타입은 EventKeyboard::KeyCode)
	// @return = m_arKeyState[nKey] >> KEY_ARRAY[KEY_TYPE]
	const E_KEY_STATE& getPushedType(const int nKey) { return m_arKeyState[nKey]; }
public:
	// INFO : 현재 클래스의 활성화/비활성화를 정할 수 있습니다.
	// @param = isEnabled >> IS_KEYEVENT_ENABLED
	void setEnabled(const bool isEnabled);
private:
	// INFO : "Node"의 "init"을 오버라이드 한 함수입니다.
	// 클래스에서 관리하는 맴버 변수들의 초기화를 맡고 있습니다.
	bool init() override;
	void preset();

	// INFO : 해당 클래스에서 사용 할 키 입력 감지 이벤트를 생성합니다.
	void createKeyEvent();

	// INFO : "Node" 클래스에서 오버라이드한 "update"함수입니다.
	// 클래스가 관리하는 모든 키 값을 정해진 시간 간격마다 업데이트합니다.
	// @param = fDelay >> UPDATE_DELAY
	void update(float fDelay) override;
private:
	// 키입력 감지 이벤트 리스너에 대한 콜백 함수입니다.
	// 키입력 이벤트를 이 함수에서 처리합니다.
	// @param = eKey	 >> 이벤트 리스너에서 입력받은 키코드입니다.
	// @param = pNotUsed >> 현재 사용되지 않는 인수입니다.(cocos2d-x에 강제로 사용하게끔 설계 되어 있습니다.)
	void onKeyPressed(const EventKeyboard::KeyCode eKey, Event* pNotUsed);

	// 비입력 감지 이벤트 리스너에 대한 콜백 함수입니다.
	// 비입력 이벤트를 이 함수에서 처리합니다.
	// 키에서 손을 땠을 경우 불립니다.
	// @param = eKey	 >> 이벤트 리스너에서 입력받은 키코드입니다.
	// @param = pNotUsed >> 현재 사용되지 않는 인수입니다.(cocos2d-x에 강제로 사용하게끔 설계 되어 있습니다.)
	void onKeyReleased(const EventKeyboard::KeyCode eKey, Event* pNotUsed);
private:
	bool m_arKeyPast[166]{};
	bool m_arKeyNow[166]{};
private:
	E_KEY_STATE m_arKeyState[166]{};
	E_KEY_STATE m_arKeyTypes[2][2]{};
private:
	bool m_isEnabled;
private:
	EventListenerKeyboard* m_pKeyListener;
private:
	static C_KeyEvent_Manager* m_pInstance;
private:
	C_KeyEvent_Manager() {}
	virtual ~C_KeyEvent_Manager() {}
	C_KeyEvent_Manager(C_KeyEvent_Manager&) = delete;
	C_KeyEvent_Manager operator=(C_KeyEvent_Manager&) = delete;
};