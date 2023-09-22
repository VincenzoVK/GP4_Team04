// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Engine/DataAsset.h"
#include "Definitions.generated.h"

USTRUCT(BlueprintType)
struct FRoomInfo
{
	GENERATED_USTRUCT_BODY()	
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Room")
	int RoomID;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Quest")
	bool IsCompleted;
	
};
