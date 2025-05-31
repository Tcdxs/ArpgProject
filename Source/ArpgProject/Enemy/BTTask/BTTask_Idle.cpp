// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Idle.h"

#include "ArpgProject/Enemy/CPP_EnemyAIController.h"
#include "ArpgProject/PlayerCharacter/PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"


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
		if (!BlackboardComp->GetValueAsObject("PlayerCharacter"))
		{
			Enemy = Cast<ACPP_EnemyBase>(AIController->GetPawn());
			if (Enemy)
			{
				Enemy->EnemyState = EEnemyState::EES_Idle; 
				AIController->StopMovement();
				BlackboardComp->SetValueAsBool("IsWait", false);
				return EBTNodeResult::Succeeded;
			}
		}
		return EBTNodeResult::Failed;
}