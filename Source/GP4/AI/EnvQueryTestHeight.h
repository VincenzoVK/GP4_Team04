// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTestHeight.generated.h"

/**
 * 
 */
UCLASS()
class GP4_API UEnvQueryTestHeight : public UEnvQueryTest
{
	GENERATED_BODY()

	UEnvQueryTestHeight();

	UPROPERTY(EditDefaultsOnly, Category=Distance)
	TSubclassOf<UEnvQueryContext> CompareHeightTo;
	
	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
