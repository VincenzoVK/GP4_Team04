// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tweakable.h"
#include "TweakConstraint.h"
#include "GameFramework/Actor.h"
#include "GP4/Hoverable.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "TweakableObject.generated.h"

class UTweak;

UENUM(BlueprintType, Meta = (Bitflags))
enum class ETweakType : uint8
{
	None = 0 UMETA(Hidden),
	Size = 1,
	Speed = 2,
	Gravity = 4
};

UCLASS()
class GP4_API ATweakableObject : public AActor, public ITweakable, public IHoverable
{
	GENERATED_BODY()

public:
	ATweakableObject();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsTweakable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = ETweakType))
	int32 TweakFlags;
	UPROPERTY(EditAnywhere)
	TMap<TSubclassOf<UTweak>, FTweakConstraint> TweakOverrides;
	UPROPERTY(BlueprintReadWrite)
	UPhysicalMaterial* PhysicalMaterial;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginDestroy() override;
	virtual void OnStartTweaking() override;
	virtual void OnEndTweaking() override;
	virtual bool CanBeTweaked() override;
	virtual int32 GetTweakFlags() override;
	UFUNCTION(BlueprintCallable)
	virtual void ReceiveTweak(UTweak* Tweak);
	UFUNCTION(BlueprintImplementableEvent)
	void OnReceiveTweak(UTweak* Tweak);
	UFUNCTION(BlueprintCallable)
	void SetFriction(float Friction);
	UFUNCTION(BlueprintCallable)
	float GetFriction();
};
