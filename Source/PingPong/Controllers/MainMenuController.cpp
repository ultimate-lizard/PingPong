#include "Controllers/MainMenuController.h"

#include "Blueprint/UserWidget.h"

AMainMenuController::AMainMenuController()
{
	MainMenuWidget = nullptr;
}

void AMainMenuController::OnPossess(APawn* PossessedPawn)
{
	Super::OnPossess(PossessedPawn);

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

void AMainMenuController::OnUnPossess()
{
	Super::OnUnPossess();

	SetShowMouseCursor(false);
	SetInputMode(FInputModeGameAndUI());
}
