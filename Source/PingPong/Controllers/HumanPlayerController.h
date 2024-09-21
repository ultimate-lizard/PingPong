#pragma once

#include "CoreMinimal.h"
#include "Controllers/PongControllerBase.h"

#include "HumanPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class PINGPONG_API AHumanPlayerController : public APongControllerBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MovementAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	float InputSensitivity;

public:
	AHumanPlayerController();
	virtual void BeginPlay() override;

protected:
	virtual void SetupInputComponent() override;

	UFUNCTION()
	void Move(const FInputActionValue& Value);
};
