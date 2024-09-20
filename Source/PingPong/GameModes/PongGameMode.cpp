#include "PongGameMode.h"

#include "Actors/PongPlayerStart.h"
#include "Camera/CameraActor.h"
#include "Controllers/PongControllerBase.h"
#include "Kismet/GameplayStatics.h"

APongGameMode::APongGameMode()
{
	MaxPlayers = 2;
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
		ErrorMessage = FString(TEXT("The server is full"));
		FGameModeEvents::GameModePreLoginEvent.Broadcast(this, UniqueId, ErrorMessage);
		return;
	}

	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
}

FString APongGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
	if (APongControllerBase* PlayerController = Cast<APongControllerBase>(NewPlayerController))
	{
		PlayerController->SetPlayerIndex(GetNumPlayers() - 1);
	}

	return Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
}
