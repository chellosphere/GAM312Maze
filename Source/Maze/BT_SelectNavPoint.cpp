// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_SelectNavPoint.h"
#include "Bot_TargetPoint.h"
#include "Bot_AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBT_SelectNavPoint::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	ABot_AIController* Bot_Controller = Cast<ABot_AIController>(OwnerComp.GetAIOwner());

	if (Bot_Controller)
	{
		//get the blackboard component
		UBlackboardComponent* BlackboardComp = Bot_Controller->GetBlackboardComp();

		//the current target is set as the value of the key LocationToGo
		ABot_TargetPoint* CurrentTarget = Cast<ABot_TargetPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));

		//get the array of avalible target points
		TArray<AActor*> AvalibleTargetPoints = Bot_Controller->GetNavPoints();

		ABot_TargetPoint* NextTarget = nullptr;

		if (Bot_Controller->CurrentTargetPoint != AvalibleTargetPoints.Num() - 1)
		{
			//increment the current target point and  set the next target equal to the result
			NextTarget = Cast<ABot_TargetPoint>(AvalibleTargetPoints[++Bot_Controller->CurrentTargetPoint]);
		}
		else//there is nothing left in the array
		{
			NextTarget = Cast<ABot_TargetPoint>(AvalibleTargetPoints[0]); //go back to the start
			Bot_Controller->CurrentTargetPoint = 0;
		}

		//set the location for the blackboard key 
		BlackboardComp->SetValueAsObject("LocationToGo", NextTarget);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}

