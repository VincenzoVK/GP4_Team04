// Fill out your copyright notice in the Description page of Project Settings.


#include "DialougeSubSystem.h"


void UDialougeSubSystem::BroadcastStopSound()
{
	OnStopSound.Broadcast();
}
