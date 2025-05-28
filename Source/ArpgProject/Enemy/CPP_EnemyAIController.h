// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "CPP_EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class ARPGPROJECT_API ACPP_EnemyAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ACPP_EnemyAIController();
	
	virtual void BeginPlay() override;

protected:
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
private:
	
public:	
};
