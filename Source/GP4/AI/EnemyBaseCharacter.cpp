// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBaseCharacter.h"

#include "AnimationCoreLibrary.h"
#include "VectorTypes.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GP4/GP4Character.h"
#include "GP4/Interactables/Tweaks/Tweak.h"
#include "GP4/Utils/TweakSubSystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyBaseCharacter::AEnemyBaseCharacter(): TweakFlags(0)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEnemyBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyBaseCharacter::OnStartTweaking()
{
	ITweakable::OnStartTweaking();
    
	Execute_StartTweaking(this);
	
	UTweakSubSystem* TweakSubSystem = GetGameInstance()->GetSubsystem<UTweakSubSystem>();
	if(TweakSubSystem)
	{
		TweakSubSystem->OnBroadcastTweak.AddUniqueDynamic(this, &AEnemyBaseCharacter::ReceiveTweak);
	}
}

void AEnemyBaseCharacter::OnEndTweaking()
{
	ITweakable::OnEndTweaking();

	Execute_EndTweaking(this);
	
	UTweakSubSystem* TweakSubSystem = GetGameInstance()->GetSubsystem<UTweakSubSystem>();
	if(TweakSubSystem)
	{
		TweakSubSystem->OnBroadcastTweak.RemoveAll(this);
	}
}

int32 AEnemyBaseCharacter::GetTweakFlags()
{
	return TweakFlags;
}

void AEnemyBaseCharacter::FindShootDirection(AActor* ProjectileTarget)
{
	if(ProjectileTarget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Target is null"));
		return;
	}

	float ProjectileSpeed = AEnemyProjectile::ProjectileInitialSpeed;
	
	FVector TargetLocation = ProjectileTarget->GetActorLocation();
	FVector CurrentLocation = GetActorLocation() + (FVector::UpVector * 100.0f);
	
	FVector TargetInitialVelocity = ProjectileTarget->GetVelocity();
	FVector DirectionToTarget = TargetLocation - CurrentLocation;

	float Distance = DirectionToTarget.Length();
	float Time = Distance / ProjectileSpeed;
	
	FVector PredictedLocation = TargetLocation + (TargetInitialVelocity * Time);

	FVector AimDirection = PredictedLocation - CurrentLocation;
	AimDirection.Normalize();

	FRotator ProjectileRotation = AimDirection.Rotation();

	FTransform ProjectileTransform;
	ProjectileTransform.SetComponents(ProjectileRotation.Quaternion(),CurrentLocation, FVector(0.2f, 0.2f, 0.2f));

	OnShootProjectile(ProjectileTransform, ProjectileActors[FMath::RandRange(0, ProjectileActors.Num()-1)]);
}

void AEnemyBaseCharacter::CheckSize()
{
	AActor* PlayerActor = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	FVector PlayerScale = PlayerActor->GetActorScale();
	
	FVector CurrentScale = GetActorScale();
	EEnemySizeState InitialSizeState = CurrentSize;

	float ScalePercentage = CurrentScale.X / PlayerScale.X;

	if(ScalePercentage <= 0.5f)
	{
		CurrentSize = EEnemySizeState::Small;
	}
	else if(ScalePercentage > 2.0f)
	{
		CurrentSize = EEnemySizeState::Big;
	}
	else
	{
		CurrentSize = EEnemySizeState::Medium;
	}
	
	if(InitialSizeState != CurrentSize)
	{
		OnChangeSize();
	}
}

void AEnemyBaseCharacter::ReceiveTweak(UTweak* Tweak)
{
	Tweak->ApplyTweak(this);
	CheckSize();
}

