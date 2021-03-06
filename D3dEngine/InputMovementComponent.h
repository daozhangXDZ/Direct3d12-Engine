#pragma once
#include "Component.h"
class D3DENGINE_API InputMovementComponent : public Component
{
public:
	InputMovementComponent();
	~InputMovementComponent();

	// Inherited via Component
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
	XMVECTOR GetPos() const { return m_position; };
	float GetPitch() const { return m_pitch; };
	float GetYaw() const { return m_yaw; };
	bool GetIdleState() const { return isIdle; };
	bool GetRunningState() const { return m_isRunning; };
	void SetRotationAbilities(bool allowPitch, bool allowYaw) { m_canRotatePitch = allowPitch; m_canRotateYaw = allowYaw; };
	void SetCanMove(bool value) { m_canMove = value; };
private:
	float m_pitch; /// The pitch of the mouse movement
	float m_yaw; /// The yaw of the mouse movement
	DirectX::XMVECTORF32 m_direction; /// The direction the keys have been pressed to form 
	DirectX::XMVECTOR m_position; /// The position of the camera
	DirectX::XMMATRIX m_camRotationMatrix; /// The rotation matrix of the camera
	DirectX::XMVECTOR DefaultForward = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f); /// The Default forward facing vector
	DirectX::XMVECTOR DefaultRight = DirectX::XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f); /// The Default Right facing vector
	bool isJumping; /// Is camera or player jumping
	bool m_canRotatePitch;
	bool m_canRotateYaw;
	DirectX::XMVECTOR m_camTarget; /// The target that the camera will look at
	bool isIdle;
	float m_rotOffset;
	bool m_canMove; 
	bool m_isRunning;
};

