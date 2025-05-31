// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArpgProject/Enemy/CPP_EnemyBase.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Chase.generated.h"

/**
 * 
 */
UCLASS()
class ARPGPROJECT_API UBTTask_Chase : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

private:
	TObjectPtr<ACPP_EnemyBase> Enemy;
	
	
};
