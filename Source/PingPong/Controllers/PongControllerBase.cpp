#include "Controllers/PongControllerBase.h"

#include "Camera/CameraActor.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerState.h"
#include "GameStates/PongGameState.h"

APongControllerBase::APongControllerBase()
{
	ControlSensitivity = 200.0f;
	PlayerCamera = nullptr;
	PlayerIndex = 0;
}

void APongControllerBase::SetPlayerCamera(ACameraActor* CameraActor)
{
	PlayerCamera = CameraActor;
}

ACameraActor* APongControllerBase::GetPlayerCamera()
{
	return PlayerCamera;
}

void APongControllerBase::OnPossess(APawn* PossessedPawn)
{
	Super::OnPossess(PossessedPawn);

	if (PlayerCamera)
	{
		SetViewTarget(PlayerCamera);
	}
}

void APongControllerBase::ClientRestart_Implementation(APawn* NewPawn)
{
	Super::ClientRestart_Implementation(NewPawn);

	if (PlayerCamera)
	{
		SetViewTarget(PlayerCamera);
	}
}

void APongControllerBase::SetPlayerIndex(int32 Index)
{
	PlayerIndex = Index;
}

int32 APongControllerBase::GetPlayerIndex() const
{
	return PlayerIndex;
}

int32 APongControllerBase::GetAwayPlayerIndex() const
{
	if (UWorld* World = GetWorld())
	{
		if (APongGameState* PongGameState = World->GetGameState<APongGameState>())
		{
			return PongGameState->GetMaxPlayers() - 1 - GetPlayerIndex();
		}
	}
	
	return 0;
}

void APongControllerBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APongControllerBase, PlayerCamera);
	DOREPLIFETIME(APongControllerBase, PlayerIndex);
}

void APongControllerBase::ServerAddMovementInput_Implementation(float MovementValue)
{
	if (APawn* CurrentPawn = GetPawn())
	{
		if (CurrentPawn->InputEnabled())
		{
			CurrentPawn->AddActorWorldOffset(CurrentPawn->GetActorRightVector() * MovementValue * ControlSensitivity, true);
		}
	}
}

void APongControllerBase::OnRep_PlayerCamera()
{
	if (PlayerCamera && GetViewTarget() != PlayerCamera)
	{
		SetViewTarget(PlayerCamera);
	}
}
