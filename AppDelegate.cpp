#include "AppDelegate.h"
#include "PlayScene.h"

AppDelegate::AppDelegate()
	: m_recWinSize(Rect::ZERO), m_strTitle()
{
	m_recWinSize.setRect(0.0f, 0.0f, Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height);
}

AppDelegate::AppDelegate(const float fWidth, const float fHeight, const std::string& strTitle)
	: m_recWinSize(Rect::ZERO), m_strTitle()
{
	m_recWinSize.setRect(0.0f, 0.0f, fWidth, fHeight);
	m_strTitle = strTitle;
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching()
{
	Director* pDirector(Director::getInstance());
	GLView*   pGLView(pDirector->getOpenGLView());
	Scene*	  pMainScene(nullptr);

    if(!pGLView)
	{
		if(checkSupportOS())
			pGLView = GLViewImpl::createWithRect(m_strTitle, m_recWinSize);
		else
			pGLView = GLViewImpl::create(m_strTitle);

        pDirector->setOpenGLView(pGLView);
    }

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0f / 1000.0f);

    // Set the design resolution
    pGLView->setDesignResolutionSize(m_recWinSize.size.width, m_recWinSize.size.height, ResolutionPolicy::NO_BORDER);

    register_all_packages();

    // create a scene. it's an autorelease object
    pMainScene = C_PlayScene::create();

    // run
    pDirector->runWithScene(pMainScene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}

// only Used: C++
const bool AppDelegate::checkSupportOS() const
{
	return CC_TARGET_PLATFORM < static_cast<int>(E_OS::E_MAX);
}
