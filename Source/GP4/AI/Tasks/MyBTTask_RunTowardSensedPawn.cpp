// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_RunTowardSensedPawn.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

FVector UMyBTTask_RunTowardSensedPawn::FindMoveLocation(AAIController* Controller)
{
	UBlackboardComponent* Blackboard = Controller->GetBlackboardComponent();

	APawn* SensedPawn = Cast<APawn>(Blackboard->GetValueAsObject("SensedPawn"));

	FVector SensedPawnLocation = SensedPawn->GetActorLocation();
	
	FVector MoveLocation = SensedPawnLocation;
	
	Blackboard->SetValueAsVector("MoveLocation", MoveLocation);
	Blackboard->SetValueAsVector("SensedPawnLocation", SensedPawnLocation);

	return MoveLocation;
}
