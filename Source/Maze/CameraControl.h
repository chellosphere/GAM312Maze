// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "Runtime/Engine/Classes/Camera/CameraActor.h"
#include "GameFramework/Actor.h"
#include "CameraControl.generated.h"



UCLASS()
class MAZE_API ACameraControl : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraControl();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//fuction to switch cameras
	void SwitchCam(APlayerController* Controller, UCameraComponent* FollowCam,AActor* Player);


	//assign the overview cam in the editor
	UPROPERTY(EditAnywhere)
		ACameraActor* Overview;


	
};
