// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_RoamArea.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

void UMyBTTask_RoamArea::FindRoamLocation(AAIController* Controller)
{
	FNavLocation RoamLocation;

	const UNavigationSystemV1* NavMesh = UNavigationSystemV1::GetCurrent(GetWorld());

	UBlackboardComponent* Blackboard = Controller->GetBlackboardComponent();
	NavMesh->GetRandomReachablePointInRadius(Blackboard->GetValueAsVector("LastSensedLocation"), 500.0f, RoamLocation);

	Blackboard->SetValueAsVector("MoveLocation", RoamLocation.Location);
}
