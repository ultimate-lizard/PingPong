#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "PongGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMatchStartSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMatchEndSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRoundStartSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreSignature, int32, LostPlayerIndex);

UCLASS()
class PINGPONG_API APongGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnMatchStartSignature OnMatchStart;

	UPROPERTY(BlueprintAssignable)
	FOnMatchEndSignature OnMatchEnd;

	UPROPERTY(BlueprintAssignable)
	FOnRoundStartSignature OnRoundStart;

	UPROPERTY(BlueprintAssignable)
	FOnScoreSignature OnScore;

	UFUNCTION(NetMulticast, Reliable)
	void BroadcastMatchStartEvent();

	UFUNCTION(NetMulticast, Reliable)
	void BroadcastMatchEndEvent();

	UFUNCTION(NetMulticast, Reliable)
	void BroadcastRoundStartEvent();

	UFUNCTION(NetMulticast, Reliable)
	void BroadcastOnScoreEvent(int32 LostPlayerIndex);
};
