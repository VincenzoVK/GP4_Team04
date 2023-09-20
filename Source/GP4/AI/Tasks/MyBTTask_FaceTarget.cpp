// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_FaceTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

void UMyBTTask_FaceTarget::LookAtTarget(AAIController* Controller, APawn* ControlledPawn)
{

	if(!Controller || !ControlledPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("You are missing function parameters"));
		return;
	}
	
	UBlackboardComponent* Blackboard = Controller->GetBlackboardComponent();

	FVector SnipingLocation = Blackboard->GetValueAsVector("MoveLocation");
	Controller->MoveToLocation(SnipingLocation, 20.0f);
	
	FVector TargetLocation = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();
	
	FVector CurrentLocation = ControlledPawn->GetActorLocation();
	TargetLocation.Z = 0;
	CurrentLocation.Z = 0;

	FRotator NewLookRotation = UKismetMathLibrary::FindLookAtRotation(CurrentLocation, TargetLocation);
	UE_LOG(LogTemp, Warning, TEXT("Vector Direction: %s"), *ControlledPawn->GetName());

	ControlledPawn->SetActorRotation(NewLookRotation);
}
