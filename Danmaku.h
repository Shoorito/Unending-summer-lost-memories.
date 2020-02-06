#pragma once
#include "cocos2d.h"
#include "EnumList.h"

using namespace cocos2d;

class C_Danmaku : public Node
{
public:
	// INFO : "Danmaku" ��������.
	// @return = �Լ� ������ ���� �Ҵ��� "Danmaku Pointer".
	static C_Danmaku* create();
public:
	// INFO : ����� ���� ����Ʈ�� �̿�Ǵ� "Prev"�κ��� �����͸� ��ȯ�մϴ�.
	// �ش� Ŭ������ �̿�Ǵ� ����� ���� ����Ʈ�� ���ؼ� �˰� �����ø� "DanmakuManager"Ŭ������ �����ϼ���.
	// @return = m_pPrev >> PREV_LINK
	inline C_Danmaku* getPrev() const
	{
		return m_pPrev;
	}

	// INFO : ����� ���� ����Ʈ�� �̿�Ǵ� "Next"�κ��� �����͸� ��ȯ�մϴ�.
	// �ش� Ŭ������ �̿�Ǵ� ����� ���� ����Ʈ�� ���ؼ� �˰� �����ø� "DanmakuManager"Ŭ������ �����ϼ���.
	// @return = m_pNext >> NEXT_LINK
	inline C_Danmaku* getNext() const
	{
		return m_pNext;
	}

	// INFO : ź���� ���Ǵ� �̹��� ������ ��ȯ�մϴ�.
	// �̹����� �浹, ������ ��ȭ�� ���� �������� �̺�Ʈ�� �� �Լ��� ���� ó���մϴ�.
	// @return = m_pTexture >> DANMAKU_SPRITE
	inline Sprite* getTexture() const
	{
		return m_pTexture;
	}
public:
	// INFO : ź���� �÷��̾�� �ִ� �������� ��ȯ�մϴ�.
	// @return = m_nDamage >> DANMAKU_DAMAGE
	inline const int& getDamage() const
	{
		return m_nDamage;
	}

	// INFO : ź���� ���� ������ ��ȯ�մϴ�.
	// �̵��� ���Ǵ� ���Դϴ�.
	// @return = m_fAngle >> DANMAKU_ANGLE
	inline const float& getAngle() const
	{
		return m_fAngle;
	}

	// INFO : ź���� �ӵ��� ��ȯ�մϴ�.
	// �̵��� ���Ǵ� ���Դϴ�.
	// @return = m_fSpeed >> DANMAKU_SPEED
	inline const float& getSpeed() const
	{
		return m_fSpeed;
	}

	// INFO : ź���� "��� ����"�� ��ȯ�մϴ�.
	// ��� ���δ� "enum class E_USE_TYPE" �� �����ϼ���.
	// ����� ������ "Ȱ��ȭ"�� ����� �ٸ��ϴ�.
	// @return = m_eNowUseType >> DANMAKU_IS_NOW_USE?
	inline const E_USE_TYPE& getUseType() const
	{
		return m_eNowUseType;
	}
public:
	// INFO : ź���� "Ȱ��ȭ ����"�� ��ȯ�մϴ�.
	// "Ȱ��ȭ"�� ź���� �ǽð� �̺�Ʈ/�̵��� ���θ� �� �� �ְ� ���ִ� �����Դϴ�.
	// "Ȱ��ȭ" ���¶�� �ص� "ź�� �Ŵ��� Ǯ"�� ������� ������ ������ �Ұ��ϱ� ������
	// ��� �ÿ��� �ݵ�� "ź�� �Ŵ��� Ǯ"�� �ְ� ����ؾ� �մϴ�.
	// @return = m_isEnabled >> DANMAKU_IS_ENABLED
	inline const bool& isEnabled() const
	{
		return m_isEnabled;
	}
public:
	// INFO : ����� ����Ʈ�� �̿�Ǵ� "Prev"�� ���� �� �ִ� �����Դϴ�.
	// @WARNING ź���� "���� ����� ���� ����Ʈ"���� ����� ��� �ݵ�� �������־�� �������� ��찡 ������ �ʽ��ϴ�.
	// @param = pDanmaku >> PREV_DANMAKU
	inline void setPrev(C_Danmaku* pDanmaku)
	{
		m_pPrev = pDanmaku;
	}

	// INFO : ����� ����Ʈ�� �̿�Ǵ� "Next"�� ���� �� �ִ� �����Դϴ�.
	// @WARNING ź���� "���� ����� ���� ����Ʈ"���� ����� ��� �ݵ�� �������־�� �������� ��찡 ������ �ʽ��ϴ�.
	// @param = pDanmaku >> NEXT_DANMAKU
	inline void setNext(C_Danmaku* pDanmaku)
	{
		m_pNext = pDanmaku;
	}

	// INFO : ź���� ��� ���θ� ���� �� �� �ֽ��ϴ�.
	// �ش� ��ҿ� ���� ������ "getUseType" �Լ��� �����Ͻñ� �ٶ��ϴ�.
	// @param = eType >> DANMAKU_USE_TYPE
	inline void setUseType(E_USE_TYPE eType)
	{
		m_eNowUseType = eType;
	}
public:
	// INFO : ź���� �÷��̾�� �� �������� ���� �� �� �ֽ��ϴ�.
	// @param = nDamage >> DANMAKU_DAMAGE
	void setDamage(const int nDamage);

	// INFO : ź���� ������ ���� �� �� �ֽ��ϴ�.
	// @param = fAngle >> DANMAKU_ANGLE
	void setAngle(const float fAngle);

	// INFO : ź���� �̵� �ӵ��� ���� �� �� �ֽ��ϴ�.
	// @param = fSpeed >> DANMAKU_SPEED
	void setSpeed(const float fSpeed);
public:
	// INFO : ź���� ���� �̺�Ʈ�� �߻� ��ŵ�ϴ�.
	// @WARNING �� �Լ��� ź���� ��ü�� ������ ������� ���� �ƴմϴ�.
	// ź���� ���� �� ������ �������� �� ��� �� �Լ��� ȣ���ϸ� ���� �̺�Ʈ�� �߻� ��Ű���� �ۼ��߽��ϴ�.
	void removeDanmaku();
public:
	// INFO : ź���� ������ ���ϰų� ���ִ� �뵵�� ���� �Լ��Դϴ�.
	// @param = fAddAngle >> DANMAKU_ANGLE + ADD_ANGLE
	void addAngle(const float fAddAngle);
public:
	// INFO : ź���� Ȱ��ȭ/��Ȱ��ȭ ��ŵ�ϴ�.
	// @param = isEnabled >> DANMAKU_IS_ENABLED
	void setEnabled(const bool isEnabled);
public:
	// INFO : ź���� �̹���(Sprite)�� �Է��� �μ��� �°� �����մϴ�.
	// @param = strFile   >> DANMKAU_TEXTURE_ROUTE + TEXTURE_NAME
	// @param = recTarget >> DANMAKU_USE_RECT
	void setTextureWithRect(const std::string& strFile, const Rect& recTarget);
private:
	// INFO : "Node"�� "init" �Լ��� �������̵� �� �Լ��Դϴ�.
	// �ɹ� ������ �ʱ�ȭ �̿� �۾��� �����ϴ�.
	bool init() override;
	void preset();
	void presetRemoveAct();
	// INFO : "Update"�Լ����� ȣ�⸶�� ź���� �̵���Ű�� �����Դϴ�.
	void move();
private:
	// INFO : ���� �� ������ ��� ���� �˸��� �Լ��Դϴ�.
	// �ַ� "update"�������� ����ϸ�, �� ���� "TRUE"�� �Ǹ� �ش� ź���� ��Ȱ��ȭ �˴ϴ�.
	// @return = IS_INTERSECTS_BORDER
	const bool onIntersectsBorder();

	// INFO : �÷��̾�� �浹 �� ���� �˸��� �Լ��Դϴ�.
	// �ַ� "update"�������� ����ϸ�, �� ���� "TRUE"�� �Ǹ� �ش� ź���� ��Ȱ��ȭ �˴ϴ�.
	// @return = IS_INTERSECTS_PLAYER
	const bool onIntersectsPlayer();
private:
	// INFO : "Node"�� "update"�Լ��� �������̵� �� �Լ��Դϴ�.
	// �ǽð� �̵� �� �浹 �̺�Ʈ�� ����մϴ�.
	// @param : �ش� �Լ��� �Ҹ��� ������ �����ɴϴ�, �������� �ʽ��ϴ�.
	void update(float fDelay) override;
private:
	bool m_isEnabled;
private:
	int m_nDamage;
private:
	float m_fAngle;
	float m_fSpeed;
private:
	C_Danmaku* m_pPrev;
	C_Danmaku* m_pNext;
private:
	Sprite* m_pTexture;
	Sprite* m_pDeleteTexture;
private:
	Sequence* m_pRemoveAct;
	ScaleTo*  m_pScaleDown;
private:
	E_USE_TYPE m_eNowUseType;
private:
	C_Danmaku() {}
	virtual ~C_Danmaku() {}
	C_Danmaku(C_Danmaku&) = delete;
	C_Danmaku operator=(C_Danmaku&) = delete;
};