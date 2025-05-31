// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Patrol.h"

#include "ArpgProject/PlayerCharacter/PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/PathFollowingComponent.h"


EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	if (!BlackboardComp->GetValueAsObject("PlayerCharacter")) //未检查到玩家
	{
		Enemy = Cast<ACPP_EnemyBase>(AIController->GetPawn());
		if (Enemy)
		{
			Enemy->EnemyState = EEnemyState::EES_Patrol;
			const TArray<APatrolPoint*>& Spheres = Enemy->GetPatrolSpheres();
			if (Spheres.Num() == 0) return EBTNodeResult::Failed;
			CurrentPatrolIndex = BlackboardComp->GetValueAsInt("CurrentPatrolIndex");
			IsWait = BlackboardComp->GetValueAsBool("ShouldWait");
			if (!IsWait)
			{
				FVector NextLocation = Spheres[CurrentPatrolIndex]->GetActorLocation();
				BlackboardComp->SetValueAsVector("PatrolTarget", NextLocation);
				FAIMoveRequest MoveReq(NextLocation);
				MoveReq.SetAcceptanceRadius(5.f);
				FPathFollowingRequestResult MoveResult = AIController->MoveTo(MoveReq);
				if (MoveResult.Code == EPathFollowingRequestResult::AlreadyAtGoal)
				{
					CurrentPatrolIndex = (CurrentPatrolIndex + 1) % Spheres.Num();
					BlackboardComp->SetValueAsBool("IsWait", true);
					BlackboardComp->SetValueAsInt("CurrentPatrolIndex", CurrentPatrolIndex);
					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	return EBTNodeResult::Failed;
}
