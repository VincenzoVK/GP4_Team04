#include "BlueprintUtility.h"

#include "TweakSubSystem.h"
#include "GP4/GP4Character.h"
#include "GP4/Interactables/Tweaks/SizeTweaker.h"
#include "Kismet/KismetMathLibrary.h"

void UBlueprintUtility::CreateTweak(AActor* Outer, TSubclassOf<UTweak> Class, float Percentage, UTweak*& OutTweak)
{
	UTweak* Tweak = NewObject<UTweak>(Outer, Class);
	Tweak->Percentage = Percentage;

	OutTweak = Tweak;
}

float UBlueprintUtility::NormalizeToActorConstraints(float X, AActor* Actor, TSubclassOf<UTweak> TweakClass)
{
	ATweakableObject* TweakableObject = Cast<ATweakableObject>(Actor);
	if(TweakableObject)
	{
		if(TweakableObject->TweakOverrides.Contains(TweakClass))
		{
			const FTweakConstraint Constraint = TweakableObject->TweakOverrides[TweakClass];
			return UKismetMathLibrary::NormalizeToRange(X, Constraint.MinPercentage, Constraint.MaxPercentage);
		}
	}

	AGP4Character* Character = Cast<AGP4Character>(Actor);
	if(Character)
	{
		if(Character->TweakOverrides.Contains(TweakClass))
		{
			const FTweakConstraint Constraint = Character->TweakOverrides[TweakClass];
			return UKismetMathLibrary::NormalizeToRange(X, Constraint.MinPercentage, Constraint.MaxPercentage);
		}
	}

	return X;
}

USizeTweaker* UBlueprintUtility::CreateSizeTweak(FVector2D ScaleRange, float Percentage)
{
	USizeTweaker* Tweaker = NewObject<USizeTweaker>(USizeTweaker::StaticClass());
	Tweaker->ScaleRange = ScaleRange;
	Tweaker->Percentage = Percentage;

	Tweaker->TweakTypes = static_cast<int32>(ETweakType::Size);
	return Tweaker;
}

bool UBlueprintUtility::HasTweakingType(AActor* Tweakable, int32 Bitmask)
{
	ITweakable* TweakableActor = Cast<ITweakable>(Tweakable);
	if(TweakableActor)
	{
		return (Bitmask & TweakableActor->GetTweakFlags()) == Bitmask;
	}
	return false;
}

void UBlueprintUtility::BroadcastTweak(UGameInstance* GameInstance, UTweak* Tweak)
{
	UTweakSubSystem* TweakSubSystem = GameInstance->GetSubsystem<UTweakSubSystem>();
	if(TweakSubSystem)
	{
		Tweak->PercentageType = ETweakPercentageType::None;
		TweakSubSystem->BroadcastTweak(Tweak);
	}
}

void UBlueprintUtility::BroadcastSelfTweak(UGameInstance* GameInstance, UTweak* Tweak)
{
	UTweakSubSystem* TweakSubSystem = GameInstance->GetSubsystem<UTweakSubSystem>();
	if(TweakSubSystem)
	{
		Tweak->PercentageType = ETweakPercentageType::None;
		TweakSubSystem->BroadcastSelfTweak(Tweak);
	}
}

void UBlueprintUtility::BroadcastTweakDelta(UGameInstance* GameInstance, UTweak* Tweak, float Delta)
{
	UTweakSubSystem* TweakSubSystem = GameInstance->GetSubsystem<UTweakSubSystem>();
	if(TweakSubSystem)
	{
		Tweak->Percentage = Delta;
		Tweak->PercentageType = ETweakPercentageType::Delta;
		TweakSubSystem->BroadcastTweak(Tweak);
	}
}

void UBlueprintUtility::BroadcastSelfTweakDelta(UGameInstance* GameInstance, UTweak* Tweak, float Delta)
{
	UTweakSubSystem* TweakSubSystem = GameInstance->GetSubsystem<UTweakSubSystem>();
	if(TweakSubSystem)
	{
		Tweak->Percentage = Delta;
		Tweak->PercentageType = ETweakPercentageType::Delta;
		TweakSubSystem->BroadcastSelfTweak(Tweak);
	}
}

void UBlueprintUtility::BroadcastTweakChange(UGameInstance* GameInstance, UTweak* Tweak, float Percentage)
{
	UTweakSubSystem* TweakSubSystem = GameInstance->GetSubsystem<UTweakSubSystem>();
	if(TweakSubSystem)
	{
		Percentage = FMath::Clamp(Percentage, 0.f, 1.f);
		Tweak->Percentage = Percentage;
		Tweak->PercentageType = ETweakPercentageType::Change;
		TweakSubSystem->BroadcastTweak(Tweak);
	}
}

void UBlueprintUtility::BroadcastSelfTweakChange(UGameInstance* GameInstance, UTweak* Tweak, float Percentage)
{
	UTweakSubSystem* TweakSubSystem = GameInstance->GetSubsystem<UTweakSubSystem>();
	if(TweakSubSystem)
	{
		Percentage = FMath::Clamp(Percentage, 0.f, 1.f);
		Tweak->Percentage = Percentage;
		Tweak->PercentageType = ETweakPercentageType::Change;
		TweakSubSystem->BroadcastSelfTweak(Tweak);
	}
}

FVector2D UBlueprintUtility::GetTweakValueRange(UTweak* Tweak, AActor* Actor)
{
	TSubclassOf<UTweak> Class = Tweak->GetClass();
	FVector2D Base = FVector2D(Tweak->GetMinValue(), Tweak->GetMaxValue());
	
	ATweakableObject* TweakableObject = Cast<ATweakableObject>(Actor);
	if(TweakableObject)
	{
		if(TweakableObject->TweakOverrides.Contains(Class))
		{
			const FTweakConstraint Constraint = TweakableObject->TweakOverrides[Class];
			return FVector2D(FMath::Lerp(Base.X, Base.Y, Constraint.MinPercentage), FMath::Lerp(Base.X, Base.Y, Constraint.MaxPercentage));
		}
	}

	AGP4Character* Character = Cast<AGP4Character>(Actor);
	if(Character)
	{
		if(Character->TweakOverrides.Contains(Class))
		{
			const FTweakConstraint Constraint = Character->TweakOverrides[Class];
			return FVector2D(FMath::Lerp(Base.X, Base.Y, Constraint.MinPercentage), FMath::Lerp(Base.X, Base.Y, Constraint.MaxPercentage));
		}
	}

	return Base;
}
