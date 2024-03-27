#pragma once

#include "CoreMinimal.h"
#include "Definitions.h"
#include "GameFramework/SaveGame.h"
#include "GP4_MainSaveGame.generated.h"

UCLASS()
class GP4_API UGP4_MainSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SaveGameName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FDateTime CreationTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FRoomInfo> RoomStatus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int RoomIndex = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool CanTweak;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool CanTweakSelf;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool CanGravity;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool CanSize;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool CanAim;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool CanFriction;
	
	void CreateSlot(const FString& SlotName)
	{
		SaveGameName = SlotName;
		CreationTime = FDateTime::Now();
		RoomStatus.Empty();
	}
};
