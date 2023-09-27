#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FNarrativeInfo.generated.h"


USTRUCT(Blueprintable)
struct FNarrativeInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(MultiLine=true))
	FString Subtitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* SFX;
};
