#include "Controllers/MainMenuController.h"

#include "Blueprint/UserWidget.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

AMainMenuController::AMainMenuController()
{
	MainMenuWidget = nullptr;
}

void AMainMenuController::BeginPlay()
{
	Super::BeginPlay();

	SetShowMouseCursor(true);

	if (MainMenuWidget)
	{
		MainMenuWidget->SetOwningPlayer(this);
		MainMenuWidget->AddToViewport();

		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);

		SetInputMode(InputMode);
	}
}

void AMainMenuController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	SetShowMouseCursor(false);

	if (IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get())
	{
		if (IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface())
		{
			SessionInterface->DestroySession(NAME_GameSession);
		}
	}
}
