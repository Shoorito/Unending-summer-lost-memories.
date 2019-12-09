#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

// INFO! �ش� Ŭ������ "ProgressBar"�� ����� �����մϴ�.
// ������ HP/MP���� ������ ü�°� ���� "ȥ�� �Ӽ�"�� ��� �� �� �ֽ��ϴ�.
// @since 2019-12-08��

struct S_PNode
{
	Node* pProgressNode;
	bool  isColorTexture;
};

class C_ProgressBar : public Node
{
public:
	// INFO! �Ϲ����� ���� �����Դϴ�. ��� ������ ���� ������ �� �ֽ��ϴ�.
	// @return "this"
	static C_ProgressBar* create();
	
	// INFO! ��� ������ �̸� �����ϰ� �����ϴ� �����Դϴ�.
	// ������ �������� set�Լ���� ���� �� �� ������, ���� �� ������ ������ �������ϴ�.
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
	// INFO! "Background_Node"�� ��ȯ�մϴ�.
	// @return "BACKGROUND"
	inline S_PNode* getBackground() const { return m_pBackground; }

	// INFO! "Border_Node"�� ��ȯ�մϴ�.
	// WARNING! "Border_Node"�� ��� Ư���� "ClippingNode"�� ���� "Sprite"�� ��찡 �����մϴ�.
	// ��� �Ҷ��� �ݵ�� ���� "Node"���¸� �˰� ����Ͻñ� �ٶ��ϴ�.
	// @example "isColorTexture == true >> ClipingNode"
	// @return "BORDER" = "SPRITE" || "CLIPPING_NODE"
	inline S_PNode* getBorder() const { return m_pBorder; }

public:

	// INFO! "ProgressBar_Node"�� ��ȯ�մϴ�.
	// �μ��� ������ ��ġ�� �ش��ϴ� "ProgressBar_Node"�� ��ȯ�ϸ�, �⺻ ��ǥ�� "0"�Դϴ�.
	// @return "PROGRESS_BAR" = "m_vecProgressBar[nPosition]"
	S_PNode* getProgressBar(const int nPosition = 0) const;

	// INFO! "ProgressBar"�� ���� ���൵�� ��ȯ�մϴ�.
	// �μ��� ������ ��ġ�� �ش��ϴ� "ProgressBar"�� ���൵�� ��ȯ�ϸ�, �⺻ ��ǥ�� "0"�Դϴ�.
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