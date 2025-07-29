// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ArpgProject/Enemy/CPP_EnemyBase.h"
#include "AttackAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class ARPGPROJECT_API UAttackAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, 
		float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyTick(USkeletalMeshComponent* MeshComp,UAnimSequenceBase* Animation,
		float FrameDeltaTime,const FAnimNotifyEventReference& EventReference);
	
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, 
		const FAnimNotifyEventReference& EventReference) override;

};
