#pragma once

#include "CoreMinimal.h"
#include "TweakConstraint.generated.h"

USTRUCT(BlueprintType)
struct FTweakConstraint
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Lock;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinPercentage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxPercentage;

	FTweakConstraint()
	{
		Lock = false;
		MinPercentage = 0;
		MaxPercentage = 1;
	}
};
