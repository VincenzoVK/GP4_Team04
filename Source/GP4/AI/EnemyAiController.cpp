// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAiController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISense_Sight.h"

void AEnemyAiController::HandleSightSense(AActor* SensedActor, FAIStimulus Stimulus)
{
	if(UAIPerceptionSystem::GetSenseClassForStimulus(GetWorld(), Stimulus) != UAISense_Sight::StaticClass())
	{
		return;
	}
	
	if(!Stimulus.WasSuccessfullySensed())
	{
		GetAIPerceptionComponent()->ForgetAll();
		GetAIPerceptionComponent()->OnTargetPerceptionForgotten.Broadcast(SensedActor);
		return;
	}

	if(SensedActor->ActorHasTag("Player"))
	{
		Blackboard->SetValueAsObject("SensedPawn", SensedActor);
		Blackboard->SetValueAsVector("LastSensedLocation", SensedActor->GetActorLocation());
		Blackboard->SetValueAsBool("HasSensedPawn", true);
	}
	
}
