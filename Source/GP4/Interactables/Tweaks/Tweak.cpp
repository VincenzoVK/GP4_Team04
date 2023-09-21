#include "Tweak.h"

#include "GP4/Utils/BlueprintUtility.h"
#include "Kismet/KismetMathLibrary.h"

ETweakResult UTweak::ApplyTweak(AActor* TweakableObject)
{
	float PreviousPercentage = Percentage;
	
	if(PercentageType == ETweakPercentageType::Delta)
	{
		Percentage = (Constraint.MaxPercentage - Constraint.MinPercentage) * Percentage;
		Percentage += GetCurrentPercentage(TweakableObject);
	}
	Percentage = FMath::Clamp(Percentage, Constraint.MinPercentage, Constraint.MaxPercentage);

	if(!Constraint.Lock)
		OnApplyTweak(TweakableObject);

	Percentage = PreviousPercentage;
	
	return ETweakResult::Success;
}

float UTweak::GetNormalizedCurrentPercentage(AActor* TweakableObject)
{
	return UBlueprintUtility::NormalizeToActorConstraints(GetCurrentPercentage(TweakableObject), TweakableObject, GetClass());
}
