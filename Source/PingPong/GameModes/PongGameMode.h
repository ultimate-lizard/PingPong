#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "PongGameMode.generated.h"

class ABall;

UCLASS()
class PINGPONG_API APongGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxPlayers;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MatchStartDelay;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float RoundStartDelay;

public:
	APongGameMode();

	virtual void StartPlay() override;

	virtual void RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot) override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

	void StartMatch();
	bool IsMatchInProgress() const;

	void Score(int32 LostPlayerIndex);

protected:
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal = TEXT("")) override;

	void SetPlayersInputEnabled(bool bEnabled);
	void ResetPlayers();

	UFUNCTION()
	void StartRound();

	bool bMatchInProgress;

	FTimerHandle MatchDelayTimer;

	ABall* Ball;
};
