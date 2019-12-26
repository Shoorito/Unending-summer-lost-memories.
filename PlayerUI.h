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

// INFO! �ش� Ŭ������ "PlayerUI"�� ������ �����մϴ�. ��, HP, MP�� �������� ���� ������ �ƴ� "UI"���� �κи� �����մϴ�.
// WARNING! �ش� Ŭ������ "PlayerState" Ŭ������ ������ �������� �����˴ϴ�.
// ���� "PlayerState"�� �������� ���� ���¿��� ����ϰ� �� ��� ���������� �۵����� �ʽ��ϴ�.
// @since 2019-12-22��

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