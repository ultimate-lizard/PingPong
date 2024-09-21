#include "Controllers/PongControllerBase.h"

#include "Camera/CameraActor.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerState.h"

APongControllerBase::APongControllerBase()
{
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

void APongControllerBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APongControllerBase, PlayerCamera);
}

void APongControllerBase::ServerAddMovementInput_Implementation(float MovementValue)
{
	if (APawn* CurrentPawn = GetPawn())
	{
		if (CurrentPawn->InputEnabled())
		{
			CurrentPawn->AddActorWorldOffset(CurrentPawn->GetActorRightVector() * MovementValue, true);
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
