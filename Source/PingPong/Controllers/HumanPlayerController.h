#pragma once

#include "CoreMinimal.h"
#include "Controllers/PongControllerBase.h"

#include "HumanPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UUserWidget;

UCLASS()
class PINGPONG_API AHumanPlayerController : public APongControllerBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* QuitGameAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float InputSensitivity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UUserWidget* HUDWidget;

	AHumanPlayerController();

	virtual void BeginPlay() override;

protected:
	virtual void SetupInputComponent() override;

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void QuitGame(const FInputActionValue& Value);
};
