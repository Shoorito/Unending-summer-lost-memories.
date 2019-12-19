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

	if (pBar != nullptr)
	{
		pBar->setBackground(strBG);
		pBar->setBorder(strBorder);
		pBar->createGauges(strProgressed, nProgressedNum);

		return pBar;
	}
	else
	{
		return nullptr;
	}
}

S_PNode* C_ProgressBar::getGauge(const int nPosition) const
{
	if (nPosition < 0 || nPosition > static_cast<int>(m_vecGaugeNode.size()))
	{
		CCLOG("Wrong Position by \"Gauge\" array");
		return nullptr;
	}

	return m_vecGaugeNode[nPosition];
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
		m_pBackground->isColorTexture = false;
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

		m_pBorder->pProgressNode  = pSprite;
		m_pBorder->isColorTexture = false;
	}
	else
	{
		pSprite = static_cast<ui::Scale9Sprite*>(m_pBorder->pProgressNode);

		pSprite->setTexture(strFile);
	}
}

void C_ProgressBar::createGauges(const std::string & strFile, const int nCount)
{
	if (!m_pBackground)
	{
		CCLOG(u8"\"Gauge\"는 대상 \"Background\"가 없으면 생성 할 수 없습니다.");
		return;
	}

	if (static_cast<int>(m_vecGaugeNode.size()) > 0)
	{
		CCLOG(u8"이 함수는 \"Gauge\"를 처음 생성할 때만 사용합니다.");
		return;
	}

	float fWidth (0.0f);
	Rect  recSize(Rect::ZERO);

	fWidth  = m_pBackground->pProgressNode->getContentSize().width;
	fWidth /= nCount;

	recSize.setRect(0.0f, 0.0f, fWidth, m_pBackground->pProgressNode->getContentSize().height);

	for (int nGauge(0); nGauge < nCount; nGauge++)
	{
		S_PNode*		  pNode(nullptr);
		S_MNode*		  pMNode(nullptr);
		ui::Scale9Sprite* pMeter(nullptr);

		pNode  = new(std::nothrow) S_PNode();
		pMNode = new(std::nothrow) S_MNode();
		pMeter = ui::Scale9Sprite::create(strFile);

		pNode->isColorTexture = false;
		pNode->pProgressNode  = pMeter;

		pMeter->setTextureRect(recSize);
		pMeter->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		pMeter->setPosition
		(
			fWidth * static_cast<float>(nGauge),
			m_pBackground->pProgressNode->getPositionY()
		);

		pMNode->fCost		  = 0.0f;
		pMNode->fMaxCost	  = 0.0f;
		pMNode->fAllotment	  = 100.0f / static_cast<float>(nCount);
		pMNode->fWidth		  = fWidth;

		addChild(pMeter);

		m_vecGaugeNode.emplace_back(pNode);
		m_vecGaugeMeter.emplace_back(pMNode);

		m_nNowUsedGauge++;
	}
}

void C_ProgressBar::createGauges(const int nCount)
{
	if (!m_pBackground)
	{
		CCLOG(u8"ProgressBar는 대상 \"Background\"가 없으면 생성 할 수 없습니다.");
		return;
	}

	if (static_cast<int>(m_vecGaugeNode.size()) > 0)
	{
		CCLOG(u8"이 함수는 \"ProgressBar\"를 처음 생성할 때만 사용합니다.");
		return;
	}

	float fWidth(0.0f);
	Rect  recSize(Rect::ZERO);

	fWidth  = m_pBackground->pProgressNode->getContentSize().width;
	fWidth /= nCount;

	recSize.setRect(0.0f, 0.0f, fWidth, m_pBackground->pProgressNode->getContentSize().height);

	for (int nGauge(0); nGauge < nCount; nGauge++)
	{
		S_PNode* pNode(nullptr);
		S_MNode* pMNode(nullptr);
		ui::Scale9Sprite* pBar(nullptr);

		pBar   = Scale9Sprite::create();
		pNode  = new(std::nothrow) S_PNode();
		pMNode = new(std::nothrow) S_MNode();

		pNode->isColorTexture = true;
		pNode->pProgressNode  = pBar;

		pBar->setColor(Color3B::MAGENTA);
		pBar->setTextureRect(recSize);
		pBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		pBar->setPosition
		(
			fWidth * static_cast<float>(nGauge),
			m_pBackground->pProgressNode->getPositionY()
		);

		pMNode->fCost		= 0.0f;
		pMNode->fMaxCost	= 0.0f;
		pMNode->fAllotment	= 100.0f / static_cast<float>(nCount);
		pMNode->fWidth		= fWidth;

		addChild(pBar);

		m_vecGaugeNode.emplace_back(pNode);
		m_vecGaugeMeter.emplace_back(pMNode);

		m_nNowUsedGauge++;
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

void C_ProgressBar::setBorder(const Color3B & c3bColor, const std::string& strTagName, const float fBorderSize)
{
	if (!m_pBorder || m_fBorderSize == fBorderSize || strTagName == "")
		return;

	Rect		  recTarget(Rect::ZERO);
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
		m_strBorderStencil = strTagName;
		
		m_pBorder->isColorTexture = true;
		m_pBorder->pProgressNode  = pClipNode;

		pClipNode->setStencil(pClip);
		pStencilNode->setStencil(pStencil);

		pClipNode->setAnchorPoint(0.5f, 0.5f);
		pStencilNode->setAnchorPoint(0.5f, 0.5f);

		pStencilNode->setInverted(true);
		pStencilNode->setName(m_strBorderStencil);
		
		pStencilNode->addChild(pClip);
		pClipNode->addChild(pStencilNode);

		addChild(pClipNode);
	}
	else
	{
		pClipNode	 = static_cast<ClippingNode*>(m_pBorder->pProgressNode);
		pStencilNode = static_cast<ClippingNode*>(pClipNode->getChildByName(m_strBorderStencil));
		pClip		 = static_cast<Sprite*>(pClipNode->getStencil());
		pStencil	 = static_cast<Sprite*>(pStencilNode->getStencil());
	}

	recTarget			= static_cast<ui::Scale9Sprite*>(m_pBackground->pProgressNode)->getTextureRect();
	m_fBorderSize		= fBorderSize;

	pStencil->setTextureRect(recTarget);

	recTarget.setRect
	(
		0.0f, 0.0f,
		recTarget.size.width  + (m_fBorderSize * 2.0f),
		recTarget.size.height + (m_fBorderSize * 2.0f)
	);

	pClip->setColor(c3bColor);
	pClip->setTextureRect(recTarget);
}

void C_ProgressBar::setGauge(const std::string& strFile, const float fUsedPercent, const int nPosition)
{
	if (nPosition < 0 || nPosition > static_cast<int>(m_vecGaugeNode.size()))
		return;

	if (!isAllocateable(fUsedPercent, nPosition) || !m_vecGaugeMeter[nPosition]->fMaxCost)
		return;

	ui::Scale9Sprite* pSprite(nullptr);
	ui::Scale9Sprite* pBG(nullptr);
	S_MNode*		  pMeter(nullptr);

	pSprite = static_cast<ui::Scale9Sprite*>(m_vecGaugeNode[nPosition]->pProgressNode);
	pBG		= static_cast<ui::Scale9Sprite*>(m_pBackground->pProgressNode);
	pMeter  = m_vecGaugeMeter[nPosition];

	if (m_vecGaugeNode[nPosition]->isColorTexture)
	{
		pSprite->init();
		m_vecGaugeNode[nPosition]->isColorTexture = false;
		m_vecGaugeNode[nPosition]->isColorTexture = false;
	}

	pSprite->setTexture(strFile);

	pMeter->fAllotment	= fUsedPercent;
	pMeter->fWidth		= pBG->getContentSize().width * fUsedPercent;

	pSprite->setContentXSize(pMeter->fWidth * (pMeter->fCost / pMeter->fMaxCost));
	pSprite->setContentYSize(m_pBackground->pProgressNode->getContentSize().height);
}

void C_ProgressBar::setGauge(const Color3B& c3bColor, const float fUsedPercent, const int nPosition)
{
	if (nPosition < 0 || nPosition > static_cast<int>(m_vecGaugeNode.size()))
		return;

	if (!isAllocateable(fUsedPercent, nPosition) || !m_vecGaugeMeter[nPosition]->fMaxCost)
		return;

	ui::Scale9Sprite* pSprite(nullptr);
	ui::Scale9Sprite* pBG(nullptr);
	S_MNode*		  pMeter(nullptr);
	Rect			  recSize(Rect::ZERO);

	pMeter  = m_vecGaugeMeter[nPosition];
	pSprite = static_cast<ui::Scale9Sprite*>(m_vecGaugeNode[nPosition]->pProgressNode);
	pBG		= static_cast<ui::Scale9Sprite*>(m_pBackground->pProgressNode);

	if (!m_vecGaugeNode[nPosition]->isColorTexture)
	{
		pSprite->init();
		m_vecGaugeNode[nPosition]->isColorTexture = true;
	}

	pMeter->fAllotment = fUsedPercent;
	pMeter->fWidth	   = pBG->getContentSize().width * (fUsedPercent / 100.0f);

	recSize.setRect(0.0f, 0.0f, pMeter->fWidth * (pMeter->fCost / pMeter->fMaxCost), pBG->getContentSize().height);

	pSprite->setColor(c3bColor);
	pSprite->setTextureRect(recSize);
}

void C_ProgressBar::setContentSize(const float fWidth, const float fHeight)
{
	if (!m_pBackground || !m_pBorder)
		return;

	if (fWidth < 0.0f || fHeight < 0.0f)
		return;

	float fXpos(0.0f);
	ui::Scale9Sprite* pBG(nullptr);
	Size  szContentSize(fWidth, fHeight);

	pBG = static_cast<ui::Scale9Sprite*>(m_pBackground->pProgressNode);

	pBG->setContentSize(szContentSize);
	
	if (m_pBorder->isColorTexture)
	{
		ClippingNode* pClipNode(nullptr);
		ClippingNode* pStencilNode(nullptr);
		Sprite*		  pClip(nullptr);
		Sprite*		  pStencil(nullptr);

		pClipNode	 = static_cast<ClippingNode*>(m_pBorder->pProgressNode);
		pStencilNode = static_cast<ClippingNode*>(pClipNode->getChildByName(m_strBorderStencil));
		pClip		 = static_cast<Sprite*>(pClipNode->getStencil());
		pStencil	 = static_cast<Sprite*>(pStencilNode->getStencil());

		pStencil->setContentSize(szContentSize);

		szContentSize.width  += m_fBorderSize * 2.0f;
		szContentSize.height += m_fBorderSize * 2.0f;

		pClip->setContentSize(szContentSize);
	}
	else
	{
		m_pBorder->pProgressNode->setContentSize(szContentSize);
	}
	
	szContentSize.height = fHeight;

	for (int nGaze(0); nGaze < static_cast<int>(m_vecGaugeNode.size()); nGaze++)
	{
		ui::Scale9Sprite* pSprite(nullptr);
		S_MNode* pNode(m_vecGaugeMeter[nGaze]);

		pNode->fWidth		= fWidth * (pNode->fAllotment / 100.0f);
		szContentSize.width = pNode->fWidth * (pNode->fCost / pNode->fMaxCost);
		pSprite				= static_cast<ui::Scale9Sprite*>(m_vecGaugeNode[nGaze]->pProgressNode);

		pSprite->setContentSize(szContentSize);
		pSprite->setPosition(pBG->getPosition());
		pSprite->addPositionX(-pBG->getContentSize().width / 2.0f);
		pSprite->addPositionX(fXpos);

		fXpos += szContentSize.width;
	}
	
	sortGauges();
}

void C_ProgressBar::setGaugeMeter(const float fProgress, const int nPosition)
{
	S_MNode* pNode(m_vecGaugeMeter[nPosition]);
	ui::Scale9Sprite* pMeter(nullptr);

	if (!pNode->fMaxCost || fProgress < 0.0f || nPosition < 0)
		return;

	pNode->fCost = fProgress;
	pMeter		 = static_cast<ui::Scale9Sprite*>(m_vecGaugeNode[nPosition]->pProgressNode);

	pMeter->setContentXSize(pNode->fWidth * (pNode->fCost / pNode->fMaxCost));
}

void C_ProgressBar::setPreloadGauge(const int nCount)
{
	int  nSize(0);
	int  arAdder[2]{ 1, -1 };
	bool isAdd(false);
	
	nSize = static_cast<int>(m_vecGaugeNode.size());

	if (nCount < 1 || nSize < 1 || nSize == nCount)
		return;
	
	isAdd = nCount < nSize;

	while (nSize != nCount)
	{
		(this->*m_arAdderFunc[isAdd])();

		nSize += arAdder[isAdd];
	}
}

void C_ProgressBar::setUseGaugeCount(const int nUseProgressCount)
{
	if (static_cast<int>(m_vecGaugeNode.size()) < nUseProgressCount)
		return;

	float			  fXpos(0.0f);
	float			  fAllotment(0.0f);
	ui::Scale9Sprite* pSprite(nullptr);
	ui::Scale9Sprite* pBG(nullptr);

	if (nUseProgressCount < m_nNowUsedGauge)
	{
		for (int nInvisible(m_nNowUsedGauge - 1); nInvisible >= nUseProgressCount; nInvisible--)
		{
			pSprite = static_cast<ui::Scale9Sprite*>(m_vecGaugeNode[nInvisible]->pProgressNode);

			pSprite->setVisible(false);
			pSprite->setPosition(-5000.0f, -5000.0f);
		}
	}

	pBG					= static_cast<ui::Scale9Sprite*>(m_pBackground->pProgressNode);
	m_nNowUsedGauge		= nUseProgressCount;
	fAllotment			= 100.0f / static_cast<float>(m_nNowUsedGauge);

	for (int nList(0); nList < m_nNowUsedGauge; nList++)
	{
		S_MNode* pNode(m_vecGaugeMeter[nList]);

		if (pNode->fMaxCost < 0.0f)
		{
			std::string strMessage("");

			strMessage += "ProgressBar의 ";
			strMessage += std::to_string(nList + 1);
			strMessage += "번째 맴버의 \"fCost\"가 0.0이거나 음수입니다.";

			CCLOG(strMessage.c_str());
			CCLOG("해당 맴버 부터의 값들을 재설정 해주시기 바랍니다.");

			return;
		}

		pSprite			  = static_cast<ui::Scale9Sprite*>(m_vecGaugeNode[nList]->pProgressNode);
		pNode->fAllotment = fAllotment;
		pNode->fWidth	  = pBG->getContentSize().width * (pNode->fAllotment / 100.0f);
		
		pSprite->setContentXSize(pNode->fWidth * (pNode->fCost / pNode->fMaxCost));
		pSprite->setPosition(pBG->getPosition());
		pSprite->setVisible(true);
		pSprite->addPositionX(-pBG->getContentSize().width / 2.0f);
		pSprite->addPositionX(fXpos);

		fXpos += static_cast<float>(pSprite->getContentSize().width);
	}
}

void C_ProgressBar::setGaugeMaxCost(const float fCost, const int nPosition)
{
	if (fCost < 1.0f || nPosition > static_cast<int>(m_vecGaugeNode.size()) || nPosition < 0)
		return;

	if (m_vecGaugeMeter[nPosition]->fCost == 0.0f)
		m_vecGaugeMeter[nPosition]->fCost = fCost;

	m_vecGaugeMeter[nPosition]->fMaxCost = fCost;
}

bool C_ProgressBar::init()
{
	if (!Node::init())
		return false;

	m_pBackground		= nullptr;
	m_pBorder			= nullptr;
	m_arAdderFunc[0]	= nullptr;
	m_arAdderFunc[1]	= nullptr;
	m_fBorderSize		= 0.0f;
	m_nNowUsedGauge		= 0;

	return true;
}

void C_ProgressBar::preset()
{
	ui::Scale9Sprite* pBackground(nullptr);
	ui::Scale9Sprite* pBorder(nullptr);

	pBackground   = ui::Scale9Sprite::create();
	pBorder	      = ui::Scale9Sprite::create();
	m_pBackground = new(std::nothrow) S_PNode();
	m_pBorder	  = new(std::nothrow) S_PNode();

	addChild(pBackground);
	addChild(pBorder);

	m_pBackground->isColorTexture = false;
	m_pBorder->isColorTexture	  = false;
	m_pBackground->pProgressNode  = pBorder;
	m_pBorder->pProgressNode	  = pBackground;
	m_arAdderFunc[false]		  = &C_ProgressBar::addGauge;
	m_arAdderFunc[true]			  = &C_ProgressBar::removeGauge;
}

void C_ProgressBar::addGauge()
{
	S_PNode*		  pNode(nullptr);
	S_MNode*		  pMeterNode(nullptr);
	ui::Scale9Sprite* pSprite(nullptr);
	ui::Scale9Sprite* pBG(nullptr);

	pNode		= new(std::nothrow) S_PNode();
	pMeterNode	= new(std::nothrow) S_MNode();
	pSprite		= ui::Scale9Sprite::create();
	pBG			= static_cast<ui::Scale9Sprite*>(m_pBackground->pProgressNode);

	pSprite->setColor(Color3B::MAGENTA);
	pSprite->setAnchorPoint(Vec2(0.0f, 0.5f));
	pSprite->setTextureRect(Rect(0.0f, 0.0f, 1.0f, pBG->getContentSize().height));
	pSprite->setVisible(false);
	pSprite->setPosition(-5000.0f, -5000.0f);

	m_vecGaugeNode.emplace_back(pNode);
	m_vecGaugeMeter.emplace_back(pMeterNode);

	pNode->isColorTexture = m_vecGaugeNode.back()->isColorTexture;
	pNode->pProgressNode  = pSprite;

	pMeterNode->fAllotment	= 0.0f;
	pMeterNode->fCost		= 0.0f;
	pMeterNode->fMaxCost	= 0.0f;
	pMeterNode->fWidth		= 0.0f;

	addChild(pSprite);
}

void C_ProgressBar::removeGauge()
{
	S_PNode* pNode(nullptr);
	S_MNode* pMNode(nullptr);

	pNode  = m_vecGaugeNode.back();
	pMNode = m_vecGaugeMeter.back();

	removeChild(pNode->pProgressNode);

	pNode->isColorTexture = false;
	pNode->pProgressNode  = nullptr;

	pMNode->fAllotment	= 0.0f;
	pMNode->fMaxCost	= 0.0f;
	pMNode->fWidth		= 0.0f;
	pMNode->fCost		= 0.0f;

	m_vecGaugeNode.pop_back();
	m_vecGaugeMeter.pop_back();

	delete pNode;
	delete pMNode;

	pNode  = nullptr;
	pMNode = nullptr;
}

bool C_ProgressBar::isAllocateable(const float fAllocate, const int nPosition)
{
	float fSum(0.0f);

	for (int nMeter(0); nMeter < m_nNowUsedGauge; nMeter++)
	{
		fSum += m_vecGaugeMeter[nMeter]->fAllotment * (nMeter != nPosition);
	}

	fSum += fAllocate;

	return fSum <= 100.0f;
}

void C_ProgressBar::sortGauges()
{
	if (!m_nNowUsedGauge)
		return;

	float fXpos(0.0f);
	float fYpos(0.0f);
	ui::Scale9Sprite* pSprite(nullptr);

	pSprite = static_cast<ui::Scale9Sprite*>(m_pBackground->pProgressNode);
	fXpos	= pSprite->getPositionX();
	fXpos  -= pSprite->getContentSize().width / 2.0f;
	fYpos	= pSprite->getPositionY();

	for (int nCount(0); nCount < m_nNowUsedGauge; nCount++)
	{
		pSprite = static_cast<ui::Scale9Sprite*>(m_vecGaugeNode[nCount]->pProgressNode);

		pSprite->setPosition(fXpos, fYpos);

		fXpos += pSprite->getContentSize().width;
	}
}

void C_ProgressBar::setPosition(const float fXpos, const float fYpos)
{
	m_pBackground->pProgressNode->setPosition(fXpos, fYpos);
	m_pBorder->pProgressNode->setPosition(fXpos, fYpos);
	
	sortGauges();
}
