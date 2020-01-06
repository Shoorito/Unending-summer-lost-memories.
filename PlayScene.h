#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class C_PlayScene : public Layer
{
public:
	static C_PlayScene* create();
	inline static C_PlayScene* getInstance() { return m_pInstance; }
public:
	inline const Rect& getWinArea() { return m_recWinArea; }
private:
	bool init();
	void preset();
private:
	Rect m_recWinArea;
private:
	static C_PlayScene* m_pInstance;
private:
	C_PlayScene() {}
 	virtual ~C_PlayScene() {}
	C_PlayScene(C_PlayScene&)			= delete;
	C_PlayScene operator=(C_PlayScene&) = delete;
};