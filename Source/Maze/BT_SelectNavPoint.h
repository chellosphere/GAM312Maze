// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BT_SelectNavPoint.generated.h"

/**
 * 
 */
UCLASS()
class MAZE_API UBT_SelectNavPoint : public UBTTaskNode
{
	GENERATED_BODY()
	
	//execute task node
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory) override;
	
	
};
