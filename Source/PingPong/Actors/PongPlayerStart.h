#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "PongPlayerStart.generated.h"

UCLASS()
class PINGPONG_API APongPlayerStart : public APlayerStart
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ACameraActor* PlayerCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int64 PlayerIndex;
};
