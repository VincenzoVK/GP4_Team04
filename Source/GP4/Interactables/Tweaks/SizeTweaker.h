#pragma once

#include "CoreMinimal.h"
#include "Tweak.h"
#include "SizeTweaker.generated.h"

/**
 * 
 */
UCLASS()
class GP4_API USizeTweaker : public UTweak
{
	GENERATED_BODY()

public:
	FVector2D ScaleRange;
	
	virtual ETweakResult ApplyTweak(AActor* TweakableObject) override;
};
