#pragma once
#include "cocos2d.h"

USING_NS_CC;

enum class E_CLOUD_TYPE
{
	E_NORMAL,
	E_RANDOM,
	E_MAX
};

enum class E_SCROLL
{
	E_BG,
	E_CLOUD,
	E_MAX
};

// INFO! 이 클래스는 "싱글톤 타입 클래스"입니다.
// 따라서 하나만 생성할 수 있으며 해당 클래스의 인스턴스로 언제든지 클래스를 참조 할 수 있습니다.
// @since 2019-12-06日

class C_2DScrollView : public Node
{
public:
	// INFO! default형 생성 함수입니다.
	// 사용 되는 스크롤 맴버에 대한 초기화만 이루어져 있습니다.
	static C_2DScrollView* create();

	// INFO!	노드 생성 함수입니다. 
	// @param	"strTexture" = "파일경로 + 파일 명"
	// @param	"nTextureCount" = "스크롤 텍스쳐의 수"
	// @default "nTextureCount" = "3"
	static C_2DScrollView* create(const std::string& strTexture, const int nTextureCount = 3);

	// INFO! 노드 반환 함수입니다.
	// @return	"this_Class"
	static inline C_2DScrollView* getInstance() { return m_pInstance; }

public:
	// INFO! 클래스 내 "스크롤 및 안개" 맴버의 반환 함수입니다.
	// @param	"nPosNum" = "Array Number"
	// @param	"eType"   = "Item Type"
	// @return	"m_arItemList[TYPE][POSITION]"
	inline Sprite* getBGNode(const int nPosnum, const E_SCROLL& eType) const
	{ 
		return m_arItemList[static_cast<int>(eType)][nPosnum]; 
	}

	// INFO! 해당 스크롤에서 사용하는 "filter"맴버의 반환 함수입니다.
	// @return	"m_pFilter"
	inline Sprite* getFilter() const
	{ 
		return m_pFilter;
	}

	// INFO! 해당 스크롤에서 사용하는 카메라의 반환 함수입니다.
	// @return	"m_pCamera"
	inline Camera* getScrollCamera() const
	{ 
		return m_pCamera;
	}

	// INFO! 카메라 각도의 반환 함수입니다.
	// @return	"m_vecCameraAngle"
	inline const Vec3& getCameraAngle() const
	{ 
		return m_vecCameraAngle; 
	}

	// INFO!	"Texture"들의 재배치 좌표를 반환합니다.
	// @param	"eType" = "Texture member Type."
	// @return	"m_arUpdatepos[TYPE]"
	inline const Vec3& getUpdatePosition(const E_SCROLL& eType) const
	{ 
		return m_arUpdatepos[static_cast<int>(eType)];
	}

	// INFO!	"Texture"들의 이동 단위 좌표를 반환합니다.
	// @param	"eType" = "Texture member Type."
	// @return	"m_arMover[TYPE]"
	inline const Vec3& getMover(const E_SCROLL& eType) const
	{ 
		return m_arMover[static_cast<int>(eType)]; 
	}

	// INFO!	"Target Texture Array"의 크기를 반환합니다.
	// @param	"eType" = "Texture member Type."
	// @return	"m_arItemCount[TYPE]"
	inline const int& getBGTextureCount(const E_SCROLL& eType) const
	{ 
		return m_arItemCount[static_cast<int>(eType)];
	}

	// INFO!	"Update Function의 Delay"를 반환합니다.
	// @return	"m_fDelaytime" = "Update Function Delay"
	inline const float& getUpdateDelay() const
	{
		return m_fDelaytime;
	}

	// INFO! 현재 활성화 여부를 반환합니다.
	// @return	"m_isEnabled"
	inline const bool& isEnabled() const 
	{ 
		return m_isEnabled; 
	}

public:
	// INFO! "setCameraMask"의 "override"함수입니다.
	// 상속에 사용한 "Node"는 실질적으로 쓰이지 않으니 부모 노드의 "setCameraMask"를 이용했습니다.
	// @param	"unMaskTag"			= "기존과 동일"
	// @param	"isApplyChildren"	= "기존과 동일"
	void setCameraMask(const unsigned short unMaskTag, const bool isApplyChildren = true) override;

	// INFO! 카메라의 구도를 결정합니다.
	// @param	"fXAngle" = "X_Axis"
	// @param	"fYAngle" = "Y_Axis"
	// @param	"fZAngle" = "Z_Axis"
	void setRotateByCamera(const float fXAngle, const float fYAngle, const float fZAngle);

	// INFO! 스크롤 노드의 모든 이벤트와 객체의 활성/비활성을 결정합니다.
	// @param	"isEnabled" = "활성화 여부"
	void setEnabled(const bool isEnabled);

	// INFO!	지정 타입의 이동 속도를 정합니다.
	// @param	"fSpeed" = "이동 속도"
	// @param	"eType"  = "텍스쳐 타입"
	inline void setSpeed(const float& fSpeed, const E_SCROLL& eType)
	{
		m_arMover[static_cast<int>(eType)].set(0.0f, -fSpeed, 0.0f);
	}

	// INFO! 해당 함수에서는 구름 텍스쳐의 재배치 방식을 정합니다.
	// @param "재 사용 방식 지정"
	// @example "E_CLOUD_TYPE::NORMAL" = "지정 좌표 생성"
	// @example "E_CLOUD_TYPE::RANDOM" = "랜덤하게 생성"
	inline void setCloudSpawnType(const E_CLOUD_TYPE& eCloudType)
	{
		m_eCloudType = eCloudType;
	}

	// INFO! 해당 함수에서는 텍스쳐의 재배치 위치를 정합니다.
	// Warning! 생성타입 : "E_CLOUD"의 경우, "E_CLOUD_TYPE::NORMAL" 모드에서만 적용됩니다.
	// @param	"vecPosition" = "2D 재배치 위치"
	// @param	"eType"		  = "텍스쳐 타입"
	inline void setUpdatePosition(const Vec3& vecPosition, const E_SCROLL& eType)
	{
		m_arUpdatepos[static_cast<int>(eType)] = vecPosition;
	}

public:
	// INFO! 타입에 따른 텍스쳐를 지정한 수만큼 생성합니다.
	// 이미 생성한 뒤에는 사용이 불가하며 대신, set함수들을 이용해 주시기 바랍니다.
	// @example "createByTexture(X)", "setTextures + setItemCount(O)" // 이미 생성한 후를 가정
	// @param	"arTexture" = "파일경로 + 파일 명"
	// @param	"nTextureCount" = "사용 할 텍스쳐의 수"
	// @param	"eType" = "사용 타입"
	// @param	"fZpos" = "Z축의 높이"
	void createByTexture(const std::string& strTexture, const int nTextureCount, const E_SCROLL& eType, const float fZpos = 0.0f);
	
	// INFO! 다른 두 텍스쳐와 다르게 필수적이지 않은 부가 함수입니다.
	// 필터 스프라이트를 생성하고 값을 할당합니다.
	// @param	"arTexture" = "파일경로 + 파일 명"
	void createFilterByTexture(const std::string& strTexture);

	// INFO! 텍스쳐 생성 편의 함수입니다, "CREATE"함수에서 사용됩니다.
	// @param "pSprite" = "등록할 텍스쳐"
	// @param "nType"	= "텍스쳐 타입"
	void createItem(Sprite* pSprite, const int& nType);

	// INFO! 배경 2D 텍스쳐를 정해줍니다.
	// @warning "createWithBackground" 또는 "createBGByTexture"를 먼저 사용 후 사용하여야 합니다.
	// @param	"arRoute"	= "Texture_Route + Name"
	// @param	"eType"		= "Texture_Type"
	void setTextureByRoute(const char* arRoute, const E_SCROLL& eType);

	// INFO! 해당 함수에서는 배경 2D 텍스쳐의 갯수를 정합니다.
	// @param	"nTextureCount" = "Texture_Number"
	// @param	"eType"		  = "Texture_Type"
	void setTextureCount(const int nTextureCount, const E_SCROLL& eType);

	// INFO! 해당 함수에서는 클래스의 업데이트 호출 주기를 정할 수 있습니다.
	// Warning! 스크롤의 속도는 "setSpeed"함수를 이용하여 조정하시기 바랍니다.
	// @param	"fDelay" = "함수 호출 주기"
	void setUpdateDelay(const float& fDelay);

private:
	// WARNING! 이 함수는 한정적 초기화 맴버 함수입니다. 따라서 다시 이 함수를 사용 한들 제대로 된 초기화가 불가능합니다.
	bool init() override;
	// INFO! "setEnabled" 함수를 위한 "onEnter"의 "override" 함수입니다.
	void onEnter() override;
private:
	void preset();
	void createCamera();
private:
	void update(float fDelay) override;
private:
	std::vector<Sprite*> m_arItemList[static_cast<int>(E_SCROLL::E_MAX)]{};
	Sprite* m_pFilter;
private:
	Camera* m_pCamera;
private:
	Vec3	m_vecCameraAngle {};
	Vec3	m_arUpdatepos[static_cast<int>(E_SCROLL::E_MAX)] {};
	Vec3	m_arMover[static_cast<int>(E_SCROLL::E_MAX)]	 {};
private:
	E_CLOUD_TYPE m_eCloudType;
	CameraFlag	 m_eCameraFlag;
private:
	SEL_SCHEDULE m_selUpdateFunction;
private:
	int		m_arItemCount[static_cast<int>(E_SCROLL::E_MAX)]{};
private:
	float	m_fDelaytime;
private:
	bool	m_isNowUpdated;
	bool	m_isEnabled;
private:
	static C_2DScrollView* m_pInstance;
private:
	C_2DScrollView() {}
	virtual ~C_2DScrollView() {}
	C_2DScrollView(C_2DScrollView&)			  = delete;
	C_2DScrollView operator=(C_2DScrollView&) = delete;
};