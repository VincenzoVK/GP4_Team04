// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "RunFromSensedPawn.generated.h"

/**
 * 
 */
UCLASS()
class GP4_API URunFromSensedPawn : public UBTTask_BlackboardBase
{
	GENERATED_BODY()


	UFUNCTION(BlueprintCallable)
	FVector FindEscapeLocation();
};
