#pragma once

#include "CoreMinimal.h"
#include "GP4/Interactables/TweakableObject.h"
#include "UObject/Object.h"
#include "Tweak.generated.h"

UENUM(BlueprintType)
enum class ETweakResult : uint8
{
	Fail,
	Success
};

UENUM(BlueprintType)
enum class ETweakPercentageType : uint8
{
	None,
	Delta,
	Change
};

/**
 * Base Tweak class which is responsible for applying the tweaks to the tweakable
 */
UCLASS(Blueprintable)
class GP4_API UTweak : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = ETweakType))
	int32 TweakTypes;
	UPROPERTY(BlueprintReadWrite)
	ETweakPercentageType PercentageType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Percentage;
	UPROPERTY()
	FTweakConstraint Constraint = FTweakConstraint();
	
	UFUNCTION(BlueprintCallable)
	virtual ETweakResult ApplyTweak(AActor* TweakableObject);
	UFUNCTION(BlueprintImplementableEvent)
	void OnApplyTweak(AActor* TweakableObject);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	float GetCurrentPercentage(AActor* TweakableObject);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	float GetMinValue();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	float GetMaxValue();
	UFUNCTION(BlueprintCallable)
	float GetNormalizedCurrentPercentage(AActor* TweakableObject);
	
};
