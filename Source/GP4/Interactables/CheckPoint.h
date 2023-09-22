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
	TArray<FName> PreviousLevels;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> CurrentLevels;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> NextLevels;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	UFUNCTION(BlueprintCallable, Category = "GP4")
	static void LoadLevel(AGP4Character* Character);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "GP4")
	void OnLoadLevel(AGP4Character* Character);
	
	UFUNCTION(BlueprintCallable, Category = "GP4")
	static void ReLoadLevel(AGP4Character* Character);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "GP4")
	void OnReLoadLevel(AGP4Character* Character);
	
	UFUNCTION(BlueprintCallable, Category = "GP4")
	static void StreamLevels(UWorld* World, TArray<FName> LevelNames);
	
	UFUNCTION(BlueprintCallable, Category = "GP4")
	static void UnloadLevels(UWorld* World, TArray<FName> LevelNames);
};
