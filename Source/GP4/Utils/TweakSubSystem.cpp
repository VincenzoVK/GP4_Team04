#include "TweakSubSystem.h"

void UTweakSubSystem::BroadcastTweak(UTweak* Tweak)
{
	OnBroadcastTweak.Broadcast(Tweak);
}

void UTweakSubSystem::BroadcastSelfTweak(UTweak* Tweak)
{
	OnBroadcastSelfTweak.Broadcast(Tweak);
}
