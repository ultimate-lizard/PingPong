#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Paddle.generated.h"

UCLASS()
class PINGPONG_API APaddle : public APawn
{
	GENERATED_BODY()

public:
	APaddle();

	virtual void BeginPlay() override;

	void ResetPaddle();

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* PaddleMesh;

	FVector InitialLocation;
};
