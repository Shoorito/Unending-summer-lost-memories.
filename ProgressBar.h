#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

// INFO! 해당 클래스는 "PROGRESS_BAR"의 기능을 전반합니다.
// 간단한 HP/MP부터 보스의 체력과 같은 "혼합 속성"도 사용 할 수 있습니다.
// @since 2019-12-18日

struct S_PNode
{
	Node* pProgressNode; 
	bool  isColorTexture;
};

struct S_MNode
{
	float fAllotment;	// Meter의 비율
	float fCost;		// HP, MP등 상대적으로 움직이는 값.(4000.0f == 100% >> 3000.0f == 75%)
	float fMaxCost;		// Cost의 초기 최대치.
	float fWidth;		// 100% 기준 가로 길이.
};

class C_ProgressBar : public Node
{
public:
	// INFO! 일반적인 생성 형태입니다. 모든 정보를 직접 지정할 수 있습니다.
	// @return "THIS_CLASS"
	static C_ProgressBar* create();
	
	// INFO! 모든 정보를 미리 지정하고 생성하는 형태입니다.
	// 각각의 유형들은 set함수들로 변경 할 수 있으며, 변경 시 기존의 정보가 지워집니다.
	// @param  "strBG"			= "Background Img 'Route + name'"
	// @param  "strBorder"		= "Border Img 'same to Background'"
	// @param  "strProgress"	= "Progress Img 'same to Background'"
	// @param  "nProgressCount"	= "Number of 'Progress'"
	// @return "THIS_CLASS"
	static C_ProgressBar* create
	(
		const std::string& strBG,
		const std::string& strBorder,
		const std::string& strProgress,
		const int nProgressCount
	);

public:
	// INFO!	"BACKGROUND_NODE"를 반환합니다.
	// @return	"BACKGROUND"
	inline S_PNode* getBackground() const
	{ 
		return m_pBackground; 
	}

	// INFO! "BORDER_NODE"를 반환합니다.
	// WARNING! "BORDER_NODE"는 사용 특성상 "CLIPPING_NODE"일 경우와 "SPRITE_NODE"인 경우가 존재합니다.
	// 사용 할때는 반드시 현재 "NODE"상태를 알고 사용하시기 바랍니다.
	// @example "isColorTexture == TRUE >> CLIPPING_NODE"
	// @return  "m_pBorder" = "BORDER" >> STATE_BY : "SPRITE_NODE" || "CLIPPING_NODE"
	inline S_PNode* getBorder() const
	{ 
		return m_pBorder; 
	}

	// INFO! "GAUGE_NODE"를 반환합니다.
	// 인수로 지정한 위치에 해당하는 "GAUGE_NODE"를 반환하며, 기본 좌표는 "0"입니다.
	// @return "m_vecGauge[nPosition]" = "GAUGE_NODE"
	S_PNode* getGauge(const int nPosition) const;

public:
	// INFO! "PROGRESS_BAR"의 [nPosition]번째 "GAUGE"의 수치 최대치를 반환합니다.
	// @param  "nPosition"	= "GAUGE_NUMBER"
	// @return "fMaxCost"	= "GAUGE_MAX_METER"
	inline const float& getGaugeLimit(const int nPosition) const
	{
		return m_vecGaugeMeter[nPosition]->fMaxCost;
	}

	// INFO! "PROGRESS_BAR"의 [nPosition]번째 "GAUGE"의 현재 수치를 반환합니다.
	// 전체 "GAUGE"에서 차지하는 백분율 수치를 얻고 싶다면 "getNowGaugeMeterByPer"를 참조하세요.
	// @param  "nPosition"	= "GAUGE_NUMBER"
	// @return "fCost"		= "NOW_GAUGE_METER"
	inline const float& getNowGaugeMeter(const int nPosition) const
	{
		return m_vecGaugeMeter[nPosition]->fCost;
	}

	// INFO! "PROGRESS_BAR"의 [nPosition]번째 "GAUGE"가 차지하는 전체 "GAUGE"의 수치를 정수 백분율(0~100)으로 반환합니다.
	// @param  "nPosition"  = "GAUGE_NUMBER"
	// @return "fAllotment" = "NOW_GAUGE_METER_BY_PERCENTAGE"
	inline const float& getNowGaugeMeterByPer(const int nPosition) const
	{
		return m_vecGaugeMeter[nPosition]->fAllotment;
	}

	// INFO! "PROGRESS_BAR"의 [nPosition]번째 "GAUGE"의 최대 길이를 반환합니다.(현재 길이가 아닙니다.)
	// @param  "nPosition"  = "GAUGE_NUMBER"
	// @return "fWidth"		= "GAUGE_MAX_WIDTH"
	inline const float& getGaugeMeterWidth(const int nPosition) const
	{
		return m_vecGaugeMeter[nPosition]->fWidth;
	}

	// INFO! "GAUGE_COUNT"를 반환합니다.
	// @return "m_nNowUsedGauge" = "NUMBER_OF_GAUGES_TO_USE"
	inline const int& getGaugeCount() const
	{
		return m_nNowUsedGauge;
	}

public:
	// INFO! "PROGRESS_BAR"에서 사용 되는 "GAUGE"를 생성합니다.
	// WARNING! 이 함수는 처음 "생성"시에만 사용 가능합니다. "생성 후" 추가로 "GAUGE_TYPE"을 추가하고 싶으면
	// "setUseGaugeCount"함수를 사용하시기 바랍니다.
	// @param	"strFile" = "GAUGE_RESOURCE_NAME"
	// @param	"nCount"  = "GAUGE_COUNT"
	// @default "nCount"값은 "1"의 값을 디폴트 값을 가지고 있습니다.
	void createGauges(const std::string& strFile, const int nCount = 1);

	// INFO! "PROGRESS_BAR"에서 사용 되는 "GAUGE"를 생성합니다.
	// WARNING! 이 함수는 처음 "생성"시에만 사용 가능합니다. "생성 후" 추가로 "GAUGE_TYPE"을 추가하고 싶으면
	// "setUseGaugeCount"함수를 사용하시기 바랍니다.
	// @param	"nCount" = "GAUGE_COUNT"
	// @default "nCount"값은 "1"의 값을 디폴트 값을 가지고 있습니다.
	void createGauges(const int nCount = 1);

public:
	// INFO! 현재 게이지에서 사용 할 배경을 "파일 경로"로 지정할 수 있습니다.
	// @param "strFile" = "FILE_ROUTE" + "FILE_NAME" >> "BACKGROUND_SETUP"
	void setBackground(const std::string& strFile);

	// INFO! 게이지에서 사용 할 외곽선을 "파일 경로"로 지정할 수 있습니다.
	// 이 함수를 통해 지정한 외곽선은 "BACKGROUND"의 사이즈 + "BORDER_SIZE"의 이미지로 지정하는 것을 추천합니다.
	// @param "strFile" = "FILE_ROUTE" + "FILE_NAME" >> "BORDER_SETUP"
	void setBorder(const std::string& strFile);

	// INFO! "PROGRESS_BAR"의 [nPosition]번째 "GAUGE"의 리소스를 지정할 수 있습니다.
	// @param "strFile"		= "FILE_ROUTE" + "FILE_NAME" >> "setProgressSprite"
	// @param "nPosition"   = "METER_NUMBER"
	void setGauge(const std::string& strFile, const float fUsedPercent, const int nPosition);

public:
	// INFO!  "BACKGROUND"의 "IS_COLOR_TEXTURE = TRUE" 타입의 "SET_FUNCTION"입니다.
	// @param "c3bColor" = "TEXTURE_COLOR"
	// @param "recSize"  = "TEXTURE_RECT"
	void setBackground(const Color3B& c3bColor, const Rect& recSize);

	// INFO!  "BORDER"의 "IS_COLOR_TEXTURE = TRUE" 타입의 "SET_FUNCTION"입니다.
	// WARNING! "strTagName"을 통해 지어진 "BORDER_NODE"의 태그 명은 중복으로 설정하면 안됩니다.
	// @param "c3bColor"   = "TEXTURE_COLOR"
	// @param "strTagName" = "TEXTURE_TAG_NAME"
	// @param "recSize"    = "TEXTURE_RECT"
	void setBorder(const Color3B& c3bColor, const std::string& strTagName, const float fBorderSize);

	// INFO!  "GAUGE"의 "IS_COLOR_TEXTURE = TRUE" 타입의 "SET_FUNCTION"입니다.
	// 본 함수에서는 "GAUGE"의 "현재 진행도"를 같이 지정해 주셔야 합니다.(fUsedPercent)
	// @param "c3bColor"	 = "TEXTURE_COLOR"
	// @param "fUsedPercent" = "PROGRESSED_PERCENT"
	// @param "recSize"		 = "TEXTURE_RECT"
	void setGauge(const Color3B& c3bColor, const float fUsedPercent, const int nPosition);

public:
	// INFO! "PROGRESS_BAR"의 모든 개체들을 기존의 "setContentSize"처럼 사용 가능한 편의함수 입니다.
	// @param "fWidth"  = "BAR_WIDTH"
	// @param "fHeight" = "BAR_HEIGHT"
	void setContentSize(const float fWidth, const float fHeight);

	// INFO! "GAUGE[POSITION]"의 "현재 진행도"를 설정 할 수 있는 편의 함수입니다.
	// @param "fProgressed" = "SET_PROGRESS"
	// @param "nPosition"	= "GAUGE_ARRAY_NUMBER"
	void setGaugeMeter(const float fProgressed, const int nPosition);

	// INFO! "GAUGE"를 비활성화 상태에서 추가 할 수 있는 함수입니다.
	// 이 함수로 추가한 "GAUGE"맴버는 "VECTOR"에는 포함되어 있지만 "사용 중인 항목"으로는 취급하지 않습니다.
	// 이 함수를 사용하고 "setUseGaugeCount"를 사용하면 정상적으로 사용 할 수 있습니다.
	// "setUseGaugeCount"를 사용하기 전, "setGaugeMaxCost"를 통해서 "GAUGE"의 최대치를 설정해주시기 바랍니다.
	// @param "nCount" = "PRELOAD_GAUGE_COUNT"
	void setPreloadGauge(const int nCount);
	
	// INFO! 사용 할 "GAUGE"의 갯수를 정합니다.
	// 모든 "GAUGE"의 길이는 "GAUGES_COUNT / BAR_WIDTH"로 결정됩니다.
	// "setPreloadGauge"를 통해서 새로운 노드를 생성한 후 사용하는 경우 "setGaugeMaxCost"를 통해 "GAUGE"의 최대치를 설정해 주셔야 합니다.
	// @param "nUseGaugeCount" = "NUMBER_OF_GAUGES_TO_USE"
	void setUseGaugeCount(const int nUseProgressCount);

	// INFO! 지정한 "GAUGE"의 최대 수치 값을 지정합니다.
	// @param "fCost"		= "MAX_GAUGE_METER"
	// @param "nPosition"	= "GAUGE_NUMBER"
	void setGaugeMaxCost(const float fCost, const int nPosition);

	// INFO! 게이지 맴버들을 모두 정렬합니다.(오름차순을 기준으로 합니다.)
	void sortGauges();
public:
	// INFO! 기존 setPosition을 "ProgressBar"에 맞게 만든 편의 오버라이딩 함수입니다.
	// @param "fXpos" = "X_AXIS"
	// @param "fYpos" = "Y_AXIS"
	void setPosition(const float fXpos, const float fYpos) override;

private:
	// INFO! Initialize Override Function.
	bool init() override;

	// INFO! Preset Default Function.
	void preset();

	// INFO! 게이지 추가 함수입니다. 한 번 사용 시 하나의 게이지가 생성됩니다.
	// WARNING! 이 함수는 "PRIVATE"선언 함수이므로 개별 사용은 추천하지 않습니다.
	void addGauge();

	// INFO! 게이지 제거 함수입니다. 한 번 사용 시 하나의 게이지가 제거됩니다.
	// WARNING! 이 함수는 "PRIVATE"선언 함수이므로 개별 사용은 추천하지 않습니다.
	void removeGauge();

private:
	// INFO! 게이지 추가에 대한 검수 함수입니다. 검수 가능여부를 반환합니다.
	// WARNING! 이 함수는 "PRIVATE"선언 함수이므로 개별 사용은 추천하지 않습니다.
	// @param  "fAllocate" = "CHANGE_ALLOCATE"
	// @param  "nPosition" = "GAUGE_NUMBER"
	// @return "IS_ALLOCATEABLE"
	bool isAllocateable(const float fAllocate, const int nPosition);
private:
	S_PNode* m_pBackground;
	S_PNode* m_pBorder;
	std::vector<S_PNode*> m_vecGaugeNode{};
	std::vector<S_MNode*> m_vecGaugeMeter{};
	void(C_ProgressBar::*m_arAdderFunc[2])();
private:
	int m_nNowUsedGauge;
private:
	float m_fBorderSize;
private:
	std::string m_strBorderStencil;
private:
	C_ProgressBar() {}
	virtual ~C_ProgressBar() {}
	C_ProgressBar(C_ProgressBar&) = delete;
	C_ProgressBar operator=(C_ProgressBar&) = delete;
};