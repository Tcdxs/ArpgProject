// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArpgProject/Enemy/CPP_EnemyBase.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class ARPGPROJECT_API UBTTask_Attack : public UBTTaskNode
{
	GENERATED_BODY()
	UBTTask_Attack();
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

	UPROPERTY(EditAnywhere, Category=Animation)
	UAnimMontage* MontageToPlay;

private:
	TObjectPtr<ACPP_EnemyBase> Enemy;
};
