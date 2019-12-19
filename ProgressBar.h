#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

// INFO! �ش� Ŭ������ "PROGRESS_BAR"�� ����� �����մϴ�.
// ������ HP/MP���� ������ ü�°� ���� "ȥ�� �Ӽ�"�� ��� �� �� �ֽ��ϴ�.
// @since 2019-12-18��

struct S_PNode
{
	Node* pProgressNode; 
	bool  isColorTexture;
};

struct S_MNode
{
	float fAllotment;	// Meter�� ����
	float fCost;		// HP, MP�� ��������� �����̴� ��.(4000.0f == 100% >> 3000.0f == 75%)
	float fMaxCost;		// Cost�� �ʱ� �ִ�ġ.
	float fWidth;		// 100% ���� ���� ����.
};

class C_ProgressBar : public Node
{
public:
	// INFO! �Ϲ����� ���� �����Դϴ�. ��� ������ ���� ������ �� �ֽ��ϴ�.
	// @return "THIS_CLASS"
	static C_ProgressBar* create();
	
	// INFO! ��� ������ �̸� �����ϰ� �����ϴ� �����Դϴ�.
	// ������ �������� set�Լ���� ���� �� �� ������, ���� �� ������ ������ �������ϴ�.
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
	// INFO!	"BACKGROUND_NODE"�� ��ȯ�մϴ�.
	// @return	"BACKGROUND"
	inline S_PNode* getBackground() const
	{ 
		return m_pBackground; 
	}

	// INFO! "BORDER_NODE"�� ��ȯ�մϴ�.
	// WARNING! "BORDER_NODE"�� ��� Ư���� "CLIPPING_NODE"�� ���� "SPRITE_NODE"�� ��찡 �����մϴ�.
	// ��� �Ҷ��� �ݵ�� ���� "NODE"���¸� �˰� ����Ͻñ� �ٶ��ϴ�.
	// @example "isColorTexture == TRUE >> CLIPPING_NODE"
	// @return  "m_pBorder" = "BORDER" >> STATE_BY : "SPRITE_NODE" || "CLIPPING_NODE"
	inline S_PNode* getBorder() const
	{ 
		return m_pBorder; 
	}

	// INFO! "GAUGE_NODE"�� ��ȯ�մϴ�.
	// �μ��� ������ ��ġ�� �ش��ϴ� "GAUGE_NODE"�� ��ȯ�ϸ�, �⺻ ��ǥ�� "0"�Դϴ�.
	// @return "m_vecGauge[nPosition]" = "GAUGE_NODE"
	S_PNode* getGauge(const int nPosition) const;

public:
	// INFO! "PROGRESS_BAR"�� [nPosition]��° "GAUGE"�� ��ġ �ִ�ġ�� ��ȯ�մϴ�.
	// @param  "nPosition"	= "GAUGE_NUMBER"
	// @return "fMaxCost"	= "GAUGE_MAX_METER"
	inline const float& getGaugeLimit(const int nPosition) const
	{
		return m_vecGaugeMeter[nPosition]->fMaxCost;
	}

	// INFO! "PROGRESS_BAR"�� [nPosition]��° "GAUGE"�� ���� ��ġ�� ��ȯ�մϴ�.
	// ��ü "GAUGE"���� �����ϴ� ����� ��ġ�� ��� �ʹٸ� "getNowGaugeMeterByPer"�� �����ϼ���.
	// @param  "nPosition"	= "GAUGE_NUMBER"
	// @return "fCost"		= "NOW_GAUGE_METER"
	inline const float& getNowGaugeMeter(const int nPosition) const
	{
		return m_vecGaugeMeter[nPosition]->fCost;
	}

	// INFO! "PROGRESS_BAR"�� [nPosition]��° "GAUGE"�� �����ϴ� ��ü "GAUGE"�� ��ġ�� ���� �����(0~100)���� ��ȯ�մϴ�.
	// @param  "nPosition"  = "GAUGE_NUMBER"
	// @return "fAllotment" = "NOW_GAUGE_METER_BY_PERCENTAGE"
	inline const float& getNowGaugeMeterByPer(const int nPosition) const
	{
		return m_vecGaugeMeter[nPosition]->fAllotment;
	}

	// INFO! "PROGRESS_BAR"�� [nPosition]��° "GAUGE"�� �ִ� ���̸� ��ȯ�մϴ�.(���� ���̰� �ƴմϴ�.)
	// @param  "nPosition"  = "GAUGE_NUMBER"
	// @return "fWidth"		= "GAUGE_MAX_WIDTH"
	inline const float& getGaugeMeterWidth(const int nPosition) const
	{
		return m_vecGaugeMeter[nPosition]->fWidth;
	}

	// INFO! "GAUGE_COUNT"�� ��ȯ�մϴ�.
	// @return "m_nNowUsedGauge" = "NUMBER_OF_GAUGES_TO_USE"
	inline const int& getGaugeCount() const
	{
		return m_nNowUsedGauge;
	}

public:
	// INFO! "PROGRESS_BAR"���� ��� �Ǵ� "GAUGE"�� �����մϴ�.
	// WARNING! �� �Լ��� ó�� "����"�ÿ��� ��� �����մϴ�. "���� ��" �߰��� "GAUGE_TYPE"�� �߰��ϰ� ������
	// "setUseGaugeCount"�Լ��� ����Ͻñ� �ٶ��ϴ�.
	// @param	"strFile" = "GAUGE_RESOURCE_NAME"
	// @param	"nCount"  = "GAUGE_COUNT"
	// @default "nCount"���� "1"�� ���� ����Ʈ ���� ������ �ֽ��ϴ�.
	void createGauges(const std::string& strFile, const int nCount = 1);

	// INFO! "PROGRESS_BAR"���� ��� �Ǵ� "GAUGE"�� �����մϴ�.
	// WARNING! �� �Լ��� ó�� "����"�ÿ��� ��� �����մϴ�. "���� ��" �߰��� "GAUGE_TYPE"�� �߰��ϰ� ������
	// "setUseGaugeCount"�Լ��� ����Ͻñ� �ٶ��ϴ�.
	// @param	"nCount" = "GAUGE_COUNT"
	// @default "nCount"���� "1"�� ���� ����Ʈ ���� ������ �ֽ��ϴ�.
	void createGauges(const int nCount = 1);

public:
	// INFO! ���� ���������� ��� �� ����� "���� ���"�� ������ �� �ֽ��ϴ�.
	// @param "strFile" = "FILE_ROUTE" + "FILE_NAME" >> "BACKGROUND_SETUP"
	void setBackground(const std::string& strFile);

	// INFO! ���������� ��� �� �ܰ����� "���� ���"�� ������ �� �ֽ��ϴ�.
	// �� �Լ��� ���� ������ �ܰ����� "BACKGROUND"�� ������ + "BORDER_SIZE"�� �̹����� �����ϴ� ���� ��õ�մϴ�.
	// @param "strFile" = "FILE_ROUTE" + "FILE_NAME" >> "BORDER_SETUP"
	void setBorder(const std::string& strFile);

	// INFO! "PROGRESS_BAR"�� [nPosition]��° "GAUGE"�� ���ҽ��� ������ �� �ֽ��ϴ�.
	// @param "strFile"		= "FILE_ROUTE" + "FILE_NAME" >> "setProgressSprite"
	// @param "nPosition"   = "METER_NUMBER"
	void setGauge(const std::string& strFile, const float fUsedPercent, const int nPosition);

public:
	// INFO!  "BACKGROUND"�� "IS_COLOR_TEXTURE = TRUE" Ÿ���� "SET_FUNCTION"�Դϴ�.
	// @param "c3bColor" = "TEXTURE_COLOR"
	// @param "recSize"  = "TEXTURE_RECT"
	void setBackground(const Color3B& c3bColor, const Rect& recSize);

	// INFO!  "BORDER"�� "IS_COLOR_TEXTURE = TRUE" Ÿ���� "SET_FUNCTION"�Դϴ�.
	// WARNING! "strTagName"�� ���� ������ "BORDER_NODE"�� �±� ���� �ߺ����� �����ϸ� �ȵ˴ϴ�.
	// @param "c3bColor"   = "TEXTURE_COLOR"
	// @param "strTagName" = "TEXTURE_TAG_NAME"
	// @param "recSize"    = "TEXTURE_RECT"
	void setBorder(const Color3B& c3bColor, const std::string& strTagName, const float fBorderSize);

	// INFO!  "GAUGE"�� "IS_COLOR_TEXTURE = TRUE" Ÿ���� "SET_FUNCTION"�Դϴ�.
	// �� �Լ������� "GAUGE"�� "���� ���൵"�� ���� ������ �ּž� �մϴ�.(fUsedPercent)
	// @param "c3bColor"	 = "TEXTURE_COLOR"
	// @param "fUsedPercent" = "PROGRESSED_PERCENT"
	// @param "recSize"		 = "TEXTURE_RECT"
	void setGauge(const Color3B& c3bColor, const float fUsedPercent, const int nPosition);

public:
	// INFO! "PROGRESS_BAR"�� ��� ��ü���� ������ "setContentSize"ó�� ��� ������ �����Լ� �Դϴ�.
	// @param "fWidth"  = "BAR_WIDTH"
	// @param "fHeight" = "BAR_HEIGHT"
	void setContentSize(const float fWidth, const float fHeight);

	// INFO! "GAUGE[POSITION]"�� "���� ���൵"�� ���� �� �� �ִ� ���� �Լ��Դϴ�.
	// @param "fProgressed" = "SET_PROGRESS"
	// @param "nPosition"	= "GAUGE_ARRAY_NUMBER"
	void setGaugeMeter(const float fProgressed, const int nPosition);

	// INFO! "GAUGE"�� ��Ȱ��ȭ ���¿��� �߰� �� �� �ִ� �Լ��Դϴ�.
	// �� �Լ��� �߰��� "GAUGE"�ɹ��� "VECTOR"���� ���ԵǾ� ������ "��� ���� �׸�"���δ� ������� �ʽ��ϴ�.
	// �� �Լ��� ����ϰ� "setUseGaugeCount"�� ����ϸ� ���������� ��� �� �� �ֽ��ϴ�.
	// "setUseGaugeCount"�� ����ϱ� ��, "setGaugeMaxCost"�� ���ؼ� "GAUGE"�� �ִ�ġ�� �������ֽñ� �ٶ��ϴ�.
	// @param "nCount" = "PRELOAD_GAUGE_COUNT"
	void setPreloadGauge(const int nCount);
	
	// INFO! ��� �� "GAUGE"�� ������ ���մϴ�.
	// ��� "GAUGE"�� ���̴� "GAUGES_COUNT / BAR_WIDTH"�� �����˴ϴ�.
	// "setPreloadGauge"�� ���ؼ� ���ο� ��带 ������ �� ����ϴ� ��� "setGaugeMaxCost"�� ���� "GAUGE"�� �ִ�ġ�� ������ �ּž� �մϴ�.
	// @param "nUseGaugeCount" = "NUMBER_OF_GAUGES_TO_USE"
	void setUseGaugeCount(const int nUseProgressCount);

	// INFO! ������ "GAUGE"�� �ִ� ��ġ ���� �����մϴ�.
	// @param "fCost"		= "MAX_GAUGE_METER"
	// @param "nPosition"	= "GAUGE_NUMBER"
	void setGaugeMaxCost(const float fCost, const int nPosition);

	// INFO! ������ �ɹ����� ��� �����մϴ�.(���������� �������� �մϴ�.)
	void sortGauges();
public:
	// INFO! ���� setPosition�� "ProgressBar"�� �°� ���� ���� �������̵� �Լ��Դϴ�.
	// @param "fXpos" = "X_AXIS"
	// @param "fYpos" = "Y_AXIS"
	void setPosition(const float fXpos, const float fYpos) override;

private:
	// INFO! Initialize Override Function.
	bool init() override;

	// INFO! Preset Default Function.
	void preset();

	// INFO! ������ �߰� �Լ��Դϴ�. �� �� ��� �� �ϳ��� �������� �����˴ϴ�.
	// WARNING! �� �Լ��� "PRIVATE"���� �Լ��̹Ƿ� ���� ����� ��õ���� �ʽ��ϴ�.
	void addGauge();

	// INFO! ������ ���� �Լ��Դϴ�. �� �� ��� �� �ϳ��� �������� ���ŵ˴ϴ�.
	// WARNING! �� �Լ��� "PRIVATE"���� �Լ��̹Ƿ� ���� ����� ��õ���� �ʽ��ϴ�.
	void removeGauge();

private:
	// INFO! ������ �߰��� ���� �˼� �Լ��Դϴ�. �˼� ���ɿ��θ� ��ȯ�մϴ�.
	// WARNING! �� �Լ��� "PRIVATE"���� �Լ��̹Ƿ� ���� ����� ��õ���� �ʽ��ϴ�.
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