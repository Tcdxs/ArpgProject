// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Idle.h"

#include "ArpgProject/Enemy/CPP_EnemyAIController.h"
#include "ArpgProject/PlayerCharacter/PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"


UBTTask_Idle::UBTTask_Idle()
{
	bNotifyTick = true;
	RemainingWaitTime = 2.f;
}

EBTNodeResult::Type UBTTask_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACPP_EnemyAIController* AIController = Cast<ACPP_EnemyAIController>(OwnerComp.GetAIOwner());
	if (!AIController)
	{
		return EBTNodeResult::Failed;
	}
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return EBTNodeResult::Failed;
	}
	Enemy = Cast<ACPP_EnemyBase>(AIController->GetPawn());
	if (Enemy)
	{
		AIController->StopMovement();
		Enemy->EnemyState = EEnemyState::EES_Idle;
	}
	UE_LOG(LogTemp, Warning, TEXT("1"));
	RemainingWaitTime = 2.f;
	return EBTNodeResult::InProgress;
}

void UBTTask_Idle::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ACPP_EnemyAIController* AIController = Cast<ACPP_EnemyAIController>(OwnerComp.GetAIOwner());
	if (!AIController)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	if (BlackboardComp->GetValueAsObject("PlayerCharacter"))
	{
		BlackboardComp->SetValueAsBool("IsWait", false);
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	RemainingWaitTime -= DeltaSeconds;
	if (RemainingWaitTime <= 0.0f)
	{
		if (!BlackboardComp->GetValueAsObject("PlayerCharacter"))
		{
			BlackboardComp->SetValueAsBool("IsWait", false);
		}
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
