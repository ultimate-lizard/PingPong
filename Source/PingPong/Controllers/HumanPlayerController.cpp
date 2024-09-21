#include "Controllers/HumanPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/GameState.h"
#include "GameModes/PongGameMode.h"

AHumanPlayerController::AHumanPlayerController()
{
	DefaultMappingContext = nullptr;
	MovementAction = nullptr;
	InputSensitivity = 10.0f;
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
}

void AHumanPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AHumanPlayerController::Move);
	}
}

void AHumanPlayerController::Move(const FInputActionValue& Value)
{
	float MovementValue = Value.Get<float>();
	ServerAddMovementInput(MovementValue * InputSensitivity);
}
