#pragma once
#include "cocos2d.h"
#include "EnumList.h"

using namespace cocos2d;

class C_Enemy;

class C_EnemyManager : public Node
{
public:
	static C_EnemyManager* create();
	inline static C_EnemyManager* getInstance() { return m_pInstance; }
public:
	inline const int& getCount(const E_USE_TYPE& eType)
	{
		return m_arCountList[static_cast<int>(eType)];
	}
	inline C_Enemy* getHead(const E_USE_TYPE& eType)
	{
		return m_arHead[static_cast<int>(eType)];
	}
	inline C_Enemy* getTail(const E_USE_TYPE& eType)
	{
		return m_arTail[static_cast<int>(eType)];
	}
	inline C_Enemy* getCursor(const E_USE_TYPE& eType)
	{
		return m_arCursor[static_cast<int>(eType)];
	}
public:
	void addEnemy(C_Enemy* pEnemy, const E_USE_TYPE& eType);
	void pushEnemy(C_Enemy* pEnemy, const E_USE_TYPE& eType);
	void changeEnemy(C_Enemy* pEnemy, const E_USE_TYPE& eChangeType);
	void popEnemy(C_Enemy* pEnemy, const E_USE_TYPE& eType);
public:
	void disabledAllEnemy(const E_ENEMY_TYPE& eType);
	void pauseAllEnemy(const E_ENEMY_TYPE& eType);
	void resumeAllEnemy(const E_ENEMY_TYPE& eType);
public:
	C_Enemy* getImmediateEnemy(const Vec2& pCharacterPos);
public:
	void initCursor(const E_USE_TYPE& eType);
	void moveCursor(const E_USE_TYPE& eType, const int nMove = 1);
private:
	bool init();
	void preset();
private:
	C_Enemy* m_arHead[static_cast<int>(E_USE_TYPE::E_MAX)]{};
	C_Enemy* m_arTail[static_cast<int>(E_USE_TYPE::E_MAX)]{};
	C_Enemy* m_arCursor[static_cast<int>(E_USE_TYPE::E_MAX)]{};
private:
	int m_arCountList[static_cast<int>(E_USE_TYPE::E_MAX)]{};
public:
	static C_EnemyManager* m_pInstance;
private:
	C_EnemyManager() {}
	~C_EnemyManager() {}
	C_EnemyManager(C_EnemyManager&) = delete;
	C_EnemyManager operator=(C_EnemyManager&) = delete;
};