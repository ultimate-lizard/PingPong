#include "Actors/GoalBox.h"

#include "Components/ShapeComponent.h"
#include "Actors/Ball.h"
#include "GameModes/PongGameMode.h"

AGoalBox::AGoalBox()
{
	PlayerIndex = 0;
}

void AGoalBox::BeginPlay()
{
	Super::BeginPlay();

	if (UShapeComponent* Collision = GetCollisionComponent())
	{
		Collision->OnComponentBeginOverlap.AddDynamic(this, &AGoalBox::OnBallBeginOverlap);
	}
}

void AGoalBox::OnBallBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->IsA<ABall>())
	{
		return;
	}

	if (UWorld* World = GetWorld())
	{
		if (APongGameMode* PongGameMode = World->GetAuthGameMode<APongGameMode>())
		{
			PongGameMode->Score(PlayerIndex);
		}
	}
}
