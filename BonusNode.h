#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class C_BonusNode : public Node
{
public:
	// INFO : "BonusNode" ��������.
	// @return = m_pInstance(singleton Type)
	static C_BonusNode* create();

	// INFO : "BonusNode" ��������.
	// @return = m_pInstance(singleton Type)
	inline static C_BonusNode* getInstance() { return m_pInstance; }
public:
	// INFO : "BonusNode"�� "TitleImg"�� ��ȯ�մϴ�.
	// @return = m_pTitle(Sprite)
	inline Sprite* getTitle()	  { return m_pTitle; }

	// INFO : "BonusNode"�� "ScoreLabel"�� ��ȯ�մϴ�.
	// @return = m_pScore(Label)
	inline Label* getScoreLabel() { return m_pScore; }
public:
	// INFO : ����ȭ�鿡 "BonusScore"�� ǥ���մϴ�.
	// @param isBonus = Whether Bonus
	// @param nScore  = Gain Score
	void showScore(const bool& isBonus, const int& nScore);

	// INFO : ȭ�鿡 ǥ�� �� "BonusScore"�� ��Ȱ��ȭ ��ŵ�ϴ�.
	void hideScore();
public:
	// INFO : "BonusScore"�� ��� �� �۾�ü�� �����մϴ�.
	// @param strFont = The type to be used.
	// @return = Whether Success
	const bool setFontFile(const std::string& strFont);
private:
	// INFO : "cocos2d-x, Node"�� "init" Override �Լ�.
	// @return = Whether Initialize Success.
	bool init() override;

	// INFO : ��� "preset"������ �����Լ�.
	void preset();

	// INFO : �ش� Ŭ�������� ��� �� �׼ǵ鿡 ���� "preset"����.
	// �ش� �Լ����� ������� �׼��� "Action->clone()"���� ����մϴ�.
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