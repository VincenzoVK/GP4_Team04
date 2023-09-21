// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "EnemyProjectile.generated.h"

UCLASS()
class GP4_API AEnemyProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyProjectile();

	UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;


	inline static float ProjectileInitialSpeed = 2500.0f;

	inline static float ProjectileMaxSpeed = 2500.0f;

	UFUNCTION()
	void HandleProjectileHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep ,const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent)
	void HandleHitObject(AActor* HitActor);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
