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

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
