#include "CheckPoint.h"

#include "Engine/LevelStreaming.h"
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
		}
	}
}

void ACheckPoint::LoadLevel(AGP4Character* Character)
{
	if(Character->PreviousCheckPoint)
	{
		UnloadLevels(Character->GetWorld(), Character->PreviousCheckPoint->PreviousLevels);
	}
	if(Character->CurrentCheckPoint)
	{
		StreamLevels(Character->GetWorld(), Character->CurrentCheckPoint->PreviousLevels);
		StreamLevels(Character->GetWorld(), Character->CurrentCheckPoint->CurrentLevels);
		StreamLevels(Character->GetWorld(), Character->CurrentCheckPoint->NextLevels);
	}
}

void ACheckPoint::ReLoadLevel(AGP4Character* Character)
{
	if(!Character)
		return;

	ACheckPoint* Prev = Character->PreviousCheckPoint;
	ACheckPoint* Current = Character->CurrentCheckPoint;
	UWorld* World = Character->GetWorld();
	
	UClass* CharacterClass = Character->GetClass();
	const FVector RespawnLocation = Character->CurrentCheckPoint->GetActorLocation() + FVector::UpVector * 300;
	const FRotator RespawnRotation = Character->CurrentCheckPoint->GetActorRotation();

	Character->Destroy();
	const FActorSpawnParameters SpawnParams;
	AGP4Character* NewCharacter = World->SpawnActor<AGP4Character>(CharacterClass, RespawnLocation, RespawnRotation, SpawnParams);
	NewCharacter->PreviousCheckPoint = Prev;
	NewCharacter->CurrentCheckPoint = Current;
	UGameplayStatics::GetPlayerController(World, 0)->Possess(NewCharacter);

	for (FName LevelName : Current->CurrentLevels)
	{
		const ULevelStreaming* Streaming = UGameplayStatics::GetStreamingLevel(World, LevelName);
			
		if(!Streaming) continue;
		if(!Streaming->IsLevelVisible()) continue;

		LastLevel = LevelName;
		FLatentActionInfo LatentInfo;
		LatentInfo.CallbackTarget = this;
		LatentInfo.ExecutionFunction = FName("StreamLastLevel");
		LatentInfo.UUID = 0;
		LatentInfo.Linkage = 0;
		UGameplayStatics::UnloadStreamLevel(World, LevelName, LatentInfo, false);
	}
}

void ACheckPoint::StreamLastLevel()
{
	FLatentActionInfo LatentInfo;
	UGameplayStatics::LoadStreamLevel(GetWorld(), LastLevel, true, false, LatentInfo);
}

void ACheckPoint::StreamLevels(UWorld* World, TArray<FName> LevelNames)
{
	for (FName LevelName : LevelNames)
	{
		const ULevelStreaming* Streaming = UGameplayStatics::GetStreamingLevel(World, LevelName);
			
		if(!Streaming) continue;
		if(Streaming->IsLevelLoaded()) continue;
			
		FLatentActionInfo LatentInfo;
		UGameplayStatics::LoadStreamLevel(World, LevelName, true, true, LatentInfo);
	}
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

