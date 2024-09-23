#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "PongControllerBase.generated.h"

UCLASS()
class PINGPONG_API APongControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	int32 GetPlayerIndex() const;

	UFUNCTION(BlueprintPure)
	int32 GetAwayPlayerIndex() const;

	UFUNCTION(BlueprintPure)
	ACameraActor* GetPlayerCamera();

public:
	APongControllerBase();

	void SetPlayerCamera(ACameraActor* CameraActor);
	void SetPlayerIndex(int32 Index);

	virtual void OnPossess(APawn* PossessedPawn) override;
	virtual void ClientRestart_Implementation(APawn* NewPawn) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION(Server, Unreliable)
	void ServerAddMovementInput(float MovementValue);

	UFUNCTION()
	void OnRep_PlayerCamera();

	UPROPERTY(ReplicatedUsing = OnRep_PlayerCamera, BlueprintReadOnly)
	ACameraActor* PlayerCamera;

	UPROPERTY(Replicated, BlueprintReadOnly)
	int32 PlayerIndex;
};
