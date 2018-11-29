// Fill out your copyright notice in the Description page of Project Settings.


#include "Bot_AIController.h"
#include "Bot_TargetPoint.h"
#include "Bot_Char.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "BehaviorTree/BehaviorTree.h"

ABot_AIController::ABot_AIController()
{
	//intialing behavior tree and blackboard component for the controller

	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));

	//key's intialized for hte blackoard
	LocationToGoKey = "LocationToGo";
	CurrentTargetPoint = 0; //current target point to go to 

}

// overriding the possess fuction
void ABot_AIController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	//cast the possessed pawn to our ai class
	ABot_Char* Bot_Char = Cast<ABot_Char>(Pawn);

	if (Bot_Char) //make sure cast worked
	{
		if (Bot_Char->BehaviorTree->BlackboardAsset) //make sure we have a blackboard component
		{
			//set the blackboardcomponent for the controller to the - blackboard component on the pawn
			BlackboardComp->InitializeBlackboard(*(Bot_Char->BehaviorTree->BlackboardAsset));
																							  
		}

		//get the array of nagivational points - get a reference to all the target points in the level
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABot_TargetPoint::StaticClass(), NavPoints); 

		BehaviorTreeComp->StartTree(*Bot_Char->BehaviorTree); //start the behavior tree which will kick off the sequence
	}
}