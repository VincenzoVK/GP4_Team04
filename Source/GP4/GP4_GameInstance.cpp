
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
