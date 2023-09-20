// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyProjectile.h"
#include "GameFramework/Character.h"
#include "GP4/Interactables/Tweakable.h"
#include "GP4/Interactables/Tweaks/Tweak.h"
#include "WebBrowser/Private/CEF/CEFBrowserByteResource.h"
#include "EnemyBaseCharacter.generated.h"

UENUM(BlueprintType)
enum class EEnemySizeState : uint8
{
	Small,
	Medium,
	Big
};

UCLASS()
class GP4_API AEnemyBaseCharacter : public ACharacter, public ITweakable
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyBaseCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AEnemyProjectile>> ProjectileActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EEnemySizeState CurrentSize = EEnemySizeState::Medium;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsBTActive = true;

	UFUNCTION(BlueprintCallable)
	void ReceiveTweak(UTweak* Tweak);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = ETweakType))
	int32 TweakFlags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SmallSizeWalkSpeed = 450.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MediumSizeWalkSpeed = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BigSizeWalkSpeed = 350.0f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnStartTweaking() override;
	virtual void OnEndTweaking() override;
	virtual int32 GetTweakFlags() override;

	UFUNCTION(BlueprintCallable)
	void FindShootDirection(AActor* ProjectileTarget);

	UFUNCTION(BlueprintImplementableEvent)
	void OnShootProjectile(FTransform ProjectileTransform, TSubclassOf<AEnemyProjectile> ProjectileClass);
	
	UFUNCTION(BlueprintCallable)
	void CheckSize();

	UFUNCTION(BlueprintImplementableEvent)
	void OnChangeSize();
	
};
