
#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DialougeSubSystem.generated.h"

UCLASS()
class GP4_API UDialougeSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStopSound);

public:
	UPROPERTY(BlueprintAssignable)
	FStopSound OnStopSound;

	UFUNCTION(BlueprintCallable)
	void BroadcastStopSound();
};
