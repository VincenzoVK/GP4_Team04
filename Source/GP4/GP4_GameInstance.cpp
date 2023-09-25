
#include "GP4_GameInstance.h"

#include "Kismet/GameplayStatics.h"

const FString UGP4_GameInstance::UNIQUE_SAVE_SLOT = "SaveData_0";

bool UGP4_GameInstance::IsNewGame()
{
	if (UGameplayStatics::DoesSaveGameExist(UNIQUE_SAVE_SLOT, 0))
	{
		return false;
	}
	return true;
}

bool UGP4_GameInstance::CreateNewSaveGame()
{
	USaveGame* NewSaveGame = UGameplayStatics::CreateSaveGameObject(UGP4_MainSaveGame::StaticClass());
		
	if (NewSaveGame != nullptr)
	{
		CurrentSaveGame = Cast<UGP4_MainSaveGame>(NewSaveGame);
	}
	
	return UGameplayStatics::SaveGameToSlot(CurrentSaveGame, UNIQUE_SAVE_SLOT, 0);
}

bool UGP4_GameInstance::LoadGame()
{
	CurrentSaveGame = nullptr;

	USaveGame* Slot = UGameplayStatics::LoadGameFromSlot(UNIQUE_SAVE_SLOT, 0);
	if(!Slot)
	{
		CreateNewSaveGame();
	}

	if (Slot != nullptr)
	{
		CurrentSaveGame = Cast<UGP4_MainSaveGame>(Slot);

		if (CurrentSaveGame != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("[UHowToGameInstance::LoadGame] Success loading %s"), *UNIQUE_SAVE_SLOT);

			return true;
		}
	}

	return false;
}

bool UGP4_GameInstance::SaveGame()
{
	
	if (CurrentSaveGame != nullptr)
	{
		return UGameplayStatics::SaveGameToSlot(CurrentSaveGame, UNIQUE_SAVE_SLOT, 0);
	}	

	return false;
}
