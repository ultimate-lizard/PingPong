#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"

#include "PongGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMatchStartSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMatchEndSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRoundStartSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreSignature, int32, ScoredPlayer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnScoreUpdateSignature);

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

	UPROPERTY(BlueprintAssignable)
	FOnScoreUpdateSignature OnScoreUpdate;

	UFUNCTION(NetMulticast, Reliable)
	void BroadcastMatchStartEvent();

	UFUNCTION(NetMulticast, Reliable)
	void BroadcastMatchEndEvent();

	UFUNCTION(NetMulticast, Reliable)
	void BroadcastRoundStartEvent();

	UFUNCTION(NetMulticast, Reliable)
	void BroadcastOnScoreEvent(int32 ScoredPlayer);

	UFUNCTION(BlueprintPure)
	int32 GetScore(int32 PlayerIndex);

	UFUNCTION(BlueprintPure)
	int32 GetMaxPlayers() const;

public:
	APongGameState();

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void Score(int32 ScoredPlayerIndex);
	void SetMaxPlayers(int32 NewMaxPlayers);

protected:
	UPROPERTY(ReplicatedUsing=OnRep_Scores)
	TArray<int32> Scores;

	UPROPERTY(ReplicatedUsing=OnRep_MaxPlayers)
	int32 MaxPlayers;

	UFUNCTION()
	void OnRep_Scores();

	UFUNCTION()
	void OnRep_MaxPlayers();

	void IncrementScore(int32 ScoredPlayerIndex);
};
