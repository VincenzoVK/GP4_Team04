#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Tweakable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UTweakable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GP4_API ITweakable
{
	GENERATED_BODY()

public:
	
	virtual void OnStartTweaking();
	virtual void OnEndTweaking();
	virtual int32 GetTweakFlags();
	virtual bool CanBeTweaked();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Tweakable")
	void StartTweaking();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Tweakable")
	void EndTweaking();
};
