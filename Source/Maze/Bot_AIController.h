// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTreeComponent.h"
#include "Bot_AIController.generated.h"



UCLASS()
class MAZE_API ABot_AIController : public AAIController
{
	GENERATED_BODY()
	
	//blackboard component
	UBlackboardComponent* BlackboardComp;

	//behavior tree component
	UBehaviorTreeComponent* BehaviorTreeComp;

	//blackboard keys
	UPROPERTY(EditDefaultsOnly, Category = AI)
		FName LocationToGoKey; //place pawn is going

	//array for navigational points
	TArray<AActor*> NavPoints;

	//override the possess fuction
	virtual void Possess(APawn* Pawn) override;



public:

	//constructor for the bot controlelr
	ABot_AIController();
	int32 CurrentTargetPoint = 0; //creat the current target point


	//force override the complier for these two fuctions
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	FORCEINLINE TArray<AActor*> GetNavPoints() const { return NavPoints; }
	
	
};
