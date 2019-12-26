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

enum class E_GAUGE
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
	inline Sprite* getItem(const E_UI& eType) const
	{ 
		return m_arItem[static_cast<int>(eType)]; 
	}

	inline C_ProgressBar* getGauge(const E_GAUGE& eType) const
	{ 
		return m_arGauge[static_cast<int>(eType)];
	}

	inline Label* getScoreLabel(const E_SCORE& eType) const
	{
		return m_arScore[static_cast<int>(eType)];
	}

public:
	void setItem(const std::string& strItem, const E_UI& eType);
	void setItemByRect(const std::string& strItem, const Rect& recSize, const E_UI& eType);
	void setGaugeConfig(const Color3B& c3bColor, const E_GAUGE& eType);
	void setGaugeConfig(Sprite* pTexture, const E_GAUGE& eType);
	void setScoreFont(const std::string& strFontFile, const E_SCORE& eType);
	void sortItems(const int nStart, const int nEnd, const float fPadding);
private:
	bool init() override;
private:
	void preset();
	void presetByGauge();
	void createItems();
	void createGauges();
	void createScore();
	void loadScore();
	void loadByFirst();
private:
	void upperValue();
private:
	Sprite* m_arItem[static_cast<int>(E_UI::E_MAX)]{};
	C_ProgressBar* m_arGauge[static_cast<int>(E_GAUGE::E_MAX)]{};
private:
	Label* m_arScore[static_cast<int>(E_SCORE::E_MAX)]{};
private:
	int m_nScore;
	int m_nHighScore;
	int m_nDefaultFontSize;
private:
	static C_PlayerUI* m_pInstance;
private:
	C_PlayerUI() {}
	virtual ~C_PlayerUI() {}
	C_PlayerUI(C_PlayerUI&) = delete;
	C_PlayerUI operator=(C_PlayerUI&) = delete;
};