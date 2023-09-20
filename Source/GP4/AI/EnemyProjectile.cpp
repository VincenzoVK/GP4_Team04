// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyProjectile.h"
#include "MeshDescription.h"
#include "MeshDescriptionBuilder.h"
#include "StaticMeshAttributes.h"
#include "GP4/Interactables/Tweakable.h"

// Sets default values
AEnemyProjectile::AEnemyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh", false);
	SetRootComponent(StaticMeshComponent);
	StaticMeshComponent->SetCanEverAffectNavigation(false);

	static ConstructorHelpers::FObjectFinder<UStaticMesh>SphereMeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	StaticMeshComponent->SetStaticMesh(SphereMeshAsset.Object);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent", false);
	ProjectileMovementComponent->SetUpdatedComponent(StaticMeshComponent);
	ProjectileMovementComponent->InitialSpeed = ProjectileInitialSpeed;
	ProjectileMovementComponent->MaxSpeed = ProjectileMaxSpeed;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	SetActorScale3D(FVector(1, 1,1));

	StaticMeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	StaticMeshComponent->SetUseCCD(true);
	StaticMeshComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &AEnemyProjectile::HandleProjectileHit);
}

void AEnemyProjectile::HandleProjectileHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep ,const FHitResult& SweepResult)
{
	if(OtherActor->ActorHasTag("Enemy"))
	{
		return;
	}

	if(OtherActor->Implements<UTweakable>())
	{
		HandleHitObject(OtherActor);
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Projectile Hit"));
	Destroy();
}

// Called when the game starts or when spawned
void AEnemyProjectile::BeginPlay()
{
	Super::BeginPlay();
}



// Called every frame
void AEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

