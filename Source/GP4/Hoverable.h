// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Hoverable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UHoverable : public UInterface
{
	GENERATED_BODY()
};

class GP4_API IHoverable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Hoverable")
	void OnStartHovered();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Hoverable")
	void OnStopHovered();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Hoverable")
	bool IsGOHovered();
};
