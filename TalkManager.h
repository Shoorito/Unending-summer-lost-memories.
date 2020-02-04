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
	static C_TalkManager* create();
	inline static C_TalkManager* getInstance() { return m_pInstance; }
public:
	void removeRetainMember();
	void startTalkEvent();
	void endTalkEvent();
public:
	void setPageNumber(const int nNumber);
	void addEventCount(const int nCount);
	void setEventCount(const int nCount, const int nArrayNum);
public:
	void setEnabled(const bool isEnabled);
public:
	void setTalkOutline(const Color4B& colorOutline, const int nArrayNum);
public:
	void setDialogueAct(const float fDelay);
	void setSCGMoveAct(const Vec2& vecMovement, const int nArrayNum);
public:
	void setTextBox(const std::string& strFile);
	void setSCGAtlas(const std::string& strFile, const Size& recSize, const int nType);
	void setDialogueFont(const std::string& strFonts);
	void presetDialouge(const std::string& strFileData);
public:
	inline const int& getNowReadPage()	{ return m_nPageNumber; }
public:
	inline const bool& isReading()		{ return m_isNowReading; }
	inline const bool& isEnabled()		{ return m_isEnabled; }
private:
	bool init() override;
	void preset();
private:
	void presetFuncs();
	void presetItems();
	void presetActions();
	void presetStartActions();
private:
	void update(float fDelay) override;
private:
	void unDelay();
	void formChange();
	void enableEvent();
	void writeDialouge();
private:
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