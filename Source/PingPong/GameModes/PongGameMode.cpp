#include "PongGameMode.h"

#include "Actors/PongPlayerStart.h"
#include "Actors/Ball.h"
#include "Actors/Paddle.h"
#include "Camera/CameraActor.h"
#include "Controllers/PongControllerBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameState.h"
#include "GameFramework/PlayerState.h"
#include "GameStates/PongGameState.h"

APongGameMode::APongGameMode()
{
	MaxPlayers = 2;
	MatchStartDelay = 3.0f;
	RoundStartDelay = 2.0f;
	GameCommenceDelay = 1.0f;
	bMatchInProgress = false;
	Ball = nullptr;
}

void APongGameMode::StartPlay()
{
	Super::StartPlay();

	Ball = Cast<ABall>(UGameplayStatics::GetActorOfClass(GetWorld(), ABall::StaticClass()));
}

void APongGameMode::RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot)
{
	if (APongPlayerStart* PongPlayerStart = Cast<APongPlayerStart>(StartSpot))
	{
		if (APongControllerBase* PlayerController = Cast<APongControllerBase>(NewPlayer))
		{
			PlayerController->SetPlayerCamera(PongPlayerStart->PlayerCamera);
		}
	}

	Super::RestartPlayerAtPlayerStart(NewPlayer, StartSpot);
}

AActor* APongGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	if (APongControllerBase* PlayerController = Cast<APongControllerBase>(Player))
	{
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APongPlayerStart::StaticClass(), OutActors);

		for (AActor* PlayerStart : OutActors)
		{
			if (APongPlayerStart* PongPlayerStart = Cast<APongPlayerStart>(PlayerStart))
			{
				if (PongPlayerStart->PlayerIndex == PlayerController->GetPlayerIndex())
				{
					return PongPlayerStart;
				}
			}
		}
	}

	return nullptr;
}

void APongGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	if (GetNumPlayers() >= MaxPlayers)
	{
		FGameModeEvents::GameModePreLoginEvent.Broadcast(this, UniqueId, ErrorMessage);
		return;
	}

	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

void APongGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (GetNumPlayers() >= MaxPlayers)
	{
		if (UWorld* World = GetWorld())
		{
			World->GetTimerManager().SetTimer(MatchDelayTimer, this, &APongGameMode::StartMatch, GameCommenceDelay, false);
		}
	}

	if (NewPlayer)
	{
		if (APawn* NewPlayerPawn = NewPlayer->GetPawn())
		{
			NewPlayerPawn->DisableInput(NewPlayer);
		}
	}
}

void APongGameMode::StartMatch()
{
	bMatchInProgress = true;

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(MatchDelayTimer, this, &APongGameMode::StartRound, MatchStartDelay, false);
	}

	if (APongGameState* PongGameState = GetGameState<APongGameState>())
	{
		PongGameState->BroadcastMatchStartEvent();
	}
}

bool APongGameMode::IsMatchInProgress() const
{
	return bMatchInProgress;
}

void APongGameMode::Score(int32 ScoredPlayer)
{
	Ball->ResetBall();

	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(MatchDelayTimer, this, &APongGameMode::StartRound, RoundStartDelay, false);
	}

	if (APongGameState* PongGameState = GetGameState<APongGameState>())
	{
		PongGameState->Score(ScoredPlayer);
	}
}

void APongGameMode::StartRound()
{
	SetPlayersInputEnabled(true);

	if (Ball)
	{
		Ball->ActivateBall();
	}

	if (APongGameState* PongGameState = GetGameState<APongGameState>())
	{
		PongGameState->BroadcastRoundStartEvent();
	}
}

FString APongGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
	if (APongControllerBase* PlayerController = Cast<APongControllerBase>(NewPlayerController))
	{
		PlayerController->SetPlayerIndex(GetNumPlayers() - 1);
	}

	return Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
}

void APongGameMode::SetPlayersInputEnabled(bool bEnabled)
{
	if (AGameStateBase* CurrentGameState = GetGameState<AGameStateBase>())
	{
		for (TObjectPtr<APlayerState>& Player : CurrentGameState->PlayerArray)
		{
			if (APlayerState* PlayerState = Player.Get())
			{
				if (APlayerController* PlayerController = PlayerState->GetPlayerController())
				{
					if (APawn* PlayerPawn = PlayerController->GetPawn())
					{
						bEnabled ? PlayerPawn->EnableInput(PlayerController) : PlayerPawn->DisableInput(PlayerController);
					}
				}
			}
		}
	}
}

void APongGameMode::ResetPlayers()
{
	if (AGameStateBase* CurrentGameState = GetGameState<AGameStateBase>())
	{
		for (TObjectPtr<APlayerState>& Player : CurrentGameState->PlayerArray)
		{
			if (APlayerState* PlayerState = Player.Get())
			{
				if (APaddle* PaddlePawn = PlayerState->GetPawn<APaddle>())
				{
					PaddlePawn->ResetPaddle();
				}
			}
		}
	}
}
