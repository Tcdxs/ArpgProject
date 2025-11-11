// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_EnemyAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"


ACPP_EnemyAIController::ACPP_EnemyAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
	check(Blackboard);

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTree>(TEXT("BehaviorTreeComponent"));
	check(BehaviorTreeComponent);
	
	GetPathFollowingComponent()->Initialize();

}

void ACPP_EnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	GetBlackboardComponent()->InitializeBlackboard(*BehaviorTreeComponent->BlackboardAsset);
	RunBehaviorTree(BehaviorTreeComponent);
}
