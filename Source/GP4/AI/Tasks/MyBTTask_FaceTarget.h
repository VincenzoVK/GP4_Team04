// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "MyBTTask_FaceTarget.generated.h"

/**
 * 
 */
UCLASS()
class GP4_API UMyBTTask_FaceTarget : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	void LookAtTarget(AAIController* Controller, APawn* ControlledPawn);
};
