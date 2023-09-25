#pragma once

#include "CoreMinimal.h"
#include "GP4_MainSaveGame.h"
#include "Engine/GameInstance.h"
#include "GP4_GameInstance.generated.h"


UCLASS()
class GP4_API UGP4_GameInstance : public UGameInstance
{
	GENERATED_BODY()

private:

	static const FString UNIQUE_SAVE_SLOT;

public:

	UPROPERTY(BlueprintReadWrite)
	UGP4_MainSaveGame* CurrentSaveGame;

	UFUNCTION(BlueprintCallable)
	bool IsNewGame();
	UFUNCTION(BlueprintCallable)
	bool CreateNewSaveGame();
	UFUNCTION(BlueprintCallable)
	bool LoadGame();
	UFUNCTION(BlueprintCallable)
	bool SaveGame();
	
};
