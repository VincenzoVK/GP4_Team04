#include "CheckPoint.h"

#include "Engine/LevelStreaming.h"
#include "GP4/GP4_GameInstance.h"
#include "Kismet/GameplayStatics.h"

ACheckPoint::ACheckPoint()
{
	PrimaryActorTick.bCanEverTick = true;
	Volume = CreateDefaultSubobject<UBoxComponent>(FName("Box Volume"));
	SetRootComponent(Volume);
	Volume->SetBoxExtent(FVector(500, 500, 1000));
}

void ACheckPoint::BeginPlay()
{
	Super::BeginPlay();
}

void ACheckPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACheckPoint::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if(OtherActor->IsA(AGP4Character::StaticClass()))
	{
		AGP4Character* Character = Cast<AGP4Character>(OtherActor);

		if(Character->CurrentCheckPoint != this)
		{
			Character->PreviousCheckPoint = Character->CurrentCheckPoint;
			Character->CurrentCheckPoint = this;

			LoadLevel(Character);
			UGP4_GameInstance* GameInstance = Cast<UGP4_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			if (GameInstance)
			{
				if(GameInstance->CurrentSaveGame)
				{
					GameInstance->CurrentSaveGame->RoomIndex = Index;
					GameInstance->SaveGame();
					GEngine->AddOnScreenDebugMessage(-1, 3, FColor::White, FString::FromInt(Index));
				}
			}
			OnReachCheckPoint();
		}
	}
}

void ACheckPoint::LoadLevel(AGP4Character* Character)
{
	if(Character->PreviousCheckPoint)
	{
		//UnloadLevels(Character->GetWorld(), Character->PreviousCheckPoint->PreviousLevels);
		UnLoadLevelByName(Character);
	}
	if(Character->CurrentCheckPoint)
	{
		LoadLevelByName();
	}
}

void ACheckPoint::ReLoadLevel(AGP4Character* Character)
{
	if(!Character)
		return;


	CurrentCharacter = Character;
	ACheckPoint* Current = Character->CurrentCheckPoint;
	ACheckPoint* Prev = CurrentCharacter->PreviousCheckPoint;
	UWorld* World = Character->GetWorld();

	if(Index == 0)
	{
		UClass* CharacterClass = CurrentCharacter->GetClass();
		const FVector RespawnLocation = CurrentCharacter->CurrentCheckPoint->GetActorLocation() + FVector::UpVector * 300;
		const FRotator RespawnRotation = CurrentCharacter->CurrentCheckPoint->GetActorRotation();

		CurrentCharacter->Destroy();
		const FActorSpawnParameters SpawnParams;
		AGP4Character* NewCharacter = World->SpawnActor<AGP4Character>(CharacterClass, RespawnLocation, RespawnRotation, SpawnParams);
		NewCharacter->PreviousCheckPoint = Prev;
		NewCharacter->CurrentCheckPoint = Current;
		UGameplayStatics::GetPlayerController(World, 0)->Possess(NewCharacter);
		CurrentCharacter = NewCharacter;
		return;		
	}
	
	LastLevelIndex = 0;
	for (FName LevelName : Current->CurrentLevels)
	{
		ULevelStreaming* Streaming = UGameplayStatics::GetStreamingLevel(World, LevelName);
			
		if(!Streaming) continue;

		Streaming->OnLevelUnloaded.Clear();
		Streaming->SetShouldBeLoaded(false);
		Streaming->SetShouldBeVisible(false);
		Streaming->OnLevelUnloaded.AddDynamic(this, &ACheckPoint::StreamLastLevel);
	}
}

void ACheckPoint::StreamLastLevel()
{
	FName LastLevel = CurrentLevels[LastLevelIndex];
	ULevelStreaming* Streaming = UGameplayStatics::GetStreamingLevel(GetWorld(), LastLevel);
			
	if(!Streaming) return;

	Streaming->SetShouldBeLoaded(true);
	Streaming->SetShouldBeVisible(true);

	if(CurrentLevels.Num() - 1 == LastLevelIndex)
	{
		ACheckPoint* Prev = CurrentCharacter->PreviousCheckPoint;
		ACheckPoint* Current = CurrentCharacter->CurrentCheckPoint;
		UWorld* World = CurrentCharacter->GetWorld();
		
		UClass* CharacterClass = CurrentCharacter->GetClass();
		const FVector RespawnLocation = CurrentCharacter->CurrentCheckPoint->GetActorLocation() + FVector::UpVector * 300;
		const FRotator RespawnRotation = CurrentCharacter->CurrentCheckPoint->GetActorRotation();

		CurrentCharacter->Destroy();
		const FActorSpawnParameters SpawnParams;
		AGP4Character* NewCharacter = World->SpawnActor<AGP4Character>(CharacterClass, RespawnLocation, RespawnRotation, SpawnParams);
		NewCharacter->PreviousCheckPoint = Prev;
		NewCharacter->CurrentCheckPoint = Current;
		UGameplayStatics::GetPlayerController(World, 0)->Possess(NewCharacter);
		CurrentCharacter = NewCharacter;
	}
	
	LastLevelIndex++;
}

void ACheckPoint::UnloadLevels(UWorld* World, TArray<FName> LevelNames)
{
	for (FName LevelName : LevelNames)
	{
		const ULevelStreaming* Streaming = UGameplayStatics::GetStreamingLevel(World, LevelName);
			
		if(!Streaming) continue;
		if(!Streaming->IsLevelLoaded()) continue;
			
		FLatentActionInfo LatentInfo;
		UGameplayStatics::UnloadStreamLevel(World, LevelName, LatentInfo, true);
	}
}

