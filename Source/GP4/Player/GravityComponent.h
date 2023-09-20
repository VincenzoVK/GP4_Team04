#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GravityComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GP4_API UGravityComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UGravityComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GravityScale = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Mass = 1.f;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
