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
	// INFO : "Item" 생성구문.
	// @return = 함수 내에서 동적 할당한 "Item Pointer".
	static C_Item* create();
public:
	// INFO : 양방향 연결 리스트에 이용되는 "Prev"부분의 포인터를 반환합니다.
	// 해당 클래스가 이용되는 양방향 연결 리스트에 대해서 알고 싶으시면 "ItemManager"클래스를 참고하세요.
	// @return = m_pPrev >> PREV_LINK
	inline C_Item* getPrev() const
	{
		return m_pPrev;
	}

	// INFO : 양방향 연결 리스트에 이용되는 "Next"부분의 포인터를 반환합니다.
	// 해당 클래스가 이용되는 양방향 연결 리스트에 대해서 알고 싶으시면 "ItemManager"클래스를 참고하세요.
	// @return = m_pNext >> NEXT_LINK
	inline C_Item* getNext() const
	{
		return m_pNext;
	}

	// INFO : 클래스의 아이템 타입을 반환합니다.
	// @return = m_eItemType >> NOW_ITEM_TYPE
	inline const E_ITEM_TYPE& getType() const
	{
		return m_eItemType;
	}

	// INFO : 클래스의 현재 사용 타입을 반환합니다.
	// 반환되는 타입의 용도는 "ItemManager.h"를 통해 알 수 있습니다.
	// @return = m_eUseType >> NOW_USE_TYPE
	inline const E_USE_TYPE& getUseType() const
	{
		return m_eUseType;
	}
public:
	// INFO : 클래스의 활성화 여부를 반환합니다.
	// @return = m_isEnabled >> NOW_IS_ENABLED
	inline const bool& isEnabled() const
	{
		return m_isEnabled;
	}

	// INFO : 아이템을 획득 했을 경우 플레이어가 가지게 되는 아이템 수치를 반환합니다.
	// 아이템 타입에 관계 없이 "얻는 수치"만을 반환합니다.
	// @return = m_nAddValue >> PLAYER_GAIN_VALUE
	inline const int& getAddValue()
	{
		return m_nAddValue;
	}
public:
	// INFO : "ItemManager"의 양방향 리스트 요소에 이용되는 "Prev"를 정할 수 있는 구문입니다.
	// @WARNING "원형 양방향 연결 리스트"에서 사용할 경우 반드시 지정해주어야 예외적인 경우가 생기지 않습니다.
	// @param = pItem >> PREV_ITEM
	inline void setPrev(C_Item* pItem)
	{
		m_pPrev = pItem;
	}

	// INFO : "ItemManager"의 양방향 리스트 요소에 이용되는 "Next"를 정할 수 있는 구문입니다.
	// @WARNING "원형 양방향 연결 리스트"에서 사용할 경우 반드시 지정해주어야 예외적인 경우가 생기지 않습니다.
	// @param = pItem >> NEXT_ITEM
	inline void setNext(C_Item* pItem)
	{
		m_pNext = pItem;
	}

	// INFO : 클래스의 아이템 타입을 설정합니다.
	// @param = eType >> USE_ITEM_TYPE
	inline void setType(const E_ITEM_TYPE& eType)
	{
		m_eItemType = eType;
	}

	// INFO : 클래스의 사용 타입을 설정합니다.
	// 인수로 지정한 타입의 용도는 "ItemManager.h"를 통해 알 수 있습니다.
	// @param = eType >> USE_TYPE
	inline void setUseType(const E_USE_TYPE& eType)
	{
		m_eUseType = eType;
	}
public:
	// INFO : 플레이어가 아이템을 얻었을 경우 얻는 수치를 설정합니다.
	// @param = nValue >> PLAYER_GAIN_VALUE
	void setAddValue(const int nValue);
public:
	// INFO : 아이템을 활성화/비활성화 시킵니다.
	// @param = isEnabled >> ITEM_IS_ENABLED
	void setEnabled(const bool isEnabled);
public:
	// INFO : 아이템의 이미지(Sprite)를 입력한 인수에 맞게 설정합니다.
	// @param = strFile   >> ITEM_TEXTURE_ROUTE + TEXTURE_NAME
	// @param = recTarget >> ITEM_USE_RECT
	void setTextureWithRect(const std::string& strFile, const Rect& recTarget);
public:
	// INFO : 아이템이 드롭 액션을 실행 시킵니다.
	// 해당 액션을 미리 설정한 구문은 "presetStartAct"에서 확인 할 수 있습니다.
	void startShowAct();
private:
	// INFO : "Sprite"의 "init" 함수를 오버라이드 한 함수입니다.
	// 맴버 변수의 초기화 이외 작업은 없습니다.
	bool init() override;
	void preset();

	// INFO : 아이템 드롭 액션에 사용되는 액션을 미리 설정합니다.
	// 액션이 저장되는 변수는 "m_pStartAct"입니다.
	void presetStartAct();

	// INFO : 드롭 액션이 끝나고 아이템이 플레이어에게 이동할 때 사용되는 함수입니다.
	// "update"함수에서 사용합니다.
	void move();
	void unDelay();
private:
	// INFO : "Sprite"의 "update"함수를 오버라이드 한 함수입니다.
	// 실시간 이동 및 충돌 이벤트를 담당합니다.
	// @param : 해당 함수가 불리는 간격을 가져옵니다, 사용되지는 않습니다.
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