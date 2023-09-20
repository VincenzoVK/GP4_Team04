// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomChanceDecorator.h"

#include "BehaviorTree/BlackboardComponent.h"

class UBlackboardComponent;

bool URandomChanceDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	float randomNumber = FMath::RandRange(0.0f, 100.0f);

	bool bSuccess = randomNumber <= SuccessChance; 
	
	// UE_LOG(LogTemp, Warning, TEXT("Attempt %s. Generated number was: %f and had to be equal to or lower than %f"), (bSuccess ? TEXT("succeeded") : TEXT("failed")), randomNumber, SuccessChance);

	if(bSuccess)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool("ShouldTweakObject", true);
	}
	
	return bSuccess;
}
