#pragma once
#include "Component.h"
#include "TerrainCollisionHelper.h"
#include "InputMovementComponent.h"
class D3DENGINE_API CameraComponent : public Component
{
public:
	CameraComponent(std::shared_ptr<InputMovementComponent> movement, float cameraGroundOffset, float camMultiplier);
	~CameraComponent();

	virtual int InitRootSignatureParameters(int indexOffset) override;
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void OnKeyDown(UINT key) override;
	virtual void OnKeyUp(UINT key) override;
	virtual void OnMouseMoved(float x, float y) override;
	virtual void OnDeviceRemoved() override;
	virtual void CreateWindowSizeDependentResources() override;
	virtual void CreateDeviceDependentResources() override;
	float m_minY;
private:
	std::shared_ptr<InputMovementComponent> m_movementComponent;


	D3D12_RECT m_scissorRect; /// Rect that anything outside of it will not be displayed

	float m_cameraGroundOffset; /// The constant offset of the camera from the ground
	bool m_isUnderGround; /// is the camera underground 
	float m_camMultiplier;
};

