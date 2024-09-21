#include "Actors/Paddle.h"

APaddle::APaddle()
{
	PrimaryActorTick.bCanEverTick = true;

	PaddleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Paddle Mesh"));
	PaddleMesh->CastShadow = false;
	SetRootComponent(PaddleMesh);
}
