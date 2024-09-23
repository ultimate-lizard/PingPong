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
	}

	FInputModeUIOnly InputMode;
	SetInputMode(InputMode);
}

void AMainMenuController::OnUnPossess()
{
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	Super::OnUnPossess();
}
