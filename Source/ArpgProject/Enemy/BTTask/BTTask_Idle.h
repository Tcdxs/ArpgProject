// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArpgProject/Enemy/CPP_EnemyBase.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ArpgProject/PlayerCharacter/PlayerCharacter.h"
#include "BTTask_Idle.generated.h"

/**
 * 
 */
UCLASS()
class ARPGPROJECT_API UBTTask_Idle : public UBTTaskNode
{
	GENERATED_BODY()
	UBTTask_Idle();
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
	
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere)
	float RemainingWaitTime;
	
	TObjectPtr<ACPP_EnemyBase> Enemy;
};
