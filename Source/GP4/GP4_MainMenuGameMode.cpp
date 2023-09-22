
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
