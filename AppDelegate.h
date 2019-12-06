#pragma once
#include "cocos2d.h"

USING_NS_CC;

enum class E_OS
{
	E_UNKNOWN,
	E_IOS,
	E_ANDROID,
	E_WIN32,
	E_MARMALADE,
	E_LINUX,
	E_BADA,
	E_BLACKBERRY,
	E_MAC,
	E_NACL,
	E_EMSCRIPTEN,
	E_TIZEN,
	E_QT5,          
	E_WINRT,
	E_MAX
};

class AppDelegate : private Application
{
public:
    AppDelegate();
	AppDelegate(const float fWidth, const float fHeight, const std::string& strTitle);
    virtual ~AppDelegate();
public:
    virtual void initGLContextAttrs();

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  Called when the application moves to the background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  Called when the application reenters the foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();
private:
	const bool checkSupportOS() const;
private:
	Rect m_recWinSize;
private:
	std::string m_strTitle;
};
