// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"

#include "ArpgProject/Enemy/CPP_EnemyAIController.h"
#include "ArpgProject/Enemy/CPP_EnemyBase.h"
#include "ArpgProject/PlayerCharacter/PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	if (BlackboardComp->GetValueAsObject("PlayerCharacter"))
	{
		Enemy = Cast<ACPP_EnemyBase>(AIController->GetPawn());
		if (Enemy)
		{
			if (BlackboardComp->GetValueAsBool("CanAttack") && !BlackboardComp->GetValueAsBool("bAttacking"))
			{
				Enemy->EnemyState = EEnemyState::EES_Attack;
				APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(BlackboardComp->GetValueAsObject("PlayerCharacter"));
				AIController->StopMovement();
				BlackboardComp->SetValueAsBool("bAttacking",true);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
