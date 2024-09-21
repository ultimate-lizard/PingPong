#include "Actors/Paddle.h"

#include "Controllers/PongControllerBase.h"

APaddle::APaddle()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicateMovement(true);

	PaddleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle Mesh"));
	PaddleMesh->CastShadow = false;
	PaddleMesh->SetIsReplicated(true);
	SetRootComponent(PaddleMesh);

	InitialLocation = FVector::ZeroVector;
}

void APaddle::BeginPlay()
{
	Super::BeginPlay();

	if (APongControllerBase* PongController = GetController<APongControllerBase>())
	{
		DisableInput(PongController);
	}

	InitialLocation = GetActorLocation();
}

void APaddle::ResetPaddle()
{
	SetActorLocation(InitialLocation);
}
