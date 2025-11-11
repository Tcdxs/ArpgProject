// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArpgProject/Enemy/CPP_EnemyBase.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDec_FindingPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ARPGPROJECT_API UBTDec_FindingPlayer : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTDec_FindingPlayer();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	TObjectPtr<ACPP_EnemyBase> Enemy;

	
	
	
};
