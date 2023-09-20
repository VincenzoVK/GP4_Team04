// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GP4/Interactables/Tweakable.h"
#include "TweakAbility.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GP4_API UTweakAbility : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTweakAbility();

	UPROPERTY(BlueprintReadOnly)
	TArray<AActor*> SelectedTweakables;
	UPROPERTY(BlueprintReadOnly)
	bool SelfSelected;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Select(AActor* Tweakable);
	UFUNCTION(BlueprintCallable)
	void SelectOnly(AActor* Tweakable);
	UFUNCTION(BlueprintCallable)
	void SelectSelf();
	UFUNCTION(BlueprintCallable)
	void EndSelection();
	UFUNCTION(BlueprintCallable)
	void DeSelectActor(AActor* Tweakable);
	UFUNCTION(BlueprintCallable)
	void EndSelfSelection();
};
