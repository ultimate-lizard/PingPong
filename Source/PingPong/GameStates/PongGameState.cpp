#include "GameStates/PongGameState.h"

void APongGameState::BroadcastMatchStartEvent_Implementation()
{
	OnMatchStart.Broadcast();
}

void APongGameState::BroadcastMatchEndEvent_Implementation()
{
	OnMatchEnd.Broadcast();
}

void APongGameState::BroadcastOnScoreEvent_Implementation(int32 LostPlayerIndex)
{
	OnScore.Broadcast(LostPlayerIndex);
}

void APongGameState::BroadcastRoundStartEvent_Implementation()
{
	OnRoundStart.Broadcast();
}
