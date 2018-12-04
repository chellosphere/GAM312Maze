// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "CameraControl.h"
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "PlayerMaze.generated.h"



UCLASS()
class MAZE_API APlayerMaze : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerMaze();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//Uproperty allows them to be edited anywhere and they appear under the character movemetn walking 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Movement: Walking", DisplayName = "Custom Walk Speed")
		int WalkS = 600;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Movement: Walking", DisplayName = "Custom Sprint Speed")
		int SprintS = 1200; //sprinting variable

							
//Pickup Variables - blueprint read write allows them to be seen in the hud blueprint
	
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Pickups")
		int totalPickups = 14;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Pickups")
		int CurrentPickups = 0;

	void AddPickup();

	

//camera variables
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	UCameraComponent* FollowCamera;
	
//turn functions
	void LookRight(float value);
	void LookUp(float value);

//modify the turn rate
	float BaseTurnRate = 45;
	float BaseLookUpRate=45;


//movement functions
	void Lateral(float Value);//foward/back movement
	void SidetoSide(float Value); //side to side movement

//sprinting fuctions
	void StartSprint();
	void EndSprint();

//void change Cameras
	void SwitchCams();


};
