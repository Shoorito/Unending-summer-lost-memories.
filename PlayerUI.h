#pragma once
#include "cocos2d.h"

using namespace cocos2d;

enum class E_UI_IMG
{
	E_BG,
	E_LOGO,
	E_MAX
};

enum class E_UI_GAUGE
{
	E_HP,
	E_MP,
	E_EXP,
	E_MAX
};

enum class E_UI_TITLE
{
	E_HIGHSCORE,
	E_SCORE,
	E_DIFFICULTY,
	E_HP,
	E_MP,
	E_EXP,
	E_MAX
};

enum class E_UI_SCORE
{
	E_SCORE,
	E_HIGHSCORE,
	E_MAX
};

class C_ProgressBar;

// INFO! 해당 클래스는 "PlayerUI"의 전반을 관리합니다. 단, HP, MP등 직접적인 값의 관리가 아닌 "UI"적인 부분만 관여합니다.
// WARNING! 해당 클래스는 "PlayerState" 클래스의 정보를 바탕으로 구성됩니다.
// 따라서 "PlayerState"가 생성되지 않은 상태에서 사용하게 될 경우 정상적으로 작동하지 않습니다.
// @since 2019-12-22日

class C_PlayerUI : public Node
{
public:
	static C_PlayerUI* create();
	static inline C_PlayerUI* getInstance() { return m_pInstance; }

public:
	// INFO! 해당 함수는 지정한 타입에 맞는 "UI_ITEM"을 반환합니다.
	// @param "eType" = "고정형_UI_TYPE"
	// @return "m_arItem[TYPE]"
	inline Sprite* getItem(const E_UI_IMG& eType) const
	{ 
		return m_arUIItem[static_cast<int>(eType)]; 
	}

	inline C_ProgressBar* getGauge(const E_UI_GAUGE& eType) const
	{ 
		return m_arUIGauge[static_cast<int>(eType)];
	}

	inline Label* getScoreLabel(const E_UI_TITLE& eType) const
	{
		return m_arUITitle[static_cast<int>(eType)];
	}

public:
	void setItem(const std::string& strItem, const E_UI_IMG& eType);
	void setItemByRect(const std::string& strItem, const Rect& recSize, const E_UI_IMG& eType);
public:
	void setGaugeConfig(const Color3B& c3bColor, const E_UI_GAUGE& eType);
	void setGaugeConfig(const std::string& strFile, const E_UI_GAUGE& eType);
public:
	void setScoreFontFile(const std::string& strFontFile, const E_UI_TITLE& eType);
public:
	void setEnabled(const bool isEnabled);
private:
	bool init() override;
private:
	void preset();
	void presetByGauge();
	void presetByItems();
	void presetByLabel();
	void createItems();
	void createGauges();
	void createLabel();
private:
	void update(float fDelay) override;
	void updateScore();
	void updatePlayerStatus();
private:
	Sprite*			m_arUIItem[static_cast<int>(E_UI_IMG::E_MAX)]{};
	C_ProgressBar*	m_arUIGauge[static_cast<int>(E_UI_GAUGE::E_MAX)]{};
	Label*			m_arUITitle[static_cast<int>(E_UI_TITLE::E_MAX)]{};
	Label*			m_arUIScore[static_cast<int>(E_UI_SCORE::E_MAX)]{};
private:
	int m_nUIScore;
	int m_nUIDifficulty;
	int m_nNowUsedComma;
	int m_nDefaultFontSize;
private:
	std::string m_strUIScore;
private:
	bool m_isEnabled;
private:
	static C_PlayerUI* m_pInstance;
private:
	C_PlayerUI() {}
	virtual ~C_PlayerUI() {}
	C_PlayerUI(C_PlayerUI&) = delete;
	C_PlayerUI operator=(C_PlayerUI&) = delete;
};