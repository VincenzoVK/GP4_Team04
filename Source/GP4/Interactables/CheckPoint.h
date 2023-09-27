#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GP4/GP4Character.h"
#include "CheckPoint.generated.h"

UCLASS()
class GP4_API ACheckPoint : public AActor
{
	GENERATED_BODY()

public:
	ACheckPoint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* Volume;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Index;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> PreviousLevels;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> CurrentLevels;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> NextLevels;

protected:
	virtual void BeginPlay() override;

	int LastLevelIndex;
	UPROPERTY()
	AGP4Character* CurrentCharacter;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	UFUNCTION(BlueprintCallable, Category = "GP4")
	void LoadLevel(AGP4Character* Character);
	
	UFUNCTION(BlueprintCallable, Category = "GP4")
	void ReLoadLevel(AGP4Character* Character);

	UFUNCTION()
	void StreamLastLevel();
	
	UFUNCTION(BlueprintCallable, Category = "GP4")
	void UnloadLevels(UWorld* World, TArray<FName> LevelNames);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void LoadLevelByName();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UnLoadLevelByName(AGP4Character* Character);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ReLoadFromCheckPoint();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnReachCheckPoint();
};
