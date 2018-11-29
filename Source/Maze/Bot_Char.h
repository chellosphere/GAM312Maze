// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Bot_Char.generated.h"

UCLASS()
class MAZE_API ABot_Char : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABot_Char();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//set the behavior tree in the editor to make it the custom tree we made
	UPROPERTY(EditAnywhere, Category = AI)
		class UBehaviorTree* BehaviorTree;
	
};
