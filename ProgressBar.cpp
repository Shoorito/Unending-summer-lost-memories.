#include "ProgressBar.h"
#include "CocosFunctions.h"

C_ProgressBar * C_ProgressBar::create()
{
	C_ProgressBar* pBar(nullptr);

	pBar = new(std::nothrow) C_ProgressBar();

	if (pBar && pBar->init())
	{
		pBar->autorelease();
		pBar->preset();

		return pBar;
	}
	else
	{
		C_Functions::safeDelete(pBar);

		return nullptr;
	}
}

C_ProgressBar * C_ProgressBar::create(const std::string & strBG, const std::string & strBorder, const std::string & strProgressed, const int nProgressedNum)
{
	C_ProgressBar* pBar(nullptr);

	pBar = C_ProgressBar::create();

	if (pBar)
	{
		pBar->setBackground(strBG);
		pBar->createProgressBar(strProgressed, nProgressedNum);
		pBar->setBorder(strBorder);

		return pBar;
	}
	else
	{
		return nullptr;
	}
}

S_PNode* C_ProgressBar::getProgressBar(const int nPosition) const
{
	if (nPosition < 0 || nPosition > static_cast<int>(m_vecProgressBar.size()))
	{
		CCLOG("Wrong Position by \"progressbar\" array");
		return nullptr;
	}

	return m_vecProgressBar[nPosition];
}

const float C_ProgressBar::getProgresseMeter(const int nPosition) const
{
	if (nPosition < 0 || nPosition > static_cast<int>(m_vecProgressMeter.size()))
	{
		CCLOG("Wrong Position by \"ProgressMeter\" array");
		return 0.0f;
	}

	return m_vecProgressMeter[nPosition];
}

void C_ProgressBar::setBackground(const std::string & strFile)
{
	if (static_cast<int>(strFile.size()) < 5)
		return;
	
	ui::Scale9Sprite* pBG(nullptr);

	pBG = static_cast<ui::Scale9Sprite*>(m_pBackground->pProgressNode);

	if (m_pBackground->isColorTexture)
	{
		pBG->init();
	}

	pBG->setTexture(strFile);
}

void C_ProgressBar::setBorder(const std::string & strFile)
{
	if ((static_cast<int>(strFile.size()) < 5) || (!m_pBorder))
		return;

	ui::Scale9Sprite* pSprite(nullptr);

	if (m_pBorder->isColorTexture)
	{
		removeChild(m_pBorder->pProgressNode);

		m_pBorder->pProgressNode = nullptr;

		pSprite = ui::Scale9Sprite::create(strFile);

		addChild(pSprite);

		m_pBorder->pProgressNode = pSprite;
	}
	else
	{
		pSprite = static_cast<ui::Scale9Sprite*>(m_pBorder->pProgressNode);

		pSprite->setTexture(strFile);
	}
}

void C_ProgressBar::setProgress(const std::string & strFile, const int nPosition)
{
	if (nPosition < 0 || nPosition > static_cast<int>(m_vecProgressBar.size()))
		return;

	ui::Scale9Sprite* pSprite(nullptr);

	pSprite = static_cast<ui::Scale9Sprite*>(m_vecProgressBar[nPosition]->pProgressNode);

	if (m_vecProgressBar[nPosition]->isColorTexture)
	{
		pSprite->init();
	}

	pSprite->setTexture(strFile);
}

void C_ProgressBar::createProgressBar(const std::string & strFile, const int nCount)
{
	if (static_cast<int>(m_vecProgressBar.size()) > 0)
	{
		CCLOG(u8"이 함수는 \"ProgressBar\"를 처음 생성할 때만 사용합니다.");
		return;
	}

	for (int nProgressBar(0); nProgressBar < nCount; nProgressBar++)
	{
		ui::Scale9Sprite* pBar(nullptr);

		pBar = ui::Scale9Sprite::create(strFile);
		
		addChild(pBar);

		//m_vecProgressBar.emplace_back(pBar);
	}
}

void C_ProgressBar::createProgressBar(const Color3B & c3bColor, const Rect& recBar, const int nCount)
{
	if (static_cast<int>(m_vecProgressBar.size()) > 0)
	{
		CCLOG(u8"이 함수는 \"ProgressBar\"를 처음 생성할 때만 사용합니다.");
		return;
	}

	for (int nProgressBar(0); nProgressBar < nCount; nProgressBar++)
	{
		ui::Scale9Sprite* pBar(nullptr);

		pBar = Scale9Sprite::create();
		pBar->setColor(c3bColor);
		pBar->setTextureRect(recBar);

		addChild(pBar);

		//m_vecProgressBar.emplace_back(pBar);
	}
}

void C_ProgressBar::setBackground(const Color3B & c3bColor, const Rect & recSize)
{
	if (!m_pBackground)
	{
		CCLOG(u8"\"m_pBackground\"가 생성되어 있지 않습니다.");
		return;
	}
	
	ui::Scale9Sprite* pSprite(nullptr);

	pSprite = static_cast<ui::Scale9Sprite*>(m_pBackground->pProgressNode);

	if (!m_pBackground->isColorTexture)
	{
		m_pBackground->isColorTexture = true;

		pSprite->init();
	}
	
	pSprite->setColor(c3bColor);
	pSprite->setTextureRect(recSize);
}

void C_ProgressBar::setBorder(const Color3B & c3bColor, const float fBorderSize)
{
	if (!m_pBorder)
		return;

	Rect		  recTarget{};
	Sprite*		  pStencil(nullptr);
	Sprite*		  pClip(nullptr);
	ClippingNode* pClipNode(nullptr);
	ClippingNode* pStencilNode(nullptr);

	if (!m_pBorder->isColorTexture)
	{
		removeChild(m_pBorder->pProgressNode);

		pStencil	 = Sprite::create();
		pClip		 = Sprite::create();
		pClipNode	 = ClippingNode::create();
		pStencilNode = ClippingNode::create();
		
		m_pBorder->isColorTexture = true;
		m_pBorder->pProgressNode  = pClipNode;

		pClipNode->setStencil(pClip);
		pStencilNode->setStencil(pStencil);

		pClipNode->setAnchorPoint(0.5f, 0.5f);
		pStencilNode->setAnchorPoint(0.5f, 0.5f);

		pStencilNode->setInverted(true);
		pStencilNode->setName("ProgressBar_Stencil");
		
		pStencilNode->addChild(pClip);
		pClipNode->addChild(pStencilNode);

		addChild(pClipNode);
	}
	else
	{
		pClipNode	 = static_cast<ClippingNode*>(m_pBorder->pProgressNode);
		pStencilNode = static_cast<ClippingNode*>(pClipNode->getChildByName("ProgressBar_Stencil"));
		pClip		 = static_cast<Sprite*>(pClipNode->getStencil());
		pStencil	 = static_cast<Sprite*>(pStencilNode->getStencil());
	}

	recTarget = static_cast<ui::Scale9Sprite*>(m_pBackground->pProgressNode)->getTextureRect();

	pStencil->setTextureRect(recTarget);

	recTarget.setRect
	(
		0.0f, 0.0f,
		recTarget.size.width + (fBorderSize * 2.0f),
		recTarget.size.height + (fBorderSize * 2.0f)
	);

	pClip->setColor(c3bColor);
	pClip->setTextureRect(recTarget);
}

void C_ProgressBar::setProgress(const Color3B c3bColor, const Rect & recSize, const int nPosition)
{
	ui::Scale9Sprite* pSprite(nullptr);

	pSprite = static_cast<ui::Scale9Sprite*>(m_vecProgressBar[nPosition]->pProgressNode);
	
	if (!m_vecProgressBar[nPosition]->isColorTexture)
	{
		m_vecProgressBar[nPosition]->isColorTexture = true;

		pSprite->init();
	}

	pSprite->setColor(c3bColor);
	pSprite->setTextureRect(recSize);
}

void C_ProgressBar::setContentSize(const float fWidth, const float fHeight)
{
}

void C_ProgressBar::setProgressMeter(const float fProgress, const int nPosition)
{
}

void C_ProgressBar::setProgressCount(const int nCount)
{
	int  nSize(0);
	int  arAdder[2]{ -1, 1 };
	bool isAdd(false);
	
	nSize = static_cast<int>(m_vecProgressBar.size());

	if (nCount < 1 || nSize < 1 || nSize == nCount)
		return;
	
	isAdd = nCount < nSize;

	while (nSize != nCount)
	{
		(this->*m_arAdderFunc[isAdd])();

		nSize += arAdder[isAdd];
	}
}

bool C_ProgressBar::init()
{
	if (!Node::init())
		return false;

	m_pBackground = nullptr;
	m_pBorder = nullptr;

	return true;
}

void C_ProgressBar::preset()
{
	ui::Scale9Sprite* pBackground(nullptr);
	ui::Scale9Sprite* pBorder(nullptr);
	S_PNode*	  pBGNode(nullptr);
	S_PNode*	  pBorderNode(nullptr);

	pBackground = ui::Scale9Sprite::create();
	pBorder	    = ui::Scale9Sprite::create();
	pBGNode		= new(std::nothrow) S_PNode();
	pBorderNode = new(std::nothrow) S_PNode();

	addChild(pBackground);
	addChild(pBorder);

	pBorderNode->isColorTexture = false;
	pBGNode->isColorTexture		= false;
	pBorderNode->pProgressNode	= pBorder;
	pBGNode->pProgressNode		= pBackground;
	m_arAdderFunc[false]		= &C_ProgressBar::addProgress;
	m_arAdderFunc[true]			= &C_ProgressBar::removeProgress;
}

void C_ProgressBar::addProgress()
{
	S_PNode*	  pNode(nullptr);
	ui::Scale9Sprite* pSprite(nullptr);
	ui::Scale9Sprite* pBack(nullptr);

	pNode	= new(std::nothrow) S_PNode();
	pBack	= static_cast<ui::Scale9Sprite*>(m_vecProgressBar.back()->pProgressNode);
	pSprite = ui::Scale9Sprite::create();

	pSprite->setColor(Color3B::MAGENTA);
	pSprite->setTextureRect(pBack->getTextureRect());

	pNode->isColorTexture = m_vecProgressBar.back()->isColorTexture;
	pNode->pProgressNode  = pSprite;

	addChild(pSprite);

	m_vecProgressBar.emplace_back(pNode);
	m_vecProgressMeter.emplace_back(100.0f);
}

void C_ProgressBar::removeProgress()
{
	S_PNode* pNode(nullptr);

	pNode = m_vecProgressBar.back();

	removeChild(pNode->pProgressNode);

	pNode->isColorTexture = false;
	pNode->pProgressNode  = nullptr;

	m_vecProgressBar.pop_back();
	m_vecProgressMeter.pop_back();

	delete pNode;

	pNode = nullptr;
}
