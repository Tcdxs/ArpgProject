// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDec_HasFoundPlayer.h"

#include "BehaviorTree/BlackboardComponent.h"


bool UBTDec_HasFoundPlayer::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
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
		return true;
	}
	else
	{
		return false;
	}
}
