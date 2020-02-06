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

// INFO! �ش� Ŭ������ "PlayerUI"�� ������ �����մϴ�. ��, HP, MP�� �������� ���� ������ �ƴ� "UI"���� �κи� �����մϴ�.
// WARNING! �ش� Ŭ������ "PlayerState" Ŭ������ ������ �������� �����˴ϴ�.
// ���� "PlayerState"�� �������� ���� ���¿��� ����ϰ� �� ��� ���������� �۵����� �ʽ��ϴ�.
// @since 2019-12-22��

class C_PlayerUI : public Node
{
public:
	// INFO : "PlayerUI" ��������.
	// @return = m_pInstance(singleton Type)
	static C_PlayerUI* create();

	// INFO : "PlayerUI" ��������.
	// @return = m_pInstance(singleton Type)
	static inline C_PlayerUI* getInstance() { return m_pInstance; }
public:
	// INFO : �ش� �Լ��� ������ Ÿ�Կ� �´� "UI_ITEM"�� ��ȯ�մϴ�.
	// @param  = "eType" >> "������_UI_TYPE"
	// @return = "m_arItem[TYPE]"
	inline Sprite* getItem(const E_UI_IMG& eType) const
	{ 
		return m_arUIItem[static_cast<int>(eType)]; 
	}

	// INFO : �Է��� Ÿ�Կ� �´� "UI������"�� ��ȯ�մϴ�.
	// @param = "eType" >> GAUGE_TYPE
	inline C_ProgressBar* getGauge(const E_UI_GAUGE& eType) const
	{ 
		return m_arUIGauge[static_cast<int>(eType)];
	}

	// INFO : �Է��� Ÿ�Կ� �´� "Score_Title" Label�� ��ȯ�մϴ�.
	// @param = "eType" >> SCORE_TYPE
	inline Label* getScoreLabel(const E_UI_TITLE& eType) const
	{
		return m_arUITitle[static_cast<int>(eType)];
	}
public:
	// INFO : �÷��̾� ���� �̿� "UI"�� ǥ�õǴ� �̹��� �ؽ��ĸ� �����մϴ�.
	// @param = "strItem" >> TEXTURE_ROUTE + TEXTURE_NAME
	// @param = "eType"	  >> ITEM_TYPE
	void setItem(const std::string& strItem, const E_UI_IMG& eType);

	// INFO : �÷��̾� ���� �̿� "UI"�� ǥ�õǴ� �̹��� �ؽ��ĸ� ��Ʋ�� �̹��� ���·� �����մϴ�.
	// @param = "strItem" >> TEXTURE_ROUTE + TEXTURE_NAME
	// @param = "recSize" >> TEXTURE_RECT_SIZE
	// @param = "eType"	  >> ITEM_TYPE
	void setItemByRect(const std::string& strItem, const Rect& recSize, const E_UI_IMG& eType);
public:
	// INFO : �÷� Ÿ������ ������ Ÿ���� UI ������ ���¸� �����մϴ�.
	// @param = "c3bColor"	>> GAUGE_COLOR
	// @param = "eType"		>> GAUGE_TYPE
	void setGaugeConfig(const Color3B& c3bColor, const E_UI_GAUGE& eType);

	// INFO : �ؽ��ķ� ������ Ÿ���� ������ ���¸� �����մϴ�.
	// @param = "strFile"	>> TEXTURE_ROUTE + TEXTURE_NAME
	// @param = "eType"		>> GAUGE_TYPE
	void setGaugeConfig(const std::string& strFile, const E_UI_GAUGE& eType);
public:
	// INFO : "Score_Label"�� ��� �� ��Ʈ�� ��Ʈ ���Ϸ� ���մϴ�.
	// ���� �����Ǵ� ��Ʈ Ÿ���� ".TTF, .OTF"�Դϴ�.
	// @param = "strFontFile" >> FONT_ROUTE + FONT_NAME
	// @param = "eType"		  >> TITLE_TYPE
	void setScoreFontFile(const std::string& strFontFile, const E_UI_TITLE& eType);
public:
	// INFO : "PlayerUI"�� Ȱ��ȭ ���θ� �����մϴ�.
	// ��Ȱ��ȭ ��ų��� �÷��̾� ������ ������Ʈ�� �̷������ �ʽ��ϴ�.
	// @param = isEnabled >> MANAGER_IS_ENABLED
	void setEnabled(const bool isEnabled);
private:
	// INFO : "Node" Ŭ������ "init"�Լ��� �������̵� �� �Լ��Դϴ�.
	// Ŭ�������� �����ϴ� �ɹ� ������ �ʱ�ȭ�� ����մϴ�.
	// @return = IS_INITIALIZE
	bool init() override;
private:
	// INFO : "preset"�Լ����� ��Ƽ� �����ϴ� ���� �Լ��Դϴ�.
	void preset();

	// INFO : ������ Ÿ���� "UI_Item"�� ���� �ʱ�ȭ �� ������ ����մϴ�.
	void presetByGauge();

	// INFO : "PLAYER_UI"Ÿ�� �̿��� "UI_Item"�� ���� �ʱ�ȭ �� ������ ����մϴ�.
	void presetByItems();

	// INFO : "UI"�� ���Ǵ� ��� "Label"�� ���� �ʱ�ȭ �� ������ ����մϴ�.
	void presetByLabel();

	// INFO : "UI"�� ���Ǵ� "UI_Item"�鿡 ���� ���� �����Դϴ�.
	void createItems();
	void createGauges();
	void createLabel();
private:
	// INFO : "Node"�� "update"�Լ��� �������̵� �Լ��Դϴ�.
	// "UI"�� ǥ�õǴ� ��� �������� �����մϴ�.
	// @param = fDelay >> UPDATE_DELAY
	void update(float fDelay) override;

	// INFO : �÷��̾��� ������ ���õ� "UI"�� �������� ������ ���� ���� �����մϴ�.
	void updateScore();

	// INFO : �÷��̾��� �������ͽ��� ���õ� "UI"�� �������� ������ ���� ���� �����մϴ�.
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