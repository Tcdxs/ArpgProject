// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Patrol.h"

#include "ArpgProject/PlayerCharacter/PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"


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
	if (!BlackboardComp->GetValueAsObject("PlayerCharacter"))
	{
		if (Enemy)
		{
			Enemy->EnemyState = EEnemyState::EES_Patrol;
			const TArray<APatrolPoint*>& Spheres = Enemy->GetPatrolSpheres();
			if (Spheres.Num() == 0) return EBTNodeResult::Failed;
			CurrentPatrolIndex = BlackboardComp->GetValueAsInt("CurrentPatrolIndex");
			CurrentPatrolIndex = (CurrentPatrolIndex + 1) % Spheres.Num();
			FVector NextLocation = Spheres[CurrentPatrolIndex]->GetActorLocation();
			BlackboardComp->SetValueAsVector("PatrolTarget", NextLocation);
			BlackboardComp->SetValueAsInt("CurrentPatrolIndex", CurrentPatrolIndex);
			AIController->MoveToLocation(NextLocation);
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
