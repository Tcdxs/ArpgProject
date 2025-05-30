// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_PatrolMoving.h"

#include "ArpgProject/Enemy/CPP_EnemyAIController.h"
#include "ArpgProject/Enemy/CPP_EnemyBase.h"
#include "ArpgProject/PlayerCharacter/PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBTTask_PatrolMoving::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
		if (Enemy)
		{
			Enemy->EnemyState = EEnemyState::EES_Patrol;
			FVector PatrolLocation = BlackboardComp->GetValueAsVector("PatrolTarget");
			AIController->MoveToLocation(PatrolLocation);
			if (Enemy->GetActorLocation() == PatrolLocation)return EBTNodeResult::Succeeded;
			return EBTNodeResult::Failed;
		}
	}
	return EBTNodeResult::Failed;
}
