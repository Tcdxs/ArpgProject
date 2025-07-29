// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackAnimNotifyState.h"

#include "ArpgProject/Enemy/CPP_EnemyBase.h"
#include "BehaviorTree/BlackboardComponent.h"


void UAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                         float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	if (!MeshComp) return;
	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	ACPP_EnemyBase* Enemy = Cast<ACPP_EnemyBase>(Owner);
	if (Enemy)
	{
		ACPP_EnemyAIController* AIController = Cast<ACPP_EnemyAIController>(Enemy->GetController());
     	if (!AIController)return;
     	
     	UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
     	if (!BlackboardComp)return;
		
		Enemy->EnableAttackCollision(true);
		UE_LOG(LogTemp,Warning,TEXT("EnableAttackCollision"));
	}
}

void UAttackAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	
}

void UAttackAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	if (!MeshComp) return;
	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	ACPP_EnemyBase* Enemy = Cast<ACPP_EnemyBase>(Owner);
	if (Enemy)
	{
		ACPP_EnemyAIController* AIController = Cast<ACPP_EnemyAIController>(Enemy->GetController());
		if (!AIController)return;
	
		UBlackboardComponent* BlackboardComp = AIController->GetBlackboardComponent();
		if (!BlackboardComp)return;
		
		Enemy->EnableAttackCollision(false);
		UE_LOG(LogTemp,Warning,TEXT("disEnableAttackCollision"));
		BlackboardComp->SetValueAsBool("bAttacking",false);
	}
}
