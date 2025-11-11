// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArpgProject/Enemy/CPP_EnemyBase.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDec_HasFoundPlayer.generated.h"

/**
 * 
 */
UCLASS()
class ARPGPROJECT_API UBTDec_HasFoundPlayer : public UBTDecorator
{
	GENERATED_BODY()
	
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	TObjectPtr<ACPP_EnemyBase> Enemy;
	
	
};
