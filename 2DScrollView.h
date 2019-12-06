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

// INFO! �� Ŭ������ "�̱��� Ÿ�� Ŭ����"�Դϴ�.
// ���� �ϳ��� ������ �� ������ �ش� Ŭ������ �ν��Ͻ��� �������� Ŭ������ ���� �� �� �ֽ��ϴ�.
// @since 2019-12-06��

class C_2DScrollView : public Node
{
public:
	// INFO! default�� ���� �Լ��Դϴ�.
	// ��� �Ǵ� ��ũ�� �ɹ��� ���� �ʱ�ȭ�� �̷���� �ֽ��ϴ�.
	static C_2DScrollView* create();

	// INFO!	��� ���� �Լ��Դϴ�. 
	// @param	"strTexture" = "���ϰ�� + ���� ��"
	// @param	"nTextureCount" = "��ũ�� �ؽ����� ��"
	// @default "nTextureCount" = "3"
	static C_2DScrollView* create(const std::string& strTexture, const int nTextureCount = 3);

	// INFO! ��� ��ȯ �Լ��Դϴ�.
	// @return	"this_Class"
	static inline C_2DScrollView* getInstance() { return m_pInstance; }

public:
	// INFO! Ŭ���� �� "��ũ�� �� �Ȱ�" �ɹ��� ��ȯ �Լ��Դϴ�.
	// @param	"nPosNum" = "Array Number"
	// @param	"eType"   = "Item Type"
	// @return	"m_arItemList[TYPE][POSITION]"
	inline Sprite* getBGNode(const int nPosnum, const E_SCROLL& eType) const
	{ 
		return m_arItemList[static_cast<int>(eType)][nPosnum]; 
	}

	// INFO! �ش� ��ũ�ѿ��� ����ϴ� "filter"�ɹ��� ��ȯ �Լ��Դϴ�.
	// @return	"m_pFilter"
	inline Sprite* getFilter() const
	{ 
		return m_pFilter;
	}

	// INFO! �ش� ��ũ�ѿ��� ����ϴ� ī�޶��� ��ȯ �Լ��Դϴ�.
	// @return	"m_pCamera"
	inline Camera* getScrollCamera() const
	{ 
		return m_pCamera;
	}

	// INFO! ī�޶� ������ ��ȯ �Լ��Դϴ�.
	// @return	"m_vecCameraAngle"
	inline const Vec3& getCameraAngle() const
	{ 
		return m_vecCameraAngle; 
	}

	// INFO!	"Texture"���� ���ġ ��ǥ�� ��ȯ�մϴ�.
	// @param	"eType" = "Texture member Type."
	// @return	"m_arUpdatepos[TYPE]"
	inline const Vec3& getUpdatePosition(const E_SCROLL& eType) const
	{ 
		return m_arUpdatepos[static_cast<int>(eType)];
	}

	// INFO!	"Texture"���� �̵� ���� ��ǥ�� ��ȯ�մϴ�.
	// @param	"eType" = "Texture member Type."
	// @return	"m_arMover[TYPE]"
	inline const Vec3& getMover(const E_SCROLL& eType) const
	{ 
		return m_arMover[static_cast<int>(eType)]; 
	}

	// INFO!	"Target Texture Array"�� ũ�⸦ ��ȯ�մϴ�.
	// @param	"eType" = "Texture member Type."
	// @return	"m_arItemCount[TYPE]"
	inline const int& getBGTextureCount(const E_SCROLL& eType) const
	{ 
		return m_arItemCount[static_cast<int>(eType)];
	}

	// INFO!	"Update Function�� Delay"�� ��ȯ�մϴ�.
	// @return	"m_fDelaytime" = "Update Function Delay"
	inline const float& getUpdateDelay() const
	{
		return m_fDelaytime;
	}

	// INFO! ���� Ȱ��ȭ ���θ� ��ȯ�մϴ�.
	// @return	"m_isEnabled"
	inline const bool& isEnabled() const 
	{ 
		return m_isEnabled; 
	}

public:
	// INFO! "setCameraMask"�� "override"�Լ��Դϴ�.
	// ��ӿ� ����� "Node"�� ���������� ������ ������ �θ� ����� "setCameraMask"�� �̿��߽��ϴ�.
	// @param	"unMaskTag"			= "������ ����"
	// @param	"isApplyChildren"	= "������ ����"
	void setCameraMask(const unsigned short unMaskTag, const bool isApplyChildren = true) override;

	// INFO! ī�޶��� ������ �����մϴ�.
	// @param	"fXAngle" = "X_Axis"
	// @param	"fYAngle" = "Y_Axis"
	// @param	"fZAngle" = "Z_Axis"
	void setRotateByCamera(const float fXAngle, const float fYAngle, const float fZAngle);

	// INFO! ��ũ�� ����� ��� �̺�Ʈ�� ��ü�� Ȱ��/��Ȱ���� �����մϴ�.
	// @param	"isEnabled" = "Ȱ��ȭ ����"
	void setEnabled(const bool isEnabled);

	// INFO!	���� Ÿ���� �̵� �ӵ��� ���մϴ�.
	// @param	"fSpeed" = "�̵� �ӵ�"
	// @param	"eType"  = "�ؽ��� Ÿ��"
	inline void setSpeed(const float& fSpeed, const E_SCROLL& eType)
	{
		m_arMover[static_cast<int>(eType)].set(0.0f, -fSpeed, 0.0f);
	}

	// INFO! �ش� �Լ������� ���� �ؽ����� ���ġ ����� ���մϴ�.
	// @param "�� ��� ��� ����"
	// @example "E_CLOUD_TYPE::NORMAL" = "���� ��ǥ ����"
	// @example "E_CLOUD_TYPE::RANDOM" = "�����ϰ� ����"
	inline void setCloudSpawnType(const E_CLOUD_TYPE& eCloudType)
	{
		m_eCloudType = eCloudType;
	}

	// INFO! �ش� �Լ������� �ؽ����� ���ġ ��ġ�� ���մϴ�.
	// Warning! ����Ÿ�� : "E_CLOUD"�� ���, "E_CLOUD_TYPE::NORMAL" ��忡���� ����˴ϴ�.
	// @param	"vecPosition" = "2D ���ġ ��ġ"
	// @param	"eType"		  = "�ؽ��� Ÿ��"
	inline void setUpdatePosition(const Vec3& vecPosition, const E_SCROLL& eType)
	{
		m_arUpdatepos[static_cast<int>(eType)] = vecPosition;
	}

public:
	// INFO! Ÿ�Կ� ���� �ؽ��ĸ� ������ ����ŭ �����մϴ�.
	// �̹� ������ �ڿ��� ����� �Ұ��ϸ� ���, set�Լ����� �̿��� �ֽñ� �ٶ��ϴ�.
	// @example "createByTexture(X)", "setTextures + setItemCount(O)" // �̹� ������ �ĸ� ����
	// @param	"arTexture" = "���ϰ�� + ���� ��"
	// @param	"nTextureCount" = "��� �� �ؽ����� ��"
	// @param	"eType" = "��� Ÿ��"
	// @param	"fZpos" = "Z���� ����"
	void createByTexture(const std::string& strTexture, const int nTextureCount, const E_SCROLL& eType, const float fZpos = 0.0f);
	
	// INFO! �ٸ� �� �ؽ��Ŀ� �ٸ��� �ʼ������� ���� �ΰ� �Լ��Դϴ�.
	// ���� ��������Ʈ�� �����ϰ� ���� �Ҵ��մϴ�.
	// @param	"arTexture" = "���ϰ�� + ���� ��"
	void createFilterByTexture(const std::string& strTexture);

	// INFO! �ؽ��� ���� ���� �Լ��Դϴ�, "CREATE"�Լ����� ���˴ϴ�.
	// @param "pSprite" = "����� �ؽ���"
	// @param "nType"	= "�ؽ��� Ÿ��"
	void createItem(Sprite* pSprite, const int& nType);

	// INFO! ��� 2D �ؽ��ĸ� �����ݴϴ�.
	// @warning "createWithBackground" �Ǵ� "createBGByTexture"�� ���� ��� �� ����Ͽ��� �մϴ�.
	// @param	"arRoute"	= "Texture_Route + Name"
	// @param	"eType"		= "Texture_Type"
	void setTextureByRoute(const char* arRoute, const E_SCROLL& eType);

	// INFO! �ش� �Լ������� ��� 2D �ؽ����� ������ ���մϴ�.
	// @param	"nTextureCount" = "Texture_Number"
	// @param	"eType"		  = "Texture_Type"
	void setTextureCount(const int nTextureCount, const E_SCROLL& eType);

	// INFO! �ش� �Լ������� Ŭ������ ������Ʈ ȣ�� �ֱ⸦ ���� �� �ֽ��ϴ�.
	// Warning! ��ũ���� �ӵ��� "setSpeed"�Լ��� �̿��Ͽ� �����Ͻñ� �ٶ��ϴ�.
	// @param	"fDelay" = "�Լ� ȣ�� �ֱ�"
	void setUpdateDelay(const float& fDelay);

private:
	// WARNING! �� �Լ��� ������ �ʱ�ȭ �ɹ� �Լ��Դϴ�. ���� �ٽ� �� �Լ��� ��� �ѵ� ����� �� �ʱ�ȭ�� �Ұ����մϴ�.
	bool init() override;
	// INFO! "setEnabled" �Լ��� ���� "onEnter"�� "override" �Լ��Դϴ�.
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