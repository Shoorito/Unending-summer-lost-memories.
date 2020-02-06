#pragma once
#include "cocos2d.h"
#include "EnumList.h"

using namespace cocos2d;

const float g_fItemWidth  = 32.0f;
const float g_fItemHeight = 32.0f;

const int g_arItemValueMin[2] = { 1, 95000 };
const int g_arItemValueMax[2] = { 5, 120000 };

class C_Item : public Sprite
{
public:
	// INFO : "Item" ��������.
	// @return = �Լ� ������ ���� �Ҵ��� "Item Pointer".
	static C_Item* create();
public:
	// INFO : ����� ���� ����Ʈ�� �̿�Ǵ� "Prev"�κ��� �����͸� ��ȯ�մϴ�.
	// �ش� Ŭ������ �̿�Ǵ� ����� ���� ����Ʈ�� ���ؼ� �˰� �����ø� "ItemManager"Ŭ������ �����ϼ���.
	// @return = m_pPrev >> PREV_LINK
	inline C_Item* getPrev() const
	{
		return m_pPrev;
	}

	// INFO : ����� ���� ����Ʈ�� �̿�Ǵ� "Next"�κ��� �����͸� ��ȯ�մϴ�.
	// �ش� Ŭ������ �̿�Ǵ� ����� ���� ����Ʈ�� ���ؼ� �˰� �����ø� "ItemManager"Ŭ������ �����ϼ���.
	// @return = m_pNext >> NEXT_LINK
	inline C_Item* getNext() const
	{
		return m_pNext;
	}

	// INFO : Ŭ������ ������ Ÿ���� ��ȯ�մϴ�.
	// @return = m_eItemType >> NOW_ITEM_TYPE
	inline const E_ITEM_TYPE& getType() const
	{
		return m_eItemType;
	}

	// INFO : Ŭ������ ���� ��� Ÿ���� ��ȯ�մϴ�.
	// ��ȯ�Ǵ� Ÿ���� �뵵�� "ItemManager.h"�� ���� �� �� �ֽ��ϴ�.
	// @return = m_eUseType >> NOW_USE_TYPE
	inline const E_USE_TYPE& getUseType() const
	{
		return m_eUseType;
	}
public:
	// INFO : Ŭ������ Ȱ��ȭ ���θ� ��ȯ�մϴ�.
	// @return = m_isEnabled >> NOW_IS_ENABLED
	inline const bool& isEnabled() const
	{
		return m_isEnabled;
	}

	// INFO : �������� ȹ�� ���� ��� �÷��̾ ������ �Ǵ� ������ ��ġ�� ��ȯ�մϴ�.
	// ������ Ÿ�Կ� ���� ���� "��� ��ġ"���� ��ȯ�մϴ�.
	// @return = m_nAddValue >> PLAYER_GAIN_VALUE
	inline const int& getAddValue()
	{
		return m_nAddValue;
	}
public:
	// INFO : "ItemManager"�� ����� ����Ʈ ��ҿ� �̿�Ǵ� "Prev"�� ���� �� �ִ� �����Դϴ�.
	// @WARNING "���� ����� ���� ����Ʈ"���� ����� ��� �ݵ�� �������־�� �������� ��찡 ������ �ʽ��ϴ�.
	// @param = pItem >> PREV_ITEM
	inline void setPrev(C_Item* pItem)
	{
		m_pPrev = pItem;
	}

	// INFO : "ItemManager"�� ����� ����Ʈ ��ҿ� �̿�Ǵ� "Next"�� ���� �� �ִ� �����Դϴ�.
	// @WARNING "���� ����� ���� ����Ʈ"���� ����� ��� �ݵ�� �������־�� �������� ��찡 ������ �ʽ��ϴ�.
	// @param = pItem >> NEXT_ITEM
	inline void setNext(C_Item* pItem)
	{
		m_pNext = pItem;
	}

	// INFO : Ŭ������ ������ Ÿ���� �����մϴ�.
	// @param = eType >> USE_ITEM_TYPE
	inline void setType(const E_ITEM_TYPE& eType)
	{
		m_eItemType = eType;
	}

	// INFO : Ŭ������ ��� Ÿ���� �����մϴ�.
	// �μ��� ������ Ÿ���� �뵵�� "ItemManager.h"�� ���� �� �� �ֽ��ϴ�.
	// @param = eType >> USE_TYPE
	inline void setUseType(const E_USE_TYPE& eType)
	{
		m_eUseType = eType;
	}
public:
	// INFO : �÷��̾ �������� ����� ��� ��� ��ġ�� �����մϴ�.
	// @param = nValue >> PLAYER_GAIN_VALUE
	void setAddValue(const int nValue);
public:
	// INFO : �������� Ȱ��ȭ/��Ȱ��ȭ ��ŵ�ϴ�.
	// @param = isEnabled >> ITEM_IS_ENABLED
	void setEnabled(const bool isEnabled);
public:
	// INFO : �������� �̹���(Sprite)�� �Է��� �μ��� �°� �����մϴ�.
	// @param = strFile   >> ITEM_TEXTURE_ROUTE + TEXTURE_NAME
	// @param = recTarget >> ITEM_USE_RECT
	void setTextureWithRect(const std::string& strFile, const Rect& recTarget);
public:
	// INFO : �������� ��� �׼��� ���� ��ŵ�ϴ�.
	// �ش� �׼��� �̸� ������ ������ "presetStartAct"���� Ȯ�� �� �� �ֽ��ϴ�.
	void startShowAct();
private:
	// INFO : "Sprite"�� "init" �Լ��� �������̵� �� �Լ��Դϴ�.
	// �ɹ� ������ �ʱ�ȭ �̿� �۾��� �����ϴ�.
	bool init() override;
	void preset();

	// INFO : ������ ��� �׼ǿ� ���Ǵ� �׼��� �̸� �����մϴ�.
	// �׼��� ����Ǵ� ������ "m_pStartAct"�Դϴ�.
	void presetStartAct();

	// INFO : ��� �׼��� ������ �������� �÷��̾�� �̵��� �� ���Ǵ� �Լ��Դϴ�.
	// "update"�Լ����� ����մϴ�.
	void move();
	void unDelay();
private:
	// INFO : "Sprite"�� "update"�Լ��� �������̵� �� �Լ��Դϴ�.
	// �ǽð� �̵� �� �浹 �̺�Ʈ�� ����մϴ�.
	// @param : �ش� �Լ��� �Ҹ��� ������ �����ɴϴ�, �������� �ʽ��ϴ�.
	void update(float fDelay) override;
private:
	int m_nAddValue;
private:
	bool m_isEnabled;
	bool m_isNowActing;
	bool m_isNowUpdate;
private:
	C_Item* m_pPrev;
	C_Item* m_pNext;
private:
	Sequence* m_pStartAct;
private:
	E_USE_TYPE  m_eUseType;
	E_ITEM_TYPE m_eItemType;
private:
	C_Item() {}
	virtual ~C_Item() {}
	C_Item(C_Item&) = delete;
	C_Item operator=(C_Item&) = delete;
};