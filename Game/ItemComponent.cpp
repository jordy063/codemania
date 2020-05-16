#include "MiniginPCH.h"
#include "ItemComponent.h"

comps::ItemComponent::ItemComponent(std::shared_ptr<dae::GameObject> pPlayerObject)
{
	//here we ask the components we want
	UNREFERENCED_PARAMETER(pPlayerObject);
}

void comps::ItemComponent::Initialize(const dae::Scene& scene)
{
	UNREFERENCED_PARAMETER(scene);
	//this will probably be empty
}

void comps::ItemComponent::Update(const dae::Scene& scene, float elapsedSecs, float2 pos)
{
	UNREFERENCED_PARAMETER(scene);
	UNREFERENCED_PARAMETER(elapsedSecs);
	UNREFERENCED_PARAMETER(pos);

	//check if the player overlaps with this boundingbox

	//if so we have to place a score instead of the texture

	//after that the texture has to become unactive
}
