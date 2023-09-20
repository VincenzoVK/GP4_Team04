// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "MyBTTask_RunTowardSensedPawn.generated.h"

/**
 * 
 */
UCLASS()
class GP4_API UMyBTTask_RunTowardSensedPawn : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
	UFUNCTION(BlueprintCallable)
	FVector FindMoveLocation(AAIController* Controller);
};
