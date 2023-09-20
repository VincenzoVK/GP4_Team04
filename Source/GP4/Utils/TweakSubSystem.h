#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GP4/Interactables/Tweaks/Tweak.h"
#include "TweakSubSystem.generated.h"

/**
 * 
 */
UCLASS()
class GP4_API UTweakSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBroadcastTweak, UTweak*, Tweak);
	
public:
	UPROPERTY(BlueprintAssignable)
	FBroadcastTweak OnBroadcastTweak;
	UPROPERTY(BlueprintAssignable)
	FBroadcastTweak OnBroadcastSelfTweak;
	
	UFUNCTION(BlueprintCallable)
	void BroadcastTweak(UTweak* Tweak);
	UFUNCTION(BlueprintCallable)
	void BroadcastSelfTweak(UTweak* Tweak);
};
