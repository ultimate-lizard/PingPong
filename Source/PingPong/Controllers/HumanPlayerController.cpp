#include "Controllers/HumanPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/GameState.h"
#include "GameModes/PongGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"

AHumanPlayerController::AHumanPlayerController()
{
	DefaultMappingContext = nullptr;
	MovementAction = nullptr;
	QuitGameAction = nullptr;
	InputSensitivity = 10.0f;
	HUDWidget = nullptr;
}

void AHumanPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (!DefaultMappingContext)
	{
		return;
	}

	if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		InputSubsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	if (HUDWidget && IsLocalController())
	{
		HUDWidget->SetOwningPlayer(this);
		HUDWidget->AddToViewport();
	}
}

void AHumanPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AHumanPlayerController::Move);
		EnhancedInputComponent->BindAction(QuitGameAction, ETriggerEvent::Started, this, &AHumanPlayerController::QuitGame);
	}
}

void AHumanPlayerController::Move(const FInputActionValue& Value)
{
	const float MovementValue = Value.Get<float>();
	ServerAddMovementInput(MovementValue * InputSensitivity);
}

void AHumanPlayerController::QuitGame(const FInputActionValue& Value)
{
	if (IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get())
	{
		if (IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface())
		{
			SessionInterface->DestroySession(NAME_GameSession);
		}
	}

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}
