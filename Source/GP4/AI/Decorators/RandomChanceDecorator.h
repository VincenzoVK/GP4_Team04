// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "RandomChanceDecorator.generated.h"

/**
 * 
 */
UCLASS()
class GP4_API URandomChanceDecorator : public UBTDecorator
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta=(UIMin = "0.0", UIMax = "100.0"))
	float SuccessChance =  50.0f;


	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
