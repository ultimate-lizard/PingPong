#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "PongControllerBase.generated.h"

UCLASS()
class PINGPONG_API APongControllerBase : public APlayerController
{
	GENERATED_BODY()

public:
	APongControllerBase();

	void SetPlayerCamera(ACameraActor* CameraActor);
	ACameraActor* GetPlayerCamera();

	void SetPlayerIndex(int32 Index);
	int32 GetPlayerIndex() const;

	virtual void OnPossess(APawn* PossessedPawn) override;
	virtual void ClientRestart_Implementation(APawn* NewPawn) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	UFUNCTION(Server, Unreliable)
	void ServerAddMovementInput(float MovementValue);

	UFUNCTION()
	void OnRep_PlayerCamera();

	UPROPERTY(ReplicatedUsing = OnRep_PlayerCamera)
	ACameraActor* PlayerCamera;

	int32 PlayerIndex;
};
