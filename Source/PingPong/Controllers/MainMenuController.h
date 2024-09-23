#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "MainMenuController.generated.h"

UCLASS()
class PINGPONG_API AMainMenuController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UUserWidget* MainMenuWidget;

	AMainMenuController();

	virtual void OnPossess(APawn* PossessedPawn) override;
	virtual void OnUnPossess() override;
};
