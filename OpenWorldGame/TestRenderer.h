#pragma once
#include "Renderer.h"
#include "Node.h"
class TestRenderer : public Renderer
{
public:
	TestRenderer();
	~TestRenderer();

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
private:
	std::shared_ptr<Node> m_playerNode;
	std::vector<std::shared_ptr<Node>> m_otherNode;
	std::vector<std::shared_ptr<Node>> m_trees;
	std::shared_ptr<Node> m_cameraNode;
	std::shared_ptr<Node> m_terrainNode;

};

