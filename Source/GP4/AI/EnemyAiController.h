// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyAiController.generated.h"

/**
 * 
 */
UCLASS()
class GP4_API AEnemyAiController : public AAIController
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	void HandleSightSense(AActor* SensedActor, FAIStimulus Stimulus);
	
};
