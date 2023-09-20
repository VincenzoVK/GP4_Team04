#include "GravityComponent.h"

UGravityComponent::UGravityComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UGravityComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UGravityComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UStaticMeshComponent* Mesh = GetOwner()->GetComponentByClass<UStaticMeshComponent>();
	Mesh->AddForce(FVector::DownVector * (981.f * GravityScale) * Mass);
}

