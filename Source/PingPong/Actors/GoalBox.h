#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"

#include "GoalBox.generated.h"

UCLASS()
class PINGPONG_API AGoalBox : public ATriggerBox
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 PlayerIndex;

public:
	AGoalBox();
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void OnBallBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
