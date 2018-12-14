// Fill out your copyright notice in the Description page of Project Settings.

#include "CameraControl.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
ACameraControl::ACameraControl()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}

// Called when the game starts or when spawned
void ACameraControl::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraControl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACameraControl::SwitchCam(APlayerController* Controller, UCameraComponent* FollowCam, AActor* Player)
{

	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("inside switch cams")); //debug message
	

	if (Controller) //only do this if the controller is valid
	{
		//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("player controller valid")); //debug message
	

		if (FollowCam->bIsActive && Player) //only do this if the followcam is active and the player is valid
		{
			//set view target to the overview camera
			Controller->SetViewTarget(Overview);
			//set follow cam inactive
			FollowCam->SetActive(false); 
			//hide the player when looking over the maze
			Player->SetActorHiddenInGame(true);

			//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("in overview")); //debug message

		
			
		}
		else if (!FollowCam->bIsActive)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("in follow cam inactive")); //debug message

			if (Player)
			{
				//set follow cam active
				FollowCam->SetActive(true);
				//set the view targe to the active camera on the player
				Controller->SetViewTarget(Player);
				//see the player when behind them
				Player->SetActorHiddenInGame(false);
			}
		}
	}
}

