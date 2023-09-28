// Copyright Epic Games, Inc. All Rights Reserved.

#include "GP4Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GP4_GameInstance.h"
#include "Hoverable.h"
#include "Interactables/CheckPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Player/TweakAbility.h"
#include "Utils/TweakSubSystem.h"


//////////////////////////////////////////////////////////////////////////
// AGP4Character

AGP4Character::AGP4Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	IsMultiSelectPressed = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	//BoxHalfSize = FVector(1100.0f, 2000.0f, 500.0f);
	//BoxCheckDistance = 1100.f;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AGP4Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	UGP4_GameInstance* GameInstance = Cast<UGP4_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance && GameInstance->LoadGame())
	{
		if(GameInstance->CurrentSaveGame)
		{
			int Index = GameInstance->CurrentSaveGame->RoomIndex;
			if(StartCheckPoint != -1)
				Index = StartCheckPoint;

			CurrentCheckPoint = GetCheckPointByIndex(Index);
			if(StartFromCheckPoint)
			{
				CurrentCheckPoint->LoadLevel(this);
				SetActorLocation(CurrentCheckPoint->GetActorLocation());
				SetActorRotation(CurrentCheckPoint->GetActorRotation());
			}
		}
	}
}

void AGP4Character::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (IsAiming)
	{
		CheckHoverable();
	}
	else
	{
		// If not aiming, stop hovering the currently hovered actor
		EmptyHoverables();
	}
}

ACheckPoint* AGP4Character::GetCheckPointByIndex(int index)
{
	TArray<AActor*> CheckPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACheckPoint::StaticClass(), CheckPoints);

	for (AActor* Actor : CheckPoints)
	{
		ACheckPoint* CheckPoint = Cast<ACheckPoint>(Actor);
		if(CheckPoint->Index == index)
			return CheckPoint;
	}

	return nullptr;
}


void AGP4Character::CheckHoverable()
{
	// Get the player controller
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!PlayerController)
	{
		return;
	}

	// Get the player's viewpoint
	FVector StartLocation;
	FRotator ViewRotation;
	PlayerController->GetPlayerViewPoint(StartLocation, ViewRotation);

	// Calculate the end location for the line trace
	FVector EndLocation = StartLocation + (ViewRotation.Vector() * BoxCheckDistance); //TODO: Adjust

	// Setup trace parameters
	TArray<FHitResult> HitResults;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this); // Ignore the character itself

	FQuat Orientation = FRotator(0, 0, 0).Quaternion();
	FCollisionShape CollisionShape = FCollisionShape::MakeBox(BoxHalfSize);

	//DrawDebugBox(GetWorld(), EndLocation, BoxHalfSize, ViewRotation.Quaternion(), FColor::Red);
	// Perform the line trace
	if (GetWorld()->SweepMultiByChannel(HitResults, EndLocation, EndLocation, ViewRotation.Quaternion(), ECC_Visibility,
	                                    CollisionShape, CollisionParams))
	{
		for (const FHitResult& Hit : HitResults)
		{
			// Check if the hit actor implements the interactable interface
			AActor* HitActor = Hit.GetActor();
			if (HitActor && HitActor->GetClass()->ImplementsInterface(UHoverable::StaticClass()))
			{
				ActorsInBoxTrace.AddUnique(HitActor);
				if (HitActor)
				{
					IHoverable::Execute_OnStartHovered(HitActor);
				}
			}
		}
	}

	TArray<AActor*> ActorsNoLongerInBoxTrace;

	for (AActor* CurrentHovered : ActorsInBoxTrace)
	{
		if (!ContainsActor(HitResults, CurrentHovered))
		{
			ActorsNoLongerInBoxTrace.Add(CurrentHovered);
			IHoverable::Execute_OnStopHovered(CurrentHovered);
		}
	}
	for (auto Actor : ActorsNoLongerInBoxTrace)
	{
		ActorsInBoxTrace.Remove(Actor);
	}
}

bool AGP4Character::ContainsActor(TArray<FHitResult> HitResults, AActor* Actor)
{
	for (auto HitResult : HitResults)
	{
		if (HitResult.GetActor() == Actor)
		{
			return true;
		}
	}
	return false;
}

void AGP4Character::EmptyHoverables()
{
	if (ActorsInBoxTrace.IsEmpty()) return;

	for (auto Actor : ActorsInBoxTrace)
	{
		IHoverable::Execute_OnStopHovered(Actor);
	}

	ActorsInBoxTrace.Empty();
}

void AGP4Character::OnStartTweaking()
{
	ITweakable::OnStartTweaking();

	UTweakSubSystem* TweakSubSystem = GetGameInstance()->GetSubsystem<UTweakSubSystem>();
	if (TweakSubSystem)
	{
		TweakSubSystem->OnBroadcastSelfTweak.AddUniqueDynamic(this, &AGP4Character::ReceiveTweak);
	}
}

void AGP4Character::OnEndTweaking()
{
	ITweakable::OnEndTweaking();

	UTweakSubSystem* TweakSubSystem = GetGameInstance()->GetSubsystem<UTweakSubSystem>();
	if (TweakSubSystem)
	{
		TweakSubSystem->OnBroadcastSelfTweak.RemoveAll(this);
	}
}

int32 AGP4Character::GetTweakFlags()
{
	return TweakFlags;
}

void AGP4Character::ReceiveTweak(UTweak* Tweak)
{
	if(!TweakOverrides.Contains(Tweak->GetClass()))
	{
		Tweak->ApplyTweak(this);
		OnCheckSizeChanged.Broadcast();
	}
	else
	{
		Tweak->Constraint = TweakOverrides[Tweak->GetClass()];
		Tweak->ApplyTweak(this);
		OnCheckSizeChanged.Broadcast();
		Tweak->Constraint = FTweakConstraint();
	}
}

//////////////////////////////////////////////////////////////////////////
// Input

void AGP4Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGP4Character::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AGP4Character::Look);
	}
}


void AGP4Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AGP4Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

bool AGP4Character::TrySelect() //TODO: Move playercontroller and vector vars
{
	UTweakAbility* Ability = Cast<UTweakAbility>(GetComponentByClass(UTweakAbility::StaticClass()));
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (!PlayerController || !Ability)
	{
		return false;
	}

	FVector StartLocation;
	FRotator ViewRotation;
	PlayerController->GetPlayerViewPoint(StartLocation, ViewRotation);

	FVector EndLocation = StartLocation + (ViewRotation.Vector() * 20000.f);

	// Setup trace parameters
	FHitResult HitResult;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this); // Ignore the character itself

	if (ActorsInBoxTrace.IsEmpty())
	{
		return false;
	}


	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, CollisionParams))
	{
		AActor* HitActor = HitResult.GetActor();
		if (HitActor && HitActor->GetClass()->ImplementsInterface(UTweakable::StaticClass()))
		{
			if (!Ability->SelectedTweakables.Contains(HitActor))
			{
				if(IsMultiSelectPressed)
				{
					Ability->Select(HitActor);
				}
				else
				{
					Ability->SelectOnly(HitActor);
				}
			}
			else
			{
				Ability->DeSelectActor(HitActor);
			}

			return true;
		}
	}

	return false;
}
