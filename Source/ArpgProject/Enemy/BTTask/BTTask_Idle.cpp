// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Idle.h"

#include "ArpgProject/Enemy/CPP_EnemyAIController.h"
#include "ArpgProject/PlayerCharacter/PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBTTask_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ACPP_EnemyAIController* AIController = Cast<ACPP_EnemyAIController>(OwnerComp.GetAIOwner());
	if (AIController)
	{
		UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
		if (BlackboardComp)
		{
			APlayerCharacter* Player = Cast<APlayerCharacter>(BlackboardComp->GetValueAsObject("PlayerCharacter"));
			if (Player)
			{
				AIController->SetFocus(Player,EAIFocusPriority::Gameplay);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
