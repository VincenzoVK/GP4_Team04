#include "Tweak.h"

#include "GP4/Utils/BlueprintUtility.h"
#include "Kismet/KismetMathLibrary.h"

ETweakResult UTweak::ApplyTweak(AActor* TweakableObject)
{
	if(UBlueprintUtility::HasTweakingType(TweakableObject, TweakTypes))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 4, FColor::White, TEXT("Fail"));
		//return ETweakResult::Fail;
	}

	float PreviousPercentage = Percentage;
	
	if(PercentageType == ETweakPercentageType::Delta)
	{
		Percentage = (Constraint.MaxPercentage - Constraint.MinPercentage) * Percentage;
		Percentage += GetCurrentPercentage(TweakableObject);
	}
	Percentage = FMath::Clamp(Percentage, Constraint.MinPercentage, Constraint.MaxPercentage);
	
	OnApplyTweak(TweakableObject);

	Percentage = PreviousPercentage;
	
	return ETweakResult::Success;
}

float UTweak::GetNormalizedCurrentPercentage(AActor* TweakableObject)
{
	return UBlueprintUtility::NormalizeToActorConstraints(GetCurrentPercentage(TweakableObject), TweakableObject, GetClass());
}
