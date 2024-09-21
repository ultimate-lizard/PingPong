#include "Actors/Ball.h"

ABall::ABall()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicateMovement(true);

	BallSpeed = 700.0f;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball Mesh"));
	BallMesh->CastShadow = false;
	BallMesh->SetIsReplicated(true);
	SetRootComponent(BallMesh);

	bActivated = false;
	InitialLocation = FVector::ZeroVector;
}

void ABall::BeginPlay()
{
	Super::BeginPlay();
	
	InitialLocation = GetActorLocation();

	BallMesh->OnComponentHit.AddDynamic(this, &ABall::OnBallHit);
}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bActivated || !HasAuthority())
	{
		return;
	}

	AddActorWorldOffset(FVector(Direction, 0.0f) * BallSpeed * DeltaTime, true);
}

void ABall::ResetBall()
{
	bActivated = false;
	SetActorLocation(InitialLocation);
}

void ABall::ActivateBall()
{
	bActivated = true;

	Direction = FVector2D(0.5f, 0.5f);
	Direction.Normalize();
	if (FMath::RandBool())
	{
		Direction = -Direction;
	}
}

bool ABall::IsBallActivated() const
{
	return bActivated;
}

void ABall::OnBallHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Direction = Direction - 2 * Direction.Dot(FVector2D(Hit.Normal)) * FVector2D(Hit.Normal);
}
