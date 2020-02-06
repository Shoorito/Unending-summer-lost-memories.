#pragma once
#include "cocos2d.h"
#include "EnumList.h"

using namespace cocos2d;

class C_Enemy : public Sprite
{
public:
	// INFO : "Enemy" ��������.
	// @return = �Լ� ������ ���� �Ҵ��� "Enemy Pointer".
	static C_Enemy* create();
public:
	// INFO : �� ��ü�� "HP"�� ��ȯ�մϴ�.
	// @return = m_nHP >> ENEMY_HP
	inline const int& getHP() const
	{ 
		return m_nHP; 
	}

	// INFO : �� ��ü�� �ǽð� ���� ���� ��ȯ�մϴ�.
	// �ַ� "update"�Լ����� ���ϵ��� �߻� ��ų �� ���˴ϴ�.
	// @return m_nUpdateCount >> UPDATE_COUNT
	inline const int& getUpdateCount() const
	{
		return m_nUpdateCount;
	}

	// INFO : �� ��ü�� ���� Ÿ���� ��ȯ�մϴ�.
	// �÷��̾� ���ݿ� �Լ� ������ �迭���� ����մϴ�.
	// @return m_nAttackType >> ENEMY_ATTACK_TYPE
	inline const int& getAttackType() const
	{
		return m_nAttackType;
	}

	// INFO : �� ��ü Ÿ���� ��ȯ�մϴ�.
	// �ش� Ÿ������ ������ ������ �����ϸ� ������ ��ȯ�� ��ȯ��ü�͵� ������ �����մϴ�.
	// @return m_eType >> ENEMY_TYPE
	inline const E_ENEMY_TYPE& getType() const
	{
		return m_eType;
	}

	// INFO : Ŭ������ Ȱ��ȭ ���θ� ��ȯ�մϴ�.
	// @return = m_isEnabled >> NOW_IS_ENABLED
	inline const bool& isEnabled() const
	{
		return m_isEnabled;
	}

	// INFO : ����� ���� ����Ʈ�� �̿�Ǵ� "Prev"�κ��� �����͸� ��ȯ�մϴ�.
	// �ش� Ŭ������ �̿�Ǵ� ����� ���� ����Ʈ�� ���ؼ� �˰� �����ø� "EnemyManager"Ŭ������ �����ϼ���.
	// @return = m_pPrev >> PREV_LINK
	inline C_Enemy* getPrev() const
	{
		return m_pPrev;
	}

	// INFO : ����� ���� ����Ʈ�� �̿�Ǵ� "Next"�κ��� �����͸� ��ȯ�մϴ�.
	// �ش� Ŭ������ �̿�Ǵ� ����� ���� ����Ʈ�� ���ؼ� �˰� �����ø� "EnemyManager"Ŭ������ �����ϼ���.
	// @return = m_pNext >> NEXT_LINK
	inline C_Enemy* getNext() const
	{
		return m_pNext;
	}
public:
	// INFO : �ش� �� ��ü���� ����ϴ� �ִϸ��̼� �׼��� ��ȯ�մϴ�.
	// �� ��ü�� ����ϴ� �ִϸ��̼��� �ټ� �� ��쵵 �ֱ⿡ �μ��� ���� �������� ���ϴ�
	// �ִϸ��̼��� �������־�� �մϴ�.
	// @param  = nPosition >> ARRAY_NUM
	// @return = m_vecAnim >> ANIMATION_ARRAY[ARRAY_NUM]
	Repeat* getAnimation(const int nPosition) const;
public:
	// INFO : �� ��ü�� Ÿ���� ������ �� �ֽ��ϴ�.
	// �� ��ü�� Ÿ�Կ� ���� ���� ���� ���մϴ�.
	// @param = eType >> ENEMY_TYPE
	inline void setType(const E_ENEMY_TYPE& eType)
	{
		m_eType = eType;
	}
	// INFO : ����� ����Ʈ�� �̿�Ǵ� "Prev"�� ���� �� �ִ� �����Դϴ�.
	// @WARNING �� ��ü�� "���� ����� ���� ����Ʈ"���� ����� ��� �ݵ�� �������־�� �������� ��찡 ������ �ʽ��ϴ�.
	// @param = pEnemy >> PREV_ENEMY
	inline void setPrev(C_Enemy* pEnemy)
	{
		m_pPrev = pEnemy;
	}

	// INFO : ����� ����Ʈ�� �̿�Ǵ� "Next"�� ���� �� �ִ� �����Դϴ�.
	// @WARNING �� ��ü�� "���� ����� ���� ����Ʈ"���� ����� ��� �ݵ�� �������־�� �������� ��찡 ������ �ʽ��ϴ�.
	// @param = pEnemy >> NEXT_ENEMY
	inline void setNext(C_Enemy* pEnemy)
	{
		m_pNext = pEnemy;
	}
public:
	// INFO : �� ��ü�� �̵�, � ��� ���Ǵ� �������� ��� �ʱ�ȭ�մϴ�.
	// �� ��ü�� � �̵� �� ����ϸ� �̵� ���ܸ� ���� �� �� �ֽ��ϴ�.
	void initMovement();
public:
	// INFO : �� ��ü�� ��� �� �ִϸ��̼� �׼��� ���� ����� ���ؼ� ���� �� �� �ֽ��ϴ�.
	// �ִϸ��̼��� ������ Ÿ���� ������ ���ϴ� �ӵ��� ��� �� �� �ֽ��ϴ�.
	// @param = vecFiles >> "'FILE_ROUTE + FILE_NAME' LIST"
	// @param = fDelay	 >> DELAY_TIME
	void addAnimationWithFiles(const std::vector<std::string>& vecFiles, const float fDelay);

	// INFO : �� ��ü�� ��� �� �ִϸ��̼� �׼��� ��Ʋ�� �̹���(Atlas Image)�� ���ؼ� ���� �� �� �ֽ��ϴ�.
	// ���� ������ "RECT"�� �����ϰ�, �ִϸ��̼� ������ ������ ���� �� �� �ִ� ������ ���� �������� ������ �����մϴ�.
	// @param = strFile  >> FILE_ROUTE + FILE_NAME
	// @param = recSize  >> ANIMATION_TEXTURE_SIZE
	// @param = nCount	 >> ANIMATION_TEXTURE_COUNT
	// @param = fDelay	 >> DELAY_TIME
	void addAnimationWithAtlas(const std::string& strFile, const Rect& recSize, const int nCount, const float fDelay);
	
	// INFO : �� ��ü�� ��Ʋ�� �̹���(Atlas Image)�� �̹� �ؽ��ķ� ���������� ��� ����ϴ� ����Դϴ�.
	// @param = recSize  >> ANIMATION_TEXTURE_SIZE
	// @param = nCount	 >> ANIMATION_TEXTURE_COUNT
	// @param = fDelay	 >> DELAY_TIME
	void addAnimationWithRects(const Rect& recSize, const int nCount, const float fDelay);
public:
	// INFO : �� ��ü�� "HP"�� ������ �� �ֽ��ϴ�.
	// @WARNING = '0'���� ������ ��� �� ��ü�� �Ҹ�� ������ ���ֵǾ� �Ҹ� �� �� ������ �����ؾ� �մϴ�.
	// @param   = nHP >> ENEMY_HP
	virtual void setHP(const int nHP);

	// INFO : �� ��ü�� "HP"�� ���ϰų� �� �� ����ϴ� ���� �Լ��Դϴ�.
	// @param = nHP >> (PREV_ENEMY_HP + ADD_HP)
	virtual void addHP(const int nHP);

	// INFO : �� ��ü�� Ȱ��ȭ/��Ȱ��ȭ ��ŵ�ϴ�.
	// @param = isEnabled >> ITEM_IS_ENABLED
	virtual void setEnabled(const bool isEnabled);
public:
	// INFO : �� ��ü�� ���� Ÿ���� �����մϴ�.
	// �÷��̾� ���ݿ� �Լ� ������ �迭���� ����մϴ�.
	// @param = nType >> ATTACK_TYPE
	void setAttackType(const int nType);
public:
	// INFO : ���� ��ü�� ���� �� �ִϸ��̼� �׼� �� �Է��� �μ��� �ش��ϴ� ��ġ�� �ִ� �ִϸ��̼��� ����մϴ�.
	// @param = nType >> PLAY_TYPE_ANIMATION
	void startAnimation(const int nType);

	// INFO : �� ��ü�� � ��� �μ����� �����մϴ�.
	// �ش� ������� ���� �� �μ����� "update"�Լ��� ���� �۵��մϴ�.
	// @param = fAngle		 >> MOVE_ANGLE
	// @param = fRadius		 >> MOVE_PIVOT_RADIUS
	// @param = fStartAngle  >> MOVE_PIVOT_START_ANGLE,
	// @param = vecSpinPivot >> MOVE_PIVOT
	// @param = isFilp		 >> MOVE_IS_FILP
	void setSpinMovement(const float fAngle, const float fRadius, const float fStartAngle, const Vec2& vecSpinPivot, const bool isFilped);
public:
	// INFO : �� ��ü�� �̹���(Sprite)�� �Է��� �μ��� �°� �����մϴ�.
	// @param = strFile   >> ENEMY_TEXTURE_ROUTE + TEXTURE_NAME
	// @param = recTarget >> ENEMY_USE_RECT
	void setTextureWithRect(const std::string& strFile, const Rect& recSprite);
protected:
	virtual bool init() override;
	virtual void preset();
	// INFO : �Լ� ������ �迭�� ���� ����� �̸� �����մϴ�.
	virtual void presetPattern();
protected:
	// INFO : �ǽð� ���� ���� ���Ƿ� �����մϴ�.
	// @param : nCount >> UPDATE_COUNT
	void setUpdateCount(const int nCount);

	// INFO : �ǽð� ���� ���� �Է��� �� ��ŭ ���ϰų� ���ϴ�.
	// @param : nCount >> PREV_UPDATE_COUNT + ADD_COUNT
	void addUpdateCount(const int nCount);
private:
	// INFO : "Sprite"�� "update"�Լ��� �������̵� �� �Լ��Դϴ�.
	// �ǽð� �̵� �� ���� �̺�Ʈ�� ����մϴ�.
	// @param : �ش� �Լ��� �Ҹ��� ������ �����ɴϴ�, �������� �ʽ��ϴ�.
	virtual void update(float fDelay);
private:
	// INFO : "Update"�Լ����� ���Ǵ� �� ��ü�� ��� �̵� ������Ʈ �Լ��Դϴ�.
	void updateSpinMover();
private:
	// INFO : "Enemy"�� ����ϴ� ���� ������ �������� "m_arPattern" �Լ� �迭 �����ͷ� ȣ�� �˴ϴ�.
	// �μ��� "nUpdateCount"�� ���� �־��ִ� ���� �ƴ� �ɹ� ������ "m_nUpdateCount"�� ���˴ϴ�.
	// "nUpdateCount"�� ���� ���� ���� ������ ����Ͽ� �ߵ� ������ �����մϴ�.
	void pattern01(const int nCount);
	void pattern02(const int nCount);
	void pattern03(const int nCount);
	void pattern04(const int nCount);
	void pattern05(const int nCount);
	void pattern06(const int nCount);
	void pattern07(const int nCount);
	void pattern08(const int nCount);
private:
	void(C_Enemy::*m_arPattern[8])(const int);
private:
	std::vector<Repeat*> m_vecAnim;
private:
	E_ENEMY_TYPE m_eType;
private:
	C_Enemy* m_pPrev;
	C_Enemy* m_pNext;
private:
	bool m_isEnabled;
	bool m_isSpinFilped;
private:
	int m_nHP;
	int m_nAttackType;
	int	m_nUpdateCount;
private:
	float m_fSpinAngle;
	float m_fAngle;
	float m_fSpinRadius;
	Vec2  m_vecSpinPivot;
protected:
	C_Enemy() {}
	virtual ~C_Enemy() {}
	C_Enemy(C_Enemy&) = delete;
	C_Enemy operator=(C_Enemy&) = delete;
};