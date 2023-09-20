// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_RunFromSensedPawn.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/MovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

FVector UMyBTTask_RunFromSensedPawn::FindEscapeLocation(AAIController* Controller, APawn* ControlledPawn)
{
	UBlackboardComponent* Blackboard = Controller->GetBlackboardComponent();

	APawn* SensedPawn = Cast<APawn>(Blackboard->GetValueAsObject("SensedPawn"));
	
	FVector ControlledPawnLocation = ControlledPawn->GetActorLocation();
	FVector SensedPawnLocation = SensedPawn->GetActorLocation();

	FRotator EscapeRotation = UKismetMathLibrary::FindLookAtRotation(ControlledPawnLocation, SensedPawnLocation);
	
	FVector EscapeLocation = (UKismetMathLibrary::GetForwardVector(EscapeRotation) * -500.0f) + ControlledPawnLocation;
	EscapeLocation.Z = ControlledPawnLocation.Z;
	
	// Blackboard->SetValueAsVector("MoveLocation", EscapeLocation);
	Blackboard->SetValueAsVector("SensedPawnLocation", SensedPawnLocation);

	return EscapeLocation;
}
