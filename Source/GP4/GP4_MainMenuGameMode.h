#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GP4_MainMenuGameMode.generated.h"

UCLASS()
class GP4_API AGP4_MainMenuGameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Menu")
	class UGP4_GameInstance* GameInstance;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Menu Events")
	void OnShowMainMenu(bool NewGame);
};
