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
	// INFO : "PlayerUI" 생성구문.
	// @return = m_pInstance(singleton Type)
	static C_PlayerUI* create();

	// INFO : "PlayerUI" 참조구문.
	// @return = m_pInstance(singleton Type)
	static inline C_PlayerUI* getInstance() { return m_pInstance; }
public:
	// INFO : 해당 함수는 지정한 타입에 맞는 "UI_ITEM"을 반환합니다.
	// @param  = "eType" >> "고정형_UI_TYPE"
	// @return = "m_arItem[TYPE]"
	inline Sprite* getItem(const E_UI_IMG& eType) const
	{ 
		return m_arUIItem[static_cast<int>(eType)]; 
	}

	// INFO : 입력한 타입에 맞는 "UI게이지"를 반환합니다.
	// @param = "eType" >> GAUGE_TYPE
	inline C_ProgressBar* getGauge(const E_UI_GAUGE& eType) const
	{ 
		return m_arUIGauge[static_cast<int>(eType)];
	}

	// INFO : 입력한 타입에 맞는 "Score_Title" Label을 반환합니다.
	// @param = "eType" >> SCORE_TYPE
	inline Label* getScoreLabel(const E_UI_TITLE& eType) const
	{
		return m_arUITitle[static_cast<int>(eType)];
	}
public:
	// INFO : 플레이어 정보 이외 "UI"에 표시되는 이미지 텍스쳐를 지정합니다.
	// @param = "strItem" >> TEXTURE_ROUTE + TEXTURE_NAME
	// @param = "eType"	  >> ITEM_TYPE
	void setItem(const std::string& strItem, const E_UI_IMG& eType);

	// INFO : 플레이어 정보 이외 "UI"에 표시되는 이미지 텍스쳐를 아틀라스 이미지 형태로 설정합니다.
	// @param = "strItem" >> TEXTURE_ROUTE + TEXTURE_NAME
	// @param = "recSize" >> TEXTURE_RECT_SIZE
	// @param = "eType"	  >> ITEM_TYPE
	void setItemByRect(const std::string& strItem, const Rect& recSize, const E_UI_IMG& eType);
public:
	// INFO : 컬러 타입으로 지정한 타입의 UI 게이지 형태를 설정합니다.
	// @param = "c3bColor"	>> GAUGE_COLOR
	// @param = "eType"		>> GAUGE_TYPE
	void setGaugeConfig(const Color3B& c3bColor, const E_UI_GAUGE& eType);

	// INFO : 텍스쳐로 지정한 타입의 게이지 형태를 설정합니다.
	// @param = "strFile"	>> TEXTURE_ROUTE + TEXTURE_NAME
	// @param = "eType"		>> GAUGE_TYPE
	void setGaugeConfig(const std::string& strFile, const E_UI_GAUGE& eType);
public:
	// INFO : "Score_Label"에 사용 될 폰트를 폰트 파일로 정합니다.
	// 현재 지원되는 폰트 타입은 ".TTF, .OTF"입니다.
	// @param = "strFontFile" >> FONT_ROUTE + FONT_NAME
	// @param = "eType"		  >> TITLE_TYPE
	void setScoreFontFile(const std::string& strFontFile, const E_UI_TITLE& eType);
public:
	// INFO : "PlayerUI"의 활성화 여부를 설정합니다.
	// 비활성화 시킬경우 플레이어 정보의 업데이트가 이루어지지 않습니다.
	// @param = isEnabled >> MANAGER_IS_ENABLED
	void setEnabled(const bool isEnabled);
private:
	// INFO : "Node" 클래스의 "init"함수를 오버라이드 한 함수입니다.
	// 클래스에서 관리하는 맴버 변수의 초기화를 담당합니다.
	// @return = IS_INITIALIZE
	bool init() override;
private:
	// INFO : "preset"함수들을 모아서 실행하는 편의 함수입니다.
	void preset();

	// INFO : 게이지 타입의 "UI_Item"에 대한 초기화 및 세팅을 담당합니다.
	void presetByGauge();

	// INFO : "PLAYER_UI"타입 이외의 "UI_Item"에 대한 초기화 및 세팅을 담당합니다.
	void presetByItems();

	// INFO : "UI"에 사용되는 모든 "Label"에 대한 초기화 및 세팅을 담당합니다.
	void presetByLabel();

	// INFO : "UI"에 사용되는 "UI_Item"들에 대한 생성 구문입니다.
	void createItems();
	void createGauges();
	void createLabel();
private:
	// INFO : "Node"의 "update"함수의 오버라이드 함수입니다.
	// "UI"에 표시되는 모든 정보들을 갱신합니다.
	// @param = fDelay >> UPDATE_DELAY
	void update(float fDelay) override;

	// INFO : 플레이어의 점수에 관련된 "UI"의 정보들을 정해진 간격 마다 갱신합니다.
	void updateScore();

	// INFO : 플레이어의 스테이터스에 관련된 "UI"의 정보들을 정해진 간격 마다 갱신합니다.
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