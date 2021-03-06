#include "PlayerNode.h"
#include "AttackComponent.h"
#include "PlayerAnimationControllerComponent.h"
#include "PathFinderComponent.h"
PlayerNode::PlayerNode() : Node()
{
	//player
	auto pathManager = PathManager();
	auto playerMesh = std::make_shared<SkeletalMeshComponent>(pathManager.GetAssetPathStr() + std::string("Character.coxl"));
	playerMesh->UseTexture(L"Character.png");
	AddComponent(playerMesh);


	auto physicsComponent = std::make_shared<PhysicsComponent>();
	AddComponent(physicsComponent);

	auto cylinderCollider = std::make_shared<CylinderCollider>();
	AddComponent(cylinderCollider);
	auto playerCylinderCollider = Structures::BoundingCylinder({ 0,0,0 }, 3.f, 3);
	cylinderCollider->InitCollider(playerCylinderCollider);

	auto boxCollider = std::make_shared<BoxCollider>();
	AddComponent(boxCollider);
	auto playerCollider = BoundingBox({ 0,0.f,0 }, { 0,8.5f,0 });
	boxCollider->InitCollider(playerCollider);


	auto movementComp = std::make_shared<InputMovementComponent>();
	AddComponent(movementComp);

	auto terrainCollisionComponent = std::make_shared<TerrainCollisionComponent>();
	AddComponent(terrainCollisionComponent);

	auto lifeComponent = std::make_shared<LifeComponent>();
	AddComponent(lifeComponent);

	auto animController = std::make_shared<PlayerAnimationControllerComponent>();
	AddComponent(animController);
}

PlayerNode::~PlayerNode()
{
}

int PlayerNode::InitRootSignatureParameters(int indexOffset)
{
	return Node::InitRootSignatureParameters(indexOffset);
}

void PlayerNode::Init()
{

	Node::Init();
}

void PlayerNode::Update()
{
	PathFinderComponent::SetPlayerTransform(*m_transform);
	TerrainComponent::m_playerPos = m_transform->position;
	Node::Update();
}

void PlayerNode::Render()
{
	Node::Render();
}

void PlayerNode::OnKeyDown(UINT key)
{
	Node::OnKeyDown(key);
}

void PlayerNode::OnKeyUp(UINT key)
{
	Node::OnKeyUp(key);
}

void PlayerNode::OnMouseMoved(float x, float y)
{
	Node::OnMouseMoved(x, y);
}

void PlayerNode::OnDeviceRemoved()
{
	Node::OnDeviceRemoved();
}

void PlayerNode::CreateWindowSizeDependentResources()
{
	Node::CreateWindowSizeDependentResources();
}

void PlayerNode::CreateDeviceDependentResources()
{
	Node::CreateDeviceDependentResources();
}
