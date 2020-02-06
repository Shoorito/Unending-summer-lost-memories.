#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class C_BonusNode : public Node
{
public:
	// INFO : "BonusNode" 생성구문.
	// @return = m_pInstance(singleton Type)
	static C_BonusNode* create();

	// INFO : "BonusNode" 참조구문.
	// @return = m_pInstance(singleton Type)
	inline static C_BonusNode* getInstance() { return m_pInstance; }
public:
	// INFO : "BonusNode"의 "TitleImg"를 반환합니다.
	// @return = m_pTitle(Sprite)
	inline Sprite* getTitle()	  { return m_pTitle; }

	// INFO : "BonusNode"의 "ScoreLabel"을 반환합니다.
	// @return = m_pScore(Label)
	inline Label* getScoreLabel() { return m_pScore; }
public:
	// INFO : 게임화면에 "BonusScore"를 표시합니다.
	// @param isBonus = Whether Bonus
	// @param nScore  = Gain Score
	void showScore(const bool& isBonus, const int& nScore);

	// INFO : 화면에 표시 된 "BonusScore"를 비활성화 시킵니다.
	void hideScore();
public:
	// INFO : "BonusScore"에 사용 될 글씨체를 설정합니다.
	// @param strFont = The type to be used.
	// @return = Whether Success
	const bool setFontFile(const std::string& strFont);
private:
	// INFO : "cocos2d-x, Node"의 "init" Override 함수.
	// @return = Whether Initialize Success.
	bool init() override;

	// INFO : 모든 "preset"구문의 모음함수.
	void preset();

	// INFO : 해당 클래스에서 사용 될 액션들에 대한 "preset"구문.
	// 해당 함수에서 만들어진 액션을 "Action->clone()"으로 사용합니다.
	void presetAct();
private:
	Sprite* m_pTitle;
	Label* m_pScore;
	int m_nDefaultFontSize;
private:
	Sequence* m_pShowAct;
private:
	static C_BonusNode* m_pInstance;
private:
	C_BonusNode() {}
	virtual ~C_BonusNode() {}
	C_BonusNode(C_BonusNode&) = delete;
	C_BonusNode operator=(C_BonusNode&) = delete;
};