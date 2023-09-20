#pragma once

#include "CoreMinimal.h"
#include "TweakConstraint.generated.h"

USTRUCT(BlueprintType)
struct FTweakConstraint
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinPercentage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxPercentage;

	FTweakConstraint()
	{
		MinPercentage = 0;
		MaxPercentage = 1;
	}
};
