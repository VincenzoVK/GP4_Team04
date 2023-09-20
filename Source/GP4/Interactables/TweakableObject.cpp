#include "TweakableObject.h"

#include "TweakConstraint.h"
#include "GP4/GP4Character.h"
#include "GP4/Player/TweakAbility.h"
#include "GP4/Utils/TweakSubSystem.h"
#include "Kismet/GameplayStatics.h"

ATweakableObject::ATweakableObject()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATweakableObject::BeginPlay()
{
	Super::BeginPlay();
	
	PhysicalMaterial = NewObject<UPhysicalMaterial>();
	PhysicalMaterial->Friction = 0.7f;
	PhysicalMaterial->StaticFriction = 0.0f;
	PhysicalMaterial->FrictionCombineMode = EFrictionCombineMode::Average;
	PhysicalMaterial->Restitution = 0.3f;
	PhysicalMaterial->RestitutionCombineMode = EFrictionCombineMode::Average;
	PhysicalMaterial->Density = 1.0f;
	PhysicalMaterial->SleepLinearVelocityThreshold = 1.0f;
	PhysicalMaterial->SleepAngularVelocityThreshold = 0.05f;
	PhysicalMaterial->SleepCounterThreshold = 4;
	PhysicalMaterial->RaiseMassToPower = 0.75;
	PhysicalMaterial->DestructibleDamageThresholdScale = 1.0f;
	PhysicalMaterial->SurfaceType = SurfaceType_Default;
}

void ATweakableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATweakableObject::BeginDestroy()
{
	AGP4Character* Character = Cast<AGP4Character>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if(Character)
	{
		UTweakAbility* TweakAbility = Character->GetComponentByClass<UTweakAbility>();
		if(TweakAbility)
		{
			TweakAbility->DeSelectActor(this);
		}
	}
	
	Super::BeginDestroy();
}

void ATweakableObject::OnStartTweaking()
{
	ITweakable::OnStartTweaking();

	Execute_StartTweaking(this);
	
	UTweakSubSystem* TweakSubSystem = GetGameInstance()->GetSubsystem<UTweakSubSystem>();
	if(TweakSubSystem)
	{
		TweakSubSystem->OnBroadcastTweak.AddUniqueDynamic(this, &ATweakableObject::ReceiveTweak);
	}
}

void ATweakableObject::OnEndTweaking()
{
	ITweakable::OnEndTweaking();

	Execute_EndTweaking(this);
	
	UTweakSubSystem* TweakSubSystem = GetGameInstance()->GetSubsystem<UTweakSubSystem>();
	if(TweakSubSystem)
	{
		TweakSubSystem->OnBroadcastTweak.RemoveAll(this);
	}
}

bool ATweakableObject::CanBeTweaked()
{
	return IsTweakable;
}

int32 ATweakableObject::GetTweakFlags()
{
	return TweakFlags;
}

void ATweakableObject::ReceiveTweak(UTweak* Tweak)
{
	if(!IsTweakable)
		return;

	if(!TweakOverrides.Contains(Tweak->GetClass()))
	{
		Tweak->ApplyTweak(this);
		OnReceiveTweak(Tweak);
	}
	else
	{
		Tweak->Constraint = TweakOverrides[Tweak->GetClass()];
		Tweak->ApplyTweak(this);
		OnReceiveTweak(Tweak);
		Tweak->Constraint = FTweakConstraint();
	}
}

void ATweakableObject::SetFriction(float Friction)
{
	PhysicalMaterial = NewObject<UPhysicalMaterial>();
	PhysicalMaterial->Friction = Friction;
	PhysicalMaterial->StaticFriction = 0.0f;
	PhysicalMaterial->FrictionCombineMode = EFrictionCombineMode::Average;
	PhysicalMaterial->Restitution = 0.3f;
	PhysicalMaterial->RestitutionCombineMode = EFrictionCombineMode::Average;
	PhysicalMaterial->Density = 1.0f;
	PhysicalMaterial->SleepLinearVelocityThreshold = 1.0f;
	PhysicalMaterial->SleepAngularVelocityThreshold = 0.05f;
	PhysicalMaterial->SleepCounterThreshold = 4;
	PhysicalMaterial->RaiseMassToPower = 0.75;
	PhysicalMaterial->DestructibleDamageThresholdScale = 1.0f;
	PhysicalMaterial->SurfaceType = SurfaceType_Default;
	GetComponentByClass<UStaticMeshComponent>()->SetPhysMaterialOverride(PhysicalMaterial);
}

float ATweakableObject::GetFriction()
{
	return PhysicalMaterial->Friction;
}

