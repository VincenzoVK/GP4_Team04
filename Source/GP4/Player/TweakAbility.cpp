// Fill out your copyright notice in the Description page of Project Settings.


#include "TweakAbility.h"


// Sets default values for this component's properties
UTweakAbility::UTweakAbility()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTweakAbility::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTweakAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTweakAbility::SelectOnly(AActor* Tweakable)
{
	EndSelection();
	Select(Tweakable);
}

void UTweakAbility::Select(AActor* Tweakable)
{
	ITweakable* TweakableInterface = Cast<ITweakable>(Tweakable);
	if(TweakableInterface)
	{
		if(!TweakableInterface->CanBeTweaked())
			return;
		SelectedTweakables.Add(Tweakable);
		SelfSelected = false;
		TweakableInterface->OnStartTweaking();
	}
}

void UTweakAbility::SelectSelf()
{
	ITweakable* TweakableActor = Cast<ITweakable>(GetOwner());
	if(TweakableActor)
	{
		SelfSelected = true;
		TweakableActor->OnStartTweaking();
	}
}

void UTweakAbility::EndSelection()
{
	for (TScriptInterface<ITweakable> Tweakable : SelectedTweakables)
	{
		if(Tweakable)
		{
			Tweakable->OnEndTweaking();
		}
	}
	SelectedTweakables.Empty();
}

void UTweakAbility::DeSelectActor(AActor* Tweakable)
{
	if(SelectedTweakables.Contains(Tweakable))
	{
		ITweakable* TweakableActor = Cast<ITweakable>(Tweakable);
		TweakableActor->OnEndTweaking();
		SelectedTweakables.Remove(Tweakable);
	}
}

void UTweakAbility::EndSelfSelection()
{
	ITweakable* TweakableActor = Cast<ITweakable>(GetOwner());
	if(TweakableActor && SelfSelected)
	{
		SelfSelected = false;
		TweakableActor->OnEndTweaking();
	}
}

