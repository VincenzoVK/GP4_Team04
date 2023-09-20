// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvQueryTestHeight.h"

#include "EnvironmentQuery/Contexts/EnvQueryContext_Querier.h"
#include "EnvironmentQuery/Items/EnvQueryAllItemTypes.h"

UEnvQueryTestHeight::UEnvQueryTestHeight()
{
	CompareHeightTo = UEnvQueryContext_Querier::StaticClass();
	ValidItemType = UEnvQueryItemType_VectorBase::StaticClass();
}

void UEnvQueryTestHeight::RunTest(FEnvQueryInstance& QueryInstance) const
{
	UObject* Owner = QueryInstance.Owner.Get();

	if (!Owner)
	{
		return;
	}

	FloatValueMin.BindData(Owner, QueryInstance.QueryID);
	float MinThresholdValue = FloatValueMin.GetValue();

	FloatValueMax.BindData(Owner, QueryInstance.QueryID);
	float MaxThresholdValue = FloatValueMax.GetValue();

	TArray<FVector> ContextLocations;
	if (!QueryInstance.PrepareContext(CompareHeightTo, ContextLocations))
	{
		return;
	}
	
	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		const FVector ItemLocation = GetItemLocation(QueryInstance, It.GetIndex());

		for (int32 ContextIndex = 0; ContextIndex < ContextLocations.Num(); ContextIndex++)
		{
			const float HeightDifference = ItemLocation.Z - ContextLocations[ContextIndex].Z;
			It.SetScore(TestPurpose, FilterType, HeightDifference, MinThresholdValue, MaxThresholdValue);
		}
	}
}
