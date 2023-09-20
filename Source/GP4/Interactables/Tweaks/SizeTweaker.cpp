#include "SizeTweaker.h"

#include "GP4/Utils/BlueprintUtility.h"

ETweakResult USizeTweaker::ApplyTweak(AActor* TweakableObject)
{
	if(UBlueprintUtility::HasTweakingType(TweakableObject, TweakTypes))
	{
		return ETweakResult::Fail;
	}

	TweakableObject->SetActorScale3D(FVector::One() * FMath::Lerp(ScaleRange.X, ScaleRange.Y, Percentage));
	OnApplyTweak(TweakableObject);
	return ETweakResult::Success;
}
