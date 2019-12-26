#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class C_PlayerState
{
public:
	static C_PlayerState* create();
	static inline C_PlayerState* getInstance() { return m_pInstance; }
public:
	void setMaxHP(const float fHP);
	void setMaxMP(const float fMP);
	void setMaxEXP(const float fEXP);
public:
	void setHP(const float fHP);
	void setMP(const float fMP);
	void setEXP(const float fEXP);
	void setScore(const int nScore);
	void setHighScore(const int nScore);
public:
	void addHP(const float fAdder);
	void addMP(const float fAdder);
	void addEXP(const float fAdder);
	void addScore(const int nAdder);
public:
	inline const float& getMaxHP() const  { return m_fPlayerMaxHP; }
	inline const float& getMaxMP() const  { return m_fPlayerMaxMP; }
	inline const float& getMaxEXP() const { return m_fPlayerMaxEXP; }
public:
	inline const int& getScore()	 const { return m_nScore; }
	inline const int& getHighScore() const { return m_nHighScore; }
private:
	void init();
private:
	float m_fPlayerHP;
	float m_fPlayerMP;
	float m_fPlayerEXP;
private:
	float m_fPlayerMaxHP;
	float m_fPlayerMaxMP;
	float m_fPlayerMaxEXP;
private:
	int m_nScore;
	int m_nHighScore;
private:
	static C_PlayerState* m_pInstance;
private:
	C_PlayerState() {}
	virtual ~C_PlayerState() {}
	C_PlayerState(C_PlayerState&)			= delete;
	C_PlayerState operator=(C_PlayerState&) = delete;
};