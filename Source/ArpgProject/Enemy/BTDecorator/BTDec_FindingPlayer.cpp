// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDec_FindingPlayer.h"

#include "ArpgProject/Enemy/CPP_EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTDec_FindingPlayer::UBTDec_FindingPlayer()
{
	
}

bool UBTDec_FindingPlayer::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	ACPP_EnemyAIController* AIController = Cast<ACPP_EnemyAIController>(OwnerComp.GetAIOwner());
	if (!AIController)
	{
		return true;
	}
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!BlackboardComp)
	{
		return true;
	}
	if (BlackboardComp->GetValueAsObject("PlayerCharacter"))
	{
		return false;
	}
	else
	{
		return true;
	}
}
