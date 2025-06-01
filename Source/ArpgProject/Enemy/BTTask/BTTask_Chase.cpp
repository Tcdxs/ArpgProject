// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Chase.h"

#include "ArpgProject/PlayerCharacter/PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"


EBTNodeResult::Type UBTTask_Chase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	if (BlackboardComp->GetValueAsObject("PlayerCharacter") && !BlackboardComp->GetValueAsBool("bAttacking"))
	{
		Enemy = Cast<ACPP_EnemyBase>(AIController->GetPawn());
		if (Enemy)
		{
			Enemy->EnemyState = EEnemyState::EES_Chase; 
			BlackboardComp->SetValueAsBool("IsWait", false);
			APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(BlackboardComp->GetValueAsObject("PlayerCharacter"));
			FAIMoveRequest MoveReq(PlayerCharacter->GetActorLocation());
			MoveReq.SetAcceptanceRadius(5.f);
			FPathFollowingRequestResult MoveResult = AIController->MoveTo(MoveReq);
			//if (MoveResult.Code == EPathFollowingRequestResult::AlreadyAtGoal)
			if (BlackboardComp->GetValueAsBool("CanAttack"))
			{
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
