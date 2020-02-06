#pragma once
#include "cocos2d.h"

USING_NS_CC;

enum class E_CHARACTER
{
	E_PLAYER = 1,
	E_BOSS	 = 2,
	E_MAX	 = 3
};

class C_TalkManager : public Node
{
public:
	// INFO : "TalkManager" 생성구문.
	// @return = m_pInstance(singleton Type)
	static C_TalkManager* create();

	// INFO : "TalkManager" 참조구문.
	// @return = m_pInstance(singleton Type)
	inline static C_TalkManager* getInstance() { return m_pInstance; }
public:
	// INFO : retain함수로 묶인 액션 노드 개체를 모두 release시킵니다.
	// "PlayScene"이 종료 될 때 사용합니다.
	void removeRetainMember();

	// INFO : 스테이지의 대화이벤트가 처음으로 시작 될 때 사용하는 구문입니다.
	// 이벤트에 필요한 여러 값을 미리 정의합니다.
	void startTalkEvent();

	// INFO : 스테이지의 대화이벤트가 끝나기 전 사용하는 구문입니다.
	// 주로 보스전 이후 회화에서 사용합니다.
	void endTalkEvent();
public:
	// INFO : 대화이벤트의 대화지점(책으로 치면 페이지)을 지정합니다.
	// 지정한 지점의 적용은 "키 입력(Z키)" 후 알 수 있습니다.
	// @param = nNumber >> PAGE_NUMBER
	void setPageNumber(const int nNumber);

	// INFO : 실시간 갱신 값을 입력한 값 만큼 더하거나 뺍니다.
	// @param : nCount >> PREV_UPDATE_COUNT + ADD_COUNT
	void addEventCount(const int nCount);

	// INFO : 실시간 갱신 값을 임의로 지정합니다.
	// @param : nCount >> UPDATE_COUNT
	void setEventCount(const int nCount, const int nArrayNum);
public:
	// INFO : 대화 이벤트 관리 개체를 활성화/비활성화 시킵니다.
	// @param = isEnabled >> POPUP_IS_ENABLED
	void setEnabled(const bool isEnabled);
public:
	// INFO : 대화에 사용되는 다이얼로그의 외곽선을 지정합니다.
	// 2번째 인수에 해당하는 대상의 다이얼로그의 외곽선으로 지정됩니다.
	// @param = colorOutline >> OUTLINE_COLOR
	// @param = nArrayNum	 >> USE_ARRAY_NUMBER
	void setTalkOutline(const Color4B& colorOutline, const int nArrayNum);
public:
	// INFO : 대화를 표시하는 다이얼로그의 액션의 시간을 지정합니다.
	// @param = fDelay >> DIALOGUE_ACTION_TIME
	void setDialogueAct(const float fDelay);

	// INFO : 대화 시 움직이는 SCG의 "Move"액션의 이동 위치를 지정합니다.
	// 2번째 인수에 해당하는 대상의 이동 위치를 지정합니다.
	// @param = vecMovement >> ACTION_MOVEMENT
	// @param = nArrayNum	>> USE_ARRAY_NUMBER
	void setSCGMoveAct(const Vec2& vecMovement, const int nArrayNum);
public:
	// INFO : 대화 다이얼로그 박스의 이미지(Sprite)를 지정합니다.
	// @param = strFile >> TEXTURE_ROUTE + TEXTURE_NAME
	void setTextBox(const std::string& strFile);

	// INFO : 대화 SCG의 아틀라스(Atlas) 단위를 지정합니다.
	// @param = strFile >> TEXTURE_ROUTE + TEXTURE_NAME
	// @param = recSize >> TEXTURE_RECT_SIZE
	// @param = nType	>> USE_SCG_ARRAY_NUMBER
	void setSCGAtlas(const std::string& strFile, const Size& recSize, const int nType);

	// INFO : 대화에 사용되는 다이얼로그 폰트파일을 지정합니다.
	// @param = strFont >> FONT_FILE_ROUTE + FONT_FILE_NAME
	void setDialogueFont(const std::string& strFonts);

	// INFO : 외부의 파일로부터 대화에 사용 될 내용들을 불러옵니다.
	// 보통 스테이지 시작 시 미리 불러와 사용합니다.
	// @param = strFileData >> DIALOGUE_FILE_ROUTE + DIALOGUE_FILE_NAME
	void presetDialouge(const std::string& strFileData);
public:
	// INFO : 현재 위치한 대화 이벤트(Page)넘버를 반환합니다.
	// @return m_nPageNumber >> PAGE_NUMBER
	inline const int& getNowReadPage()	{ return m_nPageNumber; }
public:
	// INFO : 아직 대화 표기 액션을 수행 중인지에 대한 여부를 반환합니다.
	// @return m_isNowReading >> IS_NOW_READING_DIALOGUE
	inline const bool& isReading()		{ return m_isNowReading; }

	// INFO : 현재 클래스 이벤트가 활성화 되있는지 여부를 반환합니다.
	// @return m_isEnabled >> IS_EVENT_ENABLED?
	inline const bool& isEnabled()		{ return m_isEnabled; }
private:
	// INFO : "Node"구문의 "init"함수를 오버라이드 한 함수입니다.
	// 클래스 내 맴버 변수를 초기화 하는 것에 사용합니다.
	// @return is_Initialize >> IS_INITIALIZE?
	bool init() override;
	void preset();
private:
	// INFO : 이벤트 함수 포인터 배열목록을 미리 지정합니다.
	void presetFuncs();

	// INFO : 해당 기능에서 사용하는 모든 개체들을 미리 생성합니다.
	void presetItems();

	// INFO : 해당 기능에서 사용하는 액션들을 미리 생성, "retain"합니다.
	void presetActions();

	// INFO : 대화가 시작 될 때 발생하는 액션을 미리 생성, "retain"합니다.
	void presetStartActions();
private:
	// INFO : 대화 기능 내 키 입력, 실시간 처리등을 관리합니다.
	// @param = fDelay >> UPDATE_DELAY
	void update(float fDelay) override;
private:
	// INFO : "update"함수를 "m_isNowReading"를 통해 멈춰있게 했을 경우 해당 값을 "false"로 되돌립니다.
	// "pause"와 같은 기능으로 "update"함수를 멈춰있게 한 경우에는 통하지 않습니다.
	void unDelay();
	
	// INFO : 보스의 텍스쳐, 형상을 변하게 할 경우 사용하는 액션함수입니다.
	void formChange();

	// INFO : 이벤트의 값을 처음으로 되돌리고 재시작시킵니다.
	// 주로 테스트, 또는 "presetStartAction"에서 사용합니다.
	void enableEvent();

	// INFO : 현재 이벤트 값에 따른 대화 출력과 SCG간의 이동과 같은 이벤트 액션을 담당합니다.
	void writeDialouge();
private:
	// INFO : 일정 이벤트 값에서 실행되는 이벤트들의 함수입니다.
	// "FieldManager"의 "event"함수들과 비슷합니다.
	void event01();
	void event02();
	void event03();
	void event04();
	void event05();
private:
	Label* m_pDialouge;
private:
	Sprite* m_pTextbox;
private:
	Sprite* m_arSCG[2]{};
private:
	Size m_arSCGSizes[2]{};
private:
	std::vector<Color4B> m_vecOutlineColors;
private:
	std::vector<std::string> m_vecDialogueList;
	std::vector<std::string> m_vecDialogueTarget;
	std::vector<std::string> m_vecSCGNumber;
private:
	std::vector<int> m_vecEventCounter;
private:
	std::vector<std::string>* m_arTextSource[3]
	{
		&m_vecDialogueList,
		&m_vecDialogueTarget,
		&m_vecSCGNumber
	};
private:
	Sequence*	m_pDialougeAct;
	Sequence*	m_pPlayerAct;
	Sequence*	m_pTalkBoxAct;
private:
	MoveTo* m_arMoveAct[4]{};
private:
	int m_nEventCount;
	int m_nPageNumber;
	int m_nPrevSCG;
	int m_nPrevType;
	int m_nFontSize;
private:
	bool m_isEnabled;
	bool m_isNowReading;
private:
	void(C_TalkManager::*m_arEventFunc[5])();
private:
	static C_TalkManager* m_pInstance;
private:
	C_TalkManager() {}
	virtual ~C_TalkManager() {}
	C_TalkManager(C_TalkManager&) = delete;
	C_TalkManager operator=(C_TalkManager&) = delete;
};