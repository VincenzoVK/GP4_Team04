// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GP4PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GP4_API AGP4PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isUsingGamepad;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void DetectGamepad();
	
};
