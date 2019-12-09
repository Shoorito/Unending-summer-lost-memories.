#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

// INFO! 해당 클래스는 "ProgressBar"의 기능을 전반합니다.
// 간단한 HP/MP부터 보스의 체력과 같은 "혼합 속성"도 사용 할 수 있습니다.
// @since 2019-12-08日

struct S_PNode
{
	Node* pProgressNode;
	bool  isColorTexture;
};

class C_ProgressBar : public Node
{
public:
	// INFO! 일반적인 생성 형태입니다. 모든 정보를 직접 지정할 수 있습니다.
	// @return "this"
	static C_ProgressBar* create();
	
	// INFO! 모든 정보를 미리 지정하고 생성하는 형태입니다.
	// 각각의 유형들은 set함수들로 변경 할 수 있으며, 변경 시 기존의 정보가 지워집니다.
	// @param "strBG"		= "Background Img 'Route + name'"
	// @param "strBorder"	= "Border Img 'same to Background'"
	// @param "strProgress" = "Progress Img 'same to Background'"
	// @param "nProgressCount" = "Number of 'Progress'"
	// @return "this"
	static C_ProgressBar* create
	(
		const std::string& strBG,
		const std::string& strBorder,
		const std::string& strProgress,
		const int nProgressCount
	);

public:
	// INFO! "Background_Node"를 반환합니다.
	// @return "BACKGROUND"
	inline S_PNode* getBackground() const { return m_pBackground; }

	// INFO! "Border_Node"를 반환합니다.
	// WARNING! "Border_Node"는 사용 특성상 "ClippingNode"일 경우와 "Sprite"인 경우가 존재합니다.
	// 사용 할때는 반드시 현재 "Node"상태를 알고 사용하시기 바랍니다.
	// @example "isColorTexture == true >> ClipingNode"
	// @return "BORDER" = "SPRITE" || "CLIPPING_NODE"
	inline S_PNode* getBorder() const { return m_pBorder; }

public:

	// INFO! "ProgressBar_Node"를 반환합니다.
	// 인수로 지정한 위치에 해당하는 "ProgressBar_Node"를 반환하며, 기본 좌표는 "0"입니다.
	// @return "PROGRESS_BAR" = "m_vecProgressBar[nPosition]"
	S_PNode* getProgressBar(const int nPosition = 0) const;

	// INFO! "ProgressBar"의 현재 진행도를 반환합니다.
	// 인수로 지정한 위치에 해당하는 "ProgressBar"의 진행도를 반환하며, 기본 좌표는 "0"입니다.
	// @return "PROGRESS_METER" = "m_vecProgressMeter[nPosition]"
	const float getProgresseMeter(const int nPosition = 0) const;

public:
	void setBackground(const std::string& strFile);
	void setBorder(const std::string& strFile);
	void setProgress(const std::string& strFile, const int nPosition);
public:
	void createProgressBar(const std::string& strFile, const int nCount = 1);
	void createProgressBar(const Color3B& c3bColor, const Rect& recBar, const int nCount = 1);
public:
	void setBackground(const Color3B& c3bColor, const Rect& recSize);
	void setBorder(const Color3B& c3bColor, const float fBorderSize);
	void setProgress(const Color3B c3bColor, const Rect& recSize, const int nPosition);
public: 
	void setContentSize(const float fWidth, const float fHeight);
	void setProgressMeter(const float fProgress, const int nPosition);
	void setProgressCount(const int nCount);
private:
	bool init() override;
	void preset();
	void addProgress();
	void removeProgress();
private:
	S_PNode* m_pBackground;
	S_PNode* m_pBorder;
	std::vector<S_PNode*> m_vecProgressBar{};
	std::vector<float> m_vecProgressMeter{};
	void(C_ProgressBar::*m_arAdderFunc[2])();
private:
	C_ProgressBar() {}
	virtual ~C_ProgressBar() {}
	C_ProgressBar(C_ProgressBar&) = delete;
	C_ProgressBar operator=(C_ProgressBar&) = delete;
};