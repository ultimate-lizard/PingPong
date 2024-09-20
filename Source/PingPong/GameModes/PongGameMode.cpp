// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameMode.h"

#include "Actors/PongPlayerStart.h"
#include "Camera/CameraActor.h"

void APongGameMode::RestartPlayerAtPlayerStart(AController* NewPlayer, AActor* StartSpot)
{
	Super::RestartPlayerAtPlayerStart(NewPlayer, StartSpot);

	if (APongPlayerStart* PongPlayerStart = Cast<APongPlayerStart>(StartSpot))
	{
		if (ACameraActor* PlayerCamera = PongPlayerStart->PlayerCamera)
		{
			if (APlayerController* PlayerController = Cast<APlayerController>(NewPlayer))
			{
				PlayerController->SetViewTarget(PlayerCamera);
			}
		}
	}
}
