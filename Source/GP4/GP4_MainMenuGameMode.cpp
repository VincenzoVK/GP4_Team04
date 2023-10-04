
#include "GP4_MainMenuGameMode.h"

#include "GP4_GameInstance.h"
#include "Kismet/GameplayStatics.h"

void AGP4_MainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UGP4_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (GameInstance != nullptr)
	{
		bool bIsNewGame = GameInstance->IsNewGame();

		OnShowMainMenu(bIsNewGame);
	}
}

void AGP4_MainMenuGameMode::OnNewGame_Implementation(FName MapNameToLoad)
{
	if (GameInstance == nullptr) return;
	
	if (GameInstance->CreateNewSaveGame())
	{
		FLatentActionInfo LatentInfo;
		//UGameplayStatics::LoadStreamLevel(GetWorld(), MapNameToLoad, true, false, LatentInfo);
	}
}

void AGP4_MainMenuGameMode::OnLoadGame_Implementation(FName MapNameToLoad)
{
	FLatentActionInfo LatentInfo;
	UGameplayStatics::LoadStreamLevel(GetWorld(), MapNameToLoad, true, false, LatentInfo);
}
