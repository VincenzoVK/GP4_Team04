// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GP4/Interactables/Tweaks/Tweak.h"
#include "BlueprintUtility.generated.h"


/**
 * 
 */
UCLASS()
class GP4_API UBlueprintUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "GP4", meta = (DeterminesOutputType = "Class", DynamicOutputParam = "OutTweak"))
	static void CreateTweak(AActor* Outer, TSubclassOf<UTweak> Class, float Percentage, UTweak*& OutTweak);

	UFUNCTION(BlueprintPure, Category = "GP4")
	static float NormalizeToActorConstraints(float X, AActor* Actor, TSubclassOf<UTweak> TweakClass);
	
	UFUNCTION(BlueprintPure, Category = "GP4")
	static USizeTweaker* CreateSizeTweak(FVector2D ScaleRange, float Percentage);

	UFUNCTION(BlueprintPure, Category = "GP4")
	static bool HasTweakingType(AActor* Tweakable, UPARAM(meta = (Bitmask, BitmaskEnum = ETweakType)) int32 Bitmask);

	UFUNCTION(BlueprintCallable, Category = "GP4")
	static void BroadcastTweak(UGameInstance* GameInstance, UTweak* Tweak);

	UFUNCTION(BlueprintCallable, Category = "GP4")
	static void BroadcastSelfTweak(UGameInstance* GameInstance, UTweak* Tweak);

	UFUNCTION(BlueprintCallable, Category = "GP4")
	static void BroadcastTweakDelta(UGameInstance* GameInstance, UTweak* Tweak, float Delta);

	UFUNCTION(BlueprintCallable, Category = "GP4")
	static void BroadcastSelfTweakDelta(UGameInstance* GameInstance, UTweak* Tweak, float Delta);

	UFUNCTION(BlueprintCallable, Category = "GP4")
	static void BroadcastTweakChange(UGameInstance* GameInstance, UTweak* Tweak, float Percentage);

	UFUNCTION(BlueprintCallable, Category = "GP4")
	static void BroadcastSelfTweakChange(UGameInstance* GameInstance, UTweak* Tweak, float Percentage);

	UFUNCTION(BlueprintCallable, Category = "GP4")
	static FVector2D GetTweakValueRange(UTweak* Tweak, AActor* Actor);
};
