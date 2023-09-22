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

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Menu Events")
	void OnNewGame(FName MapNameToLoad);

	void OnNewGame_Implementation(FName MapNameToLoad);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Menu Events")
	void OnLoadGame(FName MapNameToLoad);

	void OnLoadGame_Implementation(FName MapNameToLoad);

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Menu")
	class UGP4_GameInstance* GameInstance;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Menu Events")
	void OnShowMainMenu(bool NewGame);

	
};
