// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "ArpgProject/Enemy/CPP_EnemyBase.h"
#include "CPP_EnemyAnim.generated.h"

/**
 * 
 */
UCLASS()
class ARPGPROJECT_API UCPP_EnemyAnim : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

private:
	UPROPERTY(BlueprintReadOnly,Category = Character,meta=(AllowPrivateAccess=true))
	TObjectPtr<ACPP_EnemyBase> Enemy;

	UPROPERTY(BlueprintReadOnly,Category = Character,meta=(AllowPrivateAccess=true))
	TObjectPtr<UBlackboardComponent> Blackboard;

	UPROPERTY(BlueprintReadOnly,Category = Movement,meta=(AllowPrivateAccess=true))
	float Speed;

	UPROPERTY(BlueprintReadOnly,Category = Movement,meta=(AllowPrivateAccess=true))
	bool bIsAir;

	UPROPERTY(BlueprintReadOnly,Category = Movement,meta=(AllowPrivateAccess=true))
	bool bIsAttacking;
};
