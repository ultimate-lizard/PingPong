#include "GameStates/PongGameState.h"

#include "GameModes/PongGameMode.h"
#include "Net/UnrealNetwork.h"

void APongGameState::BroadcastMatchStartEvent_Implementation()
{
	OnMatchStart.Broadcast();
}

void APongGameState::BroadcastMatchEndEvent_Implementation()
{
	OnMatchEnd.Broadcast();
}

void APongGameState::BroadcastOnScoreEvent_Implementation(int32 ScoredPlayer)
{
	OnScore.Broadcast(ScoredPlayer);
}

void APongGameState::BroadcastRoundStartEvent_Implementation()
{
	OnRoundStart.Broadcast();
}

int32 APongGameState::GetScore(int32 PlayerIndex)
{
	if (PlayerIndex >= Scores.Num())
	{
		return 0;
	}

	return Scores[PlayerIndex];
}

int32 APongGameState::GetMaxPlayers() const
{
	return MaxPlayers;
}

APongGameState::APongGameState()
{
	bReplicates = true;
}

void APongGameState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		if (UWorld* World = GetWorld())
		{
			if (APongGameMode* PongGameMode = World->GetAuthGameMode<APongGameMode>())
			{
				MaxPlayers = PongGameMode->MaxPlayers;
				Scores.SetNum(MaxPlayers);
			}
		}
	}
}

void APongGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APongGameState, Scores);
	DOREPLIFETIME(APongGameState, MaxPlayers);
}

void APongGameState::Score(int32 ScoredPlayerIndex)
{
	if (HasAuthority())
	{
		IncrementScore(ScoredPlayerIndex);
		OnScoreUpdate.Broadcast();
	}
}

void APongGameState::SetMaxPlayers(int32 NewMaxPlayers)
{
	MaxPlayers = NewMaxPlayers;
}

void APongGameState::OnRep_Score()
{
	OnScoreUpdate.Broadcast();
}

void APongGameState::OnRep_MaxPlayers()
{
	Scores.SetNum(MaxPlayers);
}

void APongGameState::IncrementScore(int32 ScoredPlayerIndex)
{
	if (ScoredPlayerIndex >= Scores.Num())
	{
		return;
	}

	Scores[ScoredPlayerIndex]++;
}
