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
	void addEnemy(C_Enemy* pEnemy, const E_USE_TYPE& eType);
	void changeEnemy(C_Enemy* pEnemy, const E_USE_TYPE& eChangeType);
	void removeEnemy(C_Enemy* pEnemy, const E_USE_TYPE& eType);
public:
	void disabledAllEnemy(const E_ENEMY_TYPE& eType);
public:
	C_Enemy* popEnemy(const E_USE_TYPE& eType);
public:
	C_Enemy* getImmediateEnemy(const Vec2& pCharacterPos);
private:
	bool init();
	void preset();
private:
	std::vector<C_Enemy*> m_arEnemyList[static_cast<int>(E_USE_TYPE::E_MAX)]{};
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