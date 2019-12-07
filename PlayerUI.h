#pragma once
#include "cocos2d.h"

using namespace cocos2d;

enum class E_UI
{
	E_BG,
	E_LOGO,
	E_DIFFICULTY,
	E_HIGHSCORE,
	E_SCORE,
	E_HP,
	E_MP,
	E_POWER,
	E_MAX
};

enum class E_GAZE
{
	E_HP,
	E_MP,
	E_POWER,
	E_MAX
};

enum class E_SCORE
{
	E_NORMAL,
	E_HIGH,
	E_MAX
};

class C_ProgressBar;

// INFO! �ش� Ŭ������ "PlayerUI"�� ������ �����մϴ�. ��, HP, MP�� �������� ���� ������ �ƴ� "UI"���� �κи� �����մϴ�.
// @since 2019-12-07��

class C_PlayerUI : public Node
{
public:
	static C_PlayerUI* create();
	static inline C_PlayerUI* getInstance() { return m_pInstance; }

public:
	// INFO! �ش� �Լ��� ������ Ÿ�Կ� �´� "UI_ITEM"�� ��ȯ�մϴ�.
	// @param "eType" = "������_UI_TYPE"
	// @return "m_arItem[TYPE]"
	inline Sprite* getItem(const E_UI& eType) const
	{ 
		return m_arItem[static_cast<int>(eType)]; 
	}

	inline C_ProgressBar* getGaze(const E_GAZE& eType) const
	{ 
		return m_arGaze[static_cast<int>(eType)];
	}

	inline Label* getScoreLabel(const E_SCORE& eType) const
	{
		return m_arScore[static_cast<int>(eType)];
	}
public:
	void setItemByRect(const std::string& strFileName, const Rect& recSize, const E_UI& eType);
	void setGaze(C_ProgressBar* pGaze, const E_GAZE& eType);
	void setScoreLabel(const std::string& strFontFile, const E_SCORE& eType);
	void sortItems(const int nStart, const int nEnd);
private:
	bool init() override;
private:
	void preset();
	void createItems();
	void createGaze();
	void createScore();
private:
	Sprite* m_arItem[static_cast<int>(E_UI::E_MAX)]{};
	C_ProgressBar* m_arGaze[static_cast<int>(E_GAZE::E_MAX)]{};
private:
	Label* m_arScore[static_cast<int>(E_SCORE::E_MAX)]{};
private:
	static C_PlayerUI* m_pInstance;
private:
	C_PlayerUI() {}
	virtual ~C_PlayerUI() {}
	C_PlayerUI(C_PlayerUI&) = delete;
	C_PlayerUI operator=(C_PlayerUI&) = delete;
};