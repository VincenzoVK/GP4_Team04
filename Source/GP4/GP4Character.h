// Copyright Epic Games, Inc. All Rights Reserved.
//linetracefunction(checks if it has hoverable interface and returns if it has, otherwise null ptr)
//isaiming var move it to here and expose it to bp for vinnie to use
//call the linetracefunction (if isaiming) in tick
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Interactables/Tweakable.h"
#include "Interactables/Tweaks/Tweak.h"
#include "GP4Character.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCheckSizeChanged);
class ACheckPoint;

UCLASS(config=Game)
class AGP4Character : public ACharacter, public ITweakable
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

public:
	AGP4Character();
	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "TweakableInputs")
	bool TrySelect();
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere)
	TMap<TSubclassOf<UTweak>, FTweakConstraint> TweakOverrides;
	UPROPERTY(BlueprintReadOnly)
	TArray<AActor*> SelectedActors;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsAiming;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsSelectPressed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool IsMultiSelectPressed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool StartFromCheckPoint = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int StartCheckPoint = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = ETweakType))
	int32 TweakFlags;
	UPROPERTY(BlueprintReadWrite)
	ACheckPoint* CurrentCheckPoint;
	UPROPERTY(BlueprintReadWrite)
	ACheckPoint* PreviousCheckPoint;
	UPROPERTY(BlueprintReadOnly)
	TArray<AActor*> ActorsInBoxTrace;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FVector BoxHalfSize = FVector(1100.f, 2000.f, 500.f);
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BoxCheckDistance = 1100.f;
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	UFUNCTION(BlueprintCallable)
	void CheckHoverable();
	bool ContainsActor(TArray<FHitResult> HitResults, AActor* Actor);
	void EmptyHoverables();

	virtual void OnStartTweaking() override;
	virtual void OnEndTweaking() override;
	virtual int32 GetTweakFlags() override;
	UFUNCTION(BlueprintCallable)
	virtual void ReceiveTweak(UTweak* Tweak);

	UFUNCTION(BlueprintCallable)
	ACheckPoint* GetCheckPointByIndex(int index);

	UPROPERTY(BlueprintAssignable)
	FCheckSizeChanged OnCheckSizeChanged;
	
};





