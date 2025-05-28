// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_EnemyAIController.h"

#include "BehaviorTree/BlackboardComponent.h"


ACPP_EnemyAIController::ACPP_EnemyAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	check(Blackboard);

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	check(BehaviorTreeComponent);
}

void ACPP_EnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}
