#include "BonusNode.h"
#include "CocosFunctions.h"

C_BonusNode * C_BonusNode::m_pInstance = nullptr;

C_BonusNode * C_BonusNode::create()
{
	if (m_pInstance)
	{
		CCLOG(u8"\"BossStatus\"가 이미 생성 되어 있습니다.");

		return nullptr;
	}

	m_pInstance = new(std::nothrow) C_BonusNode();

	if (m_pInstance && m_pInstance->init())
	{
		m_pInstance->preset();
	}
	else
	{
		C_Functions::safeDelete(m_pInstance);
	}

	return m_pInstance;
}

void C_BonusNode::showScore(const bool& isBonus, const int& nScore)
{
	if (isBonus)
	{
		m_pTitle->setTextureRect(Rect(0.0f, 0.0f, 404.0f, 40.0f));
		m_pScore->setString(C_Functions::convertToString(nScore));
		m_pScore->setVisible(true);
	}
	else
	{
		m_pTitle->setTextureRect(Rect(0.0f, 40.0f, 404.0f, 40.0f));
		m_pScore->setVisible(false);
	}

	setVisible(true);
	runAction(m_pShowAct);
}

void C_BonusNode::hideScore()
{
	setVisible(false);
}

const bool C_BonusNode::setFontFile(const std::string & strFont)
{
	if (!m_pScore->initWithTTF("", strFont, m_nDefaultFontSize))
	{
		CCLOG(u8"\"BonusNode\"에 지정한 폰트 파일이 경로상 존재하지 않습니다.");

		return false;
	}

	return true;
}

bool C_BonusNode::init()
{
	if (!Node::init())
		return false;

	m_pScore = nullptr;
	m_pTitle = nullptr;
	m_pShowAct = nullptr;
	m_nDefaultFontSize = 35;

	return true;
}

void C_BonusNode::preset()
{
	m_pTitle = Sprite::create("Bonus_Score_Title.png");
	m_pScore = Label::create();

	m_pTitle->setPosition(640.0f, 500.0f);
	m_pScore->setPosition(m_pTitle->getPosition());
	m_pScore->addPositionY(-50.0f);

	presetAct();

	addChild(m_pTitle);
	addChild(m_pScore);
}

void C_BonusNode::presetAct()
{
	DelayTime* pDelay(nullptr);
	CallFunc*  pFunc(nullptr);
	
	pDelay		= DelayTime::create(3.0f);
	pFunc		= CallFunc::create(CC_CALLBACK_0(C_BonusNode::hideScore, this));
	m_pShowAct	= Sequence::create(pDelay, pFunc, nullptr);

	m_pShowAct->retain();
}
