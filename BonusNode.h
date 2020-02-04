#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class C_BonusNode : public Node
{
public:
	static C_BonusNode* create();
	inline static C_BonusNode* getInstance() { return m_pInstance; }
public:
	inline Sprite* getTitle()	  { return m_pTitle; }
	inline Label* getScoreLabel() { return m_pScore; }
public:
	void showScore(const bool& isBonus, const int& nScore);
	void hideScore();
public:
	const bool setFontFile(const std::string& strFont);
private:
	bool init() override;
	void preset();
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