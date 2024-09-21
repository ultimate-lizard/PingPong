#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Ball.generated.h"

UCLASS()
class PINGPONG_API ABall : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float BallSpeed;

public:	
	ABall();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void ResetBall();
	void ActivateBall();
	bool IsBallActivated() const;

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* BallMesh;

	UFUNCTION()
	void OnBallHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	bool bActivated;

	FVector InitialLocation;

	FVector2D Direction;
};
